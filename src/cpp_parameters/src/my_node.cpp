#include "rclcpp/rclcpp.hpp"
#include <string>
#include <array>

class MyNode : public rclcpp::Node {
public:
    MyNode(const std::array<double, 3>& arg) : Node("my_node"), my_arg(arg) {
        RCLCPP_INFO(this->get_logger(), "Received argument: %f %f %f",
                    my_arg[0], my_arg[1], my_arg[2]);
    }

private:
    std::array<double, 3> my_arg;
};

int main(int argc, char** argv) {
    rclcpp::init(argc, argv);

    if (argc != 4) {
        RCLCPP_ERROR(rclcpp::get_logger("rclcpp"),
                     "Usage: my_node <x> <y> <w>");
        return 1;
    }

    std::array<double, 3> my_arg = {
        std::stod(argv[1]),
        std::stod(argv[2]),
        std::stod(argv[3]),
    };

    rclcpp::spin(std::make_shared<MyNode>(my_arg));

    rclcpp::shutdown();
    return 0;
}
