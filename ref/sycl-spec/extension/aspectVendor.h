namespace sycl {
namespace ext {
namespace acme {
namespace aspect {

static constexpr auto bar = static_cast<sycl::aspect>(-1);

} // namespace aspect
} // namespace acme
} // namespace ext

template<> struct is_aspect_active<ext::acme::aspect::bar> : std::true_type {};

} // namespace sycl
