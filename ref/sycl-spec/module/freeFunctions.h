namespace sycl {

module<module_state::executable>
build(const module<module_state::input> &inputModule,
      const property_list &propList = {}); // (1)

module<module_state::object>
compile(const module<module_state::input> &inputModule,
        const property_list &propList = {}); // (2)

module<module_state::executable>
link(const module<module_state::object> &objModule,
     const property_list &propList = {}); // (3)

module<module_state::executable>
link(const std::vector<module<module_state::object>> &objModules,
     const property_list &propList = {}); // (4)

template<module_state T>
module<T> join(const std::vector<module<T>> &modules); // (5)

} // namespace sycl
