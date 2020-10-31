..
  Copyright 2020 The Khronos Group Inc.
  SPDX-License-Identifier: CC-BY-4.0

.. _common-byval:

====================
 By-value Semantics
====================

Types: :ref:`id`, :ref:`range`, :ref`item`, :ref:`nd_item`,
:ref:`h_item`, :ref:`group` and :ref:`nd_range`.

Classes with reference semantics support the following methods.

::

  class T {
    T(const T &rhs);
    T(T &&rhs);
    T &operator=(const T &rhs);
    T &operator=(T &&rhs);
    ~T();
    friend bool operator==(const T &lhs, const T &rhs) { /* ... */ }
    friend bool operator!=(const T &lhs, const T &rhs) { /* ... */ }
  };
