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
        "/restart_by_key", 1,
        std::bind(&RobotLocalization::restartCallback, this,
                  std::placeholders::_1));
    odom_sub_ = create_subscription<my_interfaces::msg::Pose>(
        "/odometry", 1,
        std::bind(&RobotLocalization::odometryCallback, this,
                  std::placeholders::_1));
    imu_sub_ = create_subscription<my_interfaces::msg::Double>(
        "/orientation", 1,
        std::bind(&RobotLocalization::imuCallback, this,
                  std::placeholders::_1));
    restart_pub_ =
        create_publisher<my_interfaces::msg::Boolean>("/restart_by_code", 1);

    init_particles();
    lastTime_ = std::chrono::high_resolution_clock::now();
    timer_ = std::chrono::high_resolution_clock::now();
}

void RobotLocalization::objectsCallback(
    const my_interfaces::msg::VectorObjects::SharedPtr msg) {
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
    std::cout << "[ROBOT IS KIDNAPPED. Wait for the update...]" << std::endl;
    restart();
}

void RobotLocalization::restart() {
    kidnap_ = true;
    if (recognized_objects_.size() > 0) {
        std::cout << "[LOCALIZATION RESTARTED]" << std::endl;

        auto res_msg = std::make_unique<my_interfaces::msg::Boolean>();
        res_msg->flag = true;
        restart_pub_->publish(std::move(res_msg));

        iteration_ = 0;
        robot_pose_[2] = imu_orientation_;
        init_particles();
        calculate_weight();
        resample_particles();
        kidnap_ = false;
    } else {
        std::cout << "[MOVE ROBOT TO RECOGNIZE OBJECT]" << std::endl;
    }
}

void RobotLocalization::odometryCallback(
    const my_interfaces::msg::Pose::SharedPtr msg) {
    robot_pose_[0] = msg->x;
    robot_pose_[1] = msg->y;
    robot_pose_[2] = msg->theta;

    if (kidnap_) {
        restart();
    } else {
        mcl();
    }
}

void RobotLocalization::imuCallback(
    const my_interfaces::msg::Double::SharedPtr msg) {
    imu_orientation_ = msg->data;
}

void RobotLocalization::mcl() {
    currentTime_ = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = currentTime_ - lastTime_;
    double seconds = duration.count();

    motion_update();
    if ((seconds >= TIME_STEP || firstIteration_)) {
        if (recognized_objects_.size() > 0) {
            std::vector<Particle> temp_particles = particles_;
            if (!firstIteration_) {
                resample_particles();
            }
            calculate_weight();

            if (get_sum_weight() == 0.0) {
                particles_ = temp_particles;
                // restart();
            }

        } else {
            restart();
        }
        iteration_++;
        lastTime_ = currentTime_;
        firstIteration_ = false;
    }
    estimate_pose();
    print_particles();
    print_odometry();
    recognized_objects_.clear();
}

void RobotLocalization::init_particles() {
    std::vector<Particle> new_particles;
    if (!kidnap_) {
        std::random_device xrd, yrd, wrd;
        std::normal_distribution<double> xrg(START_X, VAR_X),
            yrg(START_Y, VAR_Y), wrg(START_W, VAR_W);

        for (int i = 0; i < NUM_PARTICLES; i++) {
            Particle p;
            p.base_x = xrg(xrd);
            p.base_y = yrg(yrd);
            p.base_w = wrg(wrd);
            p.x = p.base_x;
            p.y = p.base_y;
            p.w = p.base_w;
            p.weight = 1.0 / NUM_PARTICLES;
            new_particles.push_back(p);
        }
    } else {
        const int x_gap = 5, y_gap = 5;
        num_particles_ = FIELD_WIDTH * FIELD_LENGTH;
        double angle = robot_pose_[2];

        for (int i = -FIELD_WIDTH / 2; i < FIELD_WIDTH / 2; i += x_gap) {
            for (int j = -FIELD_LENGTH / 2; j < FIELD_LENGTH / 2; j += y_gap) {
                Particle p;
                p.base_x = i;
                p.base_y = j;
                p.base_w = angle;
                p.x = i;
                p.y = j;
                p.w = angle;
                p.weight = 1.0 / num_particles_;
                new_particles.push_back(p);
            }
        }
    }
    particles_ = new_particles;
    num_particles_ = particles_.size();
}

