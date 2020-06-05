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
  template <typename value_type, access::decorated IsDecorated>
  using accessor_ptr = multi_ptr<value_type, access::address_space::local_space, IsDecorated>;
  using value_type = dataT;
  using reference = dataT &;
  using const_reference = const dataT &;
  using iterator = accessor_ptr<dataT, access::decorated::no>;
  using const_iterator = accessor_ptr<const dataT, access::decorated::no>;
  using reverse_iterator = std::reverse_iterator<iterator>;
  using const_reverse_iterator = std::reverse_iterator<const_iterator>;
  using difference_type =
      typename std::iterator_traits<iterator>::difference_type;
  using size_type = size_t;

  accessor();

  /* Available only when: dimensions == 0 */
  accessor(handler &commandGroupHandlerRef,
           const property_list &propList = {});

  /* Available only when: dimensions > 0 */
  accessor(range<dimensions> allocationSize, handler &commandGroupHandlerRef,
           const property_list &propList = {});

  /* -- common interface members -- */

  void swap(accessor &other);

  size_type byte_size() const noexcept;

  size_type size() const noexcept;

  size_type max_size() const noexcept;

  size_type get_count() const noexcept;

  bool empty() const noexcept;

  range<dimensions> get_range() const;

  /* Available only when: (dimensions == 0) */
  operator reference() const;

  /* Available only when: (dimensions > 0) */
  reference operator[](id<dimensions> index) const;

  /* Deprecated in SYCL 2020
  Available only when: accessMode == access::mode::atomic && dimensions ==  0 */
  operator cl::sycl::atomic<dataT,access::address_space::local_space> () const;

  /* Deprecated in SYCL 2020
  Available only when: accessMode == access::mode::atomic && dimensions > 0 */
  cl::sycl::atomic<dataT, access::address_space::local_space> operator[](
    id<dimensions> index) const;

  /* Available only when: dimensions > 1 */
  __unspecified__ &operator[](size_t index) const;

  std::add_pointer_t<value_type> get_pointer() const noexcept;

  template <access::decorated IsDecorated>
  accessor_ptr<value_type, IsDecorated> get_multi_ptr() const noexcept;

  iterator data() const noexcept;

  iterator begin() const noexcept;

  iterator end() const noexcept;

  const_iterator cbegin() const noexcept;

  const_iterator cend() const noexcept;

  reverse_iterator rbegin() const noexcept;

  reverse_iterator rend() const noexcept;

  const_reverse_iterator crbegin() const noexcept;

  const_reverse_iterator crend() const noexcept;
};
}  // namespace sycl
