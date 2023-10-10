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

  explicit context(const property_list& propList = {});

  explicit context(async_handler asyncHandler,
                 const property_list& propList = {});

  explicit context(const device& dev, const property_list& propList = {});

  explicit context(const device& dev, async_handler asyncHandler,
                 const property_list& propList = {});

  explicit context(const platform &plt, const property_list &propList = {});

  explicit context(const platform &plt, async_handler asyncHandler,
                 const property_list &propList = {});

  explicit context(const std::vector<device>& deviceList,
                 const property_list& propList = {});

  explicit context(const std::vector<device>& deviceList,
                 async_handler asyncHandler,
                 const property_list& propList = {});

Construct a context.

The parameters to the constructor allow control of the devices and
platforms associated with the context. The constructor uses the
:ref:`default selector <built-in-device-selectors>` when no platforms
or devices are supplied.


.. rubric:: Parameters

.. list-table::

  * - ``asyncHandler``
    - Called at specific times (see |SYCL_SPEC_EXCEPTION|)  to report asynchronous SYCL
      exceptions for this context.
  * - ``dev``
    - Constructed context contains device.
  * - ``deviceList``
    - Constructed context contains all devices in ``deviceList``,
      which must all come from the same platform.
  * - ``plt``
    - Constructed context contains all devices in platform ``plt``.


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
with the info parameters in `sycl::info::context`_ to facilitate returning the
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

.. list-table::
   :header-rows: 1

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
     - This query applies only to the capabilities of atomic operations that are applied to memory that can be
       concurrently accessed by multiple devices in the context. If these capabilities
       are not uniform across all devices in the context, the query reports only the capabilities that are common for all devices.

       Returns the set of memory orders supported by these atomic operations. When a context returns a "stronger" memory order in this set, it must also return all "weaker" memory orders. (See
       |SYCL_SPEC_MEMORY_ORDERING| for a definition of "stronger" and "weaker" memory orders.) The memory orders ``memory_order::acquire``, ``emory_order::release``, and ``memory_order::acq_rel`` are all the same strength. If a context returns one of these, it must return them all.

       At a minimum, each context must support ``memory_order::relaxed``.
   * - atomic_fence_order_capabilities
     - ``std::vector<memory_order>``
     -  This query applies only to the capabilities of ``atomic_fence`` when applied to memory that can be
        concurrently accessed by multiple devices in the context. If these capabilities are not uniform across all devices in the context, the query reports only the capabilities that are common for all devices.

        Returns the set of memory orders supported by these ``atomic_fence`` operations. When a context returns a "stronger" memory order in this set, it must also return all "weaker" memory orders. (See |SYCL_SPEC_MEMORY_ORDERING| for a definition of "stronger" and "weaker" memory orders.)

        At a minimum, each context must support ``memory_order::relaxed``, ``memory_order::acquire``, ``memory_order::release``, and ``memory_order::acq_rel``.
   * - atomic_memory_scope_capabilities
     - ``std::vector<memory_scope>``
     -  Returns the set of memory scopes supported by atomic operations on all devices in the context. When a
        context returns a "wider" memory scope in this set, it must also return all "narrower" memory scopes. (See |SYCL_SPEC_MEMORY_SCOPE| for a definition of "wider" and "narrower" scopes.) At a minimum, each context must support ``memory_scope::work_item``, ``memory_scope::sub_group``, and ``memory_scope::work_group``.
   * - atomic_fence_scope_capabilities
     - ``std::vector<memory_scope>``
     -  Returns the set of memory orderings supported by ``atomic_fence`` on all devices in the context.
        When a context returns a "wider" memory scope in this set, it must also return all "narrower" memory scopes. (See |SYCL_SPEC_MEMORY_SCOPE| for a definition of "wider" and "narrower" scopes.)
        At a minimum, each context must support ``memory_scope::work_item``, ``memory_scope::sub_group``, and ``memory_scope::work_group``.

===========================
``sycl::property::context``
===========================

The ``property_list`` constructor parameters are present for
future extensibility.


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
