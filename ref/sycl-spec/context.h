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
class context {
 public:
  explicit context(const property_list &propList = {});

  explicit context(async_handler asyncHandler,
                   const property_list &propList = {});

  explicit context(const device &dev, const property_list &propList = {});

  explicit context(const device &dev, async_handler asyncHandler,
                   const property_list &propList = {});

  explicit context(const std::vector<device> &deviceList,
                   const property_list &propList = {});

  explicit context(const std::vector<device> &deviceList,
                   async_handler asyncHandler,
                   const property_list &propList = {});

  /* -- property interface members -- */

  /* -- common interface members -- */

  backend get_backend() const;

  bool is_host() const;

  platform get_platform() const;

  std::vector<device> get_devices() const;

  template <info::context param>
  typename info::param_traits<info::context, param>::return_type get_info() const;

  template <typename BackendEnum, BackendEnum param>
  typename info::param_traits<BackendEnum, param>::return_type
  get_backend_info() const;
};
}  // namespace sycl
