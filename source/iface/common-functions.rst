..
  Copyright 2023 The Khronos Group Inc.
  SPDX-License-Identifier: CC-BY-4.0

.. _common-functions:

****************
Common functions
****************

In SYCL the OpenCL common functions are available in the
namespace ``sycl`` on host and device as defined in the
OpenCL 1.2 specification document par. 6.12.4.

The function descriptions in this section use the term
`generic floating point type` to represent the following types:

* ``float``
* ``double``
* ``half``
* ``sycl::marray<float, N>``
* ``sycl::marray<double, N>``
* ``sycl::marray<half, N>``
* ``sycl::vec<float, N>``
* ``sycl::vec<double, N>``
* ``sycl::vec<half, N>``
* ``__swizzled_vec__`` that is convertible to ``sycl::vec<float, N>``
* ``__swizzled_vec__`` that is convertible to ``sycl::vec<double, N>``
* ``__swizzled_vec__`` that is convertible to ``sycl::vec<half, N>``

===============
``sycl::clamp``
===============

.. rubric:: Overload 1

::

  template<typename GenFloat1, typename GenFloat2, typename GenFloat3>
  /*return-type*/ clamp(GenFloat1 x, GenFloat2 minval, GenFloat3 maxval);

Available only if all of the following conditions are met:

* ``GenFloat1`` is a `generic floating point type` as defined above;
* If ``GenFloat1`` is not ``sycl::vec`` or the ``__swizzled_vec__``
  type, then ``GenFloat2`` and ``GenFloat3`` must be the same as
  ``GenFloat1``;
* If GenFloat1 is ``sycl::vec`` or the ``__swizzled_vec__`` type,
  then ``GenFloat2`` and ``GenFloat3`` must also be ``sycl::vec``
  or the ``__swizzled_vec__`` type, and all three must have the
  same element type and the same number of elements.

If the inputs are scalars, the value of ``minval`` must be less than
or equal to the value of ``maxval``. If the inputs are not scalars,
each element of ``minval`` must be less than or equal to the
corresponding element of ``maxval``.

When the inputs are scalars, returns ``sycl::fmin(fmax(x, minval),
maxval)``. Otherwise, returns ``sycl::fmin(fmax(x[i], minval[i]),
maxval[i])`` for each element of ``x``, ``minval``, and ``maxval``.

The return type is ``GenFloat1`` unless ``GenFloat1`` is the
``__swizzled_vec__`` type, in which case the return type is
the corresponding ``sycl::vec``.

.. rubric:: Overload 2

::

  template<typename NonScalar>
  /*return-type*/ clamp(NonScalar x, NonScalar::value_type minval,
                        NonScalar::value_type maxval);

Available only if ``NonScalar`` is ``sycl::marray``, ``sycl::vec``,
or the ``__swizzled_vec__`` type and is a `generic floating point
type` as defined above.

The value of ``minval`` must be less than or equal to the value
of ``maxval``.

Returns ``sycl::fmin(fmax(x[i], minval), maxval)`` for each
element of ``x``.

The return type is ``NonScalar`` unless ``NonScalar`` is the
``__swizzled_vec__`` type, in which case the return type is
the corresponding ``sycl::vec``.

=================
``sycl::degrees``
=================

::

  template<typename GenFloat>
  /*return-type*/ degrees(GenFloat radians);

Available only if ``GenFloat`` is a `generic floating point type`
as defined above.

Converts radians to degrees.

When the inputs are scalars, returns ``(180 / π) * radians``. Otherwise,
returns ``(180 / π) * radians[i]`` for each element of ``radians``.

The return type is ``GenFloat`` unless ``GenFloat`` is the
``__swizzled_vec__`` type, in which case the return type is
the corresponding ``sycl::vec``.

=============
``sycl::max``
=============

.. rubric:: Overload 1

::

  template<typename GenFloat1, typename GenFloat2>
  /*return-type*/ max(GenFloat1 x, GenFloat2 y);

Available only if all of the following conditions are met:

* ``GenFloat1`` is a `generic floating point type`
  as defined above;
* If ``GenFloat1`` is not ``sycl::vec`` or the ``__swizzled_vec__``
  type, then ``GenFloat2`` must be the same as ``GenFloat1``;
