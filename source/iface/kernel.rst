..
  Copyright 2020 The Khronos Group Inc.
  SPDX-License-Identifier: CC-BY-4.0

*******
Kernels
*******


.. rst-class:: api-class
	       
.. _kernel:

============
sycl::kernel
============

::

   class kernel;

Abstraction of a kernel object.


.. seealso:: |SYCL_SPEC_KERNEL|

(constructors)
==============

::

     kernel(cl_kernel clKernel, const sycl::context& syclContext);


Constructs a SYCL kernel instance from an OpenCL kernel.

get
===

::
   
   cl_kernel get() const;


Returns OpenCL kernel associated with the SYCL kernel.

is_host
=======

::

   bool is_host() const;


Return true if this SYCL kernel is a host kernel.

get_context
===========

::

   sycl::context get_context() const;


Returns context associated with the kernel.

get_program
===========

::

   sycl::program get_program() const;


Returns program that this kernel is part of.

get_info
========

::

   template <sycl::info::kernel param>
   typename sycl::info::param_traits<sycl::info::kernel, param>::return_type
   get_info() const;


.. rubric:: Template parameters

==================  ===   
param               See `sycl::info::kernel`_
==================  ===   

Returns information about the kernel

get_work_group_info
===================

::

   template <sycl::info::kernel_work_group param>
   typename sycl::info::param_traits<sycl::info::kernel_work_group, param>::return_type
   get_work_group_info(const sycl::device &dev) const;

.. rubric:: Template parameters

==================  ===   
param               See `sycl::info::kernel_work_group`_
==================  ===   

Returns information about the work group

==================
sycl::info::kernel
==================

::
   
   enum class kernel: int {
       function_name,
       num_args,
       context,
       program,
       reference_count,
       attributes
   };

=============================
sycl::info::kernel_work_group
=============================

::

   enum class kernel_work_group: int {
       global_work_size,
       work_group_size,
       compile_work_group_size,
       preferred_work_group_size_multiple,
       private_mem_size
   };



