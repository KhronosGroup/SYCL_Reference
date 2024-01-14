..
  Copyright 2023 The Khronos Group Inc.
  SPDX-License-Identifier: CC-BY-4.0

.. _integer-functions:

*****************
Integer functions
*****************

The function descriptions in this section use the term
generic integer type to represent the following types:

``char``

``signed char``

``short``

``int``

``long``

``long long``

``unsigned char``

``unsigned short``

``unsigned int``

``unsigned long``

``unsigned long long``

``marray<char, N>``

``marray<signed char, N>``

``marray<short, N>``

``marray<int, N>``

``marray<long, N>``

``marray<long long, N>``

``marray<unsigned char, N>``

``marray<unsigned short, N>``

``marray<unsigned int, N>``

``marray<unsigned long, N>``

``marray<unsigned long long, N>``

``vec<int8_t, N>``

``vec<int16_t, N>``

``vec<int32_t, N>``

``vec<int64_t, N>``

``vec<uint8_t, N>``

``vec<uint16_t, N>``

``vec<uint32_t, N>``

``vec<uint64_t, N>``

``__swizzled_vec__`` that is convertible to ``vec<int8_t, N>``

``__swizzled_vec__`` that is convertible to ``vec<int16_t, N>``

``__swizzled_vec__`` that is convertible to ``vec<int32_t, N>``

``__swizzled_vec__`` that is convertible to ``vec<int64_t, N>``

``__swizzled_vec__`` that is convertible to ``vec<uint8_t, N>``

``__swizzled_vec__`` that is convertible to ``vec<uint16_t, N>``

``__swizzled_vec__`` that is convertible to ``vec<uint32_t, N>``

``__swizzled_vec__`` that is convertible to ``vec<uint64_t, N>``

=================
Integer functions
=================

In the list below described the integer math functions that are
available in the ``sycl`` namespace in both host and device code.

``abs``
=======

::

  template<typename GenInt>
  /*return-type*/ abs(GenInt x);

Constraints: Available only if ``GenInt`` is a generic integer type
as defined above.

Returns: When the input is a scalar, returns ``|x|``. Otherwise,
returns ``|x[i]|`` for each element of ``x``. The behavior is undefined
if the result cannot be represented by the return type.

The return type is ``GenInt`` unless ``GenInt`` is the
``__swizzled_vec__`` type, in which case the return
type is the corresponding ``vec``.

``abs_diff``
============

::

  template<typename GenInt1, typename GenInt2>
  /*return-type*/ abs_diff(GenInt1 x, GenInt2 y);

Constraints: Available only if all of the following conditions are met:

``GenInt1`` is a generic integer type as defined above;

If ``GenInt1`` is not ``vec`` or the ``__swizzled_vec__`` type,
then ``GenInt2`` must be the same as ``GenInt1``; and

If ``GenInt1`` is ``vec`` or the ``__swizzled_vec__`` type, then ``GenInt2``
must also be ``vec`` or the ``__swizzled_vec__`` type, and both must have the
same element type and the same number of elements.

Returns: When the inputs are scalars, returns ``|x - y|``. Otherwise, returns
``|x[i] - y[i]|`` for each element of ``x`` and ``y``. The subtraction is done
without modulo overflow. The behavior is undefined if the result cannot be
represented by the return type.

The return type is ``GenInt1`` unless ``GenInt1`` is the
``__swizzled_vec__`` type, in which case the return type is
the corresponding ``vec``.

``add_sat``
===========

::

  template<typename GenInt1, typename GenInt2>
  /*return-type*/ add_sat(GenInt1 x, GenInt2 y);

Constraints: Available only if all of the following conditions are met:

``GenInt1`` is a generic integer type as defined above;

If ``GenInt1`` is not ``vec`` or the ``__swizzled_vec__`` type,
then ``GenInt2`` must be the same as ``GenInt1``; and

If ``GenInt1`` is ``vec`` or the ``__swizzled_vec__`` type, then ``GenInt2``
must also be ``vec`` or the ``__swizzled_vec__`` type, and both must have the
same element type and the same number of elements.

Returns: When the inputs are scalars, returns ``x + y``. Otherwise,
returns ``x[i] + y[i]`` for each element of ``x`` and ``y``.
The addition operation saturates the result.

