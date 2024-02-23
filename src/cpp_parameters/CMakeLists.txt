cmake_minimum_required(VERSION 3.5)
project(cpp_parameters)

# Default to C++14
if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 14)
endif()

# Find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)

# Create a target executable
add_executable(my_node src/my_node.cpp)

# Link the executable with the vendor library
ament_target_dependencies(my_node rclcpp)

# Install the executable
install(TARGETS
  my_node
  DESTINATION lib/${PROJECT_NAME}
)

# Install the launch file
install(DIRECTORY
  launch
  DESTINATION share/${PROJECT_NAME}
)

# Add ament package (for ROS 2)
ament_package()
