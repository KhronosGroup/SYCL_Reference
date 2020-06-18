**************
 Vector types
**************


===============
 rounding_mode
===============

::

   enum class rounding_mode {
       automatic,
       rte,
       rtz,
       rtp,
       rtn
   };

======
 elem
======

::

   struct elem {
       static constexpr int x = 0;
       static constexpr int y = 1;
       static constexpr int z = 2;
       static constexpr int w = 3;
       static constexpr int r = 0;
       static constexpr int g = 1;
       static constexpr int b = 2;
       static constexpr int a = 3;
       static constexpr int s0 = 0;
       static constexpr int s1 = 1;
       static constexpr int s2 = 2;
       static constexpr int s3 = 3;
       static constexpr int s4 = 4;
       static constexpr int s5 = 5;
       static constexpr int s6 = 6;
       static constexpr int s7 = 7;
       static constexpr int s8 = 8;
       static constexpr int s9 = 9;
       static constexpr int sA = 10;
       static constexpr int sB = 11;
       static constexpr int sC = 12;
       static constexpr int sD = 13;
       static constexpr int sE = 14;
       static constexpr int sF = 15;
   };


.. rst-class:: api-class
	       
=====
 vec
=====

::

   template <typename dataT, int numElements>
   class vec;

.. rubric:: Member types

============  ===
element_type
vector_t
============  ===

(constructors)
==============

::

   vec();
   explicit vec(const dataT &arg);
   template <typename... argTN>
   vec(const argTN&... args);
   vec(const vec<dataT, numElements> &rhs);
   vec(vector_t openclVector);


Conversion functions
====================

.. parsed-literal::

   operator vector_t() const;

  *Available when:
   numElements == 1*
   
  operator dataT() const;



get_count
=========

::
   
   size_t get_count() const;

get_size
========

::
   
  size_t get_size() const;
   
convert
=======

::
   
   template <typename convertT, rounding_mode roundingMode = rounding_mode::automatic>
   vec<convertT, numElements> convert() const;

as
==

::

   template <typename asT>
   asT as() const;

swizzle
=======

::

   template<int... swizzleIndexes>
   __swizzled_vec__ swizzle() const;
   
swizzle access
==============

::

     __swizzled_vec__ x() const;
     __swizzled_vec__ y() const;
     __swizzled_vec__ z() const;

     __swizzled_vec__ w() const;
     __swizzled_vec__ r() const;
     __swizzled_vec__ g() const;
     __swizzled_vec__ b() const;
     __swizzled_vec__ a() const;

     __swizzled_vec__ s0() const;
     __swizzled_vec__ s1() const;
     __swizzled_vec__ s2() const;
     __swizzled_vec__ s3() const;
     __swizzled_vec__ s4() const;
     __swizzled_vec__ s5() const;
     __swizzled_vec__ s6() const;
     __swizzled_vec__ s7() const;
     __swizzled_vec__ s8() const;
     __swizzled_vec__ s9() const;
     __swizzled_vec__ sA() const;
     __swizzled_vec__ sC() const;
     __swizzled_vec__ sD() const;
     __swizzled_vec__ sE() const;
     __swizzled_vec__ sF() const;

     __swizzled_vec__ lo() const;
     __swizzled_vec__ hi() const;
     __swizzled_vec__ odd() const;
     __swizzled_vec__ even() const;

load
====

::

   template <access::address_space addressSpace>
   void load(size_t offset, multi_ptr<const dataT, addressSpace> ptr);

store
=====

::

   template <access::address_space addressSpace>
   void load(size_t offset, multi_ptr<const dataT, addressSpace> ptr);

Arithmetic operators
====================

