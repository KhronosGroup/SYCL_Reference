// Exposition only
template <typename T, typename BinaryOperation, int Dimensions>
class reducer {

  template <access_mode Mode>
  reducer(accessor<T, Dimensions, Mode> vars, BinaryOperation combiner);

  template <access_mode Mode>
  reducer(accessor<T, Dimensions, Mode> vars, const T& identity, BinaryOperation combiner);

  reducer(T* var, BinaryOperation combiner, handler& cgh);

  reducer(T* var, const T& identity, BinaryOperation combiner, handler& cgh);

  template <typename Extent>
  reducer(span<T, Extent> vars, BinaryOperation combiner, handler& cgh);

  template <typename Extent>
  reducer(span<T, Extent> vars, const T& identity, BinaryOperation combiner, handler& cgh);

  reducer(const reducer<T,BinaryOperation,Dimensions>&) = delete;
  reducer<T,BinaryOperation,Dimensions>& operator(const reducer<T,BinaryOperation,Dimensions>&) = delete;

  /* Only available if Dimensions == 0 */
  void combine(const T& partial);

  /* Only available if Dimensions > 1 */
  __unspecified__ &operator[](size_t index) const;

  /* Only available if identity value is known */
  T identity() const;

};

template <typename T>
void operator+=(reducer<T,plus<T>,0>&, const T&);

template <typename T>
void operator*=(reducer<T,multiplies<T>,0>&, const T&);

/* Only available for integral types */
template <typename T>
void operator&=(reducer<T,bit_and<T>,0>&, const T&);

/* Only available for integral types */
template <typename T>
void operator|=(reducer<T,bit_or<T>,0>&, const T&);

/* Only available for integral types */
template <typename T>
void operator^=(reducer<T,bit_xor<T>,0>&, const T&);

/* Only available for integral types */
template <typename T>
void operator++(reducer<T,plus<T>,0>&);
