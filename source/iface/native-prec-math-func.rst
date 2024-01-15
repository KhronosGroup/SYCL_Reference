..
  Copyright 2023 The Khronos Group Inc.
  SPDX-License-Identifier: CC-BY-4.0

.. _native-precision-math-functions:

*******************************
Native precision math functions
*******************************

In SYCL the implementation-defined precision math functions are defined in the
namespace ``sycl::native``. The functions that are available within this
namespace are specified in the list below.

The range of valid input values and the maximum error for these functions
is implementation defined.

``cos``
=======

::

  float cos(float x)                (1)

  template<typename NonScalar>      (2)
  /*return-type*/ cos(NonScalar x)

Overload (1):

Returns: The cosine of ``x``.

Overload (2):

Constraints: Available only if all of the following conditions are met:

NonScalar is ``marray``, ``vec``, or the ``__swizzled_vec__`` type; and

The element type is ``float``.

Returns: For each element of ``x``, the cosine of ``x[i]``.

The return type is ``NonScalar`` unless ``NonScalar`` is the
``__swizzled_vec__`` type, in which case the return type is the
corresponding ``vec``.

``divide``
==========

::

  float divide(float x, float y)                      (1)

  template<typename NonScalar1, typename NonScalar2>  (2)
  /*return-type*/ divide(NonScalar1 x, NonScalar2 y);

Overload (1):

Returns: The value ``x / y``.

Overload (2):

Constraints: Available only if all of the following conditions are met:

``NonScalar`` is ``marray``, ``vec``, or the ``__swizzled_vec__`` type; and

The element type is ``float``.

Returns: For each element of ``x`` and ``y``, the value ``x[i] / y[i]``.

The return type is ``NonScalar`` unless ``NonScalar`` is the
``__swizzled_vec__`` type, in which case the return type is the
corresponding ``vec``.

``exp``
=======

::

  float exp(float x)                (1)

  template<typename NonScalar>      (2)
  /*return-type*/ exp(NonScalar x);

Overload (1):

Returns: The base-e exponential of ``x``.

Overload (2):

Constraints: Available only if all of the following conditions are met:

``NonScalar`` is ``marray``, ``vec``, or the ``__swizzled_vec__`` type; and

The element type is ``float``.

Returns: For each element of ``x``, the base-e exponential of ``x[i]``.

The return type is ``NonScalar`` unless ``NonScalar`` is the
``__swizzled_vec__`` type, in which case the return type is the
corresponding ``vec``.

``exp2``
========

::

  float exp2(float x)                (1)

  template<typename NonScalar>       (2)
  /*return-type*/ exp2(NonScalar x)

Overload (1):

Returns: The base-2 exponential of ``x``.

Overload (2):

Constraints: Available only if all of the following conditions are met:

``NonScalar`` is ``marray``, ``vec``, or the ``__swizzled_vec__`` type; and

The element type is ``float``.

Returns: For each element of ``x``, the base-2 exponential of ``x[i]``.

The return type is ``NonScalar`` unless ``NonScalar`` is the
``__swizzled_vec__`` type, in which case the return type is the
corresponding ``vec``.

``exp10``
=========

::

  float exp10(float x)                (1)

  template<typename NonScalar>        (2)
  /*return-type*/ exp10(NonScalar x)

Overload (1):

Returns: The base-10 exponential of ``x``.

Overload (2):

Constraints: Available only if all of the following conditions are met:

``NonScalar`` is ``marray``, ``vec``, or the ``__swizzled_vec__`` type; and

The element type is ``float``.

Returns: For each element of ``x``, the base-10 exponential of ``x[i]``.

The return type is ``NonScalar`` unless ``NonScalar`` is the
``__swizzled_vec__`` type, in which case the return type is the
corresponding ``vec``.

``log``
=======

::

  float log(float x)                (1)

  template<typename NonScalar>      (2)
  /*return-type*/ log(NonScalar x)

Overload (1):

Returns: The natural logarithm of ``x``.

Overload (2):

Constraints: Available only if all of the following conditions are met:

``NonScalar`` is ``marray``, ``vec``, or the ``__swizzled_vec__`` type; and

The element type is ``float``.

Returns: For each element of ``x``, the natural logarithm of ``x[i]``.

The return type is ``NonScalar`` unless ``NonScalar`` is the
``__swizzled_vec__`` type, in which case the return type is the
corresponding ``vec``.

``log2``
========

::

  float log2(float x)                (1)

  template<typename NonScalar>       (2)
  /*return-type*/ log2(NonScalar x)

Overload (1):

Returns: The base 2 logarithm of ``x``.

Overload (2):

Constraints: Available only if all of the following conditions are met:

``NonScalar`` is ``marray``, ``vec``, or the ``__swizzled_vec__`` type; and

The element type is ``float``.

Returns: For each element of ``x``, the base 2 logarithm of ``x[i]``.

