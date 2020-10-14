..
  Copyright 2020 The Khronos Group Inc.
  SPDX-License-Identifier: CC-BY-4.0

********
Contexts
********

.. _context:

.. rst-class:: api-class
	       
=============
sycl::context
=============

::
   
  class context;
  
A context encapsulates a single SYCL platform and a collection of SYCL
devices associated with the platform.

A context may include a subset of the devices provided by the
platform. The same platform may be associated with more than one
context, but a device can only be part of a single context.

.. seealso:: |SYCL_SPEC_CONTEXT|

(constructors)
==============

::
   
  explicit context(const sycl::property_list &propList = {});
  context(sycl::async_handler asyncHandler,
          const sycl::property_list &propList = {});
  context(const sycl::device &dev, const sycl::property_list &propList = {});
  context(const sycl::device &dev, sycl::async_handler asyncHandler,
          const sycl::property_list &propList = {});
  context(const sycl::platform &plt, const sycl::property_list &propList = {});
  context(const sycl::platform &plt, sycl::async_handler asyncHandler,
          const sycl::property_list &propList = {});
  context(const sycl::vector_class<device> &deviceList,
          const sycl::property_list &propList = {});
  context(const sycl::vector_class<sycl::device> &deviceList,
          sycl::async_handler asyncHandler, const sycl::property_list &propList = {});
  context(cl_context clContext, sycl::async_handler asyncHandler = {});

Construct a context.

The parameters to the constructor allow control of the devices and
platforms associated with the context. The constructor uses the
:ref:`default selector <built-in-device-selectors>` when no platforms
or devices are supplied.


.. rubric:: Parameters

propList
  See `sycl::property::context`_.
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
   
  sycl::platform get_platform() const;

Return platform associated with this context.
	    
get_devices
===========

::
   
  sycl::vector_class<sycl::device> get_devices() const;

	    
Returns vector of devices associated with this context.

get_info
========

::
   
  template <sycl::info::context param>
  typename sycl::info::param_traits<sycl::info::context, param>::return_type get_info() const;

Returns information about the context as determined by ``param``. See
`sycl::info::context`_ for details.
	    
.. include:: property_methods.inc.rst
	     
===================
sycl::info::context
===================

::

  enum class context : int {
    reference_count,
    platform,
    devices
  };

Used as a template parameter for get_info_ to determine the type of
information.

===============  ==========================  ===
Descriptor       Return type                 Description
===============  ==========================  ===
reference_count  cl_uint                     Reference count of the underlying cl_context
platform         platform                    SYCL platform for the context
devices          vector_class<device>        SYCL devices associated with this platform
===============  ==========================  ===


=======================
sycl::property::context
=======================

SYCL does not define any properties for context_.

