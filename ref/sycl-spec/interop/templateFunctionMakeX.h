namespace sycl {

template<backend Backend>
platform make_platform(const backend_traits<Backend>::native_type<platform> &backendObject);

template<backend Backend>
device make_device(const backend_traits<Backend>::native_type<device> &backendObject);

template<backend Backend>
context make_context(const backend_traits<Backend>::native_type<context> &backendObject, const async_handler asyncHandler = {});

template<backend Backend>
queue make_queue(const backend_traits<Backend>::native_type<queue> &backendObject,
                 const context &targetContext, const async_handler asyncHandler = {});

template<backend Backend>
event make_event(const backend_traits<Backend>::native_type<event> &backendObject,
                 const context &targetContext);

template<backend Backend>
buffer make_buffer(const backend_traits<Backend>::native_type<buffer> &backendObject,
                   const context &targetContext, event availableEvent = {});

template<backend Backend>
sampled_image make_sampled_image(
  const backend_traits<Backend>::native_type<sampled_image> &backendObject,
  const context &targetContext, image_sampler imageSampler, event availableEvent = {});

template<backend Backend>
unsampled_image make_unsampled_image(
  const backend_traits<Backend>::native_type<unsampled_image> &backendObject,
  const context &targetContext, event availableEvent = {});

template<backend Backend>
image_sampler make_image_sampler(
  const backend_traits<Backend>::native_type<image_sampler> &backendObject,
  const context &targetContext);

template<backend Backend>
stream make_stream(const backend_traits<Backend>::native_type<stream> &backendObject,
                   const context &targetContext, event availableEvent = {});

template<backend Backend>
kernel make_kernel(const backend_traits<Backend>::native_type<kernel> &backendObject,
                   const context &targetContext);

template<backend Backend>
kernel make_module(const backend_traits<Backend>::native_type<event> &backendObject,
                   const context &targetContext);

}  // namespace sycl
