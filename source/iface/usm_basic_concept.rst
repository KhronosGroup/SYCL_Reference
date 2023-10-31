..
  Copyright 2020 The Khronos Group Inc.
  SPDX-License-Identifier: CC-BY-4.0

.. _malloc_device:

********************
``malloc`` Functions
********************

=======================
``sycl::malloc_device``
=======================

::

   void* sycl::malloc_device(size_t numBytes,
                             const device& syclDevice,
                             const context& syclContext,
                             const property_list &propList = {})
   template <typename T>
   T* sycl::malloc_device(size_t count,
                          const device& syclDevice,
                          const context& syclContext,
                          const property_list &propList = {})
   void* sycl::malloc_device(size_t numBytes,
                             const queue& syclQueue,
                             const property_list &propList = {})
   template <typename T>
   T* sycl::malloc_device(size_t count,
                          const queue& syclQueue,
                          const property_list &propList = {})
   void* sycl::aligned_alloc_device(size_t alignment,
                                    size_t numBytes,
                                    const device& syclDevice,
                                    const context& syclContext,
                                    const property_list &propList = {})
   template <typename T>
   T* sycl::aligned_alloc_device(size_t alignment,
                                 size_t count,
                                 const device& syclDevice,
                                 const context& syclContext,
                                 const property_list &propList = {})


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

Returns a pointer to the newly allocated memory on the specified
device on success. This memory is not accessible on the host. Memory
allocated by :ref:`sycl::malloc_device <malloc_device>` must be
deallocated with :ref:`sycl::free <sycl-free>` to avoid memory
leaks. If ``ctxt`` is a host context, it should behave as if calling
:ref:`sycl::malloc_host <malloc_host>`. On failure, returns
``nullptr``.

The host may not directly reference the memory, but can read and write
the memory with :ref:`queue` member functions (:ref:`queue-memset`,
:ref:`queue-memcpy`, :ref:`queue-fill`) or :ref:`handler` member
functions (:ref:`handler-memset`, :ref:`handler-memcpy`, and
:ref:`handler-fill`).

See :ref:`event-elapsed-time` for usage.

.. seealso:: `SYCL Specification <https://www.khronos.org/registry/SYCL/specs/sycl-2020/html/sycl-2020.html#_device_allocation_functions>`__

.. _malloc_host:

=====================
``sycl::malloc_host``
=====================

::

   void* sycl::malloc_host(size_t numBytes,
                           const context& syclContext,
                           const property_list &propList = {})
   template <typename T>
   T* sycl::malloc_host(size_t count,
                        const context& syclContext,
                        const property_list &propList = {})
   void* sycl::malloc_host(size_t numBytes,
                           const queue& syclQueue,
                           const property_list &propList = {})
   template <typename T>
   T* sycl::malloc_host(size_t count,
                        const queue& syclQueue,
                        const property_list &propList = {})
   void* sycl::aligned_alloc_host(size_t alignment,
                                  size_t numBytes,
                                  const context& syclContext,
                                  const property_list &propList = {})
   template <typename T>
   T* sycl::aligned_alloc_host(size_t alignment,
                               size_t count,
                               const context& syclContext,
                               const property_list &propList = {})
   void* sycl::aligned_alloc_host(size_t alignment,
                                  size_t numBytes,
                                  const queue& syclQueue,
                                  const property_list &propList = {})
   template <typename T>
   void* sycl::aligned_alloc_host(size_t alignment,
                                  size_t count,
                                  const queue& syclQueue,
                                  const property_list &propList = {})

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

Returns a pointer to the newly allocated host memory on success. Host
and device may reference the memory.  Memory allocated by
:ref:`sycl::malloc_host <malloc_host>` must be deallocated with
:ref:`sycl::free <sycl-free>` to avoid memory leaks. On failure,
returns ``nullptr``.

.. seealso:: `SYCL Specification <https://www.khronos.org/registry/SYCL/specs/sycl-2020/html/sycl-2020.html#_host_allocation_functions>`__

.. _malloc_shared:

=======================
``sycl::malloc_shared``
=======================

