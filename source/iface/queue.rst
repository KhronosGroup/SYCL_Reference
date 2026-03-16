..
  Copyright 2024 The Khronos Group Inc.
  SPDX-License-Identifier: CC-BY-4.0

.. _queues:

******
Queues
******

.. _queue:

===============
``sycl::queue``
===============

::

  class queue;

The ``sycl::queue`` connect a host program to a single device.
Programs submit tasks to a device via the ``sycl::queue`` and may
monitor the ``sycl::queue`` for completion. A program initiates the
task by submitting a command group to a ``sycl::queue``. The command
group defines a kernel function, the prerequisites to execute the
kernel function, and an invocation of the kernel function on an
index space. After submitting the command group, a program may
use the ``sycl::queue`` to monitor the completion of the task for
completion and errors. A ``sycl::queue`` can wait for all command
groups that it has submitted by calling ``wait`` or ``wait_and_throw``.

.. seealso:: |SYCL_SPEC_QUEUE|

.. _queue-constructors:

(constructors)
==============

::

  explicit queue(const sycl::property_list& propList = {});

  explicit queue(const sycl::async_handler& asyncHandler,
                 const sycl::property_list& propList = {});

  template <typename DeviceSelector>
  explicit queue(const DeviceSelector& deviceSelector,
                 const sycl::property_list& propList = {});

  template <typename DeviceSelector>
  explicit queue(const DeviceSelector& deviceSelector,
                 const sycl::async_handler& asyncHandler,
                 const sycl::property_list& propList = {});

  explicit queue(const sycl::device& syclDevice,
                 const sycl::property_list& propList = {});

  explicit queue(const sycl::device& syclDevice,
                 const sycl::async_handler& asyncHandler,
                 const sycl::property_list& propList = {});

  template <typename DeviceSelector>
  explicit queue(const sycl::context& syclContext,
                 const DeviceSelector& deviceSelector,
                 const sycl::property_list& propList = {});

  template <typename DeviceSelector>
  explicit queue(const sycl::context& syclContext,
                 const DeviceSelector& deviceSelector,
                 const sycl::async_handler& asyncHandler,
                 const sycl::property_list& propList = {});

  explicit queue(const sycl::context& syclContext,
                 const sycl::device& syclDevice,
                 const sycl::property_list& propList = {});

  explicit queue(const sycl::context& syclContext,
                 const sycl::device& syclDevice,
                 const sycl::async_handler& asyncHandler,
                 const sycl::property_list& propList = {});

Construct a ``sycl::queue``.

The default constructor of the ``sycl::queue`` class will construct
a queue based on the ``sycl::device`` returned from the
``sycl::default_selector_v`` (see |SYCL_SPEC_DEVICE_SELECTORS|).
All other constructors construct a queue as determined by the
parameters provided. All constructors will implicitly construct a
``sycl::platform``, ``sycl::device`` and ``sycl::context`` in order
to facilitate the construction of the queue.
Each constructor takes as the last parameter an optional
``sycl::property_list`` to provide properties to the ``sycl::queue``.

The SYCL runtime may execute tasks asynchronously. To catch exceptions
from asynchronous host tasks, construct the queue with an
``asyncHandler`` and call ``sycl::queue::wait_and_throw()``,
``sycl::queue::throw_asynchronous()`` or ``sycl::event::wait_and_throw()``.

.. rubric:: Parameters

.. list-table::

   * - ``propList``
     - See `queue-properties`_.
   * - ``asyncHandler``
     - Called for asynchronous exceptions,
       see :ref:`iface-async-error-handler`.
   * - ``deviceSelector``
     - Selects device for queue.
   * - ``syclDevice``
     - Device for queue.
   * - ``syclContext``
     - Associate queue with the context.

.. rubric:: Exceptions

``sycl::errc::invalid``
  If ``syclContext`` does not encapsulate the ``sycl::device`` returned
  by ``deviceSelector``.


===============
Member function
===============

``get_backend``
===============

::

  sycl::backend get_backend() const noexcept;

Returns a backend identifying the ``sycl::backend``
associated with this ``sycl::queue``.

``get_context``
===============

::

  sycl::context get_context() const;

Returns the SYCL queue’s context. The value returned must
be equal to that returned by ``get_info<sycl::info::queue::context>()``.

