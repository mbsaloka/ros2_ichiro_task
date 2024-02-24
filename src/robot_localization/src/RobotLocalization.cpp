#include "robot_localization/RobotLocalization.hpp"

using namespace std::chrono;

RobotLocalization::RobotLocalization() : Node("robot_localization") {
    obj_sub_ = create_subscription<my_interfaces::msg::VectorObjects>(
        "/recognized_objects", 1,
        std::bind(&RobotLocalization::objectsCallback, this,
                  std::placeholders::_1));
    vel_sub_ = create_subscription<my_interfaces::msg::Velocity>(
        "/velocity", 1,
        std::bind(&RobotLocalization::velocityCallback, this,
                  std::placeholders::_1));
    res_sub_ = create_subscription<my_interfaces::msg::Boolean>(
        "/restart", 1,
        std::bind(&RobotLocalization::restartCallback, this,
                  std::placeholders::_1));
    odom_sub_ = create_subscription<my_interfaces::msg::Pose>(
        "/odometry", 1,
        std::bind(&RobotLocalization::odometryCallback, this,
                  std::placeholders::_1));

    init_particles();
    lastTime_ = std::chrono::high_resolution_clock::now();
    timer_ = std::chrono::high_resolution_clock::now();
}

void RobotLocalization::objectsCallback(
    const my_interfaces::msg::VectorObjects::SharedPtr msg) {
    recognized_objects_.clear();

    for (const auto &detection : msg->objects) {
        RecognizedObject recognized_obj;
        recognized_obj.x = detection.x;
        recognized_obj.y = detection.y;
        recognized_objects_.push_back(recognized_obj);
    }
}

void RobotLocalization::velocityCallback(
    const my_interfaces::msg::Velocity::SharedPtr msg) {
    linear_vel_ = msg->linear;
    angular_vel_ = msg->angular;
}

void RobotLocalization::restartCallback(
    const my_interfaces::msg::Boolean::SharedPtr msg) {
    init_particles();
}

void RobotLocalization::odometryCallback(
    const my_interfaces::msg::Pose::SharedPtr msg) {
    robot_pose_[0] = msg->x;
    robot_pose_[1] = msg->y;
    robot_pose_[2] = msg->theta;

    iteration_++;
    mcl();
}

void RobotLocalization::mcl() {
    motion_update();
    sensor_update();
    estimation();

    print_particles();
    print_odometry();

    resample_particles();
}

void RobotLocalization::init_particles() {
    std::random_device x_rd, y_rd, w_rd;
    std::uniform_real_distribution<double> x_rgen(0, 450), y_rgen(-300, 300),
        w_rgen(0.0, 360.0);
    for (int i = 0; i < NUM_PARTICLES; i++) {
        Particle p;
        p.x = x_rgen(x_rd);
        p.y = y_rgen(y_rd);
        p.w = w_rgen(w_rd);
        p.weight = 1.0 / NUM_PARTICLES;
        particles_.push_back(p);
    }
}

void RobotLocalization::resample_particles() {
    std::vector<Particle> plist;

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> rg(0.0, 1.0 / NUM_PARTICLES);
    double r = rg(gen);
    double c = particles_[0].weight;
    int idx = 0;
    std::random_device rd1;
    std::mt19937 gen1(rd1());
    std::random_device rd2;
    std::mt19937 gen2(rd2());
    std::uniform_real_distribution<double> xrg(0, 450), yrg(-300, 300),
        wrg(0, 360);
    double random_prob = (1.0 - (w_fast / w_slow));
    std::bernoulli_distribution random_gen(std::max(0.0, random_prob));
    for (int i = 0; i < NUM_PARTICLES; i++) {
        if (random_gen(gen1)) {
            Particle p;
            p.x = xrg(gen2);
            p.y = yrg(gen2);
            p.w = wrg(gen2);
            p.weight = 1.0 / NUM_PARTICLES;
            plist.push_back(p);
        } else {
            double u = r + ((double)i / NUM_PARTICLES);
            while (u > c) {
                idx += 1;
                c += particles_[idx].weight;
            }
            plist.push_back(particles_[idx]);
        }
    }
    particles_ = plist;
}

void RobotLocalization::motion_update() {
    static std::random_device xrd, yrd, wrd;
    static std::normal_distribution<> xgen(0.0, VAR_X), ygen(0.0, VAR_Y),
        wgen(0.0, VAR_W);
    for (auto &p : particles_) {
        double dx = robot_pose_[0];
        double dy = robot_pose_[1];
        double dw = robot_pose_[2] * 180.0 / M_PI;

        double static_noise_x = xgen(xrd) / 5.0;
        double static_noise_y = ygen(yrd) / 5.0;
        double static_noise_w = wgen(wrd) / 1.0;
        double dynamic_noise_x = fabs(dx) * xgen(xrd) / 5.0;
        double dynamic_noise_y = fabs(dy) * ygen(yrd) / 5.0;
        double dynamic_noise_w = fabs(dw) * wgen(wrd) / 3.0;
        double x_yterm =
            fabs(dy) * xgen(xrd) /
            30.0;  // dynamic noise on x-direction because of y motion
        double x_wterm =
            fabs(dw) * xgen(xrd) /
            30.0;  // dynamic noise on x-direction because of w motion
        double y_xterm =
            fabs(dx) * ygen(yrd) /
            30.0;  // dynamic noise on y-direction because of x motion
        double y_wterm =
            fabs(dw) * ygen(yrd) /
            30.0;  // dynamic noise on y-direction because of w motion
        double w_xterm =
            fabs(dx) * wgen(wrd) /
            2.0;  // dynamic noise on w-direction because of x motion
        double w_yterm =
            fabs(dy) * wgen(wrd) /
            2.0;  // dynamic noise on w-direction because of y motion
        p.x += dx + static_noise_x + dynamic_noise_x + x_yterm + x_wterm;
        p.y += dy + static_noise_y + dynamic_noise_y + y_xterm + y_wterm;
        p.w += dw + static_noise_w + dynamic_noise_w + w_xterm + w_yterm;
        while (p.w > 360.) {
            p.w -= 360.;
        }
        while (p.w < 0.) {
            p.w += 360.;
        }
    }
}