::

   void* sycl::malloc_shared(size_t numBytes,
                             const device& syclDevice,
                             const context& syclContext,
                             const property_list &propList = {})
   template <typename T>
   T* sycl::malloc_shared(size_t count,
                          const device& syclDevice,
                          const context& syclContext,
                          const property_list &propList = {})
   void* sycl::malloc_shared(size_t numBytes,
                             const queue& syclQueue,
                             const property_list &propList = {})
   template <typename T>
   T* sycl::malloc_shared(size_t count,
                          const queue& syclQueue,
                          const property_list &propList = {})
   void* sycl::aligned_alloc_shared(size_t alignment,
                                    size_t numBytes,
                                    const device& syclDevice,
                                    const context& syclContext,
                                    const property_list &propList = {})
   template <typename T>
   T* sycl::aligned_alloc_shared(size_t alignment,
                                 size_t count,
                                 const device& syclDevice,
                                 const context& syclContext,
                                 const property_list &propList = {})
   void* sycl::aligned_alloc_shared(size_t alignment,
                                    size_t numBytes,
                                    const queue& syclQueue,
                                    const property_list &propList = {})
   template <typename T>
   T* sycl::aligned_alloc_shared(size_t alignment,
                                 size_t count,
                                 const queue& syclQueue,
                                 const property_list &propList = {})

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


Returns a pointer to the newly allocated shared memory on the
specified device on success. The SYCL runtime may migrate the data
between host and device to optimize access.  Memory allocated by
:ref:`sycl::malloc_shared <malloc_shared>` must be deallocated with
:ref:`sycl::free <sycl-free>` to avoid memory leaks. If ``ctxt`` is a
host context, should behave as if calling :ref:`sycl::malloc_host
<malloc_host>`. On failure, returns ``nullptr``.

.. seealso:: `SYCL Specification <https://www.khronos.org/registry/SYCL/specs/sycl-2020/html/sycl-2020.html#_shared_allocation_functions>`__

================
``sycl::malloc``
================

::

   void *malloc(size_t numBytes,
                const sycl::device& syclDevice,
                const sycl::context& syclContext,
                sycl::usm::alloc kind,
                const sycl::property_list &propList = {})
   template <typename T>
   T *malloc(size_t count,
             const sycl::device& syclDevice,
             const sycl::context& syclContext,
             sycl::usm::alloc kind,
             const sycl::property_list &propList = {})
   void *malloc(size_t numBytes,
                const sycl::queue& syclQueue,
                sycl::usm::alloc kind,
                const sycl::property_list &propList = {})
   template <typename T>
   T *malloc(size_t count,
             const sycl::queue& syclQueue,
             sycl::usm::alloc kind,
             const sycl::property_list &propList = {})
   void *aligned_alloc(size_t alignment,
                       size_t numBytes,
                       const sycl::device& syclDevice,
                       const sycl::context& syclContext,
                       sycl::usm::alloc kind,
                       const sycl::property_list &propList = {})
   template <typename T>
   T* aligned_alloc(size_t alignment,
                    size_t count,
                    const sycl::device& syclDevice,
                    const sycl::context& syclContext,
                    sycl::usm::alloc kind,
                    const sycl::property_list &propList = {})
   void *aligned_alloc(size_t alignment,
                       size_t numBytes,
                       const sycl::queue& syclQueue,
                       sycl::usm::alloc kind,
                       const sycl::property_list &propList = {})
   template <typename T>
   T* aligned_alloc(size_t alignment,
                    size_t count,
                    const sycl::queue& syclQueue,
                    sycl::usm::alloc kind,
                    const sycl::property_list &propList = {})

.. rubric:: Parameters

==================  ===
``alignment``       alignment of allocated data
``numBytes``        allocation size in bytes
``count``           number of elements
``syclDevice``      See :ref:`device`
``syclQueue``       See :ref:`queue`
``syclContext``     See :ref:`context`
``kind``            See `usm-alloc`
``propList``
==================  ===

.. seealso:: `SYCL Specification <https://www.khronos.org/registry/SYCL/specs/sycl-2020/html/sycl-2020.html#_parameterized_allocation_functions>`__



.. _sycl-free:

==============
``sycl::free``
==============

::

   void free(void* ptr, sycl::context& context);
   void free(void* ptr, sycl::queue& q);

Free memory allocated by `sycl::malloc_device`_, `sycl::malloc_host`_, or
`sycl::malloc_shared`_.

See :ref:`event-elapsed-time` for usage.

.. seealso:: `SYCL Specification <https://www.khronos.org/registry/SYCL/specs/sycl-2020/html/sycl-2020.html#_memory_deallocation_functions>`__
