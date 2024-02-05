..
  Copyright 2020 The Khronos Group Inc.
  SPDX-License-Identifier: CC-BY-4.0

.. _id:

************
``sycl::id``
************

::

   template <int Dimensions = 1>
   class id;

The ``id`` class is a collection of size ``Dimensions`` that is used
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

  id(size_t dim0);

  id(size_t dim0, size_t dim1);

  id(size_t dim0, size_t dim1, size_t dim2);

  id(const range<Dimensions>& range);

  id(const item<Dimensions>& item);

Construct an ``id``.

An ``id`` can be 1, 2, or 3 dimensions. An ``id`` constructed from
a :ref:`range` uses the ``range`` values. An ``id`` constructed from
an :ref:`item` uses the ``id`` contained in the ``item``.

================
Member functions
================

``get``
=======

::

  size_t get(int dimension) const

Return the value of the ``id`` for dimension ``dimension``.

``size_t& operator[]``
======================

::

  size_t& operator[](int dimension)

Return a reference to the requested dimension of the ``id`` object.

``size_t operator[]``
=====================

::

  size_t operator[](int dimension) const

Return the value of the requested dimension of the ``id`` object.

``operator size_t() const``
===========================

::

  operator size_t() const

Available only when: ``Dimensions == 1``

Returns the same value as ``get(0)``.

=======================
Hidden friend functions
=======================

``operatorOP``
==============

::

  id operatorOP(const id& lhs, const id& rhs);

Where ``OP`` is: ``+``, ``-``, ``*``, ``/``, ``%``, ``<<``,
``>>``, ``&``, ``|``,``^``, ``&&``, ``||``, ``<``, ``>``,
``<=``, ``>=``.

Constructs and returns a new instance of the SYCL ``id`` class template
with the same dimensionality as ``lhs id``, where each element of the new
SYCL ``id`` instance is the result of an element-wise ``OP`` operator
between each element of ``lhs id`` and each element of the
``rhs id``. If the operator returns a ``bool``,
the result is the cast to ``size_t``.

::

  id operatorOP(const id& lhs, const size_t& rhs);

Where ``OP`` is: ``+``, ``-``, ``*``, ``/``, ``%``, ``<<``,
``>>``, ``&``, ``|``, ``^``, ``&&``, ``||``, ``<``, ``>``,
``<=``, ``>=``.

Constructs and returns a new instance of the SYCL ``id`` class template
with the same dimensionality as ``lhs id``, where each element of the new
SYCL ``id`` instance is the result of an element-wise ``OP`` operator
between each element of this SYCL ``id`` and the ``rhs size_t``.
If the operator returns a ``bool``, the result is the cast to ``size_t``.

::

  id& operatorOP(id& lhs, const id& rhs);

Where ``OP`` is: ``+=``, ``-=``, ``*=``, ``/=``, ``%=``,
``<<=``, ``>>=``, ``&=``, ``|=``, ``^=``.

Assigns each element of ``lhs id`` instance with the result of an
element-wise ``OP`` operator between each element of ``lhs id`` and
each element of the ``rhs id`` and returns ``lhs id``.
If the operator returns a ``bool``, the result is the cast to ``size_t``.

::

  id& operatorOP(id& lhs, const size_t& rhs);

Where ``OP`` is: ``+=``, ``-=``, ``*=``, ``/=``, ``%=``,
``<<=``, ``>>=``, ``&=``, ``|=``, ``^=``.

Assigns each element of ``lhs id`` instance with the result of an
element-wise ``OP`` operator between each element of ``lhs id``
and the ``rhs size_t`` and returns ``lhs id``. If the operator
returns a ``bool``, the result is the cast to ``size_t``.

::

  id operatorOP(const size_t& lhs, const id& rhs);

Where ``OP`` is: ``+``, ``-``, ``*``, ``/``, ``%``, ``<<``,
``>>``, ``&``, ``|``, ``^``, ``&&``, ``||``, ``<``, ``>``,
``<=``, ``>=``.

Constructs and returns a new instance of the SYCL ``id`` class template
with the same dimensionality as the ``rhs`` SYCL ``id``, where each
element of the new SYCL ``id`` instance is the result of an element-wise
``OP`` operator between the ``lhs size_t`` and each element of the
``rhs`` SYCL ``range``. If the operator returns a ``bool``,
the result is the cast to ``size_t``.

::

  id operatorOP(const id& rhs);

Where ``OP`` is: unary ``+``, unary ``-``.

Constructs and returns a new instance of the SYCL ``id`` class template
with the same dimensionality as the ``rhs`` SYCL ``id``, where each element
of the new SYCL ``id`` instance is the result of an element-wise
``OP`` operator on the ``rhs`` SYCL ``id``.

::

  id& operatorOP(id& rhs);

Where ``OP`` is: prefix ``++``, prefix ``--``.

Assigns each element of the ``rhs id`` instance with the result of an
element-wise ``OP`` operator on each element of the ``rhs id``
and returns this ``id``.

::

  id operatorOP(id& lhs, int);

Where ``OP`` is: postfix ``++``, postfix ``--``.

Make a copy of the ``lhs id``. Assigns each element of the ``lhs id``
instance with the result of an element-wise ``OP`` operator on each element
of the ``lhs id``. Then return the initial copy of the ``id``.
