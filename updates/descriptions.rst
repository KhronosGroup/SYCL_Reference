..
  Copyright 2020 The Khronos Group Inc.
  SPDX-License-Identifier: CC-BY-4.0

======  ===
Intel   object
======  ===
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
        class: handler
          member: require
          member: set_arg
          member: set_args
          member: single_task
          member: parallel_for
          member: copy
          member: update_host
          member: fill
        class: command_group
          member: (constructors)
          member: events
done    class: Context
done      member: (constructors)
don       member: get
done      member: is_host
done      member: get_platform
done      member: get_devices
done      member: get_info
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
        class: exception_list
          member: size
          member: begin
          member: end
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
        class: Image accessor
          member: (constructors)
          member: get_count
          member: get_range
          member: read
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
done    class: platform
done      member: (constructor)
done      member: get
done      member: get_devices
done      member: get_info
done      member: has_extension
done      member: is_host
done      member: get_platforms
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
