.. _iface-error-handling:

**********
Exceptions
**********

.. rst-class:: api-class
	       
=========
exception
=========

::
   
   class exception;

.. member-toc::

Container for an exception that occurs during execution. Synchronous
API's throw exceptions that may be caught with C++ exception handling
methods. The SYCL runtime holds exceptions that occur during
asynchronous operations until :ref:`queue-wait_and_throw` or
:ref:`queue-throw_asynchronous` is called. They runtime delivers the
exception as a list to the `async_handler`_ associated with the
:ref:`queue`.

   
what
====

::
   
   const char *what() const;

Returns string that describes the error that triggered the exception.

has_context
===========

::

   bool has_context() const;


Returns true if error has an associated :ref:`context`.

get_context
===========

::

   context get_context() const;


Returns :ref:`context` associated with this error.

get_cl_code
===========

::

   cl_int get_cl_code() const;


Returns OpenCL error code if the error is an OpenCL error, otherwise
``CL_SUCCESS``.

.. rst-class:: api_class
	       
==============
exception_list
==============

::

   class exception_list;

An exContainer for a list of asychronous exceptions that occur in the same
queue. Re

.. rubric:: Member types

===============  ===
value_type
reference
const_reference
size_type
iterator
const_iterator
===============  ===

.. member-toc::

size
====

::

   size_type size() const;

Returns number of elements in the list.

begin
=====

::

   iterator begin() const;

Returns an iterator to the beginning of the list of exceptions.

end
===

::

   iterator end() const;

Returns an iterator to the beginning of the list of exceptions.


==================
Derived exceptions
==================

runtime_error
=============

::

   class runtime_error : public exception;

kernel_error
============

::

   class kernel_error : public runtime_error;

Error that occured before or while enqueuing the SYCL kernel.

accessor_error
==============

::

   class accessor_error : public runtime_error;

Error regarding :ref:`iface-accessors`.

nd_range_error
==============

::

   class nd_range_error : public runtime_error;

Error regarding the :ref:`nd_range` for a SYCL kernel.

event_error
===========

::

   class event_error : public runtime_error;

Error regarding an :ref:`event`.

invalid_parameter_error
=======================

::

   class invalid_parameter_error : public runtime_error;

Error regarding parameters to a SYCL kernel, including captured
parameters to a lambda.

device_error
============

::

   class device_error : public exception;

compile_program_error
=====================

::

   class compile_program_error : public device_error;

Error while compiling a SYCL kernel.

link_program_error
==================

::

   class link_program_error : public device_error;

Error linking a SYCL kernel to a SYCL device.

invalid_object_error
====================

::

   class invalid_object_error : public device_error;

Error regarding memory objects used inside a kernel.

memory_allocation_error
=======================

::

   class memory_allocation_error : public device_error;

Error regarding memory allocation on the SYCL device.

platform_error
==============

::

   class platform_error : public device_error;

Error triggered by the :ref:`platform`.

profililng_error
================

::

   class profiling_error : public device_error;

Error triggered while profiling is enabled.

featured_non_supported
======================

::

   class feature_not_supported : public device_error;

Optional feature or extension is not available on the :ref:`device`.

.. _async_handler:

=============
async_handler
=============

::

   void handler(exception_list e);

.. rubric:: Parameters

=============  ===
e              List of asynchronous exceptions. See `exception_list`_
=============  ===

The SYCL runtime delivers asynchronous exceptions by invoking an
``async_handler``. The handler is passed to a :ref:`queue`
constructor. The SYCL runtime delivers asynchronous exceptions to the
handler when :ref:`queue-wait_and_throw` or
:ref:`queue-throw_asynchronous` is called.
