cmake_minimum_required(VERSION 3.5)
project(robot_localization)

if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 14)
endif()

# Besides the package specific dependencies we also need the `pluginlib` and `webots_ros2_driver`
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(my_interfaces REQUIRED)
find_package(vision_msgs REQUIRED)
find_package(pluginlib REQUIRED)
find_package(webots_ros2_driver REQUIRED)

# Export the plugin configuration file
pluginlib_export_plugin_description_file(webots_ros2_driver my_robot_driver.xml)

# RobotController
add_executable(robot_controller src/RobotController.cpp)
ament_target_dependencies(robot_controller rclcpp my_interfaces)

# ObjectRecognizer
include_directories(
  include
)
add_executable(object_recognizer
  src/ObjectRecognizer.cpp
)
ament_target_dependencies(object_recognizer
  rclcpp
  vision_msgs
)
install(TARGETS
  object_recognizer
  DESTINATION lib/${PROJECT_NAME}
)
install(
  DIRECTORY include/
  DESTINATION include
)

# MyRobotDriver library
add_library(
  ${PROJECT_NAME}
  SHARED
  src/MyRobotDriver.cpp
)
target_include_directories(
  ${PROJECT_NAME}
  PRIVATE
  include
)
ament_target_dependencies(
  ${PROJECT_NAME}
  pluginlib
  rclcpp
  my_interfaces
  vision_msgs
  webots_ros2_driver
)
install(TARGETS
  ${PROJECT_NAME}
  robot_controller
  object_recognizer
  ARCHIVE DESTINATION lib
  LIBRARY DESTINATION lib
  RUNTIME DESTINATION bin
  DESTINATION lib/${PROJECT_NAME}
)
# Install additional directories.
install(DIRECTORY
  launch
  resource
  worlds
  DESTINATION share/${PROJECT_NAME}/
)
ament_export_include_directories(
  include
)
ament_export_libraries(
  ${PROJECT_NAME}
  my_interfaces
)
ament_package()