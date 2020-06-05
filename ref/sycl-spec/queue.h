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
class queue {
 public:
  explicit queue(const property_list &propList = {});

  explicit queue(const async_handler &asyncHandler,
                 const property_list &propList = {});

  template <typename DeviceSelector>
  explicit queue(const DeviceSelector &deviceSelector,
                 const property_list &propList = {});

  template <typename DeviceSelector>
  explicit queue(const DeviceSelector &deviceSelector,
                 const async_handler &asyncHandler,
                 const property_list &propList = {});

  explicit queue(const device &syclDevice, const property_list &propList = {});

  explicit queue(const device &syclDevice, const async_handler &asyncHandler,
                 const property_list &propList = {});

  template <typename DeviceSelector>
  explicit queue(const context &syclContext,
                 const DeviceSelector &deviceSelector,
                 const property_list &propList = {});

  template <typename DeviceSelector>
  explicit queue(const context &syclContext,
                 const DeviceSelector &deviceSelector,
                 const async_handler &asyncHandler,
                 const property_list &propList = {});

  explicit queue(const context &syclContext, const device &syclDevice,
                 const property_list &propList = {});

  explicit queue(const context &syclContext, const device &syclDevice,
                 const async_handler &asyncHandler,
                 const property_list &propList = {});

  /* -- common interface members -- */

  /* -- property interface members -- */

  backend get_backend() const;

  context get_context() const;

  device get_device() const;

  bool is_host() const;

  bool is_in_order() const;

  template <info::queue param>
  typename info::param_traits<info::queue, param>::return_type get_info() const;

  template <typename BackendEnum, BackendEnum param>
  typename info::param_traits<BackendEnum, param>::return_type
  get_backend_info() const;

  template <typename T>
  event submit(T cgf);

  template <typename T>
  event submit(T cgf, const queue &secondaryQueue);

  void wait();

  void wait_and_throw();

  void throw_asynchronous();

  /* -- convenience shortcuts -- */

  template <typename KernelName, typename KernelType>
  event single_task(const KernelType &KernelFunc);

  template <typename KernelName, typename KernelType>
  event single_task(event DepEvent, const KernelType &KernelFunc);

  template <typename KernelName, typename KernelType>
  event single_task(const std::vector<event> &DepEvents,
                    const KernelType &KernelFunc);

  template <typename KernelName, typename KernelType, int Dims>
  event parallel_for(range<Dims> NumWorkItems, const KernelType &KernelFunc);

  template <typename KernelName, typename KernelType, int Dims>
  event parallel_for(range<Dims> NumWorkItems, event DepEvent,
                     const KernelType &KernelFunc);

  template <typename KernelName, typename KernelType, int Dims>
  event parallel_for(range<Dims> NumWorkItems,
                     const std::vector<event> &DepEvents,
                     const KernelType &KernelFunc);

  template <typename KernelName, typename KernelType, int Dims>
  event parallel_for(range<Dims> NumWorkItems, id<Dims> WorkItemOffset,
                     const KernelType &KernelFunc);

  template <typename KernelName, typename KernelType, int Dims>
  event parallel_for(range<Dims> NumWorkItems, id<Dims> WorkItemOffset,
                     event DepEvent, const KernelType &KernelFunc);

  template <typename KernelName, typename KernelType, int Dims>
  event parallel_for(range<Dims> NumWorkItems, id<Dims> WorkItemOffset,
                     const std::vector<event> &DepEvents,
                     const KernelType &KernelFunc);

  template <typename KernelName, typename KernelType, int Dims>
  event parallel_for(nd_range<Dims> ExecutionRange, const KernelType &KernelFunc);

  template <typename KernelName, typename KernelType, int Dims>
  event parallel_for(nd_range<Dims> ExecutionRange, event DepEvent,
                     const KernelType &KernelFunc);

  template <typename KernelName, typename KernelType, int Dims>
  event parallel_for(nd_range<Dims> ExecutionRange,
                     const std::vector<event> &DepEvents,
                     const KernelType &KernelFunc);
};
}  // namespace sycl
