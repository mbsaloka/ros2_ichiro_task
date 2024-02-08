// generated from rosidl_generator_c/resource/idl__description.c.em
// with input from my_interfaces:msg/Pose.idl
// generated code does not contain a copyright notice

#include "my_interfaces/msg/detail/pose__functions.h"

ROSIDL_GENERATOR_C_PUBLIC_my_interfaces
const rosidl_type_hash_t *
my_interfaces__msg__Pose__get_type_hash(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_type_hash_t hash = {1, {
      0xe0, 0x54, 0x1e, 0x9e, 0x07, 0xec, 0x8e, 0xc8,
      0x12, 0x85, 0x5f, 0xbe, 0xe8, 0x48, 0x0d, 0x1b,
      0xcc, 0xa6, 0x57, 0x60, 0xc5, 0x2e, 0xab, 0xd2,
      0xe6, 0xe8, 0xce, 0x0f, 0xcc, 0x5d, 0xcc, 0x19,
    }};
  return &hash;
}

#include <assert.h>
#include <string.h>

// Include directives for referenced types

// Hashes for external referenced types
#ifndef NDEBUG
#endif

static char my_interfaces__msg__Pose__TYPE_NAME[] = "my_interfaces/msg/Pose";

// Define type names, field names, and default values
static char my_interfaces__msg__Pose__FIELD_NAME__x[] = "x";
static char my_interfaces__msg__Pose__FIELD_NAME__y[] = "y";
static char my_interfaces__msg__Pose__FIELD_NAME__theta[] = "theta";

static rosidl_runtime_c__type_description__Field my_interfaces__msg__Pose__FIELDS[] = {
  {
    {my_interfaces__msg__Pose__FIELD_NAME__x, 1, 1},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_DOUBLE,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {my_interfaces__msg__Pose__FIELD_NAME__y, 1, 1},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_DOUBLE,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {my_interfaces__msg__Pose__FIELD_NAME__theta, 5, 5},
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
my_interfaces__msg__Pose__get_type_description(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static bool constructed = false;
  static const rosidl_runtime_c__type_description__TypeDescription description = {
    {
      {my_interfaces__msg__Pose__TYPE_NAME, 22, 22},
      {my_interfaces__msg__Pose__FIELDS, 3, 3},
    },
    {NULL, 0, 0},
  };
  if (!constructed) {
    constructed = true;
  }
  return &description;
}

static char toplevel_type_raw_source[] =
  "float64 x\n"
  "float64 y\n"
  "float64 theta";

static char msg_encoding[] = "msg";

// Define all individual source functions

const rosidl_runtime_c__type_description__TypeSource *
my_interfaces__msg__Pose__get_individual_type_description_source(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static const rosidl_runtime_c__type_description__TypeSource source = {
    {my_interfaces__msg__Pose__TYPE_NAME, 22, 22},
    {msg_encoding, 3, 3},
    {toplevel_type_raw_source, 33, 33},
  };
  return &source;
}

const rosidl_runtime_c__type_description__TypeSource__Sequence *
my_interfaces__msg__Pose__get_type_description_sources(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_runtime_c__type_description__TypeSource sources[1];
  static const rosidl_runtime_c__type_description__TypeSource__Sequence source_sequence = {sources, 1, 1};
  static bool constructed = false;
  if (!constructed) {
    sources[0] = *my_interfaces__msg__Pose__get_individual_type_description_source(NULL),
    constructed = true;
  }
  return &source_sequence;
}
