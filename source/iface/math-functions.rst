..
  Copyright 2023 The Khronos Group Inc.
  SPDX-License-Identifier: CC-BY-4.0

.. _math-functions:

**************
Math functions
**************

In SYCL the OpenCL math functions are available in the
namespace ``sycl`` on host and device with the same precision
guarantees as defined in the OpenCL 1.2 specification document
for host and device.

For a SYCL platform the numerical requirements
for host need to match the numerical requirements of the OpenCL
math built-in functions.

The function descriptions use the term writable
address space to represent the following address spaces:

* ``sycl::access::address_space::global_space``;
* ``sycl::access::address_space::local_space``;
* ``sycl::access::address_space::private_space``;
* ``sycl::access::address_space::generic_space``.

.. seealso:: |SYCL_SPEC_MATH_FUNCTIONS|

==============
``sycl::acos``
==============

.. rubric:: Overloads 1-3

::

  float acos(float x);
  double acos(double x);
  half acos(half x);

Returns the inverse cosine of ``x``.

.. rubric:: Overload 4

::

  template<typename NonScalar>
  /*return-type*/ acos(NonScalar x);

Available only if all of the following conditions are met:

* ``NonScalar`` is ``sycl::marray``, ``sycl::vec``, or the
  ``__swizzled_vec__`` type;
* The element type is ``float``, ``double``, or ``half``.

Returns the inverse cosine of ``x[i]`` for each element of ``x``.

The return type is ``NonScalar`` unless ``NonScalar`` is the
``__swizzled_vec__`` type, in which case the return type is the
corresponding ``sycl::vec``.

===============
``sycl::acosh``
===============

.. rubric:: Overloads 1-3

::

  float acosh(float x);
  double acosh(double x);
  half acosh(half x);

Returns the inverse hyperbolic cosine of ``x``.

.. rubric:: Overload 4

::

  template<typename NonScalar>
  /*return-type*/ acosh(NonScalar x);

Available only if all of the following conditions are met:

* ``NonScalar`` is ``sycl::marray``, ``sycl::vec``, or the
  ``__swizzled_vec__`` type;
* The element type is ``float``, ``double``, or ``half``.

Returns the inverse hyperbolic cosine of ``x[i]`` for each element of ``x``.

The return type is ``NonScalar`` unless ``NonScalar`` is the
``__swizzled_vec__`` type, in which case the return type is the
corresponding ``sycl::vec``.

================
``sycl::acospi``
================

.. rubric:: Overloads 1-3

::

  float acospi(float x);
  double acospi(double x);
  half acospi(half x);

Returns the value ``acos(x) / π``.

.. rubric:: Overload 4

::

  template<typename NonScalar>
  /*return-type*/ acospi(NonScalar x);

Available only if all of the following conditions are met:

* ``NonScalar`` is ``sycl::marray``, ``sycl::vec``, or the
  ``__swizzled_vec__`` type;
* The element type is ``float``, ``double``, or ``half``.

Returns the value ``acos(x[i]) / π`` for each element of ``x``.

The return type is ``NonScalar`` unless ``NonScalar`` is the
``__swizzled_vec__`` type, in which case the return type is the
corresponding ``sycl::vec``.



==============
``sycl::asin``
==============

.. rubric:: Overloads 1-3

::

  float asin(float x);
  double asin(double x);
  half asin(half x);

Returns the inverse sine of ``x``.

.. rubric:: Overload 4

::

  template<typename NonScalar>
  /*return-type*/ asin(NonScalar x);

Available only if all of the following conditions are met:

* ``NonScalar`` is ``sycl::marray``, ``sycl::vec``, or the
  ``__swizzled_vec__`` type;
* The element type is ``float``, ``double``, or ``half``.

Returns the inverse sine of ``x[i]`` for each element of ``x``.

The return type is ``NonScalar`` unless ``NonScalar`` is the
``__swizzled_vec__`` type, in which case the return type is the
corresponding ``sycl::vec``.

===============
``sycl::asinh``
===============

.. rubric:: Overloads 1-3

::

  float asinh(float x);
  double asinh(double x);
  half asinh(half x);

Returns the inverse hyperbolic sine of ``x``.

.. rubric:: Overload 4

::

  template<typename NonScalar>
  /*return-type*/ asinh(NonScalar x);

Available only if all of the following conditions are met:

* ``NonScalar`` is ``sycl::marray``, ``sycl::vec``, or the
  ``__swizzled_vec__`` type;
* The element type is ``float``, ``double``, or ``half``.

Returns the inverse hyperbolic sine of ``x[i]`` for each element of ``x``.

The return type is ``NonScalar`` unless ``NonScalar`` is the
``__swizzled_vec__`` type, in which case the return type is the
corresponding ``sycl::vec``.

================
``sycl::asinpi``
================

.. rubric:: Overloads 1-3

::

  float asinpi(float x);
  double asinpi(double x);
  half asinpi(half x);

Returns the value ``asin(x) / π``.

.. rubric:: Overload 4

::

  template<typename NonScalar>
  /*return-type*/ asinpi(NonScalar x);

Available only if all of the following conditions are met:

