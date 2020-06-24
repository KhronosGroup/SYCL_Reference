=========
 nd_item
=========

::

   template <int dimensions = 1>
   class nd_item;
   
.. rubric:: Member functions

===================================  ==	    
get_global_id_
get_global_linear_id_
get_local_id_
get_local_linear_id_
get_group_
get_group_linear_id_
get_group_range_
get_global_range_
get_local_range_
get_offset_
get_nd_range_
barrier_
mem_fence_
async_work_group_copy_
wait_for_
===================================  ==	    

get_global_id
=============

::
   
  id<dimensions> get_global_id() const;
  size_t get_global_id(int dimension) const;

get_global_linear_id
====================

::
   
  size_t get_global_linear_id() const;

get_local_id
============

::
   
  id<dimensions> get_local_id() const;
  size_t get_local_id(int dimension) const;

get_local_linear_id
===================

::
   
  size_t get_local_linear_id() const;

get_group
=========

::
   
  group<dimensions> get_group() const;
  size_t get_group(int dimension) const;

get_group_linear_id
===================

::
   
  size_t get_group_linear_id() const;

get_group_range
===============

::
   
  range<dimensions> get_group_range() const;
  size_t get_group_range(int dimension) const;

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

get_offset
==========

::
   
  id<dimensions> get_offset() const;

get_nd_range
============

::
   
  nd_range<dimensions> get_nd_range() const;

barrier
=======

::
   
  void barrier(access::fence_space accessSpace =
    access::fence_space::global_and_local) const;

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