The return type is ``NonScalar`` unless ``NonScalar`` is the
``__swizzled_vec__`` type, in which case the return type is the
corresponding ``vec``.

``log10``
=========

::

  float log10(float x)                (1)

  template<typename NonScalar>        (2)
  /*return-type*/ log10(NonScalar x)

Overload (1):

Returns: The base 10 logarithm of ``x``.

Overload (2):

Constraints: Available only if all of the following conditions are met:

``NonScalar`` is ``marray``, ``vec``, or the ``__swizzled_vec__`` type; and

The element type is ``float``.

Returns: For each element of ``x``, the base 10 logarithm of ``x[i]``.

The return type is ``NonScalar`` unless ``NonScalar`` is the
``__swizzled_vec__`` type, in which case the return type is the
corresponding ``vec``.

``powr``
========

::

  float powr(float x, float y)                        (1)

  template<typename NonScalar1, typename NonScalar2>  (2)
  /*return-type*/ powr(NonScalar1 x, NonScalar2 y)

Overload (1):

Preconditions: The value of ``x`` must be greater than or equal to zero.

Returns: The value of ``x`` raised to the power ``y``.

Overload (2):

Constraints: Available only if all of the following conditions are met:

``NonScalar`` is ``marray``, ``vec``, or the ``__swizzled_vec__`` type; and

The element type is ``float``.

Preconditions: Each element of ``x`` must be greater than or equal to zero.

Returns: For each element of ``x`` and ``y``, the value of ``x[i]``
raised to the power ``y[i]``.

The return type is ``NonScalar`` unless ``NonScalar`` is the
``__swizzled_vec__`` type, in which case the return type is the
corresponding ``vec``.

``recip``
=========

::

  float recip(float x)                (1)

  template<typename NonScalar>        (2)
  /*return-type*/ recip(NonScalar x)

Overload (1):

Returns: The reciprocal of ``x``.

Overload (2):

Constraints: Available only if all of the following conditions are met:

``NonScalar`` is ``marray``, ``vec``, or the ``__swizzled_vec__`` type; and

The element type is ``float``.

Returns: For each element of ``x``, the reciprocal of ``x[i]``.

The return type is ``NonScalar`` unless ``NonScalar`` is the
``__swizzled_vec__`` type, in which case the return type is the
corresponding ``vec``.

``rsqrt``
=========

::

  float rsqrt(float x)                (1)

  template<typename NonScalar>        (2)
  /*return-type*/ rsqrt(NonScalar x)

Overload (1):

Returns: The inverse square root of ``x``.

Overload (2):

Constraints: Available only if all of the following conditions are met:

``NonScalar`` is ``marray``, ``vec``, or the ``__swizzled_vec__`` type; and

The element type is ``float``.

Returns: For each element of ``x``, the inverse square root of ``x[i]``.

The return type is ``NonScalar`` unless ``NonScalar`` is the
``__swizzled_vec__`` type, in which case the return type is the
corresponding ``vec``.

``sin``
=======

::

  float sin(float x)                (1)

  template<typename NonScalar>      (2)
  /*return-type*/ sin(NonScalar x)

Overload (1):

Returns: The sine of ``x``.

Overload (2):

Constraints: Available only if all of the following conditions are met:

``NonScalar`` is ``marray``, ``vec``, or the ``__swizzled_vec__`` type; and

The element type is ``float``.

Returns: For each element of ``x``, the sine of ``x[i]``.

The return type is ``NonScalar`` unless ``NonScalar`` is the
``__swizzled_vec__`` type, in which case the return type is the
corresponding ``vec``.

``sqrt``
========

::

  float sqrt(float x)                (1)

  template<typename NonScalar>       (2)
  /*return-type*/ sqrt(NonScalar x)

Overload (1):

Returns: The square root of ``x``.

Overload (2):

Constraints: Available only if all of the following conditions are met:

``NonScalar`` is ``marray``, ``vec``, or the ``__swizzled_vec__`` type; and

The element type is ``float``.

Returns: For each element of ``x``, the square root of ``x[i]``.

The return type is ``NonScalar`` unless ``NonScalar`` is the
``__swizzled_vec__`` type, in which case the return type is the
corresponding ``vec``.

``tan``
=======

::

  float tan(float x)                (1)

  template<typename NonScalar>      (2)
  /*return-type*/ tan(NonScalar x)

Overload (1):

Returns: The tangent of ``x``.

Overload (2):

Constraints: Available only if all of the following conditions are met:

``NonScalar`` is ``marray``, ``vec``, or the ``__swizzled_vec__`` type; and

The element type is ``float``.

Returns: For each element of ``x``, the tangent of ``x[i]``.

The return type is ``NonScalar`` unless ``NonScalar`` is the
``__swizzled_vec__`` type, in which case the return type is the
corresponding ``vec``.
