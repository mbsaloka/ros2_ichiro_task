// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from my_interfaces:msg/Velocity.idl
// generated code does not contain a copyright notice

#ifndef MY_INTERFACES__MSG__DETAIL__VELOCITY__BUILDER_HPP_
#define MY_INTERFACES__MSG__DETAIL__VELOCITY__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "my_interfaces/msg/detail/velocity__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace my_interfaces
{

namespace msg
{

namespace builder
{

class Init_Velocity_angular
{
public:
  explicit Init_Velocity_angular(::my_interfaces::msg::Velocity & msg)
  : msg_(msg)
  {}
  ::my_interfaces::msg::Velocity angular(::my_interfaces::msg::Velocity::_angular_type arg)
  {
    msg_.angular = std::move(arg);
    return std::move(msg_);
  }

private:
  ::my_interfaces::msg::Velocity msg_;
};

class Init_Velocity_linear
{
public:
  Init_Velocity_linear()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_Velocity_angular linear(::my_interfaces::msg::Velocity::_linear_type arg)
  {
    msg_.linear = std::move(arg);
    return Init_Velocity_angular(msg_);
  }

private:
  ::my_interfaces::msg::Velocity msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::my_interfaces::msg::Velocity>()
{
  return my_interfaces::msg::builder::Init_Velocity_linear();
}

}  // namespace my_interfaces

#endif  // MY_INTERFACES__MSG__DETAIL__VELOCITY__BUILDER_HPP_
