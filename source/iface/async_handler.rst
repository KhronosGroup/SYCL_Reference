..
  Copyright 2024 The Khronos Group Inc.
  SPDX-License-Identifier: CC-BY-4.0

.. _iface-async-error-handler:

**************************
Asynchronous error handler
**************************

::

  namespace sycl {

  using async_handler = std::function<void(sycl::exception_list)>;

  } // namespace sycl

The :ref:`queue` and :ref:`context` classes can optionally take
an asynchronous handler object ``sycl::async_handler`` on construction,
which is a callable such as a `function class` or `lambda`, with
an ``sycl::exception_list`` as a parameter. Invocation of an
``sycl::async_handler`` may be triggered by the queue member functions
``sycl::queue::wait_and_throw()`` or ``sycl::queue::throw_asynchronous()``,
by the ``sycl::event`` member function ``sycl::event::wait_and_throw()``,
or automatically on destruction of a :ref:`queue` or :ref:`context` that
contains unconsumed asynchronous errors. When invoked, an
``sycl::async_handler`` is called and receives an ``sycl::exception_list``
argument containing a list of exception objects representing any unconsumed
asynchronous errors associated with the :ref:`queue` or :ref:`context`.

When an asynchronous error instance has been passed to an
``sycl::async_handler``, then that instance of the error
has been consumed for handling and is not reported on any
subsequent invocations of the ``sycl::async_handler``.

The ``sycl::async_handler`` may be a named function object type, a
lambda function or a ``std::function``. The ``sycl::exception_list`` object
passed to the ``sycl::async_handler`` is constructed by the SYCL runtime.

.. seealso::

  |SYCL_SPEC_ASYNC_ERR_HAND|

  :ref:`iface-error-handling-rules`

  :ref:`iface-exceptions`

.. _behavior-without-async_hand:

===========================================
Behavior without an ``sycl::async_handler``
===========================================

If an asynchronous error occurs in a :ref:`queue` or :ref:`context` that
has no user-supplied asynchronous error handler object ``sycl::async_handler``,
then an implementation-defined default ``sycl::async_handler`` is called to
handle the error in the same situations that a user-supplied
``sycl::async_handler`` would be, as defined in section above.

The default ``sycl::async_handler`` must in some way report all errors
passed to it, when possible, and must then invoke ``std::terminate``
or equivalent.

.. _async_handler_example:

=========
Example 1
=========

Below is example of implementing an ``sycl::async_handler`` as lambda
function and passing it to the :ref:`queue`.

.. literalinclude:: /examples/async-handler.cpp
   :lines: 5-
   :linenos:

Output:

.. literalinclude:: /examples/async-handler.out
   :lines: 5-
