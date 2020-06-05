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

template <typename dataT,
          int dimensions,
          access::mode accessMode,
          access::target accessTarget>
class accessor {
 public:
  using value_type = dataT;
  using reference = dataT &;
  using const_reference = const dataT &;

  /* Available only when: accessTarget == access::target::host_unsampled_image */
  template <typename AllocatorT>
  accessor(unsampled_image<dimensions, AllocatorT> &imageRef);

  /* Available only when: accessTarget == access::target::host_sampled_image */
  template <typename AllocatorT>
  accessor(sampled_image<dimensions, AllocatorT> &imageRef);

  /* Available only when: accessTarget == access::target::unsampled_image */
  template <typename AllocatorT>
  accessor(unsampled_image<dimensions, AllocatorT> &imageRef,
    handler &commandGroupHandlerRef);

  /* Available only when: accessTarget == access::target::sampled_image */
  template <typename AllocatorT>
  accessor(sampled_image<dimensions, AllocatorT> &imageRef,
    handler &commandGroupHandlerRef);

  /* -- common interface members -- */

  /* -- property interface members -- */

  size_t get_count() const;

  /* Available only when: (accessTarget == access::target::unsampled_image &&
  accessMode == access::mode::read) || (accessTarget ==
  access::target::host_unsampled_image && accessMode == access::mode::read)
  if dimensions == 1, coordT = int
  if dimensions == 2, coordT = int2
  if dimensions == 4, coordT = int4 */
  template <typename coordT>
  dataT read(const coordT &coords) const noexcept;

  /* Available only when: (accessTarget == access::target::sampled_image &&
  accessMode == access::mode::read) || (accessTarget ==
  access::target::host_sampled_image && accessMode == access::mode::read)
  if dimensions == 1, coordT = float
  if dimensions == 2, coordT = float2
  if dimensions == 3, coordT = float4 */
  template <typename coordT>
  dataT read(const coordT &coords) const noexcept;

  /* Available only when: (accessTarget == access::target::unsampled_image &&
  (accessMode == access::mode::write || accessMode == access::mode::discard_write)) ||
  (accessTarget == access::target::host_unsampled_image && (accessMode == access::mode::write ||
  accessMode == access::mode::discard_write))
  if dimensions == 1, coordT = int
  if dimensions == 2, coordT = int2
  if dimensions == 3, coordT = int4 */
  template <typename coordT>
  void write(const coordT &coords, const dataT &color) const;
};
}  // namespace sycl
