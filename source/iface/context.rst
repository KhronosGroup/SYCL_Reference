..
  Copyright 2024 The Khronos Group Inc.
  SPDX-License-Identifier: CC-BY-4.0

********
Contexts
********

.. _context:

.. rst-class:: api-class

=================
``sycl::context``
=================

::

  class context;

The ``sycl::context`` class represents a SYCL context. A context
represents the runtime data structures and state required by a
SYCL backend API to interact with a group of devices associated
with a platform.

The ``sycl::event`` class provides the
:ref:`common reference semantics <common-reference>`.


.. seealso:: |SYCL_SPEC_CONTEXT|

(constructors)
==============

::

  explicit context(const sycl::property_list& propList = {});

  explicit context(sycl::async_handler asyncHandler,
                   const sycl::property_list& propList = {});

  explicit context(const sycl::device& dev, const sycl::property_list& propList = {});

  explicit context(const sycl::device& dev, sycl::async_handler asyncHandler,
                   const sycl::property_list& propList = {});

  explicit context(const sycl::platform &plt, const sycl::property_list &propList = {});

  explicit context(const sycl::platform &plt, sycl::async_handler asyncHandler,
                   const sycl::property_list &propList = {});

  explicit context(const std::vector<sycl::device>& deviceList,
                   const sycl::property_list& propList = {});

  explicit context(const std::vector<sycl::device>& deviceList,
                   sycl::async_handler asyncHandler,
                   const sycl::property_list& propList = {});

Construct a ``sycl::context``.

The parameters to the constructor allow control of the devices and
platforms associated with the context. The constructor uses the
:ref:`default selector <built-in-device-selectors>` when no platforms
or devices are supplied.


.. rubric:: Parameters

.. list-table::

  * - ``asyncHandler``
    - Called at specific times (see |SYCL_SPEC_ERROR_HANDLING|)  to report asynchronous SYCL
      exceptions for this context.
  * - ``dev``
    - Constructed ``sycl::context`` contains :ref:`device`.
  * - ``deviceList``
    - Constructed ``sycl::context`` contains all devices in
      ``deviceList``, which must all come from the same :ref:`platform`.
  * - ``plt``
    - Constructed context contains all devices in :ref:`platform` ``plt``.

================
Member functions
================

``get_backend``
===============

::

  sycl::backend get_backend() const noexcept;

Returns a backend identifying the ``sycl::backend``
associated with this ``sycl::context``.

``get_info``
============

::

  template <typename Param>
  typename Param::return_type get_info() const;

Queries this ``sycl::context`` for information requested by the template
parameter ``Param``. The type alias ``Param::return_type`` must be
defined in accordance with the info parameters in `sycl::info::context`_
to facilitate returning the type associated with the ``Param`` parameter.

``get_backend_info``
====================

::

  template <typename Param>
  typename Param::return_type get_backend_info() const;

Queries this ``sycl::context`` for SYCL backend-specific information
requested by the template parameter ``Param``. The type alias
``Param::return_type`` must be defined in accordance with the SYCL
backend specification. Must throw an exception with the
``sycl::errc::backend_mismatch`` error code if the SYCL backend
that corresponds with ``Param`` is different from the SYCL backend
that is associated with this context.

``get_platform``
================

::

  sycl::platform get_platform() const;

Returns the ``sycl::platform`` that is associated with this ``sycl::context``.
The value returned must be equal to that returned by
``get_info<sycl::info::context::platform>()``.

``get_devices``
===============

::

  std::vector<sycl::device> get_devices() const;

Returns a ``std::vector`` containing all SYCL devices that are associated with
this ``sycl::context``. The value returned must be equal to that returned by
``get_info<sycl::info::context::devices>()``.


=======================
Information descriptors
=======================


``sycl::info::context``
=======================

::

  namespace sycl::info::context {

  struct platform;
  struct devices;
  struct atomic_memory_order_capabilities;
  struct atomic_fence_order_capabilities;
  struct atomic_memory_scope_capabilities;
  struct atomic_fence_scope_capabilities;

  }  // namespace sycl::info::context

