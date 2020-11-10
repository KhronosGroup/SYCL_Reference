# SPDX-FileCopyrightText: 2020 The Khronos Group Inc.
#
# SPDX-License-Identifier: Apache-2.0

cmake_minimum_required(VERSION 3.13)
project(SYCL_Reference)

enable_testing()
set(CMAKE_CXX_COMPILER dpcpp)

add_compile_options(-Wall -Wextra -pedantic -Werror)


function(add_example name)
  add_executable(${name} ${name}.cpp)
  add_test(NAME ${name} COMMAND ${name})
endfunction(add_example)

add_example(host-task)
add_example(gpu-platform)
add_example(std-vector)
add_example(event-elapsed-time)
add_example(get-platforms)
add_example(get_devices)
add_example(stream)
add_example(gpu-selector)
