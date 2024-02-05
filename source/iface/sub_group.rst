..
  Copyright 2023 The Khronos Group Inc.
  SPDX-License-Identifier: CC-BY-4.0

.. _sub_group:

*******************
``sycl::sub_group``
*******************

::

   class sub_group;

The ``sub_group`` class encapsulates all functionality required to
represent a particular sub-group within a parallel execution.
It is not user-constructible.

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

.. seealso:: |SYCL_SPEC_SUB_GROUP|

================
Member functions
================

``get_group_id``
================

::

  id<Dimensions> get_group_id() const

Return an id representing the index of the sub-group within the work-group.
Since the work-items that compose a sub-group are chosen in an
implementation defined way, the returned sub-group id cannot be used to
identify a particular work-item in the global ``nd-range``. Rather, the
returned sub-group id is merely an abstract identifier of
the sub-group containing this work-item.

``get_local_id``
================

::

  id<1> get_local_id() const

Return a SYCL ``id`` representing the calling work-item’s
position within the sub-group.

``get_local_range``
===================

::

  range<1> get_local_range() const

Return a ``range`` representing the size of the sub-group. This size may
be less than the value returned by ``get_max_local_range()``,
depending on the position of the sub-group within its parent work-group
and the manner in which sub-groups are constructed by the implementation.

``get_group_range``
===================

::

  range<1> get_group_range() const

Return a ``range`` representing the number of
sub-groups in the work-group.

``get_max_local_range``
=======================

::

  range<1> get_max_local_range() const

Return a ``range`` representing the maximum number of work-items
permitted in a sub-group for the executing kernel.
This value may have been chosen by the programmer via an attribute,
or chosen by the device compiler.

``get_group_linear_id``
=======================

::

  uint32_t get_group_linear_id() const

Return the same value as ``get_group_id()[0]``.

``get_group_linear_range``
==========================

::

  uint32_t get_group_linear_range() const

Return the same value as ``get_group_range()[0]``.

``get_local_linear_id``
=======================

::

  uint32_t get_local_linear_id() const

Return the same value as ``get_local_id()[0]``.

``get_local_linear_range``
==========================

::

  uint32_t get_local_linear_range() const

Return the same value as ``get_local_range()[0]``.

``leader``
==========

::

  bool leader() const

Return true for exactly one work-item in the sub-group, if the calling
work-item is the leader of the sub-group, and false for all other
work-items in the sub-group.

The leader of the sub-group is determined during construction of the
sub-group, and is invariant for the lifetime of the sub-group.
The leader of the sub-group is guaranteed to be the
work-item with a local id of 0.
