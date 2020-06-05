namespace sycl {

class interop_handle {
 private:

  interop_handle(__unspecified__);

 public:

  interop_handle() = delete;

  template <backend Backend, typename dataT, int dims, access::mode accessMode,
            access::target accessTarget, access::placeholder isPlaceholder>
  backend_traits<Backend>::native_type<buffer>
  get_native_mem(const accessor<dataT, dims, accessMode, accessTarget,
                                isPlaceholder> &bufferAccessor) const;

  template <backend Backend, typename dataT, int dims, access::mode accessMode,
            access::target accessTarget, access::placeholder isPlaceholder>
  backend_traits<Backend>::native_type<image>
  get_native_mem(const accessor<dataT, dims, accessMode, accessTarget,
                                isPlaceholder> &imageAccessor) const;

  template <backend Backend>
  backend_traits<Backend>::native_type<queue> get_native_queue() const noexcept;

  template <backend Backend>
  backend_traits<Backend>::native_type<device> get_native_device() const noexcept;

  template <backend Backend>
  backend_traits<Backend>::native_type<context> get_native_context() const noexcept;

};

class handler {
  ...

 public:

  template <typename T>
  void host_task(T &&hostTaskCallable);

  ...
};

}  // namespace sycl