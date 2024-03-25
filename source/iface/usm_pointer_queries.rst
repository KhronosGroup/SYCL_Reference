..
  Copyright 2024 The Khronos Group Inc.
  SPDX-License-Identifier: CC-BY-4.0

.. _usm-pointer_queries:

*******************
USM Pointer Queries
*******************

Since USM pointers look like raw C++ pointers, users
cannot deduce what kind of USM allocation a given
pointer may be from by examining its type.

Two functions are defined that let users query the
type of a USM allocation and, if applicable, the
:ref:`device` on which it was allocated.

.. note::

  These query functions are only supported on the host.

.. seealso:: |SYCL_USM_POINTER_QUERIES|

=======================
Pointer query functions
=======================

``sycl::get_pointer_type``
==========================

::

  sycl::usm::alloc get_pointer_type(const void* ptr, const sycl::context& syclContext);

Returns the USM allocation type for ``ptr`` if ``ptr`` falls
inside a valid USM allocation for the context ``syclContext``.

Returns ``sycl::usm::alloc::unknown`` if ``ptr`` does
not point within a valid USM allocation from ``syclContext``.


``sycl::get_pointer_device``
============================

::

  sycl::device get_pointer_device(const void* ptr, const sycl::context& syclContext);

Returns the :ref:`device` associated with the USM allocation.

If ``ptr`` points within a device USM allocation or
a shared USM allocation for the context ``syclContext``,
returns the same device that was passed when allocating the memory.

If ``ptr`` points within a host USM allocation for the
context ``syclContext``, returns the first device in ``syclContext``.

.. rubric:: Exceptions

``sycl::errc::invalid``
  If ``ptr`` does not point within a valid
  USM allocation from ``syclContext``.
