**********************************
Ranges and index space identifiers
**********************************

=======
 range
=======

::
   
   template <int dimensions = 1>
   class range;

.. rubric:: Template parameters

| `dimensions` -

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

  friend range operatorOP(const range &lhs, const range &rhs)  [#arith]_

  friend range operatorOP(const range &lhs, const size_t &rhs) [#arith]_

  friend range operatorOP(const size_t &lhs, const range &rhs) [#arith]_

  friend range & operatorOP(const range &lhs, const range &rhs) [#assign]_

  friend range & operatorOP(const range &lhs, const size_t &rhs) [#assign]_

.. [#arith] OP is: +, -, \*, /, %, <<, >>, &, \|, ^, &&, \|\|, <, >, <=, >=
.. [#assign] OP is: +=, -=, \*=, /=, %=, <<=, >>=, &=, \|=, ^=	    

 
