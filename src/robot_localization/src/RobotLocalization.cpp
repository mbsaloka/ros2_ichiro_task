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

    mcl();
}

void RobotLocalization::mcl() {
    currentTime_ = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = currentTime_ - lastTime_;
    double seconds = duration.count();

    motion_update();
    if ((seconds >= 1.0 || firstIteration_) && recognized_objects_.size() > 0) {
        if (!firstIteration_) {
            resample_particles();
        }
        calculate_weight();

        lastTime_ = currentTime_;
        firstIteration_ = false;
        iteration_++;
    }

    print_particles();
    print_odometry();
}

void RobotLocalization::init_particles() {
    std::vector<Particle> new_particles;
    std::random_device xrd, yrd, wrd;
    std::normal_distribution<double> xrg(START_X, VAR_X), yrg(START_Y, VAR_Y),
        wrg(START_W, VAR_W);

    for (int i = 0; i < NUM_PARTICLES; i++) {
        Particle p;
        p.base_x = xrg(xrd);
        p.base_y = yrg(yrd);
        p.base_theta = wrg(wrd);
        p.x = p.base_x;
        p.y = p.base_y;
        p.theta = p.base_theta;
        p.weight = 1.0 / NUM_PARTICLES;
        new_particles.push_back(p);
    }

    particles_ = new_particles;
    num_particles_ = NUM_PARTICLES;
}

void RobotLocalization::resample_particles() {
    std::vector<Particle> new_particles;
    std::random_device xrd, yrd, wrd;
    const double var_x = 5.0, var_y = 5.0, var_w = 0.01;
    const int min_num_particle = 10;
    int n;

    for (size_t i = 0; i < particles_.size(); ++i) {
        if (particles_[i].weight > (double)1 / (double)particles_.size()) {
            new_particles.push_back(particles_[i]);

            n = int(particles_[i].weight * 100);
            std::normal_distribution<double> xrg(particles_[i].base_x, var_x),
                yrg(particles_[i].base_y, var_y),
                wrg(particles_[i].base_theta, var_w);
            for (int i = 0; i < n; i++) {
                Particle p;
                p.base_x = xrg(xrd);
                p.base_y = yrg(yrd);
                p.base_theta = wrg(wrd);
                p.x = p.base_x + robot_pose_[0] * 100;
                p.y = p.base_y + robot_pose_[1] * 100;
                p.theta = p.base_theta + robot_pose_[2];
                p.weight = particles_[i].weight / n;

                new_particles.push_back(p);
            }
        }
    }

    if (new_particles.size() > min_num_particle) {
        particles_ = new_particles;
        num_particles_ = particles_.size();
    }
}

void RobotLocalization::motion_update() {
    for (int i = 0; i < num_particles_; ++i) {
        particles_[i].x = particles_[i].base_x + robot_pose_[0] * 100;
        particles_[i].y = particles_[i].base_y + robot_pose_[1] * 100;
        particles_[i].theta = particles_[i].base_theta + robot_pose_[2];
    }
}

void RobotLocalization::calculate_weight() {
    double sum_weights = 0.0;
    for (int i = 0; i < num_particles_; ++i) {
        double likelihood = calculate_total_likelihood(particles_[i]);
        particles_[i].weight = likelihood;
        sum_weights += particles_[i].weight;
    }

    for (int i = 0; i < num_particles_; ++i) {
        particles_[i].weight /= sum_weights;
    }
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
    double relative_position_x, relative_position_y;
    double dx, dy, x_rot, y_rot, exponent, likelihood;
    double best_likelihood = 0.0;

    for (int i = 0; i < 14; i++) {
        dx = (measurement.x + CAM_POSE_X) * 100;
        dy = particle.y + measurement.y * 100;

        x_rot = dx * cos(particle.theta) - dy * sin(particle.theta);
        y_rot = dx * sin(particle.theta) + dy * cos(particle.theta);

        relative_position_x = particle.x + x_rot;
        relative_position_y = particle.y + y_rot;

        exponent =
            -0.5 *
            (pow((LANDMARK[i][0] - relative_position_x), 2) / pow(sigma_x, 2) +
             pow((LANDMARK[i][1] - relative_position_y), 2) / pow(sigma_y, 2));

        likelihood = exp(exponent) / (2 * M_PI * sigma_x * sigma_y);

        if (likelihood > best_likelihood) {
            best_likelihood = likelihood;
        }
    }

    return best_likelihood;
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
                      << std::setprecision(2) << particles_[i].theta << "]"
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
    std::cout << "Best sample: " << std::fixed << std::setprecision(5)
              << best_sample_weight << " (particle num " << best_sample_index
              << " [" << std::fixed << std::setprecision(2)
              << particles_[best_sample_index].x << ", " << std::fixed
              << std::setprecision(2) << particles_[best_sample_index].y << ", "
              << std::fixed << std::setprecision(2)
              << particles_[best_sample_index].theta << "])" << std::endl;
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