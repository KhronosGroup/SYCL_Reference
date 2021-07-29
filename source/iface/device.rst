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

An abstract class representing various models of SYCL devices. A
device could be a GPU, CPU, or other type of accelerator. Devices
execute kernel functions.

.. seealso::

   `Data Parallel C++ Guide <https://link.springer.com/content/pdf/10.1007%2F978-1-4842-5574-2.pdf#page=299>`__

   `SYCL Specification <https://www.khronos.org/registry/SYCL/specs/sycl-2020/html/sycl-2020.html#sec:device-class>`__

(constructors)
==============

.. parsed-literal::

  device();
  template <typename DeviceSelector>
  explicit device(const DeviceSelector &deviceSelector);

Construct a device.

The default constructor creates a host device. A device can also be
chosen by a :ref:`device-selectors`.

.. rubric:: Parameters

==================  =======================
``deviceSelector``  Device selector
==================  =======================

``get_backend``
===============

::

  backend get_backend() const noexcept;

``is_cpu``
==========

::

  bool is_cpu() const;

Returns True if the device is a CPU, False otherwise.

``is_gpu``
==========

::

  bool is_gpu() const;

Returns True if the device is a GPU, False otherwise.

``is_accelerator``
==================

::

  bool is_accelerator() const;

Returns True if the device is an accelerator, False otherwise.

``get_platform``
================

::

  platform get_platform() const;

Returns the platform that contains the device.

``get_info``
============

::

  template <typename param>
  typename param::return_type get_info() const;

Returns information about the device as determined by ``param``. See
`Device Info`_ for details.

.. rubric:: Example

See :ref:`platform-example`.

``get_backend_info``
====================

::

  template <typename param>
  typename param::return_type get_backend_info() const;

``has``
=======

::

  bool has(aspect asp) const;

``has_extension``
=================

::

  bool has_extension(const string_class &extension) const;

Returns True if device supports the extension.


``create_sub_devices``
======================

.. parsed-literal::

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
``prop``           See `sycl::info::partition_property`_
=================  ===


.. rubric:: Parameters

==================  ===
``count``           Number of compute units per sub-device
``counts``          Vector with number of compute units for each sub-device
``affinityDomain``  See `sycl::info::partition_affinity_domain`_
==================  ===

.. rubric:: Exceptions

feature_not_supported
  When device does not support the `sycl::info::partition_property`_
  specified by the ``prop`` template argument.


.. _device-get_devices:

``get_devices``
===============

::

  static vector_class<device> get_devices(
      info::device_type deviceType = info::device_type::all);

Returns vector of devices filtered by :ref:`info-device_type`.

.. rubric:: Example

Enumerate the GPU devices

.. literalinclude:: /examples/get_devices.cpp
   :lines: 5-
   :linenos:

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

See platform :ref:`platform-get_devices` and device :ref:`device-get_devices`.

``sycl::info::partition_property``
==================================

::

  enum class partition_property : int {
    no_partition,
    partition_equally,
    partition_by_counts,
    partition_by_affinity_domain
  };

See create_sub_devices_

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

See create_sub_devices_

.. _local_mem_type:

``sycl::info::local_mem_type``
==============================

::

  enum class local_mem_type : int { none, local, global };

See get_info_

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

See get_info_

.. _cache_type:

``sycl::info::global_mem_cache_type``
=====================================

::

  enum class global_mem_cache_type : int { none, read_only, read_write };

See get_info_

.. _exec_capability:

``sycl::info::execution_capability``
====================================

::

  enum class execution_capability : unsigned int {
    exec_kernel,
    exec_native_kernel
  };

See get_info_