The return type is ``GenInt1`` unless ``GenInt1`` is the
``__swizzled_vec__`` type, in which case the return type is
the corresponding ``vec``.

``hadd``
========

::

  template<typename GenInt1, typename GenInt2>
  /*return-type*/ hadd(GenInt1 x, GenInt2 y);

Constraints: Available only if all of the following conditions are met:

``GenInt1`` is a generic integer type as defined above;

If ``GenInt1`` is not ``vec`` or the ``__swizzled_vec__`` type,
then ``GenInt2`` must be the same as ``GenInt1``; and

If ``GenInt1`` is ``vec`` or the ``__swizzled_vec__`` type, then ``GenInt2``
must also be ``vec`` or the ``__swizzled_vec__`` type, and both must have the
same element type and the same number of elements.

Returns: When the inputs are scalars, returns ``(x + y) >> 1``.
Otherwise, returns ``(x[i] + y[i]) >> 1`` for each element of ``x``
and ``y``. The intermediate sum does not modulo overflow.

The return type is ``GenInt1`` unless ``GenInt1`` is the
``__swizzled_vec__`` type, in which case the return type is
the corresponding ``vec``.

``rhadd``
=========

::

  template<typename GenInt1, typename GenInt2>
  /*return-type*/ rhadd(GenInt1 x, GenInt2 y);

Constraints: Available only if all of the following conditions are met:

``GenInt1`` is a generic integer type as defined above;

If ``GenInt1`` is not ``vec`` or the ``__swizzled_vec__`` type,
then ``GenInt2`` must be the same as ``GenInt1``; and

If ``GenInt1`` is ``vec`` or the ``__swizzled_vec__`` type, then ``GenInt2``
must also be ``vec`` or the ``__swizzled_vec__`` type, and both must have the
same element type and the same number of elements.

Returns: When the inputs are scalars, returns ``(x + y + 1) >> 1``.
Otherwise, returns ``(x[i] + y[i] + 1) >> 1`` for each element of
``x`` and ``y``. The intermediate sum does not modulo overflow.

The return type is ``GenInt1`` unless ``GenInt1`` is the
``__swizzled_vec__`` type, in which case the return type is
the corresponding ``vec``.

``clamp``
=========

.. rubric:: Overload 1

::

  template<typename GenInt1, typename GenInt2, typename GenInt3>
  /*return-type*/ clamp(GenInt1 x, GenInt2 minval, GenInt3 maxval);

Constraints: Available only if all of the following conditions are met:

``GenInt1`` is a generic integer type as defined above;

If ``GenInt1`` is not ``vec`` or the ``__swizzled_vec__`` type, then
``GenInt2`` and ``GenInt3`` must be the same as ``GenInt1``; and

If ``GenInt1`` is ``vec`` or the ``__swizzled_vec__`` type, then
``GenInt2`` and ``GenInt3`` must also be ``vec`` or the
``__swizzled_vec__`` type, and all three must have the same
element type and the same number of elements.

Preconditions: If the inputs are scalars, the value of ``minval``
must be less than or equal to the value of ``maxval``. If the
inputs are not scalars, each ``minval`` must be less than or
equal to the corresponding ``maxval`` value.

Returns: When the inputs are scalars, returns
``min(max(x, minval), maxval)``. Otherwise, returns
``min(max(x[i], minval[i]), maxval[i])`` for each element
of ``x``, ``minval``, and ``maxval``.

The return type is ``GenInt1`` unless ``GenInt1`` is the
``__swizzled_vec__`` type, in which case the return type is
the corresponding ``vec``.

.. rubric:: Overload 2

::

  template<typename NonScalar>
  /*return-type*/ clamp(NonScalar x, NonScalar::value_type minval,
                        NonScalar::value_type maxval);

Constraints: Available only if ``NonScalar`` is ``marray``, ``vec``,
or the ``__swizzled_vec__`` type and is a generic integer type as
defined above.

Preconditions: The value of ``minval`` must be less than or equal to
the value of ``maxval``.

Returns: ``min(max(x[i], minval), maxval)`` for each element
of ``x``.

The return type is ``NonScalar`` unless ``NonScalar`` is
the ``__swizzled_vec__`` type, in which case the return
type is the corresponding ``vec``.

