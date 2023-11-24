..
  Copyright 2020 The Khronos Group Inc.
  SPDX-License-Identifier: CC-BY-4.0

.. _nd_range:

******************
``sycl::nd_range``
******************

::

  template <int Dimensions = 1>
  class nd_range;

.. rubric:: Template parameters

================  ===
``Dimensions``    Number of dimensions of ``sycl::nd_range``.
================  ===

The ``sycl::nd_range`` defines the iteration domain of both
the work-groups and the overall dispatch.

To define this the ``sycl::nd_range`` comprises two
:ref:`range` parameters: the whole range over which
the kernel is to be executed, and the range of each work group.

The ``sycl::nd_range`` class template provides the :ref:`common-byval`.

.. seealso:: |SYCL_SPEC_ND_RANGE|

==============
(constructors)
==============

::

  nd_range<Dimensions>(
      sycl::range<Dimensions> globalSize,
      sycl::range<Dimensions> localSize,
      sycl::id<Dimensions> offset = sycl::id<Dimensions>());

Construct an ``sycl::nd_range`` from the local
and global constituent :ref:`range`.

Supplying the option offset is deprecated in SYCL 2020.
If the offset is not provided it will default to no offset.

.. rubric:: Parameters

==================  ===
``globalSize``      Dimensions of the entire index space.
``localSize``       Dimensions of the work group.
``offset``          Origin of the index space. [deprecated in SYCL 2020]
==================  ===


================
Member functions
================

``get_global_range``
====================

::

  sycl::range<Dimensions> get_global_range() const;

Return the constituent global :ref:`range`.

``get_local_range``
===================

::

  sycl::range<Dimensions> get_local_range() const;

Return the constituent local :ref:`range`.

``get_group_range``
===================

::

  sycl::range<dimensions> get_group_range() const;

Returns a :ref:`range` representing the number of
groups in each dimension.

This range would result from ``globalSize``/``localSize``
as provided on construction.


``get_offset``
==============

::

  sycl::id<Dimensions> get_offset() const;

Deprecated in SYCL 2020.

Returns a :ref:`id` defining the offset.
