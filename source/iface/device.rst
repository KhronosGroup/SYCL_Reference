..
  Copyright 2024 The Khronos Group Inc.
  SPDX-License-Identifier: CC-BY-4.0

*******
Devices
*******

.. _device:

================
``sycl::device``
================

::

   class device;

The ``sycl::device`` class encapsulates a single SYCL device on
which :ref:`kernels <kernel>` can be executed.

All member functions of the ``sycl::device`` class are synchronous
and errors are handled by throwing synchronous SYCL exceptions.

The ``sycl::device`` class provides the
:ref:`common reference semantics <common-reference>`.

.. seealso:: |SYCL_SPEC_DEVICE|


(constructors)
==============

::

  device();

  template <typename DeviceSelector>
  explicit device(const DeviceSelector&);

Construct a ``sycl::device`` instance.

The default constructor creates an instance that is a copy of
the device returned by ``sycl::default_selector_v``.

A device can also be chosen by passing the
:ref:`device selector <device-selectors>` parameter.

================
Member functions
================

``get_backend``
===============

::

  sycl::backend get_backend() const noexcept;

Returns a backend identifying the SYCL backend associated
with this device.


``get_platform``
================

::

  sycl::platform get_platform() const noexcept;

Returns the associated SYCL platform. The value returned
must be equal to that returned by ``get_info<sycl::info::device::platform>()``.

``is_cpu``
==========

::

  bool is_cpu() const;

Returns the same value as ``has(sycl::aspect::cpu)``.

See :ref:`device-aspects`.

``is_gpu``
==========

::

  bool is_gpu() const;

Returns the same value as ``has(sycl::aspect::gpu)``.

See :ref:`device-aspects`.

``is_accelerator``
==================

::

  bool is_accelerator() const;

Returns the same value as ``has(sycl::aspect::accelerator)``.

See :ref:`device-aspects`.

``get_info``
============

::

  template <typename Param>
  typename Param::return_type get_info() const;

Queries this ``sycl::device`` for information requested by the
template parameter ``Param``.

The type alias ``Param::return_type`` must be defined in
accordance with the :ref:`info parameters <info-device>` to
facilitate returning the type associated with the ``Param`` parameter.

.. rubric:: Example

See :ref:`get_devices-example`.

``get_backend_info``
====================

::

  template <typename Param>
  typename Param::return_type get_backend_info() const;

Queries this ``sycl::device`` for SYCL backend-specific information
requested by the template parameter ``Param``.

The type alias ``Param::return_type`` must be defined in accordance
with the SYCL backend specification.

Must throw an exception with the ``sycl::errc::backend_mismatch``
error code if the SYCL backend that corresponds with ``Param`` is
different from the SYCL backend that is associated with this device.

``has``
=======

::

  bool has(sycl::aspect asp) const;

Returns true if ``sycl::device`` has the given aspect.
SYCL applications can use this member function to determine
which optional features this device supports (if any).

``has_extension``
=================

::

  bool has_extension(const std::string& extension) const;

Deprecated, use ``has()`` instead.

Returns true if this ``sycl::device`` supports the extension
queried by the extension parameter.

``create_sub_devices``
======================

::

  template <sycl::info::partition_property Prop>
  std::vector<device> create_sub_devices(size_t count) const;

Available only when Prop is
``sycl::info::partition_property::partition_equally``.

Returns a ``std::vector`` of sub devices partitioned
from this ``sycl::device`` based on the ``count`` parameter.
The returned vector contains as many sub devices as
can be created such that each sub device contains
``count`` compute units. If the device's total
number of compute units (as returned by
``sycl::info::device::max_compute_units``) is not evenly
divided by count, then the remaining compute units are
not included in any of the sub devices.

::

  template <sycl::info::partition_property Prop>
  std::vector<sycl::device> create_sub_devices(const std::vector<size_t>& counts) const;

Available only when Prop is
``sycl::info::partition_property::partition_by_counts``.

Returns a ``std::vector`` of sub devices partitioned from
this ``sycl::device`` based on the ``counts`` parameter. For
each non-zero value M in the ``counts`` vector, a sub
device with M compute units is created.

::

  template <sycl::info::partition_property Prop>
  std::vector<sycl::device> create_sub_devices(sycl::info::partition_affinity_domain domain) const;

Available only when Prop is
``sycl::info::partition_property::partition_by_affinity_domain``.

Returns a ``std::vector`` of sub devices partitioned from this
``sycl::device`` by affinity ``domain`` based on the domain parameter,
which must be one of the following values:

.. list-table::

  * - ``sycl::info::partition_affinity_domain::numa``
    - Split the device into sub devices comprised
      of compute units that share a NUMA node.
  * - ``sycl::info::partition_affinity_domain::L4_cache``
    - Split the device into sub devices comprised of
      compute units that share a level 4 data cache.
  * - ``sycl::info::partition_affinity_domain::L3_cache``
    - Split the device into sub devices comprised of
      compute units that share a level 3 data cache.
  * - ``sycl::info::partition_affinity_domain::L2_cache``
    - Split the device into sub devices comprised of
      compute units that share a level 2 data cache.
  * - ``sycl::info::partition_affinity_domain::L1_cache``
    - Split the device into sub devices comprised of
      compute units that share a level 1 data cache.
  * - ``sycl::info::partition_affinity_domain::next_partitionable``
    - Split the device along the next partitionable affinity domain.
      The implementation shall find the first level along which the
      device or sub device may be further subdivided in the order
      ``numa``, ``L4_cache``, ``L3_cache``, ``L2_cache``, ``L1_cache``, and partition
      the device into sub devices comprised of compute units that
      share memory subsystems at this level.

      The user may determine what happened via
      ``info::device::partition_type_affinity_domain``.

