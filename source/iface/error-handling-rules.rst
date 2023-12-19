..
  Copyright 2023 The Khronos Group Inc.
  SPDX-License-Identifier: CC-BY-4.0

.. _iface-error-handling-rules:

********************
Error handling rules
********************

Error handling in a SYCL application (host code)
uses C++ exceptions. If an error occurs, it will
be thrown by the API function call and may be
caught by the user through standard C++ exception
handling mechanisms.

SYCL applications are asynchronous in the sense that
host and device code executions are decoupled from
one another except at specific points.

For example, device code executions often begin when
dependencies in the SYCL task graph are satisfied,
which occurs asynchronously from host code execution.
As a result of this the errors that occur on a device
cannot be thrown directly from a host API call, because
the call enqueueing a device action has typically already
returned by the time that the error occurs. Such errors
are not detected until the error-causing task executes or
tries to execute, and we refer to these as asynchronous
errors. For handling those type of errors see
:ref:`iface-async-error-handler`.

.. seealso::

  |SYCL_SPEC_ERROR_HAND_RULES|

  :ref:`iface-async-error-handler`

  :ref:`iface-exceptions`

===================================
Priorities of asynchronous handlers
===================================

If the SYCL runtime can associate an asynchronous
error with a specific queue, then:

* If the :ref:`queue` was constructed with an :ref:`sycl::async_handler
  <iface-async-error-handler>`, that handler is invoked to
  handle the error.
* Otherwise if the context enclosed by the queue was
  constructed with an :ref:`sycl::async_handler
  <iface-async-error-handler>`, that handler is
  invoked to handle the error.
* Otherwise when no handler was passed to either :ref:`queue`
  or :ref:`context` on construction, then a default handler
  is invoked to handle the error. The behavior is described
  in the :ref:`behavior-without-async_hand`.
* All handler invocations in this list occur at times as defined
  in the :ref:`iface-async-error-handler`.

If the SYCL runtime cannot associate an asynchronous
error with a specific queue, then:

* If the context in which the error occurred was
  constructed with an :ref:`sycl::async_handler
  <iface-async-error-handler>`, then that handler
  is invoked to handle the error.
* Otherwise when no handler was passed to the
  associated :ref:`context` on construction,
  then a default handler is invoked to handle the error.
  The behavior is described in the :ref:`behavior-without-async_hand`.
* All handler invocations in this list occur at times as defined
  in the :ref:`iface-async-error-handler`.

==========================================
Asynchronous errors with a secondary queue
==========================================

If an asynchronous error occurs when running or enqueuing
a command group which has a secondary queue specified,
then the command group may be enqueued to the secondary
queue instead of the primary queue.
The error handling in this case is also configured
using the ``sycl::async_handler`` provided for both queues.

If there is no ``sycl::async_handler`` given on any of the
queues, then the asynchronous error handling proceeds
through the contexts associated with the queues, and if
they were also constructed without ``sycl::async_handlers``, then
the default handler will be used.

If the primary queue fails and there is an ``sycl::async_handler``
given at this queue's construction, which populates the
``sycl::exception_list`` parameter, then any errors will be added
and can be thrown whenever the user chooses to handle those
exceptions. Since there were errors on the primary queue and
a secondary queue was given, then the execution of the kernel is
re-scheduled to the secondary queue and any error reporting
for the kernel execution on that queue is done through that
queue, in the same way as described above. The secondary queue
may fail as well, and the errors will be thrown if there is an
``sycl::async_handler`` and either ``wait_and_throw()`` or ``throw()`` are
called on that queue.

If no ``sycl::async_handler`` was specified, then the one associated
with the queue's context will be used and if the context was
also constructed without an ``sycl::async_handler``, then the default
handler will be used. The command group function object
event returned by that function will be relevant to the
queue where the kernel has been enqueued.

Below is an example of catching a ``sycl::exception``
(see :ref:`iface-exceptions`) and printing out the error message.

::

  void catch_any_errors(sycl::context const& ctx) {
    try {
      do_something_to_invoke_error(ctx);
    } catch (sycl::exception const& e) {
      std::cerr << e.what();
    }
  }

Below is an example of catching a ``sycl::exception``
(see :ref:`iface-exceptions`) with the ``sycl::errc::invalid``
error code and printing out the error message.

::

  void catch_invalid_errors(sycl::context const& ctx) {
    try {
      do_something_to_invoke_error(ctx);
    } catch (sycl::exception const& e) {
      if (e.code() == sycl::errc::invalid) {
        std::cerr << "Invalid error: " << e.what();
      } else {
        throw;
      }
    }
  }
