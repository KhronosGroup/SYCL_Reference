..
  Copyright 2020 The Khronos Group Inc.
  SPDX-License-Identifier: CC-BY-4.0

********
Programs
********

===================
sycl::info::program
===================

::

   enum class program: int {
       context,
       devices,
       reference_count
   };


===================
sycl::program_state
===================

::

   enum class program_state {
       none,
       compiled,
       linked
   };

.. rst-class:: api-class
	       
=============
sycl::program
=============

::

   class program;

(constructors)
==============

::
   
  explicit program(const context &sycl::context,
                   const sycl::property_list &propList = {});
  program(const context &sycl::context, sycl::vector_class<sycl::device> deviceList,
          const sycl::property_list &propList = {});
  program(sycl::vector_class<sycl::program> &programList,
          const sycl::property_list &propList = {});
  program(sycl::vector_class<sycl::program> &programList, sycl::string_class linkOptions,
          const sycl::property_list &propList = {});
  program(const sycl::context &context, cl_program clProgram);

get
===

::

   cl_program get() const;


is_host
=======

::

   bool is_host() const;

compile_with_kernel_type
========================

::

   template <typename kernelT>
   void build_with_kernel_type(sycl::string_class buildOptions = "");

build_with_source
=================

::

   void build_with_source(sycl::string_class kernelSource,
                          sycl::string_class buildOptions = "");

link
====

::

   void link(sycl::string_class linkOptions = "");

has_kernel
==========

::

   template <typename kernelT>
   bool has_kernel<kernelT>() const;

   bool has_kernel(sycl::string_class kernelName) const;

get_kernel
==========

::

  template <typename kernelT>
  sycl::kernel get_kernel<kernelT>() const;

  sycl::kernel get_kernel(sycl::string_class kernelName) const;


get_info
========

::

  template <sycl::info::program param>
  typename info::param_traits<sycl::info::program, param>::return_type
  get_info() const;

get_binaries
============

::

  sycl::vector_class<sycl::vector_class<char>> get_binaries() const;

get_context
===========

::

   sycl::context get_context() const;


get_devices
===========

::

   sycl::vector_class<sycl::device> get_devices() const;


get_compile_options
===================

::

   sycl::string_class get_compile_options() const;


get_link_options
================

::

   sycl::string_class get_link_options() const;

get_build_options
=================

::

   sycl::string_class get_build_options() const;


get_state
=========
 
::

   sycl::program_state get_state() const;







