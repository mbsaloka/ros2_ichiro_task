#include <memory>
#include <vector>

#include "rclcpp/rclcpp.hpp"
// #include "vision_msgs/msg/detection2_d_array.hpp"
#include "webots_ros2_msgs/msg/camera_recognition_objects.hpp"

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

    std::vector<RecognizedObject> recognized_objects_;
};