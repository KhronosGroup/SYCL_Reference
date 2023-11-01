..
  Copyright 2020 The Khronos Group Inc.
  SPDX-License-Identifier: CC-BY-4.0

.. temp ref
.. _malloc_device:

***************
USM allocations
***************

.. _usm_allocations:

.. rst-class:: api-class


The USM offers a range of allocation functions, each designed to
accommodate potential future extensions by accepting a ``property_list``
parameter. It's important to note that the core SYCL specification
currently lacks any specific definitions for USM allocation properties.
Some of the allocation functions support explicit alignment parameters,
and they behave similarly to ``std::aligned_alloc`` by returning ``nullptr``
when the alignment exceeds the implementation's capabilities. Some allocation
functions are templated on the allocated type ``T``, while others are not.

.. seealso:: |SYCL_SPEC_USM_ALLOC|

=======================
C++ allocator interface
=======================

.. _allocator_interface:

SYCL defines an allocator class named ``usm_allocator`` that satisfies
the C++ named requirement ``Allocator``. The ``AllocKind`` template parameter
can be either ``usm::alloc::host`` or
``usm::alloc::shared``, causing the allocator to make
either host USM allocations or shared USM allocations.

The ``usm_allocator`` class has a template argument ``Alignment``,
which specifies the minimum alignment for memory that it allocates.
This alignment is used even if the allocator is rebound to a different
type. Memory allocated by this allocator is suitably aligned for objects
of its underlying ``value_type`` or at the alignment specified by
``Alignment``, whichever is greater.

=======================
``sycl::usm_allocator``
=======================

::

   template <typename T, sycl::usm::alloc AllocKind, size_t Alignment = 0>

   class usm_allocator;

.. rubric:: Template parameters

=============  ===
``T``          Type of allocated element
``AllocKind``  Type of allocation, see `usm-alloc`
``Alignment``  Alignment of the allocation
=============  ===

There is no specialization for ``usm::alloc::device`` because an ``Allocator``
is required to allocate memory that is accessible on the host.

(constructors)
==============

::

  usm_allocator(const context& syclContext, const device& syclDevice,
              const property_list& propList = {});

  usm_allocator(const queue& syclQueue, const property_list& propList = {});

Constructs a ``usm_allocator`` instance that allocates USM for the provided
context and device presented with first constructor.
The second constructor present a simplified form where ``syclQueue`` provides
the ``device`` and ``context``.

.. rubric:: Exceptions

``errc::invalid``
  If ``syclContext`` does not encapsulate the SYCL ``device`` returned
  by ``deviceSelector``.

``errc::feature_not_supported``
  If ``AllocKind`` is ``usm::alloc::host``, the constructors throws a synchronous
  ``exception`` with this error code if no device in ``syclContext`` has
  ``aspect::usm_host_allocations``. The ``syclDevice`` is ignored for this allocation kind.

  If ``AllocKind`` is ``usm::alloc::shared``, the constructors throws a synchronous
  ``exception`` with this error code if the ``syclDevice``
  does not have ``aspect::usm_shared_allocations``.

.. seealso:: `C++ Allocator <https://en.cppreference.com/w/cpp/named_req/Allocator>`__


.. _allocation_functions :

====================
Allocation functions
====================

=======================
``sycl::malloc_device``
=======================

::

   void* sycl::malloc_device(size_t numBytes, const device& syclDevice,
                          const context& syclContext,
                          const property_list& propList = {});

   template <typename T>
   T* sycl::malloc_device(size_t count, const device& syclDevice,
                          const context& syclContext,
                          const property_list& propList = {});

   void* sycl::malloc_device(size_t numBytes, const queue& syclQueue,
                          const property_list& propList = {});

   template <typename T>
   T* sycl::malloc_device(size_t count, const queue& syclQueue,
                          const property_list& propList = {});

   void* sycl::aligned_alloc_device(size_t alignment, size_t numBytes,
                          const device& syclDevice,
                          const context& syclContext,
                          const property_list& propList = {});

   template <typename T>
   T* sycl::aligned_alloc_device(size_t alignment, size_t count,
                          const device& syclDevice,
                          const context& syclContext,
                          const property_list& propList = {});

   void* sycl::aligned_alloc_device(size_t alignment, size_t numBytes,
                          const queue& syclQueue,
                          const property_list& propList = {});

   template <typename T>
   T* sycl::aligned_alloc_device(size_t alignment, size_t count,
                          const queue& syclQueue,
                          const property_list& propList = {})

.. rubric:: Parameters

==================  ===
``alignment``       alignment of allocated data
``numBytes``        allocation size in bytes
``count``           number of elements
``syclDevice``      See :ref:`device`
``syclQueue``       See :ref:`queue`
``syclContext``     See :ref:`context`
``propList``
==================  ===

On successful USM device allocation, these functions return a pointer to
the newly allocated memory, which must eventually be deallocated with
``sycl::free`` in order to avoid a memory leak. If there are not enough
resources to allocate the requested memory, these functions
return ``nullptr``.

When the allocation size is zero bytes (``numBytes`` or ``count`` is zero),
these functions behave in a manner consistent with C++ ``std::malloc``.
The value returned is unspecified in this case, and the returned pointer
may not be used to access storage. If this pointer is not null, it must be
passed to ``sycl::free`` to avoid a memory leak.