* ``NonScalar`` is ``sycl::marray``, ``sycl::vec``, or the
  ``__swizzled_vec__`` type;
* The element type is ``float``, ``double``, or ``half``.

Returns the value ``asin(x[i]) / π`` for each element of ``x``.

The return type is ``NonScalar`` unless ``NonScalar`` is the
``__swizzled_vec__`` type, in which case the return type is the
corresponding ``sycl::vec``.

==============
``sycl::atan``
==============

.. rubric:: Overloads 1-3

::

  float atan(float y_over_x);
  double atan(double y_over_x);
  half atan(half y_over_x);

Returns the inverse tangent of the input.

.. rubric:: Overload 4

::

  template<typename NonScalar>
  /*return-type*/ atan(NonScalar y_over_x);

Available only if all of the following conditions are met:

* ``NonScalar`` is ``sycl::marray``, ``sycl::vec``, or the
  ``__swizzled_vec__`` type;
* The element type is ``float``, ``double``, or ``half``.

Returns the inverse tangent of the element for each element
of the input.

The return type is ``NonScalar`` unless ``NonScalar`` is the
``__swizzled_vec__`` type, in which case the return type is the
corresponding ``sycl::vec``.

===============
``sycl::atan2``
===============

.. rubric:: Overloads 1-3

::

  float atan2(float y, float x);
  double atan2(double y, double x);
  half atan2(half y, half x);

Returns the inverse tangent of ``y / x``.

.. rubric:: Overload 4

::

  template<typename NonScalar1, typename NonScalar2>
  /*return-type*/ atan2(NonScalar1 y, NonScalar2 x);

Available only if all of the following conditions are met:

* One of the following conditions must hold for ``NonScalar1``
  and ``NonScalar2``:

  * Both ``NonScalar1`` and ``NonScalar2`` are ``sycl::marray``; or
  * ``NonScalar1`` and ``NonScalar2`` are any combination of ``sycl::vec``
    and the ``__swizzled_vec__`` type;
* ``NonScalar1`` and ``NonScalar2`` have the same number of elements;
* ``NonScalar1`` and ``NonScalar2`` have the same element type;
* The element type of ``NonScalar1`` and ``NonScalar2`` is
  ``float``, ``double``, or ``half``.

Returns the inverse tangent of ``y[i] / x[i]`` for each element
of ``x`` and ``y``.

The return type is ``NonScalar1`` unless ``NonScalar1`` is the
``__swizzled_vec__`` type, in which case the return type is the
corresponding ``sycl::vec``.

================
``sycl::atanh``
================

.. rubric:: Overloads 1-3

::

  float atanh(float x);
  double atanh(double x);
  half atanh(half x);

Returns the hyperbolic inverse tangent of ``x``.

.. rubric:: Overload 4

::

  template<typename NonScalar>
  /*return-type*/ atanh(NonScalar x);

Available only if all of the following conditions are met:

* ``NonScalar`` is ``sycl::marray``, ``sycl::vec``, or the
  ``__swizzled_vec__`` type;
* The element type is ``float``, ``double``, or ``half``.

Returns the hyperbolic inverse tangent of ``x[i]`` for each
element of ``x``.

The return type is ``NonScalar`` unless ``NonScalar`` is the
``__swizzled_vec__`` type, in which case the return type is the
corresponding ``sycl::vec``.

================
``sycl::atanpi``
================

.. rubric:: Overloads 1-3

::

  float atanpi(float x);
  double atanpi(double x);
  half atanpi(half x);

Returns the value ``atan(x) / π``.

.. rubric:: Overload 4

::

  template<typename NonScalar>
  /*return-type*/ atanpi(NonScalar x);

Available only if all of the following conditions are met:

* ``NonScalar`` is ``sycl::marray``, ``sycl::vec``, or the
  ``__swizzled_vec__`` type;
* The element type is ``float``, ``double``, or ``half``.

Returns the value ``atan(x[i]) / π`` for each element of ``x``.

The return type is ``NonScalar`` unless ``NonScalar`` is the
``__swizzled_vec__`` type, in which case the return type is the
corresponding ``sycl::vec``.

=================
``sycl::atan2pi``
=================

.. rubric:: Overloads 1-3

::

  float atan2pi(float y, float x);
  double atan2pi(double y, double x);
  half atan2pi(half y, half x);

Returns the value ``atan2(y, x) / π``.

.. rubric:: Overload 4

::

  template<typename NonScalar1, typename NonScalar2>
  /*return-type*/ atan2pi(NonScalar1 y, NonScalar2 x);

Available only if all of the following conditions are met:

* One of the following conditions must hold for ``NonScalar1``
  and ``NonScalar2``:

  * Both ``NonScalar1`` and ``NonScalar2`` are ``sycl::marray``; or
  * ``NonScalar1`` and ``NonScalar2`` are any combination of ``sycl::vec``
    and the ``__swizzled_vec__`` type;
* ``NonScalar1`` and ``NonScalar2`` have the same number of elements;
* ``NonScalar1`` and ``NonScalar2`` have the same element type;
* The element type of ``NonScalar1`` and ``NonScalar2`` is
  ``float``, ``double``, or ``half``.

