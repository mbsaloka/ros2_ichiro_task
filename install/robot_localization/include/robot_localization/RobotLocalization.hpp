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
#include "my_interfaces/msg/double.hpp"

#define TIME_STEP 0.032
#define MAX_SPEED 6.28
#define FIELD_WIDTH 900
#define FIELD_LENGTH 600
#define NUM_PARTICLES 1000
#define NUM_LANDMARK 23
#define CAM_POSE_X 0.04
#define START_X 0
#define START_Y 0
#define START_W 0
#define VAR_X 10
#define VAR_Y 10
#define VAR_W 0.05

typedef struct recognizedObj_t {
    double x;
    double y;
} RecognizedObject;

typedef struct particle_t {
    double base_x;
    double base_y;
    double base_w;
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
    void imuCallback(const my_interfaces::msg::Double::SharedPtr msg);

    void init_particles();
    void resample_particles();
    void motion_update();
    void calculate_weight();
    double calculate_total_likelihood(const Particle &particle);
    double calculate_object_likelihood(const RecognizedObject &measurement,
                                       const Particle &particle);
    void estimate_pose();
    void print_particles();
    void print_odometry();
    void restart();

    rclcpp::Subscription<my_interfaces::msg::VectorObjects>::SharedPtr obj_sub_;
    rclcpp::Subscription<my_interfaces::msg::Velocity>::SharedPtr vel_sub_;
    rclcpp::Subscription<my_interfaces::msg::Boolean>::SharedPtr res_sub_;
    rclcpp::Subscription<my_interfaces::msg::Pose>::SharedPtr odom_sub_;
    rclcpp::Subscription<my_interfaces::msg::Double>::SharedPtr imu_sub_;

    double robot_pose_[3] = {0.0, 0.0, 0.0};
    std::vector<Particle> particles_;
    std::vector<RecognizedObject> recognized_objects_;
    Particle pose_estimation_;
    unsigned num_particles_, iteration_ = 0;
    bool firstIteration_ = true, kidnap_ = false;
    double linear_vel_, angular_vel_, imu_orientation_;

#define NUM_LANDMARK 23

    const double LANDMARK[NUM_LANDMARK][2] = {
        {0.0, 0.0},       {0.0, 80.0},     {0.0, -80.0},     {0.0, 300.0},
        {0.0, -300.0},    {240.0, 0.0},    {350.0, 250.0},   {350.0, -250.0},
        {450.0, 250.0},   {450.0, -250.0}, {450.0, 300.0},   {450.0, -300.0},
        {450.0, 130.0},   {450.0, -130.0}, {-240.0, 0.0},    {-350.0, 250.0},
        {-350.0, -250.0}, {-450.0, 250.0}, {-450.0, -250.0}, {-450.0, 300.0},
        {-450.0, -300.0}, {-450.0, 130.0}, {-450.0, -130.0},
    };

    std::chrono::time_point<std::chrono::high_resolution_clock> lastTime_,
        currentTime_, timer_;
};

#endif  // ROBOT_LOCALIZATION_HPP