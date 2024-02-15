// generated from rosidl_generator_c/resource/idl__description.c.em
// with input from my_interfaces:msg/Objects.idl
// generated code does not contain a copyright notice

#include "my_interfaces/msg/detail/objects__functions.h"

ROSIDL_GENERATOR_C_PUBLIC_my_interfaces
const rosidl_type_hash_t *
my_interfaces__msg__Objects__get_type_hash(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_type_hash_t hash = {1, {
      0x75, 0x73, 0xa3, 0xa0, 0xd6, 0x2a, 0xf9, 0xda,
      0x74, 0xc6, 0x1b, 0xeb, 0x6b, 0x6d, 0x5d, 0x11,
      0xa2, 0xa3, 0x4f, 0x7d, 0xe1, 0x87, 0xd4, 0x35,
      0xd9, 0xf8, 0x38, 0x2a, 0x42, 0x07, 0x99, 0x8d,
    }};
  return &hash;
}

#include <assert.h>
#include <string.h>

// Include directives for referenced types
#include "my_interfaces/msg/detail/object__functions.h"

// Hashes for external referenced types
#ifndef NDEBUG
static const rosidl_type_hash_t my_interfaces__msg__Object__EXPECTED_HASH = {1, {
    0x5e, 0x59, 0x6f, 0x6c, 0x56, 0xff, 0x9c, 0x16,
    0xa0, 0x0b, 0x08, 0x32, 0x6c, 0x51, 0x72, 0x0f,
    0xb6, 0xaf, 0xce, 0x4c, 0x06, 0x51, 0x84, 0xf9,
    0x2c, 0x82, 0x08, 0x46, 0xe4, 0x6d, 0xce, 0x82,
  }};
#endif

static char my_interfaces__msg__Objects__TYPE_NAME[] = "my_interfaces/msg/Objects";
static char my_interfaces__msg__Object__TYPE_NAME[] = "my_interfaces/msg/Object";

// Define type names, field names, and default values
static char my_interfaces__msg__Objects__FIELD_NAME__objects[] = "objects";

static rosidl_runtime_c__type_description__Field my_interfaces__msg__Objects__FIELDS[] = {
  {
    {my_interfaces__msg__Objects__FIELD_NAME__objects, 7, 7},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_NESTED_TYPE_UNBOUNDED_SEQUENCE,
      0,
      0,
      {my_interfaces__msg__Object__TYPE_NAME, 24, 24},
    },
    {NULL, 0, 0},
  },
};

static rosidl_runtime_c__type_description__IndividualTypeDescription my_interfaces__msg__Objects__REFERENCED_TYPE_DESCRIPTIONS[] = {
  {
    {my_interfaces__msg__Object__TYPE_NAME, 24, 24},
    {NULL, 0, 0},
  },
};

const rosidl_runtime_c__type_description__TypeDescription *
my_interfaces__msg__Objects__get_type_description(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static bool constructed = false;
  static const rosidl_runtime_c__type_description__TypeDescription description = {
    {
      {my_interfaces__msg__Objects__TYPE_NAME, 25, 25},
      {my_interfaces__msg__Objects__FIELDS, 1, 1},
    },
    {my_interfaces__msg__Objects__REFERENCED_TYPE_DESCRIPTIONS, 1, 1},
  };
  if (!constructed) {
    assert(0 == memcmp(&my_interfaces__msg__Object__EXPECTED_HASH, my_interfaces__msg__Object__get_type_hash(NULL), sizeof(rosidl_type_hash_t)));
    description.referenced_type_descriptions.data[0].fields = my_interfaces__msg__Object__get_type_description(NULL)->type_description.fields;
    constructed = true;
  }
  return &description;
}

static char toplevel_type_raw_source[] =
  "Object[] objects";

static char msg_encoding[] = "msg";

// Define all individual source functions

const rosidl_runtime_c__type_description__TypeSource *
my_interfaces__msg__Objects__get_individual_type_description_source(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static const rosidl_runtime_c__type_description__TypeSource source = {
    {my_interfaces__msg__Objects__TYPE_NAME, 25, 25},
    {msg_encoding, 3, 3},
    {toplevel_type_raw_source, 16, 16},
  };
  return &source;
}

const rosidl_runtime_c__type_description__TypeSource__Sequence *
my_interfaces__msg__Objects__get_type_description_sources(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_runtime_c__type_description__TypeSource sources[2];
  static const rosidl_runtime_c__type_description__TypeSource__Sequence source_sequence = {sources, 2, 2};
  static bool constructed = false;
  if (!constructed) {
    sources[0] = *my_interfaces__msg__Objects__get_individual_type_description_source(NULL),
    sources[1] = *my_interfaces__msg__Object__get_individual_type_description_source(NULL);
    constructed = true;
  }
  return &source_sequence;
}
