// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from my_interfaces:msg/Boolean.idl
// generated code does not contain a copyright notice

#ifndef MY_INTERFACES__MSG__DETAIL__BOOLEAN__STRUCT_HPP_
#define MY_INTERFACES__MSG__DETAIL__BOOLEAN__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__my_interfaces__msg__Boolean __attribute__((deprecated))
#else
# define DEPRECATED__my_interfaces__msg__Boolean __declspec(deprecated)
#endif

namespace my_interfaces
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct Boolean_
{
  using Type = Boolean_<ContainerAllocator>;

  explicit Boolean_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->flag = false;
    }
  }

  explicit Boolean_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    (void)_alloc;
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->flag = false;
    }
  }

  // field types and members
  using _flag_type =
    bool;
  _flag_type flag;

  // setters for named parameter idiom
  Type & set__flag(
    const bool & _arg)
  {
    this->flag = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    my_interfaces::msg::Boolean_<ContainerAllocator> *;
  using ConstRawPtr =
    const my_interfaces::msg::Boolean_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<my_interfaces::msg::Boolean_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<my_interfaces::msg::Boolean_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      my_interfaces::msg::Boolean_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<my_interfaces::msg::Boolean_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      my_interfaces::msg::Boolean_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<my_interfaces::msg::Boolean_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<my_interfaces::msg::Boolean_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<my_interfaces::msg::Boolean_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__my_interfaces__msg__Boolean
    std::shared_ptr<my_interfaces::msg::Boolean_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__my_interfaces__msg__Boolean
    std::shared_ptr<my_interfaces::msg::Boolean_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const Boolean_ & other) const
  {
    if (this->flag != other.flag) {
      return false;
    }
    return true;
  }
  bool operator!=(const Boolean_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct Boolean_

// alias to use template instance with default allocator
using Boolean =
  my_interfaces::msg::Boolean_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace my_interfaces

#endif  // MY_INTERFACES__MSG__DETAIL__BOOLEAN__STRUCT_HPP_
