**********************************
Ranges and index space identifiers
**********************************

.. rst-class:: api-class
	       
=======
 range
=======

::
   
   template <int dimensions = 1>
   class range;

.. rubric:: Template parameters

================  ===
dimensions
================  ===

.. rubric:: Member functions

================  ===
get_
size_
================  ===

.. rubric:: Nonmember functions

=======================  ===
`operator[]`_
`Arithmetic Operators`_
=======================  ===

get
===

::
   
  size_t get(int dimension) const;

operator[]
==========

::
   
  size_t &operator[](int dimension);

  size_t operator[](int dimension) const;

size
====

::

   size_t size() const;

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


 
