..
  Copyright 2020 The Khronos Group Inc.
  SPDX-License-Identifier: CC-BY-4.0

.. _queues:

	       
******
Queues
******

.. _queue:

.. rst-class:: api-class

===========
sycl::queue
===========

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

.. todo::

   Example uses basic constructor and demonstrates the commonly uses
   member functions.

.. seealso:: |SYCL_SPEC_QUEUE|

.. _queue-constructors:

(Constructors)
==============

::
   
  explicit queue(const sycl::property_list &propList = {});
  explicit queue(const sycl::async_handler &asyncHandler,
                 const sycl::property_list &propList = {});
  explicit queue(const sycl::device_selector &deviceSelector,
                 const sycl::property_list &propList = {});
  explicit queue(const sycl::device_selector &deviceSelector,
                 const sycl::async_handler &asyncHandler,
		 const sycl::property_list &propList = {});
  explicit queue(const sycl::device &syclDevice, const sycl::property_list &propList = {});
  explicit queue(const sycl::device &syclDevice, const sycl::async_handler &asyncHandler,
                 const sycl::property_list &propList = {});
  explicit queue(const sycl::context &syclContext,
                 const sycl::device_selector &deviceSelector,
		 const sycl::property_list &propList = {});
  explicit queue(const sycl::context &syclContext,
                 const sycl::device_selector &deviceSelector,
                 const sycl::async_handler &asyncHandler,
		 const sycl::property_list &propList = {});
  explicit queue(const sycl::context &syclContext,
                 const sycl::device &syclDevice,
		 const sycl::property_list &propList = {});
  explicit queue(const sycl::context &syclContext, const sycl::device &syclDevice,
                 const sycl::async_handler &asyncHandler,
		 const sycl::property_list &propList = {});
  explicit queue(cl_command_queue clQueue, const sycl::context& syclContext,
                 const sycl::async_handler &asyncHandler = {});

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
propList                See `queue-properties`_
asyncHandler            Called for asynchronous exceptions, see :ref:`async_handler`
deviceSelector          Selects device for queue
syclDevice              Device for queue
syclContext             Associate queue with the context
clQueue                 Assocate queue with OpenCL|trade| queue
======================  ===
  
.. rubric:: Exceptions

invalid_object_error
  If ``syclContext`` does not encapsulate ``syclDevice``.

.. todo:: example exercise various constructors


get
===


::
   
  cl_command_queue get() const;

Return OpenCL queue associated with SYCL queue.

get_context
===========

::
   
  sycl::context get_context() const;

Returns context associated with queue.

get_device
==========

::
   
  sycl::device get_device() const;

Returns device associated with queue.

is_host
=======

::
   
  bool is_host() const;

Returns True if queue executes on host device.

get_info
========

::
   
  template <sycl::info::queue param>
  typename sycl::info::param_traits<sycl::info::queue, param>::return_type get_info() const;

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
provided in :ref:`queue-constructors`.

.. _queue-throw_asynchronous:

throw_asynchronous
==================

::
   
  void throw_asynchronous();

Passes any asynchronous errors to handler provided in
:ref:`queue-constructors`.

.. _queue-memcpy:

memcpy
======

::
   
   sycl::event memcpy(void* dest, const void* src, size_t num_bytes);

Set memory allocated with :ref:`malloc_device`. For usage, see
:ref:`event-elapsed-time`.

.. _queue-memset:

memset
======

::

   sycl::event memset(void* ptr, int value, size_t num_bytes);
   
Set memory allocated with :ref:`malloc_device`. For usage, see
:ref:`event-elapsed-time`.

.. _queue-fill:

fill
====

::

   template <typename T>
   sycl::event fill(void* ptr, const T& pattern, size_t count);

Set memory allocated with :ref:`malloc_device`.

=================
sycl::info::queue
=================

::

  enum class queue : int {
    context,
    device,
    reference_count,
  };

Used as a template parameter for get_info_ to determine the type of
information.

===============  ==========================  ===
Descriptor       Return type                 Description
===============  ==========================  ===
context          context                     SYCL context associated with the queue
device           device                      SYCL device associated with the queue
reference_count  cl_uint                     Reference count of the queue
===============  ==========================  ===


.. _queue-properties:

================
Queue properties
================

Queue properties are specified in the queue constructor.

.. rst-class:: api-class

sycl::property::queue::enable_profiling
=======================================

::

   class enable_profiling;
   
SYCL runtime captures profiling information for command groups
submitted to the queue.

(constructors)
--------------

::

   enable_profiling();

Constructs an enable_profiling property instance.

.. rubric:: Example

See :ref:`event-elapsed-time`.
  
.. rst-class:: api-class

sycl::property::queue::in_order
===============================

|2020|

::

   class in_order;
   
SYCL queue provides in-order semantics.

(constructors)
--------------

::

   in_order();

Constructs an in_order property instance.

  
