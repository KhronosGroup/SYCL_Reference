..
  Copyright 2024 The Khronos Group Inc.
  SPDX-License-Identifier: CC-BY-4.0

.. _item:

**************
``sycl::item``
**************

::

  template <int Dimensions = 1, bool WithOffset = true>
  class item;

.. rubric:: Template parameters

===============  ===
``Dimensions``   Number of dimensions in the index space.
``WithOffset``   ``true`` if item has offset, otherwise ``false``.
===============  ===

``sycl::item`` identifies an instance of the function object
executing at each point in a :ref:`range`. It is passed to a
``parallel_for`` call or returned by member functions of :ref:`h_item`.

It encapsulates enough information to identify the work-item's
range of possible values and its :ref:`id` in that range.

.. note::

  It can optionally carry the offset of the range if provided to the ``parallel_for``.

  This is deprecated in SYCL 2020.

Instances of the ``sycl::item`` class are not user-constructible
and are passed by the runtime to each instance of the function object.
So the interface of the ``sycl::item`` does not expose a constructor.

The ``sycl::item`` class template provides the :ref:`common-byval`.

.. seealso:: |SYCL_SPEC_ITEM|

================
Member functions
================

``get_id``
==========

.. rubric:: Overload 1

::

  sycl::id<Dimensions> get_id() const;

Return the constituent :ref:`id` representing the
work-item's position in the iteration space.

.. rubric:: Overload 2

::

  size_t get_id(int dimension) const;

Return the same value as ``get_id()[dimension]``.


``get_range``
=============

.. rubric:: Overload 1

::

  sycl::range<Dimensions> get_range() const;

Returns a :ref:`range` representing the dimensions of
the range of possible values of the ``sycl::item``.

.. rubric:: Overload 2

::

  size_t get_range(int dimension) const;

Return the same value as ``get_range().get(dimension)``.


``get_offset``
==============

::

  sycl::id<Dimensions> get_offset() const;

.. note::

  Deprecated in SYCL 2020.

Returns an :ref:`id` representing the n-dimensional offset
provided to the ``parallel_for`` and that is added by the
runtime to the global-ID of each work-item, if this item
represents a global range.

For an item converted from an item with no offset this
will always return an :ref:`id` of all 0 values.

This member function is only available if
``WithOffset`` is ``true``.


``get_linear_id``
=================

::

  size_t get_linear_id() const;

Return the id as a linear index value.

Calculating a linear address from the
multi-dimensional index follows |SYCL_SPEC_LINEARIZATION|.


``operator[]``
==============

::

  size_t operator[](int dimension) const;

Return the same value as ``get_id(dimension)``.

=========================
Type conversion functions
=========================

``operator size_t``
===================

::

  operator size_t() const;

Available only when: ``Dimensions == 1``.

Returns the same value as ``get_id(0)``.


``operator item``
=================

::

  operator item<Dimensions, true>() const;

Available only when: ``WithOffset == false``.

Returns a ``sycl::item`` representing the same information as
the object holds but also includes the offset set to 0.

This conversion allow users to seamlessly write code that
assumes an offset and still provides an offset-less ``sycl::item``.