.. rubric:: Template parameters

=================  ===
``Prop``           See `sycl::info::partition_property`_.
=================  ===


.. rubric:: Parameters

==================  ===
``count``           Number of compute units per sub-device.
``counts``          Vector with number of compute units for each sub-device.
``domain``          See `sycl::info::partition_affinity_domain`_.
==================  ===

.. rubric:: Exceptions

``sycl::errc::feature_not_supported``
  If SYCL device does not support the `sycl::info::partition_property`_
  specified by the ``Prop`` template argument.

``sycl::errc::invalid``
  In the following cases:

  * If the ``count`` parameter is greater than the number of compute units in the device (``sycl::info::device::max_compute_units``).
  * If the sum of the values in the ``counts`` vector is greater than the number of compute units in the device (``sycl::info::device::max_compute_units``).
  * If the number of non-zero elements in the ``counts`` vector is greater than the maximum number of sub-devices for the device (``sycl::info::device::partition_max_sub_devices``).


=======================
Static member functions
=======================

.. _device-get_devices:

``get_devices``
===============

::

  static std::vector<sycl::device>
  get_devices(sycl::info::device_type deviceType = sycl::info::device_type::all);

Returns a ``std::vector`` containing all the root devices from
all SYCL backends available in the system which have the device
type encapsulated by :ref:`info-device_type`.

.. rubric:: Example

See :ref:`get_devices-example`.

=======================
Information descriptors
=======================

.. _info-device:

``sycl::info::device``
======================

::

  namespace sycl::info::device {

  struct device_type;
  struct vendor_id;
  struct max_compute_units;
  struct max_work_item_dimensions;
  template<int dimensions = 3> struct max_work_item_sizes;
  struct max_work_group_size;
  struct preferred_vector_width_char;
  struct preferred_vector_width_short;
  struct preferred_vector_width_int;
  struct preferred_vector_width_long;
  struct preferred_vector_width_float;
  struct preferred_vector_width_double;
  struct preferred_vector_width_half;
  struct native_vector_width_char;
  struct native_vector_width_short;
  struct native_vector_width_int;
  struct native_vector_width_long;
  struct native_vector_width_float;
  struct native_vector_width_double;
  struct native_vector_width_half;
  struct max_clock_frequency;
  struct address_bits;
  struct max_mem_alloc_size;
  struct image_support; // Deprecated
  struct max_read_image_args;
  struct max_write_image_args;
  struct image2d_max_height;
  struct image2d_max_width;
  struct image3d_max_height;
  struct image3d_max_width;
  struct image3d_max_depth;
  struct image_max_buffer_size;
  struct max_samplers;
  struct max_parameter_size;
  struct mem_base_addr_align;
  struct half_fp_config;
  struct single_fp_config;
  struct double_fp_config;
  struct global_mem_cache_type;
  struct global_mem_cache_line_size;
  struct global_mem_cache_size;
  struct global_mem_size;
  struct max_constant_buffer_size; // Deprecated
  struct max_constant_args; // Deprecated
  struct local_mem_type;
  struct local_mem_size;
  struct error_correction_support;
  struct host_unified_memory;
  struct atomic_memory_order_capabilities;
  struct atomic_fence_order_capabilities;
  struct atomic_memory_scope_capabilities;
  struct atomic_fence_scope_capabilities;
  struct profiling_timer_resolution;
  struct is_endian_little;
  struct is_available;
  struct is_compiler_available; // Deprecated
  struct is_linker_available; // Deprecated
  struct execution_capabilities;
  struct queue_profiling; // Deprecated
  struct built_in_kernels; // Deprecated
  struct built_in_kernel_ids;
  struct platform;
  struct name;
  struct vendor;
  struct driver_version;
  struct profile;
  struct version;
  struct backend_version;
  struct aspects;
  struct extensions; // Deprecated
  struct printf_buffer_size;
  struct preferred_interop_user_sync;
  struct parent_device;
  struct partition_max_sub_devices;
  struct partition_properties;
  struct partition_affinity_domains;
  struct partition_type_property;
  struct partition_type_affinity_domain;

  } // namespace sycl::info::device

Used as a template parameter for get_info_ to determine the type of
information.

.. rubric:: ``sycl::info::device::device_type``

Returns the device type associated with the device.
May not return ``sycl::info::device_type::all``.

+--------------------------------------+
| Return type: :ref:`info-device_type` |
+--------------------------------------+


.. rubric:: ``sycl::info::device::vendor_id``

Returns a unique vendor device identifier.

+---------------------------+
| Return type: ``uint32_t`` |
+---------------------------+


.. rubric:: ``sycl::info::device::max_compute_units``

Returns the number of parallel compute units available
to the device. The minimum value is 1.

+---------------------------+
| Return type: ``uint32_t`` |
+---------------------------+


.. rubric:: ``sycl::info::device::max_work_item_dimensions``

Returns the maximum dimensions that specify the global
and local work-item IDs used by the data parallel execution
model. The minimum value is 3 if this SYCL device is not of
device type ``sycl::info::device_type::custom``.

+---------------------------+
| Return type: ``uint32_t`` |
+---------------------------+


.. rubric:: ``sycl::info::device::max_work_item_sizes<1>``

Returns the maximum number of work-items that are permitted
in a work-group for a kernel running in a one-dimensional index
space.

The minimum value is ``(1)`` for devices that are not of
device type ``sycl::info::device_type::custom``.

