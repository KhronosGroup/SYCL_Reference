..
  Copyright 2020 The Khronos Group Inc.
  SPDX-License-Identifier: CC-BY-4.0

.. _usm_allocations:

***************
USM allocations
***************

The USM offers a range of allocation functions, each designed to
accommodate potential future extensions by accepting a ``sycl::property_list``
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

SYCL defines an allocator class named ``sycl::usm_allocator`` that
satisfies the C++ named requirement ``Allocator``. The ``AllocKind``
template parameter can be either ``sycl::usm::alloc::host`` or
``sycl::usm::alloc::shared``, causing the allocator to make
either host USM allocations or shared USM allocations.

The ``sycl::usm_allocator`` class has a template argument ``Alignment``,
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
``T``          Type of allocated element.
``AllocKind``  Type of allocation.
``Alignment``  Alignment of the allocation.
=============  ===

There is no specialization for ``sycl::usm::alloc::device`` because an
``Allocator`` is required to allocate memory that is accessible on the host.

(constructors)
==============

::

  usm_allocator(const sycl::context& syclContext,
                const sycl::device& syclDevice,
                const sycl::property_list& propList = {});

  usm_allocator(const sycl::queue& syclQueue,
                const sycl::property_list& propList = {});

Constructs a ``sycl::usm_allocator`` instance that allocates USM for
the provided context and device presented with first constructor.
The second constructor present a simplified form where ``syclQueue``
provides the :ref:`device` and :ref:`context`.

.. rubric:: Exceptions

``sycl::errc::invalid``
  If ``syclContext`` does not encapsulate the ``sycl::device`` returned
  by ``deviceSelector``.

``sycl::errc::feature_not_supported``
  If ``AllocKind`` is ``sycl::usm::alloc::host``, the constructors throws a synchronous
  ``sycl::exception`` with this error code if no device in ``syclContext`` has
  ``sycl::aspect::usm_host_allocations``. The ``syclDevice`` is ignored for this
  allocation kind.

  If ``AllocKind`` is ``sycl::usm::alloc::shared``, the constructors throws a synchronous
  ``sycl::exception`` with this error code if the ``syclDevice``
  does not have ``sycl::aspect::usm_shared_allocations``.

.. seealso:: `C++ Allocator <https://en.cppreference.com/w/cpp/named_req/Allocator>`__


.. _allocation_functions :

====================
Allocation functions
====================

``sycl::malloc_device``
=======================

::

   void* sycl::malloc_device(size_t numBytes,
                             const sycl::device& syclDevice,
                             const sycl::context& syclContext,
                             const sycl::property_list& propList = {});

   template <typename T>
   T* sycl::malloc_device(size_t count,
                          const sycl::device& syclDevice,
                          const sycl::context& syclContext,
                          const sycl::property_list& propList = {});

   void* sycl::malloc_device(size_t numBytes,
                             const sycl::queue& syclQueue,
                             const sycl::property_list& propList = {});

   template <typename T>
   T* sycl::malloc_device(size_t count, const sycl::queue& syclQueue,
                          const sycl::property_list& propList = {});

   void* sycl::aligned_alloc_device(size_t alignment, size_t numBytes,
                                    const sycl::device& syclDevice,
                                    const sycl::context& syclContext,
                                    const sycl::property_list& propList = {});

   template <typename T>
   T* sycl::aligned_alloc_device(size_t alignment, size_t count,
                                 const sycl::device& syclDevice,
                                 const sycl::context& syclContext,
                                 const sycl::property_list& propList = {});

   void* sycl::aligned_alloc_device(size_t alignment, size_t numBytes,
                                    const sycl::queue& syclQueue,
                                    const sycl::property_list& propList = {});

   template <typename T>
   T* sycl::aligned_alloc_device(size_t alignment, size_t count,
                                 const sycl::queue& syclQueue,
                                 const sycl::property_list& propList = {})

.. rubric:: Parameters

