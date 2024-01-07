..
  Copyright 2023 The Khronos Group Inc.
  SPDX-License-Identifier: CC-BY-4.0

.. _group-algorithms-library:

************************
Group algorithms library
************************

SYCL provides an algorithms library based on the functions
described in Section 28 of the C++17 specification. The first
argument to each function is a :ref:`group`, and data ranges
can be described using pointers, iterators or instances of the
:ref:`multi_ptr` class. The functions defined in this section
are free functions available in the ``sycl`` namespace.

Any restrictions from the standard algorithms library apply.
Some of the functions in the SYCL algorithms library introduce
additional restrictions in order to maximize portability across
different devices and to minimize the chances of encountering
unexpected behavior.

All algorithms are supported for the fundamental scalar types
supported by SYCL (see |SYCL_SPEC_SUPP_TYPES|) and instances
of the SYCL :ref:`vec` and :ref:`marray` classes.

The group argument to a SYCL algorithm denotes that it should
be performed collaboratively by the work-items in the specified
group. All algorithms act as :ref:`group functions <group-functions>`,
inheriting all restrictions of group functions. Unless the description
of a function says otherwise, how the elements of a range are
processed by the work-items in a group is undefined.

SYCL provides separate functions for algorithms which use the
work-items in a group to execute an operation over a range of
iterators and algorithms which are applied to data held
directly by the work-items in a group.

.. seealso:: |SYCL_SPEC_ALGORITHMS|

======================================
``any_of``, ``all_of`` and ``none_of``
======================================

The ``std::any_of``, ``std::all_of`` and ``std::none_of``
functions from standard C++ test whether Boolean conditions
hold for any of, all of or none of the values in a range,
respectively.

SYCL provides two sets of similar algorithms:

1. ``sycl::joint_any_of``, ``sycl::joint_all_of`` and
   ``sycl::joint_none_of`` use the work-items in a group to
   execute the corresponding algorithm in parallel.
2. ``sycl::any_of_group``, ``sycl::all_of_group`` and
   ``sycl::none_of_group`` test Boolean conditions applied
   to data held directly by the work-items in a group.


``sycl::joint_any_of``
======================

::

  template <typename Group, typename Ptr, typename Predicate>
  bool joint_any_of(Group g, Ptr first, Ptr last, Predicate pred);

Available only if ``sycl::is_group_v<std::decay_t<Group>>`` is ``true`` 
and ``Ptr`` is a pointer.

``first`` and ``last`` must be the same for all work-items in group ``g``, 
and ``pred`` must be an immutable callable with the same type and state 
for all work-items in group ``g``.

Returns ``true`` if ``pred`` returns ``true`` when applied to the result of 
dereferencing any iterator in the range ``[first, last)``.


``sycl::any_of_group``
======================

.. rubric:: Overload 1

::

  template <typename Group, typename T, typename Predicate>
  bool any_of_group(Group g, T x, Predicate pred);

Available only if ``sycl::is_group_v<std::decay_t<Group>>`` is ``true``.

``pred`` must be an immutable callable with the same type and state for 
all work-items in group ``g``.

Returns ``true`` if ``pred(x)`` returns true for any work-item in group ``g``.

.. rubric:: Overload 2

::

  template <typename Group> 
  bool any_of_group(Group g, bool pred);

Available only if ``sycl::is_group_v<std::decay_t<Group>>`` is ``true``.

Returns ``true`` if ``pred`` is ``true`` for any work-item in group ``g``.

``sycl::joint_all_of``
======================

::

  plate <typename Group, typename Ptr, typename Predicate>
  bool joint_all_of(Group g, Ptr first, Ptr last, Predicate pred);

Available only if ``sycl::is_group_v<std::decay_t<Group>>`` is ``true`` 
and ``Ptr`` is a pointer.

``first`` and ``last`` must be the same for all work-items in group ``g``, 
and ``pred`` must be an immutable callable with the same type and state 
for all work-items in group ``g``.

Returns ``true`` if ``pred`` returns ``true`` when applied to the result 
of dereferencing all iterators in the range ``[first, last)``.

``sycl::all_of_group``
======================

.. rubric:: Overload 1

::

  template <typename Group, typename T, typename Predicate>
  bool all_of_group(Group g, T x, Predicate pred);

Available only if ``sycl::is_group_v<std::decay_t<Group>>`` is ``true``.

``pred`` must be an immutable callable with the same type and state for 
all work-items in group ``g``.

Returns ``true`` if ``pred(x)`` returns ``true`` for all work-items in group ``g``.

.. rubric:: Overload 2

