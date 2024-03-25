..
  Copyright 2024 The Khronos Group Inc.
  SPDX-License-Identifier: CC-BY-4.0

.. _handler:

*****************
``sycl::handler``
*****************

::

  class handler;

The ``sycl::handler`` class provides the interface for all of the
member functions that are able to be executed inside the
:ref:`command group scope <command-group-scope>`, and it is also
provided as a scoped object to all of the data access requests.
The command group handler class provides the interface in which
every command in the command group scope will be submitted to a queue.

A command group handler object can only be constructed by the SYCL
runtime. All of the accessors defined in :ref:`command group scope
<command-group-scope>` take as a parameter an instance of the command
group handler, and all the kernel invocation functions are member
functions of this class.

It is disallowed for an instance of the ``sycl::handler`` class to be
moved or copied.

.. seealso::

  |SYCL_SPEC_COM_GROUP_SCOPE|

  |SYCL_SPEC_HANDLER|

  :ref:`host_task-basic`

.. _command-group-scope:

===========================
Command group scope concept
===========================

A command group scope, as defined in |SYCL_SPEC_EXEC_MODEL|,
may execute a single command such as invoking a kernel, copying
memory, or executing a host task. It is legal for a command group
scope to statically contain more than one call to a command
function, but any single execution of the command group function
object may execute no more than one command.If an application fails
to do this, the function that submits the command group function
object (i.e., ``sycl::queue::submit``) must throw a synchronous
exception with the ``sycl::errc::invalid`` error code.

The statements that call commands together with the statements
that define the requirements for a kernel form the command group
function object. The command group function object takes as a
parameter an instance of the command group handler class which
encapsulates all the member functions executed in the command
group scope. The member functions and objects defined in this
scope will define the requirements for the kernel execution or
explicit memory operation, and will be used by the SYCL runtime
to evaluate if the operation is ready for execution. Host code
within a command group function object (typically setting up
requirements) is executed once, before the command group submit
call returns. This abstraction of the kernel execution unifies
the data with its processing, and consequently allows more
abstraction and flexibility in the parallel programming models
that can be implemented on top of SYCL.

The command group function object and the ``sycl::handler`` class
serve as an interface for the encapsulation of command group scope.
A SYCL kernel function is defined as a function object. All the
device data accesses are defined inside this group and any transfers
are managed by the SYCL runtime. The rules for the data transfers
regarding device and host data accesses are described in the
:ref:`iface-accessors` and the :ref:`buffer`. The overall memory model
of the SYCL application is described in the |SYCL_SPEC_MEM_MODEL|.

It is possible for a command group function object to fail to enqueue
to a :ref:`queue`, or for it to fail to execute correctly. A user can
therefore supply a secondary queue when submitting a command group to
the primary queue. If the SYCL runtime fails to enqueue or execute a
command group on a primary queue, it can attempt to run the command
group on the secondary queue. The circumstances in which it is, or is
not, possible for a SYCL runtime to fall-back from primary to secondary
queue are unspecified in the specification. Even if a command group is
run on the secondary queue, the requirement that host code within the
command group is executed exactly once remains, regardless of whether
the fallback queue is used for execution.

==============
(constructors)
==============

::

  handler(___unspecified___);

Unspecified implementation-defined constructor.

=================
Member functions
=================

Functions for adding requirements
=================================

When an :ref:`command-accessor` is created from a command group handler,
a requirement is implicitly added to the command group for the
accessor's data. However, this does not happen when creating a
placeholder accessor. In order to create a requirement for a
placeholder accessor, code must call the ``sycl::handler::require()``
member function.

.. note::

  The default constructed :ref:`command-accessor` is not
  a placeholder, so it may be passed to a SYCL kernel function
  without calling ``sycl::handler::require()``. However, this
  :ref:`command-accessor` also has no underlying memory object, so
  such an accessor does not create any requirement for the command
  group, and attempting to access data elements from it produces
  undefined behavior.

``sycl::event`` may also be used to create requirements for a
command group. Such requirements state that the actions
represented by the events must complete before the command
group may execute. Such requirements are added when code
calls the ``sycl::handler::depends_on()`` member function.

``require``
-----------

