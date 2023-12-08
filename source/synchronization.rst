..
  Copyright 2020 The Khronos Group Inc.
  SPDX-License-Identifier: CC-BY-4.0

===========================
Synchronization and atomics
===========================

The available features are:

* **Accessor classes**: Accessor classes specify acquisition
  and release of buffer and image data structures to provide
  points at which underlying queue synchronization primitives
  must be generated.
* **Atomic operations**: SYCL devices support a restricted
  subset of C++ atomics and SYCL uses the library syntax
  from the next C++ specification to make this available.
* **Fences**: Fence primitives are made available to order
  loads and stores. They are exposed through the
  ``sycl::atomic_fence`` function. Fences can have acquire
  semantics, release semantics or both.
* **Barriers**: Barrier primitives are made available to
  synchronize sets of work-items within individual groups.
  They are exposed through the ``sycl::group_barrier``
  function.
* **Hierarchical parallel dispatch**: In the hierarchical
  parallelism model of describing computations,
  synchronization within the work-group is made explicit through
  multiple instances of the ``parallel_for_work_item()`` function
  call, rather than through the use of explicit work-group barrier
  operations.
* **Device event**: they are used inside SYCL kernel functions to
  wait for asynchronous operations within a SYCL kernel function
  to complete.



.. toctree::
   :maxdepth: 1

   iface/barriers-and-fences
   iface/device_event
   iface/atomic_ref
   iface/atomic-types
   iface/interaction-with-host-code
