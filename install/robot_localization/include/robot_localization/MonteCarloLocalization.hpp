#include <memory>
#include <vector>
#include <utility>

#include "rclcpp/rclcpp.hpp"
#include "my_interfaces/msg/velocity.hpp"
#include "my_interfaces/msg/vector_objects.hpp"

#define TIME_STEP 64
#define MAX_SPEED 6.28
#define FIELD_WIDTH 450
#define FIELD_LENGTH 600
#define NUM_ANGLE 24

struct RecognizedObject {
    const double *position;
};

class Particle {
private:
    double base_x;
    double base_y;
    double base_theta;

public:
    double x;
    double y;
    double theta;
    Particle(double base_x, double base_y, double base_theta);
};

class RobotLocalization {
private:
    double robot_pose[3] = {0.0, 0.0, 0.0};

    std::vector<RecognizedObject> camera_recognition();
    double calculate_object_likelihood(const RecognizedObject &measurement,
                                       const Particle &particle);
    double calculate_total_likelihood(
        const std::vector<RecognizedObject> &object_measurements,
        const Particle &particle);
    void init_particles(std::vector<Particle> &particles,
                        std::vector<double> &weights);
    void resample_particles(std::vector<Particle> &particles,
                            std::vector<double> &weights);
    void print_particles(const std::vector<Particle> &particles,
                         const std::vector<double> &weights, int num_particles);

public:
    RobotLocalization();
    ~RobotLocalization();
    void run();
};
