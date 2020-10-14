..
  Copyright 2020 The Khronos Group Inc.
  SPDX-License-Identifier: CC-BY-4.0

.. _multipointer:

**************
 Multipointer
**************

===========================
sycl::access::address_space
===========================

::
   
   enum class address_space : int {
       global_space,
       local_space,
       constant_space,
       private_space
   };


.. seealso:: |SYCL_SPEC_ADDRESS_SPACE|

.. rst-class:: api-class
	       
===============
sycl::multi_ptr
===============

::

   template <typename ElementType, sycl::access::address_space Space> class multi_ptr;

   template <sycl::access::address_space Space> class multi_ptr<VoidType, Space>;

.. rubric:: Template parameters

===============  ===
ElementType
Space
===============  ===

.. rubric:: Member types

=================  ====
element_type
difference_type
pointer_t
const_pointer_t
reference_t
const_reference_t
=================  ====

.. rubric:: Nonmember data

=================  ====
address_space
=================  ====
   
.. seealso:: |SYCL_SPEC_MULTI_PTR|

(constructors)
==============
	    
::

  multi_ptr();
  multi_ptr(const sycl::multi_ptr&);
  multi_ptr(sycl::multi_ptr&&);
  multi_ptr(pointer_t);
  multi_ptr(ElementType*);
  multi_ptr(std::nullptr_t);

operator=
=========

.. parsed-literal::
   
  sycl::multi_ptr &operator=(const multi_ptr&);
  sycl::multi_ptr &operator=(multi_ptr&&);
  sycl::multi_ptr &operator=(pointer_t);
  sycl::multi_ptr &operator=(ElementType*);
  sycl::multi_ptr &operator=(std::nullptr_t);

   
  *Available only when:
   Space == global_space*

  template <int dimensions, access::mode Mode, access::placeholder isPlaceholder>
  sycl::multi_ptr(accessor<ElementType, dimensions, Mode, sycl::access::target::global_buffer, isPlaceholder>);

  *Available only when:
   Space == local_space*
   
  template <int dimensions, access::mode Mode, access::placeholder isPlaceholder>
  sycl::multi_ptr(accessor<ElementType, dimensions, Mode, sycl::access::target::local, isPlaceholder>);

  *Available only when:   
   Space == constant_space*
   
  template <int dimensions, access::mode Mode, access::placeholder isPlaceholder> 
  sycl::multi_ptr(accessor<ElementType, dimensions, Mode, sycl::access::target::constant_buffer, isPlaceholder>);


.. rubric:: Template parameters

===============  ===
dimensions
Mode
isPlaceholder
===============  ===


operator*
=========

::

     friend ElementType& operator*(const sycl::multi_ptr& mp);

operator->
==========

::

     ElementType* operator->() const;

get
===

::

  pointer_t get() const;

.. rubric:: Returns
	    
Returns the underlying OpenCL C pointer

(Implicit conversions)
======================

.. parsed-literal::
   
  *Implicit conversion to the underlying pointer type*

  operator ElementType*() const;

  *Implicit conversion to a multi_ptr<void>.  Only available
   when ElementType is not const-qualified*

  operator sycl::multi_ptr<void, Space>() const;

  *Implicit conversion to a multi_ptr<const void>. Only
   available when ElementType is const-qualified*
   
  operator sycl::multi_ptr<const void, Space>() const;

  *Implicit conversion to multi_ptr<const ElementType, Space>*
  
  operator sycl::multi_ptr<const ElementType, Space>() const;



(Arithmetic operators)
======================

::

  friend sycl::multi_ptr& operator++(sycl::multi_ptr& mp);
  friend sycl::multi_ptr operator++(sycl::multi_ptr& mp, int);
  friend sycl::multi_ptr& operator--(sycl::multi_ptr& mp);
  friend sycl::multi_ptr operator--(sycl::multi_ptr& mp, int);
  friend sycl::multi_ptr& operator+=(sycl::multi_ptr& lhs, difference_type r);
  friend sycl::multi_ptr& operator-=(sycl::multi_ptr& lhs, difference_type r);
  friend sycl::multi_ptr operator+(const sycl::multi_ptr& lhs, difference_type r);
  friend sycl::multi_ptr operator-(const sycl::multi_ptr& lhs, difference_type r);

prefetch
========

::
 
 void prefetch(size_t numElements) const;
  
(Relational operators)
======================

::
   
  friend bool operator==(const sycl::multi_ptr& lhs, const sycl::multi_ptr& rhs);
  friend bool operator!=(const sycl::multi_ptr& lhs, const sycl::multi_ptr& rhs);
  friend bool operator<(const sycl::multi_ptr& lhs, const sycl::multi_ptr& rhs);
  friend bool operator>(const sycl::multi_ptr& lhs, const sycl::multi_ptr& rhs);
  friend bool operator<=(const sycl::multi_ptr& lhs, const sycl::multi_ptr& rhs);
  friend bool operator>=(const sycl::multi_ptr& lhs, const sycl::multi_ptr& rhs);

  friend bool operator==(const sycl::multi_ptr& lhs, std::nullptr_t);
  friend bool operator!=(const sycl::multi_ptr& lhs, std::nullptr_t);
  friend bool operator<(const sycl::multi_ptr& lhs, std::nullptr_t);
  friend bool operator>(const sycl::multi_ptr& lhs, std::nullptr_t);
  friend bool operator<=(const sycl::multi_ptr& lhs, std::nullptr_t);
  friend bool operator>=(const sycl::multi_ptr& lhs, std::nullptr_t);

  friend bool operator==(std::nullptr_t, const sycl::multi_ptr& rhs);
  friend bool operator!=(std::nullptr_t, const sycl::multi_ptr& rhs);
  friend bool operator<(std::nullptr_t, const sycl::multi_ptr& rhs);
  friend bool operator>(std::nullptr_t, const sycl::multi_ptr& rhs);
  friend bool operator<=(std::nullptr_t, const sycl::multi_ptr& rhs);
  friend bool operator>=(std::nullptr_t, const sycl::multi_ptr& rhs);



