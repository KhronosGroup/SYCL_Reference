..
  Copyright 2024 The Khronos Group Inc.
  SPDX-License-Identifier: CC-BY-4.0

.. _range:

***************
``sycl::range``
***************

::

   template <int Dimensions = 1>
   class range;

``range<int Dimensions>`` is a 1D, 2D or 3D vector that defines
the iteration domain of either a single work-group in a parallel
dispatch, or the overall dimensions of the dispatch.
It can be constructed from integers.

.. seealso:: |SYCL_SPEC_RANGE|

==============
(constructors)
==============

::

  range();

  range(size_t dim0);

  range(size_t dim0, size_t dim1);

  range(size_t dim0, size_t dim1, size_t dim2);

Construct a ``SYCL`` range with the value ``0`` for each dimension
or a 1D,2D,3D range with values dim0, dim1 and dim2.


================
Member functions
================

``get``
=======

::

  size_t get(int dimension) const

Return the value of the specified dimension of the ``sycl::range``.

``size_t& operator[]``
======================

::

  size_t& operator[](int dimension);

Return the l-value of the specified dimension of the ``sycl::range``.

``size_t operator[]``
=====================

::

  size_t operator[](int dimension) const

Return the value of the specified dimension of the ``sycl::range``.

``size``
========

::

  size_t size() const

Return the size of the range computed as ``dimension0*…​*dimensionN``.

=======================
Hidden friend functions
=======================

``operatorOP``
==============

::

  range operatorOP(const sycl::range& lhs, const sycl::range& rhs);

Where ``OP`` is: ``+``, ``-``, ``*``, ``/``, ``%``, ``<<``,
``>>``, ``&``, ``|``,``^``, ``&&``, ``||``, ``<``, ``>``,
``<=``, ``>=``.

Constructs and returns a new instance of the ``sycl::range`` class
template with the same dimensionality as ``lhs range``, where each
element of the new ``sycl::range`` instance is the result of an
element-wise ``OP`` operator between each element of ``lhs range``
and each element of the ``rhs range``. If the operator returns
a ``bool``, the result is the cast to ``size_t``.

::

  range operatorOP(const sycl::range& lhs, const size_t& rhs);

Where ``OP`` is: ``+``, ``-``, ``*``, ``/``, ``%``, ``<<``,
``>>``, ``&``, ``|``, ``^``, ``&&``, ``||``, ``<``, ``>``,
``<=``, ``>=``.

Constructs and returns a new instance of the ``sycl::range`` class
template with the same dimensionality as ``lhs range``, where each
element of the new ``sycl::range`` instance is the result of an
element-wise ``OP`` operator between each element of this ``sycl::range``
and the ``rhs size_t``. If the operator returns a ``bool``, the
result is the cast to ``size_t``.

::

  sycl::range& operatorOP(sycl::range& lhs, const sycl::range& rhs);

Where ``OP`` is: ``+=``, ``-=``, ``*=``, ``/=``, ``%=``,
``<<=``, ``>>=``, ``&=``, ``|=``, ``^=``.

Assigns each element of ``lhs range`` instance with the result of an
element-wise ``OP`` operator between each element of ``lhs range`` and
each element of the ``rhs range`` and returns ``lhs range``.
If the operator returns a ``bool``, the result is the cast to ``size_t``.

::

  sycl::range& operatorOP(sycl::range& lhs, const size_t& rhs);

Where ``OP`` is: ``+=``, ``-=``, ``*=``, ``/=``, ``%=``,
``<<=``, ``>>=``, ``&=``, ``|=``, ``^=``.

Assigns each element of ``lhs range`` instance with the result of an
element-wise ``OP`` operator between each element of ``lhs range``
and the ``rhs size_t`` and returns ``lhs range``. If the operator
returns a ``bool``, the result is the cast to ``size_t``.

::

  range operatorOP(const size_t& lhs, const sycl::range& rhs);

Where ``OP`` is: ``+``, ``-``, ``*``, ``/``, ``%``, ``<<``,
``>>``, ``&``, ``|``, ``^``, ``&&``, ``||``, ``<``, ``>``,
``<=``, ``>=``.

Constructs and returns a new instance of the ``sycl::range``
class template with the same dimensionality as the ``rhs`` ``sycl::range``,
where each element of the new ``sycl::range`` instance is the result
of an element-wise ``OP`` operator between the ``lhs size_t``
and each element of the ``rhs`` ``sycl::range``. If the operator
returns a ``bool``, the result is the cast to ``size_t``.

::

  range operatorOP(const sycl::range& rhs);

Where ``OP`` is: unary ``+``, unary ``-``.

Constructs and returns a new instance of the ``sycl::range`` class
template with the same dimensionality as the ``rhs`` ``sycl::range``,
where each element of the new ``sycl::range`` instance is the result
of an element-wise ``OP`` operator on the ``rhs``
``sycl::range``.

::

  sycl::range& operatorOP(sycl::range& rhs);

Where ``OP`` is: prefix ``++``, prefix ``--``.

Assigns each element of the ``rhs range`` instance with the result of an
element-wise ``OP`` operator on each element of the ``rhs range``
and returns this ``sycl::range``.

::

  range operatorOP(sycl::range& lhs, int);

Where ``OP`` is: postfix ``++``, postfix ``--``.

Make a copy of the ``lhs range``. Assigns each element of the ``lhs range``
instance with the result of an element-wise ``OP`` operator on each element
of the ``lhs range``. Then return the initial copy of the ``sycl::range``.
