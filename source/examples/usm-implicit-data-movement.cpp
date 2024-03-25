// SPDX-FileCopyrightText: 2024 The Khronos Group Inc.
//
// SPDX-License-Identifier: Apache-2.0

#include <sycl/sycl.hpp>

constexpr int N = 42;

int main() {
  sycl::property_list properties{sycl::property::queue::enable_profiling()};
  auto q = sycl::queue(sycl::default_selector_v, properties);

  std::cout
      << "  Platform: "
      << q.get_device().get_platform().get_info<sycl::info::platform::name>()
      << std::endl;

  int *host_array = sycl::malloc_host<int>(N, q);
  int *shared_array = sycl::malloc_shared<int>(N, q);

  for (int i = 0; i < N; i++) {
    // Initialize hostArray on host
    host_array[i] = i;
  }

  q.submit([&](sycl::handler &h) {
    h.parallel_for(N, [=](sycl::id<1> i) {
      // access sharedArray and hostArray on device
      shared_array[i] = host_array[i] + 1;
    });
  });
  q.wait();

  for (int i = 0; i < N; i++) {
    // access sharedArray on host
    host_array[i] = shared_array[i];
  }

  sycl::free(shared_array, q);
  sycl::free(host_array, q);

  return 0;
}
