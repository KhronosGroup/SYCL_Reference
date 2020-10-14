..
  Copyright 2020 The Khronos Group Inc.
  SPDX-License-Identifier: CC-BY-4.0

.. rst-class:: api-class
	       
======================
sycl::accessor (image)
======================

::
   
   template <typename dataT, int dimensions, sycl::access::mode accessmode,
             sycl::access::target accessTarget = sycl::access::target::global_buffer,
             sycl::access::placeholder isPlaceholder = sycl::access::placeholder::false_t>
   class accessor;

Description

.. rubric:: Template parameters

================  ===
dataT
dimensions
accessmode
accessTarget
isPlaceholder
================  ===

.. rubric:: Member types

===============  =======
value_type
reference
const_reference
===============  =======

.. seealso:: |SYCL_SPEC_IMAGE_ACCESSOR|

(constructors)
==============

.. parsed-literal::
   
  *Available only when:
   accessTarget == access::target::host_image*

  template <typename AllocatorT>
  accessor(sycl::image<dimensions, AllocatorT> &imageRef,
           const sycl::property_list &propList = {});

  *Available only when:
   accessTarget == access::target::image*

  template <typename AllocatorT>
  accessor(sycl::image<dimensions, AllocatorT> &imageRef,
           sycl::handler &commandGroupHandlerRef, const sycl::property_list &propList = {});

  *Available only when:
   accessTarget == access::target::image_array && dimensions < 3*
   
  template <typename AllocatorT>
  accessor(sycl::image<dimensions + 1, AllocatorT> &imageRef,
           sycl::handler &commandGroupHandlerRef, const sycl::property_list &propList = {});


get_count
=========

::
   
  size_t get_count() const;

get_range
=========

.. parsed-literal::
   
   *Available only when:
    (accessTarget != access::target::image_array)*
    
   sycl::range<dimensions> get_range() const;

   *Available only when:
    (accessTarget == access::target::image_array)*
    
   sycl::range<dimensions+1> get_range() const;

.. rubric:: Template parameters

================  ===
dimensions
================  ===

read
====

.. parsed-literal::
   
  *Available only when:
   (accessTarget == access::target::image && accessMode == access::mode::read)
   || (accessTarget ==
        access::target::host_image && (accessMode ==
        access::mode::read || accessMode == access::mode::read_write))*

  template <typename coordT>
  dataT read(const coordT &coords) const;

  *Available only when:
   (accessTarget == access::target::image && accessMode == access::mode::read)
   || (accessTarget ==
        access::target::host_image && (accessMode ==
        access::mode::read || accessMode == access::mode::read_write))*

  template <typename coordT>
  dataT read(const coordT &coords, const sampler &smpl) const;


.. rubric:: Template parameters

================  ===
coordT
================  ===


operator[]
==========

::
   
  *Available only when:
   accessTarget == access::target::image_array && dimensions < 3*
   
  __image_array_slice__ operator[](size_t index) const;

  
