template <backend Backend, typename dataT, int dims, access::mode accMode,
          access::target accTarget, access::placeholder isPlaceholder>
backend_traits<Backend>::native_type<buffer>
get_native_mem(const accessor<dataT, dims, accMode, accTarget, // (1)
                              isPlaceholder> &bufferAccessor) const;

template <backend Backend, typename dataT, int dims, access::mode accMode,
          access::target accTarget, access::placeholder isPlaceholder>
backend_traits<Backend>::native_type<image>
get_native_mem(const accessor<dataT, dims, accMode, accTarget, // (2)
                              isPlaceholder> &imageAccessor) const;

template <backend Backend>
backend_traits<Backend>::native_type<queue> get_native_queue() const noexcept; // (3)

template <backend Backend>
backend_traits<Backend>::native_type<device> get_native_device() const noexcept; // (4)

template <backend Backend>
backend_traits<Backend>::native_type<context> get_native_context() const noexcept; // (5)