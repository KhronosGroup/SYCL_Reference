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

Queues connect a host program to a single device. Programs ``submit``
tasks to a device via the ``queue`` and may monitor the ``queue`` for
completion. A program initiates the task by submitting a command group
to a ``queue``. The command group defines a kernel function, the
prerequisites to execute the kernel function, and an invocation of the
kernel function on an index space. After submitting the command group,
a program may use the ``queue`` to monitor the completion of the task for
completion and errors. A SYCL queue can wait for all command groups that
it has submitted by calling ``wait`` or ``wait_and_throw``.


.. seealso:: |SYCL_SPEC_QUEUE|

.. _queue-constructors:

(constructors)
==============

::

  explicit queue(const property_list& propList = {});

  explicit queue(const async_handler& asyncHandler,
               const property_list& propList = {});

  template <typename DeviceSelector>
  explicit queue(const DeviceSelector& deviceSelector,
               const property_list& propList = {});

  template <typename DeviceSelector>
  explicit queue(const DeviceSelector& deviceSelector,
               const async_handler& asyncHandler,
               const property_list& propList = {});

  explicit queue(const device& syclDevice, const property_list& propList = {});

  explicit queue(const device& syclDevice, const async_handler& asyncHandler,
               const property_list& propList = {});

  template <typename DeviceSelector>
  explicit queue(const context& syclContext, const DeviceSelector& deviceSelector,
               const property_list& propList = {});

  template <typename DeviceSelector>
  explicit queue(const context& syclContext, const DeviceSelector& deviceSelector,
               const async_handler& asyncHandler,
               const property_list& propList = {});

  explicit queue(const context& syclContext, const device& syclDevice,
               const property_list& propList = {});

  explicit queue(const context& syclContext, const device& syclDevice,
               const async_handler& asyncHandler,
               const property_list& propList = {});

Construct a queue.

The default constructor of the SYCL queue class will construct
a queue based on the SYCL device returned from the :ref:`device_selector`.
All other constructors construct a queue as determined by the parameters
provided. All constructors will implicitly construct a SYCL :ref:`platform`,
:ref:`device` and :ref:`context` in order to facilitate the construction
of the queue. Each constructor takes as the last parameter an optional SYCL
``property_list`` to provide properties to the SYCL ``queue``.
Each constructor takes as the last parameter an optional SYCL ``property_list``
to provide properties to the SYCL ``queue``.

The SYCL runtime may execute tasks asynchronously. To catch exceptions
from asynchronous host tasks, construct the queue with an
``asyncHandler`` and call wait_ or wait_and_throw_.

.. rubric:: Parameters

.. list-table::

   * - ``propList``
     - See `queue-properties`_.
   * - ``asyncHandler``
     - Called for asynchronous exceptions, see :ref:`async_handler`.
   * - ``deviceSelector``
     - Selects device for queue.
   * - ``syclDevice``
     - Device for queue.
   * - ``syclContext``
     - Associate queue with the context.
   * - ``clQueue``
     - Associate queue with OpenCL|trade| queue.

.. rubric:: Exceptions

``errc::invalid``
  If ``syclContext`` does not encapsulate the SYCL ``device`` returned
  by ``deviceSelector``.


===============
Member function
===============

``get_backend``
===============

::

  backend get_backend() const noexcept;

Returns a backend identifying the SYCL ``backend``
associated with this ``queue``.

``get_context``
===============

::

  context get_context() const;

Returns the SYCL queue’s context. Reports errors using SYCL exception classes.
The value returned must be equal to that returned by
``get_info<info::queue::context>()``.

``get_device``
==============

::

  device get_device() const;

Returns the SYCL device the queue is associated with. Reports errors using
SYCL exception classes. The value returned must be equal to that returned
by ``get_info<info::queue::device>()``.

``is_in_order``
===============

::

  bool is_in_order() const;