::

  template <typename DataT, int Dimensions, sycl::access_mode AccessMode,
            sycl::target AccessTarget, sycl::access::placeholder IsPlaceholder>
  void require(
      sycl::accessor<DataT, Dimensions, AccessMode, AccessTarget, IsPlaceholder> acc);

Calling this function has no effect unless ``acc``
is a placeholder accessor.

If the accessor ``acc`` has already been registered with the
command group, calling this function has no effect.

When ``acc`` is a placeholder accessor, this function adds a
requirement to the handler's command group for the memory
object represented by ``acc``.

.. rubric:: Template parameters

==================  ===
``DataT``           Data type of the passed :ref:`command-accessor`.
``AccessMode``      Access mode type of the passed
                    :ref:`command-accessor`.
``AccessTarget``    Target of the passed :ref:`command-accessor`.
``IsPlaceholder``   States whether the passed :ref:`command-accessor`
                    is a placeholder or not.
==================  ===

``depend_on``
-------------

.. rubric:: Overload 1

::

  void depends_on(sycl::event depEvent);

The command group now has a requirement that
the action represented by ``depEvent`` must
complete before executing this command-group's
action.

.. rubric:: Overload 2

::

  void depends_on(const std::vector<sycl::event>& depEvents);

The command group now has a requirement that
the actions represented by each event in ``depEvents``
must complete before executing this command-group's action.

Functions for invoking kernels
==============================

Kernels can be invoked as single tasks, basic data-parallel
kernels, ND-range in work-groups, or hierarchical parallelism.

Each function takes an optional ``KernelName`` template parameter.
The user may optionally provide a kernel name, otherwise an
implementation-defined name will be generated for the kernel.

``set_args``
------------

.. rubric:: Overload 1

::

  template <typename T> void set_arg(int argIndex, T&& arg);

This function must only be used to set arguments for a kernel
that was constructed using a backend specific interoperability
function or for a device built-in kernel. Attempting to use
this function to set arguments for other kernels results in
undefined behavior. The precise semantics of this function
are defined by each SYCL backend specification.

.. rubric:: Overload 2

::

  template <typename... Ts> void set_args(Ts&&... args);

Set all arguments for a given kernel, as if each argument
in ``args`` was passed to ``set_arg`` in the same order
and with an increasing index starting at ``0``.

``single_task``
---------------

.. rubric:: Overload 1

::

  template <typename KernelName, typename KernelType>
  void single_task(const KernelType& kernelFunc);

Defines and invokes a SYCL kernel function as a lambda function
or a named function object type. Specification of a kernel name
(``typename KernelName``) is optional. The callable ``KernelType``
can optionally take a :ref:`kernel_handler` in which case the
SYCL runtime will construct an instance of :ref:`kernel_handler`
and pass it to ``KernelType``.

.. rubric:: Overload 2

::

  void single_task(const sycl::kernel& kernelObject);

.. warning::

  This function must only be used to invoke a kernel that
  was constructed using a backend specific interoperability
  function or to invoke a device built-in kernel.

  Attempting to use this function to invoke other kernels throws
  a synchronous exception with the ``sycl::errc::invalid`` error
  code.

The precise semantics of this function are defined by each
SYCL backend specification, but the intent is that the kernel
should execute exactly once.

This invocation function ignores any ``sycl::kernel_bundle`` that was
bound to this command group handler via
``sycl::handler::use_kernel_bundle()`` and instead implicitly uses the
kernel bundle that contains the ``kernelObject``. Throws an
exception with the ``sycl::errc::kernel_not_supported``
error code if the ``kernelObject`` is not compatible with either
the device associated with the primary queue of the command group or
with the device associated with the secondary queue (if specified).

.. rubric:: Example

:ref:`handler-example1`

.. seealso:: :ref:`single_task-invoke`

.. _handler-parallel_for:

``parallel_for``
----------------

.. rubric:: Overloads 1-2

::

  template <typename KernelName, int Dimensions, typename... Rest>
  void parallel_for(sycl::range<Dimensions> numWorkItems, Rest&&... rest);

  template <typename KernelName, int Dimensions, typename... Rest>
  void parallel_for(sycl::range<Dimensions> numWorkItems, id<Dimensions> workItemOffset,
                    const KernelType& kernelFunc) // Deprecated in SYCL 2020

.. warning:: Overload 2 is deprecated in SYCL 2020.

