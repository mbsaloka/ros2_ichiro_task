// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from my_interfaces:msg/Double.idl
// generated code does not contain a copyright notice

#ifndef MY_INTERFACES__MSG__DETAIL__DOUBLE__STRUCT_H_
#define MY_INTERFACES__MSG__DETAIL__DOUBLE__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

// Constants defined in the message

/// Struct defined in msg/Double in the package my_interfaces.
typedef struct my_interfaces__msg__Double
{
  double data;
} my_interfaces__msg__Double;

// Struct for a sequence of my_interfaces__msg__Double.
typedef struct my_interfaces__msg__Double__Sequence
{
  my_interfaces__msg__Double * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} my_interfaces__msg__Double__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // MY_INTERFACES__MSG__DETAIL__DOUBLE__STRUCT_H_
