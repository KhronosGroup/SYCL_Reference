..
  Copyright 2024 The Khronos Group Inc.
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
For allocations greater than size zero, when successful
it is guaranteed to return non-``nullptr`` and new memory
positions every call.

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
    - It is the default allocator used by the runtime for the SYCL :ref:`unsampled_image`
      and :ref:`sampled_image` classes when no allocator is provided by the user.

      The ``sycl::image_allocator`` is required to allocate in elements of ``std::byte``.


.. _host_memory_sharing:

=========================================================
Sharing host memory with the SYCL data management classes
=========================================================

In order to allow the SYCL runtime to do memory management
and allow for data dependencies, there are :ref:`buffer`
and :ref:`image <iface-images>` classes defined.

The default behavior for them is that if a “raw” pointer
is given during the construction of the data management
class, then full ownership to use it is given to the SYCL
runtime until the destruction of the SYCL object.

Below you can find details on sharing or explicitly not
sharing host memory with the SYCL data classes. The same
rules apply to :ref:`images <iface-images>` as well.

.. seealso:: |SYCL_SPEC_HOST_MEM_SHARING|


Default behavior
================

When using a :ref:`buffer`, the ownership of a pointer
passed to the constructor of the class is, by default,
passed to SYCL runtime, and that pointer cannot be used
on the host side until the :ref:`buffer` or
:ref:`image <iface-images>` is destroyed.

A SYCL application can access the contents of the memory
managed by a SYCL buffer by using a :ref:`host_accessor`.
However, there is no guarantee that the
host accessor synchronizes with the original host
address used in its constructor.

The pointer passed in is the one used to copy data back
to the host, if needed, before buffer destruction.
The memory pointed to by the host pointer will not be
deallocated by the runtime, and the data is copied back
from the device to the host through the host pointer
if there is a need for it.


SYCL ownership of the host memory
=================================

In the case where there is host memory to be used for
initialization of data but there is no intention of using
that host memory after the :ref:`buffer` is destroyed,
then the :ref:`buffer` can take full ownership of that
host memory.

When a :ref:`buffer` owns the host pointer there is no copy back,
by default. To create this situation, the SYCL application may pass
a unique pointer to the host data, which will be then used by the
runtime internally to initialize the data in the device.

For example, the following could be used:

::

  {
    auto ptr = std::make_unique<int>(-1234);
    buffer<int, 1> b { std::move(ptr), range { 1 } };
    // ptr is not valid anymore.
    // There is nowhere to copy data back
  }

However, optionally the ``sycl::buffer::set_final_data()`` can be
set to an output iterator (including a “raw” pointer) or to a
``std::weak_ptr`` to enable copying data back, to another host memory
address that is going to be valid after :ref:`buffer` destruction.

::

  {
    auto ptr = std::make_unique<int>(-42);
    buffer<int, 1> b { std::move(ptr), range { 1 } };
    // ptr is not valid anymore.
    // There is nowhere to copy data back.
    // To get copy back, a location can be specified:
    b.set_final_data(std::weak_ptr<int> { .... })
  }


Shared SYCL ownership of the host memory
========================================

When an instance of ``std::shared_ptr`` is passed to the
:ref:`buffer` constructor, then the :ref:`buffer` object
and the developer's application share the memory region.

Rules of shared ownership:

1. If the ``std::shared_ptr`` is not empty, the contents of the
   referenced memory are used to initialize the :ref:`buffer`.

   If the ``std::shared_ptr`` is empty, then the :ref:`buffer`
   is created with uninitialized memory.

2. If the ``std::shared_ptr`` is still used on the application's
   side then the data will be copied back from the :ref:`buffer`
   or :ref:`image <iface-images>` and will be available to the
   application after the :ref:`buffer` or
   :ref:`image <iface-images>` object is destroyed.

3. When the :ref:`buffer` is destroyed and the data have
   potentially been updated, if the number of copies of
   the ``std::shared_ptr`` outside the runtime is 0,
   there is no user-side shared pointer to read the data.

   Therefore the data is not copied out, and the :ref:`buffer`
   destructor does not need to wait for the data processes
   to be finished, as the outcome is not needed on the
   application's side.

Example of such behavior:

::

  {
    std::shared_ptr<int> ptr { data };
    {
      buffer<int, 1> b { ptr, range<2>{ 10, 10 } };
      // update the data
      [...]
    } // Data is copied back because there is an user side shared_ptr
  }

::

  {
    std::shared_ptr<int> ptr { data };
    {
      buffer<int, 1> b { ptr, range<2>{ 10, 10 } };
      // update the data
      [...]
      ptr.reset();
    } // Data is not copied back, there is no user side shared_ptr.
  }

This behavior can be overridden using the
``sycl::buffer::set_final_data()`` member function of the
:ref:`buffer` class, which will by any means force the
:ref:`buffer` destructor to wait until the data is copied to
wherever the ``set_final_data()`` member function has put the
data (or not wait nor copy if set final data is ``nullptr``).
