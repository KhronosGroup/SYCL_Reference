// SPDX-FileCopyrightText: 2026 The Khronos Group Inc.
//
// SPDX-License-Identifier: Apache-2.0

#include <sycl/sycl.hpp>

#include <cstdlib>
#include <iostream>

int main() {
  //  Create a default queue to enqueue work to the default device
  sycl::queue myQueue;

  // Allocate normal system memory - let the Linux kernel do the work!
  // You can also use a std::vector, etc.
  int *data = (int*) malloc(1024);

  myQueue.parallel_for(1024, [=](sycl::id<1> idx) {
    // Initialize each buffer element with its own rank number starting at 0
    data[idx] = idx;
  }); // End of the kernel function

  // Explicitly wait for kernel execution since there is no accessor involved
  myQueue.wait();

  // Print result
  for (int i = 0; i < 1024; i++)
    std::cout << "data[" << i << "] = " << data[i] << std::endl;

  // Clean up with normal system free
  free(data);

  return 0;
}
