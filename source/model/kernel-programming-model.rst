.. _kernel-programming-model:

Kernel Programming Model
========================


The Device code can specify the amount of parallelism to request
through several mechanisms.

-  ``single_task`` – execute a single instance of the kernel with a
   single work item.
-  ``parallel_for`` – execute a kernel in parallel across a range of
   processing elements. Typically, this version of parallel_for is
   employed on “embarrassingly parallel” workloads.
-  ``parallel_for_work_group`` – execute a kernel in parallel across a
   hierarchical range of processing elements using local memory and
   barriers.

The following code sample shows two combinations of invoking kernels:

#. single_task and C++ lambda (lines 30-35)
#. parallel_for and functor (lines 8-16 and line 46)

.. literalinclude:: /examples/kernel-model.cpp
   :linenos:
