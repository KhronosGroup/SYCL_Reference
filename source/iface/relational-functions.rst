..
  Copyright 2023 The Khronos Group Inc.
  SPDX-License-Identifier: CC-BY-4.0

.. _relational-functions:

********************
Relational functions
********************

Relational functions are defined in the ``sycl`` namespace
and are available on both host and device. These functions
perform various relational comparisons on ``sycl::vec``,
``sycl::marray``, and scalar types.

The comparisons performed by ``sycl::isequal``, ``sycl::isgreater``,
``sycl::isgreaterequal``, ``sycl::isless``, ``sycl::islessequal``,
and ``sycl::islessgreater`` are ``false`` when one or both operands
are NaN. The comparison performed by ``sycl::isnotequal`` is ``true``
when one or both operands are NaN.

The function descriptions in this section use two terms that refer
to a specific list of types. The term `generic scalar type` represents
the following types:

* ``char``
* ``signed char``
* ``short``
* ``int``
* ``long``
* ``long long``
* ``unsigned char``
* ``unsigned short``
* ``unsigned int``
* ``unsigned long``
* ``unsigned long long``
* ``float``
* ``double``
* ``half``

The term `vector element type` represents these types:

* ``int8_t``
* ``int16_t``
* ``int32_t``
* ``int64_t``
* ``uint8_t``
* ``uint16_t``
* ``uint32_t``
* ``uint64_t``
* ``float``
* ``double``
* ``half``

.. seealso:: |SYCL_SPEC_RELATIONAL_FUNC|

=================
``sycl::isequal``
=================

.. rubric:: Overloads 1-3

::

  bool isequal(float x, float y);
  bool isequal(double x, double y);
  bool isequal(half x, half y);

Returns the value ``(x == y)``.

.. rubric:: Overload 4

::

  template<typename NonScalar1, typename NonScalar2>
  /*return-type*/ isequal(NonScalar1 x, NonScalar2 y);

Available only if all of the following conditions are met:

* One of the following conditions must hold for ``NonScalar1``
  and ``NonScalar2``:

  * Both ``NonScalar1`` and ``NonScalar2`` are ``sycl::marray``;
  * ``NonScalar1`` and ``NonScalar2`` are any combination of
    ``sycl::vec`` and the ``__swizzled_vec__`` type;
* ``NonScalar1`` and ``NonScalar2`` have the same number of
  elements and the same element type;
* The element type is ``float``, ``double``, or ``half``.

If ``NonScalar1`` is ``sycl::marray``, the value ``(x[i] == y[i])``
for each element of ``x`` and ``y``. If ``NonScalar1`` is
``sycl::vec`` or the ``__swizzled_vec__`` type, returns the value
``((x[i] == y[i]) ? -1 : 0)`` for each element of ``x`` and ``y``.

The return type depends on ``NonScalar1``:

.. list-table::
  :header-rows: 1

  * - ``NonScalar1``
    - Return Type
  * - ``sycl::marray<float, N>``

      ``sycl::marray<double, N>``

      ``sycl::marray<half, N>``
    - ``sycl::marray<bool, N>``
  * - ``sycl::vec<float, N>``

      ``__swizzled_vec__`` convertible to ``sycl::vec<float, N>``
    - ``sycl::vec<int32_t, N>``
  * - ``sycl::vec<double, N>``

      ``__swizzled_vec__`` convertible to ``sycl::vec<double, N>``
    - ``sycl::vec<int64_t, N>``
  * - ``sycl::vec<half, N>``

      ``__swizzled_vec__`` convertible to ``sycl::vec<half, N>``
    - ``sycl::vec<int16_t, N>``

====================
``sycl::isnotequal``
====================

.. rubric:: Overloads 1-3

::

  bool isnotequal(float x, float y);
  bool isnotequal(double x, double y);
  bool isnotequal(half x, half y);

Returns the value ``(x != y)``.

.. rubric:: Overload 4

::

  template<typename NonScalar1, typename NonScalar2>
  /*return-type*/ isnotequal(NonScalar1 x, NonScalar2 y);

Available only if all of the following conditions are met:

* One of the following conditions must hold for ``NonScalar1``
  and ``NonScalar2``:

  * Both ``NonScalar1`` and ``NonScalar2`` are ``sycl::marray``;
  * ``NonScalar1`` and ``NonScalar2`` are any combination of
    ``sycl::vec`` and the ``__swizzled_vec__`` type;
* ``NonScalar1`` and ``NonScalar2`` have the same number of
  elements and the same element type;
* The element type is ``float``, ``double``, or ``half``.

