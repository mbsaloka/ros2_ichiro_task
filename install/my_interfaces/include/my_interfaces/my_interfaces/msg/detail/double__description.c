// generated from rosidl_generator_c/resource/idl__description.c.em
// with input from my_interfaces:msg/Double.idl
// generated code does not contain a copyright notice

#include "my_interfaces/msg/detail/double__functions.h"

ROSIDL_GENERATOR_C_PUBLIC_my_interfaces
const rosidl_type_hash_t *
my_interfaces__msg__Double__get_type_hash(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_type_hash_t hash = {1, {
      0xb6, 0xf9, 0x40, 0x08, 0xec, 0x19, 0xc2, 0x63,
      0x71, 0x20, 0x0a, 0xa8, 0xdb, 0xd4, 0x85, 0x3e,
      0x96, 0x18, 0x90, 0x25, 0xc2, 0xb1, 0x66, 0xb7,
      0xa2, 0x18, 0x8a, 0x27, 0xe3, 0x41, 0x88, 0x0e,
    }};
  return &hash;
}

#include <assert.h>
#include <string.h>

// Include directives for referenced types

// Hashes for external referenced types
#ifndef NDEBUG
#endif

static char my_interfaces__msg__Double__TYPE_NAME[] = "my_interfaces/msg/Double";

// Define type names, field names, and default values
static char my_interfaces__msg__Double__FIELD_NAME__data[] = "data";

static rosidl_runtime_c__type_description__Field my_interfaces__msg__Double__FIELDS[] = {
  {
    {my_interfaces__msg__Double__FIELD_NAME__data, 4, 4},
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
my_interfaces__msg__Double__get_type_description(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static bool constructed = false;
  static const rosidl_runtime_c__type_description__TypeDescription description = {
    {
      {my_interfaces__msg__Double__TYPE_NAME, 24, 24},
      {my_interfaces__msg__Double__FIELDS, 1, 1},
    },
    {NULL, 0, 0},
  };
  if (!constructed) {
    constructed = true;
  }
  return &description;
}

static char toplevel_type_raw_source[] =
  "float64 data";

static char msg_encoding[] = "msg";

// Define all individual source functions

const rosidl_runtime_c__type_description__TypeSource *
my_interfaces__msg__Double__get_individual_type_description_source(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static const rosidl_runtime_c__type_description__TypeSource source = {
    {my_interfaces__msg__Double__TYPE_NAME, 24, 24},
    {msg_encoding, 3, 3},
    {toplevel_type_raw_source, 12, 12},
  };
  return &source;
}

const rosidl_runtime_c__type_description__TypeSource__Sequence *
my_interfaces__msg__Double__get_type_description_sources(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_runtime_c__type_description__TypeSource sources[1];
  static const rosidl_runtime_c__type_description__TypeSource__Sequence source_sequence = {sources, 1, 1};
  static bool constructed = false;
  if (!constructed) {
    sources[0] = *my_interfaces__msg__Double__get_individual_type_description_source(NULL),
    constructed = true;
  }
  return &source_sequence;
}