void RobotLocalization::sensor_update() {
    int n_data = recognized_objects_.size();
    if (n_data <= 0)
        return;
    double weight_sum = 0.0;
    for (auto &p : particles_) {
        double likelihood = calculate_total_likelihood(p);
        p.weight = likelihood;
        weight_sum += p.weight;
    }
    for (auto &p : particles_) {
        p.weight /= weight_sum;
    }
    double w_avg = 0.0;
    w_avg = weight_sum / NUM_PARTICLES;
    w_slow = w_slow + A_SLOW * (w_avg - w_slow);
    w_fast = w_fast + A_FAST * (w_avg - w_fast);
    resample_particles();
}

double RobotLocalization::calculate_total_likelihood(const Particle &particle) {
    double total_likelihood = 1.0;
    for (const auto &object_measurement : recognized_objects_) {
        total_likelihood *=
            calculate_object_likelihood(object_measurement, particle);
    }

    return total_likelihood;
}

double RobotLocalization::calculate_object_likelihood(
    const RecognizedObject &measurement, const Particle &particle) {
    const double sigma_x = 1.0, sigma_y = 1.0;
    double best_likelihood = 0.0;

    for (int i = 0; i < 14; i++) {
        double dx = (measurement.x + CAM_POSE_X) * 100;
        double dy = measurement.y * 100;

        double x_rot = dx * cos(particle.w) - dy * sin(particle.w);
        double y_rot = dx * sin(particle.w) + dy * cos(particle.w);

        double relative_position_x = particle.x + x_rot;
        double relative_position_y = particle.y + y_rot;

        double exponent =
            -0.5 *
            (pow((LANDMARK[i][0] - relative_position_x), 2) / pow(sigma_x, 2) +
             pow((LANDMARK[i][1] - relative_position_y), 2) / pow(sigma_y, 2));

        double likelihood = exp(exponent) / (2 * M_PI * sigma_x * sigma_y);

        if (likelihood > best_likelihood) {
            best_likelihood = likelihood;
        }
    }

    return best_likelihood;
}

void RobotLocalization::estimation() {
    double x_mean = 0.0;
    double y_mean = 0.0;
    double w_mean = 0.0;
    for (auto p : particles_) {
        x_mean += (1.0 / NUM_PARTICLES) * p.x;
        y_mean += (1.0 / NUM_PARTICLES) * p.y;
        double wm_tmp = w_mean;
        while (wm_tmp > 360.)
            wm_tmp -= 360.;
        while (wm_tmp < 0.)
            wm_tmp += 360.;
        double dw = p.w - wm_tmp;
        if (dw > 180.) {
            dw = -(360. - dw);
        } else if (dw < -180.) {
            dw = 360. + dw;
        }
        w_mean += (1.0 / NUM_PARTICLES) * (720. / 180.) * dw;
    }
    while (w_mean > 360.)
        w_mean -= 360.;
    while (w_mean < 0.)
        w_mean += 360.;
    pose_estimation_.x = x_mean;
    pose_estimation_.y = y_mean;
    pose_estimation_.w = w_mean;
}

void RobotLocalization::print_particles() {
    double sum_samples = 0.0;
    double best_sample_weight = 0.0;
    int best_sample_index = 0;

    for (int i = 0; i < num_particles_; i++) {
        if (particles_[i].weight > 0.00001) {
            std::cout << "Particle " << std::setw(5) << i
                      << "  weight: " << std::fixed << std::setprecision(5)
                      << particles_[i].weight << std::setw(5) << " ["
                      << std::fixed << std::setprecision(2) << particles_[i].x
                      << ", " << std::fixed << std::setprecision(2)
                      << particles_[i].y << ", " << std::fixed
                      << std::setprecision(2) << particles_[i].w << "]"
                      << std::endl;
            sum_samples += particles_[i].weight;

            if (particles_[i].weight > best_sample_weight) {
                best_sample_weight = particles_[i].weight;
                best_sample_index = i;
            }
        }
    }

    std::cout << "Iteration " << iteration_ << std::endl;
    std::cout << "Num particles: " << num_particles_ << std::endl;
    std::cout << "Sum weights: " << sum_samples << std::endl;
    std::cout << "Pose Estimation: "
              << " [" << std::fixed << std::setprecision(2)
              << particles_[best_sample_index].x << ", " << std::fixed
              << std::setprecision(2) << particles_[best_sample_index].y << ", "
              << std::fixed << std::setprecision(2)
              << particles_[best_sample_index].w << "])" << std::endl;
}

void RobotLocalization::print_odometry() {
    std::cout << "----------------------------------------" << std::endl;
    std::cout << "Robot move: [" << robot_pose_[0] * 100.0 << " "
              << robot_pose_[1] * 100.0 << " " << robot_pose_[2] << "]"
              << std::endl;
    std::cout << ">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>" << std::endl;
}

int main(int argc, char **argv) {
    rclcpp::init(argc, argv);

    auto node = std::make_shared<RobotLocalization>();
    rclcpp::spin(node);
    rclcpp::shutdown();

    return 0;
}