..
  Copyright 2020 The Khronos Group Inc.
  SPDX-License-Identifier: CC-BY-4.0

.. rst-class:: api-class
	       
.. _h_item:

============
sycl::h_item
============

::

   template <int dimensions>
   class h_item;

.. seealso:: |SYCL_SPEC_H_ITEM|

get_global
==========

::

  sycl::item<dimensions, false> get_global() const;

get_local
=========

::
   
  sycl::item<dimensions, false> get_local() const;

get_logical_local
=================

::

  sycl::item<dimensions, false> get_logical_local() const;

get_physical_local
==================

::
   
  sycl::item<dimensions, false> get_physical_local() const;

get_global_range
================

::
   
  sycl::range<dimensions> get_global_range() const;
  size_t get_global_range(int dimension) const;

get_global_id
=============

::
   
  id<dimensions> get_global_id() const;
  size_t get_global_id(int dimension) const;

get_local_range
===============

::
   
  sycl::range<dimensions> get_local_range() const;
  size_t get_local_range(int dimension) const;

get_local_id
============

::
   
  sycl::id<dimensions> get_local_id() const;
  size_t get_local_id(int dimension) const;

get_logical_local_range
=======================

::
   
  sycl::range<dimensions> get_logical_local_range() const;
  size_t get_logical_local_range(int dimension) const;

get_logical_local_id
====================

::
   
  sycl::id<dimensions> get_logical_local_id() const;
  size_t get_logical_local_id(int dimension) const;

get_physical_local_range
========================

::
   
  sycl::range<dimensions> get_physical_local_range() const;
  size_t get_physical_local_range(int dimension) const;

get_physical_local_id
=====================

::
   
  sycl::id<dimensions> get_physical_local_id() const;
  size_t get_physical_local_id(int dimension) const;

