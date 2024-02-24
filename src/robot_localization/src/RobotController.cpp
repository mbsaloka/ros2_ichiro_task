#include <memory>

#include "my_interfaces/msg/velocity.hpp"
#include "my_interfaces/msg/boolean.hpp"
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
    rclcpp::Publisher<my_interfaces::msg::Boolean>::SharedPtr restart_pub_;
};

RobotController::RobotController(std::shared_ptr<rclcpp::Node> nh)
    : nh_(nh), linear_(0), angular_(0) {
    velocity_pub_ =
        nh_->create_publisher<my_interfaces::msg::Velocity>("/velocity", 1);
    restart_pub_ =
        nh_->create_publisher<my_interfaces::msg::Boolean>("/restart", 1);
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
    char c, last_c = 0;
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
    puts("Use \"wasd\" to move e-puck.\n'b' to brake. 'r' to restart.");

    for (;;) {
        // get the next event from the keyboard
        if (::read(kb, &c, 1) < 0) {
            perror("read():");
            exit(-1);
        }

        linear_ = angular_ = 0;

        if (last_c != c) {
            switch (c) {
                case 'a':
                    std::cout << "LEFT" << std::endl;
                    angular_ = 1.0;
                    dirty = true;
                    last_c = c;
                    break;
                case 'd':
                    std::cout << "RIGHT" << std::endl;
                    angular_ = -1.0;
                    dirty = true;
                    last_c = c;
                    break;
                case 'w':
                    std::cout << "UP" << std::endl;
                    linear_ = 0.12;
                    dirty = true;
                    last_c = c;
                    break;
                case 's':
                    std::cout << "DOWN" << std::endl;
                    linear_ = -0.12;
                    dirty = true;
                    last_c = c;
                    break;
                case 'b':
                    std::cout << "BREAK" << std::endl;
                    linear_ = 0.0;
                    angular_ = 0.0;
                    dirty = true;
                    last_c = c;
                    break;
                case 'r':
                    std::cout << "RESTART" << std::endl;
                    linear_ = 0.0;
                    angular_ = 0.0;
                    dirty = true;
                    last_c = c;
                    break;
            }
        }

        my_interfaces::msg::Velocity msg;
        msg.linear = linear_;
        msg.angular = angular_;

        my_interfaces::msg::Boolean restart_msg;
        restart_msg.flag = true;

        if (dirty == true) {
            if (c == 'r') {
                restart_pub_->publish(restart_msg);
            }
            velocity_pub_->publish(msg);

            dirty = false;
        }
    }

    return;
}