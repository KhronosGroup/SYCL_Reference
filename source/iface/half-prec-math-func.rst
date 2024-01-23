..
  Copyright 2023 The Khronos Group Inc.
  SPDX-License-Identifier: CC-BY-4.0

.. _half-precision-math-functions:

*****************************
Half precision math functions
*****************************

In SYCL the half precision math functions are defined in the namespace
``sycl::half_precision``.
The functions that are available within this namespace are specified
in the list below.
These functions are implemented with a minimum of 10-bits of accuracy
i.e. the maximum error is less than or equal to ``8192 ulp``.

``cos``
=======

.. rubric:: Overload 1

::

  float cos(float x);

Preconditions: The value of ``x`` must be in the range [-216, +216].

Returns: The cosine of ``x``.

.. rubric:: Overload 2

::

  template<typename NonScalar>
  /*return-type*/ cos(NonScalar x);

Constraints: Available only if all of the following conditions are met:

* ``NonScalar`` is ``marray``, ``vec``, or the ``__swizzled_vec__`` type; and

* The element type is ``float``.

Preconditions: The value of each element of ``x`` must be in
the range [-216, +216].

Returns: For each element of ``x``, the cosine of ``x[i]``.

The return type is ``NonScalar`` unless ``NonScalar`` is the
``__swizzled_vec__`` type, in which case the return type
is the corresponding ``vec``.

``divide``
==========

.. rubric:: Overload 1

::

  float divide(float x, float y);

Returns: The value ``x / y``.

.. rubric:: Overload 2

::

  template<typename NonScalar1, typename NonScalar2>
  /*return-type*/ divide(NonScalar1 x, NonScalar2 y);

Constraints: Available only if all of the following conditions are met:

* ``NonScalar`` is ``marray``, ``vec``, or the ``__swizzled_vec__`` type; and

* The element type is ``float``.

Returns: For each element of ``x`` and ``y``, the value ``x[i] / y[i]``.

The return type is ``NonScalar`` unless ``NonScalar`` is the
``__swizzled_vec__`` type, in which case the return type
is the corresponding ``vec``.

``exp``
=======

.. rubric:: Overload 1

::

  float exp(float x);

Returns: The base-e exponential of ``x``.

.. rubric:: Overload 2

::

  template<typename NonScalar>
  /*return-type*/ exp(NonScalar x);

Constraints: Available only if all of the following conditions are met:

* ``NonScalar`` is ``marray``, ``vec``, or the ``__swizzled_vec__`` type; and

* The element type is ``float``.

Returns: For each element of ``x``, the base-e exponential of ``x[i]``.

The return type is ``NonScalar`` unless ``NonScalar`` is the
``__swizzled_vec__`` type, in which case the return type
is the corresponding ``vec``.

``exp2``
========

.. rubric:: Overload 1

::

  float exp2(float x);

Returns: The base-2 exponential of ``x``.

.. rubric:: Overload 2

::

  template<typename NonScalar>
  /*return-type*/ exp2(NonScalar x);

Constraints: Available only if all of the following conditions are met:

* ``NonScalar`` is ``marray``, ``vec``, or the ``__swizzled_vec__`` type; and

* The element type is ``float``.

Returns: For each element of ``x``, the base-2 exponential of ``x[i]``.

The return type is ``NonScalar`` unless ``NonScalar`` is the
``__swizzled_vec__`` type, in which case the return type
is the corresponding ``vec``.

``exp10``
=========

.. rubric:: Overload 1

::

  float exp10(float x);

Returns: The base-10 exponential of ``x``.

.. rubric:: Overload 2

::

  template<typename NonScalar>
  /*return-type*/ exp10(NonScalar x);

Constraints: Available only if all of the following conditions are met:

* ``NonScalar`` is ``marray``, ``vec``, or the ``__swizzled_vec__`` type; and

* The element type is ``float``.

Returns: For each element of ``x``, the base-10 exponential of ``x[i]``.

The return type is ``NonScalar`` unless ``NonScalar`` is the
``__swizzled_vec__`` type, in which case the return type
is the corresponding ``vec``.

``log``
=======

.. rubric:: Overload 1

::

  float log(float x);

Returns: The natural logarithm of ``x``.

.. rubric:: Overload 2

::

  template<typename NonScalar>
  /*return-type*/ log(NonScalar x);

Constraints: Available only if all of the following conditions are met:

* ``NonScalar`` is ``marray``, ``vec``, or the ``__swizzled_vec__`` type; and

* The element type is ``float``.

Returns: For each element of ``x``, the natural logarithm of ``x[i]``.

The return type is ``NonScalar`` unless ``NonScalar`` is the
``__swizzled_vec__`` type, in which case the return type
is the corresponding ``vec``.

``log2``
========

.. rubric:: Overload 1

::

  float log2(float x);

Returns: The base 2 logarithm of ``x``.

.. rubric:: Overload 2

::

  template<typename NonScalar>
  /*return-type*/ log2(NonScalar x);

Constraints: Available only if all of the following conditions are met:

* ``NonScalar`` is ``marray``, ``vec``, or the ``__swizzled_vec__`` type; and

* The element type is ``float``.

Returns: For each element of ``x``, the base 2 logarithm of ``x[i]``.

The return type is ``NonScalar`` unless ``NonScalar`` is the
``__swizzled_vec__`` type, in which case the return type
is the corresponding ``vec``.

