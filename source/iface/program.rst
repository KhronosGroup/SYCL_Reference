*******
Program
*******

===============
 info::program
===============

::

   enum class program: int {
       context,
       devices,
       reference_count
   };


===============
 program_state
===============

::

   enum class program_state {
       none,
       compiled,
       linked
   };

.. rst-class:: api-class
	       
=========
 program
=========

::

   class program;

(constructors)
==============

::
   
  explicit program(const context &context,
                   const property_list &propList = {});
  program(const context &context, vector_class<device> deviceList,
          const property_list &propList = {});
  program(vector_class<program> &programList,
          const property_list &propList = {});
  program(vector_class<program> &programList, string_class linkOptions,
          const property_list &propList = {});
  program(const context &context, cl_program clProgram);

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
   void build_with_kernel_type(string_class buildOptions = "");

build_with_source
=================

::

   void build_with_source(string_class kernelSource,
                          string_class buildOptions = "");

link
====

::

   void link(string_class linkOptions = "");

has_kernel
==========

::

   template <typename kernelT>
   bool has_kernel<kernelT>() const;

   bool has_kernel(string_class kernelName) const;

get_kernel
==========

::

  template <typename kernelT>
  kernel get_kernel<kernelT>() const;

  kernel get_kernel(string_class kernelName) const;


get_info
========

::

  template <info::program param>
  typename info::param_traits<info::program, param>::return_type
  get_info() const;

get_binaries
============

::

  vector_class<vector_class<char>> get_binaries() const;

get_context
===========

::

   context get_context() const;


get_devices
===========

::

   vector_class<device> get_devices() const;


get_compile_options
===================

::

   string_class get_compile_options() const;


get_link_options
================

::

   string_class get_link_options() const;

get_build_options
=================

::

   string_class get_build_options() const;


get_state
=========
 
::

   program_state get_state() const;