``ctz``
=======

.. rubric:: Overload 1

::

  template<typename GenInt>
  /*return-type*/ clz(GenInt x);

Constraints: Available only if ``GenInt`` is a generic
integer type as defined above.

Returns: When the input is a scalar, returns the number of leading 0-bits
in ``x``, starting at the most significant bit position. Otherwise, returns
the number of leading 0-bits in each element of ``x``. When a value is 0,
the computed count is the size in bits of that value.

The return type is ``GenInt`` unless ``GenInt`` is the
``__swizzled_vec__`` type, in which case the return type is the
corresponding ``vec``.

.. rubric:: Overload 2

::

  template<typename GenInt>
  /*return-type*/ ctz(GenInt x);

Constraints: Available only if ``GenInt`` is a generic
integer type as defined above.

Returns: When the input is a scalar, returns the number of trailing 0-bits
in ``x``. Otherwise, returns the number of trailing 0-bits in each element
of ``x``. When a value is 0, the computed count is the size in bits
of that value.

The return type is ``GenInt`` unless ``GenInt`` is the
``__swizzled_vec__`` type, in which case the return type
is the corresponding ``vec``.

``mad_hi``
==========

::

  template<typename GenInt1, typename GenInt2, typename GenInt3>
  /*return-type*/ mad_hi(GenInt1 a, GenInt2 b, GenInt3 c);

Constraints: Available only if all of the following conditions are met:

``GenInt1`` is a generic integer type as defined above;

If ``GenInt1`` is not ``vec`` or the ``__swizzled_vec__`` type, then
``GenInt2`` and ``GenInt3`` must be the same as ``GenInt1``; and

If ``GenInt1`` is ``vec`` or the ``__swizzled_vec__`` type, then
``GenInt2`` and ``GenInt3`` must also be ``vec`` or the
``__swizzled_vec__`` type, and all three must have the same element
type and the same number of elements.

Returns: When the inputs are scalars, returns ``mul_hi(a, b)+c``.
Otherwise, returns ``mul_hi(a[i], b[i])+c[i]`` for each element of
``a``, ``b``, and ``c``.

The return type is ``GenInt1`` unless ``GenInt1`` is the
``__swizzled_vec__`` type, in which case the return type is the
corresponding ``vec``.

``mad_sat``
===========

::

  template<typename GenInt1, typename GenInt2, typename GenInt3>
  /*return-type*/ mad_hi(GenInt1 a, GenInt2 b, GenInt3 c);

Constraints: Available only if all of the following conditions are met:

``GenInt1`` is a generic integer type as defined above;

If ``GenInt1`` is not ``vec`` or the ``__swizzled_vec__`` type, then
``GenInt2`` and ``GenInt3`` must be the same as ``GenInt1``; and

If ``GenInt1`` is ``vec`` or the ``__swizzled_vec__`` type, then
``GenInt2`` and ``GenInt3`` must also be ``vec`` or the
``__swizzled_vec__`` type, and all three must have the same element
type and the same number of elements.

Returns: When the inputs are scalars, returns ``a * b + c``. Otherwise,
returns ``a[i] * b[i] + c[i]`` for each element of ``a``, ``b``, and
``c``. The operation saturates the result.

The return type is ``GenInt1`` unless ``GenInt1`` is the
``__swizzled_vec__`` type, in which case the return type is the
corresponding ``vec``.

``max``
=======

.. rubric:: Overload 1

::

  template<typename GenInt1, typename GenInt2>
  /*return-type*/ max(GenInt1 x, GenInt2 y);

Constraints: Available only if all of the following conditions are met:

``GenInt1`` is a generic integer type as defined above;

If ``GenInt1`` is not ``vec`` or the ``__swizzled_vec__`` type, then
``GenInt2`` must be the same as ``GenInt1``; and

If ``GenInt1`` is ``vec`` or the ``__swizzled_vec__`` type, then
``GenInt2`` must also be ``vec`` or the ``__swizzled_vec__`` type,
and both must have the same element type and the same number of elements.

Returns: When the inputs are scalars, returns ``y`` if ``x < y``
otherwise ``x``. When the inputs are not scalars, returns ``y[i]``
if ``x[i] < y[i]`` otherwise ``x[i]`` for each element of ``x``
and ``y``.

