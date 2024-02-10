#include <memory>

#include "rclcpp/rclcpp.hpp"
#include "my_interfaces/msg/velocity.hpp"
using std::placeholders::_1;

class MinimalSubscriber : public rclcpp::Node {
public:
    MinimalSubscriber() : Node("minimal_subscriber") {
        subscription_ = this->create_subscription<my_interfaces::msg::Velocity>(
            "topic", 10,
            std::bind(&MinimalSubscriber::topic_callback, this, _1));
    }

private:
    void topic_callback(const my_interfaces::msg::Velocity& msg) const {
        RCLCPP_INFO_STREAM(this->get_logger(),
                           "I heard: 'linear: " << msg.linear << ", angular: "
                                                << msg.angular << "'");
    }
    rclcpp::Subscription<my_interfaces::msg::Velocity>::SharedPtr subscription_;
};

int main(int argc, char* argv[]) {
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<MinimalSubscriber>());
    rclcpp::shutdown();
    return 0;
}