+----------------------------------------------+
| Return type: :ref:`sycl::range\<1\> <range>` |
+----------------------------------------------+


.. rubric:: ``sycl::info::device::max_work_item_sizes<2>``

Returns the maximum number of work-items that are permitted in
each dimension of a work-group for a kernel running in a two-dimensional
index space.

The minimum value is ``(1, 1)`` for devices that are not of
device type ``sycl::info::device_type::custom``.

+----------------------------------------------+
| Return type: :ref:`sycl::range\<2\> <range>` |
+----------------------------------------------+


.. rubric:: ``sycl::info::device::max_work_item_sizes<3>``

Returns the maximum number of work-items that are permitted in
each dimension of a work-group for a kernel running in a three-dimensional
index space.

The minimum value is ``(1, 1, 1)`` for devices that are not of
device type ``sycl::info::device_type::custom``.

+----------------------------------------------+
| Return type: :ref:`sycl::range\<3\> <range>` |
+----------------------------------------------+


.. rubric:: ``sycl::info::device::max_work_group_size``

Returns the maximum number of work-items that are permitted in a
work-group executing a kernel on a single compute unit.

The minimum value is 1.

+-----------------------------+
| Return type: ``size_t``     |
+-----------------------------+


.. rubric:: ``sycl::info::device::max_num_sub_groups``

Returns the maximum number of sub-groups in a work-group for
any kernel executed on the device.

The minimum value is 1.

+-----------------------------+
| Return type: ``uint32_t``   |
+-----------------------------+


.. rubric:: ``sycl::info::device::sub_group_sizes``

Returns a ``std::vector`` of ``size_t`` containing the
set of sub-group sizes supported by the device.

+----------------------------------------+
| Return type: ``std::vector<size_t>``   |
+----------------------------------------+


.. rubric:: ``sycl::info::device::preferred_vector_width_<type>``

::

  sycl::info::device::preferred_vector_width_char
  sycl::info::device::preferred_vector_width_short
  sycl::info::device::preferred_vector_width_int
  sycl::info::device::preferred_vector_width_long
  sycl::info::device::preferred_vector_width_float
  sycl::info::device::preferred_vector_width_double
  sycl::info::device::preferred_vector_width_half

Returns the preferred native vector width size for built-in
scalar types that can be put into vectors. The vector width
is defined as the number of scalar elements that can be stored
in the vector.

Must return 0 for ``sycl::info::device::preferred_vector_width_double``
if the device does not have ``sycl::aspect::fp64``.

Must return 0 for ``sycl::info::device::preferred_vector_width_half`` if
the device does not have ``sycl::aspect::fp16``.

+-----------------------------+
| Return type: ``uint32_t``   |
+-----------------------------+


.. rubric:: ``sycl::info::device::native_vector_width_<type>``

::

  sycl::info::device::native_vector_width_char
  sycl::info::device::native_vector_width_short
  sycl::info::device::native_vector_width_int
  sycl::info::device::native_vector_width_long
  sycl::info::device::native_vector_width_float
  sycl::info::device::native_vector_width_double
  sycl::info::device::native_vector_width_half

Returns the native ISA vector width.
The vector width is defined as the number
of scalar elements that can be stored in the vector.

Must return 0 for ``sycl::info::device::native_vector_width_double``
if the device does not have ``sycl::aspect::fp64``.

Must return 0 for ``sycl::info::device::native_vector_width_half`` if
the device does not have ``sycl::aspect::fp16``.

+-----------------------------+
| Return type: ``uint32_t``   |
+-----------------------------+


.. rubric:: ``sycl::info::device::max_clock_frequency``

Returns the maximum configured clock frequency of this
SYCL device in MHz.

+-----------------------------+
| Return type: ``uint32_t``   |
+-----------------------------+


.. rubric:: ``sycl::info::device::address_bits``

Returns the default compute device address space size
specified as an unsigned integer value in bits.

Must return either 32 or 64.

+-----------------------------+
| Return type: ``uint32_t``   |
+-----------------------------+


.. rubric:: ``sycl::info::device::max_mem_alloc_size``

Returns the maximum size of memory object allocation in bytes.

The minimum value is one of two values:

* 1/4 of ``sycl::info::device::global_mem_size``
* 128 * 1024 * 1024

whichever is larger, if this SYCL device
is not of device type ``sycl::info::device_type::custom``.

+-----------------------------+
| Return type: ``uint64_t``   |
+-----------------------------+


.. rubric:: ``sycl::info::device::image_support``

Deprecated.

Returns the same value as ``sycl::device::has(sycl::aspect::image)``.

+-----------------------------+
| Return type: ``bool``       |
+-----------------------------+


.. rubric:: ``sycl::info::device::max_read_image_args``

Returns the maximum number of simultaneous image objects
that can be read from by a kernel.

The minimum value is 128 if the SYCL device has ``sycl::aspect::image``.

+-----------------------------+
| Return type: ``uint32_t``   |
+-----------------------------+


.. rubric:: ``sycl::info::device::max_write_image_args``

Returns the maximum number of simultaneous image objects
that can be written to by a kernel.

The minimum value is 8 if the SYCL device has ``sycl::aspect::image``.

+-----------------------------+
| Return type: ``uint32_t``   |
+-----------------------------+


.. rubric:: ``sycl::info::device::image2d_max_width``

Returns the maximum width of a 2D image or 1D image in pixels.

The minimum value is 8192 if the SYCL device has ``sycl::aspect::image``.

+-----------------------------+
| Return type: ``size_t``     |
+-----------------------------+


.. rubric:: ``sycl::info::device::image2d_max_height``

Returns the maximum height of a 2D image in pixels.

The minimum value is 8192 if the SYCL device has ``sycl::aspect::image``.

+-----------------------------+
| Return type: ``size_t``     |
+-----------------------------+


.. rubric:: ``sycl::info::device::image3d_max_width``

Returns the maximum width of a 3D image in pixels.

The minimum value is 2048 if the SYCL device has ``sycl::aspect::image``.

+-----------------------------+
| Return type: ``size_t``     |
+-----------------------------+


.. rubric:: ``sycl::info::device::image3d_max_height``

Returns the maximum height of a 3D image in pixels.

The minimum value is 2048 if the SYCL device has ``sycl::aspect::image``.

+-----------------------------+
| Return type: ``size_t``     |
+-----------------------------+


.. rubric:: ``sycl::info::device::image3d_max_depth``

Returns the maximum depth of a 3D image in pixels.

The minimum value is 2048 if the SYCL device has ``sycl::aspect::image``.

+-----------------------------+
| Return type: ``size_t``     |
+-----------------------------+


.. rubric:: ``sycl::info::device::image_max_buffer_size``

Returns the number of pixels for a 1D image created from a buffer object.

The minimum value is 65536 if the SYCL device has ``sycl::aspect::image``.

Note that this information is intended for OpenCL interoperability only
as this feature is not supported in SYCL.

+-----------------------------+
| Return type: ``size_t``     |
+-----------------------------+


.. rubric:: ``sycl::info::device::max_samplers``

Returns the maximum number of samplers that can be used in a kernel.

The minimum value is 16 if the SYCL device has ``sycl::aspect::image``.

+-----------------------------+
| Return type: ``uint32_t``   |
+-----------------------------+


.. rubric:: ``sycl::info::device::max_parameter_size``

Returns the maximum size in bytes of the arguments
that can be passed to a kernel.

The minimum value is 1024 if this SYCL device is not of
device type ``sycl::info::device_type::custom``.
For this minimum value, only a maximum
of 128 arguments can be passed to a kernel.

+-----------------------------+
| Return type: ``size_t``     |
+-----------------------------+


.. rubric:: ``sycl::info::device::mem_base_addr_align``

Returns the minimum value in bits of the largest
supported SYCL built-in data
type if this SYCL device is not of device type
``sycl::info::device_type::custom``.

+-----------------------------+
| Return type: ``uint32_t``   |
+-----------------------------+


.. rubric:: ``sycl::info::device::half_fp_config``

Returns a ``std::vector`` of `sycl::info::fp_config`_ describing the
half precision floating-point capability of this SYCL device.
The ``std::vector`` must contain zero or more of the
`sycl::info::fp_config`_ values.

If half precision is supported by this SYCL device
(i.e. the device has ``sycl::aspect::fp16``) there is no minimum floating-point
capability.

If half support is not supported the returned ``std::vector`` must be empty.

+-------------------------------------------------------+
| Return type: ``std::vector<sycl::info::fp_config>``   |
+-------------------------------------------------------+

.. rubric:: ``sycl::info::device::single_fp_config``

Returns a ``std::vector`` of `sycl::info::fp_config`_ describing the
single precision floating-point capability of this SYCL device.
The ``std::vector`` must contain one or more of the
`sycl::info::fp_config`_ values.

If this SYCL device is not of type ``sycl::info::device_type::custom``
then the minimum floating-point capability must be:
``sycl::info::fp_config::round_to_nearest`` and
``sycl::info::fp_config::inf_nan``.

+-------------------------------------------------------+
| Return type: ``std::vector<sycl::info::fp_config>``   |
+-------------------------------------------------------+



.. rubric:: ``sycl::info::device::double_fp_config``

Returns a ``std::vector`` of `sycl::info::fp_config`_
describing the double precision
floating-point capability of this SYCL device. The ``std::vector``
may contain zero or more of the `sycl::info::fp_config`_ values.

If double precision is supported by this SYCL device (i.e. the device
has ``aspect::fp64``) and this SYCL device is not of type
``sycl::info::device_type::custom``
then the minimum floating-point capability must be:
``sycl::info::fp_config::fma``,
``sycl::info::fp_config::round_to_nearest``,
``sycl::info::fp_config::round_to_zero``,
``sycl::info::fp_config::round_to_inf``,
``sycl::info::fp_config::inf_nan``
and ``sycl::info::fp_config::denorm``.

If double support is not supported the returned ``std::vector`` must be empty.

+-------------------------------------------------------+
| Return type: ``std::vector<sycl::info::fp_config>``   |
+-------------------------------------------------------+


.. rubric:: ``sycl::info::device::global_mem_cache_type``

Returns the type of global memory cache supported.

+-------------------------------------------------------+
| Return type: `sycl::info::global_mem_cache_type`_     |
+-------------------------------------------------------+

.. rubric:: ``sycl::info::device::global_mem_cache_line_size``

Returns the size of global memory cache line in bytes.

+-----------------------------+
| Return type: ``uint32_t``   |
+-----------------------------+


.. rubric:: ``sycl::info::device::global_mem_cache_size``

Returns the size of global memory cache in bytes.

+-----------------------------+
| Return type: ``uint64_t``   |
+-----------------------------+


.. rubric:: ``sycl::info::device::global_mem_size``

Returns the size of global device memory in bytes.

+-----------------------------+
| Return type: ``uint64_t``   |
+-----------------------------+


.. rubric:: ``sycl::info::device::max_constant_buffer_size``

Deprecated in SYCL 2020.

Returns the maximum size in bytes of a constant buffer allocation.

The minimum value is 64 KB if this SYCL device is
not of type ``sycl::info::device_type::custom``.

