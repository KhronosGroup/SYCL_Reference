// SPDX-FileCopyrightText: 2024 The Khronos Group Inc.
//
// SPDX-License-Identifier: Apache-2.0

#include <iostream>
#include <sycl/sycl.hpp>

constexpr int count = 10;

int main() {

  // Data initialized to zeros.
  int data[count] = {0};

  auto q = sycl::queue(sycl::default_selector_v);
  {
    sycl::buffer<int, 1> data_buffer(data, sycl::range<1>(count));

    q.submit([&](sycl::handler &cgh) {
      sycl::accessor data_accessor{data_buffer, cgh};

      cgh.parallel_for<class add_five>(sycl::range<1>(count),
                                       [=](sycl::item<1> item) {
                                         auto index = item.get_id(0);
                                         data_accessor[index] += 5;
                                       });
    });
    q.wait();
  }

  for (auto e : data)
    std::cout << e << " ";
  std::cout << std::endl;
}
