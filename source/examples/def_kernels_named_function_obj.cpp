// SPDX-FileCopyrightText: 2023 The Khronos Group Inc.
//
// SPDX-License-Identifier: Apache-2.0

#include <sycl/sycl.hpp>

#include <iostream>
#include <random>

class RandomFiller {
public:
  RandomFiller(sycl::accessor<int> ptr) : ptr_{ptr} {
    std::random_device hwRand;
    std::uniform_int_distribution<> r{1, 100};
    randomNum_ = r(hwRand);
  }
  void operator()(sycl::item<1> item) const {
    ptr_[item.get_id()] = get_random();
  }
  int get_random() const { return randomNum_; }

private:
  sycl::accessor<int> ptr_;
  int randomNum_;
};

void workFunction(sycl::buffer<int, 1> &b, sycl::queue &q,
                  const sycl::range<1> r) {
  q.submit([&](sycl::handler &cgh) {
    sycl::accessor ptr{b, cgh};
    RandomFiller filler{ptr};

    cgh.parallel_for(r, filler);
  });
}

int main() {
  sycl::range<1> buffRange(10);
  sycl::buffer<int> myBuff(buffRange);
  sycl::queue myQueue;

  workFunction(myBuff, myQueue, buffRange);

  auto acc = myBuff.get_host_access();

  for (auto a : acc) {
    std::cout << a << ' ';
  }

  return 0;
}
