// SPDX-FileCopyrightText: 2020 The Khronos Group Inc.
//
// SPDX-License-Identifier: Apache-2.0

#include <CL/sycl.hpp>

int main() {
  sycl::property_list properties{sycl::property::queue::enable_profiling()};
  auto q = sycl::queue(sycl::gpu_selector(), properties);

  std::cout << "  Platform: "
	    << q.get_device().get_platform().get_info<sycl::info::platform::name>()
	    << std::endl;

  const int num_ints = 1024 * 1024;
  const size_t num_bytes = num_ints * sizeof(int);
  const int alignment = 8;

  // Alloc memory on host
  auto src = aligned_alloc(alignment, num_bytes);
  memset(src, 1, num_bytes);

  // Alloc memory on device
  auto dst = sycl::malloc_device<int>(num_ints, q);
  q.memset(dst, 0, num_bytes).wait();

  // Copy from host to device
  auto event = q.memcpy(dst, src, num_bytes);
  event.wait();

  auto end = event.get_profiling_info<sycl::info::event_profiling::command_end>();
  auto start = event.get_profiling_info<sycl::info::event_profiling::command_start>();

  std::cout << "Elapsed time: " << (end-start)/1.0e9 << " seconds\n";

  sycl::free(dst, q);
}