* If ``GenFloat1`` is ``sycl::vec`` or the ``__swizzled_vec__`` type,
  then ``GenFloat2`` must also be ``sycl::vec`` or the
  ``__swizzled_vec__`` type, and both must have the same element type
  and the same number of elements.

When the inputs are scalars, ``x`` and ``y`` must not be infinite or
NaN. When the inputs are not scalars, no element of ``x`` or ``y`` may
be infinite or NaN.

When the inputs are scalars, returns ``y`` if ``x < y`` otherwise ``x``.
When the inputs are not scalars, returns ``y[i]`` if ``x[i] < y[i]``
otherwise ``x[i]`` for each element of ``x`` and ``y``.

The return type is ``GenFloat1`` unless ``GenFloat1`` is the
``__swizzled_vec__`` type, in which case the return type is the
corresponding ``sycl::vec``.

.. rubric:: Overload 2

::

  template<typename NonScalar>
  /*return-type*/ max(NonScalar x, NonScalar::value_type y);

Available only if NonScalar is ``sycl::marray``, ``sycl::vec``, or
the ``__swizzled_vec__`` type and is a `generic floating point type`
as defined above.

No element of ``x`` may be infinite or NaN. The value of ``y`` must
not be infinite or NaN.

Returns ``y`` if ``x[i] < y`` otherwise ``x[i]`` for each
element of ``x``.

The return type is ``NonScalar`` unless ``NonScalar`` is the
``__swizzled_vec__`` type, in which case the return type is
the corresponding ``sycl::vec``.

=============
``sycl::min``
=============

.. rubric:: Overload 1

::

  template<typename GenFloat1, typename GenFloat2>
  /*return-type*/ min(GenFloat1 x, GenFloat2 y);

Available only if all of the following conditions are met:

* ``GenFloat1`` is a `generic floating point type`
  as defined above;
* If ``GenFloat1`` is not ``sycl::vec`` or the ``__swizzled_vec__``
  type, then ``GenFloat2`` must be the same as ``GenFloat1``;
* If ``GenFloat1`` is ``sycl::vec`` or the ``__swizzled_vec__`` type,
  then ``GenFloat2`` must also be ``sycl::vec`` or the
  ``__swizzled_vec__`` type, and both must have the same element type
  and the same number of elements.

When the inputs are scalars, ``x`` and ``y`` must not be infinite or
NaN. When the inputs are not scalars, no element of ``x`` or ``y`` may
be infinite or NaN.

When the inputs are scalars, returns ``y`` if ``y < x`` otherwise ``x``.
When the inputs are not scalars, returns ``y[i]`` if ``y[i] < x[i]``
otherwise ``x[i]`` for each element of ``x`` and ``y``.

The return type is ``GenFloat1`` unless ``GenFloat1`` is the
``__swizzled_vec__`` type, in which case the return type is the
corresponding ``sycl::vec``.

.. rubric:: Overload 2

::

  template<typename NonScalar>
  /*return-type*/ min(NonScalar x, NonScalar::value_type y);

Available only if NonScalar is ``sycl::marray``, ``sycl::vec``, or
the ``__swizzled_vec__`` type and is a `generic floating point type`
as defined above.

No element of ``x`` may be infinite or NaN. The value of ``y`` must
not be infinite or NaN.

Returns ``y`` if ``y < x[i]`` otherwise ``x[i]`` for each
element of ``x``.

The return type is ``NonScalar`` unless ``NonScalar`` is the
``__swizzled_vec__`` type, in which case the return type is
the corresponding ``sycl::vec``.

=============
``sycl::mix``
=============

.. rubric:: Overload 1

::

  template<typename GenFloat1, typename GenFloat2, typename GenFloat3>
  /*return-type*/ mix(GenFloat1 x, GenFloat2 y, GenFloat3 a);

Available only if all of the following conditions are met:

* ``GenFloat1`` is a `generic floating point type` as defined above;
* If ``GenFloat1`` is not ``sycl::vec`` or the ``__swizzled_vec__``
  type, then ``GenFloat2`` and ``GenFloat3`` must be the same as
  ``GenFloat1``;
