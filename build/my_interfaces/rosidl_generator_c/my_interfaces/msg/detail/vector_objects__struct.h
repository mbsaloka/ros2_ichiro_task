// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from my_interfaces:msg/VectorObjects.idl
// generated code does not contain a copyright notice

#ifndef MY_INTERFACES__MSG__DETAIL__VECTOR_OBJECTS__STRUCT_H_
#define MY_INTERFACES__MSG__DETAIL__VECTOR_OBJECTS__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

// Constants defined in the message

// Include directives for member types
// Member 'objects'
#include "my_interfaces/msg/detail/object__struct.h"

/// Struct defined in msg/VectorObjects in the package my_interfaces.
typedef struct my_interfaces__msg__VectorObjects
{
  my_interfaces__msg__Object__Sequence objects;
} my_interfaces__msg__VectorObjects;

// Struct for a sequence of my_interfaces__msg__VectorObjects.
typedef struct my_interfaces__msg__VectorObjects__Sequence
{
  my_interfaces__msg__VectorObjects * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} my_interfaces__msg__VectorObjects__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // MY_INTERFACES__MSG__DETAIL__VECTOR_OBJECTS__STRUCT_H_
