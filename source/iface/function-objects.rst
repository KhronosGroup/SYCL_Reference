..
  Copyright 2023 The Khronos Group Inc.
  SPDX-License-Identifier: CC-BY-4.0

.. _function-objects:

****************
Function objects
****************

SYCL provides a number of function objects in the ``sycl`` namespace on
host and device. All function objects obey C++ conversion and promotion
rules. Each function object is additionally specialized for ``void`` as
a transparent function object that deduces its parameter types and
return type.

.. seealso:: |SYCL_SPEC_FUNCTION_OBJECTS|.

::

  namespace sycl {

  template <typename T = void> struct plus {
    T operator()(const T& x, const T& y) const;
  };

  template <typename T = void> struct multiplies {
    T operator()(const T& x, const T& y) const;
  };

  template <typename T = void> struct bit_and {
    T operator()(const T& x, const T& y) const;
  };

  template <typename T = void> struct bit_or {
    T operator()(const T& x, const T& y) const;
  };

  template <typename T = void> struct bit_xor {
    T operator()(const T& x, const T& y) const;
  };

  template <typename T = void> struct logical_and {
    T operator()(const T& x, const T& y) const;
  };

  template <typename T = void> struct logical_or {
    T operator()(const T& x, const T& y) const;
  };

  template <typename T = void> struct minimum {
    T operator()(const T& x, const T& y) const;
  };

  template <typename T = void> struct maximum {
    T operator()(const T& x, const T& y) const;
  };

  } // namespace sycl

================
Member functions
================

``plus``
========

::

  T operator()(const T& x, const T& y) const

Returns the sum of its arguments, equivalent to ``x + y``.

``multiplies``
==============

::

  T operator()(const T& x, const T& y) const

Returns the product of its arguments, equivalent to ``x * y``.

``bit_and``
===========

::

  T operator()(const T& x, const T& y) const

Returns the bitwise AND of its arguments, equivalent to ``x & y``.

``bit_or``
==========

::

  T operator()(const T& x, const T& y) const

Returns the bitwise OR of its arguments, equivalent to ``x | y``.

``bit_xor``
===========

::

  T operator()(const T& x, const T& y) const

Returns the bitwise XOR of its arguments, equivalent to ``x ^ y``.

``logical_and``
===============

::

  T operator()(const T& x, const T& y) const

Returns the logical AND of its arguments, equivalent to ``x && y``.

``logical_or``
==============

::

  T operator()(const T& x, const T& y) const

Returns the logical OR of its arguments, equivalent to ``x || y``.

``minimum``
===========

::

  T operator()(const T& x, const T& y) const

Returns the smaller value. Returns the first argument
when the arguments are equivalent.

``maximum``
===========

::

  T operator()(const T& x, const T& y) const

Returns the larger value. Returns the first argument
when the arguments are equivalent.
