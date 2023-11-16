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
template parameter. For exaple, this is how to provide
user-defined allocator class to :ref:`buffer`:

::

  sycl::buffer<int, 1, UserDefinedAllocator<int>> b(d);