Returns the value ``atan2(y[i], x[i]) / π`` for each element
of ``x`` and ``y``.

The return type is ``NonScalar1`` unless ``NonScalar1`` is the
``__swizzled_vec__`` type, in which case the return type is the
corresponding ``sycl::vec``.

==============
``sycl::cbrt``
==============

.. rubric:: Overloads 1-3

::

  float cbrt(float x);
  double cbrt(double x);
  half cbrt(half x);

Returns the cube-root of ``x``.

.. rubric:: Overload 4

::

  template<typename NonScalar>
  /*return-type*/ cbrt(NonScalar x);

Available only if all of the following conditions are met:

* ``NonScalar`` is ``sycl::marray``, ``sycl::vec``, or the
  ``__swizzled_vec__`` type;
* The element type is ``float``, ``double``, or ``half``.

Returns the cube-root of ``x[i]`` for each element of ``x``.

The return type is ``NonScalar`` unless ``NonScalar`` is the
``__swizzled_vec__`` type, in which case the return type is the
corresponding ``sycl::vec``.

==============
``sycl::ceil``
==============

.. rubric:: Overloads 1-3

::

  float ceil(float x);
  double ceil(double x);
  half ceil(half x);

Returns the value ``x`` rounded to an integral value
using the round to positive infinity rounding mode.

.. rubric:: Overload 4

::

  template<typename NonScalar>
  /*return-type*/ ceil(NonScalar x);

Available only if all of the following conditions are met:

* ``NonScalar`` is ``sycl::marray``, ``sycl::vec``, or the
  ``__swizzled_vec__`` type;
* The element type is ``float``, ``double``, or ``half``.

Returns the value ``x[i]`` rounded to an integral value
using the round to positive infinity rounding mode for
each element of ``x``.

The return type is ``NonScalar`` unless ``NonScalar`` is the
``__swizzled_vec__`` type, in which case the return type is the
corresponding ``sycl::vec``.

==================
``sycl::copysign``
==================

.. rubric:: Overloads 1-3

::

  float copysign(float x, float y);
  double copysign(double x, double y);
  half copysign(half x, half y);

Returns the value of ``x`` with its sign changed
to match the sign of ``y``.

.. rubric:: Overload 4

::

  template<typename NonScalar1, typename NonScalar2>
  /*return-type*/ copysign(NonScalar1 x, NonScalar2 y);

Available only if all of the following conditions are met:

* One of the following conditions must hold for ``NonScalar1``
  and ``NonScalar2``:

  * Both ``NonScalar1`` and ``NonScalar2`` are ``sycl::marray``; or
  * ``NonScalar1`` and ``NonScalar2`` are any combination of ``sycl::vec``
    and the ``__swizzled_vec__`` type;
* ``NonScalar1`` and ``NonScalar2`` have the same number of elements;
* ``NonScalar1`` and ``NonScalar2`` have the same element type;
* The element type of ``NonScalar1`` and ``NonScalar2`` is
  ``float``, ``double``, or ``half``.

Returns the value of ``x[i]`` with its sign changed to match the sign
of ``y[i]`` for each element of ``x`` and ``y``.

The return type is ``NonScalar1`` unless ``NonScalar1`` is the
``__swizzled_vec__`` type, in which case the return type is the
corresponding ``sycl::vec``.

=============
``sycl::cos``
=============

.. rubric:: Overloads 1-3

::

  float cos(float x);
  double cos(double x);
  half cos(half x);

Returns the cosine of ``x``.

.. rubric:: Overload 4

::

  template<typename NonScalar>
  /*return-type*/ cos(NonScalar x);

Available only if all of the following conditions are met:

* ``NonScalar`` is ``sycl::marray``, ``sycl::vec``, or the
  ``__swizzled_vec__`` type;
* The element type is ``float``, ``double``, or ``half``.

Returns the cosine of ``x[i]`` for each element of ``x``.

The return type is ``NonScalar`` unless ``NonScalar`` is the
``__swizzled_vec__`` type, in which case the return type is the
corresponding ``sycl::vec``.

==============
``sycl::cosh``
==============

.. rubric:: Overloads 1-3

::

  float cosh(float x);
  double cosh(double x);
  half cosh(half x);

Returns the hyperbolic cosine of ``x``.

.. rubric:: Overload 4

::

  template<typename NonScalar>
  /*return-type*/ cosh(NonScalar x);

Available only if all of the following conditions are met:

* ``NonScalar`` is ``sycl::marray``, ``sycl::vec``, or the
  ``__swizzled_vec__`` type;
* The element type is ``float``, ``double``, or ``half``.

Returns the hyperbolic cosine of ``x[i]`` for each
element of ``x``.

The return type is ``NonScalar`` unless ``NonScalar`` is the
``__swizzled_vec__`` type, in which case the return type is the
corresponding ``sycl::vec``.

===============
``sycl::cospi``
===============

.. rubric:: Overloads 1-3

::

  float cospi(float x);
  double cospi(double x);
  half cospi(half x);

Returns the value ``cos(π * x)``.

.. rubric:: Overload 4

::

  template<typename NonScalar>
  /*return-type*/ cospi(NonScalar x);