.. parsed-literal::
   
  friend vec operator+(const vec &lhs, const vec &rhs);
  friend vec operator+(const vec &lhs, const dataT &rhs);
  friend vec operator+(const dataT &lhs, const vec &rhs);

  friend vec operator-(const vec &lhs, const vec &rhs);
  friend vec operator-(const vec &lhs, const dataT &rhs);
  friend vec operator-(const dataT &lhs, const vec &rhs);

  friend vec operator*(const vec &lhs, const vec &rhs);
  friend vec operator*(const vec &lhs, const dataT &rhs);
  friend vec operator*(const dataT &lhs, const vec &rhs);

  friend vec operator/(const vec &lhs, const vec &rhs);
  friend vec operator/(const vec &lhs, const dataT &rhs);
  friend vec operator/(const dataT &lhs, const vec &rhs);

  
  friend vec &operator+=(vec &lhs, const vec &rhs);
  friend vec &operator+=(vec &lhs, const dataT &rhs);

  friend vec &operator-=(vec &lhs, const vec &rhs);
  friend vec &operator-=(vec &lhs, const dataT &rhs);

  friend vec &operator*=(vec &lhs, const vec &rhs);
  friend vec &operator*=(vec &lhs, const dataT &rhs);

  friend vec &operator/=(vec &lhs, const vec &rhs);
  friend vec &operator/=(vec &lhs, const dataT &rhs);


  friend vec &operator++(vec &lhs);
  friend vec operator++(vec& lhs, int);

  friend vec &operator--(vec &lhs);
  friend vec operator--(vec& lhs, int);

  friend vec<RET, numElements> operator&&(const vec &lhs, const vec &rhs);
  friend vec<RET, numElements> operator&&(const vec& lhs, const dataT &rhs);

  friend vec<RET, numElements> operator||(const vec &lhs, const vec &rhs);
  friend vec<RET, numElements> operator||(const vec& lhs, const dataT &rhs);


  friend vec<RET, numElements> operator==(const vec &lhs, const vec &rhs);
  friend vec<RET, numElements> operator==(const vec &lhs, const dataT &rhs);
  friend vec<RET, numElements> operator==(const dataT &lhs, const vec &rhs);

  friend vec<RET, numElements> operator!=(const vec &lhs, const vec &rhs);
  friend vec<RET, numElements> operator!=(const vec &lhs, const dataT &rhs);
  friend vec<RET, numElements> operator!=(const dataT &lhs, const vec &rhs);

  friend vec<RET, numElements> operator<(const vec &lhs, const vec &rhs);
  friend vec<RET, numElements> operator<(const vec &lhs, const dataT &rhs);
  friend vec<RET, numElements> operator<(const dataT &lhs, const vec &rhs);

  friend vec<RET, numElements> operator>(const vec &lhs, const vec &rhs);
  friend vec<RET, numElements> operator>(const vec &lhs, const dataT &rhs);
  friend vec<RET, numElements> operator>(const dataT &lhs, const vec &rhs);

  friend vec<RET, numElements> operator<=(const vec &lhs, const vec &rhs);
  friend vec<RET, numElements> operator<=(const vec &lhs, const dataT &rhs);
  friend vec<RET, numElements> operator<=(const dataT &lhs, const vec &rhs);

  friend vec<RET, numElements> operator>=(const vec &lhs, const vec &rhs);
  friend vec<RET, numElements> operator>=(const vec &lhs, const dataT &rhs);
  friend vec<RET, numElements> operator>=(const dataT &lhs, const vec &rhs);

  vec<dataT, numElements> &operator=(const vec<dataT, numElements> &rhs);
  vec<dataT, numElements> &operator=(const dataT &rhs);

  friend vec<RET, numElements> operator&&(const dataT &lhs, const vec &rhs);

  friend vec<RET, numElements> operator||(const dataT &lhs, const vec &rhs);

  *Available only when:
   dataT != cl_float && dataT != cl_double && dataT != cl_half*

  friend vec operator<<(const vec &lhs, const vec &rhs);
  friend vec operator<<(const vec &lhs, const dataT &rhs);
  friend vec operator<<(const dataT &lhs, const vec &rhs);
  friend vec operator>>(const vec &lhs, const vec &rhs);
  friend vec operator>>(const vec &lhs, const dataT &rhs);
  friend vec operator>>(const dataT &lhs, const vec &rhs);
  friend vec &operator>>=(vec &lhs, const vec &rhs);
  friend vec &operator>>=(vec &lhs, const dataT &rhs);
  friend vec &operator<<=(vec &lhs, const vec &rhs);
  friend vec &operator<<=(vec &lhs, const dataT &rhs);
  friend vec operator&(const vec &lhs, const vec &rhs);
  friend vec operator&(const vec &lhs, const dataT &rhs);
  friend vec operator|(const vec &lhs, const vec &rhs);
  friend vec operator|(const vec &lhs, const dataT &rhs);
  friend vec operator^(const vec &lhs, const vec &rhs);
  friend vec operator^(const vec &lhs, const dataT &rhs);
  friend vec &operator&=(vec &lhs, const vec &rhs);
  friend vec &operator&=(vec &lhs, const dataT &rhs);
  friend vec &operator|=(vec &lhs, const vec &rhs);
  friend vec &operator|=(vec &lhs, const dataT &rhs);
  friend vec &operator^=(vec &lhs, const vec &rhs);
  friend vec &operator^=(vec &lhs, const dataT &rhs);
  friend vec &operator%=(vec &lhs, const vec &rhs);
  friend vec &operator%=(vec &lhs, const dataT &rhs);
  friend vec operator%(const vec &lhs, const vec &rhs);
  friend vec operator%(const vec &lhs, const dataT &rhs);
  friend vec operator%(const dataT &lhs, const vec &rhs);
  friend vec operator~(const vec &v);
  friend vec<RET, numElements> operator!(const vec &v);
  friend vec operator&(const dataT &lhs, const vec &rhs);
  friend vec operator|(const dataT &lhs, const vec &rhs);
  friend vec operator^(const dataT &lhs, const vec &rhs);


  