+-----------------------------+
| Return type: ``uint64_t``   |
+-----------------------------+


.. rubric:: ``sycl::info::device::max_constant_args``

Deprecated in SYCL 2020.

Returns the maximum number of constant arguments
that can be declared in a kernel.

The minimum value is 8 if this SYCL device is not
of type ``sycl::info::device_type::custom``.

+-----------------------------+
| Return type: ``uint32_t``   |
+-----------------------------+


.. rubric:: ``sycl::info::device::local_mem_type``

Returns the type of local memory supported.
This can be ``sycl::info::local_mem_type::local``
implying dedicated local memory storage such
as SRAM, or ``sycl::info::local_mem_type::global``.

If this SYCL device is of type ``sycl::info::device_type::custom``
this can also be ``sycl::info::local_mem_type::none``,
indicating local memory is not supported.

+----------------------------------------------+
| Return type: `sycl::info::local_mem_type`_   |
+----------------------------------------------+


.. rubric:: ``sycl::info::device::local_mem_size``

Returns the size of local memory arena in bytes.

The minimum value is 32 KB if this SYCL device
is not of type ``sycl::info::device_type::custom``.

+-----------------------------+
| Return type: ``uint64_t``   |
+-----------------------------+


.. rubric:: ``sycl::info::device::error_correction_support``

Returns true if the device implements error
correction for all accesses to compute
device memory (global and constant).

Returns false if the device does not implement such error correction.

+-----------------------------+
| Return type: ``bool``       |
+-----------------------------+


.. rubric:: ``sycl::info::device::host_unified_memory``

Deprecated, use ``sycl::device::has()`` with one
of the ``sycl::aspect::usm_*`` aspects instead.

Returns true if the device and the host have a
unified memory subsystem and returns false otherwise.

+-----------------------------+
| Return type: ``bool``       |
+-----------------------------+


.. rubric:: ``sycl::info::device::atomic_memory_order_capabilities``

Returns the set of memory orders (See |SYCL_SPEC_MEMORY_ORDERING|)
supported by atomic operations on the device.

When a device returns a "stronger" memory order
in this set, it must also return all
"weaker" memory orders. The memory orders
``sycl::memory_order::acquire``, ``sycl::memory_order::release``,
and ``sycl::memory_order::acq_rel`` are all
the same strength. If a device returns one of these,
it must return them all.

At a minimum, each device must support ``sycl::memory_order::relaxed``.

+-------------------------------------------------------+
| Return type: ``std::vector<sycl::memory_order>``      |
+-------------------------------------------------------+


.. rubric:: ``sycl::info::device::atomic_fence_order_capabilities``

Returns the set of memory orders (See |SYCL_SPEC_MEMORY_ORDERING|) supported by
``atomic_fence`` on the device.

When a device returns a "stronger" memory order in this set,
it must also return all "weaker" memory orders.

At a minimum, each device must support ``sycl::memory_order::relaxed``,
``sycl::memory_order::acquire``, ``sycl::memory_order::release``,
and ``sycl::memory_order::acq_rel``.

+-------------------------------------------------------+
| Return type: ``std::vector<sycl::memory_order>``      |
+-------------------------------------------------------+


.. rubric:: ``sycl::info::device::atomic_memory_scope_capabilities``

Returns the set of memory scopes (See |SYCL_SPEC_MEMORY_SCOPE|) supported by
atomic operations on the device.

When a device returns a "wider" memory scope in this set,
it must also return all "narrower" memory scopes.

At a minimum, each device must support ``sycl::memory_scope::work_item``,
``sycl::memory_scope::sub_group``, and ``sycl::memory_scope::work_group``.

+-------------------------------------------------------+
| Return type: ``std::vector<sycl::memory_scope>``      |
+-------------------------------------------------------+


.. rubric:: ``sycl::info::device::atomic_fence_scope_capabilities``

Returns the set of memory scopes (See |SYCL_SPEC_MEMORY_SCOPE|) supported by
``atomic_fence`` on the device.

When a device returns a "wider" memory scope in this set,
it must also return all "narrower" memory scopes.

At a minimum, each device must support ``sycl::memory_scope::work_item``,
``sycl::memory_scope::sub_group``, and ``sycl::memory_scope::work_group``.

+-------------------------------------------------------+
| Return type: ``std::vector<sycl::memory_scope>``      |
+-------------------------------------------------------+


.. rubric:: ``sycl::info::device::profiling_timer_resolution``

Returns the resolution of device timer in nanoseconds.

+-----------------------------+
| Return type: ``size_t``     |
+-----------------------------+


.. rubric:: ``sycl::info::device::is_endian_little``

Deprecated. Check the byte order of the host system instead.
The host and device are required to have the same byte order.

Returns true if this SYCL device is a little endian device and
returns false otherwise.

+-----------------------------+
| Return type: ``bool``       |
+-----------------------------+


.. rubric:: ``sycl::info::device::is_available``

Returns true if the SYCL device is available and returns false
if the device is not available.

+-----------------------------+
| Return type: ``bool``       |
+-----------------------------+


.. rubric:: ``sycl::info::device::is_compiler_available``

Deprecated.

Returns the same value as ``sycl::device::has(sycl::aspect::online_compiler)``.

+-----------------------------+
| Return type: ``bool``       |
+-----------------------------+


.. rubric:: ``sycl::info::device::is_linker_available``

Deprecated.

Returns the same value as ``sycl::device::has(sycl::aspect::online_linker)``.

+-----------------------------+
| Return type: ``bool``       |
+-----------------------------+


.. rubric:: ``sycl::info::device::execution_capabilities``