Available only if all of the following conditions are met:

* ``NonScalar`` is ``sycl::marray``, ``sycl::vec``, or the
  ``__swizzled_vec__`` type;
* The element type is ``float``, ``double``, or ``half``.

Returns the value ``cos(π * x[i])`` for each element of ``x``.

The return type is ``NonScalar`` unless ``NonScalar`` is the
``__swizzled_vec__`` type, in which case the return type is the
corresponding ``sycl::vec``.

==============
``sycl::erfc``
==============

.. rubric:: Overloads 1-3

::

  float erfc(float x);
  double erfc(double x);
  half erfc(half x);

Returns the complementary error function of ``x``.

.. rubric:: Overload 4

::

  template<typename NonScalar>
  /*return-type*/ erfc(NonScalar x);

Available only if all of the following conditions are met:

* ``NonScalar`` is ``sycl::marray``, ``sycl::vec``, or the
  ``__swizzled_vec__`` type;
* The element type is ``float``, ``double``, or ``half``.

Returns the complementary error function of ``x[i]`` for
each element of ``x``.

The return type is ``NonScalar`` unless ``NonScalar`` is the
``__swizzled_vec__`` type, in which case the return type is the
corresponding ``sycl::vec``.

=============
``sycl::erf``
=============

.. rubric:: Overloads 1-3

::

  float erf(float x);
  double erf(double x);
  half erf(half x);

Returns the error function of ``x`` (encountered in
integrating the normal distribution).

.. rubric:: Overload 4

::

  template<typename NonScalar>
  /*return-type*/ erf(NonScalar x);

Available only if all of the following conditions are met:

* ``NonScalar`` is ``sycl::marray``, ``sycl::vec``, or the
  ``__swizzled_vec__`` type;
* The element type is ``float``, ``double``, or ``half``.

Returns the error function of ``x[i]`` for
each element of ``x``.

The return type is ``NonScalar`` unless ``NonScalar`` is the
``__swizzled_vec__`` type, in which case the return type is the
corresponding ``sycl::vec``.

=============
``sycl::exp``
=============

.. rubric:: Overloads 1-3

::

  float exp(float x);
  double exp(double x);
  half exp(half x);

Returns the base-e exponential of ``x``.

.. rubric:: Overload 4

::

  template<typename NonScalar>
  /*return-type*/ exp(NonScalar x);

Available only if all of the following conditions are met:

* ``NonScalar`` is ``sycl::marray``, ``sycl::vec``, or the
  ``__swizzled_vec__`` type;
* The element type is ``float``, ``double``, or ``half``.

Returns the base-e exponential of ``x[i]`` for
each element of ``x``.

The return type is ``NonScalar`` unless ``NonScalar`` is the
``__swizzled_vec__`` type, in which case the return type is the
corresponding ``sycl::vec``.

==============
``sycl::exp2``
==============

.. rubric:: Overloads 1-3

::

  float exp2(float x);
  double exp2(double x);
  half exp2(half x);

Returns the base-2 exponential of ``x``.

.. rubric:: Overload 4

::

  template<typename NonScalar>
  /*return-type*/ exp2(NonScalar x);

Available only if all of the following conditions are met:

* ``NonScalar`` is ``sycl::marray``, ``sycl::vec``, or the
  ``__swizzled_vec__`` type;
* The element type is ``float``, ``double``, or ``half``.

Returns the base-2 exponential of ``x[i]`` for
each element of ``x``.

The return type is ``NonScalar`` unless ``NonScalar`` is the
``__swizzled_vec__`` type, in which case the return type is the
corresponding ``sycl::vec``.

===============
``sycl::exp10``
===============

.. rubric:: Overloads 1-3

::

  float exp10(float x);
  double exp10(double x);
  half exp10(half x);

Returns the base-10 exponential of ``x``.

.. rubric:: Overload 4

::

  template<typename NonScalar>
  /*return-type*/ exp10(NonScalar x);

Available only if all of the following conditions are met:

* ``NonScalar`` is ``sycl::marray``, ``sycl::vec``, or the
  ``__swizzled_vec__`` type;
* The element type is ``float``, ``double``, or ``half``.

Returns the base-10 exponential of ``x[i]`` for
each element of ``x``.

The return type is ``NonScalar`` unless ``NonScalar`` is the
``__swizzled_vec__`` type, in which case the return type is the
corresponding ``sycl::vec``.

===============
``sycl::expm1``
===============

.. rubric:: Overloads 1-3

::

  float expm1(float x);
  double expm1(double x);
  half expm1(half x);

Returns the value :math:`e^x - 1.0`.

.. rubric:: Overload 4

::

  template<typename NonScalar>
  /*return-type*/ expm1(NonScalar x);

Available only if all of the following conditions are met:

* ``NonScalar`` is ``sycl::marray``, ``sycl::vec``, or the
  ``__swizzled_vec__`` type;
* The element type is ``float``, ``double``, or ``half``.

Returns the value :math:`e^{x[i]} - 1.0` for
each element of ``x``.

The return type is ``NonScalar`` unless ``NonScalar`` is the
``__swizzled_vec__`` type, in which case the return type is the
corresponding ``sycl::vec``.

