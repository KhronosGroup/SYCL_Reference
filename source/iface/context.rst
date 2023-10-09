..
  Copyright 2020 The Khronos Group Inc.
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

The context class represents a SYCL context. A context represents
the runtime data structures and state required by a SYCL backend
API to interact with a group of devices associated with a platform.

.. seealso:: |SYCL_SPEC_CONTEXT|

(constructors)
==============

::

  explicit context(async_handler asyncHandler = {});

  explicit context(const device& dev, async_handler asyncHandler = {});

  explicit context(const std::vector<device>& deviceList,
                 async_handler asyncHandler = {});

Construct a context.

The parameters to the constructor allow control of the devices and
platforms associated with the context. The constructor uses the
:ref:`default selector <built-in-device-selectors>` when no platforms
or devices are supplied.


.. rubric:: Parameters

.. list-table::

  * - ``asyncHandler``
    - Called to report asynchronous SYCL exceptions for this context
  * - ``dev``
    - Constructed context contains device
  * - ``deviceList``
    - Constructed context contains devices



.. todo:: Examples that combines the functions


===============
Member function
===============

``get_backend``
===============

::

  backend get_backend() const noexcept;

Returns a backend identifying the SYCL backend associated with this context.

``get_info``
============

::

  template <typename Param>
  typename Param::return_type get_info() const;

Queries this SYCL context for information requested by the template parameter
``Param``. The type alias ``Param::return_type`` must be defined in accordance
with the info parameters in `sycl::info::context`_ facilitate returning the
type associated with the ``Param`` parameter.

``get_backend_info``
====================

::

  template <typename Param>
  typename Param::return_type get_backend_info() const;

Queries this SYCL context for SYCL backend-specific information requested by
the template parameter ``Param``. The type alias ``Param::return_type`` must
be defined in accordance with the SYCL backend specification. Must throw an
exception with the ``errc::backend_mismatch`` error code if the SYCL backend
that corresponds with ``Param`` is different from the SYCL backend that is
associated with this context.

``get_platform``
================

::

  platform get_platform() const;

Returns the SYCL platform that is associated with this SYCL context.
The value returned must be equal to that returned by
``get_info<info::context::platform>()``.

``get_devices``
===============

::

  std::vector<device> get_devices() const;

Returns a std::vector containing all SYCL devices that are associated with
this SYCL context. The value returned must be equal to that returned by
``get_info<info::context::devices>()``.


=======================
Information descriptors
=======================


=======================
``sycl::info::context``
=======================

::

  enum class context : int {
    platform,
    devices,
    atomic_memory_order_capabilities,
    atomic_fence_order_capabilities,
    atomic_memory_scope_capabilities,
    atomic_fence_scope_capabilities
  };

Used as a template parameter for get_info_ to determine the type of
information.

   * - Descriptor
     - Return type
     - Description
   * - platform
     - :ref:`platform`
     - Returns the platform associated with the context.
   * - devices
     - ``std::vector<device>``
     - Returns all of the devices associated with the context.
   * - atomic_memory_order_capabilities
     - ``std::vector<memory_order>``
     - Returns the set of memory orderings supported by atomic operations
       on all devices in the context, which is guaranteed to include ``relaxed``.
       The memory ordering of the context determines the behavior of atomic
       operations applied to any memory that can be concurrently accessed by
       multiple devices in the context.
   * - atomic_fence_order_capabilities
     - ``std::vector<memory_order>``
     -  Returns the set of memory orderings supported by ``atomic_fence`` on all
        devices in the context, which is guaranteed to include ``relaxed``,
        ``acquire``, ``release`` and ``acq_rel``.
        The memory ordering of the context determines the behavior of fence operations
        applied to any memory that can be concurrently accessed by multiple devices in the context.
   * - atomic_memory_scope_capabilities
     - ``std::vector<memory_scope>``
     -  Returns the set of memory scopes supported by atomic operations on all
        devices in the context, which is guaranteed to include ``work_group``.
   * - atomic_fence_scope_capabilities
     - ``std::vector<memory_scope>``
     -  Returns the set of memory orderings supported by ``atomic_fence`` on all
        devices in the context, which is guaranteed to include ``work_group``.

===========================
``sycl::property::context``
===========================

The ``property_list`` constructor parameters are present for extensibility.


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