Defines and invokes a SYCL kernel function as a lambda function
or a named function object type, for the specified range and
given an item or integral type (e.g ``int``, ``size_t``), if
range is 1-dimensional, for indexing in the indexing space
defined by range.

Generic kernel functions are permitted, in that case the
argument type is an ``sycl::item``.

Specification of a kernel name (``typename KernelName``) is
optional.

The ``rest`` parameter pack consists of 0 or more objects
created by the ``sycl::reduction`` function, followed by a
callable. For each object in ``rest``, the kernel function
must take an additional reference parameter corresponding to
that object's reducer type, in the same order.

The callable can optionally take a :ref:`kernel_handler`
as its last parameter, in which case the SYCL runtime will
construct an instance of :ref:`kernel_handler` and pass
it to the callable.

.. rubric:: Overload 3

::

  template <int Dimensions>
  void parallel_for(sycl::range<Dimensions> numWorkItems,
                    const sycl::kernel& kernelObject);

.. warning::

  This function must only be used to invoke a kernel that
  was constructed using a backend specific interoperability
  function or to invoke a device built-in kernel.

  Attempting to use this function to invoke other kernels throws
  a synchronous exception with the ``sycl::errc::invalid`` error
  code.

The precise semantics of this function are defined by each SYCL
backend specification, but the intent is that the kernel should
be invoked for the specified range of index values.

This invocation function ignores any ``sycl::kernel_bundle`` that was
bound to this command group handler via
``sycl::handler::use_kernel_bundle()`` and instead implicitly uses the
kernel bundle that contains the ``kernelObject``. Throws an
exception with the ``sycl::errc::kernel_not_supported``
error code if the ``kernelObject`` is not compatible with either
the device associated with the primary queue of the command group or
with the device associated with the secondary queue (if specified).

.. rubric:: Overload 4

::

  template <int Dimensions>
  void parallel_for(sycl::nd_range<Dimensions> executionRange,
                    const sycl::kernel& kernelObject)

.. warning::

  This function must only be used to invoke a kernel that
  was constructed using a backend specific interoperability
  function or to invoke a device built-in kernel.

  Attempting to use this function to invoke other kernels throws
  a synchronous exception with the ``sycl::errc::invalid`` error
  code.

The precise semantics of this function are defined by each SYCL
backend specification, but the intent is that the kernel should
be invoked for the specified ``executionRange``.

Throws an exception with the ``sycl::errc::nd_range`` error code
if the global size defined in the associated ``executionRange``
defines a non-zero index space which is not evenly divisible by
the local size in each dimension.

This invocation function ignores any ``sycl::kernel_bundle`` that was
bound to this command group handler via
``sycl::handler::use_kernel_bundle()`` and instead implicitly uses the
kernel bundle that contains the ``kernelObject``. Throws an
exception with the ``sycl::errc::kernel_not_supported``
error code if the ``kernelObject`` is not compatible with either
the device associated with the primary queue of the command group or
with the device associated with the secondary queue (if specified).

.. seealso:: :ref:`parallel_for-invoke`

``parallel_for_work_group``
---------------------------

.. warning::

  Based on developer and implementation feedback, the hierarchical
  data parallel kernel feature is undergoing improvements to better
  align with the frameworks and patterns prevalent in modern programming.

  As this is a key part of the SYCL API and we expect to make changes to
  it, we temporarily recommend that new codes refrain from using this
  feature until the new API is finished in a near-future version of the
  SYCL specification, when full use of the updated feature will be
  recommended for use in new code.

  Existing codes using this feature will of course be supported by
  conformant implementations of this specification.

.. rubric:: Overload 1

::

  template <typename KernelName, typename WorkgroupFunctionType, int Dimensions>
  void parallel_for_work_group(sycl::range<Dimensions> numWorkGroups,
                               const WorkgroupFunctionType& kernelFunc)

Defines and invokes a hierarchical kernel as a lambda function
or a named function object type, encoding the body of each
work-group to launch. Generic kernel functions are permitted,
in that case the argument type is a :ref:`group`.

May contain multiple calls to ``parallel_for_work_item()`` member
functions representing the execution on each work-item.

Launches ``numWorkGroups`` work-groups of runtime-defined size.

