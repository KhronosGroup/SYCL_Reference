// SPDX-FileCopyrightText: 2020 The Khronos Group Inc.
//
// SPDX-License-Identifier: Apache-2.0

#include <CL/sycl.hpp>

int main() {
  auto platforms = sycl::platform::get_platforms();

  for (auto &platform : platforms) {
    std::cout << "Platform: "
	      << platform.get_info<sycl::info::platform::name>()
	      << std::endl;

    auto devices = platform.get_devices();
    for (auto &device : devices ) {
      std::cout << "  Device: "
		<< device.get_info<sycl::info::device::name>()
		<< std::endl;
    }
  }

  return 0;
}
