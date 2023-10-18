..
  Copyright 2020 The Khronos Group Inc.
  SPDX-License-Identifier: CC-BY-4.0

.. _usm_basic_concept:

*****************
USM Basic Concept
*****************

Unified Shared Memory (USM) provides a pointer-based
alternative to the buffer programming model.

USM enables:

* Easier integration into existing code bases by representing
  allocations as pointers rather than buffers, with full
  support for pointer arithmetic into allocations.
* Fine-grain control over ownership and accessibility of
  allocations, to optimally choose between performance
  and programmer convenience.
* A simpler programming model, by automatically migrating
  some allocations between SYCL devices and the host.

.. seealso:: |SYCL_SPEC_USM|

==================
Unified addressing
==================

Unified Addressing guarantees that all devices will use a
unified address space.

Pointer values in the unified address space will always
refer to the same location in memory. The unified address
space encompasses the host and one or more devices.

Note that this does not require addresses in the unified
address space to be accessible on all devices, just that
pointer values will be consistent.



.. _usm-example-1:

=========
Example 1
=========

Example of how shared memory can be used between host and device:

.. literalinclude:: /examples/usm-shared.cpp
   :lines: 5-
   :linenos:

.. _usm-example-2:

=========
Example 2
=========

Example of using less capable device memory, which requires
an explicit copy between the device and the host:

.. literalinclude:: /examples/usm-device.cpp
   :lines: 5-
   :linenos:
