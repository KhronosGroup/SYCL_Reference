// SPDX-FileCopyrightText: 2020 The Khronos Group Inc.
//
// SPDX-License-Identifier: Apache-2.0

#include <CL/sycl.hpp>

int main() {
  sycl::queue q;
  q.submit([&](sycl::handler &h) {
	     // setup sycl stream class to print standard output from
	     // device code
	     auto out = sycl::stream(1024, 768, h);
	     auto task =
	       [=]() {
		 out << "In a task\n";
	       };
	     h.single_task(task);
	   });
}
