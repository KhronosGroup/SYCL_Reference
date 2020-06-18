.. _execution-model:

Execution Model
===============


The execution model is based upon the SYCL\* execution model. It
defines and specifies how code, termed kernels, execute on the host
and the devices. We explain the execution model in 2 parts,
*application execution model* and *kernel execution model*.


Application Execution Model
---------------------------


The application execution model coordinates execution and data
management between the host and devices via command groups. The
command groups, which are groupings of commands like kernel invocation
and accessors, are submitted to queues for execution. Accessors, which
are formally part of the memory model, also communicate ordering
requirements of execution. A program employing the execution model
declares and instantiates :ref:`queue`\s. Queues can execute with an in-order
or out-of-order policy controllable by the program.


Kernel Execution Model
----------------------


The device execution model specifies how computation is accomplished
on the accelerator. Compute ranging from small one-dimensional data to
large multidimensional data sets are allocated across a hierarchy of
:term:`nd-range`, :term:`work-group`, :term:`sub-group`, and
:term:`work-item`, which are all specified when the work is submitted
to the command queue.  It is important to note that the actual kernel
code represents the work that is executed for one work-item. The code
outside of the kernel controls just how much parallelism is executed;
the amount and distribution of the work is controlled by specification
of the sizes of the ND-range and work-group.

The following figure depicts the relationship between an ND-range,
work-group, sub-group, and work-item. The total amount of work is
specified by the ND-range size. The grouping of the work is specified by
the work-group size. The example shows the ND-range size of X \* Y \* Z,
work-group size of X’ \* Y’ \* Z’, and subgroup size of X’. Therefore,
there are X \* Y \* Z work-items. There are (X \* Y \* Z) / (X’ \* Y’ \*
Z’) work-groups and (X \* Y \* Z) / X’ subgroups.

|nd-range|

When kernels are executed, the location of a particular work-item in the
larger ND-range, work-group, or sub-group is important. For example, if
the work-item is assigned to compute on specific pieces of data, a
method of specification is necessary. Unique identification of the
work-item is provided via intrinsic functions such as those in the
``nd_item`` class (``global_id``, ``work_group_id``, and ``local_id``).


The following code sample launches a kernel and displays the
relationships of the previously discussed ``ND-range``, ``work-group``,
and ``work-item``.

.. literalinclude:: /examples/nd-range.cpp
   :linenos:		    

With the following output:

.. literalinclude:: /examples/nd-range.out

.. rubric:: ND-Range Parallelism Example

The following discusses the relationships in the use of the ND-range
in the previous code sample.

- Line 16 is the ``nd-range`` declaration. ``nd_range<2>``
  specifies a two-dimensional index space.
- The first argument, ``range<2>(N,N)``, defines a ``N`` by ``N``
  global index space shape.
- The second argument, ``range<2>(M,M)`` defines a ``M`` by ``M``
  local work-group shape.
- Lines 18 & 19 extract the coordinates of the work item in the index
  space

The ``sub-group`` is an extension to the SYCL execution model and
sits hierarchically between the ``work_group`` and ``work_item``. The
``sub_group`` was created to align with typical hardware resources
that contain a vector unit to execute several similar operations in
parallel and in lock step.


.. |nd-range| image:: /image/nd-range.png
   :width: 468px
   :height: 453px

.. seealso::

   * :ref:`expressing-parallelism`
