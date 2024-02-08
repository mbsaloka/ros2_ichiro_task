// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from my_interfaces:msg/Pose.idl
// generated code does not contain a copyright notice

#ifndef MY_INTERFACES__MSG__DETAIL__POSE__STRUCT_H_
#define MY_INTERFACES__MSG__DETAIL__POSE__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

// Constants defined in the message

/// Struct defined in msg/Pose in the package my_interfaces.
typedef struct my_interfaces__msg__Pose
{
  double x;
  double y;
  double theta;
} my_interfaces__msg__Pose;

// Struct for a sequence of my_interfaces__msg__Pose.
typedef struct my_interfaces__msg__Pose__Sequence
{
  my_interfaces__msg__Pose * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} my_interfaces__msg__Pose__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // MY_INTERFACES__MSG__DETAIL__POSE__STRUCT_H_
