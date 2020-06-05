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
template <int Dimensions = 1>
class group {
public:

  using id_type = id<Dimensions>;
  using range_type = range<Dimensions>;
  using linear_id_type = size_t;
  static constexpr int dimensions = Dimensions;

   /* -- common interface members -- */

  id<Dimensions> get_group_id() const;

  size_t get_group_id(int dimension) const;

  id<Dimensions> get_local_id() const;

  size_t get_local_id(int dimension) const;

  range<Dimensions> get_local_range() const;

  size_t get_local_range(int dimension) const;

  range<Dimensions> get_group_range() const;

  size_t get_group_range(int dimension) const;

  range<Dimensions> get_max_local_range() const;

  range<Dimensions> get_uniform_group_range() const;

  size_t operator[](int dimension) const;

  size_t get_group_linear_id() const;

  size_t get_local_linear_id() const;

  size_t get_group_linear_range() const;

  size_t get_local_linear_range() const;

  template<typename workItemFunctionT>
  void parallel_for_work_item(const workItemFunctionT &func) const;

  template<typename workItemFunctionT>
  void parallel_for_work_item(range<dimensions> logicalRange,
    const workItemFunctionT &func) const;

  template <typename dataT>
  device_event async_work_group_copy(decorated_local_ptr<dataT> dest,
    decorated_global_ptr<dataT> src, size_t numElements) const;

  template <typename dataT>
  device_event async_work_group_copy(decorated_global_ptr<dataT> dest,
    decorated_local_ptr<dataT> src, size_t numElements) const;

  template <typename dataT>
  device_event async_work_group_copy(decorated_local_ptr<dataT> dest,
    decorated_global_ptr<dataT> src, size_t numElements, size_t srcStride) const;

  template <typename dataT>
  device_event async_work_group_copy(decorated_global_ptr<dataT> dest,
    decorated_local_ptr<dataT> src, size_t numElements, size_t destStride) const;

  template <typename... eventTN>
  void wait_for(eventTN... events) const;
};
}  // sycl
