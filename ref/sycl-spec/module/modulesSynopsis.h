namespace sycl {

template <typename T>
class specialization_id {
 private:

  specialization_id(const specialization_id& rhs) = delete;

  specialization_id(specialization_id&& rhs) = delete;

  specialization_id &operator=(const specialization_id& rhs) = delete;

  specialization_id &operator=(specialization_id&& rhs) = delete;

 public:

  using value_type = T;

  template<class... Args >
  explicit constexpr specialization_id(Args&&... args);
};

enum class module_state {
  input,
  object,
  executable
};

template<module_state State>
class module {
 private:

  module(__unspecified__);

 public:

  using device_image_type = __unspecified__;

  using device_image_iterator = __unspecified__;

  module() = delete;

  context get_context() const noexcept;

  std::vector<device> get_devices() const noexcept;

  bool has_kernel(std::string kernelName) const noexcept;

  kernel get_kernel(std::string kernelName) const;

  std::vector<std::string> get_kernel_names() const;

  bool is_empty() const noexcept;

  device_image_iterator begin() const;

  device_image_iterator end() const;

  bool contains_specialization_constants() const noexcept;

  bool native_specialization_constant() const noexcept;

  template<auto& S>
  bool has_specialization_constant() const noexcept;

  template<auto& S>
  void set_specialization_constant(
    typename std::remove_reference_t<decltype(S)>::type value);

  template<auto& S>
  typename std::remove_reference_t<decltype(S)>::type get_specialization_constant() const;
};

module<module_state::executable>
build(const module<module_state::input> &inputModule,
      const property_list &propList = {});

module<module_state::object>
compile(const module<module_state::input> &inputModule,
        const property_list &propList = {});

module<module_state::executable>
link(const module<module_state::object> &objModule,
     const property_list &propList = {});

module<module_state::executable>
link(const std::vector<module<module_state::object>> &objModules,
     const property_list &propList = {});

template<module_state T>
module<T> join(const std::vector<module<T>> &modules);

namespace this_module {

template <typename T>
std::string kernel_name_v;

bool has_any_module(context ctxt);

template<module_state S>
bool has_module_in(context ctxt);

template<module_state S>
module<T> get(context ctxt);

}  // this_module

}  // namespace sycl
