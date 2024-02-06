..
  Copyright 2020 The Khronos Group Inc.
  SPDX-License-Identifier: CC-BY-4.0

.. _h_item:

****************
``sycl::h_item``
****************

::

  template <int Dimensions>
  class h_item;

The ``sycl::h_item`` class identifies an instance of a
``group::parallel_for_work_item`` function object executing at each
point in a local :ref:`range` passed to a
``parallel_for_work_item`` call or to the corresponding
``parallel_for_work_group`` call if no :ref:`range` is passed to the
``parallel_for_work_item`` call. It encapsulates enough information
to identify the work-item's local and global items according to the
information given to ``parallel_for_work_group`` (physical ids) as well
as the work-item's logical local items in the logical local range.
All returned item objects are offset-less. Instances of the
``sycl::h_item`` class are not user-constructible and
are passed by the runtime to each instance of the function object.

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


.. seealso:: |SYCL_SPEC_H_ITEM|

================
Member functions
================

``get_global``
==============

::

  sycl::item<Dimensions, false> get_global() const;

Return the constituent global item representing the work-item’s position
in the global iteration space as provided upon kernel invocation.


``get_local``
=============

::

  sycl::item<Dimensions, false> get_local() const;

Return the same value as ``get_logical_local()``.

``get_logical_local``
=====================

::

  sycl::item<Dimensions, false> get_logical_local() const;

Return the constituent element of the logical local work-item’s
position in the local iteration space as provided upon the invocation
of the ``sycl::group::parallel_for_work_item``.

If ``sycl::group::parallel_for_work_item`` was called without any logical
local range then the member function returns the physical local item.

A physical id can be computed from a logical id by getting the remainder
of the integer division of the logical id and the physical range:
``get_logical_local().get() % get_physical_local.get_range() ==
get_physical_local().get()``.

``get_physical_local``
======================

::

  sycl::item<Dimensions, false> get_physical_local() const;

Return the constituent element of the physical local work-item’s
position in the local iteration space as provided
(by the user or the runtime) upon the kernel invocation.

``get_global_range``
====================

::

  sycl::range<Dimensions> get_global_range() const;

Return the same value as ``get_global().get_range()``.


::

  size_t get_global_range(int dimension) const;

Return the same value as ``get_global().get_range(dimension)``.

``get_global_id``
=================

::

  sycl::id<Dimensions> get_global_id() const;

Return the same value as ``get_global().get_id()``.


::

  size_t get_global_id(int dimension) const;

Return the same value as ``get_global().get_id(dimension)``.

``get_local_range``
===================

::

  sycl::range<Dimensions> get_local_range() const;

Return the same value as ``get_local().get_range()``.


::

  size_t get_local_range(int dimension) const;

Return the same value as ``get_local().get_range(dimension)``.

``get_local_id``
================

::

  sycl::id<Dimensions> get_local_id() const;

Return the same value as ``get_local().get_id()``.


::

  size_t get_local_id(int dimension) const;

Return the same value as ``get_local().get_id(dimension)``.

``get_logical_local_range``
===========================

::

  sycl::range<Dimensions> get_logical_local_range() const;

Return the same value as ``get_logical_local().get_range()``.


::

  size_t get_logical_local_range(int dimension) const;

Return the same value as ``get_logical_local().get_range(dimension)``.

``get_logical_local_id``
========================

::

  sycl::id<Dimensions> get_logical_local_id() const;

Return the same value as ``get_logical_local().get_id()``.


::

  size_t get_logical_local_id(int dimension) const;

Return the same value as ``get_logical_local().get_id(dimension)``.

``get_physical_local_range``
============================

::

  sycl::range<Dimensions> get_physical_local_range() const;

Return the same value as ``get_physical_local().get_range()``.


::

  size_t get_physical_local_range(int dimension) const;

Return the same value as ``get_physical_local().get_range(dimension)``.

``get_physical_local_id``
=========================

::

  sycl::id<Dimensions> get_physical_local_id() const;

Return the same value as ``get_physical_local().get_id()``.


::

  size_t get_physical_local_id(int dimension) const;

Return the same value as ``get_physical_local().get_id(dimension)``.
