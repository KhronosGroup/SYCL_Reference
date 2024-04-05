# SPDX-FileCopyrightText: 2020 The Khronos Group Inc.
#
# SPDX-License-Identifier: Apache-2.0

cmake_minimum_required(VERSION 3.13)
project(SYCL_Reference)

enable_testing()

add_compile_options(-fsycl -Wall -Wextra -Werror)
add_link_options(-fsycl)

function(add_example name)
  add_executable(${name} ${name}.cpp)
  add_test(NAME ${name} COMMAND ${name})
endfunction(add_example)

add_example(atomic)
add_example(host-task)
add_example(gpu-platform)
add_example(std-vector)
add_example(event-elapsed-time)
add_example(exception-handling)
add_example(get-platforms)
add_example(get_devices)
add_example(stream)
add_example(gpu-selector)
set_tests_properties(gpu-platform PROPERTIES LABELS gpu)
add_example(queue-parallel)
add_example(queue-single-task)
add_example(usm-implicit-data-movement)
add_example(anatomy)

