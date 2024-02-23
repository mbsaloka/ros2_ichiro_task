#ifndef OBJECT_RECOGNIZER_HPP
#define OBJECT_RECOGNIZER_HPP

#include <memory>
#include <vector>

#include "rclcpp/rclcpp.hpp"
#include "webots_ros2_msgs/msg/camera_recognition_objects.hpp"
#include "my_interfaces/msg/vector_objects.hpp"
#include "my_interfaces/msg/object.hpp"

typedef struct RecognizedObject {
    double x;
    double y;
} RecognizedObject;

class ObjectRecognizer : public rclcpp::Node {
public:
    explicit ObjectRecognizer();

private:
    void cameraCallback(
        const webots_ros2_msgs::msg::CameraRecognitionObjects::SharedPtr msg);

    rclcpp::Subscription<
        webots_ros2_msgs::msg::CameraRecognitionObjects>::SharedPtr camera_sub_;

    rclcpp::Publisher<my_interfaces::msg::VectorObjects>::SharedPtr object_pub_;

    std::vector<RecognizedObject> recognized_objects_;
};

#endif  // OBJECT_RECOGNIZER_HPP