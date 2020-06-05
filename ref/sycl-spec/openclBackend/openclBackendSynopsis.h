namespace sycl {
namespace opencl {

using binary_blob_t = std::pair<const char*, size_t>;

module<module_state::input> create_module_with_source (context ctx, std::string source);

module<module_state::input> create_module_with_binary(context ctx, binary_blob_t binary);

module<module_state::input> create_module_with_il (context ctx, binary_blob_t il);

module<module_state::input> create_module_with_builtin_kernels (context ctx,
  std::vector<std::string> kernelNames);

}  // namespace opencl 
}  // namespace sycl