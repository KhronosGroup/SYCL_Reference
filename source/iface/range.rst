.. rst-class:: api-class
	       
.. _range:

=======
 range
=======

::
   
   template <int dimensions = 1>
   class range;

The range is an abstraction that describes the number of elements in
each dimension of buffers and index spaces. It can contain 1, 2, or 3
numbers, dependending on the dimensionality of the object it
describes.


.. rubric:: Template parameters

================  ===
dimensions        Number of dimensions
================  ===

.. member-toc::


(constructors)
==============

::
   
  range(size_t dim0);
  range(size_t dim0, size_t dim1);
  range(size_t dim0, size_t dim1, size_t dim2);

Constructs a 1, 2, or 3 dimensional range.  


get
===

::
   
  size_t get(int dimension) const;

Returns the range of a single dimension.

operator[]
==========

::
   
  size_t &operator[](int dimension);
  size_t operator[](int dimension) const;

Returns the range of a single dimension.

size
====

::

   size_t size() const;

Returns the size of a range by multiplying the range of the individual
dimensions.

For a buffer, it is the number of elements in the buffer.

Arithmetic Operators
====================

.. parsed-literal::

  *OP is: +, -, \*, /, %, <<, >>, &, \|, ^, &&, \|\|, <, >, <=, >=*
  
  friend range operatorOP(const range &lhs, const range &rhs)
  friend range operatorOP(const range &lhs, const size_t &rhs)
  friend range operatorOP(const size_t &lhs, const range &rhs)

  *OP is: +=, -=, \*=, /=, %=, <<=, >>=, &=, \|=, ^=*

  friend range & operatorOP(const range &lhs, const range &rhs)
  friend range & operatorOP(const range &lhs, const size_t &rhs)

Arithmetical and relational operations on ranges.  