* If GenFloat1 is ``sycl::vec`` or the ``__swizzled_vec__`` type,
  then ``GenFloat2`` and ``GenFloat3`` must also be ``sycl::vec``
  or the ``__swizzled_vec__`` type, and all three must have the
  same element type and the same number of elements.

If the inputs are scalars, the value of ``a`` must be in the range
``[0.0, 1.0]``. If the inputs are not scalars, each element of
``a`` must be in the range ``[0.0, 1.0]``.

Returns the linear blend of ``x`` and ``y``. When the inputs are
scalars, returns ``x + (y - x) * a``. Otherwise, returns
``x[i] + (y[i] - x[i]) * a[i]`` for each element of ``x``, ``y``,
and ``a``.

The return type is ``GenFloat1`` unless ``GenFloat1`` is the
``__swizzled_vec__`` type, in which case the return type is
the corresponding ``sycl::vec``.

.. rubric:: Overload 2

::

  template<typename NonScalar1, typename NonScalar2>
  /*return-type*/ mix(NonScalar1 x, NonScalar2 y, NonScalar1::value_type a);

Available only if all of the following conditions are met:

* ``NonScalar1`` is ``sycl::marray``, ``sycl::vec``, or the
  ``__swizzled_vec__`` type and is a `generic floating point type`
  as defined above;
* If ``NonScalar1`` is not ``sycl::vec`` or the ``__swizzled_vec__``
  type, then ``NonScalar2`` must be the same as ``NonScalar1``;
* If ``NonScalar1`` is ``sycl::vec`` or the ``__swizzled_vec__`` type,
  then ``NonScalar2`` must also be ``sycl::vec`` or the
  ``__swizzled_vec__`` type, and both must have the same element type
  and the same number of elements.

The value of ``a`` must be in the range ``[0.0, 1.0]``.

Returns the linear blend of ``x`` and ``y``, computed as
``x[i] + (y[i] - x[i]) * a`` for each element of ``x`` and ``y``.

The return type is ``NonScalar1`` unless ``NonScalar1`` is the
``__swizzled_vec__`` type, in which case the return type is
the corresponding ``sycl::vec``.

=================
``sycl::radians``
=================

::

  template<typename GenFloat>
  /*return-type*/ radians(GenFloat degrees);

Available only if ``GenFloat`` is a `generic floating point type`
as defined above.

Converts degrees to radians.

When the inputs are scalars, returns ``(π / 180) * degrees``.
Otherwise, returns ``(π / 180) * degrees[i]`` for each element
of ``degrees``.

The return type is ``GenFloat`` unless ``GenFloat`` is the
``__swizzled_vec__`` type, in which case the return type is
the corresponding ``sycl::vec``.

==============
``sycl::step``
==============

.. rubric:: Overload 1

::

  template<typename GenFloat1, typename GenFloat2>
  /*return-type*/ step(GenFloat1 edge, GenFloat2 x);

Available only if all of the following conditions are met:

* ``GenFloat1`` is a `generic floating point type`
  as defined above;
* If ``GenFloat1`` is not ``sycl::vec`` or the ``__swizzled_vec__``
  type, then ``GenFloat2`` must be the same as ``GenFloat1``;
* If ``GenFloat1`` is ``sycl::vec`` or the ``__swizzled_vec__`` type,
  then ``GenFloat2`` must also be ``sycl::vec`` or the
  ``__swizzled_vec__`` type, and both must have the same element type
  and the same number of elements.

When the inputs are scalars, returns the value ``(x < edge) ? 0.0 : 1.0``.
When the inputs are not scalars, returns the value
``(x[i] < edge[i]) ? 0.0 : 1.0`` for each element of ``x`` and ``edge``.

The return type is ``GenFloat1`` unless ``GenFloat1`` is the
``__swizzled_vec__`` type, in which case the return type is the
corresponding ``sycl::vec``.

.. rubric:: Overload 2

::

  template<typename NonScalar>
  /*return-type*/ step(NonScalar::value_type edge, NonScalar x);

Available only if NonScalar is ``sycl::marray``, ``sycl::vec``, or
the ``__swizzled_vec__`` type and is a `generic floating point type`
as defined above.

