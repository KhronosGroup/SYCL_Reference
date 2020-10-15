..
  Copyright 2020 The Khronos Group Inc.
  SPDX-License-Identifier: CC-BY-4.0

.. _malloc_device:

===================
sycl::malloc_device
===================

|2020|

::

   void* malloc_device(size_t num_bytes,
                       const queue& q);
   void* aligned_alloc_device(size_t alignment,
                              size_t num_bytes,
                              const queue& q);
   template <typename T>
   T* malloc_device(size_t count,
                    const queue& q);
   template <typename T>
   T* aligned_alloc_device(size_d alignment,
                           size_t count,
                           const queue& q);

   void* malloc_device(size_t num_bytes,
                       const sycl::device& dev,
                       const sycl::context& ctxt);
   void* aligned_alloc_device(size_t alignment,
                              size_t num_bytes,
                              const sycl::device& dev,
                              const sycl::context& ctxt);
   template <typename T>
   T* malloc_device(size_t count,
                    const sycl::device& dev,
                    const sycl::context& ctxt);
   template <typename T>
   T* aligned_alloc_device(size_d alignment,
                           size_t count,
                           const sycl::device& dev,
                           const sycl::context& ctxt);

.. rubric:: Parameters

==================  ===
alignment           alignment of allocated data
num_bytes           allocation size in bytes
count               number of elements
dev                 See :ref:`device`
q                   See :ref:`queue`
ctxt                See :ref:`context`
==================  ===

Returns a pointer to the newly allocated memory on the specified
device on success. This memory is not accessible on the host. Memory
allocated by malloc_device must be deallocated with :ref:`sycl::free
<sycl-free>` to avoid memory leaks. If ctxt is a host context, it
should behave as if calling malloc_host. On failure, returns nullptr.

The host may not directly reference the memory, but can read and write
the memory with :ref:`queue` member functions (:ref:`queue-memset`,
:ref:`queue-memcpy`, :ref:`queue-fill`) or :ref:`handler` member
functions (:ref:`handler-memset`, :ref:`handler-memcpy`, and
:ref:`handler-fill`).

See :ref:`event-elapsed-time` for usage.

.. seealso:: |SYCL_SPEC_MALLOC_DEVICE|

=================
sycl::malloc_host
=================

|2020|

::

   void* malloc_host(size_t num_bytes,
                     const sycl::queue& q);
   void* aligned_alloc_host(size_t alignment,
                            size_t num_bytes,
                            const sycl::queue& q);
   template <typename T>
   T* malloc_host(size_t count,
                  const sycl::queue& q);
   template <typename T>
   T* aligned_alloc_host(size_d alignment,
                         size_t count,
                         const sycl::queue& q);

   void* malloc_host(size_t num_bytes,
                     const sycl::device& dev,
                     const sycl::context& ctxt);
   void* aligned_alloc_host(size_t alignment,
                            size_t num_bytes,
                            const sycl::device& dev,
                            const sycl::context& ctxt);
   template <typename T>
   T* malloc_host(size_t count,
                  const sycl::device& dev,
                  const sycl::context& ctxt);
   template <typename T>
   T* aligned_alloc_host(size_d alignment,
                         size_t count,
                         const sycl::device& dev,
                         const sycl::context& ctxt);

.. rubric:: Parameters

==================  ===
alignment           alignment of allocated data
num_bytes           allocation size in bytes
count               number of elements
dev                 See :ref:`device`
ctxt                See :ref:`context`
==================  ===

Returns a pointer to the newly allocated host memory on success. Host
and device may reference the memory.  Memory allocated by malloc_host
must be deallocated with :ref:`sycl::free <sycl-free>` to avoid memory
leaks. On failure, returns nullptr.

.. seealso:: |SYCL_SPEC_MALLOC_HOST|

===================
sycl::malloc_shared
===================

|2020|

::

   void* malloc_shared(size_t num_bytes,
                       const queue& q);
   void* aligned_alloc_shared(size_t alignment,
                              size_t num_bytes,
                              const sycl::queue& q);
   template <typename T>
   T* malloc_shared(size_t count,
                    const sycl::queue& q);
   template <typename T>
   T* aligned_alloc_shared(size_d alignment,
                           size_t count,
                           const sycl::queue& q);

   void* malloc_shared(size_t num_bytes,
                       const sycl::device& dev,
                       const sycl::context& ctxt);
   void* aligned_alloc_shared(size_t alignment,
                              size_t num_bytes,
                              const sycl::device& dev,
                              const sycl::context& ctxt);
   template <typename T>
   T* malloc_shared(size_t count,
                    const sycl::device& dev,
                    const sycl::context& ctxt);
   template <typename T>
   T* aligned_alloc_shared(size_d alignment,
                           size_t count,
                           const sycl::device& dev,
                           const sycl::context& ctxt);

.. rubric:: Parameters

==================  ===
alignment           alignment of allocated data
num_bytes           allocation size in bytes
count               number of elements
dev                 See :ref:`device`
ctxt                See :ref:`context`
==================  ===


Returns a pointer to the newly allocated shared memory on the
specified device on success. The SYCL runtime may migrate the data
between host and device to optimize access.  Memory allocated by
malloc_shared must be deallocated with :ref:`sycl::free <sycl-free>`
to avoid memory leaks. If ctxt is a host context, should behave as if
calling malloc_host. On failure, returns nullptr.

.. seealso:: |SYCL_SPEC_MALLOC_SHARED|

.. _sycl-free:

==========
sycl::free
==========

|2020|

::

   void free(void* ptr, sycl::context& context);
   void free(void* ptr, sycl::queue& q);

Free memory allocated by `sycl::malloc_device`_, `sycl::malloc_host`_, or
`sycl::malloc_shared`_.
   
See :ref:`event-elapsed-time` for usage.

.. seealso:: |SYCL_SPEC_FREE|
