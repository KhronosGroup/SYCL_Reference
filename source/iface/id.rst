..
  Copyright 2024 The Khronos Group Inc.
  SPDX-License-Identifier: CC-BY-4.0

.. _id:

************
``sycl::id``
************

::

   template <int Dimensions = 1>
   class id;

The ``sycl::id`` class is a collection of size ``Dimensions`` that is used
to represent an id into a global or local :ref:`range`.
It can be used as an index in an accessor of the same rank.
The subscript operator (``operator[](n)``) returns the
component ``n`` as a ``size_t``.

.. seealso:: |SYCL_SPEC_ID|

==============
(constructors)
==============

::

  id();

Construct an id with the value ``0`` for each dimension

::

  id(size_t dim0);

Construct a 1D id with value ``dim0``.
Only available if ``Dimensions`` is equals to ``1``.

::

  id(size_t dim0, size_t dim1);

Construct a 2D id with value ``dim0`` and ``dim1``.
Only available if ``Dimensions`` is equals to ``2``.

::

  id(size_t dim0, size_t dim1, size_t dim2);

Construct a 3D id with value ``dim0``, ``dim1`` and ``dim2``.
Only available if ``Dimensions`` is equals to ``3``.

::

  id(const sycl::range<Dimensions>& range);

Construct an id from a :ref:`range`
using dimensions of ``range``.

::

  id(const sycl::item<Dimensions>& item);

Construct an id from a :ref:`item` using the ``sycl::id``
contained in the ``sycl::item``.

================
Member functions
================

``get``
=======

::

  size_t get(int dimension) const;

Return the value of the ``sycl::id`` for dimension ``dimension``.

``size_t& operator[]``
======================

::

  size_t& operator[](int dimension);

Return a reference to the requested ``dimension`` of the ``sycl::id`` object.

``size_t operator[]``
=====================

::

  size_t operator[](int dimension) const;

Return the value of the requested ``dimension`` of the ``sycl::id`` object.

``operator size_t() const``
===========================

::

  operator size_t() const;

Available only when: ``Dimensions == 1``

Returns the same value as ``get(0)``.

=======================
Hidden friend functions
=======================

``operatorOP``
==============

::

  id operatorOP(const sycl::id& lhs, const sycl::id& rhs);

Where ``OP`` is: ``+``, ``-``, ``*``, ``/``, ``%``, ``<<``,
``>>``, ``&``, ``|``,``^``, ``&&``, ``||``, ``<``, ``>``,
``<=``, ``>=``.

Constructs and returns a new instance of the ``sycl::id`` class template
with the same dimensionality as ``lhs`` id, where each element of the new
``sycl::id`` instance is the result of an element-wise ``OP`` operator
between each element of ``lhs`` id and each element of the
``rhs`` id. If the element-wise operator
returns a ``bool``, the element result is the cast to ``size_t``.

::

  id operatorOP(const sycl::id& lhs, const size_t& rhs);

Where ``OP`` is: ``+``, ``-``, ``*``, ``/``, ``%``, ``<<``,
``>>``, ``&``, ``|``, ``^``, ``&&``, ``||``, ``<``, ``>``,
``<=``, ``>=``.

Constructs and returns a new instance of the ``sycl::id`` class template
with the same dimensionality as ``lhs`` id, where each element of the new
``sycl::id`` instance is the result of an element-wise ``OP`` operator
between each element of this ``sycl::id`` and the ``rhs`` ``size_t``.
If the element-wise operator returns a ``bool``, the element result
is the cast to ``size_t``.

::

  id& operatorOP(sycl::id& lhs, const sycl::id& rhs);

Where ``OP`` is: ``+=``, ``-=``, ``*=``, ``/=``, ``%=``,
``<<=``, ``>>=``, ``&=``, ``|=``, ``^=``.

Assigns each element of ``lhs`` id instance with the result of an
element-wise ``OP`` operator between each element of ``lhs`` id and
each element of the ``rhs`` id and returns ``lhs`` id.
If the element-wise operator returns a ``bool``, the element result
is the cast to ``size_t``.

::

  id& operatorOP(sycl::id& lhs, const size_t& rhs);

Where ``OP`` is: ``+=``, ``-=``, ``*=``, ``/=``, ``%=``,
``<<=``, ``>>=``, ``&=``, ``|=``, ``^=``.

Assigns each element of ``lhs`` id instance with the result of an
element-wise ``OP`` operator between each element of ``lhs`` id
and the ``rhs`` ``size_t`` and returns ``lhs`` id.
If the element-wise operator returns a ``bool``, the element result
is the cast to ``size_t``.

::

  id operatorOP(const size_t& lhs, const sycl::id& rhs);

Where ``OP`` is: ``+``, ``-``, ``*``, ``/``, ``%``, ``<<``,
``>>``, ``&``, ``|``, ``^``, ``&&``, ``||``, ``<``, ``>``,
``<=``, ``>=``.

Constructs and returns a new instance of the ``sycl::id`` class template
with the same dimensionality as the ``rhs`` id, where each
element of the new ``sycl::id`` instance is the result of an element-wise
``OP`` operator between the ``lhs`` ``size_t`` and each element of the
``rhs`` ``sycl::range``.  If the element-wise operator
returns a ``bool``, the element result is the cast to ``size_t``.

::

  id operatorOP(const sycl::id& rhs);

Where ``OP`` is: unary ``+``, unary ``-``.

Constructs and returns a new instance of the ``sycl::id`` class template
with the same dimensionality as the ``rhs`` id, where each element
of the new ``sycl::id`` instance is the result of an element-wise
``OP`` operator on the ``rhs`` id.

::

  id& operatorOP(sycl::id& rhs);

Where ``OP`` is: prefix ``++``, prefix ``--``.

Assigns each element of the ``rhs`` id instance with the result of an
element-wise ``OP`` operator on each element of the ``rhs`` id
and returns ``rhs``.

::

  id operatorOP(sycl::id& lhs, int);

Where ``OP`` is: postfix ``++``, postfix ``--``.

Make a copy of the ``lhs`` id. Assigns each element of the ``lhs`` id
instance with the result of an element-wise ``OP`` operator on each element
of the ``lhs`` id. Then return the initial copy of the ``sycl::id``.
