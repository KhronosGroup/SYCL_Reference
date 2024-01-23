..
  Copyright 2020 The Khronos Group Inc.
  SPDX-License-Identifier: CC-BY-4.0

.. _common-byval:

*************************
Common By-value Semantics
*************************

Each of the following SYCL runtime classes:
:ref:`id`, :ref:`range`, :ref:`item`, :ref:`nd_item`,
:ref:`h_item`, :ref:`group`, :ref:`sub_group`, and :ref:`nd_range`
must obey the following statements, where ``T`` is the
runtime class type:

* ``T`` must be default copy constructible and copy assignable
  in the host application (in the case where ``T`` is available on
  the host) and within SYCL kernel functions.
* ``T`` must be default destructible in the host application
  (in the case where ``T`` is available on the host) and
  within SYCL kernel functions.
* ``T`` must be default move constructible and default move
  assignable in the host application (in the case where ``T``
  is available on the host) and within SYCL kernel functions.
* ``T`` must be equality comparable in the host application
  (in the case where ``T`` is available on the host) and
  within SYCL kernel functions. Equality between two
  instances of ``T`` (i.e. ``a == b``) must be true if the
  value of all members are equal and non-equality between
  two instances of ``T`` (i.e. ``a != b``) must be true
  if the value of any members are not equal, unless either
  instance has become invalidated by a move operation.
  By extension of the requirements above, equality on ``T``
  must guarantee to be reflexive (i.e. ``a == a``),
  symmetric (i.e. ``a == b`` implies ``b == a`` and ``a != b``
  implies ``b != a``) and transitive (i.e. ``a == b
  && b == c`` implies ``c == a``).

Some SYCL runtime classes will have additional behavior
associated with copy, movement, assignment or destruction
semantics. If these are specified they are in addition
to those specified above unless stated otherwise.

Each of the runtime classes mentioned above must provide
a common interface of special member functions, member functions,
and friend functions in order to fulfill the copy, move, destruction
and equality requirements, following the *rule of five*
and the *rule of zero*.

::

  namespace sycl {

  class T {
    ...

    public:

    // If any of the following five special member functions are not
    // public, inline or defaulted, then all five of them should be
    // explicitly declared (see rule of five).
    // Otherwise, none of them should be explicitly declared
    // (see rule of zero).

    // T(const T &rhs);

    // T(T &&rhs);

    // T &operator=(const T &rhs);

    // T &operator=(T &&rhs);

    // ~T();

    ...

    friend bool operator==(const T& lhs, const T& rhs) { /* ... */ }

    friend bool operator!=(const T& lhs, const T& rhs) { /* ... */ }

    ...
  };

  } // namespace sycl

.. seealso:: |SYCL_SPEC_COMMON_BYVAL|

.. _byval_special_member_func:

======================================================
Common special member functions for by-value semantics
======================================================


.. list-table::
  :header-rows: 1

  * - Special member function
    - Description
  * - ``T(const T& rhs);``
    - Copy constructor.
  * - ``T(T&& rhs);``
    - Move constructor.
  * - ``T& operator=(const T& rhs);``
    - Copy assignment operator.
  * - ``T& operator=(T&& rhs);``
    - Move assignment operator.
  * - ``~T();``
    - Destructor.

.. _byval_hidden_friend_func:

=====================================================
Common hidden friend functions for by-value semantics
=====================================================

.. list-table::
  :header-rows: 1

  * - Hidden friend function
    - Description
  * - ::

        friend bool operator!=(const T& lhs, const T& rhs);

    - Returns ``true`` if this LHS SYCL ``T`` is equal to the
      RHS SYCL ``T`` in accordance with the requirements set
      out above, otherwise returns ``false``.
  * - ::

        friend bool operator!=(const T& lhs, const T& rhs);

    - Returns ``true`` if this LHS SYCL ``T`` is not equal to the
      RHS SYCL ``T`` in accordance with the requirements set out
      above, otherwise returns ``false``.
