// SPDX-FileCopyrightText: 2023 The Khronos Group Inc.
//
// SPDX-License-Identifier: Apache-2.0

#include <sycl/sycl.hpp>

#include <iostream>
#include <numeric> 

int main() {
  sycl::queue myQueue;

  sycl::buffer<int> inputBuf { sycl::range<1>(1024) };
  sycl::buffer<int> outputBuf { sycl::range<1>(2) };
  {
    // Initialize buffer on the host with 0, 1, 2, 3, ..., 1023
    sycl::host_accessor a { inputBuf };
    std::iota(a.begin(), a.end(), 0);
  }

  myQueue.submit([&](sycl::handler& cgh) {
    sycl::accessor inputValues { inputBuf, cgh, sycl::read_only };
    sycl::accessor outputValues { outputBuf, cgh, sycl::write_only, sycl::no_init };

    cgh.parallel_for(sycl::nd_range<1>(sycl::range<1>(16), sycl::range<1>(16)), 
      [=](sycl::nd_item<1> it) {
      // Apply a group algorithm to any number of values, described by an iterator
      // range. The work-group reduces all inputValues and each work-item works on
      // part of the range.
      const int* first = inputValues.get_multi_ptr<sycl::access::decorated::no>().get_raw();
      const int* last = first + 1024;
      int sum = sycl::joint_reduce(it.get_group(), first, last, sycl::plus<>());
      outputValues[0] = sum;

      // Apply a group algorithm to a set of values held directly by work-items.
      // The work-group reduces a number of values equal to the size of the group
      // and each work-item provides one value.
      int partial_sum = sycl::reduce_over_group(it.get_group(), 
        inputValues[it.get_global_linear_id()], sycl::plus<>());
      outputValues[1] = partial_sum;
    });
  });

  {
    sycl::host_accessor a { outputBuf };
    std::cout << "sum: " << a[0] << std::endl;
    std::cout << "partial_sum: " << a[1] << std::endl;
  }

  return 0;
}
