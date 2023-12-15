..
  Copyright 2020 The Khronos Group Inc.
  SPDX-License-Identifier: CC-BY-4.0

.. _scalar-types:

************
Scalar types
************

The fundamental C++ data types which are supported in ``SYCL`` are
described in |SYCL_SPEC_FUND_DATA_TYPE|. Note these types are
fundamental and therefore do not exist within the ``sycl`` namespace.

Additional scalar data types which are supported by SYCL
within the ``sycl`` namespace are described below :

=================
Scalar data types
=================

``byte``
========

An unsigned 8-bit integer. This is deprecated in SYCL 2020
since C++17 ``std::byte`` can be used instead.

``half``
========

A 16-bit floating-point. The half data type must conform to the
IEEE 754-2008 half precision storage format. This type is only supported
on devices that have ``aspect::fp16``. ``std::numeric_limits``
must be specialized for the half data type.
