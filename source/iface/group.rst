..
  Copyright 2020 The Khronos Group Inc.
  SPDX-License-Identifier: CC-BY-4.0

.. _group:

===============
``sycl::group``
===============

::

   template <int Dimensions = 1>
   class group;

The ``group`` encapsulates all functionality required to represent
a particular work-group within a parallel execution.
It is not user-constructible.

The local range stored in the group class is provided either by the
programmer, when it is passed as an optional parameter to
``parallel_for_work_group``, or by the runtime system when it
selects the optimal work-group size. This allows the developer
to always know how many work-items are in each executing work-group,
even through the abstracted iteration range
of the ``parallel_for_work_item``.

.. warning::

  Based on developer and implementation feedback, the hierarchical
  data parallel kernel feature is undergoing improvements to better
  align with the frameworks and patterns prevalent in modern programming.

  As this is a key part of the SYCL API and we expect to make changes to
  it, we temporarily recommend that new codes refrain from using this
  feature until the new API is finished in a near-future version of the
  SYCL specification, when full use of the updated feature will be
  recommended for use in new code.

  Existing codes using this feature will of course be supported by
  conformant implementations of this specification.

.. seealso:: |SYCL_SPEC_GROUP|

================
Member functions
================

``get_group_id``
================

::

  id<Dimensions> get_group_id() const

Return an id representing the index of the work-group within the
global ``nd-range`` for every dimension. Since the work-items in
a work-group have a defined position within the global ``nd-range``,
the returned group id can be used along with the local id to
uniquely identify the work-item in the global ``nd-range``.

::

  size_t get_group_id(int dimension) const

Return the same value as ``get_group_id()[dimension]``.


``get_local_id``
================

::

  id<Dimensions> get_local_id() const

Return a SYCL ``id`` representing the calling work-item’s
position within the work-group.

It is undefined behavior for this member function to be invoked
from within a ``parallel_for_work_item`` context.

::

  size_t get_local_id(int dimension) const

Return the same value as ``get_local_id()[dimension]``.

It is undefined behavior for this member function to be invoked
from within a parallel_for_work_item context.

``get_local_range``
===================

::

  range<Dimensions> get_local_range() const

Return a SYCL ``range`` representing all dimensions
of the local range. This local range may have been
provided by the programmer, or chosen by the SYCL runtime.

::

  size_t get_local_range(int dimension) const

Return the same value as ``get_local_range()[dimension]``.

``get_group_range``
===================

::

  range<Dimensions> get_group_range() const

Return a ``range`` representing the number of work-groups
in the ``nd_range``.

::

  size_t get_group_range(int dimension) const

Return the same value as ``get_group_range()[dimension]``.

``operator[]``
==============

::

  size_t operator[](int dimension) const

Return the same value as ``get_group_id(dimension)``.

``get_max_local_range``
=======================

::

  range<Dimensions> get_max_local_range() const

Return a ``range`` representing the maximum number of
work-items in any work-group in the ``nd_range``.

``get_group_linear_id``
=======================

::

  size_t get_group_linear_id() const

Get a linearized version of the work-group id.
Calculating a linear work-group id from
a multi-dimensional index follows |SYCL_SPEC_LINEARIZATION|.

``get_group_linear_range``
==========================

::

  size_t get_group_linear_range() const

Return the total number of work-groups in the ``nd_range``.

``get_local_linear_id``
=======================

::

  size_t get_local_linear_id() const

Get a linearized version of the calling work-item’s local id.
Calculating a linear local id from a multi-dimensional
index follows |SYCL_SPEC_LINEARIZATION|.

It is undefined behavior for this member function to be
invoked from within a ``parallel_for_work_item`` context.

``get_local_linear_range``
==========================

::

  size_t get_local_linear_range() const

Return the total number of work-items in the work-group.

``leader``
==========

::

  bool leader() const

Return true for exactly one work-item in the work-group,
if the calling work-item is the leader of the work-group,
and false for all other work-items in the work-group.

The leader of the work-group is determined during construction
of the work-group, and is invariant for the lifetime of
the work-group. The leader of the work-group is guaranteed
to be the work-item with a local id of 0.

``parallel_for_work_item``
==========================

::

  template <typename WorkItemFunctionT>
  void parallel_for_work_item(const WorkItemFunctionT& func) const

Launch the work-items for this work-group.

``func`` is a function object type with a public member function
``void F::operator()(h_item<Dimensions>)``
representing the work-item computation.

This member function can only be invoked within a
``parallel_for_work_group`` context. It is undefined behavior
for this member function to be invoked from within the
``parallel_for_work_group`` form that does not define work-group
size, because then the number of work-items that should execute
the code is not defined. It is expected that this form of
``parallel_for_work_item`` is invoked within the
``parallel_for_work_group`` form that specifies
the size of a work-group.

::

  template <typename WorkItemFunctionT>
  void parallel_for_work_item(range<Dimensions> logicalRange,
                              const WorkItemFunctionT& func) const

Launch the work-items for this work-group using a logical local range.
The function object ``func`` is executed as if the kernel were invoked
with ``logicalRange`` as the local range. This new local range is
emulated and may not map one-to-one with the physical range.

``logicalRange`` is the new local range to be used. This range can be
smaller or larger than the one used to invoke the kernel. ``func`` is
a function object type with a public member function
``void F::operator()(h_item<Dimensions>)``
representing the work-item computation.

Note that the logical range does not need to be uniform across all
work-groups in a kernel. For example the logical range may depend on
a work-group varying query (e.g. ``group::get_linear_id``),
such that different work-groups in the same kernel invocation
execute different logical range sizes.

This member function can only be invoked within a
``parallel_for_work_group`` context.

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
``multi_ptr`` with ``access::decorated::legacy``.

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
