..
  Copyright 2020 The Khronos Group Inc.
  SPDX-License-Identifier: CC-BY-4.0

*********
Platforms
*********

.. _platform:

.. rst-class:: api-class

========
platform
========

::
   
   class platform;

Abstraction for SYCL platform.

A platform contains 1 or more SYCL devices, or a host device.

.. seealso:: |SYCL_SPEC_PLATFORM|
   
.. member-toc::

.. _platform-example:

.. rubric:: Example

Enumerate the platforms and the devices they contain.
   
.. literalinclude:: /examples/get-platforms.cpp
   :lines: 5-
   :linenos:

Output:

.. literalinclude:: /examples/get-platforms.out
   :lines: 5-


(constructors)
==============

::
   
  platform();
  explicit platform(cl_platform_id platformID);
  explicit platform(const device_selector &deviceSelector);

Construct a SYCL platform instance.

The default constructor creates a host platform. When passed a
``cl_platform_id``, an OpenCL|trade| platform is used to construct the
platform. The ``cl_platform_id`` is retained and available via
get_. When passed a :ref:`device_selector`, a platform is constructed
that includes the preferred device.


get
===

::
   
  cl_platform_id get() const;

Returns the OpenCL device associated with the platform.

Only call this when the platform constructor was passed a
``cl_platform_id``.

.. _platform-get_devices:

get_devices
===========

::
   
  vector_class<device> get_devices(
     info::device_type = info::device_type::all) const;

Returns vector of SYCL devices associated with the platform and
filtered by :ref:`info-device_type`

.. rubric:: Example

See `platform-example`_.


.. _platform-get_info:

get_info
========

::
   
  template< info::platform param >
  typename info::param_traits<info::platform, param>::return_type get_info() const;

Returns information about the platform as determined by ``param``.

See `Platform Info`_ for details.

.. rubric:: Example

See `platform-example`_.

.. _platform-has_extension:

has_extension
=============

::
   
  bool has_extension(const string_class &extension) const;

Returns True if the platform has ``extension``.
  
is_host
=======

::
   
  bool is_host() const;

Returns True if the platform contains a SYCL host device

get_platforms
=============

::
   
  static vector_class<platform> get_platforms();

Returns a vector_class containing SYCL platforms bound to the system.

.. rubric:: Example

See `platform-example`_.

=============
Platform Info
=============

::

  enum class platform : unsigned int {
    profile,
    version,
    name,
    vendor,
    extensions
  };

.. rubric:: Namespace

::

   info

Used as a template parameter for get_info_ to determine
the type of information.

===========  ==========================  ===
Descriptor   Return type                 Description
===========  ==========================  ===
profile      string_class                OpenCL profile
version      string_class                OpenCL software driver version
name         string_class                Device name of the platform
vendor       string_class                Vendor name
extensions   vector_class<string_class>  Extension names supported by the platform
===========  ==========================  ===
