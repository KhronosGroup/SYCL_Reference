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
template <access_mode>
struct mode_tag_t {
  explicit mode_tag_t() = default;
};

inline constexpr mode_tag_t<access_mode::read>       read_only{};
inline constexpr mode_tag_t<access_mode::read_write> read_write{};
inline constexpr mode_tag_t<access_mode::write>      write_only{};

template <access_mode, target>
struct mode_target_tag_t {
  explicit mode_target_tag_t() = default;
};

inline constexpr mode_target_tag_t<access_mode::read, target::constant_buffer> read_constant{};
}  // namespace sycl
