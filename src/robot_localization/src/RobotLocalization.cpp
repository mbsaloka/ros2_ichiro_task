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

    init_particles();
    lastTime = std::chrono::high_resolution_clock::now();
    timer = std::chrono::high_resolution_clock::now();
    firstIteration = true;
    iteration = 0;
}

void RobotLocalization::objectsCallback(
    const my_interfaces::msg::VectorObjects::SharedPtr msg) {
    recognized_objects_.clear();

    for (const auto &detection : msg->objects) {
        RecognizedObject recognized_obj;
        recognized_obj.x = detection.x;
        recognized_obj.y = detection.y;
        recognized_objects_.push_back(recognized_obj);
        // std::cout << "[object] X: " << recognized_obj.x
        //   << " Y: " << recognized_obj.y << std::endl;
    }
    // std::cout << "-------------------------" << std::endl;

    mcl();
}

void RobotLocalization::velocityCallback(
    const my_interfaces::msg::Velocity::SharedPtr msg) {
    linear_vel_ = msg->linear;
    angular_vel_ = msg->angular;

    // std::cout << "[velocity] linear: " << linear_vel_
    //           << " angular: " << angular_vel_ << std::endl;
    // std::cout << ">>>>>>>>>>>>>>>>>>>>>>" << std::endl;
}

void RobotLocalization::mcl() {
    // std::cout << "[MCL TEST A]" << std::endl;
    // init_particles();
    // auto lastTime = std::chrono::high_resolution_clock::now();
    // double firstIteration = true;
    // int iteration = 0;

    // while (true) {
    currentTime = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = currentTime - lastTime;
    double seconds = duration.count();

    // std::cout << "[MCL TEST B]" << std::endl;

    std::chrono::duration<double> duration_vel = currentTime - timer;
    double dt = duration_vel.count();
    if (dt >= 0.032) {
        // std::cout << "[MCL TEST C]" << std::endl;
        timer = currentTime;
        robot_pose_[0] += linear_vel_ * cos(robot_pose_[2]) * dt;
        robot_pose_[1] += linear_vel_ * sin(robot_pose_[2]) * dt;
        robot_pose_[2] -= angular_vel_ * dt * 0.905;

        if (robot_pose_[2] > M_PI) {
            robot_pose_[2] -= 2 * M_PI;
        } else if (robot_pose_[2] < -M_PI) {
            robot_pose_[2] += 2 * M_PI;
        }
    }

    // std::cout << "[MCL TEST D]" << std::endl;

    if (seconds >= 1.0 || firstIteration) {
        // std::cout << "[MCL TEST E]" << std::endl;
        firstIteration = false;
        lastTime = currentTime;
        iteration++;

        for (int i = 0; i < num_particles_; ++i) {
            // std::cout << "[MCL TEST F]" << std::endl;
            particles_[i].x = particles_[i].base_x + robot_pose_[0] * 100;
            particles_[i].y = particles_[i].base_y + robot_pose_[1] * 100;
            particles_[i].theta = particles_[i].base_theta + robot_pose_[2];
        }

        // std::cout << "[MCL TEST G]" << std::endl;
        if (num_particles_ > 3) {
            std::cout
                << "[Calculating likelihood for each particle. Please wait...]"
                << std::endl;
            for (int i = 0; i < num_particles_; ++i) {
                double likelihood = 0.0;
                if (recognized_objects_.size() > 0) {
                    // Likelihood evaluation
                    likelihood = calculate_total_likelihood(particles_[i]);
                }

                // Assign likelihood as weight to the particle
                particles_[i].weight = likelihood;
            }
            // std::cout << "[MCL TEST I]" << std::endl;

            // Normalize weights
            double sum_weights = 0.0;
            for (int i = 0; i < num_particles_; ++i) {
                sum_weights += particles_[i].weight;
            }

            for (int i = 0; i < num_particles_; ++i) {
                particles_[i].weight /= sum_weights;
            }
        }
        // Print particles
        // std::cout << "[MCL TEST J]" << std::endl;
        std::cout << iteration << " iteration" << std::endl;
        print_particles();
        std::cout << "Num particles: " << num_particles_ << std::endl;

        // Resampling particles based on weights
        resample_particles();
        num_particles_ = particles_.size();
    } else if (num_particles_ == 0) {
        // std::cout << "[MCL TEST K]" << std::endl;
        init_particles();
        num_particles_ = particles_.size();
    } else {
        // std::cout << "[MCL TEST L]" << std::endl;
        std::cout << iteration << " iteration" << std::endl;
        print_particles();
        std::cout << "Num particles: " << num_particles_ << std::endl;
    }
    // std::cout << "[MCL TEST M]" << std::endl;

    // Print odometry
    std::cout << "----------------------------------------" << std::endl;
    std::cout << "Robot pose: [" << robot_pose_[0] << " " << robot_pose_[1]
              << " " << robot_pose_[2] << "]" << std::endl;
    std::cout << ">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>" << std::endl;

    // Delay to maintain constant time step
    // auto end = std::chrono::high_resolution_clock::now();
    // auto elapsed =
    //     std::chrono::duration_cast<std::chrono::milliseconds>(end -
    //     start);
    // auto remaining_time = std::chrono::milliseconds(TIME_STEP) - elapsed;

    // if (remaining_time.count() > 0) {
    //     std::this_thread::sleep_for(remaining_time);
    // }
    // }
}

