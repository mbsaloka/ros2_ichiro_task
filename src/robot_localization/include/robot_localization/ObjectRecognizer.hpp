// #include <memory>
// #include <vector>

// #include "rclcpp/rclcpp.hpp"
// #include "vision_msgs/msg/detection2_d_array.hpp"

// typedef struct recognizedObj_t {
//     const double *position;
// } RecognizedObject;

// class ObjectRecognizer : public rclcpp::Node {
// public:
//     explicit ObjectRecognizer();

// private:
//     void cameraCallback(
//         const vision_msgs::msg::Detection2DArray::SharedPtr msg);

//     rclcpp::Subscription<vision_msgs::msg::Detection2DArray>::SharedPtr
//         camera_sub_;

//     std::vector<RecognizedObject> recognized_objects_;
// };