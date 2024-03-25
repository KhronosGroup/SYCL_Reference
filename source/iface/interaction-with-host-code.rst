..
  Copyright 2024 The Khronos Group Inc.
  SPDX-License-Identifier: CC-BY-4.0

.. _interaction_with_host_code:

**************************
Interaction with host code
**************************

When a kernel runs on a device that has either
``sycl::aspect::usm_atomic_host_allocations`` or
``sycl::aspect::usm_atomic_shared_allocations``, the
device code and the host code can concurrently access
the same memory. This has a ramification on the atomic
operations because it is possible for device code and
host code to perform atomic operations on the same
object `M` in this shared memory. It also has a ramification
on the fence operations because the C++ core language defines
the semantics of these fence operations in relation to atomic
operations on some shared object `M`. The following paragraphs
specify the guarantees that the SYCL implementation provides
when the application performs atomic or fence operations in
device code using the memory scope ``sycl::memory_scope::system``.

* Atomic operations in device code using ``sycl::atomic_ref`` on
  an object `M` are guaranteed to be atomic with respect to atomic
  operations in host code using ``std::atomic_ref`` on that same
  object `M`.
* Fence operations in device code using ``sycl::atomic_fence``
  synchronize with fence operations in host code using
  ``std::atomic_thread_fence`` if the fence operations shared the
  same atomic object `M` and follow the rules for fence synchronization
  defined in the C++ core language.
* Fence operations in device code using ``sycl::atomic_fence``
  synchronize with atomic operations in host code using
  ``std::atomic_ref`` if the operations share the same atomic
  object `M` and follow the rules for fence synchronization
  defined in the C++ core language.
* Atomic operations in device code using ``sycl::atomic_ref``
  synchronize with fence operations in host code using
  ``std::atomic_thread_fence`` if the operations share the same
  atomic object `M` and follow the rules for fence synchronization
  defined in the C++ core language.

.. seealso:: |SYCL_SPEC_INT_W_HOST_CODE|
