#include <CL/sycl.hpp>
using namespace sycl;

const int SIZE = 10;

void show_platforms() {
  auto platforms = platform::get_platforms();

  for (auto &platform : platforms) {
    std::cout << "Platform: "
	      << platform.get_info<info::platform::name>()
	      << std::endl;

    auto devices = platform.get_devices();
    for (auto &device : devices ) {
      std::cout << "  Device: "
		<< device.get_info<info::device::name>()
		<< std::endl;
    }
  }
}

void vec_add(int *a, int *b, int *c) {
  range<1> a_size{SIZE};

  buffer<int> a_buf(a, a_size);
  buffer<int> b_buf(b, a_size);
  buffer<int> c_buf(c, a_size);

  queue q;

  q.submit([&](handler &h) {
      auto c_res = c_buf.get_access<access::mode::write>(h);
      auto a_in = a_buf.get_access<access::mode::read>(h);
      auto b_in = b_buf.get_access<access::mode::read>(h);

      h.parallel_for(a_size,
		     [=](id<1> idx) {
		       c_res[idx] = a_in[idx] + b_in[idx];
		     });
    });
}

int main() {
  int a[SIZE], b[SIZE], c[SIZE];

  for (int i = 0; i < SIZE; ++i) {
    a[i] = i;
    b[i] = i;
    c[i] = i;
  }

  show_platforms();
  vec_add(a, b, c);

  for (int i = 0; i < SIZE; i++) std::cout << c[i] << std::endl;
  return 0;
}
