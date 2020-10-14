..
  Copyright 2020 The Khronos Group Inc.
  SPDX-License-Identifier: CC-BY-4.0

.. rst-class:: api-class
	       
=============================
sycl::accessor (local memory)
=============================

::
   
   template <typename dataT, int dimensions, sycl::access::mode accessmode,
             sycl::access::target accessTarget = sycl::access::target::global_buffer,
             sycl::access::placeholder isPlaceholder = sycl::access::placeholder::false_t>
   class accessor;

Description

.. rubric:: Template parameters

===============  =======
dataT
dimensions
accessmode
accessTarget
isPlaceholder
===============  =======

.. rubric:: Member types

===============  =======
value_type
reference
const_reference
===============  =======

.. seealso:: |SYCL_SPEC_LOCAL_ACCESSOR|

(constructors)
==============

.. parsed-literal::
   
  *Available only when:
   dimensions == 0*
   
  accessor(sycl::handler &commandGroupHandlerRef, const sycl::property_list &propList = {});

   
  *Available only when:
   dimensions > 0*
   
  accessor(sycl::range<dimensions> allocationSize, sycl::handler &commandGroupHandlerRef,
           const sycl::property_list &propList = {});



get_size
========

::
   
  size_t get_size() const;

.. rubric:: Returns

get_count
=========

::
   
  size_t get_count() const;

.. rubric:: Returns

get_range
=========

::
   
  sycl::range<dimensions> get_range() const;

.. rubric:: Template parameters

===============  =======
dimensions
===============  =======

.. rubric:: Returns

get_pointer
===========

::
   
  sycl::local_ptr<dataT> get_pointer() const;

Available only when: accessTarget == access::target::local

operator[]
==========

.. parsed-literal::
   
  *Available only when:
   accessMode == access::mode::read_write && dimensions > 0*
    
  dataT &operator[](sycl::id<dimensions> index) const;

  *Available only when:
   accessMode == access::mode::read_write && dimensions == 1*
   
  dataT &operator[](size_t index) const

  *Available only when:
   accessMode == access::mode::atomic && dimensions > 0*
   
  sycl::atomic<dataT, sycl::access::address_space::local_space> operator[](
    sycl::id<dimensions> index) const;

  *Available only when:
   accessMode == access::mode::atomic && dimensions == 1*
   
  sycl::atomic<dataT, sycl::access::address_space::local_space> operator[](
    size_t index) const;

  *Available only when:
   dimensions > 1*
   
  __unspecified__ &operator[](size_t index) const;
	 

operator ()
===========

.. parsed-literal::
   
  *Available only when:
   accessMode == access::mode::read_write && dimensions == 0*

  operator dataT &() const;
   
  *Available only when:
   accessMode == access::mode::atomic && dimensions == 0*
   
  operator sycl::atomic<dataT,sycl::access::address_space::local_space> () const;
  

  
