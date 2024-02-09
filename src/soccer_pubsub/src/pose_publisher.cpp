#include <chrono>
#include <functional>
#include <memory>
#include <string>

#include "rclcpp/rclcpp.hpp"
#include "my_interfaces/msg/pose.hpp"

using namespace std::chrono_literals;

class MinimalPublisher : public rclcpp::Node {
public:
    MinimalPublisher() : Node("minimal_publisher"), count_(1) {
        publisher_ =
            this->create_publisher<my_interfaces::msg::Pose>("topic", 10);
        timer_ = this->create_wall_timer(
            500ms, std::bind(&MinimalPublisher::timer_callback, this));
    }

private:
    void timer_callback() {
        auto message = my_interfaces::msg::Pose();
        message.x = this->count_;
        message.y = this->count_ * 1.2;
        message.theta = this->count_ * 1.5;
        this->count_ += 0.1;
        RCLCPP_INFO_STREAM(
            this->get_logger(),
            "Publishing: 'x: " << message.x << ", y: " << message.y
                               << ", theta: " << message.theta << "'");
        publisher_->publish(message);
    }
    rclcpp::TimerBase::SharedPtr timer_;
    rclcpp::Publisher<my_interfaces::msg::Pose>::SharedPtr publisher_;
    double count_;
};

int main(int argc, char* argv[]) {
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<MinimalPublisher>());
    rclcpp::shutdown();
    return 0;
}