If ``NonScalar1`` is ``sycl::marray``, the value ``(x[i] != y[i])``
for each element of ``x`` and ``y``. If ``NonScalar1`` is
``sycl::vec`` or the ``__swizzled_vec__`` type, returns the value
``((x[i] != y[i]) ? -1 : 0)`` for each element of ``x`` and ``y``.

The return type depends on ``NonScalar1``:

.. list-table::
  :header-rows: 1

  * - ``NonScalar1``
    - Return Type
  * - ``sycl::marray<float, N>``

      ``sycl::marray<double, N>``

      ``sycl::marray<half, N>``
    - ``sycl::marray<bool, N>``
  * - ``sycl::vec<float, N>``

      ``__swizzled_vec__`` convertible to ``sycl::vec<float, N>``
    - ``sycl::vec<int32_t, N>``
  * - ``sycl::vec<double, N>``

      ``__swizzled_vec__`` convertible to ``sycl::vec<double, N>``
    - ``sycl::vec<int64_t, N>``
  * - ``sycl::vec<half, N>``

      ``__swizzled_vec__`` convertible to ``sycl::vec<half, N>``
    - ``sycl::vec<int16_t, N>``

===================
``sycl::isgreater``
===================

.. rubric:: Overloads 1-3

::

  bool isgreater(float x, float y);
  bool isgreater(double x, double y);
  bool isgreater(half x, half y);

Returns the value ``(x > y)``.

.. rubric:: Overload 4

::

  template<typename NonScalar1, typename NonScalar2>
  /*return-type*/ isgreater(NonScalar1 x, NonScalar2 y);

Available only if all of the following conditions are met:

* One of the following conditions must hold for ``NonScalar1``
  and ``NonScalar2``:

  * Both ``NonScalar1`` and ``NonScalar2`` are ``sycl::marray``;
  * ``NonScalar1`` and ``NonScalar2`` are any combination of
    ``sycl::vec`` and the ``__swizzled_vec__`` type;
* ``NonScalar1`` and ``NonScalar2`` have the same number of
  elements and the same element type;
* The element type is ``float``, ``double``, or ``half``.

If ``NonScalar1`` is ``sycl::marray``, the value ``(x[i] > y[i])``
for each element of ``x`` and ``y``. If ``NonScalar1`` is
``sycl::vec`` or the ``__swizzled_vec__`` type, returns the value
``((x[i] > y[i]) ? -1 : 0)`` for each element of ``x`` and ``y``.

The return type depends on ``NonScalar1``:

.. list-table::
  :header-rows: 1

  * - ``NonScalar1``
    - Return Type
  * - ``sycl::marray<float, N>``

      ``sycl::marray<double, N>``

      ``sycl::marray<half, N>``
    - ``sycl::marray<bool, N>``
  * - ``sycl::vec<float, N>``

      ``__swizzled_vec__`` convertible to ``sycl::vec<float, N>``
    - ``sycl::vec<int32_t, N>``
  * - ``sycl::vec<double, N>``

      ``__swizzled_vec__`` convertible to ``sycl::vec<double, N>``
    - ``sycl::vec<int64_t, N>``
  * - ``sycl::vec<half, N>``

      ``__swizzled_vec__`` convertible to ``sycl::vec<half, N>``
    - ``sycl::vec<int16_t, N>``

========================
``sycl::isgreaterequal``
========================

.. rubric:: Overloads 1-3

::

  bool isgreaterequal(float x, float y);
  bool isgreaterequal(double x, double y);
  bool isgreaterequal(half x, half y);

Returns the value ``(x >= y)``.

.. rubric:: Overload 4

::

  template<typename NonScalar1, typename NonScalar2>
  /*return-type*/ isgreaterequal(NonScalar1 x, NonScalar2 y);

Available only if all of the following conditions are met:

* One of the following conditions must hold for ``NonScalar1``
  and ``NonScalar2``:

  * Both ``NonScalar1`` and ``NonScalar2`` are ``sycl::marray``;
  * ``NonScalar1`` and ``NonScalar2`` are any combination of
    ``sycl::vec`` and the ``__swizzled_vec__`` type;
* ``NonScalar1`` and ``NonScalar2`` have the same number of
  elements and the same element type;
* The element type is ``float``, ``double``, or ``half``.

If ``NonScalar1`` is ``sycl::marray``, the value ``(x[i] >= y[i])``
for each element of ``x`` and ``y``. If ``NonScalar1`` is
``sycl::vec`` or the ``__swizzled_vec__`` type, returns the value
``((x[i] >= y[i]) ? -1 : 0)`` for each element of ``x`` and ``y``.

The return type depends on ``NonScalar1``:

