// generated from rosidl_typesupport_fastrtps_c/resource/idl__type_support_c.cpp.em
// with input from my_interfaces:msg/Double.idl
// generated code does not contain a copyright notice
#include "my_interfaces/msg/detail/double__rosidl_typesupport_fastrtps_c.h"


#include <cassert>
#include <limits>
#include <string>
#include "rosidl_typesupport_fastrtps_c/identifier.h"
#include "rosidl_typesupport_fastrtps_c/wstring_conversion.hpp"
#include "rosidl_typesupport_fastrtps_cpp/message_type_support.h"
#include "my_interfaces/msg/rosidl_typesupport_fastrtps_c__visibility_control.h"
#include "my_interfaces/msg/detail/double__struct.h"
#include "my_interfaces/msg/detail/double__functions.h"
#include "fastcdr/Cdr.h"

#ifndef _WIN32
# pragma GCC diagnostic push
# pragma GCC diagnostic ignored "-Wunused-parameter"
# ifdef __clang__
#  pragma clang diagnostic ignored "-Wdeprecated-register"
#  pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
# endif
#endif
#ifndef _WIN32
# pragma GCC diagnostic pop
#endif

// includes and forward declarations of message dependencies and their conversion functions

#if defined(__cplusplus)
extern "C"
{
#endif


// forward declare type support functions


using _Double__ros_msg_type = my_interfaces__msg__Double;

static bool _Double__cdr_serialize(
  const void * untyped_ros_message,
  eprosima::fastcdr::Cdr & cdr)
{
  if (!untyped_ros_message) {
    fprintf(stderr, "ros message handle is null\n");
    return false;
  }
  const _Double__ros_msg_type * ros_message = static_cast<const _Double__ros_msg_type *>(untyped_ros_message);
  // Field name: data
  {
    cdr << ros_message->data;
  }

  return true;
}

static bool _Double__cdr_deserialize(
  eprosima::fastcdr::Cdr & cdr,
  void * untyped_ros_message)
{
  if (!untyped_ros_message) {
    fprintf(stderr, "ros message handle is null\n");
    return false;
  }
  _Double__ros_msg_type * ros_message = static_cast<_Double__ros_msg_type *>(untyped_ros_message);
  // Field name: data
  {
    cdr >> ros_message->data;
  }

  return true;
}  // NOLINT(readability/fn_size)

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_my_interfaces
size_t get_serialized_size_my_interfaces__msg__Double(
  const void * untyped_ros_message,
  size_t current_alignment)
{
  const _Double__ros_msg_type * ros_message = static_cast<const _Double__ros_msg_type *>(untyped_ros_message);
  (void)ros_message;
  size_t initial_alignment = current_alignment;

  const size_t padding = 4;
  const size_t wchar_size = 4;
  (void)padding;
  (void)wchar_size;

  // field.name data
  {
    size_t item_size = sizeof(ros_message->data);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  return current_alignment - initial_alignment;
}

static uint32_t _Double__get_serialized_size(const void * untyped_ros_message)
{
  return static_cast<uint32_t>(
    get_serialized_size_my_interfaces__msg__Double(
      untyped_ros_message, 0));
}

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_my_interfaces
size_t max_serialized_size_my_interfaces__msg__Double(
  bool & full_bounded,
  bool & is_plain,
  size_t current_alignment)
{
  size_t initial_alignment = current_alignment;

  const size_t padding = 4;
  const size_t wchar_size = 4;
  size_t last_member_size = 0;
  (void)last_member_size;
  (void)padding;
  (void)wchar_size;

  full_bounded = true;
  is_plain = true;

  // member: data
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint64_t);
    current_alignment += array_size * sizeof(uint64_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint64_t));
  }

  size_t ret_val = current_alignment - initial_alignment;
  if (is_plain) {
    // All members are plain, and type is not empty.
    // We still need to check that the in-memory alignment
    // is the same as the CDR mandated alignment.
    using DataType = my_interfaces__msg__Double;
    is_plain =
      (
      offsetof(DataType, data) +
      last_member_size
      ) == ret_val;
  }

  return ret_val;
}

static size_t _Double__max_serialized_size(char & bounds_info)
{
  bool full_bounded;
  bool is_plain;
  size_t ret_val;

  ret_val = max_serialized_size_my_interfaces__msg__Double(
    full_bounded, is_plain, 0);

  bounds_info =
    is_plain ? ROSIDL_TYPESUPPORT_FASTRTPS_PLAIN_TYPE :
    full_bounded ? ROSIDL_TYPESUPPORT_FASTRTPS_BOUNDED_TYPE : ROSIDL_TYPESUPPORT_FASTRTPS_UNBOUNDED_TYPE;
  return ret_val;
}


static message_type_support_callbacks_t __callbacks_Double = {
  "my_interfaces::msg",
  "Double",
  _Double__cdr_serialize,
  _Double__cdr_deserialize,
  _Double__get_serialized_size,
  _Double__max_serialized_size
};

static rosidl_message_type_support_t _Double__type_support = {
  rosidl_typesupport_fastrtps_c__identifier,
  &__callbacks_Double,
  get_message_typesupport_handle_function,
  &my_interfaces__msg__Double__get_type_hash,
  &my_interfaces__msg__Double__get_type_description,
  &my_interfaces__msg__Double__get_type_description_sources,
};

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, my_interfaces, msg, Double)() {
  return &_Double__type_support;
}

#if defined(__cplusplus)
}
#endif
