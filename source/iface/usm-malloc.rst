..
  Copyright 2020 Intel Corporation

.. _malloc_device:

===============
 malloc_device
===============

|2020|

::

   void* malloc_device(size_t num_bytes,
                             const device& dev,
                             const context& ctxt);
   void* aligned_alloc_device(size_t alignment,
                                    size_t num_bytes,
                                    const device& dev,
                                    const context& ctxt);
   template <typename T>
   T* malloc_device(size_t count,
                          const device& dev,
                          const context& ctxt);
   template <typename T>
   T* aligned_alloc_device(size_d alignment,
                                 size_t count,
                                 const device& dev,
                                 const context& ctxt);


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

   void* malloc_host(size_t num_bytes, const context& ctxt);
   template <typename T>
   void* aligned_alloc_host(size_t alignment, size_t num_bytes, const context& ctxt);
   T* malloc_host(size_t count, const context& ctxt);
   T* aligned_alloc_host(size_t alignment, size_t count, const context& ctxt);

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

   void* malloc_shared(size_t num_bytes,
                             const device& dev,
                             const context& ctxt);
   void* aligned_alloc_ahared(size_t alignment,
                                 size_t num_bytes,
                                 const device& dev,
                                 const context& ctxt);
   template <typename T>
   T* malloc_shared(size_t count,
                          const device& dev,
                          const context& ctxt);
   template <typename T>
   T* aligned_alloc_ahared(size_t alignment,
                              size_t count,
                              const device& dev,
                              const context& ctxt);

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

   void free(void* ptr, context& context);

Free memory allocated by `malloc_device`_, `malloc_host`_, or
`malloc_shared`_.
   
.. seealso:: |SYCL_SPEC_FREE|