Returns a ``std::vector`` of the `sycl::info::execution_capability`_
describing the supported execution capabilities.

Note that this information is intended for OpenCL interoperability only
as SYCL only supports ``sycl::info::execution_capability::exec_kernel``.

+---------------------------------------------------------------------+
| Return type: ``std::vector<sycl::info::execution_capability>``      |
+---------------------------------------------------------------------+


.. rubric:: ``sycl::info::device::queue_profiling``

Deprecated.

Returns the same value as
``sycl::device::has(sycl::aspect::queue_profiling)``.

+----------------------------+
| Return type: ``bool``      |
+----------------------------+


.. rubric:: ``sycl::info::device::built_in_kernel_ids``

Returns a ``std::vector`` of identifiers for the
built-in kernels supported by this SYCL device.

+----------------------------------------------------+
| Return type: ``std::vector<sycl::kernel_id>``      |
+----------------------------------------------------+


.. rubric:: ``sycl::info::device::built_in_kernels``

Deprecated.
Use ``sycl::info::device::built_in_kernel_ids`` instead.

Returns a ``std::vector`` of built-in OpenCL
kernels supported by this SYCL device.

+------------------------------------------------+
| Return type: ``std::vector<std::string>``      |
+------------------------------------------------+


.. rubric:: ``sycl::info::device::platform``

Returns the SYCL platform associated with this SYCL device.

+--------------------------------------+
| Return type: ``sycl::platform``      |
+--------------------------------------+


.. rubric:: ``sycl::info::device::name``

Returns the device name of this SYCL device.

+--------------------------------------+
| Return type: ``std::string``         |
+--------------------------------------+


.. rubric:: ``sycl::info::device::vendor``

Returns the vendor of this SYCL device.

+--------------------------------------+
| Return type: ``std::string``         |
+--------------------------------------+


.. rubric:: ``sycl::info::device::driver_version``

Returns a vendor-defined string describing the
version of the underlying backend software driver.

+--------------------------------------+
| Return type: ``std::string``         |
+--------------------------------------+


.. rubric:: ``sycl::info::device::profile``

Deprecated in SYCL 2020.

Returns a vendor-defined string describing the
version of the underlying backend software driver.

Only supported when using the OpenCL backend.
Throws an exception with the ``sycl::errc::invalid`` error code
if used with a device whose backend is not OpenCL.

The value returned can be one of the following strings:
``FULL_PROFILE``, ``EMBEDDED_PROFILE``.

+--------------------------------------+
| Return type: ``std::string``         |
+--------------------------------------+


.. rubric:: ``sycl::info::device::version``

Returns a backend-defined device version.

+--------------------------------------+
| Return type: ``std::string``         |
+--------------------------------------+


.. rubric:: ``sycl::info::device::backend_version``

Returns a string describing the version of the SYCL backend
associated with the device.

The possible values are specified in the SYCL backend
specification of the SYCL backend associated with the device.

+--------------------------------------+
| Return type: ``std::string``         |
+--------------------------------------+


.. rubric:: ``sycl::info::device::aspects``

Returns a ``std::vector`` of :ref:`sycl::aspect <device-aspects>`
values supported by this SYCL device.

+----------------------------------------------------+
| Return type: ``std::vector<sycl::aspect>``         |
+----------------------------------------------------+


.. rubric:: ``sycl::info::device::extensions``

Deprecated, use ``sycl::info::device::aspects`` instead.

Returns a ``std::vector`` of extension names
(the extension names do not contain any spaces) supported by
this SYCL device.

The extension names returned can be vendor supported extension names.

+----------------------------------------------------+
| Return type: ``std::vector<sycl::string>``         |
+----------------------------------------------------+


.. rubric:: ``sycl::info::device::printf_buffer_size``

Deprecated in SYCL 2020.

Returns the maximum size of the internal buffer that holds the
output of ``printf`` calls from a kernel. The minimum value is
1 MB if ``sycl::info::device::profile`` returns true for this SYCL device.

+-----------------------------+
| Return type: ``size_t``     |
+-----------------------------+


.. rubric:: ``sycl::info::device::preferred_interop_user_sync``

Deprecated in SYCL 2020. Only supported when using the OpenCL backend.
Throws an exception with the ``sycl::errc::invalid`` error code if used with
a device whose backend is not OpenCL.

Returns true if the preference for this SYCL device is for the user to
be responsible for synchronization, when sharing memory objects between
OpenCL and other APIs such as DirectX, false if the device/implementation
has a performant path for performing synchronization of memory object shared
between OpenCL and other APIs.

+-----------------------------+
| Return type: ``bool``       |
+-----------------------------+


.. rubric:: ``sycl::info::device::parent_device``

Returns the parent SYCL device to which this sub-device is a child if this is
a sub-device.

Must throw an exception with the ``sycl::errc::invalid`` error code if
this SYCL device is not a sub device.

+-------------------------------------+
| Return type: ``sycl::device``       |
+-------------------------------------+


.. rubric:: ``sycl::info::device::partition_max_sub_devices``

Returns the maximum number of sub-devices that can be created when this SYCL
device is partitioned.

The value returned cannot exceed the value returned by
``sycl::info::device::device_max_compute_units``.

+-----------------------------+
| Return type: ``uint32_t``   |
+-----------------------------+

.. rubric:: ``sycl::info::device::partition_properties``

Returns the partition properties supported by this SYCL device; a vector
of ``sycl::info::partition_property``.

An element is returned in this vector only if the device can be partitioned
into at least two sub devices along that partition property.

