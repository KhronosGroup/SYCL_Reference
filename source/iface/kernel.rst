******
Kernel
******


.. rst-class:: api-class
	       
.. _kernel:

========
 kernel
========

::

   class kernel;

Abstraction of a kernel object.


.. member-toc::


(constructors)
==============

::

     kernel(cl_kernel clKernel, const context& syclContext);


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

   context get_context() const;


Returns context associated with the kernel.

get_program
===========

::

   program get_program() const;


Returns program that this kernel is part of.

get_info
========

::

   template <info::kernel param>
   typename info::param_traits<info::kernel, param>::return_type
   get_info() const;


.. rubric:: Template parameters

==================  ===   
param               See `info::kernel`_
==================  ===   

Returns information about the kernel

get_work_group_info
===================

::

   template <info::kernel_work_group param>
   typename info::param_traits<info::kernel_work_group, param>::return_type
   get_work_group_info(const device &dev) const;

.. rubric:: Template parameters

==================  ===   
param               See `info::kernel_work_group`_
==================  ===   

Returns information about the work group

==============
 info::kernel
==============

::
   
   enum class kernel: int {
       function_name,
       num_args,
       context,
       program,
       reference_count,
       attributes
   };

=========================
 info::kernel_work_group
=========================

::

   enum class kernel_work_group: int {
       global_work_size,
       work_group_size,
       compile_work_group_size,
       preferred_work_group_size_multiple,
       private_mem_size
   };



