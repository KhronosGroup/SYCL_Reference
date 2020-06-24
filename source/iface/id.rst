====
 id
====

::

   template <int dimensions = 1>
   class id;

.. rubric:: Member functions
	    
=================  ===
`(constructors)`_
get
=================  ===

.. rubric:: Nonmember functions
	    
=================  ===
(operators)
=================  ===

(constructors)
==============

::

  id();

  *Available only when:
   dimensions==1*
    
  id(size_t dim0);

  *Available only when:
   dimensions==2*

  id(size_t dim0, size_t dim1);

  *Available only when:
   dimensions==3*

  id(size_t dim0, size_t dim1, size_t dim2);

  id(const range<dimensions> &range);
  id(const item<dimensions> &item);

get
===

::
   
  size_t get(int dimension) const;

(operators)
===========

::
   
  size_t &operator[](int dimension);
  size_t operator[](int dimension) const;

  *OP is:
   +, -, \*, /, %, <<, >>, &, |, ^, &&, ||, <, >, <=, >=*

  friend id operatorOP(const id &lhs, const id &rhs);
  friend id operatorOP(const id &lhs, const size_t &rhs);

  *OP is:
   +=, -=, \*=, /=, %=, <<=, >>=, &=, |=, ^=*
   
  friend id &operatorOP(id &lhs, const id &rhs);
  friend id &operatorOP(id &lhs, const size_t &rhs);

  *OP is:
   +, -, \*, /, %, <<, >>, &, |, ^, &&, ||, <, >, <=, >=*
   
   friend id operatorOP(const size_t &lhs, const id &rhs);

