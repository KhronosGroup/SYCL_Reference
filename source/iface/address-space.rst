..
  Copyright 2020 The Khronos Group Inc.
  SPDX-License-Identifier: CC-BY-4.0

.. _address_space_classes:

*********************
Address space classes
*********************

There are five different address spaces (see also :ref:`address_space`):

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

.. _address_space:

===============================
``sycl::access::address_space``
===============================

::

  namespace sycl::access {

    enum class address_space : /* unspecified */ {
      global_space,
      local_space,
      constant_space, // Deprecated in SYCL 2020
      private_space,
      generic_space
    };

  } // namespace sycl::access

.. _access-decorated:

===========================
``sycl::access::decorated``
===========================

::

  namespace sycl {

  namespace access {

  enum class decorated : /* unspecified */ {
    no,
    yes,
    legacy // Deprecated in SYCL 2020
  };

  } // namespace access

  template <typename T> struct remove_decoration {
    using type = /* ... */;
  };

  template <typename T> using remove_decoration_t = remove_decoration<T>::type;

  } // namespace sycl

The :ref:`multi_ptr` class exposes 3 flavors of the
same interface:

* If the value of ``sycl::access::decorated`` is
  ``sycl::access::decorated::no``, the interface exposes pointers and
  references type that are not decorated by an address space.
* If the value of ``sycl::access::decorated`` is
  ``sycl::access::decorated::yes``, the interface exposes pointers and
  references type that are decorated by an address space.
* If the value of  ``sycl::access::decorated`` is
  ``sycl::access::decorated::legacy``, the 1.2.1 interface is exposed.
  This interface is deprecated.

The decoration is implementation dependent and relies
on device compiler extensions.

The decorated type may be distinct from the non-decorated one.

For interoperability with the SYCL backend, users
should rely on types exposed by the decorated version.

The template traits ``sycl::remove_decoration`` and type alias
``sycl::remove_decoration_t`` retrieve the non-decorated pointer
or reference from a decorated one. Using this template trait
with a non-decorated type is safe and returns the same type.

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

===================  ==========
``ElementType``      Type of pointed value.
``Space``            Selected address space (see :ref:`address_space`).
``DecorateAddress``  See :ref:`access-decorated`.
===================  ==========

The ``sycl::multi_ptr`` class is the common interface for the explicit
pointer classes, defined in :ref:`explicit_pointer_aliases`.

There are situations where a user may want to make their type address
space dependent. This allows performing generic programming that depends
on the address space associated with their data.
An example might be wrapping a pointer inside a class, where a user may
need to template the class according to the address space of the pointer
the class is initialized with. In this case, the ``sycl::multi_ptr``
class enables users to do this in a portable and stable way.

You can select address space via :ref:`address_space` ``Space`` template
parameter and also interface type via :ref:`access-decorated`
``DecorateAddress`` template parameter.

It is possible to use the ``void`` type for the ``sycl::multi_ptr`` class,
but in that case some functionality is disabled. ``sycl::multi_ptr<void>``
does not provide the ``reference`` or ``const_reference`` types, the access
operators (``operator*()``, ``operator->()``), the arithmetic operators or
``prefetch`` member function.

``constexpr`` values
====================

.. list-table::
  :header-rows: 1

  * - Field
    - Value
  * - ``is_decorated``
    - Equals to ``DecorateAddress == sycl::access::decorated::yes``.
  * - ``address_space``
    - Equals to ``Space`` template parameter value.

Member types
============

.. list-table::
  :header-rows: 1

  * - Type
    - Description
  * - ``value_type``
    - Type of pointed value (``ElementType``).
  * - ``pointer``
    - Type of the pointer to the value.
      Same as:
      ::

        std::conditional_t<is_decorated, __unspecified__*,
                           std::add_pointer_t<value_type>>;

  * - ``reference``
    - Type of the reference to the value.
      Same as:
      ::

        std::conditional_t<is_decorated, __unspecified__&,
                           std::add_lvalue_reference_t<value_type>>;

  * - ``iterator_category``
    - Same as ``std::random_access_iterator_tag``.
  * - ``difference_type``
    - Same as ``std::ptrdiff_t``.


(constructors)
==============


(operators)
===========


Member functions
================

``get``
-------

::

  pointer get() const;

Returns the underlying pointer. Whether the pointer is
decorated depends on the value of ``DecorateAddress``.

``get_decorated``
-----------------

::

  __unspecified__* get_decorated() const;

Returns the underlying pointer decorated by the address
space that it addresses.

.. note::

  The support involves implementation-defined device
  compiler extensions.

