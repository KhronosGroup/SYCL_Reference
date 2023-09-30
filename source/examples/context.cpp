// SPDX-FileCopyrightText: 2020 The Khronos Group Inc.
//
// SPDX-License-Identifier: Apache-2.0

#include <sycl/sycl.hpp>

int main() {
  sycl::context context;
  auto devices = context.get_info<sycl::info::context::devices>();
  for (auto device : devices) {
    std::cout << device.get_info<sycl::info::device::name>() << std::endl;
  }
}
