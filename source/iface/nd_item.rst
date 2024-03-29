..
  Copyright 2024 The Khronos Group Inc.
  SPDX-License-Identifier: CC-BY-4.0

.. _nd_item:

*****************
``sycl::nd_item``
*****************

::

   template <int Dimensions = 1>
   class nd_item;

The ``sycl::nd_item`` class identifies an instance of the function object
executing at each point in an ``sycl::nd_range<int Dimensions>``
passed to a ``parallel_for`` call. It encapsulates enough
information to identify the work-item's local and global ids,
the work-group id and also provides access to the ``sycl::group``
and ``sycl::sub_group`` classes. Instances of the
``sycl::nd_item<int Dimensions>`` class are not user-constructible
and are passed by the runtime to each instance of the function object.

.. seealso:: |SYCL_SPEC_ND_ITEM|

================
Member functions
================

``get_global_id``
=================

::

  sycl::id<Dimensions> get_global_id() const;

Return the constituent global id representing the work-item’s
position in the global iteration space.


::

  size_t get_global_id(int dimension) const;

Return the constituent element of the global id representing
the work-item’s position in the ``sycl::nd_range`` in the given
``dimension``.

``get_global_linear_id``
========================

::

  size_t get_global_linear_id() const;

Return the constituent global id as a linear index value, representing
the work-item’s position in the global iteration space.
The linear address is calculated from the multi-dimensional index by
first subtracting the offset and then following |SYCL_SPEC_LINEARIZATION|.

``get_local_id``
================

::

  sycl::id<Dimensions> get_local_id() const;

Return the constituent local id representing the work-item’s
position within the current work-group.

::

  size_t get_local_id(int dimension) const;

Return the constituent element of the local id representing the
work-item’s position within the current
work-group in the given ``dimension``.

``get_local_linear_id``
========================

::

  size_t get_local_linear_id() const;

Return the constituent local id as a linear index value, representing
the work-item’s position within the current work-group.
The linear address is calculated from the multi-dimensional index
following |SYCL_SPEC_LINEARIZATION|.

``get_group``
=============

::

  sycl::group<Dimensions> get_group() const;

Return the constituent work-group, group representing the work-group's
position within the overall ``nd-range``.

::

  size_t get_group(int dimension) const;

Return the constituent element of the group ``sycl::id`` representing
the work-group’s position within the overall ``sycl::nd_range`` in
the given ``dimension``.

``get_sub_group``
=================

::

  sycl::sub_group get_sub_group() const;

Return a ``sycl::sub_group`` representing the sub-group
to which the work-item belongs.

``get_group_linear_id``
=======================

::

  size_t get_group_linear_id() const;

Return the group id as a linear index value. Calculating a linear address
from a multi-dimensional index follows |SYCL_SPEC_LINEARIZATION|.

``get_group_range``
===================

::

  sycl::range<Dimensions> get_group_range() const;

Returns the number of work-groups in the iteration space.

::

  size_t get_group_range(int dimension) const;

Return the number of work-groups for ``dimension`` in
the iteration space.

``get_global_range``
====================

::

  sycl::range<Dimensions> get_global_range() const;

Returns a ``sycl::range`` representing the dimensions
of the global iteration space.


::

  size_t get_global_range(int dimension) const;

Return the same value as ``get_global_range().get(dimension)``.

``get_local_range``
===================

::

  sycl::range<Dimensions> get_local_range() const;

Returns a ``sycl::range`` representing the dimensions
of the current work-group.


::

  size_t get_local_range(int dimension) const;

Return the same value as ``get_local_range().get(dimension)``.

``get_offset``
==============

::

  sycl::id<Dimensions> get_offset() const;
    // Deprecated in SYCL 2020.

Deprecated in SYCL 2020.

Returns an id representing the n-dimensional offset
provided to the constructor of the ``sycl::nd_range``
and that is added by the runtime to the global id of
each work-item.

``get_nd_range``
================

::

  sycl::nd_range<Dimensions> get_nd_range() const;

Returns the ``sycl::nd_range`` of the current execution.

``async_work_group_copy``
=========================

::

  template <typename DataT>
  sycl::device_event async_work_group_copy(sycl::local_ptr<DataT> dest,
                                           sycl::global_ptr<DataT> src,
                                           size_t numElements) const;

  template <typename DataT>
  sycl::device_event async_work_group_copy(sycl::global_ptr<DataT> dest,
                                           sycl::local_ptr<DataT> src,
                                           size_t numElements) const;

  template <typename DataT>
  sycl::device_event async_work_group_copy(sycl::local_ptr<DataT> dest,
                                           sycl::global_ptr<DataT> src,
                                           size_t numElements, size_t srcStride) const;

  template <typename DataT>
  sycl::device_event async_work_group_copy(sycl::global_ptr<DataT> dest,
                                           sycl::local_ptr<DataT> src,
                                           size_t numElements, size_t destStride) const;

All four ``async_work_group_copy`` functions listed above are deprecated
in SYCL 2020. Has the same effect as the overload taking
``sycl::decorated_local_ptr`` and ``sycl::decorated_global_ptr``
except that the ``dest`` and ``src`` parameters are
``sycl::multi_ptr`` with ``sycl::access::decorated::legacy``.

::

  template <typename DestDataT, typename SrcDataT>
  sycl::device_event async_work_group_copy(sycl::decorated_global_ptr<DestDataT> dest,
                                           sycl::decorated_local_ptr<SrcDataT> src,
                                           size_t numElements) const;

  template <typename DestDataT, typename SrcDataT>
  sycl::device_event async_work_group_copy(sycl::decorated_local_ptr<DestDataT> dest,
                                           sycl::decorated_global_ptr<SrcDataT> src,
                                           size_t numElements, size_t srcStride) const;

  template <typename DestDataT, SrcDataT>
  sycl::device_event async_work_group_copy(sycl::decorated_global_ptr<DestDataT> dest,
                                           sycl::decorated_local_ptr<SrcDataT> src,
                                           size_t numElements, size_t destStride) const;

All three functions above are available only when:
``(std::is_same_v<DestDataT, std::remove_const_t<SrcDataT>> == true)``

Permitted types for ``DataT`` are all scalar and vector types.
Asynchronously copies a number of elements specified by
``numElements`` from the source pointer ``src`` to destination pointer
``dest`` with a destination stride specified by ``destStride``
and returns a ``sycl::device_event`` which can be used to wait
on the completion of the copy.

``wait_for``
============

::

  template <typename... EventTN> void wait_for(EventTN... events) const;

Permitted type for ``EventTN`` is ``sycl::device_event``. Waits for the
asynchronous operations associated with each
``sycl::device_event`` to complete.
