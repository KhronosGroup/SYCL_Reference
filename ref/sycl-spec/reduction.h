template <typename AccessorT, typename BinaryOperation>
__unspecified__ reduction(AccessorT vars, BinaryOperation combiner);

template <typename AccessorT, typename BinaryOperation>
__unspecified__ reduction(AccessorT vars, const T& identity, BinaryOperation combiner);

template <typename T, typename BinaryOperation>
__unspecified__ reduction(T* var, BinaryOperation combiner);

template <typename T, typename BinaryOperation>
__unspecified__ reduction(T* var, T& identity, BinaryOperation combiner);

template <typename T, typename Extent, typename BinaryOperation>
__unspecified__ reduction(span<T, Extent> vars, BinaryOperation combiner);

template <typename T, typename Extent, typename BinaryOperation>
__unspecified__ reduction(span<T, Extent> vars, const T& identity, BinaryOperation combiner);
