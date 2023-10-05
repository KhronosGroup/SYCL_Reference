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
  template <typename DeviceSelector> explicit platform(const DeviceSelector&);

Construct a SYCL platform instance.

The default constructor create a SYCL platform instance that is a
copy of the platform which contains the device returned by
default_selector_v. When passed a :ref:`device selector<device-selectors>`,
constructs a SYCL platform instance that is a copy of the platform which
contains the device returned by the device selector parameter.

===============
Member function
===============

``get_backend``
===============

::

  backend get_backend() const noexcept;

Returns a backend identifying the SYCL backend associated with
this platform.

``get_info``
============

::

  template <typename Param>
  typename Param::return_type get_info() const;

Queries this SYCL platform for information requested by the template
parameter Param. The type alias Param::return_type must be defined in
accordance with the info parameters in :ref:`device descriptors<device>`
to facilitate returning the type associated with the Param parameter.

``get_backend_info``
====================

::

  template <typename Param>
  typename Param::return_type get_backend_info() const;


Queries this SYCL platform for SYCL backend-specific information requested
by the template parameter Param. The type alias Param::return_type must be
defined in accordance with the SYCL backend specification. Must throw an
exception with the errc::backend_mismatch error code if the SYCL backend
that corresponds with Param is different from the SYCL backend that is
associated with this platform.

.. rubric:: Example

See `platform-example`_.


.. _platform-get_info:


``has``
=======

::

  bool has(sycl::aspect asp) const;

Returns true if all of the SYCL devices associated
with this SYCL platform have the given aspect.

``has_extension``
=================

::

  bool has_extension(const std::string& extension) const;

Deprecated, use has() instead.

Returns true if this SYCL platform supports the extension queried by
the extension parameter. A SYCL platform can only support an extension
if all associated SYCL devices support that extension.

``get_devices``
===============

::

  std::vector<device>
  get_devices(info::device_type deviceType = info::device_type::all) const;

Returns a std::vector containing all the root devices associated with this
SYCL platform which have the device type encapsulated by deviceType.

======================
Static member function
======================

``get_platforms``
=================

::

  static std::vector<platform> get_platforms();

Returns a std::vector containing all SYCL platforms from all SYCL backends
available in the system.

.. rubric:: Example

See `platform-example`_.

=======================
Information descriptors
=======================

========================
``sycl::info::platform``
========================

::

  enum class platform : unsigned int {
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
   * - version
     - std::string
     - Returns a backend-defined platform version.
   * - name
     - std::string
     - Returns the name of the platform.
   * - vendor
     - std::string
     - Returns the name of the vendor providing the platform.
   * - extensions
     - std::vector<std::string>
     - Deprecated, use sycl::device::get_info() with sycl::info::device::aspects instead.
       Returns the extensions supported by the platform.


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
