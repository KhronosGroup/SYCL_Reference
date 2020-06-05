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

using async_handler = std::function<void(sycl::exception_list)>;

class exception : public virtual std::exception {
 public:
    exception(std::error_code ec, const std::string& what_arg);
    exception(std::error_code ec, const char * what_arg);
    exception(std::error_code ec);
    exception(int ev, const std::error_category& ecat, const std::string& what_arg);
    exception(int ev, const std::error_category& ecat, const char* what_arg);
    exception(int ev, const std::error_category& ecat);

    exception(context ctx, std::error_code ec, const std::string& what_arg);
    exception(context ctx, std::error_code ec, const char* what_arg);
    exception(context ctx, std::error_code ec);
    exception(context ctx, int ev, const std::error_category& ecat, const std::string& what_arg);
    exception(context ctx, int ev, const std::error_category& ecat, const char* what_arg);
    exception(context ctx, int ev, const std::error_category& ecat);

    const std::error_code& code() const noexcept;
    const std::error_category& category() const noexcept;

    bool has_context() const noexcept;
    context get_context() const;
};

class exception_list {
  // Used as a container for a list of asynchronous exceptions
 public:
  using value_type = std::exception_ptr;
  using reference = value_type&;
  using const_reference = const value_type&;
  using size_type = std::size_t;
  using iterator = /*unspecified*/;
  using const_iterator = /*unspecified*/;

  size_type size() const;
  iterator begin() const;  // first asynchronous exception
  iterator end() const;    // refer to past-the-end last asynchronous exception
};

enum class errc {
  runtime_error = /* implementation-defined */,
  kernel = /* implementation-defined */,
  accessor = /* implementation-defined */,
  nd_range = /* implementation-defined */,
  event = /* implementation-defined */,
  invalid_parameter = /* implementation-defined */,
  compile_program = /* implementation-defined */,
  link_program = /* implementation-defined */,
  invalid_object = /* implementation-defined */,
  memory_allocation = /* implementation-defined */,
  platform = /* implementation-defined */,
  profiling = /* implementation-defined */,
  feature_not_supported = /* implementation-defined */
};

template<backend b>
using errc_for = typename backend_traits<b>::errc;

std::error_condition make_error_condition(errc e) noexcept;
std::error_code make_error_code(errc e) noexcept;

const std::error_category& sycl_category() noexcept;

template<backend b>
const std::error_category& error_category_for() noexcept;

}  // namespace sycl

namespace std {

  template <>
  struct is_error_condition_enum<sycl::errc> : true_type {};

  template <>
  struct is_error_code_enum<see-below> : true_type {};

}  // namespace std