.. list-table::
  :header-rows: 1

  * - ``NonScalar1``
    - Return Type
  * - ``sycl::marray<float, N>``

      ``sycl::marray<double, N>``

      ``sycl::marray<half, N>``
    - ``sycl::marray<bool, N>``
  * - ``sycl::vec<float, N>``

      ``__swizzled_vec__`` convertible to ``sycl::vec<float, N>``
    - ``sycl::vec<int32_t, N>``
  * - ``sycl::vec<double, N>``

      ``__swizzled_vec__`` convertible to ``sycl::vec<double, N>``
    - ``sycl::vec<int64_t, N>``
  * - ``sycl::vec<half, N>``

      ``__swizzled_vec__`` convertible to ``sycl::vec<half, N>``
    - ``sycl::vec<int16_t, N>``

================
``sycl::isless``
================

.. rubric:: Overloads 1-3

::

  bool isless(float x, float y);
  bool isless(double x, double y);
  bool isless(half x, half y);

Returns the value ``(x < y)``.

.. rubric:: Overload 4

::

  template<typename NonScalar1, typename NonScalar2>
  /*return-type*/ isless(NonScalar1 x, NonScalar2 y);

Available only if all of the following conditions are met:

* One of the following conditions must hold for ``NonScalar1``
  and ``NonScalar2``:

  * Both ``NonScalar1`` and ``NonScalar2`` are ``sycl::marray``;
  * ``NonScalar1`` and ``NonScalar2`` are any combination of
    ``sycl::vec`` and the ``__swizzled_vec__`` type;
* ``NonScalar1`` and ``NonScalar2`` have the same number of
  elements and the same element type;
* The element type is ``float``, ``double``, or ``half``.

If ``NonScalar1`` is ``sycl::marray``, the value ``(x[i] < y[i])``
for each element of ``x`` and ``y``. If ``NonScalar1`` is
``sycl::vec`` or the ``__swizzled_vec__`` type, returns the value
``((x[i] < y[i]) ? -1 : 0)`` for each element of ``x`` and ``y``.

The return type depends on ``NonScalar1``:

.. list-table::
  :header-rows: 1

  * - ``NonScalar1``
    - Return Type
  * - ``sycl::marray<float, N>``

      ``sycl::marray<double, N>``

      ``sycl::marray<half, N>``
    - ``sycl::marray<bool, N>``
  * - ``sycl::vec<float, N>``

      ``__swizzled_vec__`` convertible to ``sycl::vec<float, N>``
    - ``sycl::vec<int32_t, N>``
  * - ``sycl::vec<double, N>``

      ``__swizzled_vec__`` convertible to ``sycl::vec<double, N>``
    - ``sycl::vec<int64_t, N>``
  * - ``sycl::vec<half, N>``

      ``__swizzled_vec__`` convertible to ``sycl::vec<half, N>``
    - ``sycl::vec<int16_t, N>``

=====================
``sycl::islessequal``
=====================

.. rubric:: Overloads 1-3

::

  bool islessequal(float x, float y);
  bool islessequal(double x, double y);
  bool islessequal(half x, half y);

Returns the value ``(x <= y)``.

.. rubric:: Overload 4

::

  template<typename NonScalar1, typename NonScalar2>
  /*return-type*/ islessequal(NonScalar1 x, NonScalar2 y);

Available only if all of the following conditions are met:

* One of the following conditions must hold for ``NonScalar1``
  and ``NonScalar2``:

  * Both ``NonScalar1`` and ``NonScalar2`` are ``sycl::marray``;
  * ``NonScalar1`` and ``NonScalar2`` are any combination of
    ``sycl::vec`` and the ``__swizzled_vec__`` type;
* ``NonScalar1`` and ``NonScalar2`` have the same number of
  elements and the same element type;
* The element type is ``float``, ``double``, or ``half``.

If ``NonScalar1`` is ``sycl::marray``, the value ``(x[i] <= y[i])``
for each element of ``x`` and ``y``. If ``NonScalar1`` is
``sycl::vec`` or the ``__swizzled_vec__`` type, returns the value
``((x[i] <= y[i]) ? -1 : 0)`` for each element of ``x`` and ``y``.

The return type depends on ``NonScalar1``:

.. list-table::
  :header-rows: 1

  * - ``NonScalar1``
    - Return Type
  * - ``sycl::marray<float, N>``

      ``sycl::marray<double, N>``

      ``sycl::marray<half, N>``
    - ``sycl::marray<bool, N>``
  * - ``sycl::vec<float, N>``

      ``__swizzled_vec__`` convertible to ``sycl::vec<float, N>``
    - ``sycl::vec<int32_t, N>``
  * - ``sycl::vec<double, N>``

      ``__swizzled_vec__`` convertible to ``sycl::vec<double, N>``
    - ``sycl::vec<int64_t, N>``
  * - ``sycl::vec<half, N>``

      ``__swizzled_vec__`` convertible to ``sycl::vec<half, N>``
    - ``sycl::vec<int16_t, N>``

