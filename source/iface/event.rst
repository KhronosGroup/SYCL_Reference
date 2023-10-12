..
  Copyright 2020 The Khronos Group Inc.
  SPDX-License-Identifier: CC-BY-4.0

******
Events
******


.. _event:

.. rst-class:: api-class

===============
``sycl::event``
===============

::

  class event;

An event in SYCL is an object that represents the
status of an operation that is being executed by
the SYCL runtime.

Although an event represents the status of a particular
operation, the dependencies of a certain event can be
used to keep track of multiple steps required to
synchronize said operation.

A SYCL event is returned by the submission of a command group.
The dependencies of the event returned via the submission of
the command group are the implementation-defined commands
associated with the command group execution.

The SYCL event class provides the
:ref:`common reference semantics <common-reference>`.

.. seealso:: |SYCL_SPEC_EVENT|

(constructors)
==============

::

  event();

Constructs an event that is immediately ready.

The event has no dependencies and no associated commands.

Waiting on this event will return immediately and querying
its status will return ``sycl::info::event_command_status::complete``.

The event is constructed as though it was created
from a default-constructed queue.
Therefore, its backend is the same as the backend from the default device.


================
Member functions
================

``get_backend``
===============

::

  backend get_backend() const noexcept;

Returns a backend identifying the SYCL backend associated with this event.

``get_wait_list``
=================

::

  std::vector<sycl::event> get_wait_list();

Return the list of events that this event waits for in the dependence graph.

Only direct dependencies are returned, and not transitive dependencies that
direct dependencies wait on. Whether already completed events are included
in the returned list is implementation-defined.

``wait``
========

::

  void wait();

Wait for the event and the command associated with it to complete.

``wait_and_throw``
==================

::

  void wait_and_throw();

Wait for the event and the command associated with it to complete.

Any unconsumed asynchronous errors from any context that the event
was waiting on executions from will be passed to the ``async_handler``
associated with the context. If no user defined ``async_handler`` is
associated with the context, then an implementation-defined default
``async_handler`` is called to handle any errors.

=======================
Static member functions
=======================

``wait``
========

::

  static void wait(const std::vector<event>& eventList);

Synchronously wait on a list of events.

``wait_and_throw``
==================

::

  static void wait_and_throw(const std::vector<event>& eventList);

Synchronously wait on a list of events.

Any unconsumed asynchronous errors from any context that the event
was waiting on executions from will be passed to the ``async_handler``
associated with the context. If no user defined ``async_handler`` is
associated with the context, then an implementation-defined default
``async_handler`` is called to handle any errors.

``get_info``
============

::

  template <typename Param>
  typename Param::return_type get_info() const;


Queries this SYCL event for information requested by the template
parameter ``Param``.

The type alias ``Param::return_type`` must be defined in accordance
with the :ref:`information parameters <event_descriptors>` to
facilitate returning the type associated with the ``Param`` parameter.

``get_backend_info``
====================

::

  template <typename Param>
  typename Param::return_type get_backend_info() const;

Queries this SYCL event for SYCL backend-specific information requested
by the template parameter ``Param``.

The type alias ``Param::return_type`` must be defined in accordance
with the SYCL backend specification.

.. rubric:: Exceptions

``errc::backend_mismatch``
  If the SYCL backend that corresponds with ``Param`` is different from
  the SYCL backend that is associated with this event.

``get_profiling_info``
======================

::

  template <typename Param>
  typename Param::return_type get_profiling_info() const;

Queries this SYCL event for profiling information requested by the
parameter ``Param``.

If the requested profiling information is unavailable when
``get_profiling_info`` is called due to incompletion of
command groups associated with the event, then the call
to ``get_profiling_info`` will block until the requested
profiling information is available.

An example is asking for ``sycl::info::event_profiling::command_end``
when the associated command group action has yet to finish execution.

The type alias ``Param::return_type`` must be defined in accordance
with the :ref:`information profiling parameters <event_profiling_descriptors>`
to facilitate returning the type associated with the ``Param`` parameter.

