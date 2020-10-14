..
  Copyright 2020 The Khronos Group Inc.
  SPDX-License-Identifier: CC-BY-4.0

.. _iface-images:

******
Images
******

.. rst-class:: api-class
	       
===========
sycl::image
===========

::
   
   template <int dimensions = 1,
             typename AllocatorT = sycl::image_allocator>
   class image;

.. rubric:: Template parameters

========================  ==========
dimensions
AllocatorT
========================  ==========

.. seealso:: |SYCL_SPEC_IMAGE|

.. _image-image:

(constructors)
==============

.. parsed-literal::
   
  image(sycl::image_channel_order order, sycl::image_channel_type type,
        const sycl::range<dimensions> &range, const sycl::property_list &propList = {});
  image(sycl::image_channel_order order, sycl::image_channel_type type,
        const sycl::range<dimensions> &range, AllocatorT allocator,
        const sycl::property_list &propList = {});
  image(void *hostPointer, sycl::image_channel_order order,
        sycl::image_channel_type type, const sycl::range<dimensions> &range,
        const sycl::property_list &propList = {});
  image(void *hostPointer, sycl::image_channel_order order,
        sycl::image_channel_type type, const sycl::range<dimensions> &range,
        AllocatorT allocator, const sycl::property_list &propList = {});
  image(const void *hostPointer, sycl::image_channel_order order,
        sycl::image_channel_type type, const sycl::range<dimensions> &range,
        const sycl::property_list &propList = {});
  image(const void *hostPointer, sycl::image_channel_order order,
        sycl::image_channel_type type, const sycl::range<dimensions> &range,
        AllocatorT allocator, const sycl::property_list &propList = {});
  image(sycll::shared_ptr_class<void> &hostPointer, sycl::image_channel_order order,
        sycl::image_channel_type type, const sycl::range<dimensions> &range,
        const sycl::property_list &propList = {});
  image(sycl::shared_ptr_class<void> &hostPointer, sycl::image_channel_order order,
        sycl::image_channel_type type, const sycl::range<dimensions> &range,
        AllocatorT allocator, const sycl::property_list &propList = {});
  image(cl_mem clMemObject, const sycl::context &syclContext,
        sycl::event availableEvent = {});

  *Available only when:
   dimensions > 1*
	      
  image(sycl::image_channel_order order, sycl::image_channel_type type,
        const sycl::range<dimensions> &range, const sycl::range<dimensions - 1> &pitch,
        const sycl::property_list &propList = {});
  image(sycl::image_channel_order order, sycl::image_channel_type type,
        const sycl::range<dimensions> &range, const sycl::range<dimensions - 1> &pitch,
        AllocatorT allocator, const sycl::property_list &propList = {});
  image(void \*hostPointer, sycl::image_channel_order order,     
        sycl::image_channel_type type, const sycl::range<dimensions> &range,
        sycl::range<dimensions - 1> &pitch, const sycl::property_list &propList = {});   
  image(void \*hostPointer, sycl::image_channel_order order,     
        sycl::image_channel_type type, const sycl::range<dimensions> &range,
        sycl::range<dimensions - 1> &pitch, AllocatorT allocator,
        const sycl::property_list &propList = {});
  image(sycl::shared_ptr_class<void> &hostPointer, sycl::image_channel_order order,
        sycl::image_channel_type type, const sycl::range<dimensions> &range,
        const sycl::range<dimensions - 1> &pitch, const sycl::property_list &propList = {});
  image(sycl::shared_ptr_class<void> &hostPointer, sycl::image_channel_order order,
        sycl::image_channel_type type, const sycl::range<dimensions> &range,
        const sycl::range<dimensions - 1> &pitch, AllocatorT allocator,
        const sycl::property_list &propList = {});


.. rubric:: Parameters

================  ===
order
type
range
propList          See `Image properties`_
allocator
pitch
hostPointer
syclContext
clMemObject
availableEvent
================  ===

get_range
=========

::
   
  sycl::range<dimensions> get_range() const;

get_pitch
=========

::
   
  sycl::range<dimensions-1> get_pitch() const;

Available only when dimensions > 1

get_count
=========

::

  size_t get_count() const;

get_size
========

::

  size_t get_size() const;

get_allocator
=============

::

  AllocatorT get_allocator() const;

get_access
==========

::

  template <typename dataT, sycl::access::mode accessMode>
  accessor<dataT, dimensions, accessMode, sycl::access::target::image>
  get_access(sycl::handler & commandGroupHandler);
  template <typename dataT, sycl::access::mode accessMode>
  accessor<dataT, dimensions, accessMode, sycl::access::target::host_image>
  get_access();

.. rubric:: Template parameters

===================  ===
dataT
accessMode
===================  ===

.. rubric:: Parameters

===================  ===
commandGroupHandler
===================  ===

	    
set_final_data
==============

::

  template <typename Destination = std::nullptr_t>
  void set_final_data(Destination finalData = nullptr);

Description

.. rubric:: Template parameters

================  ===
Destination
================  ===

.. rubric:: Parameters

================  ===
finalData
================  ===


set_write_back
==============

::

  void set_write_back(bool flag = true);

.. rubric:: Parameters

=================  =======
flag
=================  =======

==================
 Image properties
==================

.. rst-class:: api-class
	       
sycl::property::image::use_host_ptr
===================================

::

   class use_host_ptr;

Description

.. _image-use_host_ptr-use_host_ptr:

(constructors)
--------------

::

   use_host_ptr();

Description

.. rst-class:: api-class
	       
sycl::property::image::use_mutex
================================

::

   class use_mutex;

Description

.. _image-get_mutex_ptr-get_mutex_ptr:
   
(constructors)
--------------

::

   use_mutex();

Description

get_mutex_ptr
-------------

::

   mutex_class *get_mutex_ptr() const;


Description

sycl::property::image::context_bound
====================================


::

   class context_bound;

.. rubric:: Namespace

::

   property::image

Description

.. _image-context_bound-context_bound:

(constructors)
--------------

::

   use_mutex();


Description


get_context
-----------

::

   context get_context() const;


Description

=========================
sycl::image_channel_order
=========================

::
   
   enum class image_channel_order : unsigned int {
     a,
     r,
     rx,
     rg,
     rgx,
     ra,
     rgb,
     rgbx,
     rgba,
     argb,
     bgra,
     intensity,
     luminance,
     abgr
   }

========================
sycl::image_channel_type
========================

::
   
   enum class image_channel_type : unsigned int {
     snorm_int8,
     snorm_int16,
     unorm_int8,
     unorm_int16,
     unorm_short_565,
     unorm_short_555,
     unorm_int_101010,
     signed_int8,
     signed_int16,
     signed_int32,
     unsigned_int8,
     unsigned_int16,
     unsigned_int32,
     fp16,
     fp32
   }
