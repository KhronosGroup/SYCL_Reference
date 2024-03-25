..
  Copyright 2024 The Khronos Group Inc.
  SPDX-License-Identifier: CC-BY-4.0

.. _geometric-functions:

*******************
Geometric functions
*******************

In SYCL the OpenCL geometric functions are available in the namespace
``sycl`` on host and device as defined in the OpenCL 1.2 specification
document par. 6.12.5. On the host the vector types use the ``sycl::vec``
class and on a SYCL device use the corresponding native SYCL backend
vector types. All of the geometric functions use round-to-nearest-even
rounding mode.

The function descriptions in this section use two terms that refer to
a specific list of types. The term `generic geometric type` represents
the following types:

* ``float``
* ``double``
* ``half``
* ``sycl::marray<float, N>``, where ``N`` is 2, 3, or 4
* ``sycl::marray<double, N>``, where ``N`` is 2, 3, or 4
* ``sycl::marray<half, N>``, where ``N`` is 2, 3, or 4
* ``sycl::vec<float, N>``, where ``N`` is 2, 3, or 4
* ``sycl::vec<double, N>``, where ``N`` is 2, 3, or 4
* ``sycl::vec<half, N>``, where ``N`` is 2, 3, or 4
* ``__swizzled_vec__`` that is convertible to
  ``sycl::vec<float, N>``, where ``N`` is 2, 3, or 4
* ``__swizzled_vec__`` that is convertible to
  ``sycl::vec<double, N>``, where ``N`` is 2, 3, or 4
* ``__swizzled_vec__`` that is convertible to
  ``sycl::vec<half, N>``, where ``N`` is 2, 3, or 4

The term `float geometric type` represents these types:

* ``float``
* ``sycl::marray<float, N>``, where ``N`` is 2, 3, or 4
* ``sycl::vec<float, N>``, where ``N`` is 2, 3, or 4
* ``__swizzled_vec__`` that is convertible to
  ``sycl::vec<float, N>``, where ``N`` is 2, 3, or 4

.. seealso:: |SYCL_SPEC_GEOM_FUNCTIONS|

===============
``sycl::cross``
===============

::

  template<typename Geo3or4Float1, typename Geo3or4Float2>
  /*return-type*/ cross(Geo3or4Float1 p0, Geo3or4Float2 p1);

Available only if all of the following conditions are met:

* ``Geo3or4Float1`` is one of the following types:

  * ``sycl::marray<float, 3>``
  * ``sycl::marray<double, 3>``
  * ``sycl::marray<half, 3>``
  * ``sycl::marray<float, 4>``
  * ``sycl::marray<double, 4>``
  * ``sycl::marray<half, 4>``
  * ``sycl::vec<float, 3>``
  * ``sycl::vec<double, 3>``
  * ``sycl::vec<half, 3>``
  * ``sycl::vec<float, 4>``
  * ``sycl::vec<double, 4>``
  * ``sycl::vec<half, 4>``
  * ``__swizzled_vec__`` that is convertible to ``sycl::vec<float, 3>``
  * ``__swizzled_vec__`` that is convertible to ``sycl::vec<double, 3>``
  * ``__swizzled_vec__`` that is convertible to ``sycl::vec<half, 3>``
  * ``__swizzled_vec__`` that is convertible to ``sycl::vec<float, 4>``
  * ``__swizzled_vec__`` that is convertible to ``sycl::vec<double, 4>``
  * ``__swizzled_vec__`` that is convertible to ``sycl::vec<half, 4>``
* If ``Geo3or4Float1`` is ``sycl::marray``, then ``Geo3or4Float2``
  must be the same as ``Geo3or4Float1``;
* If ``Geo3or4Float1`` is ``sycl::vec`` or the ``__swizzled_vec__``
  type, then ``Geo3or4Float2`` must also be ``sycl::vec`` or the
  ``__swizzled_vec__`` type, and both must have the same element
  type and the same number of elements.

Returns the cross product of first 3 components of ``p0``
and ``p1``. When the inputs have 4 components, the 4th
component of the result is ``0.0``.

The return type is ``Geo3or4Float1`` unless ``Geo3or4Float1`` is
the ``__swizzled_vec__`` type, in which case the return type is
the corresponding ``sycl::vec``.

=============
``sycl::dot``
=============

::

  template<typename GeoFloat1, typename GeoFloat2>
  /*return-type*/ dot(GeoFloat1 p0, GeoFloat2 p1);

Available only if all of the following conditions are met:

* ``GeoFloat1`` is a `generic geometric type` as defined above;
* If ``GeoFloat1`` is not ``sycl::vec`` or the ``__swizzled_vec__``
  type, then ``GeoFloat2`` must be the same as ``GeoFloat1``;
