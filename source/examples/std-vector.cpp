#include <vector>

#include <CL/sycl.hpp>

using namespace sycl;

const int size = 10;

int main() {
  queue q;

  // USM allocator for data of type int in shared memory
  typedef usm_allocator<int, usm::alloc::shared> vec_alloc;
  // Create allocator for device associated with q
  vec_alloc myAlloc(q);
  // Create std vectors with the allocator
  std::vector<int, vec_alloc >
    a(size, myAlloc),
    b(size, myAlloc),
    c(size, myAlloc);

  // Get pointer to vector data for access in kernel
  auto A = a.data();
  auto B = b.data();
  auto C = c.data();
  
  for (int i = 0; i < size; i++) {
    a[i] = i;
    b[i] = i;
    c[i] = i;
  }

  q.submit([&](handler &cgh) {
      cgh.parallel_for(range<1>(size),
		       [=](id<1> idx) {
			 C[idx] = A[idx] + B[idx];
		       });
    }).wait();

  for (int i = 0; i < size; i++) std::cout << c[i] << std::endl;
  return 0;
}
