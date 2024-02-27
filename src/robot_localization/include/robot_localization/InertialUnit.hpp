#ifndef INERTIAL_UNIT_HPP
#define INERTIAL_UNIT_HPP

#include <memory>

#include "rclcpp/rclcpp.hpp"
#include "sensor_msgs/msg/imu.hpp"
#include "my_interfaces/msg/double.hpp"

class InertialUnit : public rclcpp::Node {
public:
    explicit InertialUnit();

private:
    void imuCallback(const sensor_msgs::msg::Imu::SharedPtr msg);

    rclcpp::Subscription<sensor_msgs::msg::Imu>::SharedPtr imu_sub_;

    rclcpp::Publisher<my_interfaces::msg::Double>::SharedPtr orientation_pub_;

    double roll_, pitch_, yaw_;
};

#endif  // INERTIAL_UNIT_HPP