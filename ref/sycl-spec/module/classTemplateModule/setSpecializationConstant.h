template<auto& S>
void set_specialization_constant(
  typename std::remove_reference_t<decltype(S)>::type value); // (1)