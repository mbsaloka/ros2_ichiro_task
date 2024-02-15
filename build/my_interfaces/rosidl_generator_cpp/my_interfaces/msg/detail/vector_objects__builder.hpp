// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from my_interfaces:msg/VectorObjects.idl
// generated code does not contain a copyright notice

#ifndef MY_INTERFACES__MSG__DETAIL__VECTOR_OBJECTS__BUILDER_HPP_
#define MY_INTERFACES__MSG__DETAIL__VECTOR_OBJECTS__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "my_interfaces/msg/detail/vector_objects__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace my_interfaces
{

namespace msg
{

namespace builder
{

class Init_VectorObjects_objects
{
public:
  Init_VectorObjects_objects()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  ::my_interfaces::msg::VectorObjects objects(::my_interfaces::msg::VectorObjects::_objects_type arg)
  {
    msg_.objects = std::move(arg);
    return std::move(msg_);
  }

private:
  ::my_interfaces::msg::VectorObjects msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::my_interfaces::msg::VectorObjects>()
{
  return my_interfaces::msg::builder::Init_VectorObjects_objects();
}

}  // namespace my_interfaces

#endif  // MY_INTERFACES__MSG__DETAIL__VECTOR_OBJECTS__BUILDER_HPP_
