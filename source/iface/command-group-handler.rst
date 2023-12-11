..
  Copyright 2020 The Khronos Group Inc.
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
  group, and attempting to access dataelements from it produces 
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
kernels, nd-range in work-groups, or hierarchical parallelism.

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

Functions for explicit memory operations
========================================

Functions for using a kernel bundle
===================================

.. _handler-example1:

=========
Example 1
=========

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

.. literalinclude:: /examples/handler-copy.cpp
   :lines: 5-
   :linenos:

Output:

.. literalinclude:: /examples/handler-copy.out
   :lines: 5-

.. _parallel_for_hierarchical:

================================
Parallel for hierarchical invoke
================================
