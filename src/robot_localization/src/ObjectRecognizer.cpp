#include "robot_localization/ObjectRecognizer.hpp"

ObjectRecognizer::ObjectRecognizer() : Node("object_recognizer") {
    camera_sub_ =
        create_subscription<webots_ros2_msgs::msg::CameraRecognitionObjects>(
            "/robot_vision/recognitions/webots", 1,
            std::bind(&ObjectRecognizer::cameraCallback, this,
                      std::placeholders::_1));
}

void ObjectRecognizer::cameraCallback(
    const webots_ros2_msgs::msg::CameraRecognitionObjects::SharedPtr msg) {
    recognized_objects_.clear();

    for (const auto &detection : msg->objects) {
        RecognizedObject recognized_obj;
        recognized_obj.x = detection.pose.pose.position.z;
        recognized_obj.y = -detection.pose.pose.position.x;
        recognized_objects_.push_back(recognized_obj);
    }

    for (const auto obj : recognized_objects_) {
        std::cout << "X: " << obj.x << " Y: " << obj.y << std::endl;
    }
    std::cout << "-------------------------" << std::endl;
}

int main(int argc, char *argv[]) {
    rclcpp::init(argc, argv);
    auto recognizer = std::make_shared<ObjectRecognizer>();
    rclcpp::spin(recognizer);
    rclcpp::shutdown();
    return 0;
}