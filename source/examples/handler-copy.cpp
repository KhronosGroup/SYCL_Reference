// SPDX-FileCopyrightText: 2024 The Khronos Group Inc.
//
// SPDX-License-Identifier: Apache-2.0

#include <sycl/sycl.hpp>

int main() {
  const size_t nElems = 10u;

  // Create a vector and fill it with values 0, 1, 2, 3, 4, 5, 6, 7, 8, 9
  std::vector<int> vec(nElems);
  for (size_t i = 0; i < nElems; i++)
    vec[i] = i;

  std::cout << "vec: ";
  for (int i = 0; i < nElems; i++)
    std::cout << vec[i] << " ";
  std::cout << std::endl;

  // Create a buffer with no associated user storage
  sycl::buffer<int, 1> buf{sycl::range<1>(nElems)};

  // Create a queue
  sycl::queue myQueue;

  myQueue
      .submit([&](sycl::handler &cgh) {
        // Retrieve a ranged write accessor to a global buffer with access to
        // the first half of the buffer
        sycl::accessor acc{buf, cgh, sycl::range<1>(nElems / 2), sycl::id<1>(0),
                           sycl::write_only};

        // Copy the first five elements of the vector into the buffer associated
        // with the accessor
        cgh.copy(vec.data(), acc);
      })
      .wait();

  auto h_acc = buf.get_host_access(sycl::read_only);
  std::cout << "buf: ";
  for (int i = 0; i < nElems; i++)
    std::cout << h_acc[i] << " ";
  std::cout << std::endl;
}
