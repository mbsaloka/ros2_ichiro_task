// #include "robot_localization/ObjectRecognizer.hpp"

// #define MAX_RANGE 0.15

// ObjectRecognizer::ObjectRecognizer() : Node("object_recognizer") {
//     recognized_objects_ =
//         create_subscription<vision_msgs::msg::Detection2DArray>(
//             "/camera", 1,
//             std::bind(&ObjectRecognizer::cameraCallback, this,
//                       std::placeholders::_1));
// }

// void ObjectRecognizer::cameraCallback(
//     const vision_msgs::msg::Detection2DArray::SharedPtr msg) {
//     auto recognized_objects_value = msg->detections;
// }

// int main(int argc, char *argv[]) {
//     rclcpp::init(argc, argv);
//     auto avoider = std::make_shared<ObjectRecognizer>();
//     rclcpp::spin(avoider);
//     rclcpp::shutdown();
//     return 0;
// }