The return type is ``GenInt1`` unless ``GenInt1`` is the
``__swizzled_vec__`` type, in which case the return type is
the corresponding ``vec``.

.. rubric:: Overload 2

::

  template<typename NonScalar>
  /*return-type*/ max(NonScalar x, NonScalar::value_type y);

Constraints: Available only if ``NonScalar`` is ``marray``, ``vec``,
or the ``__swizzled_vec__`` type and is a generic integer type as
defined above.

Returns: y if ``x[i] < y`` otherwise ``x[i]`` for each element of ``x``.

The return type is ``NonScalar`` unless NonScalar is the
``__swizzled_vec__`` type, in which case the return type is
the corresponding ``vec``.

``min``
=======

.. rubric:: Overload 1

::

  template<typename GenInt1, typename GenInt2>
  /*return-type*/ min(GenInt1 x, GenInt2 y);

Constraints: Available only if all of the following conditions are met:

``GenInt1`` is a generic integer type as defined above;

If ``GenInt1`` is not ``vec`` or the ``__swizzled_vec__`` type, then
``GenInt2`` must be the same as ``GenInt1``; and

If ``GenInt1`` is ``vec`` or the ``__swizzled_vec__`` type, then
``GenInt2`` must also be ``vec`` or the ``__swizzled_vec__`` type,
and both must have the same element type and the same number of elements.

Returns: When the inputs are scalars, returns ``y`` if ``y < x``
otherwise ``x``. When the inputs are not scalars, returns ``y[i]``
if ``y[i] < x[i]`` otherwise ``x[i]`` for each element of
``x`` and ``y``.

The return type is ``GenInt1`` unless ``GenInt1`` is the
``__swizzled_vec__`` type, in which case the return type is
the corresponding ``vec``.

.. rubric:: Overload 2

::

  template<typename NonScalar>
  /*return-type*/ min(NonScalar x, NonScalar::value_type y);

Constraints: Available only if ``NonScalar`` is ``marray``, ``vec``,
or the ``__swizzled_vec__`` type and is a generic integer type as
defined above.

Returns: ``y`` if ``y < x[i]`` otherwise ``x[i]`` for each
element of ``x``.

The return type is ``NonScalar`` unless NonScalar is the
``__swizzled_vec__`` type, in which case the return type is
the corresponding ``vec``.

``mul_hi``
==========

::

  template<typename GenInt1, typename GenInt2>
  /*return-type*/ mul_hi(GenInt1 x, GenInt2 y);

Constraints: Available only if all of the following conditions are met:

``GenInt1`` is a generic integer type as defined above;

If ``GenInt1`` is not ``vec`` or the ``__swizzled_vec__`` type, then
``GenInt2`` must be the same as ``GenInt1``; and

If ``GenInt1`` is ``vec`` or the ``__swizzled_vec__`` type, then
``GenInt2`` must also be ``vec`` or the ``__swizzled_vec__`` type,
and both must have the same element type and the same number
of elements.

Effects: Computes ``x * y`` and returns the high half of the
product of ``x`` and ``y``.

Returns: When the inputs are scalars, returns the high half of
the product of ``x * y``. Otherwise, returns the high half of
the product of ``x[i] * y[i]`` for each element of
``x`` and ``y``.

The return type is ``GenInt1`` unless ``GenInt1`` is the
``__swizzled_vec__`` type, in which case the return type
is the corresponding ``vec``.

``rotate``
==========

::

  template<typename GenInt1, typename GenInt2>
  /*return-type*/ rotate(GenInt1 v, GenInt2 count);

Constraints: Available only if all of the following conditions are met:

``GenInt1`` is a generic integer type as defined above;

If ``GenInt1`` is not ``vec`` or the ``__swizzled_vec__`` type, then
``GenInt2`` must be the same as ``GenInt1``; and

If ``GenInt1`` is ``vec`` or the ``__swizzled_vec__`` type, then
``GenInt2`` must also be ``vec`` or the ``__swizzled_vec__`` type,
and both must have the same element type and the same number
of elements.

