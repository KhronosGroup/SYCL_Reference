namespace sycl {

template <backend Backend>
class backend_traits {
 public:

  template <class T>
  using native_type = see-below;

  using errc = see-below;

};

}  // namespace sycl