Returns true if the SYCL ``queue`` was created with the ``in_order`` property.
Equivalent to ``has_property<property::queue::in_order>()``.

``wait``
========

::

  void wait();

Performs a blocking wait for the completion of all enqueued tasks in the queue.
Synchronous errors will be reported through SYCL exceptions.

.. _queue-wait_and_throw:

``wait_and_throw``
==================

::

  void wait_and_throw();

Performs a blocking wait for the completion of all enqueued tasks in the queue.
Synchronous errors will be reported through SYCL exceptions. Any unconsumed
asynchronous errors will be passed to the ``async_handler``
associated with the queue or enclosing context. If no user defined
``async_handler`` is associated with the queue or enclosing context,
then an implementation-defined default ``async_handler`` is called to
handle any errors, as described in |SYCL_SPEC_WITHOUT_ASYC_HANDLER|.

.. _queue-throw_asynchronous:

``throw_asynchronous``
======================

::

  void throw_asynchronous();

Checks to see if any unconsumed asynchronous errors have been produced
by the queue and if so reports them by passing them to the ``async_handler``
associated with the queue or enclosing context. If no user defined
``async_handler`` is associated with the queue or enclosing context, then
an implementation-defined default ``async_handler`` is called to handle any
errors, as described in |SYCL_SPEC_WITHOUT_ASYC_HANDLER|.

``get_info``
============

::

  template <typename Param> typename Param::return_type get_info() const;

Queries this SYCL ``queue`` for information requested by the template
parameter ``Param``. The type alias ``Param::return_type`` must be defined
in accordance with the info parameters in |SYCL_SPEC_QUEUE_INFO_DESC|
to facilitate returning the type associated with the ``Param`` parameter.

.. _queue-submit:

``submit``
==========

::

  template <typename T>
  event submit(T cgf);
  template <typename T>
  event submit(T cgf, const queue &secondaryQueue);

Submit a command group function object to the queue, in order to be scheduled
for execution on the device. On a kernel error, this command group function
object is then scheduled for execution on the secondary queue. Returns
an event, which corresponds to the queue the command group function object
is being enqueued on.

``get_backend_info``
====================

::

  template <typename Param>
  typename Param::return_type get_backend_info() const;

Queries this SYCL ``queue`` for SYCL backend-specific information requested by
the template parameter ``Param``. The type alias ``Param::return_type``
must defined in accordance with the SYCL backend specification. Must throw
an ``exception``with the ``errc::backend_mismatch`` error code if the SYCL
backend that corresponds with ``Param`` is different from the SYCL backend
that is associated with this ``queue``.

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

.. rubric:: Example

See `queue-example-1`_.


==================
Shortcut functions
==================

The full list of queue shortcuts is
defined in |SYCL_SPEC_QUEUE_SHOURTCUT_FUNC|.

``single_task``
===============

::

  template <typename KernelName, typename KernelType>
  event single_task(const KernelType& kernelFunc);

  template <typename KernelName, typename KernelType>
  event single_task(event depEvent, const KernelType& kernelFunc);

  template <typename KernelName, typename KernelType>
  event single_task(const std::vector<event>& depEvents,
                  const KernelType& kernelFunc);

.. rubric:: Example

See `queue-example-1`_.

``parallel_for``
================

::

  template <typename KernelName, int Dimensions, typename... Rest>
  event parallel_for(range<Dimensions> numWorkItems, Rest&&... rest);

  template <typename KernelName, int Dimensions, typename... Rest>
  event parallel_for(range<Dimensions> numWorkItems, event depEvent,
                   Rest&&... rest);

  template <typename KernelName, int Dimensions, typename... Rest>
  event parallel_for(range<Dimensions> numWorkItems,
                   const std::vector<event>& depEvents, Rest&&... rest);

  template <typename KernelName, int Dimensions, typename... Rest>
  event parallel_for(nd_range<Dimensions> executionRange, Rest&&... rest);

  template <typename KernelName, int Dimensions, typename... Rest>
  event parallel_for(nd_range<Dimensions> executionRange, event depEvent,
                   Rest&&... rest);

  template <typename KernelName, int Dimensions, typename... Rest>
  event parallel_for(nd_range<Dimensions> executionRange,
                   const std::vector<event>& depEvents, Rest&&... rest);

