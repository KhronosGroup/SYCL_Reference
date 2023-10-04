..
  Copyright 2020 The Khronos Group Inc.
  SPDX-License-Identifier: CC-BY-4.0

*********
Platforms
*********

.. _platform:

.. rst-class:: api-class

==================
``sycl::platform``
==================

::

   class platform;

Abstraction for SYCL platform.

The SYCL platform class encapsulates a single SYCL platform on which SYCL
kernel functions may be executed. A SYCL platform must be associated
with a single SYCL backend.

A SYCL platform is also associated with one or more SYCL devices
associated with the same SYCL backend.

.. seealso:: |SYCL_SPEC_PLATFORM|


(constructors)
==============

::

  platform();
  explicit platform(cl_platform_id platformID);
  explicit platform(const sycl::device_selector &deviceSelector);

Construct a SYCL platform instance.

The default constructor create a SYCL platform instance that is a
copy of the platform which
contains the device returned by default_selector_v. When passed a
``cl_platform_id``, an OpenCL|trade| platform is used to construct the
platform. The ``cl_platform_id`` is retained and available via
get_. When passed a :ref:`device_selector`, a platform is constructed
that includes the preferred device.


``get``
=======

::

  cl_platform_id get() const;

Returns the OpenCL device associated with the platform.

Only call this when the platform constructor was passed a
``cl_platform_id``.

.. _platform-get_devices:

``get_devices``
===============

::

  sycl::vector_class<sycl::device> get_devices(
     sycl::info::device_type = sycl::info::device_type::all) const;

Returns vector of SYCL devices associated with the platform and
filtered by :ref:`info-device_type`

.. rubric:: Example

See `platform-example`_.


.. _platform-get_info:

``get_info``
============

::

  template< sycl::info::platform param >
  typename sycl::info::param_traits<sycl::info::platform, param>::return_type get_info() const;

Returns information about the platform as determined by ``param``.

See `sycl::info::platform`_ for details.

.. rubric:: Example

See `platform-example`_.

.. _platform-has_extension:

``has``
=================

::

  bool has(sycl::aspect asp) const

Returns true if all of the SYCL devices associated
with this SYCL platform have the given aspect.


``get_platforms``
=================

::

  static sycl::vector_class<platform> get_platforms();

Returns a vector_class containing SYCL platforms bound to the system.

.. rubric:: Example

See `platform-example`_.

========================
``sycl::info::platform``
========================

::

  enum class platform : unsigned int {
    profile,
    version,
    name,
    vendor,
    extensions
  };

Used as a template parameter for get_info_ to determine
the type of information.

.. list-table::
   :header-rows: 1

   * - Descriptor
     - Return type
     - Description
   * - profile
     - string_class
     - OpenCL profile
   * - version
     - string_class
     - Returns a backend-defined platform version.
   * - name
     - string_class
     - Returns the name of the platform.
   * - vendor
     - string_class
     - Returns the name of the vendor providing the platform.
   * - extensions
     - vector_class<string_class>
     - Deprecated, use sycl::device::get_info() with sycl::info::device::aspects instead.


.. _platform-example:

=========
Example 1
=========

Enumerate the platforms and the devices they contain.

.. literalinclude:: /examples/get-platforms.cpp
   :lines: 5-
   :linenos:

Output:

.. literalinclude:: /examples/get-platforms.out
   :lines: 5-
