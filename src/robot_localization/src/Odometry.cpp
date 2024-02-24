#include "robot_localization/Odometry.hpp"

Odometry::Odometry() : Node("odometry") {
    vel_sub_ = create_subscription<my_interfaces::msg::Velocity>(
        "/velocity", 1,
        std::bind(&Odometry::velocityCallback, this, std::placeholders::_1));

    pose_pub_ = create_publisher<my_interfaces::msg::Pose>("/odometry", 1);

    res_sub_ = create_subscription<my_interfaces::msg::Boolean>(
        "/restart", 1,
        std::bind(&Odometry::restartCallback, this, std::placeholders::_1));

    timer_ = this->create_wall_timer(
        32ms, std::bind(&Odometry::timer_callback, this));
}

void Odometry::velocityCallback(
    const my_interfaces::msg::Velocity::SharedPtr msg) {
    linear_vel_ = msg->linear;
    angular_vel_ = msg->angular;
}

void Odometry::timer_callback() {
    auto message = my_interfaces::msg::Pose();
    const double x_err = 0.855;
    const double y_err = 0.855;
    const double w_err = 0.77;
    const double dt = TIME_STEP;

    robot_pose_[2] += angular_vel_ * dt * w_err;
    robot_pose_[0] += linear_vel_ * cos(robot_pose_[2]) * dt * x_err;
    robot_pose_[1] += linear_vel_ * sin(robot_pose_[2]) * dt * y_err;

    if (robot_pose_[2] > M_PI) {
        robot_pose_[2] -= 2 * M_PI;
    } else if (robot_pose_[2] < -M_PI) {
        robot_pose_[2] += 2 * M_PI;
    }

    message.x = robot_pose_[0];
    message.y = robot_pose_[1];
    message.theta = robot_pose_[2];

    pose_pub_->publish(message);
}

void Odometry::restartCallback(
    const my_interfaces::msg::Boolean::SharedPtr msg) {
    robot_pose_[0] = 0.0;
    robot_pose_[1] = 0.0;
    robot_pose_[2] = 0.0;
}

int main(int argc, char *argv[]) {
    rclcpp::init(argc, argv);
    auto odometry = std::make_shared<Odometry>();
    rclcpp::spin(odometry);
    rclcpp::shutdown();
    return 0;
}