.. rubric:: Example

See `queue-example-2`_.

.. _queue-memcpy:

``memcpy``
==========

::

  event memcpy(void* dest, const void* src, size_t numBytes);

  event memcpy(void* dest, const void* src, size_t numBytes, event depEvent);

  event memcpy(void* dest, const void* src, size_t numBytes,
             const std::vector<event>& depEvents);

Set memory allocated with :ref:`malloc_device`.

.. rubric:: Example

See :ref:`event-elapsed-time-example<event-elapsed-time>`.

``copy``
========

::

  template <typename T> event copy(const T* src, T* dest, size_t count);

  template <typename T>
  event copy(const T* src, T* dest, size_t count, event depEvent);

  template <typename T>
  event copy(const T* srct, T* dest, size_t count,
           const std::vector<event>& depEvents);

.. _queue-memset:

``memset``
==========

::

  event memset(void* ptr, int value, size_t numBytes);

  event memset(void* ptr, int value, size_t numBytes, event depEvent);

  event memset(void* ptr, int value, size_t numBytes,
             const std::vector<event>& depEvents);

Set memory allocated with :ref:`malloc_device`. For usage, see
:ref:`event-elapsed-time`.

.. _queue-fill:

``fill``
========

::

  template <typename T> event fill(void* ptr, const T& pattern, size_t count);

  template <typename T>
  event fill(void* ptr, const T& pattern, size_t count, event depEvent);

  template <typename T>
  event fill(void* ptr, const T& pattern, size_t count,
           const std::vector<event>& depEvents);

Set memory allocated with :ref:`malloc_device`.

``prefetch``
============

::

  event prefetch(void* ptr, size_t numBytes);

  event prefetch(void* ptr, size_t numBytes, event depEvent);

  event prefetch(void* ptr, size_t numBytes, const std::vector<event>& depEvents);

``mem_advise``
==============

::

  event mem_advise(void* ptr, size_t numBytes, int advice);

  event mem_advise(void* ptr, size_t numBytes, int advice, event depEvent);

  event mem_advise(void* ptr, size_t numBytes, int advice,
                 const std::vector<event>& depEvents);


``copy``
========

::

  template <typename SrcT, int SrcDims, access_mode SrcMode, target SrcTgt,
          access::placeholder IsPlaceholder, typename DestT>
  event copy(accessor<SrcT, SrcDims, SrcMode, SrcTgt, IsPlaceholder> src,
           std::shared_ptr<DestT> dest);

  template <typename SrcT, typename DestT, int DestDims, access_mode DestMode,
          target DestTgt, access::placeholder IsPlaceholder>
  event copy(std::shared_ptr<SrcT> src,
           accessor<DestT, DestDims, DestMode, DestTgt, IsPlaceholder> dest);

  template <typename SrcT, int SrcDims, access_mode SrcMode, target SrcTgt,
          access::placeholder IsPlaceholder, typename DestT>
  event copy(accessor<SrcT, SrcDims, SrcMode, SrcTgt, IsPlaceholder> src,
           DestT* dest);

  template <typename SrcT, typename DestT, int DestDims, access_mode DestMode,
          target DestTgt, access::placeholder IsPlaceholder>
  event copy(const SrcT* src,
           accessor<DestT, DestDims, DestMode, DestTgt, IsPlaceholder> dest);

  template <typename SrcT, int SrcDims, access_mode SrcMode, target SrcTgt,
          access::placeholder IsSrcPlaceholder, typename DestT, int DestDims,
          access_mode DestMode, target DestTgt,
          access::placeholder IsDestPlaceholder>
  event copy(
    accessor<SrcT, SrcDims, SrcMode, SrcTgt, IsSrcPlaceholder> src,
    accessor<DestT, DestDims, DestMode, DestTgt, IsDestPlaceholder> dest);