void RobotLocalization::resample_particles() {
    std::vector<Particle> new_particles;
    if (!kidnap_) {
        std::random_device xrd, yrd, wrd;
        const double var_x = 5.0, var_y = 5.0, var_w = 0.01;
        int n;

        for (size_t i = 0; i < particles_.size(); ++i) {
            if (particles_[i].weight >=
                (double)1 / (double)particles_.size() / 10.0) {
                new_particles.push_back(particles_[i]);

                n = int(particles_[i].weight * 100);
                std::normal_distribution<double> xrg(particles_[i].base_x,
                                                     var_x),
                    yrg(particles_[i].base_y, var_y),
                    wrg(particles_[i].base_w, var_w);
                for (int i = 0; i < n; i++) {
                    Particle p;
                    p.base_x = xrg(xrd);
                    p.base_y = yrg(yrd);
                    p.base_w = wrg(wrd);
                    p.x = p.base_x + robot_pose_[0] * 100;
                    p.y = p.base_y + robot_pose_[1] * 100;
                    p.w = p.base_w + robot_pose_[2];
                    p.weight = particles_[i].weight / n;
                    new_particles.push_back(p);
                }
            }
        }
    } else {
        for (auto &p : particles_) {
            if (p.weight > 0.00001) {
                new_particles.push_back(p);
            }
        }

        if (new_particles.size() < NUM_PARTICLES) {
            kidnap_ = false;
        }
    }
    particles_ = new_particles;
    num_particles_ = particles_.size();
}

void RobotLocalization::motion_update() {
    for (int i = 0; i < num_particles_; ++i) {
        particles_[i].x = particles_[i].base_x + robot_pose_[0] * 100;
        particles_[i].y = particles_[i].base_y + robot_pose_[1] * 100;
        particles_[i].w = particles_[i].base_w + robot_pose_[2];
    }
}

void RobotLocalization::calculate_weight() {
    for (int i = 0; i < num_particles_; ++i) {
        double likelihood = calculate_total_likelihood(particles_[i]);
        particles_[i].weight = likelihood;
    }

    double sum_weight = get_sum_weight();
    if (sum_weight == 0.0) {
        for (int i = 0; i < num_particles_; ++i) {
            particles_[i].weight = 1 / num_particles_;
        }
    } else {
        for (int i = 0; i < num_particles_; ++i) {
            particles_[i].weight /= sum_weight;
        }
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
    double current_likelihood = 0.0;

    for (int i = 0; i < NUM_LANDMARK; i++) {
        dx = (measurement.x + CAM_POSE_X) * 100;
        dy = measurement.y * 100;

        x_rot = dx * cos(particle.w) - dy * sin(particle.w);
        y_rot = dx * sin(particle.w) + dy * cos(particle.w);

        relative_position_x = particle.x + x_rot;
        relative_position_y = particle.y + y_rot;

        exponent =
            -0.5 *
            (pow((LANDMARK[i][0] - relative_position_x), 2) / pow(sigma_x, 2) +
             pow((LANDMARK[i][1] - relative_position_y), 2) / pow(sigma_y, 2));

        likelihood = exp(exponent) / (2 * M_PI * sigma_x * sigma_y);

        if (likelihood > current_likelihood) {
            current_likelihood = likelihood;
        }
    }

    return current_likelihood;
}

void RobotLocalization::estimate_pose() {
    double x_mean = 0.0;
    double y_mean = 0.0;
    double w_mean = 0.0;
    for (auto p : particles_) {
        x_mean += (1.0 / num_particles_) * p.x;
        y_mean += (1.0 / num_particles_) * p.y;
        w_mean += (1.0 / num_particles_) * p.w;
    }
    pose_estimation_.x = x_mean;
    pose_estimation_.y = y_mean;
    pose_estimation_.w = w_mean;
}

double RobotLocalization::get_sum_weight() {
    double sum = 0.0;
    for (auto p : particles_) {
        sum += p.weight;
    }
    return sum;
}

void RobotLocalization::print_particles() {
    double sum_samples = 0.0;

    for (int i = 0; i < num_particles_; i++) {
        if (particles_[i].weight > 0.0001) {
            std::cout << "Particle " << std::setw(5) << i
                      << "  weight: " << std::fixed << std::setprecision(5)
                      << particles_[i].weight << std::setw(5) << " ["
                      << std::fixed << std::setprecision(2) << particles_[i].x
                      << ", " << std::fixed << std::setprecision(2)
                      << particles_[i].y << ", " << std::fixed
                      << std::setprecision(2) << particles_[i].w << "]"
                      << std::endl;

            sum_samples += particles_[i].weight;
        }
    }

    std::cout << "Iteration " << iteration_ << std::endl;
    std::cout << "Num particles: " << num_particles_ << std::endl;
    std::cout << "Sum weights: " << sum_samples << std::endl;
    std::cout << "Pose estimation: "
              << " [" << std::fixed << std::setprecision(2)
              << pose_estimation_.x << ", " << std::fixed
              << std::setprecision(2) << pose_estimation_.y << ", "
              << std::fixed << std::setprecision(2) << pose_estimation_.w
              << "])" << std::endl;
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