=======================
``sycl::islessgreater``
=======================

.. rubric:: Overloads 1-3

::

  bool islessgreater(float x, float y);
  bool islessgreater(double x, double y);
  bool islessgreater(half x, half y);

Returns the value ``(x < y) || (x > y)``.

.. rubric:: Overload 4

::

  template<typename NonScalar1, typename NonScalar2>
  /*return-type*/ islessgreater(NonScalar1 x, NonScalar2 y);

Available only if all of the following conditions are met:

* One of the following conditions must hold for ``NonScalar1``
  and ``NonScalar2``:

  * Both ``NonScalar1`` and ``NonScalar2`` are ``sycl::marray``;
  * ``NonScalar1`` and ``NonScalar2`` are any combination of
    ``sycl::vec`` and the ``__swizzled_vec__`` type;
* ``NonScalar1`` and ``NonScalar2`` have the same number of
  elements and the same element type;
* The element type is ``float``, ``double``, or ``half``.

If ``NonScalar1`` is ``sycl::marray``, the value
``(x[i] < y[i]) || (x[i] > y[i])``
for each element of ``x`` and ``y``. If ``NonScalar1`` is
``sycl::vec`` or the ``__swizzled_vec__`` type, returns the value
``(((x[i] < y[i]) || (x[i] > y[i])) ? -1 : 0)`` for each element
of ``x`` and ``y``.

The return type depends on ``NonScalar1``:

.. list-table::
  :header-rows: 1

  * - ``NonScalar1``
    - Return Type
  * - ``sycl::marray<float, N>``

      ``sycl::marray<double, N>``

      ``sycl::marray<half, N>``
    - ``sycl::marray<bool, N>``
  * - ``sycl::vec<float, N>``

      ``__swizzled_vec__`` convertible to ``sycl::vec<float, N>``
    - ``sycl::vec<int32_t, N>``
  * - ``sycl::vec<double, N>``

      ``__swizzled_vec__`` convertible to ``sycl::vec<double, N>``
    - ``sycl::vec<int64_t, N>``
  * - ``sycl::vec<half, N>``

      ``__swizzled_vec__`` convertible to ``sycl::vec<half, N>``
    - ``sycl::vec<int16_t, N>``

==================
``sycl::isfinite``
==================

.. rubric:: Overloads 1-3

::

  bool isfinite(float x);
  bool isfinite(double x);
  bool isfinite(half x);

Returns the value ``true`` only if ``x`` has finite ``value``.

.. rubric:: Overload 4

::

  template<typename NonScalar>
  /*return-type*/ isfinite(NonScalar x);

Available only if all of the following conditions are met:

* ``NonScalar`` is ``sycl::marray``, ``sycl::vec``, or the
  ``__swizzled_vec__`` type;
* The element type is ``float``, ``double``, or ``half``.

If ``NonScalar`` is ``sycl::marray``, returns ``true`` for
each element of ``x`` only if ``x[i]`` is a finite value. If
``NonScalar`` is ``sycl::vec`` or the ``__swizzled_vec__`` type,
returns -1 for each element of ``x`` if ``x[i]`` is a finite
value and returns 0 otherwise.

The return type depends on ``NonScalar``:

.. list-table::
  :header-rows: 1

  * - ``NonScalar``
    - Return Type
  * - ``sycl::marray<float, N>``

      ``sycl::marray<double, N>``

      ``sycl::marray<half, N>``
    - ``sycl::marray<bool, N>``
  * - ``sycl::vec<float, N>``

      ``__swizzled_vec__`` convertible to ``sycl::vec<float, N>``
    - ``sycl::vec<int32_t, N>``
  * - ``sycl::vec<double, N>``

      ``__swizzled_vec__`` convertible to ``sycl::vec<double, N>``
    - ``sycl::vec<int64_t, N>``
  * - ``sycl::vec<half, N>``

      ``__swizzled_vec__`` convertible to ``sycl::vec<half, N>``
    - ``sycl::vec<int16_t, N>``

===============
``sycl::isinf``
===============

.. rubric:: Overloads 1-3

::

  bool isinf(float x);
  bool isinf(double x);
  bool isinf(half x);

Returns the value ``true`` only if ``x`` has an
infinity value (either positive or negative).

.. rubric:: Overload 4

::

  template<typename NonScalar>
  /*return-type*/ isinf(NonScalar x);

Available only if all of the following conditions are met:

* ``NonScalar`` is ``sycl::marray``, ``sycl::vec``, or the
  ``__swizzled_vec__`` type;
* The element type is ``float``, ``double``, or ``half``.

