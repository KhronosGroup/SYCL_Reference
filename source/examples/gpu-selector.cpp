// SPDX-FileCopyrightText: 2020 The Khronos Group Inc.
//
// SPDX-License-Identifier: Apache-2.0

#include <sycl/sycl.hpp>

int main() {
  sycl::device d;

  try {
    d = sycl::device(sycl::gpu_selector_v);
  } catch (sycl::exception const &e) {
    std::cout << "Cannot select a GPU\n" << e.what() << "\n";
    std::cout << "Using a CPU device\n";
    d = sycl::device(sycl::cpu_selector_v);
  }

  std::cout << "Using " << d.get_info<sycl::info::device::name>();
}