The callable WorkgroupFunctionType can optionally take a
:ref:`kernel_handler` as its last parameter, in which
case the SYCL runtime will construct an instance of
:ref:`kernel_handler` and pass it to ``WorkgroupFunctionType``.

.. rubric:: Overload 2

::

  template <typename KernelName, typename WorkgroupFunctionType, int Dimensions>
  void parallel_for_work_group(sycl::range<Dimensions> numWorkGroups,
                               sycl::range<Dimensions> workGroupSize,
                               const WorkgroupFunctionType& kernelFunc)

Defines and invokes a hierarchical kernel as a lambda
function or a named function object type, encoding the
body of each work-group to launch. Generic kernel
functions are permitted, in that case the argument
type is a ``group``.

May contain multiple calls to ``parallel_for_work_item()``
member functions representing the execution on each work-item.
Launches ``numWorkGroups`` work-groups of
``workGroupSize`` work-items each.


The callable WorkgroupFunctionType can optionally take a
:ref:`kernel_handler` as its last parameter, in which
case the SYCL runtime will construct an instance of
:ref:`kernel_handler` and pass it to ``WorkgroupFunctionType``.

.. seealso:: :ref:`parallel_for_hierarchical`


.. _handler_expl_mem_ops:

Functions for explicit memory operations
========================================

In addition to kernels, command group objects can also be
used to perform manual operations on host and device memory
by using the copy API of the command group handler. Manual
copy operations can be seen as specialized kernels executing
on the device, except that typically this operations will be
implemented using a host API that exists as part of a backend.

These explicit copy operations have a `source` and a `destination`.

* When a :ref:`command-accessor` is the `source` of the operation,
  the `destination` can be a host pointer or another accessor.
  The source accessor must have either ``sycl::access_mode::read``
  or ``sycl::access_mode::read_write`` access mode.
* When a :ref:`command-accessor` is the `destination` of the explicit
  copy operation, the `source` can be a host pointer or another accessor.
  The `destination` accessor must have either ``sycl::access_mode::write``,
  ``sycl::access_mode::read_write``, ``sycl::access_mode::discard_write``
  or ``sycl::access_mode::discard_read_write`` access mode.

When a :ref:`command-accessor` is used as a parameter to one of these
explicit copy operations, the target must be either ``sycl::target::device``
or ``sycl::target::constant_buffer``.

When accessors are both the `source` and the `destination`, the operation is
executed on objects controlled by the SYCL runtime. The SYCL runtime is
allowed to not perform an explicit in-copy operation if a different path to
update the data is available according to the SYCL application memory model.

The most recent copy of the memory object may reside on any context
controlled by the SYCL runtime, or on the host in a pointer controlled
by the SYCL runtime. The SYCL runtime will ensure that data is copied
to the destination once the command group has completed execution.

Whenever a host pointer is used as either the `source` or the
`destination` of these explicit memory operations, it is the
responsibility of the user for that pointer to have at least
as much memory allocated as the accessor is giving access to,
e.g: if an accessor accesses a range of ``10`` elements of ``int``
type, the host pointer must at least have ``10 * sizeof(int)``
bytes of memory allocated.

A special case is the ``update_host`` member function. This
member function only requires a :ref:`command-accessor`, and
instructs the runtime to update the internal copy of the data
in the host, if any. This is particularly useful when users
use manual synchronization with host pointers, e.g. via
mutex objects on the :ref:`buffer` constructors.


``copy``
--------

.. rubric:: Overloads 1-2

::

  template <typename SrcT, int SrcDims, sycl::access_mode SrcMode, sycl::target SrcTgt,
            typename DestT, sycl::access::placeholder IsPlaceholder>
  void copy(sycl::accessor<SrcT, SrcDims, SrcMode, SrcTgt, IsPlaceholder> src,
            std::shared_ptr<DestT> dest);

  template <typename SrcT, int SrcDims, sycl::access_mode SrcMode, sycl::target SrcTgt,
            typename DestT, sycl::access::placeholder IsPlaceholder>
  void copy(sycl::accessor<SrcT, SrcDims, SrcMode, SrcTgt, IsPlaceholder> src,
            DestT* dest);

Copies the contents of the memory object accessed by
``src`` into the memory pointed to by ``dest``. ``dest``
must be a host pointer and must have at least as many
bytes as the range accessed by ``src``. The type ``DestT``
must be device copyable.

