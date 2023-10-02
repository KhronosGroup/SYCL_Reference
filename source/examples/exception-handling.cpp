// SPDX-FileCopyrightText: 2020 The Khronos Group Inc.
//
// SPDX-License-Identifier: Apache-2.0

#include <sycl/sycl.hpp>

int main() {

  auto exception_handler = [](sycl::exception_list exceptions) {
    for (const std::exception_ptr &e : exceptions) {
      try {
        std::rethrow_exception(e);
      } catch (const sycl::exception &e) {
        std::cout << "Caught asynchronous SYCL exception:\n"
                  << e.what() << std::endl;
      }
    }
  };

  auto q = sycl::queue(sycl::default_selector_v, exception_handler);

  try {
    q.submit([&](sycl::handler &cgh) {
      cgh.parallel_for<class error_handling>(
          // Local size (second parameter) cannot be larger than global size
          // This will throw an intentional asynchronous exception
          sycl::nd_range<1>(sycl::range<1>(1), sycl::range<1>(30)),
          [=](sycl::nd_item<1>) {
            // ...
          });
    });
    q.wait_and_throw();
  } catch (const sycl::exception &e) {
    std::cout << "Caught synchronous SYCL exception:\n"
              << e.what() << std::endl;
  }
}
