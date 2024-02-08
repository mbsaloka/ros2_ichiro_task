// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from my_interfaces:msg/Pose.idl
// generated code does not contain a copyright notice

#ifndef MY_INTERFACES__MSG__DETAIL__POSE__BUILDER_HPP_
#define MY_INTERFACES__MSG__DETAIL__POSE__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "my_interfaces/msg/detail/pose__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace my_interfaces
{

namespace msg
{

namespace builder
{

class Init_Pose_theta
{
public:
  explicit Init_Pose_theta(::my_interfaces::msg::Pose & msg)
  : msg_(msg)
  {}
  ::my_interfaces::msg::Pose theta(::my_interfaces::msg::Pose::_theta_type arg)
  {
    msg_.theta = std::move(arg);
    return std::move(msg_);
  }

private:
  ::my_interfaces::msg::Pose msg_;
};

class Init_Pose_y
{
public:
  explicit Init_Pose_y(::my_interfaces::msg::Pose & msg)
  : msg_(msg)
  {}
  Init_Pose_theta y(::my_interfaces::msg::Pose::_y_type arg)
  {
    msg_.y = std::move(arg);
    return Init_Pose_theta(msg_);
  }

private:
  ::my_interfaces::msg::Pose msg_;
};

class Init_Pose_x
{
public:
  Init_Pose_x()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_Pose_y x(::my_interfaces::msg::Pose::_x_type arg)
  {
    msg_.x = std::move(arg);
    return Init_Pose_y(msg_);
  }

private:
  ::my_interfaces::msg::Pose msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::my_interfaces::msg::Pose>()
{
  return my_interfaces::msg::builder::Init_Pose_x();
}

}  // namespace my_interfaces

#endif  // MY_INTERFACES__MSG__DETAIL__POSE__BUILDER_HPP_