``get_raw``
-----------

::

  std::add_pointer_t<value_type> get_raw() const;

Returns the underlying pointer, always undecorated.

``prefetch``
------------

::

  void prefetch(size_t numElements) const;

Available only when:
``Space == sycl::access::address_space::global_space``.

Prefetches a number of elements specified by ``numElements`` into
the global memory cache. This operation is an implementation-defined
optimization and does not effect the functional behavior of the SYCL
kernel function.

Hidden friend functions
=======================

``operator*``
-------------

::

  reference operator*(const multi_ptr& mp);

Available only when: ``!std::is_void_v<ElementType>``.

Operator that returns a reference to the ``value_type`` of ``mp``.


``operator++``
--------------

::

  multi_ptr& operator++(multi_ptr& mp);

Available only when: ``!std::is_void_v<ElementType>``.

Increments ``mp`` by ``1`` and returns ``mp``.

::

  multi_ptr operator++(multi_ptr& mp, int);

Available only when: ``!std::is_void_v<ElementType>``.

Increments ``mp`` by ``1`` and returns a new ``multi_ptr``
with the value of the original ``mp``.

``operator--``
--------------

::

  sycl::multi_ptr& operator--(sycl::multi_ptr& mp);

Available only when: ``!std::is_void_v<ElementType>``.

Decrements ``mp`` by ``1`` and returns ``mp``.

::

  sycl::multi_ptr operator--(sycl::multi_ptr& mp, int);

Available only when: ``!std::is_void_v<ElementType>``.

Decrements ``mp`` by ``1`` and returns a new ``multi_ptr``
with the value of the original ``mp``.

``operator+=``
--------------

::

  sycl::multi_ptr& operator+=(sycl::multi_ptr& lhs, difference_type r);

Available only when: ``!std::is_void_v<ElementType>``.

Moves ``mp`` forward by ``r`` and returns ``lhs``.

``operator-=``
--------------

::

  sycl::multi_ptr& operator-=(sycl::multi_ptr& lhs, difference_type r);

Available only when: ``!std::is_void_v<ElementType>``.

Moves ``mp`` backward by ``r`` and returns ``lhs``.

``operator+``
-------------

::

  sycl::multi_ptr operator+(const sycl::multi_ptr& lhs, difference_type r);

Available only when: ``!std::is_void_v<ElementType>``.

Creates a new ``sycl::multi_ptr`` that points ``r``
forward compared to ``lhs``.

``operator-``
-------------

::

  sycl::multi_ptr operator-(const sycl::multi_ptr& lhs, difference_type r);

Available only when: ``!std::is_void_v<ElementType>``.

Creates a new ``sycl::multi_ptr`` that points ``r``
backward compared to ``lhs``.

``operator==``
--------------

::

  bool operator==(const sycl::multi_ptr& lhs, const sycl::multi_ptr& rhs);

Comparison operator ``==`` for ``sycl::multi_ptr`` class.

::

  bool operator==(const sycl::multi_ptr& lhs, std::nullptr_t);

  bool operator==(std::nullptr_t, const sycl::multi_ptr& rhs);

Comparison operator ``==`` for ``sycl::multi_ptr`` class
with a ``std::nullptr_t``.


``operator!=``
--------------

::

  bool operator!=(const sycl::multi_ptr& lhs, const sycl::multi_ptr& rhs);

Comparison operator ``!=`` for ``sycl::multi_ptr`` class.

::

  bool operator!=(const sycl::multi_ptr& lhs, std::nullptr_t);

  bool operator!=(std::nullptr_t, const sycl::multi_ptr& rhs);

Comparison operator ``!=`` for ``sycl::multi_ptr`` class
with a ``std::nullptr_t``.


``operator<``
-------------

::

  bool operator<(const sycl::multi_ptr& lhs, const sycl::multi_ptr& rhs);

Comparison operator ``<`` for ``sycl::multi_ptr`` class.

::

  bool operator<(const sycl::multi_ptr& lhs, std::nullptr_t);

  bool operator<(std::nullptr_t, const sycl::multi_ptr& rhs);

Comparison operator ``<`` for ``sycl::multi_ptr`` class
with a ``std::nullptr_t``.


``operator>``
-------------

::

  bool operator>(const sycl::multi_ptr& lhs, const sycl::multi_ptr& rhs);

Comparison operator ``>`` for ``sycl::multi_ptr`` class.

::

  bool operator>(const sycl::multi_ptr& lhs, std::nullptr_t);

  bool operator>(std::nullptr_t, const sycl::multi_ptr& rhs);