``get_device``
==============

::

  sycl::device get_device() const;

Returns the ``sycl::device`` the queue is associated with.
The value returned must be equal to that returned by
``get_info<sycl::info::queue::device>()``.

``is_in_order``
===============

::

  bool is_in_order() const;

Returns true if the ``sycl::queue`` was created with the ``in_order`` property.
Equivalent to ``has_property<sycl::property::queue::in_order>()``.

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
asynchronous errors will be passed to the ``sycl::async_handler``
associated with the queue or enclosing context. If no user defined
``sycl::async_handler`` is associated with the queue or enclosing context,
then an implementation-defined default ``sycl::async_handler`` is called to
handle any errors, as described in |SYCL_SPEC_WITHOUT_ASYC_HANDLER|.

.. _queue-throw_asynchronous:

``throw_asynchronous``
======================

::

  void throw_asynchronous();

Checks to see if any unconsumed asynchronous errors have been produced
by the queue and if so reports them by passing them to the
``sycl::async_handler`` associated with the queue or enclosing context.
If no user defined ``sycl::async_handler`` is associated with the queue
or enclosing context, then an implementation-defined default
``sycl::async_handler`` is called to handle any errors, as described in
|SYCL_SPEC_WITHOUT_ASYC_HANDLER|.

``get_info``
============

::

  template <typename Param>
  typename Param::return_type get_info() const;

Queries this ``sycl::queue`` for information requested by the template
parameter ``Param``. The type alias ``Param::return_type`` must be defined
in accordance with the info parameters in `sycl::info::queue`_
to facilitate returning the type associated with the ``Param`` parameter.

.. _queue-submit:

``submit``
==========

::

  template <typename T>
  sycl::event submit(T cgf);

  template <typename T>
  sycl::event submit(T cgf, sycl::queue& secondaryQueue);

Submit a command group function object to the queue, in order to be scheduled
for execution on the device. In the context of the second overload,
if a kernel error occurs, this command group function object is then
scheduled for execution on the secondary queue. Returns an event,
which corresponds to the queue the command group function object
is being enqueued on.

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

``get_backend_info``
====================

::

  template <typename Param>
  typename Param::return_type get_backend_info() const;

Queries this ``sycl::queue`` for SYCL backend-specific information requested
by the template parameter ``Param``. The type alias ``Param::return_type``
must defined in accordance with the SYCL backend specification. Must throw
an ``sycl::exception`` with the ``sycl::errc::backend_mismatch`` error code
if the SYCL backend that corresponds with ``Param`` is different from the
SYCL backend that is associated with this ``sycl::queue``.

.. _queue_shortcut:

==================
Shortcut functions
==================

Queue shortcut functions are part of the ``sycl::queue`` class and simplify
command group creation. They generate a command group with a single command,
invoke a corresponding member function in the handler, and submit the group.
The key distinction is that handler member functions return void,
while queue shortcuts return an event object representing the submitted
command group. You can specify a list of events to wait on, just like
using ``sycl::handler::depends_on`` for the implicit command group.

``single_task``
===============

::

  template <typename KernelName, typename KernelType>
  sycl::event single_task(const KernelType& kernelFunc);

  template <typename KernelName, typename KernelType>
  sycl::event single_task(sycl::event depEvent,
                          const KernelType& kernelFunc);

  template <typename KernelName, typename KernelType>
  esycl::vent single_task(const std::vector<sycl::event>& depEvents,
                          const KernelType& kernelFunc);

.. rubric:: Example

See `queue-example-1`_.

``parallel_for``
================

::

  template <typename KernelName, int Dimensions, typename... Rest>
  sycl::event parallel_for(sycl::range<Dimensions> numWorkItems, Rest&&... rest);

  template <typename KernelName, int Dimensions, typename... Rest>
  sycl::event parallel_for(sycl::range<Dimensions> numWorkItems,
                           sycl::event depEvent, Rest&&... rest);

  template <typename KernelName, int Dimensions, typename... Rest>
  sycl::event parallel_for(sycl::range<Dimensions> numWorkItems,
                           const std::vector<sycl::event>& depEvents, Rest&&... rest);

  template <typename KernelName, int Dimensions, typename... Rest>
  sycl::event parallel_for(sycl::nd_range<Dimensions> executionRange, Rest&&... rest);

  template <typename KernelName, int Dimensions, typename... Rest>
  sycl::event parallel_for(sycl::nd_range<Dimensions> executionRange,
                           sycl::event depEvent, Rest&&... rest);

  template <typename KernelName, int Dimensions, typename... Rest>
  sycl::event parallel_for(sycl::nd_range<Dimensions> executionRange,
                           const std::vector<sycl::event>& depEvents, Rest&&... rest);

