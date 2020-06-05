namespace sycl {
enum class image_format : unsigned int {
  r8g8b8a8_unorm,
  r16g16b16a16_unorm,
  r8g8b8a8_sint,
  r16g16b16a16_sint,
  r32b32g32a32_sint,
  r8g8b8a8_uint,
  r16g16b16a16_uint,
  r32b32g32a32_uint,
  r16b16g16a16_sfloat,
  r32g32b32a32_sfloat,
  b8g8r8a8_unorm,
};

using byte = unsigned char;

template <int dimensions = 1, typename AllocatorT = sycl::image_allocator>
class sampled_image {
 public:
  sampled_image(const void *hostPointer, image_format format,
                  image_sampler sampler, const range<dimensions> &rangeRef,
                  const property_list &propList = {});

  /* Available only when: dimensions > 1 */
  sampled_image(const void *hostPointer, image_format format,
                  image_sampler sampler, const range<dimensions> &rangeRef,
                  const range<dimensions -1> &pitch,
                  const property_list &propList = {});

  sampled_image(std::shared_ptr<const void> &hostPointer, image_format format,
                  image_sampler sampler, const range<dimensions> &rangeRef,
                  const property_list &propList = {});

  /* Available only when: dimensions > 1 */
  sampled_image(std::shared_ptr<const void> &hostPointer, image_format format,
                  image_sampler sampler, const range<dimensions> &rangeRef,
                  const range<dimensions -1> &pitch,
                  const property_list &propList = {});

  /* -- common interface members -- */

  /* -- property interface members -- */

  range<dimensions> get_range() const;

  /* Available only when: dimensions > 1 */
  range<dimensions - 1> get_pitch() const;

  size_t get_count() const;

  size_t get_size() const;

  template <typename dataT, access::mode accessMode>
  accessor<dataT, dimensions, accessMode, access::target::sampled_image>
  get_access(handler & commandGroupHandler);

  template <typename dataT, access::mode accessMode>
  accessor<dataT, dimensions, accessMode, access::target::host_sampled_image>
  get_access();
};
}  // namespace sycl
