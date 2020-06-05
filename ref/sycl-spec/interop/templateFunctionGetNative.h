namespace sycl {

template<backend Backend, class T>
backend_traits<Backend>::native_type<T> get_native(const T &syclObject);

}  // namespace sycl
