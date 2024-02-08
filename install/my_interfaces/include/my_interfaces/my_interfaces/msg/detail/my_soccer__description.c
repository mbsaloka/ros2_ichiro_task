// generated from rosidl_generator_c/resource/idl__description.c.em
// with input from my_interfaces:msg/MySoccer.idl
// generated code does not contain a copyright notice

#include "my_interfaces/msg/detail/my_soccer__functions.h"

ROSIDL_GENERATOR_C_PUBLIC_my_interfaces
const rosidl_type_hash_t *
my_interfaces__msg__MySoccer__get_type_hash(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_type_hash_t hash = {1, {
      0x5c, 0xb8, 0x18, 0x63, 0xec, 0x36, 0x94, 0x79,
      0x54, 0x0b, 0x1f, 0xde, 0x83, 0xbd, 0x05, 0x6a,
      0xbb, 0xf1, 0x58, 0x3a, 0x28, 0xcf, 0x73, 0x05,
      0xb5, 0xc2, 0xc0, 0x1d, 0x9f, 0x81, 0x25, 0x8b,
    }};
  return &hash;
}

#include <assert.h>
#include <string.h>

// Include directives for referenced types

// Hashes for external referenced types
#ifndef NDEBUG
#endif

static char my_interfaces__msg__MySoccer__TYPE_NAME[] = "my_interfaces/msg/MySoccer";

// Define type names, field names, and default values
static char my_interfaces__msg__MySoccer__FIELD_NAME__linear_vel[] = "linear_vel";
static char my_interfaces__msg__MySoccer__FIELD_NAME__angular_vel[] = "angular_vel";

static rosidl_runtime_c__type_description__Field my_interfaces__msg__MySoccer__FIELDS[] = {
  {
    {my_interfaces__msg__MySoccer__FIELD_NAME__linear_vel, 10, 10},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_DOUBLE,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {my_interfaces__msg__MySoccer__FIELD_NAME__angular_vel, 11, 11},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_DOUBLE,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
};

const rosidl_runtime_c__type_description__TypeDescription *
my_interfaces__msg__MySoccer__get_type_description(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static bool constructed = false;
  static const rosidl_runtime_c__type_description__TypeDescription description = {
    {
      {my_interfaces__msg__MySoccer__TYPE_NAME, 26, 26},
      {my_interfaces__msg__MySoccer__FIELDS, 2, 2},
    },
    {NULL, 0, 0},
  };
  if (!constructed) {
    constructed = true;
  }
  return &description;
}

static char toplevel_type_raw_source[] =
  "float64 linear_vel\n"
  "float64 angular_vel";

static char msg_encoding[] = "msg";

// Define all individual source functions

const rosidl_runtime_c__type_description__TypeSource *
my_interfaces__msg__MySoccer__get_individual_type_description_source(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static const rosidl_runtime_c__type_description__TypeSource source = {
    {my_interfaces__msg__MySoccer__TYPE_NAME, 26, 26},
    {msg_encoding, 3, 3},
    {toplevel_type_raw_source, 38, 38},
  };
  return &source;
}

const rosidl_runtime_c__type_description__TypeSource__Sequence *
my_interfaces__msg__MySoccer__get_type_description_sources(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_runtime_c__type_description__TypeSource sources[1];
  static const rosidl_runtime_c__type_description__TypeSource__Sequence source_sequence = {sources, 1, 1};
  static bool constructed = false;
  if (!constructed) {
    sources[0] = *my_interfaces__msg__MySoccer__get_individual_type_description_source(NULL),
    constructed = true;
  }
  return &source_sequence;
}
