namespace sycl {
namespace khr {
namespace aspect {

static constexpr auto foo = static_cast<sycl::aspect>(1000);

} // namespace aspect
} // namespace khr

template<> struct is_aspect_active<khr::aspect::foo> : std::true_type {};

} // namespace sycl
