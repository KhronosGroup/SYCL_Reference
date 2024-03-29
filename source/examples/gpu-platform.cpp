// SPDX-FileCopyrightText: 2024 The Khronos Group Inc.
//
// SPDX-License-Identifier: Apache-2.0

#include <sycl/sycl.hpp>

int main() {
  // Select a platform with a GPU
  auto p = sycl::platform(sycl::gpu_selector_v);
  std::cout << "Platform: " << p.get_info<sycl::info::platform::name>() << "\n";
  // Enumerate all the GPUs
  for (auto &d : p.get_devices()) {
    std::cout << "  Device: " << d.get_info<sycl::info::device::name>()
              << std::endl;
  }
}
