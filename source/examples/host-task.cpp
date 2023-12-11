// SPDX-FileCopyrightText: 2023 The Khronos Group Inc.
//
// SPDX-License-Identifier: Apache-2.0

#include <sycl/sycl.hpp>

#include <iostream>

int main() {
  const int n = 10;
  sycl::queue q;

  int *data = sycl::malloc_shared<int>(n + 1, q);
  memset(data, 0, sizeof(*data) * n);

  sycl::event e;
  for (int i = 1; i < n; i += 2) {
    e = q.submit([&](auto &h) {
      // wait for previous device task
      e.wait();
      auto device_task = [=]() { data[i] = data[i - 1] + 1; };
      h.single_task(device_task);
    });

    q.submit([&](auto &h) {
      // wait for device task to complete
      e.wait();
      auto host_task = [=]() { data[i + 1] = data[i] + 1; };
      h.host_task(host_task);
    });
  }
  for (int i = 0; i < n; i++)
    std::cout << i << ": " << data[i] << "\n";

  sycl::free(data, q);
}
