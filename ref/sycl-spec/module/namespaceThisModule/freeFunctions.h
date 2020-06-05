bool has_any_module(context ctxt); // (1)

template<module_state S> // (2)
bool has_module_in(context ctxt);

template<module_state S> // (3)
module<T> get(context ctxt);