..
  Copyright 2023 The Khronos Group Inc.
  SPDX-License-Identifier: CC-BY-4.0

.. _group-functions:

***************
Group functions
***************

SYCL provides a number of functions that expose functionality tied to
groups of work-items (such as group barriers and collective operations).
These group functions act as synchronization points and must be
encountered in converged control flow by all work-items in the group.
If one work-item in a group calls a group function, then all work-items
in that group must call exactly the same function under the same set of
conditions --- calling the same function under different conditions
(e.g. in different iterations of a loop, or different branches of a
conditional statement) results in undefined behavior. Additionally,
restrictions may be placed on the arguments passed to each function
in order to ensure that all work-items in the group agree on the
operation that is being performed. Any such restrictions on the arguments
passed to a function are defined within the descriptions of those
functions. Violating these restrictions results in undefined behavior.

Using a group function inside of a kernel may introduce additional
limits on the resources available to user code inside the same kernel.
The behavior of these limits is implementation-defined, but must be
reflected by calls to kernel querying functions
(such as ``kernel::get_info``) as described in |SYCL_SPEC_QUERIES|.

It is undefined behavior for any group function to be invoked within
a ``parallel_for_work_group`` or ``parallel_for_work_item`` context.

====================
``Group type trait``
====================

::

  namespace sycl {
  template <class T> struct is_group;

  template <class T> inline constexpr bool is_group_v = is_group<T>::value;
  } // namespace sycl

The ``is_group`` type trait is used to determine which types of groups are
supported by group functions, and to control when group functions participate
in overload resolution.

``is_group<T>`` inherits from ``std::true_type`` if T is the type of a standard
SYCL group (``group`` or ``sub_group``) and it inherits from
``std::false_type`` otherwise. A SYCL implementation may introduce additional
specializations of ``is_group<T>`` for implementation-defined group types,
if the interface of those types supports all member functions and static
members common to the ``group`` and ``sub_group`` classes.

===================
``group_broadcast``
===================

The ``group_broadcast`` function communicates a value held by
one work-item to all other work-items in the group.

::

  template <typename Group, typename T> T group_broadcast(Group g, T x); // (1)

  template <typename Group, typename T>
  T group_broadcast(Group g, T x, Group::linear_id_type local_linear_id); // (2)

  template <typename Group, typename T>
  T group_broadcast(Group g, T x, Group::id_type local_id); // (3)

1.Constraints: Available only if ``sycl::is_group_v<std::decay_t<Group>>``
is true and ``T`` is a trivially copyable type.

Returns: The value of ``x`` from the work-item with the smallest
linear id within group ``g``.

2.Constraints: Available only if ``sycl::is_group_v<std::decay_t<Group>>``
is true and ``T`` is a trivially copyable type.

Preconditions: ``local_linear_id`` must be the same for all work-items in
the group and must be in the range ``[0, get_local_linear_range())``.

Returns: The value of ``x`` from the work-item with the specified
linear id within group ``g``.

3.Constraints: Available only if ``sycl::is_group_v<std::decay_t<Group>>``
is true and ``T`` is a trivially copyable type.

Preconditions: ``local_id`` must be the same for all work-items in the group,
and its dimensionality must match the dimensionality of the group. The value
of ``local_id`` in each dimension must be greater than or equal to 0 and less
than the value of ``get_local_range()`` in the same dimension.

Returns: The value of ``x`` from the work-item with the
specified id within group ``g``.

=================
``group_barrier``
=================

The ``group_barrier`` function synchronizes all work-items in a
group, using a group barrier.

::

  template <typename Group>
  void group_barrier(Group g,
                     memory_scope fence_scope = Group::fence_scope); // (1)

1.Constraints: Available only if
``sycl::is_group_v<std::decay_t<Group>>`` is true.

Effects: Synchronizes all work-items in group ``g``. The current work-item
will wait at the barrier until all work-items in group ``g`` have reached
the barrier. In addition, the barrier performs ``mem-fence`` operations
ensuring that memory accesses issued before the barrier are not re-ordered
with those issued after the barrier: all work-items in group ``g`` execute
a release fence prior to synchronizing at the barrier, all work-items in
group ``g`` execute an acquire fence afterwards, and there is an implicit
synchronization of these fences as if provided by an explicit atomic
operation on an atomic object.

By default, the scope of these fences is set to the narrowest scope
including all work-items in group ``g`` (as reported by
``Group::fence_scope``). This scope may be optionally overridden with
a wider scope, specified by the ``fence_scope`` argument.
