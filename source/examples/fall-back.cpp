#include<CL/sycl.hpp>
#include<iostream>

const int N = 1024;
const int M = 32;

using namespace sycl;

int main(){
  cpu_selector cpuSelector;
  queue cpuQueue(cpuSelector);
  queue defaultqueue;
  buffer<int,2> buf(range<2>(N,N));

  defaultqueue.submit([&](handler &h){
      auto bufacc = buf.get_access<access::mode::read_write>(h);
      h.parallel_for(nd_range<2>(range<2>(N,N), range<2>(M,M)),
		     [=](nd_item<2> i){
		       id<2> ind = i.get_global_id();
		       bufacc[ind[0]][ind[1]] = ind[0]+ind[1];
		     });
    }, cpuQueue);
  auto bufacc1 = buf.get_access<access::mode::read>();
  for(int i = 0; i < N; i++){
    for(int j = 0; j < N; j++){
      if(bufacc1[i][j] != i+j){
	std::cout<<"Wrong result\n";
	return 1;
      }
    }
  }
  std::cout<<"Correct results\n";
  return 0;
}