See :ref:`event-elapsed-time` for usage.


=====================
``sycl::malloc_host``
=====================

::

   void* sycl::malloc_host(size_t numBytes, const context& syclContext,
                        const property_list& propList = {});

   template <typename T>
   T* sycl::malloc_host(size_t count, const context& syclContext,
                        const property_list& propList = {});

   void* sycl::malloc_host(size_t numBytes, const queue& syclQueue,
                        const property_list& propList = {});

   template <typename T>
   T* sycl::malloc_host(size_t count, const queue& syclQueue,
                        const property_list& propList = {});

   void* sycl::aligned_alloc_host(size_t alignment, size_t numBytes,
                        const context& syclContext,
                        const property_list& propList = {});

   template <typename T>
   T* sycl::aligned_alloc_host(size_t alignment, size_t count,
                        const context& syclContext,
                        const property_list& propList = {});

   void* sycl::aligned_alloc_host(size_t alignment, size_t numBytes,
                        const queue& syclQueue,
                        const property_list& propList = {});

   template <typename T>
   T* sycl::aligned_alloc_host(size_t alignment, size_t count,
                        const queue& syclQueue,
                        const property_list& propList = {});

.. rubric:: Parameters

==================  ===
``alignment``       alignment of allocated data
``numBytes``        allocation size in bytes
``count``           number of elements
``syclDevice``      See :ref:`device`
``syclQueue``       See :ref:`queue`
``syclContext``     See :ref:`context`
``propList``
==================  ===

On successful USM host allocation, these functions return a pointer
to the newly allocated memory, which must eventually be deallocated
with ``sycl::free`` in order to avoid a memory leak. If there are
not enough resources to allocate the requested memory, these functions
return ``nullptr``.

When the allocation size is zero bytes (``numBytes`` or ``count`` is zero),
these functions behave in a manner consistent with C++ ``std::malloc``.
The value returned is unspecified in this case, and the returned pointer
may not be used to access storage. If this pointer is not null, it must be
passed to ``sycl::free`` to avoid a memory leak.

See :ref:`usm-implicit-data-movement` for usage.

=======================
``sycl::malloc_shared``
=======================

::

   void* sycl::malloc_shared(size_t numBytes, const device& syclDevice,
                          const context& syclContext,
                          const property_list& propList = {});

   template <typename T>
   T* sycl::malloc_shared(size_t count, const device& syclDevice,
                          const context& syclContext,
                          const property_list& propList = {});

   void* sycl::malloc_shared(size_t numBytes, const queue& syclQueue,
                          const property_list& propList = {});

   template <typename T>
   T* sycl::malloc_shared(size_t count, const queue& syclQueue,
                          const property_list& propList = {});

   void* sycl::aligned_alloc_shared(size_t alignment, size_t numBytes,
                          const device& syclDevice,
                          const context& syclContext,
                          const property_list& propList = {});

   template <typename T>
   T* sycl::aligned_alloc_shared(size_t alignment, size_t count,
                          const device& syclDevice,
                          const context& syclContext,
                          const property_list& propList = {});

   void* sycl::aligned_alloc_shared(size_t alignment, size_t numBytes,
                          const queue& syclQueue,
                          const property_list& propList = {});

   template <typename T>
   T* sycl::aligned_alloc_shared(size_t alignment, size_t count,
                          const queue& syclQueue,
                          const property_list& propList = {});

.. rubric:: Parameters

==================  ===
``alignment``       alignment of allocated data
``numBytes``        allocation size in bytes
``count``           number of elements
``syclDevice``      See :ref:`device`
``syclQueue``       See :ref:`queue`
``syclContext``     See :ref:`context`
``propList``
==================  ===

On successful USM shared allocation, these functions return a pointer to the
newly allocated memory, which must eventually be deallocated with
``sycl::free`` in order to avoid a memory leak. If there are not enough
resources to allocate the requested memory, these functions return ``nullptr``.

When the allocation size is zero bytes (``numBytes`` or ``count`` is zero),
these functions behave in a manner consistent with C++ ``std::malloc``.
The value returned is unspecified in this case, and the returned pointer
may not be used to access storage. If this pointer is not null, it must be
passed to ``sycl::free`` to avoid a memory leak.

See :ref:`usm-implicit-data-movement` for usage.

.. rubric:: Example 1

.. literalinclude:: /examples/std-vector.cpp
   :lines: 5-
   :linenos:

Output:

.. literalinclude:: /examples/std-vector.out
   :lines: 5-

.. _usm-implicit-data-movement:

.. rubric:: Example 2

In this example two arrays are created, ``hostArray`` and ``sharedArray``,
that are host and shared allocations, respectively. While both host
and shared allocations are directly accessible in host code, we only
initialize ``hostArray`` here. Similarly, it can be directly accessed
inside the kernel, performing remote reads of the data. The runtime
ensures that ``sharedArray`` is available on the device before the
kernel accesses it and that it is later available
by the host code, all without programmer intervention.

.. literalinclude:: /examples/usm-implicit-data-movement.cpp
   :lines: 5-
   :linenos:

Output:

.. literalinclude:: /examples/usm-implicit-data-movement.out
   :lines: 5-
