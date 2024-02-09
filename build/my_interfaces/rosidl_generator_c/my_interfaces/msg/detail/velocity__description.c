// generated from rosidl_generator_c/resource/idl__description.c.em
// with input from my_interfaces:msg/Velocity.idl
// generated code does not contain a copyright notice

#include "my_interfaces/msg/detail/velocity__functions.h"

ROSIDL_GENERATOR_C_PUBLIC_my_interfaces
const rosidl_type_hash_t *
my_interfaces__msg__Velocity__get_type_hash(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_type_hash_t hash = {1, {
      0xd2, 0xa9, 0x1c, 0x17, 0xd7, 0x3b, 0xdf, 0x1f,
      0xfa, 0x9a, 0x39, 0xdc, 0x3b, 0x48, 0xa8, 0xd5,
      0xe4, 0x09, 0x3e, 0x5a, 0xdd, 0xa0, 0x24, 0x12,
      0x53, 0x90, 0xb6, 0x8a, 0xa1, 0x22, 0x4b, 0x2c,
    }};
  return &hash;
}

#include <assert.h>
#include <string.h>

// Include directives for referenced types

// Hashes for external referenced types
#ifndef NDEBUG
#endif

static char my_interfaces__msg__Velocity__TYPE_NAME[] = "my_interfaces/msg/Velocity";

// Define type names, field names, and default values
static char my_interfaces__msg__Velocity__FIELD_NAME__linear[] = "linear";
static char my_interfaces__msg__Velocity__FIELD_NAME__angular[] = "angular";

static rosidl_runtime_c__type_description__Field my_interfaces__msg__Velocity__FIELDS[] = {
  {
    {my_interfaces__msg__Velocity__FIELD_NAME__linear, 6, 6},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_DOUBLE,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {my_interfaces__msg__Velocity__FIELD_NAME__angular, 7, 7},
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
my_interfaces__msg__Velocity__get_type_description(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static bool constructed = false;
  static const rosidl_runtime_c__type_description__TypeDescription description = {
    {
      {my_interfaces__msg__Velocity__TYPE_NAME, 26, 26},
      {my_interfaces__msg__Velocity__FIELDS, 2, 2},
    },
    {NULL, 0, 0},
  };
  if (!constructed) {
    constructed = true;
  }
  return &description;
}

static char toplevel_type_raw_source[] =
  "float64 linear\n"
  "float64 angular";

static char msg_encoding[] = "msg";

// Define all individual source functions

const rosidl_runtime_c__type_description__TypeSource *
my_interfaces__msg__Velocity__get_individual_type_description_source(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static const rosidl_runtime_c__type_description__TypeSource source = {
    {my_interfaces__msg__Velocity__TYPE_NAME, 26, 26},
    {msg_encoding, 3, 3},
    {toplevel_type_raw_source, 30, 30},
  };
  return &source;
}

const rosidl_runtime_c__type_description__TypeSource__Sequence *
my_interfaces__msg__Velocity__get_type_description_sources(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_runtime_c__type_description__TypeSource sources[1];
  static const rosidl_runtime_c__type_description__TypeSource__Sequence source_sequence = {sources, 1, 1};
  static bool constructed = false;
  if (!constructed) {
    sources[0] = *my_interfaces__msg__Velocity__get_individual_type_description_source(NULL),
    constructed = true;
  }
  return &source_sequence;
}
