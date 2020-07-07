..
  // Copyright (c) 2011-2020 The Khronos Group, Inc.
  //
  // Licensed under the Apache License, Version 2.0 (the License);
  // you may not use this file except in compliance with the License.
  // You may obtain a copy of the License at
  //
  //     http://www.apache.org/licenses/LICENSE-2.0
  //
  // Unless required by applicable law or agreed to in writing, software
  // distributed under the License is distributed on an AS IS BASIS,
  // WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  // See the License for the specific language governing permissions and
  // limitations under the License.

******
Events
******


.. _event:

.. rst-class:: api-class
	       
=====
event
=====

::
   
   class event;

Events support the explicit control of scheduling of kernels, and
querying status of a running kernel. Operations like
:ref:`queue-submit` that queue a kernel for execution may accept an
event to wait on and return an event associated with the queued
kernel.

.. member-toc::

(constructors)
==============

::
   
  event();
  event(cl_event clEvent, const context& syclContext);

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
   
  vector_class<event> get_wait_list();


Returns vector of events that this events waits on.

wait
====

::
   
  void wait();

Wait for the associated command to complete.

wait
====

::
   
  static void wait(const vector_class<event> &eventList);

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

  static void wait_and_throw(const vector_class<event> &eventList);

Wait for a vector of events to complete, and pass asynchronous errors
to handlers associated with the commands.

get_info
========

::
   
  template <info::event param>
  typename info::param_traits<info::event, param>::return_type get_info() const;

Returns information about the queue as determined by ``param``. See
`Event Info`_ for details.


get_profiling_info
==================

::
   
  template <info::event_profiling param>
  typename info::param_traits<info::event_profiling, param>::return_type get_profiling_info() const;

Returns information about the queue as determined by ``param``. See
`Event profiling info`_ for details.

==========
Event info
==========

::
   
   enum class event: int {
     command_execution_status,
     reference_count
   };

.. rubric:: Namespace

::

   info

Used as a template parameter for get_info_ to determine the type of
information.

========================  ==========================  ===
Descriptor                Return type                 Description
========================  ==========================  ===
command_execution_status  info::event_command_status  See event_command_status_
reference_count           cl_uint                     Reference count of the event
========================  ==========================  ===
	    
====================
event_command_status
====================

::

   enum class event_command_status : int {
     submitted,
     running,
     complete
   };


====================
Event profiling info
====================

::

   enum class event_profiling : int {
     command_submit,
     command_start,
     command_end
   };

.. rubric:: Namespace

::

   info

Used as a template parameter for get_profiling_info_ to determine the
type of information.

===============  ==========================  ===
Descriptor       Return type                 Description
===============  ==========================  ===
command_submit   cl_ulong                    Time in nanoseconds when :ref:`command_group` was submitted
command_start    cl_ulong                    Time in nanoseconds when :ref:`command_group` started execution
command_end      cl_ulong                    Time in nanoseconds when :ref:`command_group` finished execution
===============  ==========================  ===
   
