..
  Copyright 2020 The Khronos Group Inc.
  SPDX-License-Identifier: CC-BY-4.0

*******
Devices
*******

.. _device:

.. rst-class:: api-class

================
``sycl::device``
================

::

   class device;

The SYCL device class encapsulates a single SYCL device on
which :ref:`kernels <kernel>` can be executed.

All member functions of the device class are synchronous
and errors are handled by throwing synchronous SYCL exceptions.

The SYCL device class provides the
:ref:`common reference semantics <common-reference>`.

.. seealso:: |SYCL_SPEC_DEVICE|


(constructors)
==============

::

  device();
  template <typename DeviceSelector> explicit device(const DeviceSelector&);

Construct a SYCL device instance.

The default constructor creates an instance that is a copy of
the device returned by ``default_selector_v``.

A device can also be chosen by passing the
:ref:`device selector <device-selectors>` parameter.

..
  rubric:: Parameters
  ==================  =======================
  ``deviceSelector``  Device selector
  ==================  =======================


================
Member functions
================

``get_backend``
===============

::

  backend get_backend() const noexcept;

Returns a backend identifying the SYCL backend associated
with this device.


``get_platform``
================

::

  platform get_platform() const noexcept;

Returns the associated SYCL platform. The value returned
must be equal to that returned by ``get_info<info::device::platform>()``.

``is_cpu``
==========

::

  bool is_cpu() const;

Returns the same value as ``has(aspect::cpu)``.
.. TODO: add reference to aspect table

``is_gpu``
==========

::

  bool is_gpu() const;

Returns the same value as ``has(aspect::gpu)``.
.. TODO: add reference to aspect table

``is_accelerator``
==================

::

  bool is_accelerator() const;

Returns the same value as ``has(aspect::accelerator)``.
.. TODO: add reference to aspect table

``get_info``
============

::

  template <typename Param>
  typename Param::return_type get_info() const;

Queries this SYCL device for information requested by the
template parameter ``Param``.

The type alias ``Param::return_type`` must be defined in
accordance with the :ref:`info parameters <info-device>` to
facilitate returning the type associated with the ``Param`` parameter.

.. TODO: Update or modify example
.. .. rubric:: Example

.. See :ref:`platform-example <platform-example>`.

``get_backend_info``
====================

::

  template <typename Param>
  typename Param::return_type get_backend_info() const;

Queries this SYCL device for SYCL backend-specific information
requested by the template parameter ``Param``.

The type alias ``Param::return_type`` must be defined in accordance
with the SYCL backend specification.

Must throw an exception with the ``errc::backend_mismatch``
error code if the SYCL backend that corresponds with ``Param`` is
different from the SYCL backend that is associated with this device.

``has``
=======

::

  bool has(aspect asp) const;

Returns true if this SYCL device has the given aspect.
SYCL applications can use this member function to determine
which optional features this device supports (if any).

``has_extension``
=================

.. TODO: Decide what to do with deprecated API

::

  bool has_extension(const string_class &extension) const;

Deprecated, use ``has()`` instead.

Returns true if this SYCL device supports the extension
queried by the extension parameter.

``create_sub_devices``
======================
.. TODO: Update create_sub_devices

::

  // Available only when prop == info::partition_property::partition_equally
  template <info::partition_property prop>
  std::vector<device> create_sub_devices(size_t count) const;
  // Available only when prop == info::partition_property::partition_by_counts
  template <info::partition_property prop>
  std::vector<device> create_sub_devices(const std::vector<size_t> &counts) const;
  // Available only when prop == info::partition_property::partition_by_affinity_domain
  template <info::partition_property prop>
  std::vector<device> create_sub_devices(info::partition_affinity_domain affinityDomain) const;

Divide into sub-devices, according to the requested partition
property.

.. rubric:: Template parameters

=================  ===
``prop``           See `sycl::info::partition_property`_.
=================  ===


.. rubric:: Parameters

==================  ===
``count``           Number of compute units per sub-device.
``counts``          Vector with number of compute units for each sub-device.
``affinityDomain``  See `sycl::info::partition_affinity_domain`_.
==================  ===

.. rubric:: Exceptions

feature_not_supported
  When device does not support the `sycl::info::partition_property`_
  specified by the ``prop`` template argument.

=======================
Static member functions
=======================

.. _device-get_devices:

``get_devices``
===============

::

  static std::vector<device> get_devices(info::device_type deviceType = info::device_type::all);

Returns a ``std::vector`` containing all the root devices from
all SYCL backends available in the system which have the device
type encapsulated by :ref:`info-device_type`.

.. rubric:: Example

See get_devices-example_.

===========
Device Info
===========

.. _info-device:

``sycl::info::device``
======================

::

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

Used as a template parameter for get_info_ to determine the type of
information.

See `SYCL Specification <https://www.khronos.org/registry/SYCL/specs/sycl-2020/html/sycl-2020.html#_device_information_descriptors>`__ for further details on these types.

.. _info-device_type:

``sycl::info::device_type``
===========================

::

  enum class device_type : unsigned int {
    cpu,         // Maps to OpenCL CL_DEVICE_TYPE_CPU
    gpu,         // Maps to OpenCL CL_DEVICE_TYPE_GPU
    accelerator, // Maps to OpenCL CL_DEVICE_TYPE_ACCELERATOR
    custom,      // Maps to OpenCL CL_DEVICE_TYPE_CUSTOM
    automatic,   // Maps to OpenCL CL_DEVICE_TYPE_DEFAULT
    host,
    all          // Maps to OpenCL CL_DEVICE_TYPE_ALL
  };

..
  TODO See platform :ref:`platform-get_devices` and device
  :ref:`device-get_devices`.

``sycl::info::partition_property``
==================================

::

  enum class partition_property : int {
    no_partition,
    partition_equally,
    partition_by_counts,
    partition_by_affinity_domain
  };

See create_sub_devices_.

``sycl::info::partition_affinity_domain``
=========================================

::

  enum class partition_affinity_domain : int {
    not_applicable,
    numa,
    L4_cache,
    L3_cache,
    L2_cache,
    L1_cache,
    next_partitionable
  };

See create_sub_devices_.

.. _local_mem_type:

``sycl::info::local_mem_type``
==============================

::

  enum class local_mem_type : int { none, local, global };

See get_info_.

.. _fp_config:

``sycl::info::fp_config``
=========================

::

  enum class fp_config : int {
    denorm,
    inf_nan,
    round_to_nearest,
    round_to_zero,
    round_to_inf,
    fma,
    correctly_rounded_divide_sqrt,
    soft_float
  };

See get_info_.

.. _cache_type:

``sycl::info::global_mem_cache_type``
=====================================

::

  enum class global_mem_cache_type : int { none, read_only, read_write };

See get_info_.

.. _exec_capability:

``sycl::info::execution_capability``
====================================

::

  enum class execution_capability : unsigned int {
    exec_kernel,
    exec_native_kernel
  };

See get_info_.

.. _get_devices-example:

=========
Example 1
=========

Enumerate the GPU devices.

.. literalinclude:: /examples/get_devices.cpp
   :lines: 5-
   :linenos:
