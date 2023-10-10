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

See :ref:`device-aspects`.

``is_gpu``
==========

::

  bool is_gpu() const;

Returns the same value as ``has(aspect::gpu)``.

See :ref:`device-aspects`.

``is_accelerator``
==================

::

  bool is_accelerator() const;

Returns the same value as ``has(aspect::accelerator)``.

See :ref:`device-aspects`.

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

.. rubric:: Example

See :ref:`get_devices-example`.

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

::

  bool has_extension(const string_class &extension) const;

Deprecated, use ``has()`` instead.

Returns true if this SYCL device supports the extension
queried by the extension parameter.

``create_sub_devices``
======================

::

  template <info::partition_property Prop>
  std::vector<device> create_sub_devices(size_t count) const;

Available only when Prop is
``sycl::info::partition_property::partition_equally``.

Returns a ``std::vector`` of sub devices partitioned
from this SYCL device based on the ``count`` parameter.
The returned vector contains as many sub devices as
can be created such that each sub device contains
``count`` compute units. If the device's total
number of compute units (as returned by
``sycl::info::device::max_compute_units``) is not evenly
divided by count, then the remaining compute units are
not included in any of the sub devices.

::

  template <info::partition_property Prop>
  std::vector<device> create_sub_devices(const std::vector<size_t>& counts) const;

Available only when Prop is
``sycl::info::partition_property::partition_by_counts``.

Returns a ``std::vector`` of sub devices partitioned from
this SYCL device based on the ``counts`` parameter. For
each non-zero value M in the ``counts`` vector, a sub
device with M compute units is created.

::

  template <info::partition_property Prop>
  std::vector<device> create_sub_devices(info::partition_affinity_domain domain) const;

Available only when Prop is
``sycl::info::partition_property::partition_by_affinity_domain``.

Returns a ``std::vector`` of sub devices partitioned from this
SYCL device by affinity ``domain`` based on the domain parameter,
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
      share memory subsystems at this level. The user may determine
      what happened via ``info::device::partition_type_affinity_domain``.

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

``errc::feature_not_supported``
  If SYCL device does not support the `sycl::info::partition_property`_
  specified by the ``Prop`` template argument.

``errc::invalid``
  If the device's maximum number of sub devices is less than ``count``,
  number of non-zero values in ``counts`` or the total of all the values
  in the ``counts`` vector.

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

.. list-table::
   :header-rows: 1

   * - Descriptor
     - Return type
     - Description
   * -
     - 
     - 

====================================
Information descriptors return types
====================================

.. _info-device_type:

``sycl::info::device_type``
===========================

