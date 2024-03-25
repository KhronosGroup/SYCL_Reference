..
  Copyright 2024 The Khronos Group Inc.
  SPDX-License-Identifier: CC-BY-4.0

.. _iface-barriers-and-fences:

*******************
Barriers and fences
*******************

::

  namespace sycl {

    void atomic_fence(sycl::memory_order order, sycl::memory_scope scope);

  } // namespace sycl

A group barrier or memory-fence provides memory ordering semantics
over both the local address space and global address space.

A memory-fence provides control over the re-ordering of memory load
and store operations, subject to the associated memory ``order`` and
memory ``scope``, when paired with synchronization through an atomic
object.

The effects of a call to ``sycl::atomic_fence`` depend on the value
of the ``order`` parameter:

* ``sycl::memory_order::relaxed``: No effect.

* ``sycl::memory_order::acquire``: Acquire fence.

* ``sycl::memory_order::release``: Release fence.

* ``sycl::memory_order::acq_rel``: Both an acquire fence and a release fence.

* ``sycl::memory_order::seq_cst``: A sequentially consistent acquire
  and release fence.

A group barrier acts as both an acquire fence and a release fence: all
work-items in the group execute a release fence prior to synchronizing
at the barrier, and all work-items in the group execute an acquire
fence afterwards.

A group barrier provides implicit atomic synchronization as if through
an internal atomic object, such that the acquire and release fences
associated with the barrier synchronize with each other, without an
explicit atomic operation being required on an atomic object to
synchronize the fences.

.. seealso:: |SYCL_SPEC_BARRIERS_FENCES|