Used as a template parameter for get_info_ to determine the type of
information.

.. rubric:: ``sycl::info::context::platform``

Returns the platform associated with the context.

+--------------------------------------+
| Return type: :ref:`platform`         |
+--------------------------------------+


.. rubric:: ``sycl::info::context::devices``

Returns all of the devices associated with the context.

+----------------------------------------------------+
| Return type: ``std::vector<sycl::device>``         |
+----------------------------------------------------+


.. rubric:: ``sycl::info::context::atomic_memory_order_capabilities``

This query applies only to the capabilities of atomic
operations that are applied to memory that can be
concurrently accessed by multiple devices in the context.

If these capabilities are not uniform across all devices in
the context, the query reports only the capabilities that
are common for all devices.

Returns the set of memory orders supported by these atomic
operations. When a context returns a "stronger" memory order
in this set, it must also return all "weaker" memory orders.
(See |SYCL_SPEC_MEMORY_ORDERING| for a definition of "stronger"
and "weaker" memory orders.)

The memory orders ``sycl::memory_order::acquire``,
``sycl::memory_order::release``, and ``sycl::memory_order::acq_rel``
are all the same strength. If a context
returns one of these, it must return them all.

At a minimum, each context must support ``sycl::memory_order::relaxed``.

+----------------------------------------------------------+
| Return type: ``std::vector<sycl::memory_order>``         |
+----------------------------------------------------------+


.. rubric:: ``sycl::info::context::atomic_fence_order_capabilities``

This query applies only to the capabilities of
``sycl::atomic_fence`` when applied to memory that can be
concurrently accessed by multiple devices in the context.

If these capabilities are not uniform across all devices
in the context, the query reports only the capabilities
that are common for all devices.

Returns the set of memory orders supported by these
``sycl::atomic_fence`` operations. When a context returns
a "stronger" memory order in this set, it must also
return all "weaker" memory orders.
(See |SYCL_SPEC_MEMORY_ORDERING| for a definition of
"stronger" and "weaker" memory orders.)

At a minimum, each context must support
``sycl::memory_order::relaxed``, ``sycl::memory_order::acquire``,
``sycl::memory_order::release``, and ``sycl::memory_order::acq_rel``.

+----------------------------------------------------------+
| Return type: ``std::vector<sycl::memory_order>``         |
+----------------------------------------------------------+


.. rubric:: ``sycl::info::context::atomic_memory_scope_capabilities``

Returns the set of memory scopes supported by atomic
operations on all devices in the context.

When a context returns a "wider" memory scope in this
set, it must also return all "narrower" memory scopes.
(See |SYCL_SPEC_MEMORY_SCOPE| for a definition of "wider"
and "narrower" scopes.)

At a minimum, each context must support
``sycl::memory_scope::work_item``,
``sycl::memory_scope::sub_group``,
and ``sycl::memory_scope::work_group``.

+----------------------------------------------------------+
| Return type: ``std::vector<sycl::memory_scope>``         |
+----------------------------------------------------------+

.. rubric:: ``sycl::info::context::atomic_memory_scope_capabilities``

Returns the set of memory orderings supported by
``sycl::atomic_fence`` on all devices in the context.

When a context returns a "wider" memory scope in this
set, it must also return all "narrower" memory scopes.
(See |SYCL_SPEC_MEMORY_SCOPE| for a definition of "wider"
and "narrower" scopes.)

At a minimum, each context must support
``sycl::memory_scope::work_item``,
``sycl::memory_scope::sub_group``, and
``sycl::memory_scope::work_group``.

+----------------------------------------------------------+
| Return type: ``std::vector<sycl::memory_scope>``         |
+----------------------------------------------------------+

===========================
``sycl::property::context``
===========================

The ``sycl::property_list`` constructor parameters are
present for future extensibility.

.. _context-example:

=======
Example
=======

Print out all the devices within a context.

.. literalinclude:: /examples/context.cpp
   :lines: 5-
   :linenos:

Potential Output:

.. literalinclude:: /examples/context.out
   :lines: 5-
