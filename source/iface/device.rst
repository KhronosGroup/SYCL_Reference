..
  // Copyright (c) 2011-2020 The Khronos Group, Inc.
  //
  // Licensed under the Apache License, Version 2.0 (the License);
  // you may not use this file except in compliance with the License.
  // You may obtain a copy of the License at
  //
  //     http://www.apache.org/licenses/LICENSE-2.0
  //
  // Unless required by applicable law or agreed to in writing, software
  // distributed under the License is distributed on an AS IS BASIS,
  // WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  // See the License for the specific language governing permissions and
  // limitations under the License.

*******
Devices
*******

.. rst-class:: api-class
	       
==========
``device``
==========

::
   
   class device;

An abstract class representing various models of SYCL devices

.. member-toc::

   
(constructors)
==============

.. parsed-literal::
   
  *Default Constructor. Constructs a device object in host mode*
  device();

  *Constructs a device object from another device object and
   retains the cl_device_id object if the device is not in
   host mode.*

  explicit device(cl_device_id deviceId);

  *Use deviceSelector to choose device*

  explicit device(const device_selector &deviceSelector);

	     
.. rubric:: Parameters

=================  =======================
deviceID           OpenCL device id
deviceSelector     Device selector
=================  =======================

get
===

::
   
  cl_device_id get() const;

Return the cl_device_id of the underlying OpenCL platform

.. rubric:: Returns

cl_device_id of underlying OpenCL platform

is_host
=======

::
   
  bool is_host() const;

Checks if the device is a SYCL host device

.. rubric:: Returns

True if the device is a :term:`host device`, false otherwise.

is_cpu
======

::
   
  bool is_cpu() const;

Checks if the device is a CPU

.. rubric:: Returns

True if the device is a CPU, false otherwise

is_gpu
======

::
   
  bool is_gpu() const;

Checks if the device is a GPU

.. rubric:: Returns

True if the device is a GPU, false otherwise

is_accelerator
==============

::
   
  bool is_accelerator() const;

Checks if the device is a GPU

.. rubric:: Returns

True if the device is a GPU, false otherwise

get_platform
============

::
   
  platform get_platform() const;

Returns the platform that contains the device

.. rubric:: Returns

Platform object

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


.. rubric:: Parameters

=================  ===
extension          name of extension
=================  ===


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


.. rubric:: Parameters

=================  ===
nbSubDev
counts
affinityDomain
=================  ===


get_devices
===========

::
   
  static vector_class<device> get_devices(
      info::device_type deviceType = info::device_type::all);

.. _device-info:
   
===========
Device Info
===========

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
half_fp_config
single_fp_config
double_fp_config
global_mem_cache_type
global_mem_cache_line_size
global_mem_cache_size
global_mem_size
max_constant_buffer_size
max_constant_args
local_mem_type
local_mem_size
error_correction_support
host_unified_memory
profiling_timer_resolution
is_endian_little
is_available
is_compiler_available
is_linker_available
execution_capabilities
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