==============
``sycl::fabs``
==============

.. rubric:: Overloads 1-3

::

  float fabs(float x);
  double fabs(double x);
  half fabs(half x);

Returns the absolute value of ``x``.

.. rubric:: Overload 4

::

  template<typename NonScalar>
  /*return-type*/ fabs(NonScalar x);

Available only if all of the following conditions are met:

* ``NonScalar`` is ``sycl::marray``, ``sycl::vec``, or the
  ``__swizzled_vec__`` type;
* The element type is ``float``, ``double``, or ``half``.

Returns the absolute value of ``x[i]`` for
each element of ``x``.

The return type is ``NonScalar`` unless ``NonScalar`` is the
``__swizzled_vec__`` type, in which case the return type is the
corresponding ``sycl::vec``.

==============
``sycl::fdim``
==============

.. rubric:: Overloads 1-3

::

  float fdim(float x, float y);
  double fdim(double x, double y);
  half fdim(half x, half y);

Returns the value ``x - y`` if ``x > y``, otherwise ``+0``.

.. rubric:: Overload 4

::

  template<typename NonScalar1, typename NonScalar2>
  /*return-type*/ fdim(NonScalar1 x, NonScalar2 y);

Available only if all of the following conditions are met:

* One of the following conditions must hold for ``NonScalar1``
  and ``NonScalar2``:

  * Both ``NonScalar1`` and ``NonScalar2`` are ``sycl::marray``; or
  * ``NonScalar1`` and ``NonScalar2`` are any combination of ``sycl::vec``
    and the ``__swizzled_vec__`` type;
* ``NonScalar1`` and ``NonScalar2`` have the same number of elements;
* ``NonScalar1`` and ``NonScalar2`` have the same element type;
* The element type of ``NonScalar1`` and ``NonScalar2`` is
  ``float``, ``double``, or ``half``.

Returns the value ``x[i] - y[i]`` if ``x[i] > y[i]``, otherwise ``+0``
for each element of ``x`` and ``y``.

The return type is ``NonScalar1`` unless ``NonScalar1`` is the
``__swizzled_vec__`` type, in which case the return type is the
corresponding ``sycl::vec``.

===============
``sycl::floor``
===============

.. rubric:: Overloads 1-3

::

  float floor(float x);
  double floor(double x);
  half floor(half x);

Returns the value ``x`` rounded to an integral value using
the round to negative infinity rounding mode.

.. rubric:: Overload 4

::

  template<typename NonScalar>
  /*return-type*/ floor(NonScalar x);

Available only if all of the following conditions are met:

* ``NonScalar`` is ``sycl::marray``, ``sycl::vec``, or the
  ``__swizzled_vec__`` type;
* The element type is ``float``, ``double``, or ``half``.

Returns the value x[i] rounded to an integral value using
the round to negative infinity rounding mode for
each element of ``x``.

The return type is ``NonScalar`` unless ``NonScalar`` is the
``__swizzled_vec__`` type, in which case the return type is the
corresponding ``sycl::vec``.

=============
``sycl::fma``
=============

.. rubric:: Overloads 1-3

::

  float fma(float a, float b, float c);
  double fma(double a, double b, double c);
  half fma(half a, half b, half c);

Returns the correctly rounded floating-point representation
of the sum of ``c`` with the infinitely precise product of
``a`` and ``b``. Rounding of intermediate products shall not
occur. Edge case behavior is per the IEEE 754-2008 standard.

.. rubric:: Overload 4

::

  template<typename NonScalar1, typename NonScalar2>
  /*return-type*/ fdim(NonScalar1 y, NonScalar2 x);

Available only if all of the following conditions are met:

* One of the following conditions must hold for ``NonScalar1``,
  ``NonScalar2``, and ``NonScalar3``:

  * ``NonScalar1``, ``NonScalar2``, and ``NonScalar3`` are each
    ``sycl::marray``; or
  * ``NonScalar1``, ``NonScalar2``, and ``NonScalar3`` are any
    combination of ``sycl::vec`` and the ``__swizzled_vec__`` type;
* ``NonScalar1``, ``NonScalar2``, and ``NonScalar3`` have the same
  number of elements;
* ``NonScalar1``, ``NonScalar2``, and ``NonScalar3`` have the same
  element type;
* The element type of ``NonScalar1``, ``NonScalar2``, and ``NonScalar3``
  is ``float``, ``double``, or ``half``.

Returns the correctly rounded floating-point representation of the sum
of ``c[i]`` with the infinitely precise product of ``a[i]`` and ``b[i]``
for each element of ``a``, ``b``, and ``c``. Rounding of intermediate
products shall not occur. Edge case behavior is per the IEEE 754-2008
standard.

The return type is ``NonScalar1`` unless ``NonScalar1`` is the
``__swizzled_vec__`` type, in which case the return type is the
corresponding ``sycl::vec``.

==============
``sycl::fmax``
==============

.. rubric:: Overloads 1-3

::

  float fmax(float x, float y);
  double fmax(double x, double y);
  half fmax(half x, half y);