.. rubric:: Overloads 3-4

::

  template <typename SrcT, typename DestT, int DestDims, sycl::access_mode DestMode,
            sycl::target DestTgt, sycl::access::placeholder IsPlaceholder>
  void copy(std::shared_ptr<SrcT> src,
            sycl::accessor<DestT, DestDims, DestMode, DestTgt, IsPlaceholder> dest);

  template <typename SrcT, typename DestT, int DestDims, sycl::access_mode DestMode,
            sycl::target DestTgt, sycl::access::placeholder IsPlaceholder>
  void copy(const SrcT* src,
            accessor<DestT, DestDims, DestMode, DestTgt, IsPlaceholder> dest)

Copies the contents of the memory pointed to by
``src`` into the memory object accessed by ``dest``.
``src`` must be a host pointer and must have at
least as many bytes as the range accessed by ``dest``.
The type ``SrcT`` must be device copyable.


.. rubric:: Overload 5

::

  template <typename SrcT, int SrcDims, sycl::access_mode SrcMode, sycl::target SrcTgt,
            sycl::access::placeholder IsSrcPlaceholder, typename DestT, int DestDims,
            sycl::access_mode DestMode, sycl::target DestTgt,
            sycl::access::placeholder IsDestPlaceholder>
  void copy(sycl::accessor<SrcT, SrcDims, SrcMode, SrcTgt, IsSrcPlaceholder> src,
            sycl::accessor<DestT, DestDims, DestMode, DestTgt, IsDestPlaceholder> dest);

Copies the contents of the memory object accessed
by ``src`` into the memory object accessed by ``dest``.
The size of the ``src`` accessor determines the number
of bytes that are copied, and ``dest`` must have at least
this many bytes.

If the size of ``dest`` is too small, the implementation throws
a synchronous exception with the ``sycl::errc::invalid`` error code.

.. rubric:: Overload 6

::

  template <typename T> void copy(const T* src, T* dest, size_t count);

Copies count elements of type ``T`` from the pointer ``src``
to the pointer ``dest``. The ``dest`` and ``src`` parameters
must each either be a host pointer or a pointer within a USM
allocation that is accessible on the handler's device. If a
pointer is to a USM allocation, that allocation must have been
created from the same context as the handler's queue.

For more detail on USM, please see :ref:`usm_basic_concept`.

The type ``T`` must be device copyable.

.. rubric:: Example

:ref:`handler-example2`


``update_host``
---------------

::

  template <typename T, int Dims, sycl::access_mode Mode, sycl::target Tgt,
            sycl::access::placeholder IsPlaceholder>
  void update_host(sycl::accessor<T, Dims, Mode, Tgt, IsPlaceholder> acc);

The contents of the memory object accessed via ``acc``
on the host are guaranteed to be up-to-date after this
command group object execution is complete.


``fill``
--------

.. rubric:: Overload 1

::

  template <typename T, int Dims, sycl::access_mode Mode, sycl::target Tgt,
            sycl::access::placeholder IsPlaceholder>
  void fill(sycl::accessor<T, Dims, Mode, Tgt, IsPlaceholder> dest, const T& src);

Replicates the value of ``src`` into the memory
object accessed by ``dest``.

.. rubric:: Overload 2

::

  template <typename T>
  void fill(void* ptr, const T& pattern, size_t count);

Replicates the provided ``pattern`` into the memory at
address ``ptr``. The ``ptr`` must point within a USM
allocation from the same context as the handler's queue,
and the pointer must be accessible from the queue's device.
The ``pattern`` is filled ``count`` times.

For more detail on USM, please see :ref:`usm_basic_concept`.

The type ``T`` must be device copyable.


``memcpy``
----------

::

  void memcpy(void* dest, const void* src, size_t numBytes);

Copies ``numBytes`` of data from the pointer ``src`` to the
pointer ``dest``. The ``dest`` and ``src`` parameters must
each either be a host pointer or a pointer within a USM
allocation that is accessible on the handler's device.
If a pointer is to a USM allocation, that allocation must
have been created from the same context as the handler's queue.

For more detail on USM, please see :ref:`usm_basic_concept`.


``memset``
----------

::

  void memset(void* ptr, int value, size_t numBytes);

