cmake_minimum_required(VERSION 3.8)
project(soccer_pubsub)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(my_interfaces REQUIRED)

add_executable(pose_talker src/pose_publisher.cpp)
ament_target_dependencies(pose_talker rclcpp my_interfaces)

add_executable(pose_listener src/pose_subscriber.cpp)
ament_target_dependencies(pose_listener rclcpp my_interfaces)

add_executable(velocity_talker src/velocity_publisher.cpp)
ament_target_dependencies(velocity_talker rclcpp my_interfaces)

add_executable(velocity_listener src/velocity_subscriber.cpp)
ament_target_dependencies(velocity_listener rclcpp my_interfaces)

install(TARGETS
  pose_talker
  pose_listener
  velocity_talker
  velocity_listener
  DESTINATION lib/${PROJECT_NAME})

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  set(ament_cmake_copyright_FOUND TRUE)
  set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()

ament_package()