Returns ``y`` if ``x < y``, otherwise ``x``.

If one argument is a NaN, returns the other argument.

If both arguments are NaNs, returns a NaN.

.. rubric:: Overload 4

::

  template<typename NonScalar1, typename NonScalar2>
  /*return-type*/ fmax(NonScalar1 x, NonScalar2 y);

Available only if all of the following conditions are met:

* One of the following conditions must hold for ``NonScalar1``
  and ``NonScalar2``:

  * Both ``NonScalar1`` and ``NonScalar2`` are ``sycl::marray``; or
  * ``NonScalar1`` and ``NonScalar2`` are any combination of ``sycl::vec``
    and the ``__swizzled_vec__`` type;
* ``NonScalar1`` and ``NonScalar2`` have the same number of elements;
* ``NonScalar1`` and ``NonScalar2`` have the same element type;
* The element type of ``NonScalar1`` and ``NonScalar2`` is
  ``float``, ``double``, or ``half``.

Returns the value ``y[i]`` if ``x[i] < y[i]``, otherwise ``x[i]``,
for each element of ``x`` and ``y``. If one element is a NaN, the
result is the other element. If both elements are NaNs, the result
is NaN.

The return type is ``NonScalar1`` unless ``NonScalar1`` is the
``__swizzled_vec__`` type, in which case the return type is the
corresponding ``sycl::vec``.

.. rubric:: Overload 5

::

  template<typename NonScalar>
  /*return-type*/ fmax(NonScalar x, NonScalar::value_type y);

Available only if all of the following conditions are met:

* ``NonScalar`` is ``sycl::marray``, ``sycl::vec``, or the
  ``__swizzled_vec__`` type;
* The element type is ``float``, ``double``, or ``half``.

Returns the value ``y`` if ``x[i] < y``, otherwise ``x[i]``,
for each element of ``x``. If one value is a NaN, the result
is the other value. If both value are NaNs, the result is a NaN.

The return type is ``NonScalar`` unless ``NonScalar`` is the
``__swizzled_vec__`` type, in which case the return type is the
corresponding ``sycl::vec``.

==============
``sycl::fmin``
==============

.. rubric:: Overloads 1-3

::

  float fmin(float x, float y);
  double fmin(double x, double y);
  half fmin(half x, half y);

Returns ``y`` if ``y < x``, otherwise ``x``.

If one argument is a NaN, returns the other argument.

If both arguments are NaNs, returns a NaN.

.. rubric:: Overload 4

::

  template<typename NonScalar1, typename NonScalar2>
  /*return-type*/ fmin(NonScalar1 x, NonScalar2 y);

Available only if all of the following conditions are met:

* One of the following conditions must hold for ``NonScalar1``
  and ``NonScalar2``:

  * Both ``NonScalar1`` and ``NonScalar2`` are ``sycl::marray``; or
  * ``NonScalar1`` and ``NonScalar2`` are any combination of ``sycl::vec``
    and the ``__swizzled_vec__`` type;
* ``NonScalar1`` and ``NonScalar2`` have the same number of elements;
* ``NonScalar1`` and ``NonScalar2`` have the same element type;
* The element type of ``NonScalar1`` and ``NonScalar2`` is
  ``float``, ``double``, or ``half``.

Returns the value ``y[i]`` if ``y[i] < x[i]``, otherwise ``x[i]``,
for each element of ``x`` and ``y``. If one element is a NaN, the
result is the other element. If both elements are NaNs, the result
is NaN.

The return type is ``NonScalar1`` unless ``NonScalar1`` is the
``__swizzled_vec__`` type, in which case the return type is the
corresponding ``sycl::vec``.

.. rubric:: Overload 5

::

  template<typename NonScalar>
  /*return-type*/ fmin(NonScalar x, NonScalar::value_type y);

Available only if all of the following conditions are met:

* ``NonScalar`` is ``sycl::marray``, ``sycl::vec``, or the
  ``__swizzled_vec__`` type;
* The element type is ``float``, ``double``, or ``half``.

Returns the value ``y`` if ``y < x[i]``, otherwise ``x[i]``,
for each element of ``x``. If one value is a NaN, the result
is the other value. If both value are NaNs, the result is a NaN.

The return type is ``NonScalar`` unless ``NonScalar`` is the
``__swizzled_vec__`` type, in which case the return type is the
corresponding ``sycl::vec``.

==============
``sycl::fmod``
==============

.. rubric:: Overloads 1-3

::

  float fmod(float y, float x);
  double fmod(double y, double x);
  half fmod(half y, half x);

Returns the value ``x - y * trunc(x/y)``.

.. rubric:: Overload 4

::

  template<typename NonScalar1, typename NonScalar2>
  /*return-type*/ fmod(NonScalar1 y, NonScalar2 x);

Available only if all of the following conditions are met:

* One of the following conditions must hold for ``NonScalar1``
  and ``NonScalar2``:

  * Both ``NonScalar1`` and ``NonScalar2`` are ``sycl::marray``; or
  * ``NonScalar1`` and ``NonScalar2`` are any combination of ``sycl::vec``
    and the ``__swizzled_vec__`` type;