.. rubric:: Example

See `queue-example-2`_.

.. _queue-memcpy:

``memcpy``
==========

::

  sycl::event memcpy(void* dest, const void* src, size_t numBytes);

  sycl::event memcpy(void* dest, const void* src, size_t numBytes,
                     sycl::event depEvent);

  sycl::event memcpy(void* dest, const void* src, size_t numBytes,
                     const std::vector<sycl::event>& depEvents);

Set memory allocated with :ref:`usm_allocations`.

.. rubric:: Example

See :ref:`event-elapsed-time-example<event-elapsed-time>`.

``copy``
========

::

  template <typename T>
  sycl::event copy(const T* src, T* dest, size_t count);

  template <typename T>
  sycl::event copy(const T* src, T* dest, size_t count,
                   sycl::event depEvent);

  template <typename T>
  sycl::event copy(const T* srct, T* dest, size_t count,
                   const std::vector<sycl::event>& depEvents);

.. _queue-memset:

``memset``
==========

::

  sycl::event memset(void* ptr, int value, size_t numBytes);

  sycl::event memset(void* ptr, int value, size_t numBytes,
                     sycl::event depEvent);

  sycl::event memset(void* ptr, int value, size_t numBytes,
                     const std::vector<sycl::event>& depEvents);

Set memory allocated with :ref:`usm_allocations`. For usage, see
:ref:`event-elapsed-time`.

.. _queue-fill:

``fill``
========

::

  template <typename T>
  sycl::event fill(void* ptr, const T& pattern, size_t count);

  template <typename T>
  sycl::event fill(void* ptr, const T& pattern, size_t count,
                   sycl::event depEvent);

  template <typename T>
  sycl::event fill(void* ptr, const T& pattern, size_t count,
                   const std::vector<sycl::event>& depEvents);

Set memory allocated with :ref:`usm_allocations`.

``prefetch``
============

::

  sycl::event prefetch(void* ptr, size_t numBytes);

  sycl::event prefetch(void* ptr, size_t numBytes,
                       sycl::event depEvent);

  sycl::event prefetch(void* ptr, size_t numBytes,
                       const std::vector<sycl::event>& depEvents);

``mem_advise``
==============

::

  sycl::event mem_advise(void* ptr, size_t numBytes, int advice);

  sycl::event mem_advise(void* ptr, size_t numBytes, int advice,
                         sycl::event depEvent);

  sycl::event mem_advise(void* ptr, size_t numBytes, int advice,
                         const std::vector<sycl::event>& depEvents);


``copy``
========

::

  template <typename SrcT, int SrcDims, sycl::access_mode SrcMode, sycl::target SrcTgt,
            sycl::access::placeholder IsPlaceholder, typename DestT>
  sycl::event copy(sycl::accessor<SrcT, SrcDims, SrcMode, SrcTgt, IsPlaceholder> src,
                   std::shared_ptr<DestT> dest);

  template <typename SrcT, typename DestT, int DestDims, sycl::access_mode DestMode,
            sycl::target DestTgt, sycl::access::placeholder IsPlaceholder>
  sycl::event copy(std::shared_ptr<SrcT> src,
                   sycl::accessor<DestT, DestDims, DestMode, DestTgt, IsPlaceholder> dest);

  template <typename SrcT, int SrcDims, sycl::access_mode SrcMode, sycl::target SrcTgt,
            sycl::access::placeholder IsPlaceholder, typename DestT>
  sycl::event copy(sycl::accessor<SrcT, SrcDims, SrcMode, SrcTgt, IsPlaceholder> src,
                   DestT* dest);

  template <typename SrcT, typename DestT, int DestDims, sycl::access_mode DestMode,
            sycl::target DestTgt, sycl::access::placeholder IsPlaceholder>
  sycl::event copy(const SrcT* src,
                   sycl::accessor<DestT, DestDims, DestMode, DestTgt, IsPlaceholder> dest);

  template <typename SrcT, int SrcDims, sycl::access_mode SrcMode, sycl::target SrcTgt,
            sycl::access::placeholder IsSrcPlaceholder, typename DestT, int DestDims,
            sycl::access_mode DestMode, sycl::target DestTgt,
            sycl::access::placeholder IsDestPlaceholder>
  sycl::event copy(sycl::accessor<SrcT, SrcDims, SrcMode, SrcTgt, IsSrcPlaceholder> src,
                   sycl::accessor<DestT, DestDims, DestMode, DestTgt, IsDestPlaceholder> dest);