If ``NonScalar`` is ``sycl::marray``, returns ``true`` for
each element of ``x`` only if ``x[i]`` has an infinity value.
If ``NonScalar`` is ``sycl::vec`` or the ``__swizzled_vec__``
type, returns -1 for each element of ``x`` if ``x[i]`` has an
infinity value and returns 0 otherwise.

The return type depends on ``NonScalar``:

.. list-table::
  :header-rows: 1

  * - ``NonScalar``
    - Return Type
  * - ``sycl::marray<float, N>``

      ``sycl::marray<double, N>``

      ``sycl::marray<half, N>``
    - ``sycl::marray<bool, N>``
  * - ``sycl::vec<float, N>``

      ``__swizzled_vec__`` convertible to ``sycl::vec<float, N>``
    - ``sycl::vec<int32_t, N>``
  * - ``sycl::vec<double, N>``

      ``__swizzled_vec__`` convertible to ``sycl::vec<double, N>``
    - ``sycl::vec<int64_t, N>``
  * - ``sycl::vec<half, N>``

      ``__swizzled_vec__`` convertible to ``sycl::vec<half, N>``
    - ``sycl::vec<int16_t, N>``

===============
``sycl::isnan``
===============

.. rubric:: Overloads 1-3

::

  bool isnan(float x);
  bool isnan(double x);
  bool isnan(half x);

Returns the value ``true`` only if ``x`` has a NaN value.

.. rubric:: Overload 4

::

  template<typename NonScalar>
  /*return-type*/ isnan(NonScalar x);

Available only if all of the following conditions are met:

* ``NonScalar`` is ``sycl::marray``, ``sycl::vec``, or the
  ``__swizzled_vec__`` type;
* The element type is ``float``, ``double``, or ``half``.

If NonScalar is ``sycl::marray``, returns ``true`` for each
element of ``x`` only if ``x[i]`` has a NaN value. If
``NonScalar`` is ``sycl::vec`` or the ``__swizzled_vec__``
type, returns -1 for each element of ``x`` if ``x[i]`` has
a NaN value and returns 0 otherwise.

The return type depends on ``NonScalar``:

.. list-table::
  :header-rows: 1

  * - ``NonScalar``
    - Return Type
  * - ``sycl::marray<float, N>``

      ``sycl::marray<double, N>``

      ``sycl::marray<half, N>``
    - ``sycl::marray<bool, N>``
  * - ``sycl::vec<float, N>``

      ``__swizzled_vec__`` convertible to ``sycl::vec<float, N>``
    - ``sycl::vec<int32_t, N>``
  * - ``sycl::vec<double, N>``

      ``__swizzled_vec__`` convertible to ``sycl::vec<double, N>``
    - ``sycl::vec<int64_t, N>``
  * - ``sycl::vec<half, N>``

      ``__swizzled_vec__`` convertible to ``sycl::vec<half, N>``
    - ``sycl::vec<int16_t, N>``

==================
``sycl::isnormal``
==================

.. rubric:: Overloads 1-3

::

  bool isnormal(float x);
  bool isnormal(double x);
  bool isnormal(half x);

Returns the value ``true`` only if ``x`` has a normal value.

.. rubric:: Overload 4

::

  template<typename NonScalar>
  /*return-type*/ isnormal(NonScalar x);

Available only if all of the following conditions are met:

* ``NonScalar`` is ``sycl::marray``, ``sycl::vec``, or the
  ``__swizzled_vec__`` type;
* The element type is ``float``, ``double``, or ``half``.

If ``NonScalar`` is ``sycl::marray``, returns ``true`` for
each element of ``x`` only if ``x[i]`` has a normal value.
If ``NonScalar`` is ``sycl::vec`` or the ``__swizzled_vec__``
type, returns -1 for each element of ``x`` if ``x[i]`` has a
normal value and returns 0 otherwise.

The return type depends on ``NonScalar``:

.. list-table::
  :header-rows: 1

  * - ``NonScalar``
    - Return Type
  * - ``sycl::marray<float, N>``

      ``sycl::marray<double, N>``

      ``sycl::marray<half, N>``
    - ``sycl::marray<bool, N>``
  * - ``sycl::vec<float, N>``

      ``__swizzled_vec__`` convertible to ``sycl::vec<float, N>``
    - ``sycl::vec<int32_t, N>``
  * - ``sycl::vec<double, N>``

      ``__swizzled_vec__`` convertible to ``sycl::vec<double, N>``
    - ``sycl::vec<int64_t, N>``
  * - ``sycl::vec<half, N>``

      ``__swizzled_vec__`` convertible to ``sycl::vec<half, N>``
    - ``sycl::vec<int16_t, N>``

===================
``sycl::isordered``
===================

.. rubric:: Overloads 1-3

::

  bool isordered(float x, float y);
  bool isordered(double x, double y);
  bool isordered(half x, half y);