* ``NonScalar1`` and ``NonScalar2`` have the same number of elements;
* ``NonScalar1`` and ``NonScalar2`` have the same element type;
* The element type of ``NonScalar1`` and ``NonScalar2`` is
  ``float``, ``double``, or ``half``.

Returns the value ``x[i] - y[i] * trunc(x[i]/y[i])``
for each element of ``x`` and ``y``.

The return type is ``NonScalar1`` unless ``NonScalar1`` is the
``__swizzled_vec__`` type, in which case the return type is the
corresponding ``sycl::vec``.

===============
``sycl::fract``
===============

.. rubric:: Overloads 1-3

::

  template<typename Ptr>
  float fract(float x, Ptr iptr);

  template<typename Ptr>
  double fract(double x, Ptr iptr);

  template<typename Ptr>
  half fract(half x, Ptr iptr);

Available only if ``Ptr`` is :ref:`multi_ptr` with ``ElementType``
equal to the same type as ``x`` and with ``Space`` equal to one of
the writable address spaces as defined above.

Writes the value ``floor(x)`` to ``iptr``.

Returns the value ``fmin(x - floor(x), nextafter(T{1.0}, T{0.0}))``,
where T is the type of x.

.. rubric:: Overload 4

::

  template<typename NonScalar, typename Ptr>
  /*return-type*/ fract(NonScalar x, Ptr iptr)

Available only if all of the following conditions are met:

* ``NonScalar`` is ``sycl::marray``, ``sycl::vec``, or the
  ``__swizzled_vec__`` type with element type ``float``,
  ``double``, or ``half``;
* ``Ptr`` is :ref:`multi_ptr` with ``ElementType`` equal to
  ``NonScalar``, unless ``NonScalar`` is the ``__swizzled_vec__``
  type, in which case the ``ElementType`` is the corresponding
  ``sycl::vec``;
* ``Ptr`` is :ref:`multi_ptr` with ``Space`` equal to one of the
  writable address spaces as defined above.

Writes the value ``floor(x)`` to ``iptr``.

Returns the value
``fmin(x[i] - floor(x[i]), nextafter(T{1.0}, T{0.0}))``,
where ``T`` is the element type of ``x`` for
each element of ``x``.

The return type is ``NonScalar`` unless ``NonScalar`` is the
``__swizzled_vec__`` type, in which case the return type is the
corresponding ``sycl::vec``.

===============
``sycl::frexp``
===============

.. rubric:: Overloads 1-3

::

  template<typename Ptr>
  float frexp(float x, Ptr exp);

  template<typename Ptr>
  double frexp(double x, Ptr exp);

  template<typename Ptr>
  half frexp(half x, Ptr exp);

Available only if ``Ptr`` is :ref:`multi_ptr` with ``ElementType``
of ``int`` and with ``Space`` equal to one of the writable
address spaces as defined above.

Extracts the mantissa and exponent from ``x``. The mantissa is a
floating point number whose magnitude is in the interval ``[0.5, 1)``
or ``0``. The extracted mantissa and exponent are such that
:math:`mantissa \cdot 2^{exp}` equals ``x``. The exponent is written
to ``exp``.

Returns the mantissa of ``x``.

.. rubric:: Overload 4

::

  template<typename NonScalar, typename Ptr>
  /*return-type*/ frexp(NonScalar x, Ptr exp)

Available only if all of the following conditions are met:

* ``NonScalar`` is ``sycl::marray``, ``sycl::vec``, or the
  ``__swizzled_vec__`` type with element type ``float``,
  ``double``, or ``half``;
* ``Ptr`` is :ref:`multi_ptr` with the following ``ElementType``:

  * If ``NonScalar`` is ``sycl::marray``, ``ElementType`` is
    ``sycl::marray`` of ``int`` with the same number of
    elements as ``NonScalar``;
  * If ``NonScalar`` is ``sycl::vec`` or the ``__swizzled_vec__``
    type, ``ElementType`` is ``sycl::vec`` of ``int32_t`` with the
    same number of elements as ``NonScalar``;
* ``Ptr`` is :ref:`multi_ptr` with ``Space`` equal to one of the
  writable address spaces as defined above.

Extracts the mantissa and exponent from each element of ``x``. Each
mantissa is a floating point number whose magnitude is in the interval
``[0.5, 1)`` or ``0``. Each extracted mantissa and exponent are such
that :math:`mantissa \cdot 2^{exp}` equals ``x[i]``. The exponent of
each element of ``x`` is written to ``exp``.

Returns the mantissa of ``x[i]`` for each element of ``x``.

The return type is ``NonScalar`` unless ``NonScalar`` is the
``__swizzled_vec__`` type, in which case the return type is the
corresponding ``sycl::vec``.

===============
``sycl::hypot``
===============

.. rubric:: Overloads 1-3

::

  float hypot(float y, float x);
  double hypot(double y, double x);
  half hypot(half y, half x);

Returns the value :math:`\sqrt{x^2 + y^2}` without undue overflow
or underflow.

.. rubric:: Overload 4

::

  template<typename NonScalar1, typename NonScalar2>
  /*return-type*/ hypot(NonScalar1 y, NonScalar2 x);