::

  template <typename Group> 
  bool all_of_group(Group g, bool pred);

Available only if ``sycl::is_group_v<std::decay_t<Group>>`` is ``true``.

Returns ``true`` if ``pred`` is ``true`` for all work-items in group ``g``.

``sycl::joint_none_of``
=======================

::

  template <typename Group, typename Ptr, typename Predicate>
  bool joint_none_of(Group g, Ptr first, Ptr last, Predicate pred);

Available only if ``sycl::is_group_v<std::decay_t<Group>>`` is ``true`` 
and ``Ptr`` is a pointer.

``first`` and ``last`` must be the same for all work-items in group ``g``, 
and ``pred`` must be an immutable callable with the same type and state 
for all work-items in group ``g``.

Returns ``true`` if ``pred`` returns ``false`` when applied to the result 
of dereferencing all iterators in the range ``[first, last)``.

``sycl::none_of_group``
=======================

.. rubric:: Overload 1

::

  template <typename Group, typename T, typename Predicate>
  bool none_of_group(Group g, T x, Predicate pred);

Available only if ``sycl::is_group_v<std::decay_t<Group>>`` is ``true``.

``pred`` must be an immutable callable with the same type and state for 
all work-items in group ``g``.

Returns ``true`` if ``pred(x)`` returns ``false`` for all work-items in group ``g``.

.. rubric:: Overload 2

::

  template <typename Group> 
  bool none_of_group(Group g, bool pred);

Available only if ``sycl::is_group_v<std::decay_t<Group>>`` is ``true``.

Returns ``true`` if ``pred`` is ``false`` for all work-items in group ``g``.


==================================
``shift_left`` and ``shift_right``
==================================

The ``std::shift_left`` and ``std::shift_right`` functions from standard C++ 
move values in a range down (to the left) or up (to the right) respectively.

SYCL provides similar algorithms compatible with the sub_group class:
``sycl::shift_group_left`` and ``sycl::shift_group_right`` move values held 
by the work-items in a group directly to another work-item in group ``g``, 
by shifting values a fixed number of work-items to the left or right.

``sycl::shift_group_left``
==========================

::

  template <typename Group, typename T>
  T shift_group_left(Group g, T x, Group::linear_id_type delta = 1);

Available only if ``std::is_same_v<std::decay_t<Group>, sub_group>`` is 
``true`` and ``T`` is a trivially copyable type.

``delta`` must be the same for all work-items in the group.

Returns the value of ``x`` from the work-item whose group local id (:ref:`id`) 
is delta larger than that of the calling work-item. ``id + delta`` may be 
greater than or equal to the group's linear size, but the value returned in this 
case is unspecified.


``sycl::shift_group_right``
===========================

::

  template <typename Group, typename T>
  T shift_group_right(Group g, T x, Group::linear_id_type delta = 1);

Available only if ``std::is_same_v<std::decay_t<Group>, sub_group>`` is 
``true`` and ``T`` is a trivially copyable type.

``delta`` must be the same for all work-items in the group.

Returns the value of ``x`` from the work-item whose group local id (:ref:`id`) 
is delta smaller than that of the calling work-item. ``id - delta`` may be less 
than 0, but the value returned in this case is unspecified.

===========
``permute``
===========

SYCL provides an algorithm to permute the values held by work-items in a sub-group:
``sycl::permute_group_by_xor`` permutes values by exchanging values held by 
pairs of work-items identified by computing the bitwise exclusive OR of the 
work-item id and some fixed mask.

``sycl::permute_group_by_xor``
==============================

::

  template <typename Group, typename T>
  T permute_group_by_xor(Group g, T x, Group::linear_id_type mask);

Available only if ``std::is_same_v<std::decay_t<Group>, sub_group>`` is 
``true`` and ``T`` is a trivially copyable type.

``mask`` must be the same for all work-items in the group.

Returns the value of ``x`` from the work-item whose group local id (:ref:`id`) 
is equal to the bitwise exclusive OR of the calling work-item's group local id 
and ``mask``. The result of the exclusive OR may be greater than or equal to 
the group's linear size, but the value returned in this case is unspecified.

==========
``select``
==========

==========
``reduce``
==========

=========================================
``exclusive_scan`` and ``inclusive_scan``
=========================================

.. _reduce-example:

=======
Example
=======

.. literalinclude:: /examples/reduce-alg-lib.cpp
   :lines: 5-
   :linenos:
   :caption: Using the group algorithms library to perform a work-group reduce.

.. literalinclude:: /examples/reduce-alg-lib.out
   :lines: 5-
   :caption: Output.