Returns the value ``sycl::isequal(x, x) && sycl::isequal(y, y)``.

.. rubric:: Overload 4

::

  template<typename NonScalar1, typename NonScalar2>
  /*return-type*/ isordered(NonScalar1 x, NonScalar2 y);

Available only if all of the following conditions are met:

* One of the following conditions must hold for ``NonScalar1``
  and ``NonScalar2``:

  * Both ``NonScalar1`` and ``NonScalar2`` are ``sycl::marray``;
  * ``NonScalar1`` and ``NonScalar2`` are any combination of
    ``sycl::vec`` and the ``__swizzled_vec__`` type;
* ``NonScalar1`` and ``NonScalar2`` have the same number of
  elements and the same element type;
* The element type is ``float``, ``double``, or ``half``.

Tests if each element of ``x`` and ``y`` are ordered.

If ``NonScalar1`` is ``marray``, the value
``sycl::isequal(x[i], x[i]) && sycl::isequal(y[i], y[i])`` for
each element of ``x`` and ``y``. If ``NonScalar1`` is ``sycl::vec``
or the ``__swizzled_vec__`` type, returns the value
``((sycl::isequal(x[i], x[i]) && sycl::isequal(y[i], y[i])) ? -1 : 0)``
for each element of ``x`` and ``y``.

The return type depends on ``NonScalar1``:

.. list-table::
  :header-rows: 1

  * - ``NonScalar1``
    - Return Type
  * - ``sycl::marray<float, N>``

      ``sycl::marray<double, N>``

      ``sycl::marray<half, N>``
    - ``sycl::marray<bool, N>``
  * - ``sycl::vec<float, N>``

      ``__swizzled_vec__`` convertible to ``sycl::vec<float, N>``
    - ``sycl::vec<int32_t, N>``
  * - ``sycl::vec<double, N>``

      ``__swizzled_vec__`` convertible to ``sycl::vec<double, N>``
    - ``sycl::vec<int64_t, N>``
  * - ``sycl::vec<half, N>``

      ``__swizzled_vec__`` convertible to ``sycl::vec<half, N>``
    - ``sycl::vec<int16_t, N>``

=====================
``sycl::isunordered``
=====================

.. rubric:: Overloads 1-3

::

  bool isunordered(float x, float y);
  bool isunordered(double x, double y);
  bool isunordered(half x, half y);

Returns the value ``sycl::isnan(x) || sycl::isnan(y)``.

.. rubric:: Overload 4

::

  template<typename NonScalar1, typename NonScalar2>
  /*return-type*/ isunordered(NonScalar1 x, NonScalar2 y);

Available only if all of the following conditions are met:

* One of the following conditions must hold for ``NonScalar1``
  and ``NonScalar2``:

  * Both ``NonScalar1`` and ``NonScalar2`` are ``sycl::marray``;
  * ``NonScalar1`` and ``NonScalar2`` are any combination of
    ``sycl::vec`` and the ``__swizzled_vec__`` type;
* ``NonScalar1`` and ``NonScalar2`` have the same number of
  elements and the same element type;
* The element type is ``float``, ``double``, or ``half``.

Tests if each element of ``x`` and ``y`` are unordered.

If ``NonScalar1`` is ``marray``, the value
``sycl::isnan(x[i]) || sycl::isnan(y[i])`` for
each element of ``x`` and ``y``. If ``NonScalar1`` is ``sycl::vec``
or the ``__swizzled_vec__`` type, returns the value
``((sycl::isnan(x[i]) || sycl::isnan(y[i])) ? -1 : 0)``
for each element of ``x`` and ``y``.

The return type depends on ``NonScalar1``:

.. list-table::
  :header-rows: 1

  * - ``NonScalar1``
    - Return Type
  * - ``sycl::marray<float, N>``

      ``sycl::marray<double, N>``

      ``sycl::marray<half, N>``
    - ``sycl::marray<bool, N>``
  * - ``sycl::vec<float, N>``

      ``__swizzled_vec__`` convertible to ``sycl::vec<float, N>``
    - ``sycl::vec<int32_t, N>``
  * - ``sycl::vec<double, N>``

      ``__swizzled_vec__`` convertible to ``sycl::vec<double, N>``
    - ``sycl::vec<int64_t, N>``
  * - ``sycl::vec<half, N>``

      ``__swizzled_vec__`` convertible to ``sycl::vec<half, N>``
    - ``sycl::vec<int16_t, N>``

=================
``sycl::signbit``
=================

.. rubric:: Overloads 1-3

::

  bool signbit(float x);
  bool signbit(double x);
  bool signbit(half x);

Returns the value ``true`` only if the sign bit of ``x`` is set.

.. rubric:: Overload 4