Available only if all of the following conditions are met:

* One of the following conditions must hold for ``NonScalar1``
  and ``NonScalar2``:

  * Both ``NonScalar1`` and ``NonScalar2`` are ``sycl::marray``; or
  * ``NonScalar1`` and ``NonScalar2`` are any combination of ``sycl::vec``
    and the ``__swizzled_vec__`` type;
* ``NonScalar1`` and ``NonScalar2`` have the same number of elements;
* ``NonScalar1`` and ``NonScalar2`` have the same element type;
* The element type of ``NonScalar1`` and ``NonScalar2`` is
  ``float``, ``double``, or ``half``.

Returns the value :math:`\sqrt{x[i]^2 + y[i]^2}` without undue overflow
or underflow for each element of ``x`` and ``y``.

The return type is ``NonScalar1`` unless ``NonScalar1`` is the
``__swizzled_vec__`` type, in which case the return type is the
corresponding ``sycl::vec``.

===============
``sycl::ilogb``
===============

.. rubric:: Overloads 1-3

::

  int ilogb(float x);
  int ilogb(double x);
  int ilogb(half x);

Compute the integral part of :math:`log_r(|x|)` and return
the result as an integer, where ``r`` is the value returned
by ``std::numeric_limits<decltype(x)>::radix``.

.. rubric:: Overload 4

::

  template<typename NonScalar>
  /*return-type*/ ilogb(NonScalar x);

Available only if all of the following conditions are met:

* ``NonScalar`` is ``sycl::marray``, ``sycl::vec``, or the
  ``__swizzled_vec__`` type;
* The element type is ``float``, ``double``, or ``half``.

For each element of ``x``, compute the integral part of
:math:`log_r(|x[i]|)` and return the result as an integer,
where ``r`` is the value returned by
``std::numeric_limits<NonScalar::value_type)>::radix``.

The return type depends on ``NonScalar``. If ``NonScalar``
is ``sycl::marray``, the return type is ``sycl::marray`` of
``int`` with the same number of element as ``NonScalar``. If
``NonScalar`` is ``sycl::vec`` or the ``__swizzled_vec__`` type,
the return type is ``sycl::vec`` of ``int32_t`` with the same
number of elements as ``NonScalar``.

===============
``sycl::ldexp``
===============

.. rubric:: Overloads 1-3

::

  float ldexp(float x, int k);
  double ldexp(double x, int k);
  half ldexp(half x, int k);

Returns the value ``x`` multiplied by :math:`2^k`.

.. rubric:: Overload 4

::

  template<typename NonScalar1, typename NonScalar2>
  /*return-type*/ ldexp(NonScalar1 x, NonScalar2 k);

Available only if all of the following conditions are met:

* ``NonScalar1`` is ``sycl::marray``, ``sycl::vec``, or
  the ``__swizzled_vec__`` type;
* The element type of ``NonScalar1`` is ``float``,
  ``double``, or ``half``;
* If ``NonScalar1`` is ``sycl::marray``, ``NonScalar2`` is
  ``sycl::marray`` of int with the same number of elements
  as ``NonScalar1``; and
* If ``NonScalar1`` is ``sycl::vec`` or the ``__swizzled_vec__``
  type, ``NonScalar2`` is ``sycl::vec`` or the ``__swizzled_vec__``
  type of ``int32_t`` with the same number of elements as ``NonScalar1``.


Returns the value ``x[i]`` multiplied by :math:`2^{k[i]}`
for each element of ``x`` and ``k``.

The return type is ``NonScalar1`` unless ``NonScalar1`` is the
``__swizzled_vec__`` type, in which case the return type is the
corresponding ``sycl::vec``.

.. rubric:: Overload 5

::

  template<typename NonScalar>
  /*return-type*/ ldexp(NonScalar x, int k);

Available only if all of the following conditions are met:

* ``NonScalar`` is ``sycl::marray``, ``sycl::vec``, or the
  ``__swizzled_vec__`` type;
* The element type is ``float``, ``double``, or ``half``.

Returns the value ``x[i]`` multiplied by :math:`2^k`
for each element of ``x`` and ``k``.

The return type is ``NonScalar`` unless ``NonScalar`` is the
``__swizzled_vec__`` type, in which case the return type is the
corresponding ``sycl::vec``.

================
``sycl::lgamma``
================

.. rubric:: Overloads 1-3

::

  int lgamma(float x);
  int lgamma(double x);
  int lgamma(half x);

Returns the natural logarithm of the absolute
value of the gamma function of ``x``.

.. rubric:: Overload 4

::

  template<typename NonScalar>
  /*return-type*/ lgamma(NonScalar x);

Available only if all of the following conditions are met:

* ``NonScalar`` is ``sycl::marray``, ``sycl::vec``, or the
  ``__swizzled_vec__`` type;
* The element type is ``float``, ``double``, or ``half``.

Returns the natural logarithm of the absolute value of the
gamma function of ``x[i]`` for each element of ``x``.

The return type is ``NonScalar`` unless ``NonScalar`` is the
``__swizzled_vec__`` type, in which case the return type is the
corresponding ``sycl::vec``.
