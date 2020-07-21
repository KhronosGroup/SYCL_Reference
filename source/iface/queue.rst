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

=====
queue
=====

::
   
   class queue;

Queues connect a host program to a single device. Programs submit
tasks to a device via the queue and may monitor the queue for
completion. A program initiates the task by submitting a
:ref:`command_group-function-object` to a queue. The command group
defines a kernel function, the prerequisites to execute the kernel
function, and an invocation of the kernel function on an index
space. After submitting the command group, a program may use the queue
to monitor the completion of the task for completion and errors.

.. rubric:: Example

.. todo::

   Example uses basic constructor and demonstrates the commonly uses
   member functions.

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

Construct a queue.

Constructing a queue selects the device attached to the queue. The
program may control the device by passing a cl_command_queue,
:ref:`device`, or a :ref:`device_selector <device-selectors>`. If none
are provided, the constructor uses the :ref:`default_selector
<built-in-device-selectors>` to select a device. The constructor
implicitly creates the :ref:`context`, :ref:`platform`, and
:ref:`device` as needed.

The SYCL runtime executes the tasks asynchronously. Programs may catch
asynchronous errors that occur during execution by constructing the
queue with an ``asyncHandler`` and calling wait_and_throw_.

.. rubric:: Parameters

======================  ===
propList                See `Queue Properties`_
asyncHandler            Called for asynchronous exceptions, see :ref:`async_handler`
deviceSelector          Selects device for queue
syclDevice              Device for queue
syclContext             Associate queue with the context
clQueue                 Assocate queue with OpenCL|trade| queue
======================  ===
  
.. rubric:: Exceptions

invalid_object_error
  If ``syclContext`` does not encapsulate ``syclDevice``.

.. rubric:: Example

.. todo:: exercise various constructors


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

Returns device associated with queue.

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

.. _queue-submit:

submit
======

::
   
  template <typename T>
  event submit(T cgf);
  template <typename T>
  event submit(T cgf, const queue &secondaryQueue);

.. rubric:: Template parameters

=================  ===
T
=================  ===

.. rubric:: Parameters

=================  ===
cgf                Command group function object
secondaryQueue     On error, runtime resubmits command group to the secondary queue.
=================  ===

Submit a command group function object to the queue for asynchronous
execution.

Returns an :ref:`event`, which may be used for synchronizing enqueued
tasks. See :ref:`command_group-function-object` for more
information on the ``cgf`` parameter.

In most cases, the ``T`` template parameter is not provided because it
is inferred from the type of ``cgf``.

.. rubric:: Exceptions
	    
The runtime resubmits the command group to the secondary queue
if an error occurs executing on the primary queue.


wait
====

::
   
  void wait();

Wait for all enqueued tasks to complete.

.. _queue-wait_and_throw:

wait_and_throw
==============

::
   
  void wait_and_throw();

Wait for all enqueued tasks and pass asynchronous errors to handler
provided in `(constructors)`_.

.. _queue-throw_asynchronous:

throw_asynchronous
==================

::
   
  void throw_asynchronous();

Passes any asynchronous errors to handler provided in
`(constructors)`_.

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
reference_count  cl_uint                     Reference count of the queue
===============  ==========================  ===


================
Queue Properties
================

.. rubric:: Namespace

::

   property::queue
	    
Queue properties are specified in the queue constructor.

enable_profiling
  SYCL runtime captures profiling information for command groups
  submitted to the queue.
