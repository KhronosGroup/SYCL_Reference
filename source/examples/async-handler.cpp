// SPDX-FileCopyrightText: 2023 The Khronos Group Inc.
//
// SPDX-License-Identifier: Apache-2.0

#include <sycl/sycl.hpp>

auto async_handler = [](sycl::exception_list exceptions) {
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
  sycl::queue myQueue{async_handler};

  myQueue.submit([&](sycl::handler &cgh) {
    // Throw sycl::exception for async_handler to catch
    cgh.host_task([]() {
      throw sycl::exception(std::error_code{}, "Example exception!");
    });
  });

  // Invocation of async_handler is triggered here
  myQueue.wait_and_throw();
}
