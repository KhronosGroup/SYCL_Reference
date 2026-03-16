..
  Copyright 2024 The Khronos Group Inc.
  SPDX-License-Identifier: CC-BY-4.0

.. _private_memory:

************************
``sycl::private_memory``
************************

::

  template <typename T, int Dimensions = 1>
  class private_memory;


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

The ``sycl::private_memory`` class simply constructs private data
for a given group across the entire group. The ``id`` of the
current work-item is passed to any access to grab the correct data.

It is used to wrap the data, which guarantees use of private
per-work-item memory in the
:ref:`hierarchical parallel_for invoke <parallel_for_hierarchical>`.

Private memory is allocated per underlying work-item, not per
iteration of the ``parallel_for_work_item`` loop.

The number of instances of a private memory object is
only under direct control if a work-group size is passed
to the ``parallel_for_work_group`` call.
If the underlying work-group size is chosen by the runtime,
the number of private memory instances is opaque to the program.

Explicit private memory declarations should therefore be used
with care and with a full understanding of which instances of
a ``parallel_for_work_item`` loop will share the same
underlying variable.








.. seealso::

  :ref:`parallel_for_hierarchical`

  |SYCL_SYNC_PARALLEL_FOR_HIERARCHICAL|


==============
(constructors)
==============

::

  private_memory(const sycl::group<Dimensions>&);

Place an object of type ``T`` in the underlying private
memory of each work-items. The type ``T`` must be default
constructible.

The underlying constructor will be called for each work-item.

================
Member functions
================

::

  T& operator()(const sycl::h_item<Dimensions>& id)

Retrieve a reference to the object for the work-items.

=========
Example 1
=========

Example of usage of the ``sycl::private_memory``:

.. literalinclude:: /examples/private_memory_example.cpp
   :lines: 5-
   :linenos:

Output example:

.. literalinclude:: /examples/private_memory_example.out
   :language: none
   :lines: 5-
