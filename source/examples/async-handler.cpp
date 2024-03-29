// SPDX-FileCopyrightText: 2024 The Khronos Group Inc.
//
// SPDX-License-Identifier: Apache-2.0

#include <sycl/sycl.hpp>

auto async_handler_object = [](sycl::exception_list exceptions) {
  for (auto e : exceptions) {
    try {
      std::rethrow_exception(e);
    } catch (sycl::exception const &e) {
      std::cout << "Caught asynchronous SYCL exception:\n"
                << e.what() << std::endl;
    }
  }
};

class async_error_example {};

int main() {
  // Create a queue with asynchronous handler
  sycl::queue myQueue{async_handler_object};

  myQueue.submit([&](sycl::handler &cgh) {
    // Throw sycl::exception for async_handler_object to catch
    cgh.host_task([]() {
      throw sycl::exception(std::error_code{}, "Example exception!");
    });
  });

  // Invocation of sycl::async_handler is triggered here
  myQueue.wait_and_throw();
}
