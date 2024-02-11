#include "robot_localization/ObjectRecognizer.hpp"

#define MAX_RANGE 0.15

ObjectRecognizer::ObjectRecognizer() : Node("object_recognizer") {
    camera_sub_ = create_subscription<vision_msgs::msg::Detection2DArray>(
        "/robot_vision", 1,
        std::bind(&ObjectRecognizer::cameraCallback, this,
                  std::placeholders::_1));
}

void ObjectRecognizer::cameraCallback(
    const vision_msgs::msg::Detection2DArray::SharedPtr msg) {
    recognized_objects_.clear();

    for (const auto &detection : msg->detections) {
        RecognizedObject recognized_obj;
        recognized_obj.x = &detection.results[0].pose.pose.position.x;
        recognized_obj.y = &detection.results[0].pose.pose.position.y;
    }

    for (const auto &obj : recognized_objects_) {
        std::cout << "X: " << *obj.x << " Y: " << *obj.y << std::endl;
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