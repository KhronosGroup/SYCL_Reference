..
  Copyright 2024 The Khronos Group Inc.
  SPDX-License-Identifier: CC-BY-4.0

*********
Platforms
*********

.. _platform:

==================
``sycl::platform``
==================

::

   class platform;

Abstraction for SYCL platform.

The ``sycl::platform`` class encapsulates a single SYCL platform on which
SYCL kernel functions may be executed. A SYCL platform must be associated
with a single SYCL backend.

A ``sycl::platform`` is also associated with one or more SYCL :ref:`devices
<device>` associated with the same SYCL backend.

.. seealso:: |SYCL_SPEC_PLATFORM|


(constructors)
==============

::

  platform();

  template <typename DeviceSelector>
  explicit platform(const DeviceSelector&);

Construct a ``sycl::platform`` instance.

The default constructor create a ``sycl::platform`` instance that is a
copy of the platform which contains the device returned by
``sycl::default_selector_v``. When passed a :ref:`device
selector <device-selectors>`, constructs a ``sycl::platform`` instance
that is a copy of the platform which contains the device returned
by the device selector parameter.

================
Member functions
================

``get_backend``
===============

::

  sycl::backend get_backend() const noexcept;

Returns a ``sycl::backend`` identifying the SYCL backend associated with
this ``sycl::platform``.

``get_info``
============

::

  template <typename Param>
  typename Param::return_type get_info() const;

Queries this ``sycl::platform`` for information requested by the template
parameter ``Param``. The type alias ``Param::return_type`` must be defined in
accordance with the info parameters in `sycl::info::platform`_
to facilitate returning the type associated with the ``Param`` parameter.

.. rubric:: Example

See `platform-example`_.

``get_backend_info``
====================

::

  template <typename Param>
  typename Param::return_type get_backend_info() const;


Queries this ``sycl::platform`` for SYCL backend-specific information requested
by the template parameter ``Param``. The type alias ``Param::return_type``
must be defined in accordance with the SYCL backend specification. Must throw
an exception with the ``sycl::errc::backend_mismatch`` error code if the SYCL
backend that corresponds with ``Param`` is different from the SYCL backend
that is associated with this ``sycl::platform``.


``has``
=======

::

  bool has(sycl::aspect asp) const;

Returns true if all of the SYCL devices associated
with this ``sycl::platform`` have the given aspect.

``has_extension``
=================

::

  bool has_extension(const std::string& extension) const;

Deprecated, use ``has()`` instead.

Returns true if this ``sycl::platform`` supports the extension queried
by the ``extension`` parameter. A ``sycl::platform`` can only support
an extension if all associated SYCL devices support that extension.

``get_devices``
===============

::

  std::vector<sycl::device>
  get_devices(sycl::info::device_type deviceType = sycl::info::device_type::all) const;

Returns a ``std::vector`` containing all the root devices associated with this
``sycl::platform`` which have the device type encapsulated by ``deviceType``.

.. rubric:: Example

See `platform-example`_.

=======================
Static member functions
=======================

``get_platforms``
=================

::

  static std::vector<sycl::platform> get_platforms();

Returns a ``std::vector`` containing all SYCL platforms from all SYCL backends
available in the system.

.. rubric:: Example

See `platform-example`_.

=======================
Information descriptors
=======================

``sycl::info::platform``
========================

::

  namespace sycl::info::platform {

  struct version;
  struct name;
  struct vendor;
  struct extensions;

  }  // namespace sycl::info::platform

Used as a template parameter for get_info_ to determine
the type of information.

.. rubric:: ``sycl::info::platform::version``

Returns a backend-defined platform version.

+--------------------------------------+
| Return type: ``std::string``         |
+--------------------------------------+


.. rubric:: ``sycl::info::platform::name``

Returns the name of the platform.

+--------------------------------------+
| Return type: ``std::string``         |
+--------------------------------------+


.. rubric:: ``sycl::info::platform::vendor``

Returns the name of the vendor providing the platform.

+--------------------------------------+
| Return type: ``std::string``         |
+--------------------------------------+


.. rubric:: ``sycl::info::platform::extensions``

Deprecated, use ``sycl::device::get_info()``
with ``sycl::info::device::aspects`` instead.
Returns the extensions supported by the platform.

+---------------------------------------------------+
| Return type: ``std::vector<std::string>``         |
+---------------------------------------------------+

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
   :language: none
   :lines: 5-
