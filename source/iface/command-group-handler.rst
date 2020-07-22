****************
Invoking kernels
****************

.. rst-class:: api-class
	       
=========
 handler
=========

::

   class handler;

The ``handler`` defines the interface to invoke kernels by submitting
commands to a queue.

A ``handler`` can only be constructed by the SYCL runtime and is
passed as an argument to the command group function. The command group
function is an argument to :ref:`queue-submit`.


.. member-toc::


require
=======

::
   
  template <typename dataT, int dimensions, access::mode accessMode,
    access::target accessTarget>
  void require(accessor<dataT, dimensions, accessMode, accessTarget,
               access::placeholder::true_t> acc);

Adds a requirement before a device may execute a kernel.

set_arg
=======

::
   
  template <typename T>
  void set_arg(int argIndex, T && arg);

Sets a kernel argument.

set_args
========

::
   
  template <typename... Ts>
  void set_args(Ts &&... args);

Sets all kernel arguments.

single_task
===========

::

  template <typename KernelName, typename KernelType>
  void single_task(KernelType kernelFunc);

  void single_task(kernel syclKernel);

Defines and invokes a kernel function.

.. _handler-parallel_for:


parallel_for
============

::

  template <typename KernelName, typename KernelType, int dimensions>
  void parallel_for(range<dimensions> numWorkItems, KernelType kernelFunc);

  template <typename KernelName, typename KernelType, int dimensions>
  void parallel_for(range<dimensions> numWorkItems,
                    id<dimensions> workItemOffset, KernelType kernelFunc);

  template <typename KernelName, typename KernelType, int dimensions>
  void parallel_for(nd_range<dimensions> ndRange, KernelType kernelFunc);

  template <int dimensions>
  void parallel_for(range<dimensions> numWorkItems, kernel syclKernel);

  template <int dimensions>
  void parallel_for(range<dimensions> numWorkItems,
                    id<dimensions> workItemOffset, kernel syclKernel);

  template <int dimensions>
  void parallel_for(nd_range<dimensions> ndRange, kernel syclKernel);

Invokes a kernel function for a :ref:`range` or :ref:`nd_range`.

.. rubric:: Parameters

=================  ===
numWorkItems       Range for work items
workItemOffset     Offset into range for work items
kernelFunc         Kernel function      
syclKernel         See :ref:`kernel`
ndRange            See :ref:`nd_range`
=================  ===
	    
  
parallel_for_work_group
=======================

::
   
  template <typename KernelName, typename WorkgroupFunctionType, int dimensions>
  void parallel_for_work_group(range<dimensions> numWorkGroups,
                               WorkgroupFunctionType kernelFunc);

  template <typename KernelName, typename WorkgroupFunctionType, int dimensions>
  void parallel_for_work_group(range<dimensions> numWorkGroups,
                               range<dimensions> workGroupSize,
                               WorkgroupFunctionType kernelFunc);

Outer invocation in a hierarchical invocation of a kernel.

The kernel function is executed once per work group.

copy
====

::
   
  template <typename T_src, int dim_src, access::mode mode_src, access::target tgt_src,
            access::placeholder isPlaceholder, typename T_dest>
  void copy(accessor<T_src, dim_src, mode_src, tgt_src, isPlaceholder> src,
            shared_ptr_class<T_dest> dest);
  template <typename T_src,
            typename T_dest, int dim_dest, access::mode mode_dest, access::target tgt_dest,
	    access::placeholder isPlaceholder>
  void copy(shared_ptr_class<T_src> src,
            accessor<T_dest, dim_dest, mode_dest, tgt_dest, isPlaceholder> dest);
  template <typename T_src, int dim_src, access::mode mode_src,
            access::target tgt_src, access::placeholder isPlaceholder,
            typename T_dest>
  void copy(accessor<T_src, dim_src, mode_src, tgt_src, isPlaceholder> src,
            T_dest *dest);
  template <typename T_src,
            typename T_dest, int dim_dest, access::mode mode_dest,
	    access::target tgt_dest, access::placeholder isPlaceholder>
  void copy(const T_src *src,
            accessor<T_dest, dim_dest, mode_dest, tgt_dest, isPlaceholder> dest);
  template <typename T_src, int dim_src, access::mode mode_src,
            access::target tgt_src, access::placeholder isPlaceholder_src,
            typename T_dest, int dim_dest, access::mode mode_dest, access::target tgt_dest,
	    access::placeholder isPlaceholder_dest>
  void copy(accessor<T_src, dim_src, mode_src, tgt_src, isPlaceholder_src> src,
            accessor<T_dest, dim_dest, mode_dest, tgt_dest, isPlaceholder_dest> dest);

Copies memory from ``src`` to ``dest``.

``copy`` invokes the operation on a :ref:`device`. The source,
destination, or both source and destination are
:ref:`iface-accessors`. Source or destination can be a pointer or a
``shared_ptr``.

.. rubric:: Template parameters

==================  ===
T_src               Type of source data elements
dim_src             Dimensionality of source accessor data
T_dest              Type of element for destination data
dim_dest            Dimensionality of destination accessor data
mode_src            Mode for source accessor
mode_dest           Mode for destination accessor
tgt_src             Target for source accessor
tgt_dest            Target for destination accessor
isPlaceholder_src   Placeholder value for source accessor
isPlaceholder_dest  Placeholder value for destination accessor
==================  ===

.. rubric:: Parameters

=============  ===
src            source of copy
dest           destination of copy
=============  ===

update_host
===========

::

  template <typename T, int dim, access::mode mode,
            access::target tgt, access::placeholder isPlaceholder>
  void update_host(accessor<T, dim, mode, tgt, isPlaceholder> acc);

.. rubric:: Template parameters

==============  ===
T               Type of element associated with accessor
dim             Dimensionality of accessor
mode            Access mode for accessor
tgt             Target for accessor
isPlaceholder   Placeholder value for accessor
==============  ===

Updates host copy of data associated with accessor.

fill
====

::

  template <typename T, int dim, access::mode mode,
            access::target tgt, access::placeholder isPlaceholder>
  void fill(accessor<T, dim, mode, tgt, isPlaceholder> dest, const T& src);

.. rubric:: Template parameters

==============  ===
T               Type of element associated with accessor
dim             Dimensionality of accessor
mode            Access mode for accessor
tgt             Target for accessor
isPlaceholder   Placeholder value for accessor
==============  ===

.. rubric:: Parameters

==============  ===
dest            Destination of fill operation
src             Value to fill
==============  ===

Fill the destination of the memory associated with the accessor with
the value in ``src``.
