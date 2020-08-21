..
  Copyright 2020 Intel Corporation

================
 private_memory
================

::

   template <typename T, int Dimensions = 1>
   class private_memory;
   
.. seealso:: |SYCL_SPEC_PRIVATE_MEMORY|

.. member-toc::

(constructors)
==============

::

  private_memory(const group<Dimensions> &);

(operators)
===========

::

  T &operator()(const h_item<Dimensions> &id);
