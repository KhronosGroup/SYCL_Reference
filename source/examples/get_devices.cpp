// SPDX-FileCopyrightText: 2024 The Khronos Group Inc.
//
// SPDX-License-Identifier: Apache-2.0

#include <sycl/sycl.hpp>

int main() {
  for (auto device : sycl::device::get_devices(sycl::info::device_type::gpu)) {
    std::cout << "  Device: " << device.get_info<sycl::info::device::name>()
              << std::endl;
  }
}
