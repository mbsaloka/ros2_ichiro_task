#include <memory>
#include <vector>
#include <utility>
#include <cmath>
#include <chrono>
#include <thread>
#include <signal.h>

#include "rclcpp/rclcpp.hpp"
#include "my_interfaces/msg/velocity.hpp"
#include "my_interfaces/msg/vector_objects.hpp"
#include "my_interfaces/msg/boolean.hpp"
#include "my_interfaces/msg/pose.hpp"

#define TIME_STEP 32
#define MAX_SPEED 6.28
#define FIELD_WIDTH 450
#define FIELD_LENGTH 600
#define NUM_ANGLE 24
#define CAM_POSE_X 0.04

typedef struct recognizedObj_t {
    double x;
    double y;
} RecognizedObject;

typedef struct particle_t {
    double base_x;
    double base_y;
    double base_theta;
    double x;
    double y;
    double theta;
    double weight;
} Particle;

class RobotLocalization : public rclcpp::Node {
public:
    explicit RobotLocalization();
    void mcl();

private:
    void objectsCallback(
        const my_interfaces::msg::VectorObjects::SharedPtr msg);
    void velocityCallback(const my_interfaces::msg::Velocity::SharedPtr msg);
    void restartCallback(const my_interfaces::msg::Boolean::SharedPtr msg);
    void odometryCallback(const my_interfaces::msg::Pose::SharedPtr msg);

    void init_particles();
    void resample_particles();
    double calculate_total_likelihood(const Particle &particle);
    double calculate_object_likelihood(const RecognizedObject &measurement,
                                       const Particle &particle);
    void print_particles();

    rclcpp::Subscription<my_interfaces::msg::VectorObjects>::SharedPtr obj_sub_;
    rclcpp::Subscription<my_interfaces::msg::Velocity>::SharedPtr vel_sub_;
    rclcpp::Subscription<my_interfaces::msg::Boolean>::SharedPtr res_sub_;
    rclcpp::Subscription<my_interfaces::msg::Pose>::SharedPtr odom_sub_;

    double robot_pose_[3] = {0.0, 0.0, 0.0};
    std::vector<Particle> particles_;
    std::vector<RecognizedObject> recognized_objects_;
    int num_particles_;
    double linear_vel_;
    double angular_vel_;
    double LANDMARK[14][2] = {
        {0.0, 0.0},     {0.0, 80.0},     {0.0, -80.0},   {0.0, 300.0},
        {0.0, -300.0},  {240.0, 0.0},    {350.0, 250.0}, {350.0, -250.0},
        {450.0, 250.0}, {450.0, -250.0}, {450.0, 300.0}, {450.0, -300.0},
        {450.0, 130.0}, {450.0, -130.0},
    };

    std::chrono::time_point<std::chrono::high_resolution_clock> lastTime,
        currentTime, timer;
    bool firstIteration;
    unsigned iteration;
};
