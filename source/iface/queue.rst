..
  Copyright 2020 The Khronos Group Inc.
  SPDX-License-Identifier: CC-BY-4.0

.. _queues:


******
Queues
******

.. _queue:

.. rst-class:: api-class

===============
``sycl::queue``
===============

::

   class queue;

Queues connect a host program to a single device. Programs submit
tasks to a device via the queue and may monitor the queue for
completion. A program initiates the task by submitting a command group
to a queue. The command group defines a kernel function, the
prerequisites to execute the kernel function, and an invocation of the
kernel function on an index space. After submitting the command group,
a program may use the queue to monitor the completion of the task for
completion and errors.

.. todo::

   Example uses basic constructor and demonstrates the commonly uses
   member functions.

.. seealso:: `queue in SYCL Specification <https://www.khronos.org/registry/SYCL/specs/sycl-2020/html/sycl-2020.html#sec:interface.queue.class>`__

.. _queue-constructors:

(Constructors)
==============

::

  explicit queue(const property_list &propList = {});
  explicit queue(const async_handler &asyncHandler,
                 const property_list &propList = {});
  template <typename DeviceSelector>
  explicit queue(const DeviceSelector &deviceSelector,
                 const property_list &propList = {});
  template <typename DeviceSelector>
  explicit queue(const DeviceSelector &deviceSelector,
                 const async_handler &asyncHandler,
                 const property_list &propList = {});
  explicit queue(const device &syclDevice, const property_list &propList = {});
  explicit queue(const device &syclDevice, const async_handler &asyncHandler,
                 const property_list &propList = {});
  template <typename DeviceSelector>
  explicit queue(const context &syclContext,
                 const DeviceSelector &deviceSelector,
                 const property_list &propList = {});
  template <typename DeviceSelector>
  explicit queue(const context &syclContext,
                 const DeviceSelector &deviceSelector,
                 const async_handler &asyncHandler,
                 const property_list &propList = {});
  explicit queue(const context &syclContext, const device &syclDevice,
                 const property_list &propList = {});
  explicit queue(const context &syclContext, const device &syclDevice,
                 const async_handler &asyncHandler,
                 const property_list &propList = {});

Construct a queue.

Constructing a queue selects the device attached to the queue. The
program may control the device by passing a cl_command_queue,
:ref:`device`, or a :ref:`device_selector <device-selectors>`. If none
are provided, the constructor uses the :ref:`default_selector
<built-in-device-selectors>` to select a device. The constructor
implicitly creates the :ref:`context`, :ref:`platform`, and
:ref:`device` as needed.

The SYCL runtime may execute tasks asynchronously. To catch exceptions
from asynchronous host tasks, construct the queue with an
``asyncHandler`` and call wait_and_throw_.

.. rubric:: Parameters

.. list-table::

   * - ``propList``
     - See `queue-properties`_
   * - ``asyncHandler``
     - Called for asynchronous exceptions, see :ref:`async_handler`
   * - ``deviceSelector``
     - Selects device for queue
   * - ``syclDevice``
     - Device for queue
   * - ``syclContext``
     - Associate queue with the context
   * - ``clQueue``
     - Associate queue with OpenCL|trade| queue

.. rubric:: Exceptions

invalid_object_error
  If ``syclContext`` does not encapsulate ``syclDevice``.

.. todo:: example exercise various constructors


``get_backend``
===============

::

  backend get_backend() const noexcept;

``get_context``
===============

::

  context get_context() const;

Returns context associated with queue.

``get_device``
===============

::

  device get_device() const;

Returns device associated with queue.

``is_in_order``
===============

::

  bool is_in_order() const;

Returns ``true`` if queue is in order.

``get_info``
============

::

  template <typename param> typename param::return_type get_info() const;

Returns information about the queue as determined by ``param``. See
queue_ for details.

``get_backend_info``
====================

::

  template <typename param>
  typename param::return_type get_backend_info() const;


.. _queue-submit:

``submit``
==========

