// SPDX-FileCopyrightText: 2024 The Khronos Group Inc.
//
// SPDX-License-Identifier: Apache-2.0

#include <vector>

#include <sycl/sycl.hpp>

constexpr int size = 10;

int main() {
  sycl::queue q;

  // USM allocator for data of type int in shared memory
  typedef sycl::usm_allocator<int, sycl::usm::alloc::shared> vec_alloc;
  // Create allocator for device associated with q
  vec_alloc myAlloc(q);
  // Create std vectors with the allocator
  std::vector<int, vec_alloc> a(size, myAlloc), b(size, myAlloc),
      c(size, myAlloc);

  // Get pointer to vector data for access in kernel
  auto A = a.data();
  auto B = b.data();
  auto C = c.data();

  for (int i = 0; i < size; i++) {
    a[i] = i;
    b[i] = i;
    c[i] = i;
  }

  q.submit([&](sycl::handler &h) {
     h.parallel_for(sycl::range<1>(size),
                    [=](sycl::id<1> idx) { C[idx] = A[idx] + B[idx]; });
   }).wait();

  for (int i = 0; i < size; i++)
    std::cout << c[i] << std::endl;
  return 0;
}