``update_host``
===============

::

  template <typename T, int Dims, sycl::access_mode Mode, sycl::target Tgt,
            sycl::access::placeholder IsPlaceholder>
  sycl::event update_host(sycl::accessor<T, Dims, Mode, Tgt, IsPlaceholder> acc);

``fill``
===============

::

  template <typename T, int Dims, sycl::access_mode Mode, sycl::target Tgt,
            sycl::access::placeholder IsPlaceholder>
  sycl::event fill(sycl::accessor<T, Dims, Mode, Tgt, IsPlaceholder> dest, const T& src);


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
   * - ``sycl::info::queue::context``
     - ``sycl::context``
     - Returns the ``sycl::context`` associated with this ``sycl::queue``.
   * - ``sycl::info::queue::device``
     - ``sycl::device``
     - Returns the ``sycl::device`` associated with this ``sycl::queue``.

.. _queue-properties:

================
Queue properties
================

The properties that can be provided when constructing the ``sycl::queue``
class are describe in |SYCL_SPEC_QUEUE_PROPERTIES|.

.. rst-class:: api-class

``sycl::property::queue::enable_profiling``
===========================================


The ``enable_profiling`` property adds the requirement that the SYCL runtime
must capture profiling information for the command groups that are submitted
from this ``sycl::queue`` and provide said information via the ``sycl::event``
class ``get_profiling_info`` member function. If the queue's associated device
does not have ``sycl::aspect::queue_profiling``, passing this
property to the queue's constructor causes the constructor to throw
a synchronous ``sycl::exception`` with the
``sycl::errc::feature_not_supported`` error code.

(constructors)
--------------

::

   enable_profiling();

Constructs a SYCL ``enable_profiling`` property instance.

.. rubric:: Example

See :ref:`event-elapsed-time-example<event-elapsed-time>`.

.. rst-class:: api-class

``sycl::property::queue::in_order``
===================================


The ``in_order`` property adds the requirement that a ``sycl::queue`` provides
in-order semantics whereby commands submitted to said ``sycl::queue`` are
executed in the order in which they are submitted.
Commands submitted in this fashion can be viewed as-if having an implicit
dependence on the previous command submitted to that ``sycl::queue``.
Using the ``in_order`` property makes no guarantees about the ordering
of commands submitted to different queues with respect to each other.

(constructors)
--------------

::

   in_order();

Constructs a SYCL ``in_order`` property instance.

.. _queue-example-1:

====================
Queue error handling
====================

Queue errors come in two forms:

``Synchronous Errors`` are those that we would expect to be reported directly
at the point of waiting on an event, and hence waiting for a
``sycl::queue`` to complete, as well as any immediate errors reported
by enqueuing work onto a ``sycl::queue``. Such errors are reported
through C++ exceptions.

``Asynchronous errors`` are those that are produced or detected after
associated host API calls have returned (so can’t be thrown
as exceptions by the API call), and that are handled by an
``sycl::async_handler`` through which the errors are reported. Handling
of asynchronous errors from a ``sycl::queue`` occurs at specific times,
as described by |SYCL_SPEC_ERROR_HANDLING|.


=========
Example 1
=========

Submission of a single task SYCL kernel function.

.. literalinclude:: /examples/queue-single-task.cpp
   :lines: 5-
   :linenos:

Output:

.. literalinclude:: /examples/queue-single-task.out
   :language: none
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
   :language: none
   :lines: 5-
