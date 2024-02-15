// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from my_interfaces:msg/VectorObjects.idl
// generated code does not contain a copyright notice

#ifndef MY_INTERFACES__MSG__DETAIL__VECTOR_OBJECTS__STRUCT_HPP_
#define MY_INTERFACES__MSG__DETAIL__VECTOR_OBJECTS__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


// Include directives for member types
// Member 'objects'
#include "my_interfaces/msg/detail/object__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__my_interfaces__msg__VectorObjects __attribute__((deprecated))
#else
# define DEPRECATED__my_interfaces__msg__VectorObjects __declspec(deprecated)
#endif

namespace my_interfaces
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct VectorObjects_
{
  using Type = VectorObjects_<ContainerAllocator>;

  explicit VectorObjects_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    (void)_init;
  }

  explicit VectorObjects_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    (void)_init;
    (void)_alloc;
  }

  // field types and members
  using _objects_type =
    std::vector<my_interfaces::msg::Object_<ContainerAllocator>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<my_interfaces::msg::Object_<ContainerAllocator>>>;
  _objects_type objects;

  // setters for named parameter idiom
  Type & set__objects(
    const std::vector<my_interfaces::msg::Object_<ContainerAllocator>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<my_interfaces::msg::Object_<ContainerAllocator>>> & _arg)
  {
    this->objects = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    my_interfaces::msg::VectorObjects_<ContainerAllocator> *;
  using ConstRawPtr =
    const my_interfaces::msg::VectorObjects_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<my_interfaces::msg::VectorObjects_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<my_interfaces::msg::VectorObjects_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      my_interfaces::msg::VectorObjects_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<my_interfaces::msg::VectorObjects_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      my_interfaces::msg::VectorObjects_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<my_interfaces::msg::VectorObjects_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<my_interfaces::msg::VectorObjects_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<my_interfaces::msg::VectorObjects_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__my_interfaces__msg__VectorObjects
    std::shared_ptr<my_interfaces::msg::VectorObjects_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__my_interfaces__msg__VectorObjects
    std::shared_ptr<my_interfaces::msg::VectorObjects_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const VectorObjects_ & other) const
  {
    if (this->objects != other.objects) {
      return false;
    }
    return true;
  }
  bool operator!=(const VectorObjects_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct VectorObjects_

// alias to use template instance with default allocator
using VectorObjects =
  my_interfaces::msg::VectorObjects_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace my_interfaces

#endif  // MY_INTERFACES__MSG__DETAIL__VECTOR_OBJECTS__STRUCT_HPP_