+----------------------------------------------------------------+
| Return type: ``std::vector<sycl::info::partition_property>``   |
+----------------------------------------------------------------+

.. rubric:: ``sycl::info::device::partition_affinity_domains``

Returns a std::vector of the partition affinity domains supported by this
SYCL device when partitioning with
``sycl::info::partition_property::partition_by_affinity_domain``.

An element is returned in this vector only if the device can be partitioned
into at least two sub devices along that affinity domain.

+-----------------------------------------------------------------------+
| Return type: ``std::vector<sycl::info::partition_affinity_domain>``   |
+-----------------------------------------------------------------------+

.. rubric:: ``sycl::info::device::partition_type_property``

Returns the partition property of this SYCL device.

If this SYCL device is not a sub device then the return
value must be ``sycl::info::partition_property::no_partition``,
otherwise it must be one of the following values:
``sycl::info::partition_property::partition_equally``,
``sycl::info::partition_property::partition_by_counts``,
``sycl::info::partition_property::partition_by_affinity_domain``.

+-------------------------------------------------------+
| Return type: `sycl::info::partition_property`_        |
+-------------------------------------------------------+

.. rubric:: ``sycl::info::device::partition_type_affinity_domain``

Returns the partition affinity domain of this SYCL device.

If this SYCL device is not a sub device or the sub device was not partitioned
with ``sycl::info::partition_type::partition_by_affinity_domain``
then the return value must be
``sycl::info::partition_affinity_domain::not_applicable``,
otherwise it must be one of the following values:
``sycl::info::partition_affinity_domain::numa``,
``sycl::info::partition_affinity_domain::L4_cache``,
``sycl::info::partition_affinity_domain::L3_cache``,
``sycl::info::partition_affinity_domain::L2_cache``,
``sycl::info::partition_affinity_domain::L1_cache``.

+-------------------------------------------------------+
| Return type: `sycl::info::partition_affinity_domain`_ |
+-------------------------------------------------------+


Return types
============

.. _info-device_type:

``sycl::info::device_type``
---------------------------

::

  namespace sycl::info {

  enum class device_type : /* unspecified */ {
    cpu,         // Maps to OpenCL CL_DEVICE_TYPE_CPU
    gpu,         // Maps to OpenCL CL_DEVICE_TYPE_GPU
    accelerator, // Maps to OpenCL CL_DEVICE_TYPE_ACCELERATOR
    custom,      // Maps to OpenCL CL_DEVICE_TYPE_CUSTOM
    automatic,   // Maps to OpenCL CL_DEVICE_TYPE_DEFAULT
    host,
    all          // Maps to OpenCL CL_DEVICE_TYPE_ALL
  };

  } // namespace sycl::info

.. rubric:: Example

See :ref:`get_devices-example`.

``sycl::info::partition_property``
----------------------------------

::

  namespace sycl::info {

  enum class partition_property : /* unspecified */ {
    no_partition,
    partition_equally,
    partition_by_counts,
    partition_by_affinity_domain
  };

  } // namespace sycl::info

See create_sub_devices_.

``sycl::info::partition_affinity_domain``
-----------------------------------------

::

  namespace sycl::info {

  enum class partition_affinity_domain : /* unspecified */ {
    not_applicable,
    numa,
    L4_cache,
    L3_cache,
    L2_cache,
    L1_cache,
    next_partitionable
  };

  } // namespace sycl::info

See create_sub_devices_.

.. _local_mem_type:

``sycl::info::local_mem_type``
------------------------------

::

  namespace sycl::info {

  enum class local_mem_type : /* unspecified */ {
    none,
    local,
    global
  };

  } // namespace sycl::info

See get_info_.

.. _fp_config:

``sycl::info::fp_config``
-------------------------

::

  namespace sycl::info {

  enum class fp_config : /* unspecified */ {
    denorm,
    inf_nan,
    round_to_nearest,
    round_to_zero,
    round_to_inf,
    fma,
    correctly_rounded_divide_sqrt,
    soft_float
  };

  } // namespace sycl::info

.. list-table::

  * - ``sycl::info::fp_config::denorm``
    - ``Denorms`` are supported.
  * - ``sycl::info::fp_config::inf_nan``
    - ``INF`` and ``NaNs`` are supported.
  * - ``sycl::info::fp_config::round_to_nearest``
    - Round to nearest even rounding mode is supported.
  * - ``sycl::info::fp_config::round_to_zero``
    - Round to zero rounding mode is supported.
  * - ``sycl::info::fp_config::round_to_inf``
    - Round to positive and negative infinity rounding modes are supported.
  * - ``sycl::info::fp_config::fma``
    - IEEE754-2008 fused multiply-add is supported.
  * - ``sycl::info::fp_config::soft_float``
    - Basic floating-point operations (such as addition, subtraction,
      multiplication) are implemented in software.


See get_info_.

.. _cache_type:

``sycl::info::global_mem_cache_type``
-------------------------------------

::

  namespace sycl::info {

  enum class global_mem_cache_type : /* unspecified */ {
    none,
    read_only,
    read_write
  };

  } // namespace sycl::info

See get_info_.

.. _exec_capability:

``sycl::info::execution_capability``
------------------------------------

::

  namespace sycl::info {

  enum class execution_capability : /* unspecified */ {
    exec_kernel,
    exec_native_kernel
  };

  } // namespace sycl::info

See get_info_.

.. _device-aspects:

==============
Device aspects
==============

Every ``sycl::device`` has an associated set of aspects which
identify characteristics of the device. Aspects are defined
via the ``enum class aspect`` enumeration:

