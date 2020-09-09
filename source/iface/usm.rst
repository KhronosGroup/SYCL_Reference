..
  Copyright 2020 The Khronos Group Inc.
  SPDX-License-Identifier: CC-BY-4.0

.. _usm-alloc:

=======
 alloc
=======

|2020|

::

   enum class alloc {
     host,
     device,
     shared,
     unknown
   };

.. rubric:: Namespace

::

   usm

Identifies type of USM memory in calls to USM-related API.

host
  Resides on host and also accessible by device

device
  Resides on device and only accessible by device

shared
  SYCL runtime may move data between host and device. Accessible by
  host and device.

.. seealso:: |SYCL_SPEC_USM_ALLOC|
