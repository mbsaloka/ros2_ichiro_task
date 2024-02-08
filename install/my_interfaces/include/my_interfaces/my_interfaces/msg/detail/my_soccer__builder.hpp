// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from my_interfaces:msg/MySoccer.idl
// generated code does not contain a copyright notice

#ifndef MY_INTERFACES__MSG__DETAIL__MY_SOCCER__BUILDER_HPP_
#define MY_INTERFACES__MSG__DETAIL__MY_SOCCER__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "my_interfaces/msg/detail/my_soccer__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace my_interfaces
{

namespace msg
{

namespace builder
{

class Init_MySoccer_angular_vel
{
public:
  explicit Init_MySoccer_angular_vel(::my_interfaces::msg::MySoccer & msg)
  : msg_(msg)
  {}
  ::my_interfaces::msg::MySoccer angular_vel(::my_interfaces::msg::MySoccer::_angular_vel_type arg)
  {
    msg_.angular_vel = std::move(arg);
    return std::move(msg_);
  }

private:
  ::my_interfaces::msg::MySoccer msg_;
};

class Init_MySoccer_linear_vel
{
public:
  Init_MySoccer_linear_vel()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_MySoccer_angular_vel linear_vel(::my_interfaces::msg::MySoccer::_linear_vel_type arg)
  {
    msg_.linear_vel = std::move(arg);
    return Init_MySoccer_angular_vel(msg_);
  }

private:
  ::my_interfaces::msg::MySoccer msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::my_interfaces::msg::MySoccer>()
{
  return my_interfaces::msg::builder::Init_MySoccer_linear_vel();
}

}  // namespace my_interfaces

#endif  // MY_INTERFACES__MSG__DETAIL__MY_SOCCER__BUILDER_HPP_
