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

.. _queues:

	       
******
Queues
******

.. _queue:

.. rst-class:: api-class

=========
``queue``
=========

::
   
   class queue;

.. member-toc::

(constructors)
==============

::
   
  explicit queue(const property_list &propList = {});
  explicit queue(const async_handler &asyncHandler,
                 const property_list &propList = {});
  explicit queue(const device_selector &deviceSelector,
                 const property_list &propList = {});
  explicit queue(const device_selector &deviceSelector,
                 const async_handler &asyncHandler,
		 const property_list &propList = {});
  explicit queue(const device &syclDevice, const property_list &propList = {});
  explicit queue(const device &syclDevice, const async_handler &asyncHandler,
                 const property_list &propList = {});
  explicit queue(const context &syclContext,
                 const device_selector &deviceSelector,
		 const property_list &propList = {});
  explicit queue(const context &syclContext,
                 const device_selector &deviceSelector,
                 const async_handler &asyncHandler,
		 const property_list &propList = {});
  explicit queue(const context &syclContext,
                 const device &syclDevice,
		 const property_list &propList = {});
  explicit queue(const context &syclContext, const device &syclDevice,
                 const async_handler &asyncHandler,
		 const property_list &propList = {});
  explicit queue(cl_command_queue clQueue, const context& syclContext,
                 const async_handler &asyncHandler = {});

.. rubric:: Parameters

======================  ===
propList                See `Queue Properties`_
asyncHandler            Called for asynchronous exceptions
deviceSelector          Select device for queue
syclDevice              Select device for queue
syclContext             Associate queue with the context
clQueue                 Encapsulate OpenCL queue
======================  ===
  

get
===


::
   
  cl_command_queue get() const;

Return OpenCL queue associated with SYCL queue.

get_context
===========

::
   
  context get_context() const;

Returns context associated with queue.

get_device
==========

::
   
  device get_device() const;

Returns device associated with queue


is_host
=======

::
   
  bool is_host() const;

Returns True if queue executes on host device.


get_info
========

::
   
  template <info::queue param>
  typename info::param_traits<info::queue, param>::return_type get_info() const;

Returns information about the queue as determined by ``param``. See
queue_ for details.

submit
======

::
   
  template <typename T>
  event submit(T cgf);
  template <typename T>
  event submit(T cgf, const queue &secondaryQueue);

.. rubric:: Parameters

=================  ===
cgf
secondaryQueue
=================  ===

Submit a task to the queue.

wait
====

::
   
  void wait();

Wait for all enqueued tasks to complete.

wait_and_throw
==============

::
   
  void wait_and_throw();

Wait for all enqueued tasks and pass asynchronous errors to handler.

throw_asynchronous
==================

::
   
  void throw_asynchronous();

Pass asynchronous errors to handler.

==========
Queue Info
==========

::

  enum class queue : int {
    context,
    device,
    reference_count,
  };

.. rubric:: Namespace

::

   info

Used as a template parameter for get_info_ to determine the type of
information.

===============  ==========================  ===
Descriptor       Return type                 Description
===============  ==========================  ===
context          context                     SYCL context associated with the queue
device           device                      SYCL device associated with the queue
reference_count  cl_uint                     reference count of the queue
===============  ==========================  ===


================
Queue Properties
================

.. rubric:: Namespace

::

   property::queue
	    
enable_profiling
  When passed to a constructor for a queue, SYCL runtime captures
  profiling information for command groups submitted to the queue.
