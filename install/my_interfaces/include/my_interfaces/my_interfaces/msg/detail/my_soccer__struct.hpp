// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from my_interfaces:msg/MySoccer.idl
// generated code does not contain a copyright notice

#ifndef MY_INTERFACES__MSG__DETAIL__MY_SOCCER__STRUCT_HPP_
#define MY_INTERFACES__MSG__DETAIL__MY_SOCCER__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__my_interfaces__msg__MySoccer __attribute__((deprecated))
#else
# define DEPRECATED__my_interfaces__msg__MySoccer __declspec(deprecated)
#endif

namespace my_interfaces
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct MySoccer_
{
  using Type = MySoccer_<ContainerAllocator>;

  explicit MySoccer_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->linear_vel = 0.0;
      this->angular_vel = 0.0;
    }
  }

  explicit MySoccer_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    (void)_alloc;
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->linear_vel = 0.0;
      this->angular_vel = 0.0;
    }
  }

  // field types and members
  using _linear_vel_type =
    double;
  _linear_vel_type linear_vel;
  using _angular_vel_type =
    double;
  _angular_vel_type angular_vel;

  // setters for named parameter idiom
  Type & set__linear_vel(
    const double & _arg)
  {
    this->linear_vel = _arg;
    return *this;
  }
  Type & set__angular_vel(
    const double & _arg)
  {
    this->angular_vel = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    my_interfaces::msg::MySoccer_<ContainerAllocator> *;
  using ConstRawPtr =
    const my_interfaces::msg::MySoccer_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<my_interfaces::msg::MySoccer_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<my_interfaces::msg::MySoccer_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      my_interfaces::msg::MySoccer_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<my_interfaces::msg::MySoccer_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      my_interfaces::msg::MySoccer_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<my_interfaces::msg::MySoccer_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<my_interfaces::msg::MySoccer_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<my_interfaces::msg::MySoccer_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__my_interfaces__msg__MySoccer
    std::shared_ptr<my_interfaces::msg::MySoccer_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__my_interfaces__msg__MySoccer
    std::shared_ptr<my_interfaces::msg::MySoccer_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const MySoccer_ & other) const
  {
    if (this->linear_vel != other.linear_vel) {
      return false;
    }
    if (this->angular_vel != other.angular_vel) {
      return false;
    }
    return true;
  }
  bool operator!=(const MySoccer_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct MySoccer_

// alias to use template instance with default allocator
using MySoccer =
  my_interfaces::msg::MySoccer_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace my_interfaces

#endif  // MY_INTERFACES__MSG__DETAIL__MY_SOCCER__STRUCT_HPP_