``log10``
=========

::

  float log10(float x)                (1)

  template<typename NonScalar>        (2)
  /*return-type*/ log10(NonScalar x)

.. rubric:: Overload 1

::

  float log10(float x);

Returns: The base 10 logarithm of ``x``.

.. rubric:: Overload 2

::

  template<typename NonScalar>
  /*return-type*/ log10(NonScalar x);

Constraints: Available only if all of the following conditions are met:

* ``NonScalar`` is ``marray``, ``vec``, or the ``__swizzled_vec__`` type; and

* The element type is ``float``.

Returns: For each element of ``x``, the base 10 logarithm of ``x[i]``.

The return type is ``NonScalar`` unless ``NonScalar`` is the
``__swizzled_vec__`` type, in which case the return type
is the corresponding ``vec``.

``powr``
========

.. rubric:: Overload 1

::

  float powr(float x, float y);

Preconditions: The value of ``x`` must be greater than or equal to zero.

Returns: The value of ``x`` raised to the power ``y``.

.. rubric:: Overload 2

::

  template<typename NonScalar1, typename NonScalar2>
  /*return-type*/ powr(NonScalar1 x, NonScalar2 y);

Constraints: Available only if all of the following conditions are met:

* ``NonScalar`` is ``marray``, ``vec``, or the ``__swizzled_vec__`` type; and

* The element type is ``float``.

Preconditions: Each element of ``x`` must be greater than or equal to zero.

Returns: For each element of ``x`` and ``y``, the value of
``x[i]`` raised to the power ``y[i]``.

The return type is ``NonScalar`` unless ``NonScalar`` is the
``__swizzled_vec__`` type, in which case the return type
is the corresponding ``vec``.

``recip``
=========

.. rubric:: Overload 1

::

  float recip(float x);

Returns: The reciprocal of ``x``.

.. rubric:: Overload 2

::

  template<typename NonScalar>
  /*return-type*/ recip(NonScalar x);

Constraints: Available only if all of the following conditions are met:

* ``NonScalar`` is ``marray``, ``vec``, or the ``__swizzled_vec__`` type; and

* The element type is ``float``.

Returns: For each element of ``x``, the reciprocal of ``x[i]``.

The return type is ``NonScalar`` unless ``NonScalar`` is the
``__swizzled_vec__`` type, in which case the return type
is the corresponding ``vec``.

``rsqrt``
=========

.. rubric:: Overload 1

::

  float rsqrt(float x);

Returns: The inverse square root of ``x``.

.. rubric:: Overload 2

::

  template<typename NonScalar>
  /*return-type*/ rsqrt(NonScalar x);

Constraints: Available only if all of the following conditions are met:

* ``NonScalar`` is ``marray``, ``vec``, or the ``__swizzled_vec__`` type; and

* The element type is ``float``.

Returns: For each element of ``x``, the inverse square root of ``x[i]``.

The return type is ``NonScalar`` unless ``NonScalar`` is the
``__swizzled_vec__`` type, in which case the return type
is the corresponding ``vec``.

``sin``
=======

.. rubric:: Overload 1

::

  float sin(float x);

Preconditions: The value of ``x`` must be in the range [-216, +216].

Returns: The sine of ``x``.

.. rubric:: Overload 2

::

  template<typename NonScalar>
  /*return-type*/ sin(NonScalar x);

Constraints: Available only if all of the following conditions are met:

* ``NonScalar`` is ``marray``, ``vec``, or the ``__swizzled_vec__`` type; and

* The element type is ``float``.

Preconditions: The value of each element of ``x`` must be in the
range [-216, +216].

Returns: For each element of ``x``, the sine of ``x[i]``.

The return type is ``NonScalar`` unless ``NonScalar`` is the
``__swizzled_vec__`` type, in which case the return type
is the corresponding ``vec``.

``sqrt``
========

.. rubric:: Overload 1

::

 float sqrt(float x);

Returns: The square root of ``x``.

.. rubric:: Overload 2

::

  template<typename NonScalar>
  /*return-type*/ sqrt(NonScalar x);

Constraints: Available only if all of the following conditions are met:

* ``NonScalar`` is ``marray``, ``vec``, or the ``__swizzled_vec__`` type; and

* The element type is ``float``.

Returns: For each element of ``x``, the square root of ``x[i]``.

The return type is ``NonScalar`` unless ``NonScalar`` is the
``__swizzled_vec__`` type, in which case the return type
is the corresponding ``vec``.

``tan``
=======

::

  float tan(float x)                (1)

  template<typename NonScalar>      (2)
  /*return-type*/ tan(NonScalar x)

.. rubric:: Overload 1

::

  float tan(float x);

Preconditions: The value of ``x`` must be in the range [-216, +216].

Returns: The tangent of ``x``.

.. rubric:: Overload 2

::

  template<typename NonScalar>
  /*return-type*/ tan(NonScalar x);

Constraints: Available only if all of the following conditions are met:

* ``NonScalar`` is ``marray``, ``vec``, or the ``__swizzled_vec__`` type; and

* The element type is ``float``.

Preconditions: The value of each element of ``x`` must be in the
range [-216, +216].

Returns: For each element of ``x``, the tangent of ``x[i]``.

The return type is ``NonScalar`` unless ``NonScalar`` is the
``__swizzled_vec__`` type, in which case the return type
is the corresponding ``vec``.
