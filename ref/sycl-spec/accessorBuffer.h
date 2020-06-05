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
          access::mode accessmode,
          access::target accessTarget,
          access::placeholder isPlaceholder>
class accessor {
 public:
  template <access::decorated IsDecorated>
  using accessor_ptr =   // Corresponds to the target address space,
      __pointer_class__; // is pointer-to-const
                         // when (accessmode == access::mode::read);
  using value_type =  // const dataT when (accessmode == access::mode::read),
      __value_type__; // dataT otherwise
  using reference =       // const dataT& when (accessmode == access::mode::read),
      __reference_type__; // dataT& otherwise
  using const_reference = const dataT &;
  using iterator =      // Corresponds to the target address space,
      __pointer_type__; // is pointer-to-const
                        // when (accessmode == access::mode::read)
  using const_iterator =
      __pointer_to_const_type__; // Corresponds to the target address space
  using reverse_iterator = std::reverse_iterator<iterator>;
  using const_reverse_iterator = std::reverse_iterator<const_iterator>;
  using difference_type =
      typename std::iterator_traits<iterator>::difference_type;
  using size_type = size_t;

  accessor();

  /* Available only when: (dimensions == 0) */
  template <typename AllocatorT>
  accessor(buffer<dataT, 1, AllocatorT> &bufferRef,
           const property_list &propList = {});

  /* Available only when: (dimensions == 0) */
  template <typename AllocatorT>
  accessor(buffer<dataT, 1, AllocatorT> &bufferRef,
           handler &commandGroupHandlerRef, const property_list &propList = {});

  /* Available only when: (dimensions > 0) */
  template <typename AllocatorT>
  accessor(buffer<dataT, dimensions, AllocatorT> &bufferRef,
           const property_list &propList = {});

  /* Available only when: (dimensions > 0) */
  template <typename AllocatorT, typename TagT>
  accessor(buffer<dataT, dimensions, AllocatorT> &bufferRef, TagT tag,
           const property_list &propList = {});

  /* Available only when: (dimensions > 0) */
  template <typename AllocatorT>
  accessor(buffer<dataT, dimensions, AllocatorT> &bufferRef,
           handler &commandGroupHandlerRef, const property_list &propList = {});

  /* Available only when: (dimensions > 0) */
  template <typename AllocatorT, typename TagT>
  accessor(buffer<dataT, dimensions, AllocatorT> &bufferRef,
           handler &commandGroupHandlerRef, TagT tag,
           const property_list &propList = {});

  /* Available only when: (dimensions > 0) */
  template <typename AllocatorT>
  accessor(buffer<dataT, dimensions, AllocatorT> &bufferRef,
           range<dimensions> accessRange, const property_list &propList = {});

  /* Available only when: (dimensions > 0) */
  template <typename AllocatorT, typename TagT>
  accessor(buffer<dataT, dimensions, AllocatorT> &bufferRef,
           range<dimensions> accessRange, TagT tag,
           const property_list &propList = {});

  /* Available only when: (dimensions > 0) */
  template <typename AllocatorT>
  accessor(buffer<dataT, dimensions, AllocatorT> &bufferRef,
           range<dimensions> accessRange, id<dimensions> accessOffset,
           const property_list &propList = {});

  /* Available only when: (dimensions > 0) */
  template <typename AllocatorT, typename TagT>
  accessor(buffer<dataT, dimensions, AllocatorT> &bufferRef,
           range<dimensions> accessRange, id<dimensions> accessOffset,
           TagT tag, const property_list &propList = {});

  /* Available only when: (dimensions > 0) */
  template <typename AllocatorT>
  accessor(buffer<dataT, dimensions, AllocatorT> &bufferRef,
           handler &commandGroupHandlerRef, range<dimensions> accessRange,
           const property_list &propList = {});

  /* Available only when: (dimensions > 0) */
  template <typename AllocatorT, typename TagT>
  accessor(buffer<dataT, dimensions, AllocatorT> &bufferRef,
           handler &commandGroupHandlerRef, range<dimensions> accessRange,
           TagT tag, const property_list &propList = {});

  /* Available only when: (dimensions > 0) */
  template <typename AllocatorT>
  accessor(buffer<dataT, dimensions, AllocatorT> &bufferRef,
           handler &commandGroupHandlerRef, range<dimensions> accessRange,
           id<dimensions> accessOffset, const property_list &propList = {});

  /* Available only when: (dimensions > 0) */
  template <typename AllocatorT, typename TagT>
  accessor(buffer<dataT, dimensions, AllocatorT> &bufferRef,
           handler &commandGroupHandlerRef, range<dimensions> accessRange,
           id<dimensions> accessOffset, TagT tag,
           const property_list &propList = {});

  /* -- common interface members -- */

  void swap(accessor &other);

  bool is_placeholder() const;

  size_type byte_size() const noexcept;

  size_type size() const noexcept;

  size_type max_size() const noexcept;

  size_type get_count() const noexcept;

  bool empty() const noexcept;

  /* Available only when: dimensions > 0 */
  range<dimensions> get_range() const;

  /* Available only when: dimensions > 0 */
  id<dimensions> get_offset() const;

  /* Available only when: (dimensions == 0) */
  operator reference() const;

  /* Available only when: (dimensions > 0) */
  reference operator[](id<dimensions> index) const;

  /* Deprecated in SYCL 2020
  Available only when: accessMode == access::mode::atomic && dimensions ==  0 */
  operator cl::sycl::atomic<dataT, access::address_space::global_space> () const;

  /* Deprecated in SYCL 2020
  Available only when: accessMode == access::mode::atomic && dimensions > 0 */
  cl::sycl::atomic<dataT, access::address_space::global_space> operator[](
    id<dimensions> index) const;

  /* Available only when: dimensions > 1 */
  __unspecified__ &operator[](size_t index) const;

  std::add_pointer_t<value_type> get_pointer() const noexcept;

  template <access::decorated IsDecorated>
  accessor_ptr<IsDecorated> get_multi_ptr() const noexcept;

  iterator data() const noexcept;

  iterator begin() const noexcept;

  iterator end() const noexcept;

  const_iterator cbegin() const noexcept;

  const_iterator cend() const noexcept;
};

}  // namespace sycl
