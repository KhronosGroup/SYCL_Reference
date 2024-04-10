..
  Copyright 2024 The Khronos Group Inc.
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

===================================
``any_of``, ``all_of``, ``none_of``
===================================

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

Returns ``true`` if ``pred(x)`` returns ``true`` for all work-items in
group ``g``.

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

Returns ``true`` if ``pred(x)`` returns ``false`` for all work-items
in group ``g``.

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
greater than or equal to the group's linear size, but the value returned
in this case is unspecified.


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

SYCL provides an algorithm to permute the values held by work-items in
a sub-group: ``sycl::permute_group_by_xor`` permutes values by exchanging
values held by pairs of work-items identified by computing the bitwise
exclusive OR of the work-item id and some fixed mask.

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

SYCL provides an algorithm to directly exchange the values held by
work-items in a sub-group:
``sycl::select_from_group`` allows work-items to obtain a copy of a value held
by any other work-item in group ``g``.

``sycl::select_from_group``
===========================

::

  template <typename Group, typename T>
  T select_from_group(Group g, T x, Group::id_type remote_local_id);

Available only if ``std::is_same_v<std::decay_t<Group>, sub_group>`` is
``true`` and ``T`` is a trivially copyable type.

Returns the value of ``x`` from the work-item with the group local id
(:ref:`id`) specified by ``remote_local_id``. The value of ``remote_local_id``
may be outside of the group, but the value returned in this case
is unspecified.

==========
``reduce``
==========

The ``std::reduce`` function from standard C++ combines the values
in a range in an unspecified order using a binary operator.

SYCL provides two similar algorithms that compute the same generalized sum as
defined by standard C++:

1. ``sycl::joint_reduce`` uses the work-items in a group to execute a
   reduce operation in parallel.
2. ``sycl::reduce_over_group`` combines values held directly by the
   work-items in a group.

The result of a call to these functions is non-deterministic if the binary
operator is not commutative and associative. Only the binary operators
defined in :ref:`function-objects` are supported by the reduce functions
in SYCL 2020, but the standard C++ syntax is used for forward compatibility
with future SYCL versions.


``joint_reduce``
================

.. rubric:: Overload 1

::

  template <typename Group, typename Ptr, typename BinaryOperation>
  std::iterator_traits<Ptr>::value_type
  joint_reduce(Group g, Ptr first, Ptr last, BinaryOperation binary_op);

Available only if ``sycl::is_group_v<std::decay_t<Group>>`` is ``true``,
``Ptr`` is a pointer to a fundamental type, and ``BinaryOperation`` is a
SYCL function object type.

``binary_op(*first, *first)`` must return a value of type
``std::iterator_traits<Ptr>::value_type``.

``first``, ``last``, and the type of ``binary_op`` must be the same for all
work-items in group ``g``. ``binary_op`` must be an instance of a SYCL
function object.

Returns the result of combining the values resulting from dereferencing all
iterators in the range ``[first, last)`` using the operator ``binary_op``,
where the values are combined according to the generalized sum defined in
standard C++.


.. rubric:: Overload 2

::

  template <typename Group, typename Ptr, typename T, typename BinaryOperation>
  T joint_reduce(Group g, Ptr first, Ptr last, T init, BinaryOperation binary_op);

Available only if ``sycl::is_group_v<std::decay_t<Group>>`` is ``true``,
``Ptr`` is a pointer to a fundamental type, ``T`` is a fundamental type,
and ``BinaryOperation`` is a SYCL function object type.

``binary_op(*first, *first)`` must return a value of type ``T``.

``first``, ``last``, ``init``, and the type of ``binary_op`` must be the
same for all work-items in group ``g``. ``binary_op`` must be an instance
of a SYCL function object.

Returns the result of combining the values resulting from dereferencing all
iterators in the range ``[first, last)`` and the initial value ``init`` using
the operator ``binary_op``, where the values are combined according to the
generalized sum defined in standard C++.

``reduce_over_group``
=====================

.. rubric:: Overload 1

::

  template <typename Group, typename T, typename BinaryOperation>
  T reduce_over_group(Group g, T x, BinaryOperation binary_op);

Available only if ``sycl::is_group_v<std::decay_t<Group>>`` is ``true``, ``T``
is a fundamental type and ``BinaryOperation`` is a SYCL function object type.

``binary_op(x, x)`` must return a value of type ``T``.

``binary_op`` must be an instance of a SYCL function object.

Returns the result of combining all the values of ``x`` specified by each
work-item in group ``g`` using the operator ``binary_op``, where the values
are combined according to the generalized sum defined in standard C++.

.. rubric:: Overload 2

::

  template <typename Group, typename V, typename T, typename BinaryOperation>
  T reduce_over_group(Group g, V x, T init, BinaryOperation binary_op);

Available only if ``sycl::is_group_v<std::decay_t<Group>>`` is ``true``, ``V``
and ``T`` are fundamental types, and ``BinaryOperation`` is a SYCL function
object type.

``binary_op(init, x)`` must return a value of type ``T``.

``binary_op`` must be an instance of a SYCL function object.

