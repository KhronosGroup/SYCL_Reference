namespace sycl {

enum class aspect {
  host,
  cpu,
  gpu,
  accelerator,
  custom,
  fp16,
  fp64,
  int64_base_atomics,
  int64_extended_atomics,
  image,
  online_compiler,
  online_linker,
  queue_profiling,
  usm_device_allocations,
  usm_host_allocations,
  usm_shared_allocations,
  usm_restricted_shared_allocations,
  usm_system_allocator
};

} // namespace sycl
