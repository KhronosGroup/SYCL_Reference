..
  Copyright 2020 The Khronos Group Inc.
  SPDX-License-Identifier: CC-BY-4.0

====================
sycl::private_memory
====================

::

   template <typename T, int Dimensions = 1>
   class private_memory;
   
.. seealso:: |SYCL_SPEC_PRIVATE_MEMORY|

(constructors)
==============

::

  private_memory(const sycl::group<Dimensions> &);

(operators)
===========

::

  T &operator()(const sycl::h_item<Dimensions> &id);
