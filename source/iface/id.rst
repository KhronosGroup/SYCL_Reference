..
  Copyright 2020 The Khronos Group Inc.
  SPDX-License-Identifier: CC-BY-4.0

.. rst-class:: api-class
	       
.. _id:

========
sycl::id
========

::

   template <int dimensions = 1>
   class id;

The ``id`` is an abstraction that describes the location of a point in
a :ref:`range`. Examples includes use as an index in an
:ref:`buffer-accessor` and as an argument to a kernel function in a
:ref:`handler-parallel_for` to identify the work item.

.. seealso:: |SYCL_SPEC_ID|

(constructors)
==============

::

  id();
  id(size_t dim0);
  id(size_t dim0, size_t dim1);
  id(size_t dim0, size_t dim1, size_t dim2);

  id(const sycl::range<dimensions> &range);
  id(const sycl::item<dimensions> &item);

Construct an ``id``.

An ``id`` can be 0, 1, 2, or 3 dimensions. An ``id`` constructed from
a :ref:`range` uses the ``range`` values. An ``id`` constructed from
an :ref:`item` uses the ``id`` contained in the ``item``.

get
===

::
   
  size_t get(int dimension) const;

Returns the value for dimension ``dimension``.

(operators)
===========

::
   
  size_t &operator[](int dimension);
  size_t operator[](int dimension) const;

  *OP is:
   +, -, \*, /, %, <<, >>, &, |, ^, &&, ||, <, >, <=, >=*

  friend id operatorOP(const sycl::id &lhs, const sycl::id &rhs);
  friend id operatorOP(const sycl::id &lhs, const size_t &rhs);

  *OP is:
   +=, -=, \*=, /=, %=, <<=, >>=, &=, |=, ^=*
   
  friend sycl::id &operatorOP(sycl::id &lhs, const sycl::id &rhs);
  friend sycl::id &operatorOP(sycl::id &lhs, const size_t &rhs);

  *OP is:
   +, -, \*, /, %, <<, >>, &, |, ^, &&, ||, <, >, <=, >=*
   
   friend sycl::id operatorOP(const size_t &lhs, const sycl::id &rhs);

Relational, arithmetic, and indexing operators on an ``id``.
