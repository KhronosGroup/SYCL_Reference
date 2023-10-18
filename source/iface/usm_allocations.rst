..
  Copyright 2020 The Khronos Group Inc.
  SPDX-License-Identifier: CC-BY-4.0

***************
USM allocations
***************

.. _usm_allocations:

.. rst-class:: api-class


The USM offers a range of allocation functions, each designed to
accommodate potential future extensions by accepting a ``property_list``
parameter. It's important to note that the core SYCL specification
currently lacks any specific definitions for USM allocation properties.
Some of the allocation functions support explicit alignment parameters,
and they behave similarly to ``std::aligned_alloc`` by returning ``nullptr``
when the alignment exceeds the implementation's capabilities. Some allocation
functions are templated on the allocated type ``T``, while others are not.

For alignment guarantees
for each category check link below:

.. seealso:: |SYCL_SPEC_USM_ALLOC|

***********************
C++ allocator interface
***********************

.. _allocator_interface:

SYCL defines an allocator class named ``usm_allocator`` that satisfies
the C++ named requirement ``Allocator``. The ``AllocKind`` template parameter
can be either ``usm::alloc::host`` or
``usm::alloc::shared``, causing the allocator to make
either host USM allocations or shared USM allocations.

The ``usm_allocator`` class has a template argument ``Alignment``,
which specifies the minimum alignment for memory that it allocates.
This alignment is used even if the allocator is rebound to a different
type. Memory allocated by this allocator is suitably aligned for objects
of its underlying ``value_type`` or at the alignment specified by
``Alignment``, whichever is greater.

=======================
``sycl::usm_allocator``
=======================

::

   template <typename T, sycl::usm::alloc AllocKind, size_t Alignment = 0>

   class usm_allocator;

.. rubric:: Template parameters

=============  ===
``T``          Type of allocated element
``AllocKind``  Type of allocation, see :ref:`usm-alloc`
``Alignment``  Alignment of the allocation
=============  ===

.. todo change ref:`usm-alloc`

There is no specialization for ``usm::alloc::device`` because an ``Allocator``
is required to allocate memory that is accessible on the host.

(constructors)
==============

::

  usm_allocator(const context& syclContext, const device& syclDevice,
              const property_list& propList = {});

  usm_allocator(const queue& syclQueue, const property_list& propList = {});

.. rubric:: Example 1

.. literalinclude:: /examples/std-vector.cpp
   :lines: 5-
   :linenos:

Output:

.. literalinclude:: /examples/std-vector.out
   :lines: 5-

.. rubric:: Member types

.. todo check why this mentoined in synopsis of the usm_allocator class
  file:///home/mvucic/Downloads/spec-outputs/html/sycl-2020.html#_c_allocator_interface

``allocate``
============

::

  T *allocate(size_t Size);

Allocates memory

``deallocate``
==============

::

  void deallocate(T *Ptr, size_t size);

Deallocates memory