.. rubric:: Exceptions

``errc::invalid``
  if the SYCL queue which submitted the command group this SYCL event
  is associated with was not constructed with the
  ``sycl::property::queue::enable_profiling`` property.

.. rubric:: Example

See `event-elapsed-time`_.

=====================================
Information and profiling descriptors
=====================================

.. _event_descriptors:

``sycl::info::event``
=====================

::

  namespace sycl::info::event {

  struct command_execution_status;

  } // namespace sycl::info::event

Used as a template parameter for get_info_ to determine the type of
information.

.. rubric:: ``sycl::info::event::command_execution_status``

Returns the event status of the command group and contained
action (e.g. kernel invocation) associated with this SYCL event.

+---------------------------------------------------------+
| Return type: `sycl::info::event_command_status`_        |
+---------------------------------------------------------+

Return types
============

``sycl::info::event_command_status``
------------------------------------

::

  namespace sycl::info {

  enum class event_command_status : /* unspecified */ {
    submitted,
    running,
    complete
  };

  } // namespace sycl::info

.. list-table::

  * - ``sycl::info::event_command_status::submitted``
    - Indicates that the command has been submitted to the SYCL
      queue but has not yet started running on the device.
  * - ``sycl::info::event_command_status::running``
    - Indicates that the command has started running on the device
      but has not yet completed.
  * - ``sycl::info::event_command_status::complete``
    - Indicates that the command has finished running on the device.
      Attempting to wait on such an event will not block.

.. _event_profiling_descriptors:

``sycl::info::event_profiling``
===============================

::

  namespace sycl::info::event_profiling  {

  struct command_submit;
  struct command_start;
  struct command_end;

  } // namespace sycl::info::event_profiling

Used as a template parameter for get_profiling_info_ to determine the
type of information.

Each profiling descriptor returns a 64-bit timestamp
that represents the number of nanoseconds that have
elapsed since some implementation-defined timebase.

All events that share the same backend are guaranteed
to share the same timebase, therefore the difference
between two timestamps from the same backend yields
the number of nanoseconds that have elapsed between
those events.

.. rubric:: ``sycl::info::event_profiling::command_submit``

Returns a timestamp telling when the associated command group
was submitted to the :ref:`queue`.

This is always some time after the command group function
object returns and before the associated call
to ``sycl::queue::submit`` returns.

+----------------------------------+
| Return type: ``uint64_t``        |
+----------------------------------+


.. rubric:: ``sycl::info::event_profiling::command_start``

Querying this profiling descriptor blocks until the event's state
becomes either ``sycl::info::event_command_status::running``
or ``sycl::info::event_command_status::complete``.

The returned timestamp tells when the action associated with the
command group (e.g. kernel invocation) started executing on the device.

For any given event, this timestamp is always greater than or equal to
the ``sycl::info::event_profiling::command_submit`` timestamp.

Implementations are encouraged to return a timestamp that is as close
as possible to the point when the action starts running on the device,
but there is no specific accuracy that is guaranteed.

+----------------------------------+
| Return type: ``uint64_t``        |
+----------------------------------+


.. rubric:: ``sycl::info::event_profiling::command_end``

Querying this profiling descriptor blocks until the event's state
becomes ``sycl::info::event_command_status::complete``.

The returned timestamp tells when the action associated with the
command group (e.g. kernel invocation) finished executing on the device.

For any given event, this timestamp is always greater than or equal
to the ``sycl::info::event_profiling::command_start`` timestamp.

+----------------------------------+
| Return type: ``uint64_t``        |
+----------------------------------+

.. rubric:: Example

See `event-elapsed-time`_.

.. _event-elapsed-time:

=========
Example 1
=========

Measure the elapsed time of a ``memcpy`` executed on a device with
event profiling info.

.. literalinclude:: /examples/event-elapsed-time.cpp
   :lines: 5-
   :linenos:

Output example:

.. literalinclude:: /examples/event-elapsed-time.out
   :lines: 5-
