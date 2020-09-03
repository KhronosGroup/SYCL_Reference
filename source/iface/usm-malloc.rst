..
  Copyright 2020 Intel Corporation

.. _malloc_device:

===============
 malloc_device
===============

|2020|

::

   void* sycl::malloc_device(size_t num_bytes,
                             const sycl::device& dev,
                             const sycl::context& ctxt);
   void* sycl::aligned_alloc_device(size_t alignment,
                                    size_t num_bytes,
                                    const sycl::device& dev,
                                    const sycl::context& ctxt);
   template <typename T>
   T* sycl::malloc_device(size_t count,
                          const sycl::device& dev,
                          const sycl::context& ctxt);
   template <typename T>
   T* sycl::aligned_alloc_device(size_d alignment,
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

Returns a pointer to memory that resides on the device.

The host may not directly reference the memory, but can read and write
the memory with :ref:`queue` member functions (:ref:`queue-memset`,
:ref:`queue-memcpy`, :ref:`queue-fill`) or :ref:`handler` member
functions (:ref:`handler-memset`, :ref:`handler-memcpy`, and
:ref:`handler-fill`).

Deallocate with free_.

.. seealso:: |SYCL_SPEC_MALLOC_DEVICE|

=============
 malloc_host
=============

|2020|

::

   void* sycl::malloc_host(size_t num_bytes, const sycl::context& ctxt);
   template <typename T>
   void* sycl::aligned_alloc_host(size_t alignment, size_t num_bytes, const sycl::context& ctxt);
   T* sycl::malloc_host(size_t count, const sycl::context& ctxt);
   T* sycl::aligned_alloc_host(size_t alignment, size_t count, const sycl::context& ctxt);

.. rubric:: Parameters

==================  ===
alignment           alignment of allocated data
num_bytes           allocation size in bytes
count               number of elements
dev                 See :ref:`device`
ctxt                See :ref:`context`
==================  ===

Returns a pointer to memory that resides on the host.

Host and device may reference the memory.

Deallocate with free_.

.. seealso:: |SYCL_SPEC_MALLOC_HOST|

===============
 malloc_shared
===============

|2020|

::

   void* sycl::malloc_shared(size_t num_bytes,
                             const sycl::device& dev,
                             const sycl::context& ctxt);
   void* sycl::aligned_alloc_ahared(size_t alignment,
                                 size_t num_bytes,
                                 const sycl::device& dev,
                                 const sycl::context& ctxt);
   template <typename T>
   T* sycl::malloc_shared(size_t count,
                          const sycl::device& dev,
                          const sycl::context& ctxt);
   template <typename T>
   T* sycl::aligned_alloc_ahared(size_t alignment,
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

Returns a pointer to memory that may reside on host or device.

The SYCL runtime may migrate the data between host and device to
optimize access.

Deallocate with free_.

.. seealso:: |SYCL_SPEC_MALLOC_SHARED|

======
 free
======

|2020|

::

   void free(void* ptr, sycl::context& context);

Free memory allocated by `malloc_device`_, `malloc_host`_, or
`malloc_shared`_.
   
.. seealso:: |SYCL_SPEC_FREE|
