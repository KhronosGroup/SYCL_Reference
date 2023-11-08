// SPDX-FileCopyrightText: 2023 The Khronos Group Inc.
//
// SPDX-License-Identifier: Apache-2.0

#include <sycl/sycl.hpp>

#include <iostream>

int main() {
  
  // Create 2-d buffer with 8x8 ints
  sycl::buffer<int, 2> parent_buffer { sycl::range<2> { 8, 8 } };

  try
  {
    // OK: Contiguous region from middle of buffer
    sycl::buffer<int, 2> sub_buf1 { parent_buffer, /*offset*/ sycl::range<2> { 2, 0 },
                                                     /*size*/ sycl::range<2> { 2, 8 } };

    std::cout << "sub_buf1 created successfully" << std::endl;
  }
  catch(const sycl::exception& e)
  {
    std::cerr << "Exception while creating sub_buf1: " << e.what() << std::endl;
  }
  
  try
  {
    // invalid exception: Non-contiguous regions of 2-d buffer
    sycl::buffer<int, 2> sub_buf2 { parent_buffer, /*offset*/ sycl::range<2> { 2, 0 },
                                                     /*size*/ sycl::range<2> { 2, 2 } };

    std::cout << "sub_buf2 created successfully" << std::endl;
  }
  catch(const sycl::exception& e)
  {
    std::cerr << "Exception while creating sub_buf2: " << e.what() << std::endl;
  }

  try
  {
    // invalid exception: Non-contiguous regions of 2-d buffer
    sycl::buffer<int, 2> sub_buf3 { parent_buffer, /*offset*/ sycl::range<2> { 2, 2 },
                                                     /*size*/ sycl::range<2> { 2, 6 } };

    std::cout << "sub_buf3 created successfully" << std::endl;
  }
  catch(const sycl::exception& e)
  {
    std::cerr << "Exception while creating sub_buf3: " << e.what() << std::endl;
  }

  try
  {
    // invalid exception: Out-of-bounds size
    sycl::buffer<int, 2> sub_buf4 { parent_buffer, /*offset*/ sycl::range<2> { 2, 2 },
                                                     /*size*/ sycl::range<2> { 2, 8 } };

    std::cout << "sub_buf4 created successfully" << std::endl;
  }
  catch(const sycl::exception& e)
  {
    std::cerr << "Exception while creating sub_buf4: " << e.what() << std::endl;
  }

  return 0;
}
