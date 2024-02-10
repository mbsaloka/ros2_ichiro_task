#include <memory>

#include "my_interfaces/msg/velocity.hpp"
#include "rclcpp/rclcpp.hpp"

#include <signal.h>
#include <termios.h>
#include <stdio.h>
#include <memory.h>
#include <unistd.h>

class RobotController {
public:
    explicit RobotController(std::shared_ptr<rclcpp::Node> nh);
    void keyLoop();

private:
    std::shared_ptr<rclcpp::Node> nh_;
    double linear_, angular_;
    rclcpp::Publisher<my_interfaces::msg::Velocity>::SharedPtr velocity_pub_;
};

RobotController::RobotController(std::shared_ptr<rclcpp::Node> nh)
    : nh_(nh), linear_(0), angular_(0) {
    velocity_pub_ =
        nh_->create_publisher<my_interfaces::msg::Velocity>("/velocity", 1);
}

int kb = 0;
struct termios cooked, raw;

void quit(int sig) {
    (void)sig;
    tcsetattr(kb, TCSANOW, &cooked);
    rclcpp::shutdown();
    exit(0);
}

int main(int argc, char** argv) {
    rclcpp::init(argc, argv);
    auto node = rclcpp::Node::make_shared("robot_controller");
    RobotController robot_controller(node);

    signal(SIGINT, quit);

    robot_controller.keyLoop();

    return (0);
}

void RobotController::keyLoop() {
    char c;
    bool dirty = false;

    // get the console in raw mode
    tcgetattr(kb, &cooked);
    memcpy(&raw, &cooked, sizeof(struct termios));
    raw.c_lflag &= ~(ICANON | ECHO);
    // Setting a new line, then end of file
    raw.c_cc[VEOL] = 1;
    raw.c_cc[VEOF] = 2;
    tcsetattr(kb, TCSANOW, &raw);

    puts("Reading from keyboard");
    puts("---------------------------");
    puts("Use arrow keys to move the turtle.");

    for (;;) {
        // get the next event from the keyboard
        if (::read(kb, &c, 1) < 0) {
            perror("read():");
            exit(-1);
        }

        linear_ = angular_ = 0;
        // ROS_DEBUG("value: 0x%02X\n", c);

        switch (c) {
            case 'a':
                std::cout << "LEFT" << std::endl;
                angular_ = 0.1;
                dirty = true;
                break;
            case 'd':
                // ROS_DEBUG("RIGHT");
                std::cout << "RIGHT" << std::endl;
                angular_ = -0.1;
                dirty = true;
                break;
            case 'w':
                // ROS_DEBUG("UP");
                std::cout << "UP" << std::endl;
                linear_ = 0.1;
                dirty = true;
                break;
            case 's':
                // ROS_DEBUG("DOWN");
                std::cout << "DOWN" << std::endl;
                linear_ = -0.1;
                dirty = true;
                break;
        }

        my_interfaces::msg::Velocity msg;
        msg.linear = linear_;
        msg.angular = angular_;

        if (dirty == true) {
            velocity_pub_->publish(msg);
            dirty = false;
        }
    }

    return;
}