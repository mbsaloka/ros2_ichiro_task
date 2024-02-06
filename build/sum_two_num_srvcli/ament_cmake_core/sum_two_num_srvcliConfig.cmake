# generated from ament/cmake/core/templates/nameConfig.cmake.in

# prevent multiple inclusion
if(_sum_two_num_srvcli_CONFIG_INCLUDED)
  # ensure to keep the found flag the same
  if(NOT DEFINED sum_two_num_srvcli_FOUND)
    # explicitly set it to FALSE, otherwise CMake will set it to TRUE
    set(sum_two_num_srvcli_FOUND FALSE)
  elseif(NOT sum_two_num_srvcli_FOUND)
    # use separate condition to avoid uninitialized variable warning
    set(sum_two_num_srvcli_FOUND FALSE)
  endif()
  return()
endif()
set(_sum_two_num_srvcli_CONFIG_INCLUDED TRUE)

# output package information
if(NOT sum_two_num_srvcli_FIND_QUIETLY)
  message(STATUS "Found sum_two_num_srvcli: 0.0.0 (${sum_two_num_srvcli_DIR})")
endif()

# warn when using a deprecated package
if(NOT "" STREQUAL "")
  set(_msg "Package 'sum_two_num_srvcli' is deprecated")
  # append custom deprecation text if available
  if(NOT "" STREQUAL "TRUE")
    set(_msg "${_msg} ()")
  endif()
  # optionally quiet the deprecation message
  if(NOT sum_two_num_srvcli_DEPRECATED_QUIET)
    message(DEPRECATION "${_msg}")
  endif()
endif()

# flag package as ament-based to distinguish it after being find_package()-ed
set(sum_two_num_srvcli_FOUND_AMENT_PACKAGE TRUE)

# include all config extra files
set(_extras "")
foreach(_extra ${_extras})
  include("${sum_two_num_srvcli_DIR}/${_extra}")
endforeach()