::

  template <typename T>
  event submit(T cgf);
  template <typename T>
  event submit(T cgf, const queue &secondaryQueue);

.. rubric:: Template parameters

=================  ===
``T``
=================  ===

.. rubric:: Parameters

.. list-table::

  * - ``cgf``
    - Command group function object
  * - ``secondaryQueue``
    - On error, runtime resubmits command group to the secondary
      queue.

Submit a command group function object to the queue for asynchronous
execution.

Returns an :ref:`event`, which may be used for synchronizing enqueued
tasks.

In most cases, the ``T`` template parameter is not provided because it
is inferred from the type of ``cgf``.

.. rubric:: Exceptions

The runtime resubmits the command group to the secondary queue
if an error occurs executing on the primary queue.

``wait``
========

::

  void wait();

Wait for all enqueued tasks to complete.

.. _queue-wait_and_throw:

``wait_and_throw``
==================

::

  void wait_and_throw();

Wait for all enqueued tasks and pass asynchronous errors to handler
provided in :ref:`queue-constructors`.

.. _queue-throw_asynchronous:

``throw_asynchronous``
======================

::

  void throw_asynchronous();

Passes any asynchronous errors to handler provided in
:ref:`queue-constructors`.

``single_task``
===============

::

  template <typename KernelName, typename KernelType>
  event single_task(const KernelType &kernelFunc);
  template <typename KernelName, typename KernelType>
  event single_task(event depEvent, const KernelType &kernelFunc);
  template <typename KernelName, typename KernelType>
  event single_task(const std::vector<event> &depEvents,
                    const KernelType &kernelFunc);

``parallel_for``
================

::

  // Parameter pack acts as-if: Reductions&&... reductions, const KernelType &kernelFunc
  template <typename KernelName, int Dims, typename... Rest>
  event parallel_for(range<Dims> numWorkItems,
                     Rest&&... rest);
  // Parameter pack acts as-if: Reductions&&... reductions, const KernelType &kernelFunc
  template <typename KernelName, int Dims, typename... Rest>
  event parallel_for(range<Dims> numWorkItems, event depEvent,
                     Rest&&... rest);
  // Parameter pack acts as-if: Reductions&&... reductions, const KernelType &kernelFunc
  template <typename KernelName, int Dims, typename... Rest>
  event parallel_for(range<Dims> numWorkItems,
                     const std::vector<event> &depEvents,
                     Rest&&... rest);
  // Parameter pack acts as-if: Reductions&&... reductions, const KernelType &kernelFunc
  template <typename KernelName, int Dims, typename... Rest>
  event parallel_for(nd_range<Dims> executionRange,
                     Rest&&... rest);
  // Parameter pack acts as-if: Reductions&&... reductions, const KernelType &kernelFunc
  template <typename KernelName, int Dims, typename... Rest>
  event parallel_for(nd_range<Dims> executionRange,
                     event depEvent,
                     Rest&&... rest);
  // Parameter pack acts as-if: Reductions&&... reductions, const KernelType &kernelFunc
  template <typename KernelName, int Dims, typename... Rest>
  event parallel_for(nd_range<Dims> executionRange,
                     const std::vector<event> &depEvents,
                     Rest&&... rest);

.. _queue-memcpy:

``memcpy``
==========

::

  event memcpy(void* dest, const void* src, size_t numBytes);
  event memcpy(void* dest, const void* src, size_t numBytes,
               event depEvent);
  event memcpy(void* dest, const void* src, size_t numBytes,
               const std::vector<event> &depEvents);

Set memory allocated with :ref:`malloc_device`. For usage, see
:ref:`event-elapsed-time`.

``copy``
========

::

  template <typename T>
  event copy(T* dest, const T *src, size_t count);
  template <typename T>
  event copy(T* dest, const T *src, size_t count,
             event depEvent);
  template <typename T>
  event copy(T* dest, const T *src, size_t count,
             const std::vector<event> &depEvents);

.. _queue-memset:

``memset``
==========

