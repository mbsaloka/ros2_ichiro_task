// generated from rosidl_generator_c/resource/idl__description.c.em
// with input from my_interfaces:msg/Boolean.idl
// generated code does not contain a copyright notice

#include "my_interfaces/msg/detail/boolean__functions.h"

ROSIDL_GENERATOR_C_PUBLIC_my_interfaces
const rosidl_type_hash_t *
my_interfaces__msg__Boolean__get_type_hash(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_type_hash_t hash = {1, {
      0x9c, 0x9f, 0x03, 0x54, 0x3e, 0x65, 0xe7, 0xa5,
      0x2a, 0x60, 0xd5, 0x3d, 0xa3, 0x1b, 0xc0, 0x7e,
      0x7a, 0x58, 0x93, 0x22, 0x18, 0xa5, 0x26, 0xa8,
      0x6b, 0xfd, 0x06, 0x49, 0x34, 0xfa, 0x9f, 0x3d,
    }};
  return &hash;
}

#include <assert.h>
#include <string.h>

// Include directives for referenced types

// Hashes for external referenced types
#ifndef NDEBUG
#endif

static char my_interfaces__msg__Boolean__TYPE_NAME[] = "my_interfaces/msg/Boolean";

// Define type names, field names, and default values
static char my_interfaces__msg__Boolean__FIELD_NAME__flag[] = "flag";

static rosidl_runtime_c__type_description__Field my_interfaces__msg__Boolean__FIELDS[] = {
  {
    {my_interfaces__msg__Boolean__FIELD_NAME__flag, 4, 4},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_BOOLEAN,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
};

const rosidl_runtime_c__type_description__TypeDescription *
my_interfaces__msg__Boolean__get_type_description(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static bool constructed = false;
  static const rosidl_runtime_c__type_description__TypeDescription description = {
    {
      {my_interfaces__msg__Boolean__TYPE_NAME, 25, 25},
      {my_interfaces__msg__Boolean__FIELDS, 1, 1},
    },
    {NULL, 0, 0},
  };
  if (!constructed) {
    constructed = true;
  }
  return &description;
}

static char toplevel_type_raw_source[] =
  "bool flag";

static char msg_encoding[] = "msg";

// Define all individual source functions

const rosidl_runtime_c__type_description__TypeSource *
my_interfaces__msg__Boolean__get_individual_type_description_source(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static const rosidl_runtime_c__type_description__TypeSource source = {
    {my_interfaces__msg__Boolean__TYPE_NAME, 25, 25},
    {msg_encoding, 3, 3},
    {toplevel_type_raw_source, 9, 9},
  };
  return &source;
}

const rosidl_runtime_c__type_description__TypeSource__Sequence *
my_interfaces__msg__Boolean__get_type_description_sources(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_runtime_c__type_description__TypeSource sources[1];
  static const rosidl_runtime_c__type_description__TypeSource__Sequence source_sequence = {sources, 1, 1};
  static bool constructed = false;
  if (!constructed) {
    sources[0] = *my_interfaces__msg__Boolean__get_individual_type_description_source(NULL),
    constructed = true;
  }
  return &source_sequence;
}
