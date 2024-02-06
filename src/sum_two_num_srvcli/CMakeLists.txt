cmake_minimum_required(VERSION 3.8)
project(sum_two_num_srvcli)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(example_interfaces REQUIRED)

add_executable(server src/sum_two_num_server.cpp)
ament_target_dependencies(server rclcpp example_interfaces)

add_executable(client src/sum_two_num_client.cpp)
ament_target_dependencies(client rclcpp example_interfaces)

install(TARGETS
    server
    client
  DESTINATION lib/${PROJECT_NAME})

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  set(ament_cmake_copyright_FOUND TRUE)
  set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()

ament_package()
