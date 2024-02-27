// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from my_interfaces:msg/Double.idl
// generated code does not contain a copyright notice

#ifndef MY_INTERFACES__MSG__DETAIL__DOUBLE__BUILDER_HPP_
#define MY_INTERFACES__MSG__DETAIL__DOUBLE__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "my_interfaces/msg/detail/double__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace my_interfaces
{

namespace msg
{

namespace builder
{

class Init_Double_data
{
public:
  Init_Double_data()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  ::my_interfaces::msg::Double data(::my_interfaces::msg::Double::_data_type arg)
  {
    msg_.data = std::move(arg);
    return std::move(msg_);
  }

private:
  ::my_interfaces::msg::Double msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::my_interfaces::msg::Double>()
{
  return my_interfaces::msg::builder::Init_Double_data();
}

}  // namespace my_interfaces

#endif  // MY_INTERFACES__MSG__DETAIL__DOUBLE__BUILDER_HPP_
