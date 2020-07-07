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

********
Contexts
********

.. _context:

.. rst-class:: api-class
	       
=======
context
=======

::
   
  class context;
  
A context encapsulates a single SYCL platform and a collection of SYCL
devices associated with the platform.

A context may include a subset of the devices provided by the
platform. The same platform may be associated with more than one
context, but a device can only be part of a single context.

.. member-toc::

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

Construct a context.

The parameters to the constructor allow control of the devices and
platforms associated with the context. The constructor uses the
:ref:`default selector <built-in-device-selectors>` when no platforms
or devices are supplied.


.. rubric:: Parameters

propList
  See `Context Properties`_.
asyncHandler
  Called to report asynchronous SYCL exceptions for this context
dev
  Constructed context contains device
deviceList
  Constructed context contains devices
plt
  Constructed context contains platform
clContext
  Constructed context contains cl_context


.. todo:: Examples that combines the functions

	  

Constructs a context

get
===

::
   
  cl_context get() const;

	    
Returns cl_context that was passed in constructor.

is_host
=======

::
   
  bool is_host() const;

Returns True if this context is a host context.

get_platform
============

::
   
  platform get_platform() const;

Return platform associated with this context.
	    
get_devices
===========

::
   
  vector_class<device> get_devices() const;

	    
Returns vector of devices associated with this context.

get_info
========

::
   
  template <info::context param>
  typename info::param_traits<info::context, param>::return_type get_info() const;

Returns information about the context as determined by ``param``. See
`Context Info`_ for details.
	    
.. include:: property_methods.inc.rst
	     
============
Context Info
============

::

  enum class context : int {
    reference_count,
    platform,
    devices
  };

.. rubric:: Namespace

::

   info

Used as a template parameter for get_info_ to determine the type of
information.

===============  ==========================  ===
Descriptor       Return type                 Description
===============  ==========================  ===
reference_count  cl_uint                     Reference count of the underlying cl_context
platform         platform                    SYCL platform for the context
devices          vector_class<device>        SYCL devices associated with this platform
===============  ==========================  ===


==================
Context Properties
==================

SYCL does not define any properties for context_.

