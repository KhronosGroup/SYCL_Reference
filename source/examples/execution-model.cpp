#include<CL/sycl.hpp>
#include<iostream>

using namespace cl::sycl;

const int N = 6;
const int M = 2;

int main() {
  queue q;
  buffer<int,2> buf(range<2>(N,N));
  q.submit([&](handler &h){
      auto bufacc = buf.get_access<access::mode::read_write>(h);
      h.parallel_for<class ndim>(nd_range<2>(range<2>(N,N), range<2>(M,M)),
				 [=](nd_item<2> i) {
				   id<2> ind = i.get_global_id();
				   bufacc[ind[0]][ind[1]] = ind[0]+ind[1];
				 });
    });
  auto bufacc1 = buf.get_access<access::mode::read>();
  for(int i = 0; i < N; i++){
    for(int j = 0; j < N; j++)
      std::cout<<bufacc1[i][j]<<"\t";
    std::cout<<"\n";
  }
  return 0;
}
