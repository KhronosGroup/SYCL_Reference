..
  Copyright 2020 The Khronos Group Inc.
  SPDX-License-Identifier: CC-BY-4.0

.. temp ref
.. _malloc_device:

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
``AllocKind``  Type of allocation, see `usm-alloc`
``Alignment``  Alignment of the allocation
=============  ===

There is no specialization for ``usm::alloc::device`` because an ``Allocator``
is required to allocate memory that is accessible on the host.

(constructors)
==============

::

  usm_allocator(const context& syclContext, const device& syclDevice,
              const property_list& propList = {});

  usm_allocator(const queue& syclQueue, const property_list& propList = {});

Constructs a ``usm_allocator`` instance that allocates USM for the provided
context and device presented with first constructor.
The second constructor present a simplified form where ``syclQueue`` provides
the ``device`` and ``context``.

.. rubric:: Exceptions

``errc::invalid``
  If ``syclContext`` does not encapsulate the SYCL ``device`` returned
  by ``deviceSelector``.

``errc::feature_not_supported``
  If ``AllocKind`` is ``usm::alloc::host``, the constructors throws a synchronous
  ``exception`` with this error code if no device in ``syclContext`` has
  ``aspect::usm_host_allocations``. The ``syclDevice`` is ignored for this allocation kind.

  If ``AllocKind`` is ``usm::alloc::shared``, the constructors throws a synchronous
  ``exception`` with this error code if the ``syclDevice``
  does not have ``aspect::usm_shared_allocations``.

.. seealso:: `C++ Allocator <https://en.cppreference.com/w/cpp/named_req/Allocator>`__

.. rubric:: Example 1

.. literalinclude:: /examples/std-vector.cpp
   :lines: 5-
   :linenos:

Output:

.. literalinclude:: /examples/std-vector.out
   :lines: 5-