No element of ``x`` may be infinite or NaN. The value of ``y`` must
not be infinite or NaN.

The value ``(x[i] < edge) ? 0.0 : 1.0`` for each element of ``x``.

The return type is ``NonScalar`` unless ``NonScalar`` is the
``__swizzled_vec__`` type, in which case the return type is
the corresponding ``sycl::vec``.

====================
``sycl::smoothstep``
====================

.. rubric:: Overload 1

::

  template<typename GenFloat1, typename GenFloat2, typename GenFloat3>
  /*return-type*/ smoothstep(GenFloat1 edge0, GenFloat2 edge1, GenFloat3 x);

Available only if all of the following conditions are met:

* ``GenFloat1`` is a `generic floating point type` as defined above;
* If ``GenFloat1`` is not ``sycl::vec`` or the ``__swizzled_vec__``
  type, then ``GenFloat2`` and ``GenFloat3`` must be the same as
  ``GenFloat1``;
* If GenFloat1 is ``sycl::vec`` or the ``__swizzled_vec__`` type,
  then ``GenFloat2`` and ``GenFloat3`` must also be ``sycl::vec``
  or the ``__swizzled_vec__`` type, and all three must have the
  same element type and the same number of elements.

If the inputs are scalar, ``edge0`` must be less than ``edge1``
and none of ``edge0``, ``edge1``, or ``x`` may be NaN. If the
inputs are not scalar, each element of ``edge0`` must be less
than the corresponding element of ``edge1`` and no element of
``edge0``, ``edge1``, or ``x`` may be NaN.

When the inputs are scalars, returns ``0.0`` if ``x <= edge0``
and ``1.0`` if ``x >= edge1`` and performs smooth Hermite
interpolation between 0 and 1 when ``edge0 < x < edge1``. This
is useful in cases where you would want a threshold function
with a smooth transition. This is equivalent to:

::

  GenFloat1 t;
  t = sycl::clamp((x - edge0) / (edge1 - edge0), 0, 1);
  return t * t * (3 - 2 * t);

When the inputs are not scalars, returns the following value for
each element of ``edge0``, ``edge1``, and ``x``:

::

  GenFloat1::value_type t;
  t = sycl::clamp((x[i] - edge0[i]) / (edge1[i] - edge0[i]), 0, 1);
  return t * t * (3 - 2 * t);

The return type is ``GenFloat1`` unless ``GenFloat1`` is the
``__swizzled_vec__`` type, in which case the return type is
the corresponding ``sycl::vec``.

.. rubric:: Overload 2

::

  template<typename NonScalar>
  /*return-type*/ smoothstep(NonScalar::value_type edge0,
                             NonScalar::value_type edge1,
                             NonScalar x);

Available only if NonScalar is ``sycl::marray``, ``sycl::vec``,
or the ``__swizzled_vec__`` type and is a `generic floating
point type` as defined above.

The value of ``edge0`` must be less than ``edge1`` and neither
``edge0`` nor ``edge1`` may be NaN. No element of ``x`` may be
NaN.

Returns the following value for each element of ``x``:

::

  NonScalar::value_type t;
  t = sycl::clamp((x[i] - edge0) / (edge1 - edge0), 0, 1);
  return t * t * (3 - 2 * t);

The return type is ``NonScalar`` unless ``NonScalar`` is the
``__swizzled_vec__`` type, in which case the return type is
the corresponding ``sycl::vec``.

==============
``sycl::sign``
==============

::

  template<typename GenFloat>
  /*return-type*/ sign(GenFloat x);

Available only if GenFloat is a `generic floating point type`
as defined above.

When the input is scalar, returns ``1.0`` if ``x > 0``, ``-0.0``
if ``x == -0.0``, ``+0.0`` if ``x == +0.0``, ``-1.0`` if ``x < 0``,
or ``0.0`` if ``x`` is a NaN. When the input is not scalar, returns
these values for each element of ``x``.

The return type is ``GenFloat`` unless ``GenFloat`` is the
``__swizzled_vec__`` type, in which case the return type is
the corresponding ``sycl::vec``.