Effects: For each element in ``v``, the bits are shifted left by the number
of bits given by the corresponding element in ``count`` (subject to usual
shift modulo rules described in the OpenCL 1.2 specification
|SYCL_SPEC_OPENCL|). Bits shifted off the left side of the element are
shifted back in from the right.

Returns: When the inputs are scalars, the result of rotating
``v`` by ``count``  as described above. Otherwise, the result of
rotating ``v[i]`` by ``count[i]`` for each element of ``v``
and ``count``.

The return type is ``GenInt1`` unless ``GenInt1`` is the
``__swizzled_vec__`` type, in which case the return type
is the corresponding ``vec``.

``sub_sat``
===========

::

  template<typename GenInt1, typename GenInt2>
  /*return-type*/ sub_sat(GenInt1 x, GenInt2 y);

Constraints: Available only if all of the following conditions are met:

``GenInt1`` is a generic integer type as defined above;

If ``GenInt1`` is not ``vec`` or the ``__swizzled_vec__`` type, then
``GenInt2`` must be the same as ``GenInt1``; and

If ``GenInt1`` is ``vec`` or the ``__swizzled_vec__`` type, then
``GenInt2`` must also be ``vec`` or the ``__swizzled_vec__`` type,
and both must have the same element type and the same number
of elements.

Returns: When the inputs are scalars, returns ``x - y``.
Otherwise, returns ``x[i] - y[i]`` for each element of ``x``
and ``y``. The subtraction operation saturates the result.

The return type is ``GenInt1`` unless ``GenInt1`` is the
``__swizzled_vec__`` type, in which case the return type
is the corresponding ``vec``.

``upsample``
============

::

  template<typename UInt8Bit1, typename UInt8Bit2>
  /*return-type*/ upsample(UInt8Bit1 hi, UInt8Bit2 lo);

Constraints: Available only if one of the following conditions is met:

``UInt8Bit1`` and ``UInt8Bit2`` are both ``uint8_t``;

``UInt8Bit1`` and ``UInt8Bit2`` are both ``marray`` with element type
``uint8_t`` and the same number of elements; or

``UInt8Bit1`` and ``UInt8Bit2`` are any combination of ``vec`` or the
``__swizzled_vec__`` type with element type ``uint8_t`` and the same
number of elements.

Returns: When the inputs are scalars, returns
``((uint16_t)hi << 8) | lo``. Otherwise, returns
``((uint16_t)hi[i] << 8) | lo[i]`` for each element
of ``hi`` and ``lo``.

The return type is ``uint16_t`` when the inputs are scalar. When the
inputs are ``marray``, the return type is ``marray`` with element type
``uint16_t`` and the same number of elements as the inputs. Otherwise,
the return type is ``vec`` with element type ``uint16_t`` and the same
number of elements as the inputs.

::

  template<typename Int8Bit, typename UInt8Bit>
  /*return-type*/ upsample(Int8Bit hi, UInt8Bit lo);

Constraints: Available only if one of the following conditions is met:

``Int8Bit`` is ``int8_t`` and ``UInt8Bit`` is ``uint8_t``;

``Int8Bit`` is ``marray`` with element type ``int8_t`` and
``UInt8Bit`` is ``marray`` with element type ``uint8_t`` and both
have the same number of elements; or

``Int8Bit`` is ``vec`` or the ``__swizzled_vec__`` type with element
type ``int8_t`` and ``UInt8Bit`` is ``vec`` or the
``__swizzled_vec__`` type with element type ``uint8_t`` and both have
the same number of elements.

Returns: When the inputs are scalars, returns
``((int16_t)hi << 8) | lo``. Otherwise, returns
``((int16_t)hi[i] << 8) | lo[i]`` for each element of
``hi`` and ``lo``.

The return type is ``int16_t`` when the inputs are scalar. When the
inputs are ``marray``, the return type is ``marray`` with element
type ``int16_t`` and the same number of elements as the inputs.
Otherwise, the return type is ``vec`` with element type
``int16_t`` and the same number of elements as the inputs.

::

  template<typename UInt16Bit1, typename UInt16Bit2>
  /*return-type*/ upsample(UInt16Bit1 hi, UInt16Bit2 lo);

Constraints: Available only if one of the following conditions is met:

