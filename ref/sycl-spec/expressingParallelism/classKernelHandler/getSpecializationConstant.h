template<auto& S>
typename std::remove_reference_t<decltype(S)>::type get_specialization_constant(); // (1)