void RobotLocalization::init_particles() {
    std::vector<Particle> new_particles;
    std::vector<double> angles;

    num_particles_ = FIELD_WIDTH * FIELD_LENGTH * NUM_ANGLE;

    for (int i = 0; i < 12; i++) {
        double angle = (double)i / 12 * M_PI;
        angles.push_back(angle);
    }

    for (int i = 12; i > 0; i--) {
        double angle = (double)i / 12 * M_PI * -1;
        angles.push_back(angle);
    }

    for (auto angle : angles) {
        for (int i = 0; i < FIELD_WIDTH; ++i) {
            for (int j = -FIELD_LENGTH / 2; j < FIELD_LENGTH / 2; ++j) {
                Particle particle;
                particle.base_x = i;
                particle.base_y = j;
                particle.x = i;
                particle.y = j;
                particle.base_theta = angle;
                particle.theta = angle;
                particle.weight = 1.0 / num_particles_;
                new_particles.push_back(particle);
            }
        }
    }

    particles_ = new_particles;
}

void RobotLocalization::resample_particles() {
    std::vector<Particle> new_particles;

    for (size_t i = 0; i < particles_.size(); ++i) {
        if (particles_[i].weight > 0.0001) {
            new_particles.push_back(particles_[i]);
        }
    }

    particles_ = new_particles;
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
    double sigma_x = 1.0;
    double sigma_y = 1.0;

    double best_likelihood = 0.0;
    for (int i = 0; i < 14; i++) {
        double relative_position_x = particle.x + measurement.x * 100;
        double relative_position_y = particle.y + measurement.y * 100;

        double dx = relative_position_x - particle.x;
        double dy = relative_position_y - particle.y;

        double x_rot = dx * cos(particle.theta) - dy * sin(particle.theta);
        double y_rot = dx * sin(particle.theta) + dy * cos(particle.theta);

        relative_position_x = x_rot + particle.x;
        relative_position_y = y_rot + particle.y;

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

    std::cout << "Sum weights: " << sum_samples << std::endl;
    std::cout << "Best sample: " << std::fixed << std::setprecision(5)
              << best_sample_weight << " (particle num " << best_sample_index
              << " [" << std::fixed << std::setprecision(2)
              << particles_[best_sample_index].x << ", " << std::fixed
              << std::setprecision(2) << particles_[best_sample_index].y << ", "
              << std::fixed << std::setprecision(2)
              << particles_[best_sample_index].theta << "])" << std::endl;
}

void quit(int sig) {
    (void)sig;
    rclcpp::shutdown();
    exit(0);
}

void spinThread() {
    auto node = std::make_shared<RobotLocalization>();
    rclcpp::spin(node);
}

int main(int argc, char **argv) {
    rclcpp::init(argc, argv);

    auto node = std::make_shared<RobotLocalization>();
    rclcpp::spin(node);

    // std::thread spin_thread(spinThread);
    // signal(SIGINT, quit);

    // RobotLocalization localization;
    // localization.mcl();

    // spin_thread.join();

    rclcpp::shutdown();

    return 0;
}