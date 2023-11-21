..
  Copyright 2020 The Khronos Group Inc.
  SPDX-License-Identifier: CC-BY-4.0

.. _address_space_classes:

*********************
Address space classes
*********************

There are five different address spaces:

* global;
* local;
* constant;
* private;
* generic.

In a SYCL generic implementation, types are not affected by the
address spaces. However, there are situations where users need
to explicitly carry address spaces in the type.

For example:

* For performance tuning and genericness. Even if the platform
  supports the representation of the generic address space,
  this may come at some performance sacrifice. In order to help
  the target compiler, it can be useful to track specifically
  which address space a pointer is addressing.

* When linking SYCL kernels with SYCL backend-specific functions.
  In this case, it might be necessary to specify the address
  space for any pointer parameters.

Direct declaration of pointers with address spaces is discouraged
as the definition is implementation-defined. Users must rely on
the :ref:`multi_ptr` class to handle address space boundaries
and interoperability.

.. seealso:: |SYCL_SPEC_ADDRESS_SPACE|

.. _multi_ptr:

===================
``sycl::multi_ptr``
===================

::

  template <typename ElementType, access::address_space Space,
            access::decorated DecorateAddress = access::decorated::legacy>
  class multi_ptr;

  // Specialization of multi_ptr for void and const void
  // VoidType can be either void or const void
  template <access::address_space Space, access::decorated DecorateAddress>
  class multi_ptr<VoidType, Space, DecorateAddress>;

.. rubric:: Template parameters

===============  ===
``ElementType``
``Space``
===============  ===

.. rubric:: Member types

=====================  ====
``element_type``
``difference_type``
``pointer_t``
``const_pointer_t``
``reference_t``
``const_reference_t``
=====================  ====

.. rubric:: Nonmember data

=================  ====
``address_space``
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

``operator=``
=============

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

=================  ===
``dimensions``
``Mode``
``isPlaceholder``
=================  ===


``operator*``
=============

::

     friend ElementType& operator*(const sycl::multi_ptr& mp);

``operator->``
==============

::

     ElementType* operator->() const;

``get``
=======

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

``prefetch``
============

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

.. _explicit_pointer_aliases:

========================
Explicit pointer aliases
========================
