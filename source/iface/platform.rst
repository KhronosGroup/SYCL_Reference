..
   // Copyright (c) 2011-2020 The Khronos Group, Inc.
   //
   // Licensed under the Apache License, Version 2.0 (the License);
   // you may not use this file except in compliance with the License.
   // You may obtain a copy of the License at
   //
   //     http://www.apache.org/licenses/LICENSE-2.0
   //
   // Unless required by applicable law or agreed to in writing, software
   // distributed under the License is distributed on an AS IS BASIS,
   // WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   // See the License for the specific language governing permissions and
   // limitations under the License.

.. _platform-class:

.. rst-class:: api-class
	       
========
platform
========

::
   
   class platform;

Abstraction for SYCL platform.

.. rubric:: Member functions

================  =======================
`(constructor)`_  constructs a platform
destructor        destroys a platform
get_              returns OpenCL platform ID
get_devices_      returns devices bound to the platform
get_info_         queries properties of the platform
has_extension_    checks if platform has an extension
is_host_          checks if platform has a SYCL host device
================  =======================

.. rubric:: Nonmember functions

==============  =======================
get_platforms_  returns available platforms
==============  =======================

.. _platform-example:

.. rubric:: Example

Enumerate the platforms and the devices they contain.
   
.. literalinclude:: /examples/get-platforms.cpp

Output:

.. literalinclude:: /examples/get-platforms.out


.. _platform-constructor:

(constructor)
=============

::
   
  platform();

.. parsed-literal::
   
  explicit platform(cl_platform_id platformID);             [#opencl]_

.. parsed-literal::
   
  explicit platform(const device_selector &deviceSelector); [#selector]_

Constructs a platform handle.

.. [#opencl] Constructs a SYCL platform that retains an OpenCL id
.. [#selector] Selects a platform that contains the desired device
	     

.. rubric:: Parameters

| ``platformID`` - OpenCL platform ID
| ``deviceSelector`` -  Platform must contain the selected device

get
===

::
   
  cl_platform_id get() const;

Returns OpenCL platform id used in the constructor.

.. rubric:: Returns

OpenCL platform id	    

get_devices
===========

::
   
  vector_class<device> get_devices(
     info::device_type = info::device_type::all) const;

Returns vector of devices of the requested type

.. rubric:: Parameters

| ``device_type`` - limits type of device returned

.. rubric:: Returns

``vector`` containing devices of the specified type bound to the
platform.

.. rubric:: Example

See `platform-example`_.


get_info
========

::
   
  template< info::platform param >
  typename info::param_traits<info::platform, param>::return_type get_info() const;

Returns information about the platform, as specified by ``param``.

.. rubric:: Returns

Requested information

.. rubric:: Example

See `platform-example`_.


.. _platform-has_extension:

has_extension
=============

::
   
  bool has_extension(const string_class &extension) const;

Checks if the platform has the requested extension.
  

.. rubric:: Parameters

| ``extension`` -

.. rubric:: Returns

True if the platform has ``extension``

is_host
=======

::
   
  bool is_host() const;

Checks if the platform contains a SYCL :term:`host device`

.. rubric:: Returns

True if the platform contains a host device


get_platforms
=============

::
   
  static vector_class<platform> get_platforms();

Returns vector of platforms

.. rubric:: Returns

vector_class containing SYCL platforms bound to the system

.. rubric:: Example

See `platform-example`_.
