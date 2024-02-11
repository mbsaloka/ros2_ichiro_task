#ifndef WEBOTS_ROS2_PLUGIN_EXAMPLE_HPP
#define WEBOTS_ROS2_PLUGIN_EXAMPLE_HPP

#include "rclcpp/macros.hpp"
#include "webots_ros2_driver/PluginInterface.hpp"
#include "webots_ros2_driver/WebotsNode.hpp"

#include "my_interfaces/msg/velocity.hpp"
#include "rclcpp/rclcpp.hpp"

#include <webots/Robot.hpp>
#include <webots/Motor.hpp>

using namespace webots;

namespace my_robot_driver {
class MyRobotDriver : public webots_ros2_driver::PluginInterface {
public:
    void step() override;
    void init(
        webots_ros2_driver::WebotsNode *node,
        std::unordered_map<std::string, std::string> &parameters) override;

private:
    void velocityCallback(const my_interfaces::msg::Velocity::SharedPtr msg);

    rclcpp::Subscription<my_interfaces::msg::Velocity>::SharedPtr
        velocity_subscription_;
    my_interfaces::msg::Velocity velocity_msg;

    Robot *robot;
    Motor *leftMotor;
    Motor *rightMotor;
};
}  // namespace my_robot_driver
#endif