Fills ``numBytes`` bytes of memory beginning at
address ``ptr`` with ``value``. The ``ptr`` must
point within a USM allocation from the same context
as the handler's queue, and the pointer must be
accessible from the queue's device. Note that ``value``
is interpreted as an ``unsigned char``.

For more detail on USM, please see :ref:`usm_basic_concept`.


``prefetch``
------------

::

  void prefetch(void* ptr, size_t numBytes);

Enqueues a prefetch of ``num_bytes`` of data starting at
address ``ptr``. The ``ptr`` must point within a USM allocation
from the same context as the handler's queue, and the
pointer must be accessible from the queue's device.

For more detail on USM, please see :ref:`usm_basic_concept`.


``mem_advise``
--------------

::

  void mem_advise(void* ptr, size_t numBytes, int advice);

Enqueues a command that provides information to the
implementation about a region of USM starting at ``ptr``
and extending for ``numBytes`` bytes. The ``ptr`` must
point within a USM allocation from the same context
as the handler's queue, and the pointer must be
accessible from the queue's device.

The values for ``advice`` are vendor- or backend-specific,
with the exception of the value ``0`` which reverts the
advice for ``ptr`` to the default behavior.

For more detail on USM, please see :ref:`usm_basic_concept`.


Functions for using a kernel bundle
===================================

``use_kernel_bundle``
---------------------

::

  void use_kernel_bundle(const
      sycl::kernel_bundle<sycl::bundle_state::executable>& execBundle);

The command group associated with the handler will use device
images of the ``sycl::kernel_bundle`` ``execBundle`` in any of
its kernel invocation commands. If the ``sycl::kernel_bundle``
contains multiple device images that are compatible with the
device to which the kernel is submitted, then the device image
chosen is implementation-defined.

If the command group attempts to invoke a kernel that is not
contained by a compatible device image in ``execBundle``, the
kernel invocation command throws a synchronous exception
with the ``sycl::errc::kernel_not_supported`` error code. If the
command group has a secondary queue, then the ``execBundle``
must contain a kernel that is compatible with both the primary
queue's device and the secondary queue's device, otherwise the
kernel invocation command throws this exception.

Since the handler method for setting specialization constants
is incompatible with the kernel bundle method, applications
should not call this function if
``sycl::handler::set_specialization_constant()`` has been
previously called for this same command group.

.. rubric:: Exceptions

``sycl::errc::invalid``
  1. If the context associated with the command group
     handler via its associated primary queue or the
     context associated with the secondary queue
     (if provided) is different from the context
     associated with the kernel bundle specified by ``execBundle``.
  2. If ``sycl::handler::set_specialization_constant()``
     has been called for this command group.


.. _single_task-invoke:

==================
Single task invoke
==================

SYCL provides a simple interface to enqueue a kernel that
will be sequentially executed on a device. Only one instance
of the kernel will be executed. This interface is useful as a
primitive for more complicated parallel algorithms, as it can
easily create a chain of sequential tasks on a SYCL device
with each of them managing its own data transfers.

This function can only be called inside a command group using
the ``sycl::handler`` object created by the runtime. Any
accessors that are used in a kernel should be defined
inside the same command group.

.. note:: Local accessors are disallowed for single task invocations.

Example of kernel invocation with ``single_task``:

::

  myQueue.submit([&](sycl::handler& cgh) {
  cgh.single_task(
      [=] () {
      // [kernel code]
      }));
  });

For single tasks, the kernel member function takes no
parameters, as there is no need for index space classes
in a unary index space.

A :ref:`kernel_handler` can optionally be passed as
a parameter to the SYCL kernel function that is invoked
by ``single_task``. See :ref:`kernel_handler` for detailed
explanation.

::

  myQueue.submit([&](sycl::handler& cgh) {
  cgh.single_task(
      [=] (sycl::kernel_handler kh) {
      // [kernel code]
      }));
  });


.. seealso:: |SYCL_SPEC_SINGLE_TASK|

.. _parallel_for-invoke:

===================
Parallel for invoke
===================

The ``parallel_for`` member function of the ``sycl::handler``
class provides an interface to define and invoke a SYCL kernel
function in a command group, to execute in parallel execution
over a 3 dimensional index space. There are three overloads of
the ``parallel_for`` member function which provide variations
of this interface, each with a different level of complexity
and providing a different set of features.

