..
  Copyright 2023 The Khronos Group Inc.
  SPDX-License-Identifier: CC-BY-4.0

.. _iface-async-error-handler:

**************************
Asynchronous error handler
**************************

The :ref:`queue` and :ref:`context` classes can optionally take
an asynchronous handler object ``async_handler`` on construction,
which is a callable such as a `function class` or `lambda`, with
an ``sycl::exception_list`` as a parameter. Invocation of an ``async_handler``
may be triggered by the queue member functions
``sycl::queue::wait_and_throw()`` or ``sycl::queue::throw_asynchronous()``,
by the ``sycl::event`` member function ``sycl::event::wait_and_throw()``,
or automatically on destruction of a :ref:`queue` or :ref:`context` that
contains unconsumed asynchronous errors. When invoked, an ``async_handler``
is called and receives an ``sycl::exception_list`` argument containing a
list of exception objects representing any unconsumed asynchronous errors
associated with the :ref:`queue` or :ref:`context`.

When an asynchronous error instance has been passed to an ``async_handler``,
then that instance of the error has been consumed for handling and is not
reported on any subsequent invocations of the ``async_handler``.

The ``async_handler`` may be a named function object type, a lambda function
or a ``std::function``. The ``sycl::exception_list`` object passed to the
``async_handler`` is constructed by the SYCL runtime.

.. seealso::

  |SYCL_SPEC_ASYNC_ERR_HAND|

  :ref:`iface-error-handling-rules`

  :ref:`iface-exceptions`

.. _behavior-without-async_hand:

======================================
Behavior without an ``async_handler``
======================================

If an asynchronous error occurs in a :ref:`queue` or :ref:`context` that
has no user-supplied asynchronous error handler object ``async_handler``,
then an implementation-defined default ``async_handler`` is called to
handle the error in the same situations that a user-supplied
``async_handler`` would be, as defined in section above.

The default ``async_handler`` must in some way report all errors
passed to it, when possible, and must then invoke ``std::terminate``
or equivalent.