Comparison operator ``>`` for ``sycl::multi_ptr`` class
with a ``std::nullptr_t``.


``operator<=``
--------------

::

  bool operator<=(const sycl::multi_ptr& lhs, const sycl::multi_ptr& rhs);

Comparison operator ``<=`` for ``sycl::multi_ptr`` class.

::

  bool operator<=(const sycl::multi_ptr& lhs, std::nullptr_t);

  bool operator<=(std::nullptr_t, const sycl::multi_ptr& rhs);

Comparison operator ``<=`` for ``sycl::multi_ptr`` class
with a ``std::nullptr_t``.


``operator>=``
--------------

::

  bool operator>=(const sycl::multi_ptr& lhs, const sycl::multi_ptr& rhs);

Comparison operator ``>=`` for ``sycl::multi_ptr`` class.

::

  bool operator>=(const sycl::multi_ptr& lhs, std::nullptr_t);

  bool operator>=(std::nullptr_t, const sycl::multi_ptr& rhs);

Comparison operator ``>=`` for ``sycl::multi_ptr`` class
with a ``std::nullptr_t``.


.. _explicit_pointer_aliases:

========================
Explicit pointer aliases
========================

SYCL provides aliases to the :ref:`multi_ptr` class template
for each specialization of :ref:`address_space`.

A synopsis of the SYCL :ref:`multi_ptr` class template aliases
is provided below.

.. note::

  Using ``sycl::global_ptr``, ``sycl::local_ptr``, ``sycl::constant_ptr`` or
  ``sycl::private_ptr`` without specifying the decoration is deprecated.
  The default argument is provided for compatibility with 1.2.1.


``sycl::global_ptr``
====================

::

  namespace sycl {

  template <typename ElementType,
            access::decorated IsDecorated = access::decorated::legacy>
  using global_ptr =
      multi_ptr<ElementType, access::address_space::global_space, IsDecorated>;

  } // namespace sycl


``sycl::local_ptr``
===================

::

  namespace sycl {

  template <typename ElementType,
            access::decorated IsDecorated = access::decorated::legacy>
  using local_ptr =
      multi_ptr<ElementType, access::address_space::local_space, IsDecorated>;

  } // namespace sycl


``sycl::constant_ptr``
======================

.. warning::

  Deprecated in SYCL2020.

::

  namespace sycl {

  template <typename ElementType>
  using constant_ptr =
      multi_ptr<ElementType, access::address_space::constant_space,
                access::decorated::legacy>;

  } // namespace sycl


``sycl::private_ptr``
=====================

::

  namespace sycl {

  template <typename ElementType,
            access::decorated IsDecorated = access::decorated::legacy>
  using private_ptr =
      multi_ptr<ElementType, access::address_space::private_space, IsDecorated>;

  } // namespace sycl


``sycl::raw_global_ptr``
========================

The interface exposes non-decorated pointer while
keeping the address space information internally.

::

  namespace sycl {

  template <typename ElementType>
  using raw_global_ptr =
      multi_ptr<ElementType, access::address_space::global_space,
                access::decorated::no>;

  } // namespace sycl


``sycl::raw_local_ptr``
=======================

The interface exposes non-decorated pointer while
keeping the address space information internally.

::

  namespace sycl {

  template <typename ElementType>
  using raw_local_ptr =
      multi_ptr<ElementType, access::address_space::local_space,
                access::decorated::no>;

  } // namespace sycl


``sycl::raw_private_ptr``
=========================

The interface exposes non-decorated pointer while
keeping the address space information internally.

::

  namespace sycl {

  template <typename ElementType>
  using raw_private_ptr =
      multi_ptr<ElementType, access::address_space::private_space,
                access::decorated::no>;

  } // namespace sycl


``sycl::decorated_global_ptr``
==============================

The interface exposes decorated pointer.

::

  namespace sycl {

  template <typename ElementType>
  using decorated_global_ptr =
      multi_ptr<ElementType, access::address_space::global_space,
                access::decorated::yes>;

  } // namespace sycl


``sycl::decorated_local_ptr``
=============================

The interface exposes decorated pointer.

::

  namespace sycl {

  template <typename ElementType>
  using decorated_local_ptr =
      multi_ptr<ElementType, access::address_space::local_space,
                access::decorated::yes>;

  } // namespace sycl


``sycl::decorated_private_ptr``
===============================

The interface exposes decorated pointer.

::

  namespace sycl {

  template <typename ElementType>
  using decorated_private_ptr =
      multi_ptr<ElementType, access::address_space::private_space,
                access::decorated::yes>;

  } // namespace sycl