==================  ===
``alignment``       Alignment of allocated data.
``numBytes``        Allocation size in bytes.
``count``           Number of elements.
``syclDevice``      See :ref:`device`.
``syclQueue``       See :ref:`queue`.
``syclContext``     See :ref:`context`.
``propList``        Optional property list.
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

See :ref:`Events example 1 <event-elapsed-time>` for usage.


``sycl::malloc_host``
=====================

::

   void* sycl::malloc_host(size_t numBytes,
                           const sycl::context& syclContext,
                           const sycl::property_list& propList = {});

   template <typename T>
   T* sycl::malloc_host(size_t count,
                        const sycl::context& syclContext,
                        const sycl::property_list& propList = {});

   void* sycl::malloc_host(size_t numBytes,
                           const sycl::queue& syclQueue,
                           const sycl::property_list& propList = {});

   template <typename T>
   T* sycl::malloc_host(size_t count,
                        const sycl::queue& syclQueue,
                        const sycl::property_list& propList = {});

   void* sycl::aligned_alloc_host(size_t alignment, size_t numBytes,
                                  const sycl::context& syclContext,
                                  const sycl::property_list& propList = {});

   template <typename T>
   T* sycl::aligned_alloc_host(size_t alignment, size_t count,
                               const sycl::context& syclContext,
                               const sycl::property_list& propList = {});

   void* sycl::aligned_alloc_host(size_t alignment, size_t numBytes,
                                  const sycl::queue& syclQueue,
                                  const sycl::property_list& propList = {});

   template <typename T>
   T* sycl::aligned_alloc_host(size_t alignment, size_t count,
                               const sycl::queue& syclQueue,
                               const sycl::property_list& propList = {});

.. rubric:: Parameters

==================  ===
``alignment``       Alignment of allocated data.
``numBytes``        Allocation size in bytes.
``count``           Number of elements.
``syclDevice``      See :ref:`device`.
``syclQueue``       See :ref:`queue`.
``syclContext``     See :ref:`context`.
``propList``        Optional property list.
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

``sycl::malloc_shared``
=======================

::

   void* sycl::malloc_shared(size_t numBytes,
                             const sycl::device& syclDevice,
                             const sycl::context& syclContext,
                             const sycl::property_list& propList = {});

   template <typename T>
   T* sycl::malloc_shared(size_t count,
                          const sycl::device& syclDevice,
                          const sycl::context& syclContext,
                          const sycl::property_list& propList = {});

   void* sycl::malloc_shared(size_t numBytes,
                             const sycl::queue& syclQueue,
                             const sycl::property_list& propList = {});

   template <typename T>
   T* sycl::malloc_shared(size_t count,
                          const sycl::queue& syclQueue,
                          const sycl::property_list& propList = {});

   void* sycl::aligned_alloc_shared(size_t alignment, size_t numBytes,
                                    const sycl::device& syclDevice,
                                    const sycl::context& syclContext,
                                    const sycl::property_list& propList = {});

   template <typename T>
   T* sycl::aligned_alloc_shared(size_t alignment, size_t count,
                                 const sycl::device& syclDevice,
                                 const sycl::context& syclContext,
                                 const sycl::property_list& propList = {});

   void* sycl::aligned_alloc_shared(size_t alignment, size_t numBytes,
                                    const sycl::queue& syclQueue,
                                    const sycl::property_list& propList = {});

   template <typename T>
   T* sycl::aligned_alloc_shared(size_t alignment, size_t count,
                                 const sycl::queue& syclQueue,
                                 const sycl::property_list& propList = {});

.. rubric:: Parameters

==================  ===
``alignment``       Alignment of allocated data.
``numBytes``        Allocation size in bytes.
``count``           Number of elements.
``syclDevice``      See :ref:`device`.
``syclQueue``       See :ref:`queue`.
``syclContext``     See :ref:`context`.
``propList``        Optional property list.
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


==================================
Parameterized allocation functions
==================================