::

  event memset(void* ptr, int value, size_t numBytes);
  event memset(void* ptr, int value, size_t numBytes,
               event depEvent);
  event memset(void* ptr, int value, size_t numBytes,
               const std::vector<event> &depEvents);

Set memory allocated with :ref:`malloc_device`. For usage, see
:ref:`event-elapsed-time`.

.. _queue-fill:

``fill``
========

::

  template <typename T>
  event fill(void* ptr, const T& pattern, size_t count);
  template <typename T>
  event fill(void* ptr, const T& pattern, size_t count,
             event depEvent);
  template <typename T>
  event fill(void* ptr, const T& pattern, size_t count,
             const std::vector<event> &depEvents);

Set memory allocated with :ref:`malloc_device`.

``prefetch``
============

::

  event prefetch(void* ptr, size_t numBytes);
  event prefetch(void* ptr, size_t numBytes,
                 event depEvent);
  event prefetch(void* ptr, size_t numBytes,
                 const std::vector<event> &depEvents);

``mem_advise``
==============

::

  event mem_advise(void *ptr, size_t numBytes, int advice);
  event mem_advise(void *ptr, size_t numBytes, int advice,
                   event depEvent);
  event mem_advise(void *ptr, size_t numBytes, int advice,
                   const std::vector<event> &depEvents);


``copy``
========

::

  template <typename T_src, int dim_src, access_mode mode_src, target tgt_src,
            access::placeholder isPlaceholder, typename T_dest>
  event copy(accessor<T_src, dim_src, mode_src, tgt_src, isPlaceholder> src,
             std::shared_ptr<T_dest> dest);
  template <typename T_src, typename T_dest, int dim_dest,
            access_mode mode_dest, target tgt_dest,
            access::placeholder isPlaceholder>
  event
  copy(std::shared_ptr<T_src> src,
       accessor<T_dest, dim_dest, mode_dest, tgt_dest, isPlaceholder> dest);
  template <typename T_src, int dim_src, access_mode mode_src, target tgt_src,
            access::placeholder isPlaceholder, typename T_dest>
  event copy(accessor<T_src, dim_src, mode_src, tgt_src, isPlaceholder> src,
             T_dest *dest);
  template <typename T_src, typename T_dest, int dim_dest,
            access_mode mode_dest, target tgt_dest,
            access::placeholder isPlaceholder>
  event
  copy(const T_src *src,
       accessor<T_dest, dim_dest, mode_dest, tgt_dest, isPlaceholder> dest);

  template <typename T_src, int dim_src, access_mode mode_src, target tgt_src,
            access::placeholder isPlaceholder_src, typename T_dest,
            int dim_dest, access_mode mode_dest, target tgt_dest,
            access::placeholder isPlaceholder_dest>
  event copy(
      accessor<T_src, dim_src, mode_src, tgt_src, isPlaceholder_src> src,
      accessor<T_dest, dim_dest, mode_dest, tgt_dest, isPlaceholder_dest> dest);

``update_host``
===============

::

  template <typename T, int dim, access_mode mode, target tgt,
            access::placeholder isPlaceholder>
  event update_host(accessor<T, dim, mode, tgt, isPlaceholder> acc);


=====================
``sycl::info::queue``
=====================

::

  enum class queue : int {
    context,
    device,
    reference_count,
  };

Used as a template parameter for get_info_ to determine the type of
information.

.. list-table::
   :header-rows: 1

   * - Descriptor
     - Return type
     - Description
   * - ``context``
     - ``context``
     - SYCL context associated with the queue
   * - ``device``
     - ``device``
     - SYCL device associated with the queue
   * - ``reference_count``
     - ``cl_uint``
     - Reference count of the queue


.. _queue-properties:

================
Queue properties
================

Queue properties are specified in the queue constructor.

.. rst-class:: api-class

``sycl::property::queue::enable_profiling``
===========================================

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

``sycl::property::queue::in_order``
===================================

|2020|

::

   class in_order;

SYCL queue provides in-order semantics.

(constructors)
--------------

::

   in_order();

Constructs an in_order property instance.
