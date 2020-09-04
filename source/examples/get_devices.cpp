#include <CL/sycl.hpp>

int main() {
  for (auto device : sycl::device::get_devices(sycl::info::device_type::gpu)) {
    std::cout << "  Device: "
	      << device.get_info<sycl::info::device::name>()
	      << std::endl;
  }
}
