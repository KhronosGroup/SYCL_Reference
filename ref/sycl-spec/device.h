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

class device {
 public:
  device();

  template <typename DeviceSelector>
  explicit device(const DeviceSelector &deviceSelector);

  /* -- common interface members -- */

  backend get_backend() const;

  bool is_host() const;

  bool is_cpu() const;

  bool is_gpu() const;

  bool is_accelerator() const;

  platform get_platform() const;

  template <info::device param>
  typename info::param_traits<info::device, param>::return_type
  get_info() const;

  template <typename BackendEnum, BackendEnum param>
  typename info::param_traits<BackendEnum, param>::return_type
  get_backend_info() const;

  bool has(aspect asp) const;

  bool has_extension(const std::string &extension) const; // Deprecated

  // Available only when prop == info::partition_property::partition_equally
  template <info::partition_property prop>
  std::vector<device> create_sub_devices(size_t nbSubDev) const;

  // Available only when prop == info::partition_property::partition_by_counts
  template <info::partition_property prop>
  std::vector<device> create_sub_devices(const std::vector<size_t> &counts) const;

  // Available only when prop == info::partition_property::partition_by_affinity_domain
  template <info::partition_property prop>
  std::vector<device> create_sub_devices(info::affinity_domain affinityDomain) const;

  static std::vector<device> get_devices(
      info::device_type deviceType = info::device_type::all);
};
} // namespace sycl
