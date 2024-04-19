..
  Copyright 2024 The Khronos Group Inc.
  SPDX-License-Identifier: CC-BY-4.0

******************
Class availability
******************

In SYCL some SYCL runtime classes are available to the SYCL application, some
are available within a SYCL kernel function and some are available on both and
can be passed as arguments to a SYCL kernel function.

Each of the following SYCL runtime classes must be available to the host
application: :ref:`buffer`, :ref:`buffer_allocator`, :ref:`context`,
:ref:`device`, :ref:`device_image`, :ref:`event`, :ref:`exception`,
:ref:`handler`, :ref:`host_accessor`, :ref:`host_sampled_image_accessor`,
:ref:`host_unsampled_image_accessor`, :ref:`id`, :ref:`image_allocator`,
:ref:`kernel`, :ref:`kernel_id`, :ref:`marray`, `kernel_bundle`,
:ref:`nd_range`, :ref:`platform`, :ref:`queue`, :ref:`range`,
:ref:`sampled_image`, :ref:`image_sampler`, :ref:`stream`,
:ref:`unsampled_image` and :ref:`vec`.

Each of the following SYCL runtime classes must be available within a SYCL
kernel function: :ref:`command-accessor`, :ref:`atomic_ref`,
:ref:`device_event`, :ref:`group`, :ref:`h_item`, :ref:`id`, :ref:`item`,
:ref:`local_accessor`, :ref:`marray`, :ref:`multi_ptr`, :ref:`nd_item`,
:ref:`range`, :ref:`reducer`, :ref:`sampled_image_accessor`, :ref:`stream`,
:ref:`sub_group`, :ref:`unsampled_image_accessor` and :ref:`vec`.

.. seealso:: |SYCL_SPEC_CLASS_AVLBL|
