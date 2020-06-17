****************
Invoking kernels
****************

.. rst-class:: api-class
	       
=========
 handler
=========

::

   class handler;

.. rubric:: Kernel dispatch

=================  ===
require_
set_arg_
set_args_
single_task_
parallel_for_
=================  ===

.. rubric:: Memory operations	    

=================  ===
copy_
update_host_
fill_
=================  ===


require
=======

::
   
  template <typename dataT, int dimensions, access::mode accessMode,
    access::target accessTarget>
  void require(accessor<dataT, dimensions, accessMode, accessTarget,
               access::placeholder::true_t> acc);

set_arg
=======

::
   
  template <typename T>
  void set_arg(int argIndex, T && arg);

set_args
========

::
   
  template <typename... Ts>
  void set_args(Ts &&... args);

single_task
===========

::

  template <typename KernelName, typename KernelType>
  void single_task(KernelType kernelFunc);

  void single_task(kernel syclKernel);

parallel_for
============

::

  template <typename KernelName, typename KernelType, int dimensions>
  void parallel_for(range<dimensions> numWorkItems, KernelType kernelFunc);

  template <typename KernelName, typename KernelType, int dimensions>
  void parallel_for(range<dimensions> numWorkItems,
                    id<dimensions> workItemOffset, KernelType kernelFunc);

  template <typename KernelName, typename KernelType, int dimensions>
  void parallel_for(nd_range<dimensions> executionRange, KernelType kernelFunc);

  template <typename KernelName, typename WorkgroupFunctionType, int dimensions>
  void parallel_for_work_group(range<dimensions> numWorkGroups,
                               WorkgroupFunctionType kernelFunc);

  template <typename KernelName, typename WorkgroupFunctionType, int dimensions>
  void parallel_for_work_group(range<dimensions> numWorkGroups,
                               range<dimensions> workGroupSize,
                               WorkgroupFunctionType kernelFunc);

  template <int dimensions>
  void parallel_for(range<dimensions> numWorkItems, kernel syclKernel);

  template <int dimensions>
  void parallel_for(range<dimensions> numWorkItems,
                    id<dimensions> workItemOffset, kernel syclKernel);

  template <int dimensions>
  void parallel_for(nd_range<dimensions> ndRange, kernel syclKernel);

  
copy
====

::
   
  template <typename T_src, int dim_src, access::mode mode_src, access::target tgt_src, access::placeholder isPlaceholder,
            typename T_dest>
  void copy(accessor<T_src, dim_src, mode_src, tgt_src, isPlaceholder> src,
            shared_ptr_class<T_dest> dest);

  template <typename T_src,
            typename T_dest, int dim_dest, access::mode mode_dest, access::target tgt_dest, access::placeholder isPlaceholder>
  void copy(shared_ptr_class<T_src> src,
            accessor<T_dest, dim_dest, mode_dest, tgt_dest, isPlaceholder> dest);

  template <typename T_src, int dim_src, access::mode mode_src, access::target tgt_src, access::placeholder isPlaceholder,
            typename T_dest>
  void copy(accessor<T_src, dim_src, mode_src, tgt_src, isPlaceholder> src,
            T_dest *dest);

  template <typename T_src,
            typename T_dest, int dim_dest, access::mode mode_dest, access::target tgt_dest, access::placeholder isPlaceholder>
  void copy(const T_src *src,
            accessor<T_dest, dim_dest, mode_dest, tgt_dest, isPlaceholder> dest);

  template <typename T_src, int dim_src, access::mode mode_src, access::target tgt_src, access::placeholder isPlaceholder_src,
            typename T_dest, int dim_dest, access::mode mode_dest, access::target tgt_dest, access::placeholder isPlaceholder_dest>
  void copy(accessor<T_src, dim_src, mode_src, tgt_src, isPlaceholder_src> src,
            accessor<T_dest, dim_dest, mode_dest, tgt_dest, isPlaceholder_dest> dest);

update_host
===========

::

  template <typename T, int dim, access::mode mode, access::target tgt, access::placeholder isPlaceholder>
  void update_host(accessor<T, dim, mode, tgt, isPlaceholder> acc);

fill
====

::

  template <typename T, int dim, access::mode mode, access::target tgt, access::placeholder isPlaceholder>
  void fill(accessor<T, dim, mode, tgt, isPlaceholder> dest, const T& src);

