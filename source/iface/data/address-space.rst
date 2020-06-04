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


===========
 multi_ptr
===========

::

   template <typename ElementType, access::address_space Space> class multi_ptr;

   template <access::address_space Space> class multi_ptr<VoidType, Space>;

.. rubric:: Template parameters

| `ElementType` -
| `Space` -

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
   
(constructors)
==============
	    
::

  multi_ptr();

::

  multi_ptr(const multi_ptr&);

::

  multi_ptr(multi_ptr&&);

::

  multi_ptr(pointer_t);

::

  multi_ptr(ElementType*);

::

  multi_ptr(std::nullptr_t);

operator=
=========

::
   
  multi_ptr &operator=(const multi_ptr&);

::
   
  multi_ptr &operator=(multi_ptr&&);

::
   
  multi_ptr &operator=(pointer_t);

::
   
  multi_ptr &operator=(ElementType*);

::
   
  multi_ptr &operator=(std::nullptr_t);

.. parsed-literal::
   
  template <int dimensions, access::mode Mode, access::placeholder isPlaceholder>  [#global]_
  multi_ptr(accessor<ElementType, dimensions, Mode, access::target::global_buffer, isPlaceholder>);

.. parsed-literal::
   
  template <int dimensions, access::mode Mode, access::placeholder isPlaceholder>  [#local]_
  multi_ptr(accessor<ElementType, dimensions, Mode, access::target::local, isPlaceholder>);

.. parsed-literal::
   
  template <int dimensions, access::mode Mode, access::placeholder isPlaceholder>  [#constant]_
  multi_ptr(accessor<ElementType, dimensions, Mode, access::target::constant_buffer, isPlaceholder>);

.. [#global] Only if Space == global_space
.. [#local] Only if Space == local_space
.. [#constant] Only if Space == constant_space

.. rubric:: Template parameters

| `dimensions` -
| `Mode` -
| `isPlaceholder` -


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

Implicit conversions
====================

.. parsed-literal::
   
  operator ElementType*() const;                         [#pointer]_

  operator multi_ptr<void, Space>() const;               [#void]_

  operator multi_ptr<const void, Space>() const;         [#const-void]_

  operator multi_ptr<const ElementType, Space>() const;  [#const-elementtype]_

.. [#pointer] Implicit conversion to the underlying pointer type
.. [#void] Implicit conversion to a multi_ptr<void>.  Only available
           when ElementType is not const-qualified
.. [#const-void] Implicit conversion to a multi_ptr<const void>. Only
                 available when ElementType is const-qualified
.. [#const-elementtype] Implicit conversion to multi_ptr<const
                        ElementType, Space>


Arithmetic operators
====================

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
  
Relational operators
====================

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



