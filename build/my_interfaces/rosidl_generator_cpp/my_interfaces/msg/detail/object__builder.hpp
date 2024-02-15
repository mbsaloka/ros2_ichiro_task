// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from my_interfaces:msg/Object.idl
// generated code does not contain a copyright notice

#ifndef MY_INTERFACES__MSG__DETAIL__OBJECT__BUILDER_HPP_
#define MY_INTERFACES__MSG__DETAIL__OBJECT__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "my_interfaces/msg/detail/object__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace my_interfaces
{

namespace msg
{

namespace builder
{

class Init_Object_y
{
public:
  explicit Init_Object_y(::my_interfaces::msg::Object & msg)
  : msg_(msg)
  {}
  ::my_interfaces::msg::Object y(::my_interfaces::msg::Object::_y_type arg)
  {
    msg_.y = std::move(arg);
    return std::move(msg_);
  }

private:
  ::my_interfaces::msg::Object msg_;
};

class Init_Object_x
{
public:
  Init_Object_x()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_Object_y x(::my_interfaces::msg::Object::_x_type arg)
  {
    msg_.x = std::move(arg);
    return Init_Object_y(msg_);
  }

private:
  ::my_interfaces::msg::Object msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::my_interfaces::msg::Object>()
{
  return my_interfaces::msg::builder::Init_Object_x();
}

}  // namespace my_interfaces

#endif  // MY_INTERFACES__MSG__DETAIL__OBJECT__BUILDER_HPP_