``UInt16Bit1`` and ``UInt16Bit2`` are both ``uint16_t``;

``UInt16Bit1`` and ``UInt16Bit2`` are both ``marray`` with
element type ``uint16_t`` and the same number of elements; or

``UInt16Bit1`` and ``UInt16Bit2`` are any combination of
``vec`` or the ``__swizzled_vec__`` type with element type
``uint16_t`` and the same number of elements.

Returns: When the inputs are scalars, returns
``((uint32_t)hi << 16) | lo``. Otherwise, returns
``((uint32_t)hi[i] << 16) | lo[i]`` for each element
of ``hi`` and ``lo``.

The return type is ``uint32_t`` when the inputs are scalar.
When the inputs are ``marray``, the return type is
``marray`` with element type ``uint32_t`` and the same number
of elements as the inputs. Otherwise, the return type is
``vec`` with element type ``uint32_t`` and the same number
of elements as the inputs.

::

  template<typename Int16Bit, typename UInt16Bit>
  /*return-type*/ upsample(Int16Bit hi, UInt16Bit lo);

Constraints: Available only if one of the following conditions is met:

``Int16Bit`` is ``int16_t`` and ``UInt16Bit`` is ``uint16_t``;

``Int16Bit`` is ``marray`` with element type ``int16_t`` and
``UInt16Bit`` is ``marray`` with element type ``uint16_t`` and
both have the same number of elements; or

``Int16Bit`` is ``vec`` or the ``__swizzled_vec__`` type with
element type ``int16_t`` and ``UInt16Bit`` is ``vec`` or the
``__swizzled_vec__`` type with element type ``uint16_t`` and
both have the same number of elements.

Returns: When the inputs are scalars, returns
``((int32_t)hi << 16) | lo``. Otherwise, returns
``((int32_t)hi[i] << 16) | lo[i]`` for each element of
``hi`` and ``lo``.

The return type is ``int32_t`` when the inputs are scalar.
When the inputs are ``marray``, the return type is
``marray`` with element type ``int32_t`` and the same
number of elements as the inputs. Otherwise, the return
type is ``vec`` with element type ``int32_t`` and the
same number of elements as the inputs.

::

  template<typename UInt32Bit1, typename UInt32Bit2>
  /*return-type*/ upsample(UInt32Bit1 hi, UInt32Bit2 lo);

Constraints: Available only if one of the following conditions is met:

``UInt32Bit1`` and ``UInt32Bit2`` are both ``uint32_t``;

``UInt32Bit1`` and ``UInt32Bit2`` are both ``marray`` with element
type ``uint32_t`` and the same number of elements; or

``UInt32Bit1`` and ``UInt32Bit2`` are any combination of
``vec`` or the ``__swizzled_vec__`` type with element type
``uint32_t`` and the same number of elements.

Returns: When the inputs are scalars, returns
``((uint64_t)hi << 32) | lo``. Otherwise, returns
``((uint64_t)hi[i] << 32) | lo[i]`` for each element of
``hi`` and ``lo``.

The return type is ``uint64_t`` when the inputs are scalar.
When the inputs are ``marray``, the return type is
``marray`` with element type ``uint64_t`` and the same number of
elements as the inputs. Otherwise, the return type is ``vec`` with
element type ``uint64_t`` and the same number of elements as the inputs.

::

  template<typename Int32Bit, typename UInt32Bit>
  /*return-type*/ upsample(Int32Bit hi, UInt32Bit lo);

Constraints: Available only if one of the following conditions is met:

``Int32Bit`` is ``int32_t`` and ``UInt32Bit`` is ``uint32_t``;

``Int32Bit`` is ``marray`` with element type ``int32_t`` and
``UInt32Bit`` is ``marray`` with element type ``uint32_t`` and
both have the same number of elements; or

``Int32Bit`` is ``vec`` or the ``__swizzled_vec__`` type with
element type ``int32_t`` and ``UInt32Bit`` is ``vec`` or the
``__swizzled_vec__`` type with element type ``uint32_t`` and
both have the same number of elements.

Returns: When the inputs are scalars, returns
``((int64_t)hi << 32) | lo``. Otherwise, returns
``((int64_t)hi[i] << 32) | lo[i]`` for each element of
``hi`` and ``lo``.

