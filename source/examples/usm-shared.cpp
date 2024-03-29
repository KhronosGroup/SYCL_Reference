// SPDX-FileCopyrightText: 2024 The Khronos Group Inc.
//
// SPDX-License-Identifier: Apache-2.0

#include <sycl/sycl.hpp>

#include <iostream>

int main() {
  //  Create a default queue to enqueue work to the default device
  sycl::queue myQueue;

  // Allocate shared memory bound to the device and context associated to the
  // queue Replacing malloc_shared with malloc_host would yield a correct
  // program that allocated device-visible memory on the host.
  int *data = sycl::malloc_shared<int>(1024, myQueue);

  myQueue.parallel_for(1024, [=](sycl::id<1> idx) {
    // Initialize each buffer element with its own rank number starting at 0
    data[idx] = idx;
  }); // End of the kernel function

  // Explicitly wait for kernel execution since there is no accessor involved
  myQueue.wait();

  // Print result
  for (int i = 0; i < 1024; i++)
    std::cout << "data[" << i << "] = " << data[i] << std::endl;

  return 0;
}
