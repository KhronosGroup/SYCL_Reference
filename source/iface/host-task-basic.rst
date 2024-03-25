..
  Copyright 2024 The Khronos Group Inc.
  SPDX-License-Identifier: CC-BY-4.0

.. _host_task-basic:

*****************
Host task concept
*****************

A host task is a native C++ callable which is scheduled by the SYCL runtime.
A host task is submitted to a :ref:`queue` via a command group by
a host task command.

When a host task command is submitted to a :ref:`queue` it is scheduled
based on its data dependencies with other commands including kernel
invocation commands and asynchronous copies, resolving any requisites
created by accessors attached to the command group
as defined in |SYCL_SPEC_MEM_MODEL|.

Since a host task is invoked directly by the SYCL runtime rather than being
compiled as a SYCL kernel function, it does not have the same restrictions as
a SYCL kernel function, and can therefore contain any arbitrary C++ code.

Capturing accessors in a host task is allowed, however, capturing or using any
other SYCL class that has reference semantics
(see |SYCL_SPEC_COMMON_REFERENCE|) is undefined behavior.

A host task can be enqueued on any :ref:`queue` and the callable will be
invoked directly by the SYCL runtime, regardless of which :ref:`device`
the queue is associated with.

A host task is enqueued on a :ref:`queue` via the ``sycl::host_task`` member
function of the ``sycl::handler`` class. The event returned by the
submission of the associated command group enters the completed state
(corresponding to a status of ``sycl::info::event_command_status::complete``)
once the invocation of the provided C++ callable has returned. Any uncaught
exception thrown during the execution of a host task will be turned
into an asynchronous error that can be handled
as described in |SYCL_SPEC_ASYNC_ERR_HAND|.

A host task can optionally be used to interoperate with the native backend
objects associated with the :ref:`queue` executing the host task,
the context that the :ref:`queue` is associated with, the :ref:`device`
that the :ref:`queue`  is associated with and the accessors that have been
captured in the callable, via an optional ``sycl::interop_handle`` parameter.

This allows host tasks to be used for two purposes: either as a task which
can perform arbitrary C++ code within the scheduling of the SYCL runtime or
as a task which can perform interoperability at a point within the scheduling
of the SYCL runtime.

For the former use case, construct a buffer accessor with
``sycl::target::host_task`` or an image accessor with
``sycl::image_target::host_task``. This makes the buffer
or image available on the host during execution of the host task.

For the latter case, construct a buffer accessor with
``sycl::target::device`` or ``sycl::target::constant_buffer``,
or construct an image accessor with ``sycl::image_target::device``.
This makes the buffer or image available on the :ref:`device` that
is associated with the :ref:`queue` used to submit the host task,
so that it can be accessed via interoperability member functions
provided by the ``sycl::interop_handle`` class.

.. seealso:: |SYCL_SPEC_HOST_TASKS|