The functions below take a ``kind`` parameter that specifies the type of
USM to allocate. When ``kind`` is ``sycl::usm::alloc::device``, then the
allocation device must have ``sycl::aspect::usm_device_allocations``.
When kind is ``sycl::usm::alloc::host``, at least one device in the allocation
context must have ``sycl::aspect::usm_host_allocations``. When ``kind`` is
``sycl::usm::alloc::shared``, the allocation device must have
``sycl::aspect::usm_shared_allocations``. If these requirements are violated,
the allocation function throws a synchronous ``sycl::exception`` with the
``sycl::errc::feature_not_supported`` error code.

``sycl::malloc``
================

::

   void* sycl::malloc(size_t numBytes,
                      const sycl::device& syclDevice,
                      const sycl::context& syclContext,
                      sycl::usm::alloc kind,
                      const sycl::property_list& propList = {});

   template <typename T>
   T* sycl::malloc(size_t count,
                   const sycl::device& syclDevice,
                   const sycl::context& syclContext,
                   sycl::usm::alloc kind,
                   const sycl::property_list& propList = {});

   void* sycl::malloc(size_t numBytes,
                      const sycl::queue& syclQueue,
                      sycl::usm::alloc kind,
                      const sycl::property_list& propList = {});

   template <typename T>
   T* sycl::malloc(size_t count,
                   const sycl::queue& syclQueue,
                   sycl::usm::alloc kind,
                   const sycl::property_list& propList = {});

   void* sycl::aligned_alloc(size_t alignment, size_t numBytes,
                             const sycl::device& syclDevice,
                             const sycl::context& syclContext,
                             sycl::usm::alloc kind,
                             const sycl::property_list& propList = {});

   template <typename T>
   T* sycl::aligned_alloc(size_t alignment, size_t count,
                          const sycl::device& syclDevice,
                          const sycl::context& syclContext,
                          sycl::usm::alloc kind,
                          const sycl::property_list& propList = {});

   void* sycl::aligned_alloc(size_t alignment, size_t numBytes,
                             const sycl::queue& syclQueue,
                             sycl::usm::alloc kind,
                             const sycl::property_list& propList = {});

   template <typename T>
   T* sycl::aligned_alloc(size_t alignment, size_t count,
                          const sycl::queue& syclQueue,
                          sycl::usm::alloc kind,
                          const sycl::property_list& propList = {});


On successful USM shared allocation, these functions return a pointer to the
newly allocated memory, which must eventually be deallocated with
``sycl::free`` in order to avoid a memory leak. If there are not enough
resources to allocate the requested memory, these functions return ``nullptr``.

When the allocation size is zero bytes (``numBytes`` or ``count`` is zero),
these functions behave in a manner consistent with C++ ``std::malloc``.
The value returned is unspecified in this case, and the returned pointer
may not be used to access storage. If this pointer is not null, it must be
passed to ``sycl::free`` to avoid a memory leak.

.. rubric:: Parameters

==================  ===
``alignment``       Alignment of allocated data.
``numBytes``        Allocation size in bytes.
``count``           Number of elements.
``syclDevice``      See :ref:`device`.
``syclQueue``       See :ref:`queue`.
``syclContext``     See :ref:`context`.
``kind``            Kind of USM allocation.
``propList``        Optional property list.
==================  ===

Memory deallocation functions
=============================

==============
``sycl::free``
==============

::

   void sycl::free(void* ptr, const sycl::context& syclContext);

   void sycl::free(void* ptr, const sycl::queue& syclQueue);

Frees an allocation. The memory pointed to by ``ptr`` must have been
allocated using one of the USM allocation routines. ``syclContext``
must be the same ``sycl::context`` that was used to allocate the memory.
The memory is freed without waiting for commands operating on
it to be completed. If commands that use this memory are
in-progress or are enqueued the behavior is undefined.
In the second form the context is automatically extracted from the
``syclQueue`` that is passed in, as a convenience.

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
