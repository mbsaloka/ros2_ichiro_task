// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from my_interfaces:msg/VectorObjects.idl
// generated code does not contain a copyright notice
#include "my_interfaces/msg/detail/vector_objects__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


// Include directives for member types
// Member `objects`
#include "my_interfaces/msg/detail/object__functions.h"

bool
my_interfaces__msg__VectorObjects__init(my_interfaces__msg__VectorObjects * msg)
{
  if (!msg) {
    return false;
  }
  // objects
  if (!my_interfaces__msg__Object__Sequence__init(&msg->objects, 0)) {
    my_interfaces__msg__VectorObjects__fini(msg);
    return false;
  }
  return true;
}

void
my_interfaces__msg__VectorObjects__fini(my_interfaces__msg__VectorObjects * msg)
{
  if (!msg) {
    return;
  }
  // objects
  my_interfaces__msg__Object__Sequence__fini(&msg->objects);
}

bool
my_interfaces__msg__VectorObjects__are_equal(const my_interfaces__msg__VectorObjects * lhs, const my_interfaces__msg__VectorObjects * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // objects
  if (!my_interfaces__msg__Object__Sequence__are_equal(
      &(lhs->objects), &(rhs->objects)))
  {
    return false;
  }
  return true;
}

bool
my_interfaces__msg__VectorObjects__copy(
  const my_interfaces__msg__VectorObjects * input,
  my_interfaces__msg__VectorObjects * output)
{
  if (!input || !output) {
    return false;
  }
  // objects
  if (!my_interfaces__msg__Object__Sequence__copy(
      &(input->objects), &(output->objects)))
  {
    return false;
  }
  return true;
}

my_interfaces__msg__VectorObjects *
my_interfaces__msg__VectorObjects__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  my_interfaces__msg__VectorObjects * msg = (my_interfaces__msg__VectorObjects *)allocator.allocate(sizeof(my_interfaces__msg__VectorObjects), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(my_interfaces__msg__VectorObjects));
  bool success = my_interfaces__msg__VectorObjects__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
my_interfaces__msg__VectorObjects__destroy(my_interfaces__msg__VectorObjects * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    my_interfaces__msg__VectorObjects__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
my_interfaces__msg__VectorObjects__Sequence__init(my_interfaces__msg__VectorObjects__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  my_interfaces__msg__VectorObjects * data = NULL;

  if (size) {
    data = (my_interfaces__msg__VectorObjects *)allocator.zero_allocate(size, sizeof(my_interfaces__msg__VectorObjects), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = my_interfaces__msg__VectorObjects__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        my_interfaces__msg__VectorObjects__fini(&data[i - 1]);
      }
      allocator.deallocate(data, allocator.state);
      return false;
    }
  }
  array->data = data;
  array->size = size;
  array->capacity = size;
  return true;
}

void
my_interfaces__msg__VectorObjects__Sequence__fini(my_interfaces__msg__VectorObjects__Sequence * array)
{
  if (!array) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();

  if (array->data) {
    // ensure that data and capacity values are consistent
    assert(array->capacity > 0);
    // finalize all array elements
    for (size_t i = 0; i < array->capacity; ++i) {
      my_interfaces__msg__VectorObjects__fini(&array->data[i]);
    }
    allocator.deallocate(array->data, allocator.state);
    array->data = NULL;
    array->size = 0;
    array->capacity = 0;
  } else {
    // ensure that data, size, and capacity values are consistent
    assert(0 == array->size);
    assert(0 == array->capacity);
  }
}

my_interfaces__msg__VectorObjects__Sequence *
my_interfaces__msg__VectorObjects__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  my_interfaces__msg__VectorObjects__Sequence * array = (my_interfaces__msg__VectorObjects__Sequence *)allocator.allocate(sizeof(my_interfaces__msg__VectorObjects__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = my_interfaces__msg__VectorObjects__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
my_interfaces__msg__VectorObjects__Sequence__destroy(my_interfaces__msg__VectorObjects__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    my_interfaces__msg__VectorObjects__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
my_interfaces__msg__VectorObjects__Sequence__are_equal(const my_interfaces__msg__VectorObjects__Sequence * lhs, const my_interfaces__msg__VectorObjects__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!my_interfaces__msg__VectorObjects__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
my_interfaces__msg__VectorObjects__Sequence__copy(
  const my_interfaces__msg__VectorObjects__Sequence * input,
  my_interfaces__msg__VectorObjects__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(my_interfaces__msg__VectorObjects);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    my_interfaces__msg__VectorObjects * data =
      (my_interfaces__msg__VectorObjects *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!my_interfaces__msg__VectorObjects__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          my_interfaces__msg__VectorObjects__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!my_interfaces__msg__VectorObjects__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
