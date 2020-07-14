.. _group:

.. rst-class:: api-class
	       
=======
 group
=======

::

   template <int dimensions = 1>
   class group;

.. rubric:: Template parameters

===========  ===
dimensions
===========  ===

.. member-toc::

get_id
======

::

  id<dimensions> get_id() const;
  size_t get_id(int dimension) const;

get_global_range
================

::

  range<dimensions> get_global_range() const;
  size_t get_global_range(int dimension) const;

get_local_range
===============

::
   
  range<dimensions> get_local_range() const;
  size_t get_local_range(int dimension) const;

get_group_range
===============

::
   
  range<dimensions> get_group_range() const;
  size_t get_group_range(int dimension) const;


get_linear_id
=============

::
   
  size_t get_linear_id() const;

parallel_for_work_item
======================

::
   
  template<typename workItemFunctionT>
  void parallel_for_work_item(workItemFunctionT func) const;
  template<typename workItemFunctionT>
  void parallel_for_work_item(range<dimensions> logicalRange,
    workItemFunctionT func) const;

mem_fence
=========

::
   
  template <access::mode accessMode = access::mode::read_write>
  void mem_fence(access::fence_space accessSpace =
    access::fence_space::global_and_local) const;

async_work_group_copy
=====================

::
   
  template <typename dataT>
  device_event async_work_group_copy(local_ptr<dataT> dest,
    global_ptr<dataT> src, size_t numElements) const;
  template <typename dataT>
  device_event async_work_group_copy(global_ptr<dataT> dest,
    local_ptr<dataT> src, size_t numElements) const;
  template <typename dataT>
  device_event async_work_group_copy(local_ptr<dataT> dest,
    global_ptr<dataT> src, size_t numElements, size_t srcStride) const;
  template <typename dataT>
  device_event async_work_group_copy(global_ptr<dataT> dest,
    local_ptr<dataT> src, size_t numElements, size_t destStride) const;

wait_for
========

::
   
  template <typename... eventTN>
  void wait_for(eventTN... events) const;

operator[]
==========

::
   
  size_t operator[](int dimension) const;
