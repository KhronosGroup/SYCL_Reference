// SPDX-FileCopyrightText: 2024 The Khronos Group Inc.
//
// SPDX-License-Identifier: Apache-2.0

#include <sycl/sycl.hpp>

int main() {
  sycl::queue q;

  q.submit([&](sycl::handler &cgh) {
    // Setup sycl::stream class to print standard output from
    // the device code
    auto out = sycl::stream(1024, 768, cgh);

    cgh.single_task<class stream_task>([=]() { out << "In a task\n"; });
  });

  q.wait();
}
