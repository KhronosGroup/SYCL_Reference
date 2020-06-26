.. _multipointer:

**************
 Multipointer
**************

=======================
 access::address_space
=======================

::
   
   enum class address_space : int {
       global_space,
       local_space,
       constant_space,
       private_space
   };


.. rst-class:: api-class
	       
===========
 multi_ptr
===========

::

   template <typename ElementType, access::address_space Space> class multi_ptr;

   template <access::address_space Space> class multi_ptr<VoidType, Space>;

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
   
.. member-toc::

(constructors)
==============
	    
::

  multi_ptr();
  multi_ptr(const multi_ptr&);
  multi_ptr(multi_ptr&&);
  multi_ptr(pointer_t);
  multi_ptr(ElementType*);
  multi_ptr(std::nullptr_t);

operator=
=========

.. parsed-literal::
   
  multi_ptr &operator=(const multi_ptr&);
  multi_ptr &operator=(multi_ptr&&);
  multi_ptr &operator=(pointer_t);
  multi_ptr &operator=(ElementType*);
  multi_ptr &operator=(std::nullptr_t);

   
  *Available only when:
   Space == global_space*

  template <int dimensions, access::mode Mode, access::placeholder isPlaceholder>
  multi_ptr(accessor<ElementType, dimensions, Mode, access::target::global_buffer, isPlaceholder>);

  *Available only when:
   Space == local_space*
   
  template <int dimensions, access::mode Mode, access::placeholder isPlaceholder>
  multi_ptr(accessor<ElementType, dimensions, Mode, access::target::local, isPlaceholder>);

  *Available only when:   
   Space == constant_space*
   
  template <int dimensions, access::mode Mode, access::placeholder isPlaceholder> 
  multi_ptr(accessor<ElementType, dimensions, Mode, access::target::constant_buffer, isPlaceholder>);


.. rubric:: Template parameters

===============  ===
dimensions
Mode
isPlaceholder
===============  ===


operator*
=========

::

     friend ElementType& operator*(const multi_ptr& mp);

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

  operator multi_ptr<void, Space>() const;

  *Implicit conversion to a multi_ptr<const void>. Only
   available when ElementType is const-qualified*
   
  operator multi_ptr<const void, Space>() const;

  *Implicit conversion to multi_ptr<const ElementType, Space>*
  
  operator multi_ptr<const ElementType, Space>() const;



(Arithmetic operators)
======================

::

  friend multi_ptr& operator++(multi_ptr& mp);
  friend multi_ptr operator++(multi_ptr& mp, int);
  friend multi_ptr& operator--(multi_ptr& mp);
  friend multi_ptr operator--(multi_ptr& mp, int);
  friend multi_ptr& operator+=(multi_ptr& lhs, difference_type r);
  friend multi_ptr& operator-=(multi_ptr& lhs, difference_type r);
  friend multi_ptr operator+(const multi_ptr& lhs, difference_type r);
  friend multi_ptr operator-(const multi_ptr& lhs, difference_type r);

prefetch
========

::
 
 void prefetch(size_t numElements) const;
  
(Relational operators)
======================

::
   
  friend bool operator==(const multi_ptr& lhs, const multi_ptr& rhs);
  friend bool operator!=(const multi_ptr& lhs, const multi_ptr& rhs);
  friend bool operator<(const multi_ptr& lhs, const multi_ptr& rhs);
  friend bool operator>(const multi_ptr& lhs, const multi_ptr& rhs);
  friend bool operator<=(const multi_ptr& lhs, const multi_ptr& rhs);
  friend bool operator>=(const multi_ptr& lhs, const multi_ptr& rhs);

  friend bool operator==(const multi_ptr& lhs, std::nullptr_t);
  friend bool operator!=(const multi_ptr& lhs, std::nullptr_t);
  friend bool operator<(const multi_ptr& lhs, std::nullptr_t);
  friend bool operator>(const multi_ptr& lhs, std::nullptr_t);
  friend bool operator<=(const multi_ptr& lhs, std::nullptr_t);
  friend bool operator>=(const multi_ptr& lhs, std::nullptr_t);

  friend bool operator==(std::nullptr_t, const multi_ptr& rhs);
  friend bool operator!=(std::nullptr_t, const multi_ptr& rhs);
  friend bool operator<(std::nullptr_t, const multi_ptr& rhs);
  friend bool operator>(std::nullptr_t, const multi_ptr& rhs);
  friend bool operator<=(std::nullptr_t, const multi_ptr& rhs);
  friend bool operator>=(std::nullptr_t, const multi_ptr& rhs);



