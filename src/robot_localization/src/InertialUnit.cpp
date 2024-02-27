#include "robot_localization/InertialUnit.hpp"

InertialUnit::InertialUnit() : Node("inertial_unit") {
    imu_sub_ = create_subscription<sensor_msgs::msg::Imu>(
        "/imu", 1,
        std::bind(&InertialUnit::imuCallback, this, std::placeholders::_1));

    orientation_pub_ =
        create_publisher<my_interfaces::msg::Double>("/orientation", 1);
}

void InertialUnit::imuCallback(const sensor_msgs::msg::Imu::SharedPtr msg) {
    auto message = std::make_unique<my_interfaces::msg::Double>();
    double qx = msg->orientation.x;
    double qy = msg->orientation.y;
    double qz = msg->orientation.z;
    double qw = msg->orientation.w;

    double norm = std::sqrt(qx * qx + qy * qy + qz * qz + qw * qw);
    double x = qx / norm;
    double y = qy / norm;
    double z = qz / norm;
    double w = qw / norm;

    roll_ = std::atan2(2 * (w * x + y * z), 1 - 2 * (x * x + y * y));
    pitch_ = std::asin(2 * (w * y - z * x));
    yaw_ = std::atan2(2 * (w * z + x * y), 1 - 2 * (y * y + z * z));

    message->data = yaw_;

    orientation_pub_->publish(std::move(message));
}

int main(int argc, char *argv[]) {
    rclcpp::init(argc, argv);
    auto imu = std::make_shared<InertialUnit>();
    rclcpp::spin(imu);
    rclcpp::shutdown();
    return 0;
}