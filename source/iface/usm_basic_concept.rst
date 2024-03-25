..
  Copyright 2024 The Khronos Group Inc.
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

.. _unified_addressing:

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

.. _usm-types:

============
Kinds of USM
============

USM builds upon Unified Addressing to define a shared
address space where pointer values in this space always
refer to the same location in memory. USM defines three
types of memory allocations: ``host``, ``device``, and ``shared``.

The following ``enum`` is used to refer to the different
types of allocations inside of a SYCL program:

::

  namespace sycl::usm {

  enum class alloc : /* unspecified */ {
    host,
    device,
    shared,
    unknown
  };

  } // namespace sycl::usm

.. list-table::
  :header-rows: 1

  * - USM allocation type
    - Description
  * - ``host``
    - Allocations in host memory that are accessible by a device (in addition to the host).
  * - ``device``
    - Allocations in device memory that are not accessible by the host.
  * - ``shared``
    - Allocations in shared memory that are accessible by both host and device.

USM is an optional feature which may not be supported by all devices, and
devices that support USM may not support all types of USM allocation.

A SYCL application can use the ``sycl::device::has()``
function to determine the level of USM support for a device
(See :ref:`device-aspects`).

.. seealso:: |SYCL_SPEC_USM_KINDS|

USM accesses must be within the ``sycl::context`` used for allocation
---------------------------------------------------------------------

Each USM allocation has an associated SYCL context, and any access to
that memory must use the same context.
Specifically, any SYCL kernel function that dereferences a pointer to
a USM allocation must be submitted to a :ref:`queue` that was constructed
with the same context that was used to allocate that memory.
The explicit memory operation commands that take USM pointers have a
similar restriction.

There are no similar restrictions for dereferencing a USM pointer in a
host task. This is legal regardless of which queue the host task
was submitted to so long as the USM pointer is accessible on the host.

.. warning::

  Each type of USM allocation has different rules for where that memory
  is accessible. Attempting to dereference a USM pointer on the host or
  on a device in violation of these rules results in undefined behavior.

  Passing a USM pointer to one of the explicit memory functions where
  the pointer is not accessible to the device generally results in
  undefined behavior.


Host allocations
----------------

Host allocations allow devices to directly read and write host
memory inside of a kernel.

Host allocations must also be obtained using SYCL routines
instead of system allocation routines. While a device may remotely
read and write a host allocation, the allocation does not migrate
to the device - it remains in host memory.

.. warning::

  Users should take care to properly synchronize access to
  host allocations between host execution and kernels.

The total size of host allocations will be limited by the amount
of pinnable-memory on the host on most systems.

Support for host allocations on a specific device can be queried
through ``sycl::aspect::usm_host_allocations``.

Support for atomic modification of host allocations on a specific
device can be queried through ``sycl::aspect::usm_atomic_host_allocations``.


Device allocations
------------------

Device allocations are used for explicitly managing device memory.

Device allocations are obtained through SYCL device USM allocation
routines instead of system allocation routines like ``std::malloc``
or C++ ``new``.

Device allocations are not accessible on the host, but the pointer
values remain consistent on account of :ref:`unified_addressing`.

With device allocations data is directly allocated in the device memory
and it must be explicitly copied between the host and a device.

The size of device allocations will be limited by the amount of
memory in a device.

Support for device allocations on a specific
device can be queried through ``sycl::aspect::usm_device_allocations``.

The member functions to copy and initialize data are found in
:ref:`sycl::queue shortcut functions <queue_shortcut>` and
:ref:`sycl::handler explicit memory operations <handler_expl_mem_ops>`,
and these functions may be used on device allocations if a device
supports ``sycl::aspect::usm_device_allocations``.

.. rubric:: Example

See `usm-example-2`_.


Shared allocations
------------------

Shared allocations implicitly share data between the host and devices.

Data may move to where it is being used without the programmer explicitly
informing the runtime. It is up to the runtime and backends to make sure
that a shared allocation is available where it is used.

Shared allocations must also be obtained using SYCL allocation routines
instead of the system allocator.

The maximum size of a shared allocation on a specific
device, and the total size of all shared allocations
in a context, are implementation-defined.

Support for shared allocations on a specific device can be
queried through ``sycl::aspect::usm_shared_allocations``.

.. warning::

  Not all devices may support concurrent access of a shared allocation with the host.

If a device does not support this, host execution and device
code must take turns accessing the allocation, so the host
must not access a shared allocation while a kernel is executing.

.. warning::

  Host access to a shared allocation which is also accessed by an executing
  kernel on a device that does not support concurrent access results in
  undefined behavior.

  If a device does support concurrent access, both the host and and
  the device may atomically modify the same data inside an allocation.

Allocations, or pieces of allocations, are now free to migrate to different
devices in the same context that also support this capability.
Additionally, many devices that support concurrent access may support
a working set of shared allocations larger than device memory.

Whether a device supports concurrent access with atomic modification of
shared allocations can be queried through the aspect
``sycl::aspect::usm_atomic_shared_allocations``.

.. rubric:: Performance hints

1. Performance hints for shared allocations may be specified by
   the user by enqueueing ``prefetch`` operations on a device.
   These operations inform the SYCL runtime that the specified
   shared allocation is likely to be accessed on the device in
   the future, and that it is free to migrate the allocation to
   the device. If a device supports concurrent access to shared
   allocations, then ``prefetch`` operations may be overlapped with
   kernel execution. More about ``prefetch`` is found in
   :ref:`sycl::queue shortcut functions <queue_shortcut>` and
   :ref:`sycl::handler explicit memory operations <handler_expl_mem_ops>`,
2. Users also may use the ``mem_advise`` member function to
   annotate shared allocations with ``advice``. Valid ``advice`` is defined
   by the device and its associated backend.
   See :ref:`sycl::queue shortcut functions <queue_shortcut>`
   and :ref:`sycl::handler explicit memory operations <handler_expl_mem_ops>`,
   for more information.

.. rubric:: Example

See `usm-example-1`_.


System allocations
------------------

In the most capable systems, users do not need to use SYCL USM
allocation functions to create shared allocations. The system
allocator (``malloc``/``new``) may instead be used.
Likewise, ``std::free`` and ``delete`` are used instead of ``sycl::free``.

Users may query the device to determine if
system allocations are supported for use on the device,
through ``sycl::aspect::usm_system_allocations``.

.. note::

  Host and device allocations are unaffected by this change and
  must still be allocated using their respective USM functions in order to
  guarantee their behavior.

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
