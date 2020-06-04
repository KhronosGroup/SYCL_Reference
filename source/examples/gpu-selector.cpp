#include <CL/sycl.hpp>

using namespace cl::sycl;

int main() {
  device d;
  
  try {
    d = device(gpu_selector());
  } catch (exception const& e) {
    std::cout << "Cannot select a GPU\n" << e.what() << "\n";
    std::cout << "Using a CPU device\n";
    d = device(cpu_selector());
  }

  std::cout << "Using " << d.get_info<sycl::info::device::name>();
}