For the simplest case, users need only provide the global
range (the total number of work-items in the index space)
via a :ref:`range` parameter. In this case the function
object that represents the SYCL kernel function must take
one of:

1. a single :ref:`item` parameter,
2. a single generic parameter (``template`` parameter or
   ``auto``) that will be treated as an item parameter,
3. any other type implicitly converted from :ref:`item`,
   representing the currently executing work-item
   within the range specified by the :ref:`range` parameter.

The execution of the kernel function is the same whether
the parameter to the SYCL kernel function is a :ref:`id`
or a :ref:`item`. What differs is the functionality
that is available to the SYCL kernel function via the
respective interfaces.

Examples of invoking ``parallel_for``
=====================================

Below is an examples of invoking a SYCL kernel function
with ``parallel_for`` using a lambda function, and passing
different parameters.

::

  // Example 1 (kernel argument type is sycl::id)
  myQueue.submit([&](sycl::handler& cgh) {
    sycl::accessor acc { myBuffer, cgh, write_only };

    cgh.parallel_for(sycl::range<1>(numWorkItems),
                    [=](sycl::id<1> index) { acc[index] = 42.0f; });
  });

  // Example 2 (kernel argument type is sycl::item)
  myQueue.submit([&](sycl::handler& cgh) {
    sycl::accessor acc { myBuffer, cgh, write_only };

    cgh.parallel_for(sycl::range<1>(numWorkItems), [=](sycl::item<1> item) {
      size_t index = item.get_linear_id();
      acc[index] = index;
    });
  });

  // Example 3 (kernel argument type is auto treated as an item)
  myQueue.submit([&](sycl::handler& cgh) {
    auto acc = myBuffer.get_access<sycl::access_mode::write>(cgh);

    cgh.parallel_for(sycl::range<1>(numWorkItems), [=](auto item) {
      size_t index = item.get_linear_id();
      acc[index] = index;
    });
  });

  // Example 4 (kernel argument type is size_t)
  myQueue.submit([&](sycl::handler& cgh) {
    auto acc = myBuffer.get_access<sycl::access_mode::write>(cgh);

    cgh.parallel_for(sycl::range<1>(numWorkItems), [=](size_t index) {
      acc[index] = index;
    });
  });

The ``parallel_for`` overload without an offset can be called
with either a number or a ``braced-init-list`` with 1-3 elements.
In that case the following calls are equivalent:

* ``parallel_for(N, some_kernel)`` has same effect
  as ``parallel_for(range<1>(N), some_kernel)``;
* ``parallel_for({N}, some_kernel)`` has same effect
  as ``parallel_for(range<1>(N), some_kernel)``;
* ``parallel_for({N1, N2}, some_kernel)`` has same effect
  as ``parallel_for(range<2>(N1, N2), some_kernel)``;
* ``parallel_for({N1, N2, N3}, some_kernel)`` has same effect
  as ``parallel_for(range<3>(N1, N2, N3), some_kernel)``.

Below is an example of invoking parallel_for with a number instead
of an explicit :ref:`range` object.

::

  myQueue.submit([&](sycl::handler& cgh) {
    auto acc = myBuffer.get_access<sycl::access_mode::write>(cgh);

    // parallel_for may be called with number (with numWorkItems)
    cgh.parallel_for(numWorkItems, [=](auto item) {
      size_t index = item.get_linear_id();
      acc[index] = index;
    });
  });

For SYCL kernel functions invoked via the above described
overload of the ``parallel_for`` member function, it is disallowed
to use :ref:`local_accessor` or to use a work-group barrier.

The following two examples show how a kernel function object can be
launched over a 3D grid, with 3 elements in each dimension. In the
first case work-item ids range from 0 to 2 inclusive, and in the
second case work-item ids run from 1 to 3.

::

  // Example 1
  myQueue.submit([&](sycl::handler& cgh) {
    cgh.parallel_for(sycl::range<3>(3, 3, 3), // global range
                     [=](sycl::item<3> it) {
                       //[kernel code]
                     });
  });

  // Example 2
  // This form of parallel_for with the "offset"
  // parameter is deprecated in SYCL 2020
  myQueue.submit([&](sycl::handler& cgh) {
    cgh.parallel_for(sycl::range<3>(3, 3, 3), // global range
                     sycl::id<3>(1, 1, 1),    // offset
                     [=](sycl::item<3> it) {
                       //[kernel code]
                     });
  });