Returns the result of combining all the values of ``x`` specified by each
work-item in group ``g`` and the initial value ``init`` using the operator
``binary_op``, where the values are combined according to the generalized
sum defined in standard C++.


=========================================
``exclusive_scan`` and ``inclusive_scan``
=========================================

The ``std::exclusive_scan`` and ``std::inclusive_scan`` functions in standard
C++ compute a prefix sum using a binary operator. For a scan of elements
:math:`[x_0, …, x_n]`, the `i`-th result in an exclusive scan is the
generalized non-commutative sum of all elements preceding :math:`x_i`
(excluding :math:`x_i` itself), whereas the `i`-th result in an inclusive scan
is the generalized non-commutative sum of all elements preceding :math:`x_i`
(including :math:`x_i` itself).

SYCL provides two similar sets of algorithms that compute the same prefix
sums using the generalized non-commutative sum as defined by standard C++:

1. ``sycl::joint_exclusive_scan`` and ``sycl::joint_inclusive_scan`` use
   the work-items in a group to execute the corresponding algorithm in
   parallel, and intermediate partial prefix sums are written to memory
   as in standard C++.
2. ``sycl::exclusive_scan_over_group`` and ``sycl::inclusive_scan_over_group``
   perform a scan over values held directly by the work-items in a group, and
   the result returned to each work-item represents a partial prefix sum.

The result of a call to a scan is non-deterministic if the binary operator is
not associative. Only the binary operators defined in :ref:`function-objects`
are supported by the scan functions in SYCL 2020, but the standard C++ syntax
is used for forward compatibility with future SYCL versions.

``sycl::joint_exclusive_scan``
==============================

.. rubric:: Overload 1

::

  template <typename Group, typename InPtr, typename OutPtr, typename BinaryOperation>
  OutPtr joint_exclusive_scan(Group g, InPtr first, InPtr last, OutPtr result,
                              BinaryOperation binary_op);

Available only if ``sycl::is_group_v<std::decay_t<Group>>`` is ``true``,
``InPtr`` and ``OutPtr`` are pointers to fundamental types, and
``BinaryOperation`` is a SYCL function object type.

``binary_op(*first, *first)`` must return a value of type
``std::iterator_traits<OutPtr>::value_type``.

``first``, ``last``, ``result``, and the type of ``binary_op`` must be the
same for all work-items in group ``g``. ``binary_op`` must be an instance
of a SYCL function object.

.. note:: Note that ``first`` may be equal to ``result``.

The value written to ``result + i`` is the exclusive scan of the values
resulting from dereferencing the first ``i`` values in the range
``[first, last)`` and the identity value of ``binary_op`` (as identified
by ``sycl::known_identity``), using the operator ``binary_op``. The scan
is computed using a generalized non-commutative sum as defined in
standard C++.

Returns a pointer to the end of the output range.


.. rubric:: Overload 2

::

  template <typename Group, typename InPtr, typename OutPtr, typename T,
            typename BinaryOperation>
  OutPtr joint_exclusive_scan(Group g, InPtr first, InPtr last, OutPtr result,
                              T init, BinaryOperation binary_op);

Available only if ``sycl::is_group_v<std::decay_t<Group>>`` is ``true``,
``InPtr`` and ``OutPtr`` are pointers to fundamental types, ``T`` is a
fundamental type, and ``BinaryOperation`` is a SYCL function object type.

``binary_op(init, *first)`` must return a value of type ``T``.

``first``, ``last``, ``result``, ``init``, and the type of ``binary_op``
must be the same for all work-items in group ``g``. ``binary_op`` must
be an instance of a SYCL function object.

.. note:: Note that ``first`` may be equal to ``result``.

The value written to ``result + i`` is the exclusive scan of the values
resulting from dereferencing the first ``i`` values in the range
``[first, last)`` and an initial value specified by ``init``, using the
operator ``binary_op``. The scan is computed using a generalized
non-commutative sum as defined in standard C++.

Returns a pointer to the end of the output range.


``sycl::exclusive_scan_over_group``
===================================

.. rubric:: Overload 1

::

  template <typename Group, typename T, typename BinaryOperation>
  T exclusive_scan_over_group(Group g, T x, BinaryOperation binary_op);

Available only if ``sycl::is_group_v<std::decay_t<Group>>`` is ``true``,
``T`` is a fundamental type, and ``BinaryOperation`` is a SYCL function
object type.

``binary_op(x, x)`` must return a value of type ``T``.

``binary_op`` must be an instance of a SYCL function object.

Returns the value returned on work-item ``i`` is the exclusive scan of the
first ``i`` values in group ``g`` and the identity value of ``binary_op``
(as identified by ``sycl::known_identity``), using the operator ``binary_op``.
The scan is computed using a generalized non-commutative sum as defined in
standard C++. For multi-dimensional groups, the order of work-items in
group ``g`` is determined by their linear id.


.. rubric:: Overload 2

::

  template <typename Group, typename V, typename T, typename BinaryOperation>
  T exclusive_scan_over_group(Group g, V x, T init, BinaryOperation binary_op);

