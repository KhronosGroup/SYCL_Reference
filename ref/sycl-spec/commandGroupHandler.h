// Copyright (c) 2011-2020 The Khronos Group, Inc.
//
// Licensed under the Apache License, Version 2.0 (the License);
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an AS IS BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

namespace sycl {

class handler {
 private:

  // implementation defined constructor
  handler(___unspecified___);

 public:

  template <typename dataT, int dimensions, access::mode accessMode,
    access::target accessTarget, access::placeholder isPlaceholder>
  void require(accessor<dataT, dimensions, accessMode, accessTarget,
               isPlaceholder> acc);

  //----- OpenCL interoperability interface
  //
  template <typename T>
  void set_arg(int argIndex, T && arg);

  template <typename... Ts>
  void set_args(Ts &&... args);

  //------ Kernel dispatch API
  //
  // Note: In all kernel dispatch functions, the template parameter
  // "typename kernelName" is optional.
  //
  template <typename KernelName, typename KernelType>
  void single_task(const KernelType &kernelFunc);

  template <typename KernelName, typename KernelType, int dimensions>
  void parallel_for(range<dimensions> numWorkItems, const KernelType &kernelFunc);

  template <typename KernelName, typename KernelType, int dimensions>
  void parallel_for(range<dimensions> numWorkItems,
                    id<dimensions> workItemOffset, const KernelType &kernelFunc);

  template <typename KernelName, typename KernelType, int dimensions>
  void parallel_for(nd_range<dimensions> executionRange, const KernelType &kernelFunc);

  template <typename KernelName, typename WorkgroupFunctionType, int dimensions>
  void parallel_for_work_group(range<dimensions> numWorkGroups,
                               const WorkgroupFunctionType &kernelFunc);

  template <typename KernelName, typename WorkgroupFunctionType, int dimensions>
  void parallel_for_work_group(range<dimensions> numWorkGroups,
                               range<dimensions> workGroupSize,
                               const WorkgroupFunctionType &kernelFunc);

  void single_task(kernel syclKernel);

  template <int dimensions>
  void parallel_for(range<dimensions> numWorkItems, kernel syclKernel);

  template <int dimensions>
  void parallel_for(range<dimensions> numWorkItems,
                    id<dimensions> workItemOffset, kernel syclKernel);

  template <int dimensions>
  void parallel_for(nd_range<dimensions> ndRange, kernel syclKernel);

  //------ Explicit memory operation APIs
  //
  template <typename T_src, int dim_src, access::mode mode_src, access::target tgt_src, access::placeholder isPlaceholder,
            typename T_dest>
  void copy(accessor<T_src, dim_src, mode_src, tgt_src, isPlaceholder> src,
            std::shared_ptr<T_dest> dest);

  template <typename T_src,
            typename T_dest, int dim_dest, access::mode mode_dest, access::target tgt_dest, access::placeholder isPlaceholder>
  void copy(std::shared_ptr<T_src> src,
            accessor<T_dest, dim_dest, mode_dest, tgt_dest, isPlaceholder> dest);

  template <typename T_src, int dim_src, access::mode mode_src, access::target tgt_src, access::placeholder isPlaceholder,
            typename T_dest>
  void copy(accessor<T_src, dim_src, mode_src, tgt_src, isPlaceholder> src,
            T_dest *dest);

  template <typename T_src,
            typename T_dest, int dim_dest, access::mode mode_dest, access::target tgt_dest, access::placeholder isPlaceholder>
  void copy(const T_src *src,
            accessor<T_dest, dim_dest, mode_dest, tgt_dest, isPlaceholder> dest);

  template <typename T_src, int dim_src, access::mode mode_src, access::target tgt_src, access::placeholder isPlaceholder_src,
            typename T_dest, int dim_dest, access::mode mode_dest, access::target tgt_dest, access::placeholder isPlaceholder_dest>
  void copy(accessor<T_src, dim_src, mode_src, tgt_src, isPlaceholder_src> src,
            accessor<T_dest, dim_dest, mode_dest, tgt_dest, isPlaceholder_dest> dest);

  template <typename T, int dim, access::mode mode, access::target tgt, access::placeholder isPlaceholder>
  void update_host(accessor<T, dim, mode, tgt, isPlaceholder> acc);

  template <typename T, int dim, access::mode mode, access::target tgt, access::placeholder isPlaceholder>
  void fill(accessor<T, dim, mode, tgt, isPlaceholder> dest, const T& src);

  void use_module(const module<module_state::executable> &execModule);

  template <typename T>
  void use_module(const module<module_state::executable> &execModule
                  T deviceImageSelector);

  template<auto& S>
  bool has_specialization_constant() const noexcept;

  template<auto& S>
  typename std::remove_reference_t<decltype(S)>::type get_specialization_constant();

};
}  // namespace sycl
