#include "robot_localization/MyRobotDriver.hpp"

#include "rclcpp/rclcpp.hpp"
#include "my_interfaces/msg/velocity.hpp"
#include <cstdio>
#include <functional>
#include <webots/Robot.hpp>
#include <webots/Motor.hpp>

#define HALF_DISTANCE_BETWEEN_WHEELS 0.026
#define WHEEL_RADIUS 0.02

namespace my_robot_driver {
void MyRobotDriver::init(
    webots_ros2_driver::WebotsNode *node,
    std::unordered_map<std::string, std::string> &parameters) {
    robot = new Robot();

    rightMotor = robot->getMotor("right wheel motor");
    leftMotor = robot->getMotor("left wheel motor");

    rightMotor->setPosition(INFINITY);
    rightMotor->setVelocity(0.0);

    leftMotor->setPosition(INFINITY);
    leftMotor->setVelocity(0.0);

    velocity_subscription_ =
        node->create_subscription<my_interfaces::msg::Velocity>(
            "/velocity", rclcpp::SensorDataQoS().reliable(),
            std::bind(&MyRobotDriver::velocityCallback, this,
                      std::placeholders::_1));
}

void MyRobotDriver::velocityCallback(
    const my_interfaces::msg::Velocity::SharedPtr msg) {
    velocity_msg.linear = msg->linear;
    velocity_msg.angular = msg->angular;
}

void MyRobotDriver::step() {
    auto forward_speed = velocity_msg.linear;
    auto angular_speed = velocity_msg.angular;

    auto command_motor_left =
        (forward_speed - angular_speed * HALF_DISTANCE_BETWEEN_WHEELS) /
        WHEEL_RADIUS;
    auto command_motor_right =
        (forward_speed + angular_speed * HALF_DISTANCE_BETWEEN_WHEELS) /
        WHEEL_RADIUS;

    leftMotor->setVelocity(command_motor_left);
    rightMotor->setVelocity(command_motor_right);
}
}  // namespace my_robot_driver

#include "pluginlib/class_list_macros.hpp"
PLUGINLIB_EXPORT_CLASS(my_robot_driver::MyRobotDriver,
                       webots_ros2_driver::PluginInterface)