::

  namespace sycl {

  enum class aspect : /* unspecified */ {
    cpu,
    gpu,
    accelerator,
    custom,
    emulated,
    host_debuggable,
    fp16,
    fp64,
    atomic64,
    image,
    online_compiler,
    online_linker,
    queue_profiling,
    usm_device_allocations,
    usm_host_allocations,
    usm_atomic_host_allocations,
    usm_shared_allocations,
    usm_atomic_shared_allocations,
    usm_system_allocations
  };

  } // namespace sycl

SYCL applications can query the aspects for a ``sycl::device``
via ``sycl::device::has()`` in order to determine whether the
device supports any optional features.

Device aspects defined by the core SYCL specification:

.. list-table::

  * - ``sycl::aspect::cpu``
    - A device that runs on a CPU. Devices with this ``aspect`` have device type
      ``sycl::info::device_type::cpu``.
  * - ``sycl::aspect::gpu``
    - A device that can also be used to accelerate a 3D graphics API.
      Devices with this ``sycl::aspect`` have device type ``sycl::info::device_type::gpu``.
  * - ``sycl::aspect::accelerator``
    - A dedicated accelerator device, usually using a peripheral interconnect for communication.
      Devices with this ``aspect`` have device type ``sycl::info::device_type::accelerator``.
  * - ``sycl::aspect::custom``
    - A dedicated accelerator that can use the SYCL API, but programmable kernels cannot
      be dispatched to the device, only fixed functionality is available.
      Devices with this ``aspect`` have device type ``sycl::info::device_type::custom``.
  * - ``sycl::aspect::emulated``
    - Indicates that the device is somehow emulated. A device with this aspect is not intended
      for performance, and instead will generally have another purpose such as emulation or profiling.
      The precise definition of this aspect is left open to the SYCL implementation.
  * - ``sycl::aspect::host_debuggable``
    - Indicates that kernels running on this device can be debugged using standard debuggers that
      are normally available on the host system where the SYCL implementation resides. The precise
      definition of this aspect is left open to the SYCL implementation.
  * - ``sycl::aspect::fp16``
    - Indicates that kernels submitted to the device may use the ``sycl::half`` data type.
  * - ``sycl::aspect::fp64``
    - Indicates that kernels submitted to the device may use the ``double`` data type.
  * - ``sycl::aspect::atomic64``
    - Indicates that kernels submitted to the device may perform 64-bit atomic operations.
  * - ``sycl::aspect::image``
    - Indicates that the device supports images.
  * - ``sycl::aspect::online_compiler``
    - Indicates that the device supports online compilation of device code.
      Devices that have this aspect support the ``build()`` and ``compile()`` functions.
  * - ``sycl::aspect::online_linker``
    - Indicates that the device supports online linking of device code.
      Devices that have this aspect support the ``link()`` function.

      All devices that have this aspect also have ``sycl::aspect::online_compiler``.
  * - ``sycl::aspect::queue_profiling``
    - Indicates that the device supports queue profiling via ``sycl::property::queue::enable_profiling``.
  * - ``sycl::aspect::usm_device_allocations``
    - Indicates that the device supports explicit USM allocations.
  * - ``sycl::aspect::usm_host_allocations``
    - Indicates that the device can access USM memory allocated via ``sycl::usm::alloc::host``.

      The device only supports atomic modification of a host allocation if
      ``sycl::aspect::usm_atomic_host_allocations`` is also supported.
  * - ``sycl::aspect::usm_atomic_host_allocations``
    - Indicates that the device supports USM memory allocated via ``sycl::usm::alloc::host``.
      The host and this device may concurrently access and atomically modify host allocations.
  * - ``sycl::aspect::usm_shared_allocations``
    - Indicates that the device supports USM memory allocated via ``sycl::usm::alloc::shared``
      on the same device.

      Concurrent access and atomic modification of a shared allocation
      is only supported if ``sycl::aspect::usm_atomic_shared_allocations`` is also supported.
  * - ``sycl::aspect::usm_atomic_shared_allocations``
    - Indicates that the device supports USM memory allocated via ``sycl::usm::alloc::shared``.
      The host and other devices in the same context that also support this capability
      may concurrently access and atomically modify shared allocations.
      The allocation is free to migrate between the host and the appropriate devices.
  * - ``sycl::aspect::usm_system_allocations``
    - Indicates that the system allocator may be used instead of SYCL USM allocation
      mechanisms for ``sycl::usm::alloc::shared`` allocations on this device.

The implementation also provides two traits that the
application can use to query aspects at compilation time.

The traits ``sycl::any_device_has<sycl::aspect>`` and
``sycl::all_devices_have<sycl::aspect>`` are set according to
the collection of devices D that can possibly execute device
code, as determined by the compilation environment.

::

  namespace sycl {

  template <aspect Aspect> struct any_device_has;
  template <aspect Aspect> struct all_devices_have;

  template <aspect A>
  inline constexpr bool any_device_has_v = any_device_has<A>::value;
  template <aspect A>
  inline constexpr bool all_devices_have_v = all_devices_have<A>::value;

  } // namespace sycl

The trait ``sycl::any_device_has<sycl::aspect>`` inherits from
``std::true_type`` only if at least one device in D has the specified aspect.

The trait ``sycl::all_devices_have<sycl::aspect>`` inherits from
``std::true_type`` only if all devices in D have the specified aspect.

Applications can use these traits to reduce their code size.

.. _get_devices-example:

=========
Example 1
=========

Enumerate the GPU devices.

.. literalinclude:: /examples/get_devices.cpp
   :lines: 5-
   :linenos:

Output example:

.. literalinclude:: /examples/get_devices.out
   :lines: 5-
