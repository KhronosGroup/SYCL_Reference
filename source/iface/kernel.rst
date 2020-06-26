******
Kernel
******

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

.. rst-class:: api-class
	       
========
 kernel
========

::

   class kernel;

.. member-toc::


(constructors)
==============

::

     kernel(cl_kernel clKernel, const context& syclContext);


get
===

::
   
   cl_kernel get() const;


is_host
=======

::

   bool is_host() const;


get_context
===========

::

   context get_context() const;


get_program
===========

::

   program get_program() const;


get_info
========

::

   template <info::kernel param>
   typename info::param_traits<info::kernel, param>::return_type
   get_info() const;


get_work_group_info
===================

::

   template <info::kernel_work_group param>
   typename info::param_traits<info::kernel_work_group, param>::return_type
   get_work_group_info(const device &dev) const;





