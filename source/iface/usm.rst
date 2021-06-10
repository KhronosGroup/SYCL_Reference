..
  Copyright 2020 The Khronos Group Inc.
  SPDX-License-Identifier: CC-BY-4.0

.. _usm-alloc:

====================
``sycl::usm::alloc``
====================

|2020|

::

   enum class alloc {
     host,
     device,
     shared,
     unknown
   };

Identifies type of USM memory in calls to USM-related API.

host
  Resides on host and also accessible by device

device
  Resides on device and only accessible by device

shared
  SYCL runtime may move data between host and device. Accessible by
  host and device.

.. seealso:: `SYCL Specification <https://www.khronos.org/registry/SYCL/specs/sycl-2020/html/sycl-2020.html#_kinds_of_unified_shared_memory>`__
