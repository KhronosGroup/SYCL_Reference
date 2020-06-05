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
          access::mode accessmode>
class host_accessor {
 public:
  using value_type =  // const dataT when (accessmode == access::mode::read),
      __value_type__; // dataT otherwise
  using reference =       // const dataT& when (accessmode == access::mode::read),
      __reference_type__; // dataT& otherwise
  using const_reference = const dataT &;
  using iterator =      // const dataT* when (accessmode == access::mode::read),
      __pointer_type__; // dataT* otherwise
  using const_iterator = const dataT *;
  using difference_type =
      typename std::iterator_traits<iterator>::difference_type;
  using size_type = size_t;

  host_accessor();

  /* Available only when: (dimensions == 0) */
  template <typename AllocatorT>
  host_accessor(buffer<dataT, 1, AllocatorT> &bufferRef,
                const property_list &propList = {});

  /* Available only when: (dimensions == 0) */
  template <typename AllocatorT>
  host_accessor(buffer<dataT, 1, AllocatorT> &bufferRef,
                handler &commandGroupHandlerRef, const property_list &propList = {});

  /* Available only when: (dimensions > 0) */
  template <typename AllocatorT>
  host_accessor(buffer<dataT, dimensions, AllocatorT> &bufferRef,
                const property_list &propList = {});

  /* Available only when: (dimensions > 0) */
  template <typename AllocatorT, typename TagT>
  host_accessor(buffer<dataT, dimensions, AllocatorT> &bufferRef, TagT tag,
                const property_list &propList = {});

  /* Available only when: (dimensions > 0) */
  template <typename AllocatorT>
  host_accessor(buffer<dataT, dimensions, AllocatorT> &bufferRef,
                handler &commandGroupHandlerRef, const property_list &propList = {});

  /* Available only when: (dimensions > 0) */
  template <typename AllocatorT, typename TagT>
  host_accessor(buffer<dataT, dimensions, AllocatorT> &bufferRef,
                handler &commandGroupHandlerRef, TagT tag,
                const property_list &propList = {});

  /* Available only when: (dimensions > 0) */
  template <typename AllocatorT>
  host_accessor(buffer<dataT, dimensions, AllocatorT> &bufferRef,
                range<dimensions> accessRange, const property_list &propList = {});

  /* Available only when: (dimensions > 0) */
  template <typename AllocatorT, typename TagT>
  host_accessor(buffer<dataT, dimensions, AllocatorT> &bufferRef,
                range<dimensions> accessRange, TagT tag,
                const property_list &propList = {});

  /* Available only when: (dimensions > 0) */
  template <typename AllocatorT>
  host_accessor(buffer<dataT, dimensions, AllocatorT> &bufferRef,
                range<dimensions> accessRange, id<dimensions> accessOffset,
                const property_list &propList = {});

  /* Available only when: (dimensions > 0) */
  template <typename AllocatorT, typename TagT>
  host_accessor(buffer<dataT, dimensions, AllocatorT> &bufferRef,
                range<dimensions> accessRange, id<dimensions> accessOffset,
                TagT tag, const property_list &propList = {});

  /* Available only when: (dimensions > 0) */
  template <typename AllocatorT>
  host_accessor(buffer<dataT, dimensions, AllocatorT> &bufferRef,
                handler &commandGroupHandlerRef, range<dimensions> accessRange,
                const property_list &propList = {});

  /* Available only when: (dimensions > 0) */
  template <typename AllocatorT, typename TagT>
  host_accessor(buffer<dataT, dimensions, AllocatorT> &bufferRef,
                handler &commandGroupHandlerRef, range<dimensions> accessRange,
                TagT tag, const property_list &propList = {});

  /* Available only when: (dimensions > 0) */
  template <typename AllocatorT>
  host_accessor(buffer<dataT, dimensions, AllocatorT> &bufferRef,
                handler &commandGroupHandlerRef, range<dimensions> accessRange,
                id<dimensions> accessOffset, const property_list &propList = {});

  /* Available only when: (dimensions > 0) */
  template <typename AllocatorT, typename TagT>
  host_accessor(buffer<dataT, dimensions, AllocatorT> &bufferRef,
                handler &commandGroupHandlerRef, range<dimensions> accessRange,
                id<dimensions> accessOffset, TagT tag,
                const property_list &propList = {});

  /* -- common interface members -- */

  void swap(host_accessor &other);

  size_type byte_size() const noexcept;

  size_type size() const noexcept;

  size_type max_size() const noexcept;

  bool empty() const noexcept;

  /* Available only when: dimensions > 0 */
  range<dimensions> get_range() const;

  /* Available only when: dimensions > 0 */
  id<dimensions> get_offset() const;

  /* Available only when: (dimensions == 0) */
  operator reference() const;

  /* Available only when: (dimensions > 0) */
  reference operator[](id<dimensions> index) const;

  /* Available only when: dimensions > 1 */
  __unspecified__ &operator[](size_t index) const;

  iterator data() const noexcept;

  iterator begin() const noexcept;

  iterator end() const noexcept;

  const_iterator cbegin() const noexcept;

  const_iterator cend() const noexcept;
};
}  // namespace sycl
