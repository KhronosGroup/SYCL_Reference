..
  Copyright 2020 The Khronos Group Inc.
  SPDX-License-Identifier: CC-BY-4.0

*******
Devices
*******

.. _device:

.. rst-class:: api-class
	       
======
device
======

::
   
   class device;

An abstract class representing various models of SYCL devices. A
device could be a GPU, CPU, or other type of accelerator. Devices
execute kernel functions.

.. seealso:: |SYCL_SPEC_DEVICE|

.. member-toc::

   
(constructors)
==============

.. parsed-literal::
   
  device();
  explicit device(cl_device_id deviceId);
  explicit device(const device_selector &deviceSelector);

Construct a device.

The default constructor creates a host device. A device can also be
constructed from an OpenCL|trade| device or may be chosen by a
:ref:`device-selectors`.
	     
.. rubric:: Parameters

=================  =======================
deviceID           OpenCL device id
deviceSelector     Device selector
=================  =======================

get
===

::
   
  cl_device_id get() const;

Return the cl_device_id of the underlying OpenCL platform.

is_host
=======

::
   
  bool is_host() const;

Returns True if the device is a host device, False otherwise.

is_cpu
======

::
   
  bool is_cpu() const;

Returns True if the device is a CPU, False otherwise.

is_gpu
======

::
   
  bool is_gpu() const;

Returns True if the device is a GPU, False otherwise.

is_accelerator
==============

::
   
  bool is_accelerator() const;

Returns True if the device is an accelerator, False otherwise.

get_platform
============

::
   
  platform get_platform() const;

Returns the platform that contains the device.

get_info
========

::
   
  template <info::device param>
  typename info::param_traits<info::device, param>::return_type
  get_info() const;

Returns information about the device as determined by ``param``. See
`Device Info`_ for details.

.. rubric:: Example

See :ref:`platform-example`.

has_extension
=============

::
   
  bool has_extension(const string_class &extension) const;

Returns True if device supports the extension.


create_sub_devices
==================

.. parsed-literal::
   
  *Available only when:
   prop == info::partition_property::partition_equally*

  template <info::partition_property prop>
  vector_class<device> create_sub_devices(size_t nbSubDev) const;

  *Available only when:
   prop == info::partition_property::partition_by_counts*
   
  template <info::partition_property prop>
  vector_class<device> create_sub_devices(const vector_class<size_t> &counts) const;

  *Available only when:
   prop == info::partition_property::partition_by_affinity_domain*
   
  template <info::partition_property prop>
  vector_class<device> create_sub_devices(info::affinity_domain affinityDomain) const;

Divide into sub-devices, according to the requested partition
property.

.. rubric:: Template parameters

=================  ===
prop               See partition_property_
=================  ===
	    

.. rubric:: Parameters

=================  ===
nbSubDev           Number of subdevices
counts             Vector of sizes for the subdevices
affinityDomain     See partition_affinity_domain_
=================  ===

.. rubric:: Exceptions

feature_not_supported
  When device does not support the partition_property_ specified by
  the ``prop`` template argument.


.. _device-get_devices:

get_devices
===========

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

device
======

::

  enum class device : int {
    device_type,
    vendor_id,
    max_compute_units,
    max_work_item_dimensions,
    max_work_item_sizes,
    max_work_group_size,
    preferred_vector_width_char,
    preferred_vector_width_short,
    preferred_vector_width_int,
    preferred_vector_width_long,
    preferred_vector_width_float,
    preferred_vector_width_double,
    preferred_vector_width_half,
    native_vector_width_char,
    native_vector_width_short,
    native_vector_width_int,
    native_vector_width_long,
    native_vector_width_float,
    native_vector_width_double,
    native_vector_width_half,
    max_clock_frequency,
    address_bits,
    max_mem_alloc_size,
    image_support,
    max_read_image_args,
    max_write_image_args,
    image2d_max_height,
    image2d_max_width,
    image3d_max_height,
    image3d_max_width,
    image3d_max_depth,
    image_max_buffer_size,
    image_max_array_size,
    max_samplers,
    max_parameter_size,
    mem_base_addr_align,
    half_fp_config,
    single_fp_config,
    double_fp_config,
    global_mem_cache_type,
    global_mem_cache_line_size,
    global_mem_cache_size,
    global_mem_size,
    max_constant_buffer_size,
    max_constant_args,
    local_mem_type,
    local_mem_size,
    error_correction_support,
    host_unified_memory,
    profiling_timer_resolution,
    is_endian_little,
    is_available,
    is_compiler_available,
    is_linker_available,
    execution_capabilities,
    queue_profiling,
    built_in_kernels,
    platform,
    name,
    vendor,
    driver_version,
    profile,
    version,
    opencl_c_version,
    extensions,
    printf_buffer_size,
    preferred_interop_user_sync,
    parent_device,
    partition_max_sub_devices,
    partition_properties,
    partition_affinity_domains,
    partition_type_property,
    partition_type_affinity_domain,
    reference_count
  }
  
.. rubric:: Namespace

::

   info

Used as a template parameter for get_info_ to determine the type of
information.

==================================  ==========================  ===
Descriptor                          Return type                 Description
==================================  ==========================  ===
device_type
vendor_id
max_compute_units
max_work_item_dimensions
max_work_item_sizes
max_work_group_size
preferred_vector_width_char
preferred_vector_width_short
preferred_vector_width_int
preferred_vector_width_long
preferred_vector_width_float
preferred_vector_width_double
preferred_vector_width_half
native_vector_width_char
native_vector_width_short
native_vector_width_int
native_vector_width_long
native_vector_width_float
native_vector_width_double
native_vector_width_half
max_clock_frequency
address_bits
max_mem_alloc_size
image_support
max_read_image_args
max_write_image_args
image2d_max_height
image2d_max_width
image3d_max_height
image3d_max_width
image3d_max_depth
image_max_buffer_size
image_max_array_size
max_samplers
max_parameter_size
mem_base_addr_align
half_fp_config                      fp_config_
single_fp_config                    fp_config_
double_fp_config                    fp_config_
global_mem_cache_type               global_mem_cache_type_
global_mem_cache_line_size
global_mem_cache_size
global_mem_size
max_constant_buffer_size
max_constant_args
local_mem_type                      local_mem_type_
local_mem_size
error_correction_support
host_unified_memory
profiling_timer_resolution
is_endian_little
is_available
is_compiler_available
is_linker_available
execution_capabilities              execution_capability_
queue_profiling
built_in_kernels
platform
name
vendor
driver_version
profile
version
opencl_c_version
extensions
printf_buffer_size
preferred_interop_user_sync
parent_device
partition_max_sub_devices
partition_properties
partition_affinity_domains
partition_type_property
partition_type_affinity_domain
reference_count
==================================  ==========================  ===

.. _info-device_type:

device_type
===========

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

partition_property
==================

::

  enum class partition_property : int {
    no_partition,
    partition_equally,
    partition_by_counts,
    partition_by_affinity_domain
  };

See create_sub_devices_

partition_affinity_domain
=========================

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

local_mem_type
==============

::

  enum class local_mem_type : int { none, local, global };

See get_info_

fp_config
=========

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

global_mem_cache_type
=====================

::

  enum class global_mem_cache_type : int { none, read_only, read_write };

See get_info_

execution_capability
====================

::
   
  enum class execution_capability : unsigned int {
    exec_kernel,
    exec_native_kernel
  };

See get_info_  