::

  template<typename NonScalar>
  /*return-type*/ isnormal(NonScalar x);

Available only if all of the following conditions are met:

* ``NonScalar`` is ``sycl::marray``, ``sycl::vec``, or the
  ``__swizzled_vec__`` type;
* The element type is ``float``, ``double``, or ``half``.

If ``NonScalar`` is ``sycl::marray``, returns ``true`` for
each element of ``x`` only if the sign bit of ``x[i]`` is set.
If ``NonScalar`` is ``sycl::vec`` or the ``__swizzled_vec__``
type, returns -1 for each element of ``x`` if the sign bit of
``x[i]`` is set and returns 0 otherwise.

The return type depends on ``NonScalar``:

.. list-table::
  :header-rows: 1

  * - ``NonScalar``
    - Return Type
  * - ``sycl::marray<float, N>``

      ``sycl::marray<double, N>``

      ``sycl::marray<half, N>``
    - ``sycl::marray<bool, N>``
  * - ``sycl::vec<float, N>``

      ``__swizzled_vec__`` convertible to ``sycl::vec<float, N>``
    - ``sycl::vec<int32_t, N>``
  * - ``sycl::vec<double, N>``

      ``__swizzled_vec__`` convertible to ``sycl::vec<double, N>``
    - ``sycl::vec<int64_t, N>``
  * - ``sycl::vec<half, N>``

      ``__swizzled_vec__`` convertible to ``sycl::vec<half, N>``
    - ``sycl::vec<int16_t, N>``

=============
``sycl::any``
=============

.. rubric:: Overload 1

::

  template<typename GenInt>
  /*return-type*/ any(GenInt x);

Available only if ``GenInt`` is one of the following types:

* ``sycl::marray<bool, N>``
* ``sycl::vec<int8_t, N>``
* ``sycl::vec<int16_t, N>``
* ``sycl::vec<int32_t, N>``
* ``sycl::vec<int64_t, N>``
* ``__swizzled_vec__`` that is
  convertible to ``sycl::vec<int8_t, N>``
* ``__swizzled_vec__`` that is
  convertible to ``sycl::vec<int16_t, N>``
* ``__swizzled_vec__`` that is
  convertible to ``sycl::vec<int32_t, N>``
* ``__swizzled_vec__`` that is
  convertible to ``sycl::vec<int64_t, N>``

When ``x`` is ``sycl::marray``, returns a Boolean
telling whether any element of ``x`` is ``true``.
When ``x`` is ``sycl::vec`` or the ``__swizzled_vec__``
type, returns the value 1 if any element in ``x`` has
its most significant bit set, otherwise returns the value 0.

The return type is ``bool`` if ``GenInt`` is ``sycl::marray``.
Otherwise, the return type is ``int``.

.. rubric:: Overload 2

::

  template<typename GenInt>
  bool any(GenInt x);

.. warning:: This overload is deprecated in SYCL 2020.

Available only if ``GenInt`` is one of the following types:

* ``signed char``
* ``short``
* ``int``
* ``long``
* ``long long``
* ``sycl::marray<signed char, N>``
* ``sycl::marray<short, N>``
* ``sycl::marray<int, N>``
* ``sycl::marray<long, N>``
* ``sycl::marray<long long, N>``

When ``x`` is a scalar, returns a Boolean telling whether
the most significant bit of ``x`` is set. When ``x`` is
``sycl::marray``, returns a Boolean telling whether the
most significant bit of any element in ``x`` is set.

=============
``sycl::all``
=============

.. rubric:: Overload 1

::

  template<typename GenInt>
  /*return-type*/ all(GenInt x);

Available only if ``GenInt`` is one of the following types:

* ``sycl::marray<bool, N>``
* ``sycl::vec<int8_t, N>``
* ``sycl::vec<int16_t, N>``
* ``sycl::vec<int32_t, N>``
* ``sycl::vec<int64_t, N>``
* ``__swizzled_vec__`` that is
  convertible to ``sycl::vec<int8_t, N>``
* ``__swizzled_vec__`` that is
  convertible to ``sycl::vec<int16_t, N>``
* ``__swizzled_vec__`` that is
  convertible to ``sycl::vec<int32_t, N>``
* ``__swizzled_vec__`` that is
  convertible to ``sycl::vec<int64_t, N>``

When ``x`` is ``sycl::marray``, returns a Boolean
telling whether all elements of ``x`` are ``true``.
When ``x`` is ``sycl::vec`` or the ``__swizzled_vec__``
type, returns the value 1 if all elements in ``x`` have
their most significant bit set, otherwise returns the value 0.

The return type is ``bool`` if ``GenInt`` is ``sycl::marray``.
Otherwise, the return type is ``int``.

.. rubric:: Overload 2

