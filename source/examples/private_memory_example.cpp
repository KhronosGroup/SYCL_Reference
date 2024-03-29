// SPDX-FileCopyrightText: 2024 The Khronos Group Inc.
//
// SPDX-License-Identifier: Apache-2.0

#include <sycl/sycl.hpp>

#include <iostream>

int main() {
  sycl::queue myQueue;

  myQueue.submit([&](sycl::handler &cgh) {
    sycl::stream out(256, 256, cgh);

    // Issue 8 work-groups of 8 work-items each
    cgh.parallel_for_work_group(
        sycl::range<3>(2, 2, 2), sycl::range<3>(2, 2, 2),
        [=](sycl::group<3> myGroup) {
          //[workgroup code]

          // this variable is shared between workitems
          int myLocal;

          // this variable will be instantiated for each work-item separately
          sycl::private_memory<int, 3> myPrivate(myGroup);

          // Issue parallel work-items.  The number issued per work-group is
          // determined by the work-group size range of parallel_for_work_group.
          // In this case, 8 work-items will execute the parallel_for_work_item
          // body for each of the 8 work-groups, resulting in 64 executions
          // globally/total.
          myGroup.parallel_for_work_item([&](sycl::h_item<3> myItem) {
            //[work-item code]
            sycl::id<3> myItemId = myItem.get_local_id();
            myPrivate(myItem) = myItemId[0] + myItemId[1] + myItemId[2];
          });

          // Implicit work-group barrier

          // Carry private value across loops
          myGroup.parallel_for_work_item([&](sycl::h_item<3> myItem) {
            //[work-item code]
            out << myPrivate(myItem) << ' ';
          });
          out << sycl::stream_manipulator::endl;

          //[workgroup code]
        });
  });
}