``update_host``
===============

::

  template <typename T, int Dims, access_mode Mode, target Tgt,
          access::placeholder IsPlaceholder>
  event update_host(accessor<T, Dims, Mode, Tgt, IsPlaceholder> acc);

``fill``
===============

::

  template <typename T, int Dims, access_mode Mode, target Tgt,
          access::placeholder IsPlaceholder>
  event fill(accessor<T, Dims, Mode, Tgt, IsPlaceholder> dest, const T& src);


=======================
Information descriptors
=======================

=====================
``sycl::info::queue``
=====================

::

  namespace sycl::info::queue {

  struct context;
  struct device;

  } // namespace sycl::info::queue

Used as a template parameter for get_info_ to determine the type of
information.

.. list-table::
   :header-rows: 1

   * - Descriptor
     - Return type
     - Description
   * - ``context``
     - ``context``
     - Returns the SYCL ``context`` associated with this SYCL ``queue``.
   * - ``device``
     - ``device``
     - Returns the SYCL ``device`` associated with this SYCL ``queue``.

.. _queue-properties:

================
Queue properties
================

Queue properties are specified in the queue constructor.

.. rst-class:: api-class

``sycl::property::queue::enable_profiling``
===========================================

The ``enable_profiling`` property adds the requirement that the SYCL runtime
must capture profiling information for the command groups that are submitted
from this SYCL ``queue`` and provide said information via the SYCL ``event``
class ``get_profiling_info`` member function. If the queue’s associated device
does not have ``aspect::queue_profiling``, passing this
property to the queue’s constructor causes the constructor to throw
a synchronous ``exception`` with the ``errc::feature_not_supported``
error code.

(constructors)
--------------

::

   enable_profiling();

Constructs a SYCL enable_profiling property instance.

.. rubric:: Example

See :ref:`event-elapsed-time-example<event-elapsed-time>`.

.. rst-class:: api-class

``sycl::property::queue::in_order``
===================================

The ``in_order`` property adds the requirement that a SYCL ``queue`` provides
in-order semantics whereby commands submitted to said ``queue`` are executed
in the order in which they are submitted.
Commands submitted in this fashion can be viewed as-if having an implicit
dependence on the previous command submitted to that ``queue``.
Using the ``in_order`` property makes no guarantees about the ordering
of commands submitted to different queues with respect to each other.

(constructors)
--------------

::

   in_order();

Constructs a SYCL in_order property instance.

.. _queue-example-1:

====================
Queue error handling
====================

Queue errors come in two forms:

``Synchronous Errors`` are those that we would expect to be reported directly
at the point of waiting on an event, and hence waiting for a
``queue`` to complete, as well as any immediate errors reported
by enqueuing work onto a ``queue``. Such errors are reported
through C++ exceptions.

``Asynchronous errors`` are those that are produced or detected after
associated host API calls have returned (so can’t be thrown
as exceptions by the API call), and that are handled by an
``async_handler`` through which the errors are reported. Handling
of asynchronous errors from a ``queue`` occurs at specific times, as described
by |SYCL_SPEC_ERROR_HANDLING|.


=========
Example 1
=========

Submission of a single task SYCL kernel function.

.. literalinclude:: /examples/queue-single-task.cpp
   :lines: 5-
   :linenos:

Output:

.. literalinclude:: /examples/queue-single-task.out
   :lines: 5-

.. _queue-example-2:

=========
Example 2
=========

Submission of a parallel SYCL kernel function.

.. literalinclude:: /examples/queue-parallel.cpp
   :lines: 5-
   :linenos:

Output:

.. literalinclude:: /examples/queue-parallel.out
   :lines: 5-