::

  namespace sycl::info {

  enum class device_type : unsigned int {
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
==================================

::

  namespace sycl::info {

  enum class partition_property : int {
    no_partition,
    partition_equally,
    partition_by_counts,
    partition_by_affinity_domain
  };

  } // namespace sycl::info

See create_sub_devices_.

``sycl::info::partition_affinity_domain``
=========================================

::

  namespace sycl::info {

  enum class partition_affinity_domain : int {
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
==============================

::

  namespace sycl::info {

  enum class local_mem_type : int { 
    none, 
    local, 
    global 
  };

  } // namespace sycl::info

See get_info_.

.. _fp_config:

``sycl::info::fp_config``
=========================

::

  namespace sycl::info {

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

  } // namespace sycl::info

See get_info_.

.. _cache_type:

``sycl::info::global_mem_cache_type``
=====================================

::

  namespace sycl::info {

  enum class global_mem_cache_type : int { 
    none, 
    read_only, 
    read_write 
  };

  } // namespace sycl::info

See get_info_.

.. _exec_capability:

``sycl::info::execution_capability``
====================================

::

  namespace sycl::info {

  enum class execution_capability : unsigned int {
    exec_kernel,
    exec_native_kernel
  };

  } // namespace sycl::info

See get_info_.

.. _device-aspects:

==============
Device aspects
==============

Every SYCL device has an associated set of aspects which
identify characteristics of the ``device``. Aspects are defined
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

SYCL applications can query the aspects for a ``device``
via ``device::has()`` in order to determine whether the
device supports any optional features.

Device aspects defined by the core SYCL specification:

.. list-table::

  * - ``aspect::cpu``
    - A device that runs on a CPU. Devices with this ``aspect`` have device type ``info::device_type::cpu``.
  * - ``aspect::gpu``
    - A device that can also be used to accelerate a 3D graphics API.
      Devices with this ``aspect`` have device type ``info::device_type::gpu``.
  * - ``aspect::accelerator``
    - A dedicated accelerator device, usually using a peripheral interconnect for communication.
      Devices with this ``aspect`` have device type ``info::device_type::accelerator``.
  * - ``aspect::custom``
    - A dedicated accelerator that can use the SYCL API, but programmable kernels cannot
      be dispatched to the device, only fixed functionality is available.
      Devices with this ``aspect`` have device type ``info::device_type::custom``.
  * - ``aspect::emulated``
    - Indicates that the device is somehow emulated. A device with this aspect is not intended
      for performance, and instead will generally have another purpose such as emulation or profiling.
      The precise definition of this aspect is left open to the SYCL implementation.
  * - ``aspect::host_debuggable``
    - Indicates that kernels running on this device can be debugged using standard debuggers that
      are normally available on the host system where the SYCL implementation resides. The precise
      definition of this aspect is left open to the SYCL implementation.
  * - ``aspect::fp16``
    - Indicates that kernels submitted to the device may use the ``sycl::half`` data type.
  * - ``aspect::fp64``
    - Indicates that kernels submitted to the device may use the ``double`` data type.
  * - ``aspect::atomic64``
    - Indicates that kernels submitted to the device may perform 64-bit atomic operations.
  * - ``aspect::image``
    - Indicates that the device supports images.
  * - ``aspect::online_compiler``
    - Indicates that the device supports online compilation of device code.
      Devices that have this aspect support the ``build()`` and ``compile()`` functions.
  * - ``aspect::online_linker``
    - Indicates that the device supports online linking of device code.
      Devices that have this aspect support the ``link()`` function.

      All devices that have this aspect also have ``aspect::online_compiler``.
  * - ``aspect::queue_profiling``
    - Indicates that the device supports queue profiling via ``property::queue::enable_profiling``.
  * - ``aspect::usm_device_allocations``
    - Indicates that the device supports explicit USM allocations.
  * - ``aspect::usm_host_allocations``
    - Indicates that the device can access USM memory allocated via ``usm::alloc::host``.

      The device only supports atomic modification of a host allocation if
      ``aspect::usm_atomic_host_allocations`` is also supported.
  * - ``aspect::usm_atomic_host_allocations``
    - Indicates that the device supports USM memory allocated via ``usm::alloc::host``.
      The host and this device may concurrently access and atomically modify host allocations.
  * - ``aspect::usm_shared_allocations``
    - Indicates that the device supports USM memory allocated via ``usm::alloc::shared``
      on the same device.

      Concurrent access and atomic modification of a shared allocation
      is only supported if ``aspect::usm_atomic_shared_allocations`` is also supported.
  * - ``aspect::usm_atomic_shared_allocations``
    - Indicates that the device supports USM memory allocated via ``usm::alloc::shared``.
      The host and other devices in the same context that also support this capability
      may concurrently access and atomically modify shared allocations.
      The allocation is free to migrate between the host and the appropriate devices.
  * - ``aspect::usm_system_allocations``
    - Indicates that the system allocator may be used instead of SYCL USM allocation
      mechanisms for ``usm::alloc::shared`` allocations on this device.

The implementation also provides two traits that the
application can use to query aspects at compilation time.

The traits ``any_device_has<aspect>`` and ``all_devices_have<aspect>``
are set according to the collection of devices D that can possibly
execute device code, as determined by the compilation environment.

::

  namespace sycl {

  template <aspect Aspect> struct any_device_has;
  template <aspect Aspect> struct all_devices_have;

  template <aspect A>
  inline constexpr bool any_device_has_v = any_device_has<A>::value;
  template <aspect A>
  inline constexpr bool all_devices_have_v = all_devices_have<A>::value;

  } // namespace sycl

The trait ``any_device_has<aspect>`` inherits from ``std::true_type`` only
if at least one device in D has the specified aspect.

The trait ``all_devices_have<aspect>`` inherits from ``std::true_type`` only
if all devices in D have the specified aspect.

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