Available only if ``sycl::is_group_v<std::decay_t<Group>>`` is ``true``,
``V`` and ``T`` are fundamental types, and ``BinaryOperation`` is a SYCL
function object type.

``binary_op(init, x)`` must return a value of type ``T``.

``binary_op`` must be an instance of a SYCL function object.

The value returned on work-item ``i`` is the exclusive scan of the first
``i`` values in group ``g`` and an initial value specified by ``init``,
using the operator ``binary_op``. The scan is computed using a generalized
non-commutative sum as defined in standard C++. For multi-dimensional groups,
the order of work-items in group ``g`` is determined by their linear id.


``sycl::joint_inclusive_scan``
==============================

.. rubric:: Overload 1

::

  template <typename Group, typename InPtr, typename OutPtr, typename BinaryOperation>
  OutPtr joint_inclusive_scan(Group g, InPtr first, InPtr last, OutPtr result,
                              BinaryOperation binary_op);

Available only if ``sycl::is_group_v<std::decay_t<Group>>`` is ``true``,
``InPtr`` and ``OutPtr`` are pointers to fundamental types, and
``BinaryOperation`` is a SYCL function object type.

``binary_op(*first, *first)`` must return a value of type
``std::iterator_traits<OutPtr>::value_type``.

``first``, ``last``, ``result``, and the type of ``binary_op`` must be the
same for all work-items in group ``g``. ``binary_op`` must be an instance
of a SYCL function object.

.. note:: Note that ``first`` may be equal to ``result``.

The value written to ``result + i`` is the inclusive scan of the values
resulting from dereferencing the first ``i`` values in the range
``[first, last)`` and the identity value of ``binary_op`` (as identified
by ``sycl::known_identity``), using the operator ``binary_op``. The scan
is computed using a generalized non-commutative sum as defined in
standard C++.

Returns a pointer to the end of the output range.


.. rubric:: Overload 2

::

  template <typename Group, typename InPtr, typename OutPtr, typename T,
            typename BinaryOperation>
  OutPtr joint_inclusive_scan(Group g, InPtr first, InPtr last, OutPtr result,
                              BinaryOperation binary_op, T init);

Available only if ``sycl::is_group_v<std::decay_t<Group>>`` is ``true``,
``InPtr`` and ``OutPtr`` are pointers to fundamental types, ``T`` is a
fundamental type, and ``BinaryOperation`` is a SYCL function object type.

``binary_op(init, *first)`` must return a value of type ``T``.

``first``, ``last``, ``result``, ``init``, and the type of ``binary_op``
must be the same for all work-items in group ``g``. ``binary_op`` must
be an instance of a SYCL function object.

.. note:: Note that ``first`` may be equal to ``result``.

The value written to ``result + i`` is the inclusive scan of the values
resulting from dereferencing the first ``i`` values in the range
``[first, last)`` and an initial value specified by ``init``, using the
operator ``binary_op``. The scan is computed using a generalized
non-commutative sum as defined in standard C++.

Returns a pointer to the end of the output range.


``sycl::inclusive_scan_over_group``
===================================

.. rubric:: Overload 1

::

  template <typename Group, typename T, typename BinaryOperation>
  T inclusive_scan_over_group(Group g, T x, BinaryOperation binary_op);

Available only if ``sycl::is_group_v<std::decay_t<Group>>`` is ``true``,
``T`` is a fundamental type, and ``BinaryOperation`` is a SYCL function
object type.

``binary_op(x, x)`` must return a value of type ``T``.

``binary_op`` must be an instance of a SYCL function object.

Returns the value returned on work-item ``i`` is the inclusive scan of the
first ``i`` values in group ``g`` and the identity value of ``binary_op``
(as identified by ``sycl::known_identity``), using the operator ``binary_op``.
The scan is computed using a generalized non-commutative sum as defined in
standard C++. For multi-dimensional groups, the order of work-items in
group ``g`` is determined by their linear id.


.. rubric:: Overload 2

::

  template <typename Group, typename V, typename T, typename BinaryOperation>
  T inclusive_scan_over_group(Group g, V x, BinaryOperation binary_op, T init);

Available only if ``sycl::is_group_v<std::decay_t<Group>>`` is ``true``,
``V`` and ``T`` are fundamental types, and ``BinaryOperation`` is a SYCL
function object type.

``binary_op(init, x)`` must return a value of type ``T``.

``binary_op`` must be an instance of a SYCL function object.

The value returned on work-item ``i`` is the inclusive scan of the first
``i`` values in group ``g`` and an initial value specified by ``init``,
using the operator ``binary_op``. The scan is computed using a generalized
non-commutative sum as defined in standard C++. For multi-dimensional groups,
the order of work-items in group ``g`` is determined by their linear id.


.. _reduce-example:

=======
Example
=======

.. literalinclude:: /examples/reduce-alg-lib.cpp
   :lines: 5-
   :linenos:
   :caption: Using the group algorithms library to perform a work-group reduce.

.. literalinclude:: /examples/reduce-alg-lib.out
   :language: none
   :lines: 5-
   :caption: Output.
