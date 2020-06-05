void use_module(const module<module_state::executable> &execModule); // (1)

template <typename T>
void use_module(const module<module_state::executable> &execModule // (2)
                T deviceImageSelector);