::

  template<typename GenInt>
  bool all(GenInt x);

.. warning:: This overload is deprecated in SYCL 2020.

Available only if ``GenInt`` is one of the following types:

* ``signed char``
* ``short``
* ``int``
* ``long``
* ``long long``
* ``sycl::marray<signed char, N>``
* ``sycl::marray<short, N>``
* ``sycl::marray<int, N>``
* ``sycl::marray<long, N>``
* ``sycl::marray<long long, N>``

When ``x`` is a scalar, returns a Boolean telling whether
the most significant bit of ``x`` is set. When ``x`` is
``sycl::marray``, returns a Boolean telling whether the
most significant bit of all elements in ``x`` are set.

===================
``sycl::bitselect``
===================

::

  template<typename GenType1, typename GenType2, typename GenType3>
  /*return-type*/ bitselect(GenType1 a, GenType2 b, GenType3 c);

Available only if all of the following conditions are met:

* ``GenType1`` is one of the following types:

  * One of the `generic scalar types` as defined above;
  * ``sycl::marray<T, N>``, where ``T`` is one of the
    `generic scalar types`;
  * ``sycl::vec<T, N>``, where ``T`` is one of the
    `vector element types` as defined above;
  * ``__swizzled_vec__`` that is convertible to
    ``sycl::vec<T, N>``, where ``T`` is one of the
    `vector element types`;
* If ``GenType1`` is not ``sycl::vec`` or the ``__swizzled_vec__``
  type, then ``GenType2`` and ``GenType3`` must be the same as
  ``GenType1``;
* If ``GenType1`` is ``sycl::vec`` or the ``__swizzled_vec__``
  type, then ``GenType2`` and ``GenType3`` must also be
  ``sycl::vec`` or the ``__swizzled_vec__`` type, and all three
  must have the same element type and the same number of elements.

When the input parameters are scalars, returns a result where each
bit of the result is the corresponding bit of ``a`` if the
corresponding bit of ``c`` is 0. Otherwise it is the corresponding
bit of ``b``.

When the input parameters are not scalars, returns a result for
each element where each bit of the result for element ``i`` is
the corresponding bit of ``a[i]`` if the corresponding bit of
``c[i]`` is 0. Otherwise it is the corresponding bit of ``b[i]``.

The return type is ``GenType1`` unless ``GenType1`` is the
``__swizzled_vec__`` type, in which case the return type is
the corresponding ``sycl::vec``.

================
``sycl::select``
================

.. rubric:: Overload 1

::

  template<typename Scalar>
  Scalar select(Scalar a, Scalar b, bool c);

Available only if Scalar is one of the `generic scalar types`
as defined above.

Returns the value ``(c ? b : a)``.

.. rubric:: Overload 2

::

  template<typename NonScalar1, typename NonScalar2, typename NonScalar3>
  /*return-type*/ select(NonScalar1 a, NonScalar2 b, NonScalar3 c);

Available only if all of the following conditions are met:

* ``NonScalar1`` is one of the following types:

  * ``sycl::marray<T, N>``, where ``T`` is one of
    the `generic scalar types` as defined above;
  * ``sycl::vec<T, N>``, where ``T`` is one of the
    `vector element types` as defined above;
  * ``__swizzled_vec__`` that is convertible to
    ``sycl::vec<T, N>``, where ``T`` is one of the
    `vector element types`;
* If ``NonScalar1`` is ``sycl::marray``, then:

  * ``NonScalar2`` must be the same as ``NonScalar1``;
  * ``NonScalar3`` must be ``sycl::marray`` with element
    type bool and the same number of elements as ``NonScalar1``;
* If ``NonScalar1`` is ``sycl::vec`` or the ``__swizzled_vec__``
  type, then:

  * ``NonScalar2`` must also be ``sycl::vec`` or the ``__swizzled_vec__``
    type, and both must have the same element type and the same number
    of elements; and
  * ``NonScalar3`` must be ``sycl::vec`` or the ``__swizzled_vec__``
    type with the same number of elements as ``NonScalar1``. The
    element type of ``NonScalar3`` must be a signed or unsigned
    integer with the same number of bits as the element type of ``NonScalar1``.

If ``NonScalar1`` is ``sycl::marray``, return the value ``(c[i] ? b[i] : a[i])``
for each element of ``a``, ``b``, and ``c``.

If ``NonScalar1`` is ``sycl::vec`` or the ``__swizzled_vec__`` type,
returns the value ``((MSB of c[i] is set) ? b[i] : a[i])`` for each
element of ``a``, ``b``, and ``c``.

The return type is ``NonScalar1`` unless ``NonScalar1`` is the
``__swizzled_vec__`` type, in which case the return type is the
corresponding ``sycl::vec``.
