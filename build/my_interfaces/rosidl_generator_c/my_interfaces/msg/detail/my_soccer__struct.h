// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from my_interfaces:msg/MySoccer.idl
// generated code does not contain a copyright notice

#ifndef MY_INTERFACES__MSG__DETAIL__MY_SOCCER__STRUCT_H_
#define MY_INTERFACES__MSG__DETAIL__MY_SOCCER__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

// Constants defined in the message

/// Struct defined in msg/MySoccer in the package my_interfaces.
typedef struct my_interfaces__msg__MySoccer
{
  double linear_vel;
  double angular_vel;
} my_interfaces__msg__MySoccer;

// Struct for a sequence of my_interfaces__msg__MySoccer.
typedef struct my_interfaces__msg__MySoccer__Sequence
{
  my_interfaces__msg__MySoccer * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} my_interfaces__msg__MySoccer__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // MY_INTERFACES__MSG__DETAIL__MY_SOCCER__STRUCT_H_
