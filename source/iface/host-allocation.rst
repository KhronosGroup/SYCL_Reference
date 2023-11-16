..
  Copyright 2023 The Khronos Group Inc.
  SPDX-License-Identifier: CC-BY-4.0

***********************************
Host allocations and memory sharing
***********************************

.. _host-allocations:

================
Host allocations
================

A SYCL runtime may need to allocate temporary objects
on the host to handle some operations (such as copying
data from one context to another).

Allocation on the host is managed using an allocator
object, following the standard C++ allocator class
definition.

The default allocator for memory objects is
implementation-defined, but the user can supply
their own allocator class by passing it as
template parameter. For example, this is how to provide
user-defined allocator class to :ref:`buffer`:

::

  {
    sycl::buffer<int, 1, UserDefinedAllocator<int>> b(d);
  }

When an allocator returns a ``nullptr``, the runtime
cannot allocate data on the host. Note that in this case
the runtime will raise an error if it requires host memory
but it is not available (e.g when moving data across SYCL
backend contexts).

In some cases, the implementation may retain a copy of
the allocator object even after the buffer is destroyed.
For example, this can happen when the buffer object is
destroyed before commands using accessors to the buffer
have completed. Therefore, the application must be
prepared for calls to the allocator even after the buffer
is destroyed.

.. note::

  If the application needs to know when the implementation
  has destroyed all copies of the allocator, it can maintain
  a reference count within the allocator.

The definition of allocators extends the current functionality
of SYCL, ensuring that users can define allocator functions for
specific hardware or certain complex shared memory mechanisms,
and improves interoperability with STL-based libraries.

.. seealso:: |SYCL_SPEC_HOST_ALLOC|

Default allocators
==================

A default allocator is always defined by the implementation.
For allocations greater than size zero, it is guaranteed to
return non-``nullptr`` and new memory positions every call.

The default allocator for ``const`` buffers will remove the
constantness of the type (therefore, the default allocator
for a buffer of type ``const int`` will be an ``Allocator<int>``).
This implies that host accessors will not synchronize with the
pointer given by the user in the :ref:`buffer`/:ref:`image <iface-images>`
constructor, but will use the memory returned by the ``Allocator``
itself for that purpose.

The user can implement an allocator that returns the same address
as the one passed in the buffer constructor, but it is the
responsibility of the user to handle the potential race conditions.

The list of SYCL default allocators:

.. list-table::
  :header-rows: 1

  * - Allocator
    - Description
  * - ``template <class T> sycl::buffer_allocator``
    - It is the default :ref:`buffer` allocator used by the runtime,
      when no allocator is defined by the user.

      Meets the C++ named requirement Allocator.

      A buffer of data type ``const T`` uses ``buffer_allocator<T>``
      by default.
  * - ``sycl::image_allocator``
    - It is the default allocator used by the runtime for the SYCL `unsampled_image`
      and `sampled_image` classes when no allocator is provided by the user.

      The ``sycl::image_allocator`` is required to allocate in elements of ``std::byte``.

.. TODO: Add references when images is complete
