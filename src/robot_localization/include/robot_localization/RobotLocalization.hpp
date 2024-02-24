#ifndef ROBOT_LOCALIZATION_HPP
#define ROBOT_LOCALIZATION_HPP

#include <memory>
#include <vector>
#include <cmath>
#include <chrono>
#include <random>

#include "rclcpp/rclcpp.hpp"
#include "my_interfaces/msg/velocity.hpp"
#include "my_interfaces/msg/vector_objects.hpp"
#include "my_interfaces/msg/boolean.hpp"
#include "my_interfaces/msg/pose.hpp"

#define TIME_STEP 0.032
#define FIELD_WIDTH 450
#define FIELD_LENGTH 600
#define NUM_PARTICLES 600
#define NUM_LANDMARK 14
#define CAM_POSE_X 0.04
#define START_X 0
#define START_Y 0
#define START_W 0
#define VAR_X 10
#define VAR_Y 10
#define VAR_W 0.05
#define A_FAST 1.0
#define A_SLOW 0.0005
#define TO_RAD M_PI / 180.0

typedef struct recognizedObj_t {
    double x;
    double y;
} RecognizedObject;

typedef struct particle_t {
    double x;
    double y;
    double w;
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
    void motion_update();
    void sensor_update();
    double calculate_total_likelihood(const Particle &particle);
    double calculate_object_likelihood(const RecognizedObject &measurement,
                                       const Particle &particle);
    void estimation();
    void print_particles();
    void print_odometry();

    rclcpp::Subscription<my_interfaces::msg::VectorObjects>::SharedPtr obj_sub_;
    rclcpp::Subscription<my_interfaces::msg::Velocity>::SharedPtr vel_sub_;
    rclcpp::Subscription<my_interfaces::msg::Boolean>::SharedPtr res_sub_;
    rclcpp::Subscription<my_interfaces::msg::Pose>::SharedPtr odom_sub_;

    double robot_pose_[3] = {0.0, 0.0, 0.0};
    std::vector<Particle> particles_;
    std::vector<RecognizedObject> recognized_objects_;
    unsigned num_particles_, iteration_ = 0;
    bool firstIteration_ = true;
    double linear_vel_, angular_vel_;
    const double LANDMARK[NUM_LANDMARK][2] = {
        {0.0, 0.0},     {0.0, 80.0},     {0.0, -80.0},   {0.0, 300.0},
        {0.0, -300.0},  {240.0, 0.0},    {350.0, 250.0}, {350.0, -250.0},
        {450.0, 250.0}, {450.0, -250.0}, {450.0, 300.0}, {450.0, -300.0},
        {450.0, 130.0}, {450.0, -130.0},
    };
    std::chrono::time_point<std::chrono::high_resolution_clock> lastTime_,
        currentTime_, timer_;

    double w_fast, w_slow;
    Particle pose_estimation_;
};

#endif  // ROBOT_LOCALIZATION_HPP