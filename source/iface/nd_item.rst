..
  Copyright 2020 The Khronos Group Inc.
  SPDX-License-Identifier: CC-BY-4.0

.. _nd_item:

=================
``sycl::nd_item``
=================

::

   template <int Dimensions = 1>
   class nd_item;

The ``nd_item`` identifies an instance of the function object
executing at each point in an ``nd_range<int Dimensions>``
passed to a ``parallel_for`` call. It encapsulates enough
information to identify the work-item's local and global ids,
the work-group id and also provides access to the ``group``
and ``sub_group`` classes. Instances of the
``nd_item<int Dimensions>`` class are not user-constructible
and are passed by the runtime to each instance of the function object.

.. seealso:: |SYCL_SPEC_ND_ITEM|

================
Member functions
================

``get_global_id``
=================

::

  id<Dimensions> get_global_id() const

Return the constituent global id representing the work-item’s
position in the global iteration space.


::

  size_t get_global_id(int dimension) const

Return the constituent element of the global id representing
the work-item’s position in the ``nd-range`` in the given ``Dimension``.

``get_global_linear_id``
========================

::

  size_t get_global_linear_id() const

Return the constituent global id as a linear index value, representing
the work-item’s position in the global iteration space.
The linear address is calculated from the multi-dimensional index by
first subtracting the offset and then following |SYCL_SPEC_LINEARIZATION|.

``get_local_id``
================

::

  id<Dimensions> get_local_id() const

Return the constituent local id representing the work-item’s
position within the current work-group.

::

  size_t get_local_id(int dimension) const

Return the constituent element of the local id representing the
work-item’s position within the current
work-group in the given ``Dimension``.

``get_local_linear_id``
========================

::

  size_t get_local_linear_id() const

Return the constituent local id as a linear index value, representing
the work-item’s position within the current work-group.
The linear address is calculated from the multi-dimensional index
following |SYCL_SPEC_LINEARIZATION|.

``get_group``
=============

::

  group<Dimensions> get_group() const

Return the constituent work-group, group representing the work-group's
position within the overall ``nd-range``.

::

  size_t get_group(int dimension) const

Return the constituent element of the group ``id`` representing
the work-group’s position within the overall
``nd_range`` in the given ``Dimension``.

``get_sub_group``
=================

::

  sub_group get_sub_group() const

Return a ``sub_group`` representing the sub-group
to which the work-item belongs.

``get_group_linear_id``
=======================

::

  size_t get_group_linear_id() const

Return the group id as a linear index value. Calculating a linear address
from a multi-dimensional index follows |SYCL_SPEC_LINEARIZATION|.

``get_group_range``
===================

::

  range<Dimensions> get_group_range() const

Returns the number of work-groups in the iteration space.

::

  size_t get_group_range(int dimension) const

Return the number of work-groups for ``Dimension`` in
the iteration space.

``get_global_range``
====================

::

  range<Dimensions> get_global_range() const

Returns a ``range`` representing the dimensions
of the global iteration space.


::

  size_t get_global_range(int dimension) const

Return the same value as ``get_global_range().get(dimension).``.

``get_local_range``
===================

::

  range<Dimensions> get_local_range() const

Returns a ``range`` representing the dimensions
of the current work-group.


::

  size_t get_local_range(int dimension) const

Return the same value as ``get_local_range().get(dimension)``.

``get_offset``
==============

::

  id<Dimensions> get_offset() const
    // Deprecated in SYCL 2020.

Deprecated in SYCL 2020. Returns an id representing the
n-dimensional offset provided to the constructor of the
``nd_range`` and that is added by the runtime to
the global id of each work-item.

``get_nd_range``
================

::

  nd_range<Dimensions> get_nd_range() const

Returns the ``nd_range`` of the current execution.

``async_work_group_copy``
=========================

::

  template <typename DataT>
  device_event async_work_group_copy(local_ptr<DataT> dest,
                                     global_ptr<DataT> src,
                                     size_t numElements) const

  template <typename DataT>
  device_event async_work_group_copy(global_ptr<DataT> dest,
                                     local_ptr<DataT> src,
                                     size_t numElements) const

  template <typename DataT>
  device_event async_work_group_copy(local_ptr<DataT> dest,
                                     global_ptr<DataT> src,
                                     size_t numElements, size_t srcStride) const

  template <typename DataT>
  device_event async_work_group_copy(global_ptr<DataT> dest,
                                     local_ptr<DataT> src,
                                     size_t numElements, size_t destStride) const

All four ``async_work_group_copy`` functions listed above are deprecated
in SYCL 2020. Has the same effect as the overload taking
``decorated_local_ptr`` and ``decorated_global_ptr``
except that the ``dest`` and ``src`` parameters are
``multi_ptr#s with [code]#access::decorated::legacy``.

::

  template <typename DestDataT, typename SrcDataT>
  device_event async_work_group_copy(decorated_global_ptr<DestDataT> dest,
                                     decorated_local_ptr<SrcDataT> src,
                                     size_t numElements) const

  template <typename DestDataT, typename SrcDataT>
  device_event async_work_group_copy(decorated_local_ptr<DestDataT> dest,
                                     decorated_global_ptr<SrcDataT> src,
                                     size_t numElements, size_t srcStride) const

  template <typename DestDataT, SrcDataT>
  device_event async_work_group_copy(decorated_global_ptr<DestDataT> dest,
                                     decorated_local_ptr<SrcDataT> src,
                                     size_t numElements, size_t destStride) const

All three functions above are available only when:
``(std::is_same_v<DestDataT, std::remove_const_t<SrcDataT>> == true)``

Permitted types for ``DataT`` are all scalar and vector types.
Asynchronously copies a number of elements specified by
``numElements`` from the source pointer ``src`` to destination pointer
``dest`` with a destination stride specified by ``destStride``
and returns a SYCL ``device_event`` which can be used to wait
on the completion of the copy.

``wait_for``
============

::

  template <typename... EventTN> void wait_for(EventTN... events) const

Permitted type for ``EventTN`` is ``device_event``. Waits for the
asynchronous operations associated with each
``device_event`` to complete.