The return type is ``int64_t`` when the inputs are scalar.
When the inputs are ``marray``, the return type is
``marray`` with element type ``int64_t`` and the same number
of elements as the inputs. Otherwise, the return type is
``vec`` with element type ``int64_t`` and the same number
of elements as the inputs.

``popcount``
============

::

  template<typename GenInt>
  /*return-type*/ popcount(GenInt x);

Constraints: Available only if ``GenInt`` is a generic
integer type as defined above.

Returns: When the input is a scalar, returns the number of
non-zero bits in ``x`` Otherwise, returns the number of non-zero
bits in ``x[i]`` for each element of ``x``.

The return type is ``GenInt`` unless ``GenInt`` is the
``__swizzled_vec__`` type, in which case the return type
is the corresponding ``vec``.

``mad24``
=========

::

  template<typename Int32Bit1, typename Int32Bit2, typename Int32Bit3>
  /*return-type*/ mad24(Int32Bit1 x, Int32Bit2 y, Int32Bit3 z);

Constraints: Available only if all of the following conditions are met:

``Int32Bit1`` is one of the following types:

``int32_t``

``uint32_t``

``marray<int32_t, N>``

``marray<uint32_t, N>``

``vec<int32_t, N>``

``vec<uint32_t, N>``

``__swizzled_vec__`` that is convertible to ``vec<int32_t, N>``

``__swizzled_vec__`` that is convertible to ``vec<uint32_t, N>``

If ``Int32Bit1`` is not ``vec`` or the ``__swizzled_vec__`` type, then
``Int32Bit2`` and ``Int32Bit`` must be the same as ``Int32Bit1``; and

If ``Int32Bit1`` is ``vec`` or the ``__swizzled_vec__`` type, then
``Int32Bit2`` and ``Int32Bit3`` must also be ``vec`` or the
``__swizzled_vec__`` type, and all three must have the same
element type and the same number of elements.

Preconditions: If the inputs are signed scalars, the values of
``x`` and ``y`` must be in the range [-223, 223-1]. If the inputs
are unsigned scalars, the values of ``x`` and ``y`` must be in
the range [0, 224-1]. If the inputs are not scalars, each element
of ``x`` and ``y`` must be in these ranges.

Returns: When the inputs are scalars, returns ``x * y + z``.
Otherwise, returns ``x[i] * y[i] + z[i]`` for each element
of ``x``, ``y``, and ``z``.

The return type is ``Int32Bit1`` unless ``Int32Bit1`` is the
``__swizzled_vec__`` type, in which case the return type is
the corresponding ``vec``.

``mul24``
=========

::

  template<typename Int32Bit1, typename Int32Bit2>
  /*return-type*/ mul24(Int32Bit1 x, Int32Bit2 y);

Constraints: Available only if all of the following conditions are met:

``Int32Bit1`` is one of the following types:

``int32_t``

``uint32_t``

``marray<int32_t, N>``

``marray<uint32_t, N>``

``vec<int32_t, N>``

``vec<uint32_t, N>``

``__swizzled_vec__`` that is convertible to ``vec<int32_t, N>``

``__swizzled_vec__`` that is convertible to ``vec<uint32_t, N>``

If ``Int32Bit1`` is not ``vec`` or the ``__swizzled_vec__``
type, then ``Int32Bit2`` must be the same as ``Int32Bit1``; and

If ``Int32Bit1`` is ``vec`` or the ``__swizzled_vec__`` type,
then ``Int32Bit2`` must also be ``vec`` or the
``__swizzled_vec__`` type, and both must have the same element
type and the same number of elements.

Preconditions: If the inputs are signed scalars, the values of
``x`` and ``y`` must be in the range [-223, 223-1]. If the inputs
are unsigned scalars, the values of ``x`` and ``y`` must be in the
range [0, 224-1]. If the inputs are not scalars, each element of
``x`` and ``y`` must be in these ranges.

Returns: When the inputs are scalars, returns ``x * y``.
Otherwise, returns ``x[i] * y[i]`` for each element of
``x`` and ``y``.

The return type is ``Int32Bit1`` unless ``Int32Bit1`` is the
``__swizzled_vec__`` type, in which case the return type is
the corresponding ``vec``.
