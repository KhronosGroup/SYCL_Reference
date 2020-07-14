.. rst-class:: api-class
	       
.. _nd_item:

=========
 nd_item
=========

::

   template <int dimensions = 1>
   class nd_item;
   
The ``nd_item`` describes the location of a point in an
:ref:`nd_range`.

An ``nd_item`` is typically passed to a kernel function in a
:ref:`handler-parallel_for`. It addition to containing the ``id`` of
the work item in the work group and global space, the ``nd_item`` also
contains the :ref:`nd_range` defining the index space.

.. member-toc::

get_global_id
=============

::
   
  id<dimensions> get_global_id() const;
  size_t get_global_id(int dimension) const;

Returns global :ref:`id` for the requested dimensions.

get_global_linear_id
====================

::
   
  size_t get_global_linear_id() const;

Returns global id mapped to a linear space.

get_local_id
============

::
   
  id<dimensions> get_local_id() const;
  size_t get_local_id(int dimension) const;

Returns id for the point in the work group.

get_local_linear_id
===================

::
   
  size_t get_local_linear_id() const;

Returns linear id for point in the work group.

get_group
=========

::
   
  group<dimensions> get_group() const;
  size_t get_group(int dimension) const;

Returns :ref:`group` associated with the item.

get_group_linear_id
===================

::
   
  size_t get_group_linear_id() const;

Returns linear id for group in workspace.

get_group_range
===============

::
   
  range<dimensions> get_group_range() const;
  size_t get_group_range(int dimension) const;

Returns the number of groups in every dimension.

get_global_range
================

::
   
  range<dimensions> get_global_range() const;
  size_t get_global_range(int dimension) const;

Returns the :ref:`range` of the index space.

get_local_range
===============

::
   
  range<dimensions> get_local_range() const;
  size_t get_local_range(int dimension) const;

Returns the position of the work item in the work group.

get_offset
==========

::
   
  id<dimensions> get_offset() const;

Returns the offset provided to the :ref:`handler-parallel_for`.

get_nd_range
============

::
   
  nd_range<dimensions> get_nd_range() const;

Returns the :ref:`nd_range` provided to the :ref:`handler-parallel_for`.

barrier
=======

::
   
  void barrier(access::fence_space accessSpace =
    access::fence_space::global_and_local) const;

Executes a work group barrier.


mem_fence
=========

::
   
  template <access::mode accessMode = access::mode::read_write>
  void mem_fence(access::fence_space accessSpace =
    access::fence_space::global_and_local) const;

Executes a work group memory fence.

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

Copies elements from a source local to the destination asynchronously.

Returns an event that indicates when the operation has completed.

wait_for
========

::
   
  template <typename... eventTN>
  void wait_for(eventTN... events) const;

Wait for asynchronous events to complete.
