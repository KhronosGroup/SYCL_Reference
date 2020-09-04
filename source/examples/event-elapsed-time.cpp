#include <CL/sycl.hpp>

int main() {
  auto q = sycl::queue(sycl::gpu_selector());

  const int bytes = 1024 * 1024;

  // Alloc memory on host
  auto src = aligned_alloc(8, bytes);
  memset(src, 1, bytes);

  // Alloc memory on device
  auto dst = sycl::malloc_device(bytes, q);
  q.memset(dst, 0, bytes).wait();

  // Copy from host to device
  auto event = q.memcpy(dst, src, bytes);
  event.wait();

  auto end = event.get_profiling_info<sycl::info::event_profiling::command_end>();
  auto start = event.get_profiling_info<sycl::info::event_profiling::command_start>();

  std::cout << "Elapsed time: " << (end-start)/1.0e9 << " seconds\n";
}
