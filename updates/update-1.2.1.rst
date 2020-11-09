..
  Copyright 2020 The Khronos Group Inc.
  SPDX-License-Identifier: CC-BY-4.0

====================
 SYCL 1.2.1 Classes
====================

::

   find ref/sycl-1.2.1 -name '*.h' | xargs grep -n '^class'

====== ===
Status Path
====== ===
yes    ref/sycl-1.2.1/accessorBuffer.h:20:class accessor {
yes    ref/sycl-1.2.1/accessorImage.h:20:class accessor {
yes    ref/sycl-1.2.1/accessorLocal.h:20:class accessor {
yes    ref/sycl-1.2.1/atomic.h:23:class atomic {
yes    ref/sycl-1.2.1/buffer.h:19:class use_host_ptr {
yes    ref/sycl-1.2.1/buffer.h:24:class use_mutex {
yes    ref/sycl-1.2.1/buffer.h:31:class context_bound {
yes    ref/sycl-1.2.1/buffer.h:42:class buffer {
yes    ref/sycl-1.2.1/commandGroup.h:17:class command_group {
yes    ref/sycl-1.2.1/commandGroupHandler.h:18:class handler {
skip   ref/sycl-1.2.1/common-byval.h:18:class T {
skip   ref/sycl-1.2.1/common-reference.h:18:class T {
yes    ref/sycl-1.2.1/context.h:17:class context {
yes    ref/sycl-1.2.1/device.h:17:class device {
yes    ref/sycl-1.2.1/deviceEvent.h:17:class device_event {
yes    ref/sycl-1.2.1/deviceSelector.h:17:class default_selector : public device_selector {
yes    ref/sycl-1.2.1/deviceSelector.h:26:class opencl_selector : public device_selector {
yes    ref/sycl-1.2.1/deviceSelector.h:35:class cpu_selector : public device_selector {
yes    ref/sycl-1.2.1/deviceSelector.h:44:class gpu_selector : public device_selector {
yes    ref/sycl-1.2.1/deviceSelector.h:53:class host_selector : public device_selector {
yes    ref/sycl-1.2.1/deviceSelectorInterface.h:17:class device_selector {
yes    ref/sycl-1.2.1/event.h:18:class event {
yes    ref/sycl-1.2.1/exception.h:20:class exception {
yes    ref/sycl-1.2.1/exception.h:31:class exception_list {
yes    ref/sycl-1.2.1/exception.h:46:class runtime_error : public exception;
yes    ref/sycl-1.2.1/exception.h:48:class kernel_error : public runtime_error;
yes    ref/sycl-1.2.1/exception.h:50:class accessor_error : public runtime_error;
yes    ref/sycl-1.2.1/exception.h:52:class nd_range_error : public runtime_error;
yes    ref/sycl-1.2.1/exception.h:54:class event_error : public runtime_error;
yes    ref/sycl-1.2.1/exception.h:56:class invalid_parameter_error : public runtime_error;
yes    ref/sycl-1.2.1/exception.h:58:class device_error : public exception;
yes    ref/sycl-1.2.1/exception.h:60:class compile_program_error : public device_error;
yes    ref/sycl-1.2.1/exception.h:62:class link_program_error : public device_error;
yes    ref/sycl-1.2.1/exception.h:64:class invalid_object_error : public device_error;
yes    ref/sycl-1.2.1/exception.h:66:class memory_allocation_error : public device_error;
yes    ref/sycl-1.2.1/exception.h:68:class platform_error : public device_error;
yes    ref/sycl-1.2.1/exception.h:70:class profiling_error : public device_error;
yes    ref/sycl-1.2.1/exception.h:72:class feature_not_supported : public device_error;
yes    ref/sycl-1.2.1/group.h:18:class group {
yes    ref/sycl-1.2.1/hitem.h:18:class h_item {
yes    ref/sycl-1.2.1/id.h:18:class id {
yes    ref/sycl-1.2.1/image.h:19:class use_host_ptr {
yes    ref/sycl-1.2.1/image.h:24:class use_mutex {
yes    ref/sycl-1.2.1/image.h:31:class context_bound {
yes    ref/sycl-1.2.1/image.h:78:class image {
yes    ref/sycl-1.2.1/item.h:18:class item {
yes    ref/sycl-1.2.1/kernelWIP.h:17:class kernel {
yes    ref/sycl-1.2.1/multipointer.h:27:class multi_ptr {
yes    ref/sycl-1.2.1/multipointer.h:126:class multi_ptr<VoidType, Space> {
yes    ref/sycl-1.2.1/nditem.h:18:class nd_item {
yes    ref/sycl-1.2.1/ndRange.h:18:class nd_range {
yes    ref/sycl-1.2.1/paramTraits.h:19:class param_traits {
yes    ref/sycl-1.2.1/platform.h:17:class platform {
yes    ref/sycl-1.2.1/pointer.h:19:class multi_ptr;
yes    ref/sycl-1.2.1/priv.h:18:class private_memory {
yes    ref/sycl-1.2.1/programWIP.h:23:class program {
skip   ref/sycl-1.2.1/properties.h:24:class T {
skip   ref/sycl-1.2.1/properties.h:36:class property_list {
yes    ref/sycl-1.2.1/queue.h:17:class queue {
yes    ref/sycl-1.2.1/range.h:18:class range {
yes    ref/sycl-1.2.1/sampler.h:36:class sampler {
yes    ref/sycl-1.2.1/stream.h:65:class stream {
yes    ref/sycl-1.2.1/vec.h:54:class vec {
====== ===

::

  class: multi_ptr
    member: (constructors)
    member: operator=
    member: operator*
    member: operator->
    member: get
    member: (Implicit conversions)
    member: (Arithmetic operators)
    member: prefetch
    member: (Relational operators)
  class: buffer
    member: (constructors)
    member: get_range
    member: get_count
    member: get_size
    member: get_allocator
    member: get_access
    member: set_final_data
    member: set_write_back
    member: is_sub_buffer
    member: reinterpret
  class: use_host_ptr
    member: (constructors)
  class: use_mutex
    member: (constructors)
    member: get_mutex_ptr
  class: Buffer accessor
    member: (constructors)
    member: is_placeholder
    member: get_size
    member: get_count
    member: get_range
    member: get_offset
    member: operator ()
    member: operator[]
    member: get_pointer
  class: command_group
    member: (constructors)
    member: events
  class: handler
    member: require
    member: set_arg
    member: set_args
    member: single_task
    member: parallel_for
    member: copy
    member: update_host
    member: fill
  class: Context
    member: (constructors)
    member: get
    member: is_host
    member: get_platform
    member: get_devices
    member: get_info
  class: device
    member: (constructors)
    member: get
    member: is_host
    member: is_cpu
    member: is_gpu
    member: is_accelerator
    member: get_platform
    member: get_info
    member: has_extension
    member: create_sub_devices
    member: get_devices
  class: device_event
    member: wait
  class: device_selector
    member: (constructors)
    member: select_device
    member: operator()
  class: default_selector
  class: gpu_selector
  class: accelerator_selector
  class: cpu_selector
  class: host_selector
  class: event
    member: (constructors)
    member: cl_event_get
    member: is_host
    member: get_wait_list
    member: wait
    member: wait_and_throw
    member: get_info
    member: get_profiling_info
  class: exception
    member: what
    member: has_context
    member: get_context
    member: get_cl_code
  class: group
    member: get_id
    member: get_global_range
    member: get_local_range
    member: get_group_range
    member: get_linear_id
    member: parallel_for_work_item
    member: mem_fence
    member: asyn_work_group_copy
    member: wait_for
    member: operator[]
  class: image
    member: (constructors)
    member: get_range
    member: get_pitch
    member: get_count
    member: get_size
    member: get_allocator
    member: get_access
    member: set_final_data
    member: set_write_back
  class: use_host_ptr
    member: (constructors)
  class: use_mutex
    member: (constructors)
    member: get_mutex_ptr
  class: Image accessor
    member: (constructors)
    member: get_count
    member: get_range
    member: read
    member: operator[]
  class: kernel
    member: (constructors)
    member: get
    member: is_host
    member: get_context
    member: get_program
    member: get_info
    member: get_work_group_info
  class: Local accessor
    member: (constructors)
    member: get_size
    member: get_count
    member: get_range
    member: get_pointer
    member: operator[]
    member: operator ()
  class: platform
    member: (constructor)
    member: get
    member: get_devices
    member: get_info
    member: has_extension
    member: is_host
    member: get_platforms
  class: program
    member: (constructors)
    member: get
    member: is_host
    member: compile_with_kernel_type
    member: build_with_source
    member: link
    member: has_kernel
    member: get_kernel
    member: get_info
    member: get_binaries
    member: get_context
    member: get_devices
    member: get_compile_options
    member: get_link_options
    member: get_build_options
    member: get_state
  class: queue
    member: (constructors)
    member: get
    member: get_context
    member: get_device
    member: is_host
    member: get_info
    member: submit
    member: wait
    member: wait_and_throw
    member: throw_asynchronous
  class: range
    member: get
    member: operator[]
    member: size
    member: Arithmetic Operators
  class: sampler
  class: stream
    member: (constructors)
    member: get_size
    member: get_work_item_buffer_size
    member: get_max_statement_size
  class: atomic
    member: (constructors)
    member: store
    member: load
    member: exchange
    member: compare_exchange_strong
    member: fetch_add
    member: fetch_sub
    member: fetch_and
    member: fetch_or
    member: fetch_xor
    member: fetch_min
    member: fetch_max
  class: vec
    member: (constructors)
    member: Conversion functions
    member: get_count
    member: get_size
    member: convert
    member: as
    member: swizzle
    member: swizzle access
    member: load
    member: store
    member: Arithmetic operators

======  ===
Status
======  ===
done    accessorBuffer.h:20:class accessor {
done    accessorImage.h:20:class accessor {
done    accessorLocal.h:20:class accessor {
done    atomic.h:23:class atomic {
done    buffer.h:19:class use_host_ptr {
done    buffer.h:24:class use_mutex {
done    buffer.h:31:class context_bound {
done    buffer.h:42:class buffer {
done    commandGroup.h:17:class command_group {
done    commandGroupHandler.h:18:class handler {
skip    common-byval.h:18:class T {
skip    common-reference.h:18:class T {
done    context.h:17:class context {
done    device.h:17:class device {
done    deviceEvent.h:17:class device_event {
done    deviceSelector.h:17:class default_selector : public device_selector {
done    deviceSelector.h:26:class opencl_selector : public device_selector {
done    deviceSelector.h:35:class cpu_selector : public device_selector {
done    deviceSelector.h:44:class gpu_selector : public device_selector {
done    deviceSelector.h:53:class host_selector : public device_selector {
done    deviceSelectorInterface.h:17:class device_selector {
done    event.h:18:class event {
done    exception.h:20:class exception {
done    exception.h:31:class exception_list {
done    exception.h:46:class runtime_error : public exception;
done    exception.h:48:class kernel_error : public runtime_error;
done    exception.h:50:class accessor_error : public runtime_error;
done    exception.h:52:class nd_range_error : public runtime_error;
done    exception.h:54:class event_error : public runtime_error;
done    exception.h:56:class invalid_parameter_error : public runtime_error;
done    exception.h:58:class device_error : public exception;
done    exception.h:60:class compile_program_error : public device_error;
done    exception.h:62:class link_program_error : public device_error;
done    exception.h:64:class invalid_object_error : public device_error;
done    exception.h:66:class memory_allocation_error : public device_error;
done    exception.h:68:class platform_error : public device_error;
done    exception.h:70:class profiling_error : public device_error;
done    exception.h:72:class feature_not_supported : public device_error;
done    group.h:18:class group {
        hitem.h:18:class h_item {
        id.h:18:class id {
        image.h:19:class use_host_ptr {
        image.h:24:class use_mutex {
        image.h:31:class context_bound {
        image.h:78:class image {
        item.h:18:class item {
        kernelWIP.h:17:class kernel {
        multipointer.h:27:class multi_ptr {
        multipointer.h:126:class multi_ptr<VoidType, Space> {
        ndRange.h:18:class nd_range {
        nditem.h:18:class nd_item {
        paramTraits.h:19:class param_traits {
        platform.h:17:class platform {
        pointer.h:19:class multi_ptr;
        priv.h:18:class private_memory {
        programWIP.h:23:class program {
        properties.h:24:class T {
        properties.h:36:class property_list {
        queue.h:17:class queue {
        range.h:18:class range {
        sampler.h:36:class sampler {
        stream.h:65:class stream {
        vec.h:54:class vec {
======  ===
