..
  Copyright 2020 The Khronos Group Inc.
  SPDX-License-Identifier: CC-BY-4.0

******
Events
******


.. _event:

.. rst-class:: api-class
	       
===========
sycl::event
===========

::
   
   class event;

Events support the explicit control of scheduling of kernels, and
querying status of a running kernel. Operations like
:ref:`queue-submit` that queue a kernel for execution may accept an
event to wait on and return an event associated with the queued
kernel.

.. seealso:: |SYCL_SPEC_EVENT|

(constructors)
==============

::
   
  event();
  event(cl_event clEvent, const sycl::context& syclContext);

Construct an event.

cl_event_get
============

::
   
  cl_event get();


Returns OpenCL|trade| event associated with this event.

is_host
=======

::
   
  bool is_host() const;


Returns True if this a host event

get_wait_list
=============

::
   
  sycl::vector_class<sycl::event> get_wait_list();


Returns vector of events that this events waits on.

wait
====

::
   
  void wait();

Wait for the associated command to complete.

wait
====

::
   
  static void wait(const sycl::vector_class<sycl::event> &eventList);

Wait for vector of events to complete.

wait_and_throw
==============

::
   
  void wait_and_throw();

Wait for an event to complete, and pass asynchronous errors to handler
associated with the command.

wait_and_throw
==============

::

  static void wait_and_throw(const sycl::vector_class<sycl::event> &eventList);

Wait for a vector of events to complete, and pass asynchronous errors
to handlers associated with the commands.

get_info
========

::
   
  template <sycl::info::event param>
  typename sycl::info::param_traits<sycl::info::event, param>::return_type get_info() const;

Returns information about the queue as determined by ``param``. See
`sycl::info::event`_ for details.


get_profiling_info
==================

::
   
  template <sycl::info::event_profiling param>
  typename sycl::info::param_traits<sycl::info::event_profiling, param>::return_type get_profiling_info() const;

Returns information about the queue as determined by ``param``. See
`sycl::info::event_profiling`_ for details.

.. _event-elapsed-time:
   
.. rubric:: Example

Measure the elapsed time of a memcpy executed on a device with event
profiling info.
   
.. literalinclude:: /examples/event-elapsed-time.cpp
   :lines: 5-
   :linenos:

Output:

.. literalinclude:: /examples/event-elapsed-time.out
   :lines: 5-


=================
sycl::info::event
=================

::
   
   enum class event: int {
     command_execution_status,
     reference_count
   };

Used as a template parameter for get_info_ to determine the type of
information.

========================  ================================  ===
Descriptor                Return type                       Description
========================  ================================  ===
command_execution_status  sycl::info::event_command_status  See `sycl::info::event_command_status`_
reference_count           cl_uint                           Reference count of the event
========================  ================================  ===
	    
================================
sycl::info::event_command_status
================================

::

   enum class event_command_status : int {
     submitted,
     running,
     complete
   };


===========================
sycl::info::event_profiling
===========================

::

   enum class event_profiling : int {
     command_submit,
     command_start,
     command_end
   };

Used as a template parameter for get_profiling_info_ to determine the
type of information.

===============  ==========================  ===
Descriptor       Return type                 Description
===============  ==========================  ===
command_submit   cl_ulong                    Time in nanoseconds when :ref:`command_group` was submitted
command_start    cl_ulong                    Time in nanoseconds when :ref:`command_group` started execution
command_end      cl_ulong                    Time in nanoseconds when :ref:`command_group` finished execution
===============  ==========================  ===
   