* If ``GeoFloat1`` is ``sycl::vec`` or the ``__swizzled_vec__`` type,
  then ``GeoFloat2`` must also be ``sycl::vec`` or the
  ``__swizzled_vec__`` type, and both must have the same element
  type and the same number of elements.

Returns the dot product of ``p0`` and ``p1``.

The return type is ``GeoFloat1`` if the input types are scalar.
Otherwise, the return type is ``GeoFloat1::value_type``.

==================
``sycl::distance``
==================

::

  template<typename GeoFloat1, typename GeoFloat2>
  /*return-type*/ distance(GeoFloat1 p0, GeoFloat2 p1);

Available only if all of the following conditions are met:

* ``GeoFloat1`` is a `generic geometric type` as defined above;
* If ``GeoFloat1`` is not ``sycl::vec`` or the ``__swizzled_vec__``
  type, then ``GeoFloat2`` must be the same as ``GeoFloat1``;
* If ``GeoFloat1`` is ``sycl::vec`` or the ``__swizzled_vec__`` type,
  then ``GeoFloat2`` must also be ``sycl::vec`` or the
  ``__swizzled_vec__`` type, and both must have the same element
  type and the same number of elements.

Returns the distance between ``p0`` and ``p1``. This is calculated
as ``sycl::length(p0 - p1)``.

The return type is ``GeoFloat1`` if the input types are scalar.
Otherwise, the return type is ``GeoFloat1::value_type``.

================
``sycl::length``
================

::

  template<typename GeoFloat>
  /*return-type*/ length(GeoFloat p);

Available only if ``GeoFloat`` is a `generic geometric type`
as defined above.

Returns the length of vector ``p``, i.e.,
``sycl::sqrt(sycl::pow(p[0],2) + sycl::pow(p[1],2) + ...)``.

The return type is ``GeoFloat`` if the input type is scalar.
Otherwise, the return type is ``GeoFloat::value_type``.

===================
``sycl::normalize``
===================

::

  template<typename GeoFloat>
  /*return-type*/ normalize(GeoFloat p);

Available only if ``GeoFloat`` is a `generic geometric type`
as defined above.

Returns a vector in the same direction as ``p`` but with a
length of 1.

The return type is ``GeoFloat`` unless ``GeoFloat`` is the
``__swizzled_vec__`` type, in which case the return type is
the corresponding ``sycl::vec``.

=======================
``sycl::fast_distance``
=======================

::

  template<typename GeoFloat1, typename GeoFloat2>
  /*return-type*/ fast_distance(GeoFloat1 p0, GeoFloat2 p1);

Available only if all of the following conditions are met:

* ``GeoFloat1`` is a `float geometric type` as defined above;
* If ``GeoFloat1`` is not ``sycl::vec`` or the ``__swizzled_vec__``
  type, then ``GeoFloat2`` must be the same as ``GeoFloat1``;
* If ``GeoFloat1`` is ``sycl::vec`` or the ``__swizzled_vec__`` type,
  then ``GeoFloat2`` must also be ``sycl::vec`` or the
  ``__swizzled_vec__`` type, and both must have the same element
  type and the same number of elements.

Returns the value ``sycl::fast_length(p0 - p1)``.

The return type is ``GeoFloat1`` if the input types are scalar.
Otherwise, the return type is ``GeoFloat1::value_type``.

=====================
``sycl::fast_length``
=====================

::

  template<typename GeoFloat>
  /*return-type*/ fast_length(GeoFloat p);

Available only if ``GeoFloat`` is a `float geometric type`
as defined above.

Returns the length of vector ``p`` computed as:

``sycl::half_precision::sqrt(sycl::pow(p[0],2) + sycl::pow(p[1],2) + ...)``.

The return type is ``GeoFloat`` if the input type is scalar.
Otherwise, the return type is ``GeoFloat::value_type``.

========================
``sycl::fast_normalize``
========================

::

  template<typename GeoFloat>
  /*return-type*/ fast_normalize(GeoFloat p);

Available only if ``GeoFloat`` is a `float geometric type`
as defined above.

Returns a vector in the same direction as ``p`` but with a length
of ``1`` computed as:

``p * sycl::half_precision::rsqrt(sycl::pow(p[0],2)
+ sycl::pow(p[1],2) + ...)``.

The result shall be within 8192 ulps error from the infinitely
precise result of:

::

  if (sycl::all(p == 0.0f))
    result = p;
  else
    result = p / sycl::sqrt(sycl::pow(p[0], 2) + sycl::pow(p[1], 2) + ...);

with the following exceptions:

1. If the sum of squares is greater than ``FLT_MAX`` then the
   value of the floating-point values in the result vector
   are undefined.
2. If the sum of squares is less than ``FLT_MIN`` then the
   implementation may return back ``p``.

The return type is ``GeoFloat`` unless ``GeoFloat`` is the
``__swizzled_vec__`` type, in which case the return type is
the corresponding ``sycl::vec``.
