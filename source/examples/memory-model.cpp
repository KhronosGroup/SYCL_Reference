#include <CL/sycl.hpp>

using namespace sycl;

const int SIZE = 64;

int main() {
  std::array<int, SIZE> a, c;
  std::array<sycl::float4, SIZE> b;
  for (int i = 0; i<SIZE; ++i) {
    a[i] = i;
    b[i] = (float)-i;
    c[i] = i;
  }

  {
    range<1> a_size{SIZE};
    queue q;

    buffer<int>  a_device(a.data(), a_size);
    buffer<int>  c_device(c.data(), a_size);
    image<2>  b_device(b.data(),image_channel_order::rgba,
		       image_channel_type::fp32, range<2>(8, 8));

    q.submit([&](handler &h) {
	accessor<int, 1, access::mode::discard_write,
		 access::target::global_buffer> c_res(c_device, h);
	accessor<int, 1, access::mode::read,
		 access::target::constant_buffer> a_res(a_device, h);
	accessor<float4, 2, access::mode::write,
		 access::target::image> b_res(b_device, h);

	float4 init = {0.f, 0.f, 0.f, 0.f};

	h.parallel_for(a_size,[=](id<1> idx) {
	    c_res[idx] = a_res[idx];
	    b_res.write(int2(0,0), init);
	  });
      });
  }
  return 0;
} 
