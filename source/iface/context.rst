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

=======
Context
=======

::
   
  class context;
  
.. rubric:: Member functions

==================  =======================
`(constructors)`_   constructs a context
get_                returns OpenCL conext ID
is_host_            checks if contains a SYCL host device
get_platform_
get_devices_        returns devices bound to the context
get_info_           queries properties
==================  =======================


(constructors)
==============

::
   
  explicit context(const property_list &propList = {});
  context(async_handler asyncHandler,
          const property_list &propList = {});
  context(const device &dev, const property_list &propList = {});
  context(const device &dev, async_handler asyncHandler,
          const property_list &propList = {});
  context(const platform &plt, const property_list &propList = {});
  context(const platform &plt, async_handler asyncHandler,
          const property_list &propList = {});
  context(const vector_class<device> &deviceList,
          const property_list &propList = {});
  context(const vector_class<device> &deviceList,
          async_handler asyncHandler, const property_list &propList = {});
  context(cl_context clContext, async_handler asyncHandler = {});

.. rubric:: Parameters

=================  ===	    
propList
asyncHandler
dev
plt
deviceList
=================  ===	    

get
===

::
   
  cl_context get() const;

	    
is_host
=======

::
   
  bool is_host() const;

	    
get_platform
============

::
   
  platform get_platform() const;

	    
get_devices
===========

::
   
  vector_class<device> get_devices() const;

	    
get_info
========

::
   
  template <info::context param>
  typename info::param_traits<info::context, param>::return_type get_info() const;

.. rubric:: Template parameters

=================  ===	    
param
=================  ===	    
	    
