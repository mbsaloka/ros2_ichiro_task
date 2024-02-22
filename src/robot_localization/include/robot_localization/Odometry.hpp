#ifndef ODOMETRY_HPP
#define ODOMETRY_HPP

#include <memory>
#include <chrono>
#include <functional>
#include <cmath>

#include "rclcpp/rclcpp.hpp"
#include "my_interfaces/msg/velocity.hpp"
#include "my_interfaces/msg/pose.hpp"
#include "my_interfaces/msg/boolean.hpp"

using namespace std::chrono_literals;

class Odometry : public rclcpp::Node {
public:
    explicit Odometry();

private:
    void velocityCallback(const my_interfaces::msg::Velocity ::SharedPtr msg);
    void restartCallback(const my_interfaces::msg::Boolean::SharedPtr msg);

    void timer_callback();

    rclcpp::TimerBase::SharedPtr timer_;

    rclcpp::Subscription<my_interfaces::msg::Velocity>::SharedPtr vel_sub_;
    rclcpp::Publisher<my_interfaces::msg::Pose>::SharedPtr pose_pub_;
    rclcpp::Subscription<my_interfaces::msg::Boolean>::SharedPtr res_sub_;

    double linear_vel_;
    double angular_vel_;
    double robot_pose_[3] = {0.0, 0.0, 0.0};
};

#endif  // ODOMETRY_HPP