A :ref:`kernel_handler` can optionally be passed as a parameter
to the SYCL kernel function that is invoked by both variants
of ``parallel_for``.

.. seealso:: |SYCL_SPEC_PAR_FOR|

.. _parallel_for_hierarchical:

================================
Parallel for hierarchical invoke
================================

.. warning::

  Based on developer and implementation feedback, the hierarchical
  data parallel kernel feature is undergoing improvements to better
  align with the frameworks and patterns prevalent in modern programming.

  As this is a key part of the SYCL API and we expect to make changes to
  it, we temporarily recommend that new codes refrain from using this
  feature until the new API is finished in a near-future version of the
  SYCL specification, when full use of the updated feature will be
  recommended for use in new code.

  Existing codes using this feature will of course be supported by
  conformant implementations of this specification.

The hierarchical parallel kernel execution interface provides the
same functionality as is available from the ND-range interface, but
exposed differently. To execute the same sixty-four work-items in eight
work-groups that we saw in a previous example, we execute an outer
``parallel_for_work_group`` call to create the groups. The member
function ``syck::handler::parallel_for_work_group`` is parameterized
by the number of work-groups, such that the size of each group is
chosen by the runtime, or by the number of work-groups and number
of work-items for users who need more control.

The body of the outer ``parallel_for_work_group`` call consists
of a lambda function or function object. The body of this
function object contains code that is executed only once for
the entire work-group. If the code has no side-effects and
the compiler heuristic suggests that it is more efficient
to do so, this code will be executed for each work-item.

Within this region any variable declared will have the
semantics of local memory, shared between all work-items
in the work-group. If the device compiler can prove that
an array of such variables is accessed only by a single
work-item throughout the lifetime of the work-group, for
example if access is derived from the id of the work-item
with no transformation, then it can allocate the data in
private memory or registers instead. To guarantee use of
private per-work-item memory, the :ref:`private_memory`
class can be used to wrap the data.

Example of kernel invocation using ``parallel_for_work_group``:

::

  myQueue.submit([&](sycl::handler& cgh) {
    // Issue 8 work-groups of 8 work-items each
    cgh.parallel_for_work_group(
        sycl::range<3>(2, 2, 2), sycl::range<3>(2, 2, 2),
        [=](sycl::group<3> myGroup, sycl::kernel_handler kh) {
          //[workgroup code]
          int myLocal; // this variable is shared between workitems
          // this variable will be instantiated for each work-item separately
          sycl::private_memory<int> myPrivate(myGroup);

          // Issue parallel work-items.  The number issued per work-group is
          // determined by the work-group size range of parallel_for_work_group.
          // In this case, 8 work-items will execute the parallel_for_work_item
          // body for each of the 8 work-groups, resulting in 64 executions
          // globally/total.
          myGroup.parallel_for_work_item([&](sycl::h_item<3> myItem) {
            //[work-item code]
            myPrivate(myItem) = 0;
          });

          // Implicit work-group barrier

          // Carry private value across loops
          myGroup.parallel_for_work_item([&](sycl::h_item<3> myItem) {
            //[work-item code]
            output[myItem.get_global_id()] = myPrivate(myItem);
          });
          //[workgroup code]
        });
  });

.. seealso:: |SYCL_SPEC_PAR_FOR_HIER|


.. _handler-example1:

=========
Example 1
=========

This example shows how to use ``single_task()`` member function.

Also it involves call of ``host_task()`` function, which is
described in :ref:`host_task-basic` chapter.

.. literalinclude:: /examples/host-task.cpp
   :lines: 5-
   :linenos:

Output:

.. literalinclude:: /examples/host-task.out
   :lines: 5-

.. _handler-example2:

=========
Example 2
=========

This example shows how to perform copy operations using
``copy()`` member function of ``sycl::handler`` class.

The example copies half of the contents of a ``std::vector``
into the device, leaving the rest of the contents of the
buffer on the device unchanged.

.. literalinclude:: /examples/handler-copy.cpp
   :lines: 5-
   :linenos:

Output:

.. literalinclude:: /examples/handler-copy.out
   :lines: 5-
