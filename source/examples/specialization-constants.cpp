// SPDX-FileCopyrightText: 2024 The Khronos Group Inc.
//
// SPDX-License-Identifier: Apache-2.0

#include <sycl/sycl.hpp>

using coeff_t = std::array<std::array<float, 3>, 3>;

// Identify the specialization constant.
constexpr sycl::specialization_id<coeff_t> coeff_id;

// Function to get coefficients (in this case, a simple example)
coeff_t get_coefficients() {
  // Read coefficients from somewhere or generate them
  return {{{1.0f, 2.0f, 1.0f}, {0.0f, 0.0f, 0.0f}, {-1.0f, -2.0f, -1.0f}}};
}

// Convolution kernel function
void do_conv(sycl::buffer<float, 2> &in, sycl::buffer<float, 2> &out,
             coeff_t coefficients) {
  sycl::property_list properties{sycl::property::queue::enable_profiling()};
  auto myQueue = sycl::queue(sycl::default_selector_v, properties);

  myQueue.submit([&](sycl::handler &cgh) {
    sycl::accessor in_acc{in, cgh, sycl::read_only};
    sycl::accessor out_acc{out, cgh, sycl::write_only};

    // Set the coefficient of the convolution as constant.
    // This will build a specific kernel the coefficient available as literals.
    cgh.set_specialization_constant<coeff_id>(get_coefficients());

    cgh.parallel_for<class Convolution>(
        in.get_range(), [=](sycl::item<2> item_id, sycl::kernel_handler h) {
          float acc = 0;
          coeff_t coeff = h.get_specialization_constant<coeff_id>();
          for (int i = -1; i <= 1; i++) {
            if (item_id[0] + i < 0 || item_id[0] + i >= in_acc.get_range()[0])
              continue;
            for (int j = -1; j <= 1; j++) {
              if (item_id[1] + j < 0 || item_id[1] + j >= in_acc.get_range()[1])
                continue;
              // The underlying JIT can see all the values of the array returned
              // by coeff.get().
              acc +=
                  coeff[i + 1][j + 1] * in_acc[item_id[0] + i][item_id[1] + j];
            }
          }
          out_acc[item_id] = acc;
        });
  });

  myQueue.wait();
}

void printResults(sycl::buffer<float, 2> &input_buf,
                  sycl::buffer<float, 2> &output_buf,
                  const coeff_t &coefficients, size_t width, size_t height) {
  auto accessorIn = input_buf.get_access<sycl::access::mode::read>();
  auto accessorOut = output_buf.get_access<sycl::access::mode::read>();

  std::cout << "Input:" << std::endl;
  for (size_t y = 0; y < height; ++y) {
    for (size_t x = 0; x < width; ++x) {
      std::cout << accessorIn[x][y] << " ";
    }
    std::cout << std::endl;
  }

  std::cout << "\nOutput after convolution:" << std::endl;
  for (size_t y = 0; y < height; ++y) {
    for (size_t x = 0; x < width; ++x) {
      std::cout << accessorOut[x][y] << " ";
    }
    std::cout << std::endl;
  }

  std::cout << "\nCoefficients:" << std::endl;
  for (const auto &row : coefficients) {
    for (const auto &value : row) {
      std::cout << value << " ";
    }
    std::cout << std::endl;
  }
}

int main() {
  constexpr size_t width = 10;
  constexpr size_t height = 10;

  // Create input and output buffers
  sycl::buffer<float, 2> input_buf(sycl::range<2>(width, height));
  sycl::buffer<float, 2> output_buf(sycl::range<2>(width, height));

  // Get coefficients
  coeff_t coefficients = get_coefficients();

  // Call convolution function
  do_conv(input_buf, output_buf, coefficients);

  // Print input, output, and coefficients using printResults function
  printResults(input_buf, output_buf, coefficients, width, height);

  return 0;
}
