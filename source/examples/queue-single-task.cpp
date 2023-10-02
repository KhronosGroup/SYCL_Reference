// SPDX-FileCopyrightText: 2020 The Khronos Group Inc.
//
// SPDX-License-Identifier: Apache-2.0

#include <sycl/sycl.hpp>

int main() {

  auto q = sycl::queue(sycl::default_selector_v);

  q.submit([&](sycl::handler &cgh) {
    auto os = sycl::stream{128, 128, cgh};
    cgh.single_task<class hello_world>([=] { os << "Hello World!\n"; });
  });
  q.wait();
}
