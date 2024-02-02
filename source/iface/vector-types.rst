..
  Copyright 2020 The Khronos Group Inc.
  SPDX-License-Identifier: CC-BY-4.0

.. _vector-types:

************
Vector types
************

SYCL provides a cross-platform class template that works
efficiently on SYCL devices as well as in host C++ code.
This type allows sharing of vectors between the host and its
SYCL devices. The vector supports member functions that allow
construction of a new vector from a swizzled set of component
elements.

The ``sycl::vec`` class is templated on its number of elements
and its element type. The number of elements parameter, NumElements,
can be one of: 1, 2, 3, 4, 8 or 16. Any other value shall produce
a compilation failure. The element type parameter, ``DataT``, must be
one of the basic scalar types supported in device code.

The SYCL ``sycl::vec`` class template provides interoperability with the
underlying vector type defined by ``vector_t`` which is available
only when compiled for the device. The SYCL ``sycl::vec`` class can be
constructed from an instance of ``vector_t`` and can implicitly
convert to an instance of ``vector_t`` in order to support
interoperability with native SYCL backend functions from
a SYCL kernel function.

An instance of the SYCL ``sycl::vec`` class template can also be
implicitly converted to an instance of the data type when the
number of elements is ``1`` in order to allow single element
vectors and scalars to be convertible with each other.

=======================
``sycl::rounding_mode``
=======================

::

   enum class rounding_mode {
       automatic,
       rte,
       rtz,
       rtp,
       rtn
   };

==============
``sycl::elem``
==============

::

   struct elem {
       static constexpr int x = 0;
       static constexpr int y = 1;
       static constexpr int z = 2;
       static constexpr int w = 3;
       static constexpr int r = 0;
       static constexpr int g = 1;
       static constexpr int b = 2;
       static constexpr int a = 3;
       static constexpr int s0 = 0;
       static constexpr int s1 = 1;
       static constexpr int s2 = 2;
       static constexpr int s3 = 3;
       static constexpr int s4 = 4;
       static constexpr int s5 = 5;
       static constexpr int s6 = 6;
       static constexpr int s7 = 7;
       static constexpr int s8 = 8;
       static constexpr int s9 = 9;
       static constexpr int sA = 10;
       static constexpr int sB = 11;
       static constexpr int sC = 12;
       static constexpr int sD = 13;
       static constexpr int sE = 14;
       static constexpr int sF = 15;
   };


.. _vec:

=============
``sycl::vec``
=============

::

   template <typename dataT, int numElements>
   class vec;

(constructors)
==============

::

   vec();

   explicit constexpr vec(const DataT& arg);

   template <typename... ArgTN> constexpr vec(const ArgTN&... args);

   constexpr vec(const vec<DataT, NumElements>& rhs);

   vec(vector_t nativeVector);

The first option default constructs a vector with element type ``DataT``
and with ``NumElements`` dimensions by default construction
of each of its elements.
The second option is by setting each value to ``arg`` by assignment.
Other options are to construct a SYCL ``sycl::vec`` instance from any
combination of scalar and SYCL ``sycl::vec`` parameters of the same element
type or copy from another similar vector.

Member functions
================

``vector_t``
------------

::

  operator vector_t() const

Available only when: compiled for the device.

Converts this SYCL ``sycl::vec`` instance to the underlying backend-native
vector type defined by ``vector_t``.

``DataT``
---------

::

  operator DataT() const

Available only when: ``NumElements == 1``.

Converts this SYCL ``sycl::vec`` instance to an instance of ``DataT``
with the value of the single element in this SYCL ``sycl::vec`` instance.

The SYCL ``sycl::vec`` instance shall be implicitly convertible to the
same data types, to which ``DataT`` is implicitly convertible.
Note that conversion operator shall not be templated to allow
standard conversion sequence for implicit conversion.

``size``
--------

::

  static constexpr size_t size() noexcept

Returns the number of elements of this SYCL ``sycl::vec``.

``get_count``
-------------

::

  size_t get_count() const

Returns the same value as ``sycl::size()``. Deprecated.

``byte_size``
-------------

::

  static constexpr size_t byte_size() noexcept

Returns the size of this SYCL ``sycl::vec`` in bytes.

3-element vector size matches 4-element vector size
to provide interoperability with OpenCL vector types.
The same rule applies to vector alignment as described
in |SYCL_SPEC_MEMORY_LAYOUT_AND_ALIG|.

``sycl::get_size``
------------------

::

  size_t sycl::get_size() const

Returns the same value as ``byte_size()``. Deprecated.

``convert``
-----------

::

  template <typename ConvertT,
            sycl::rounding_mode RoundingMode = sycl::rounding_mode::automatic>
  sycl::vec<ConvertT, NumElements> convert() const

Converts this SYCL ``sycl::vec`` to a SYCL ``sycl::vec`` of a different element
type specified by ``ConvertT`` using the rounding mode specified
by ``RoundingMode``. The new SYCL ``sycl::vec`` type must have the same
number of elements as this SYCL ``sycl::vec``.

``as``
------

::

  template <typename asT> asT as() const

Bitwise reinterprets this SYCL ``sycl::vec`` as a SYCL ``sycl::vec`` of a
different element type and number of elements specified by ``asT``.
The new SYCL ``sycl::vec`` type must have the same storage size in bytes as
this SYCL ``sycl::vec``, and the size of the elements in the new SYCL
``vec (NumElements * sizeof(DataT))`` must be the same as the
size of the elements in this SYCL ``sycl::vec``.


``swizzle``
-----------

::

   template <int... swizzleIndexes>
   __swizzled_vec__ swizzle() const

Return an instance of the implementation-defined intermediate class
template ``__swizzled_vec__`` representing an index sequence which can
be used to apply the swizzle in a valid expression as described
in |SYCL_SPEC_SWIZZLED_VEC_CLASS|.

``swizzle access``
------------------

::

  __swizzled_vec__ XYZW_ACCESS() const

Available only when: ``NumElements <= 4``.

Returns an instance of the implementation-defined intermediate class template
``__swizzled_vec__`` representing an index sequence which can be used to
apply the swizzle in a valid expression as described
in |SYCL_SPEC_SWIZZLED_VEC_CLASS|.

Where ``XYZW_ACCESS`` is: ``x`` for ``NumElements == 1``, ``x``, ``y``
for ``NumElements == 2``, ``x``, ``y``, ``z`` for ``NumElements == 3``
and ``x``, ``y``, ``z``, ``w`` for ``NumElements == 4``.

::

  __swizzled_vec__ RGBA_ACCESS() const


Available only when: ``NumElements == 4``.

Returns an instance of the implementation-defined intermediate class template
``__swizzled_vec__`` representing an index sequence which can be used to
apply the swizzle in a valid expression as described
in |SYCL_SPEC_SWIZZLED_VEC_CLASS|.

Where ``RGBA_ACCESS`` is: ``r``, ``g``, ``b``, ``a``.

::

  __swizzled_vec__ INDEX_ACCESS() const


Returns an instance of the implementation-defined intermediate class template
``__swizzled_vec__`` representing an index sequence which can be used to
apply the swizzle in a valid expression as described
in |SYCL_SPEC_SWIZZLED_VEC_CLASS|.

Where ``INDEX_ACCESS`` is: ``s0`` for ``NumElements == 1``,
``s0``, ``s1`` for ``NumElements == 2``, ``s0``, ``s1``, ``s2``
for ``NumElements == 3``, ``s0``, ``s1``, ``s2``, ``s3`` for
``NumElements == 4``, ``s0``, ``s1``, ``s2``, ``s3``, ``s4``,
``s5``, ``s6``, ``s7``, ``s8`` for ``NumElements == 8`` and
``s0``, ``s1``, ``s2``, ``s3``, ``s4``, ``s5``, ``s6``, ``s7``,
``s8``, ``s9``, ``sA``, ``sB``, ``sC``, ``sD``, ``sE``, ``sF``
for ``NumElements == 16``.

::

  __swizzled_vec__ XYZW_SWIZZLE() const

Available only when: ``NumElements <= 4``, and when the macro
``SYCL_SIMPLE_SWIZZLES`` is defined before ``including <sycl/sycl.hpp>``.

Returns an instance of the implementation-defined intermediate
class template ``__swizzled_vec__`` representing an index sequence
which can be used to apply the swizzle in a valid expression as
described in |SYCL_SPEC_SWIZZLED_VEC_CLASS|.

Where XYZW_SWIZZLE is all permutations with repetition, of any
subset with length greater than ``1``, of ``x``, ``y`` for
``NumElements == 2``, ``x``, ``y``, ``z`` for ``NumElements == 3``
and ``x``, ``y``, ``z``, ``w`` for ``NumElements == 4``.
For example a four element ``sycl::vec`` provides permutations
including ``xzyw``, ``xyyy`` and ``xz``.

::

  __swizzled_vec__ XYZW_SWIZZLE() const

Available only when: ``NumElements == 4``, and when the macro
``SYCL_SIMPLE_SWIZZLES`` is defined before ``including <sycl/sycl.hpp>``.

Returns an instance of the implementation-defined intermediate class template
``__swizzled_vec__`` representing an index sequence which can be used to
apply the swizzle in a valid expression as described
in |SYCL_SPEC_SWIZZLED_VEC_CLASS|.

Where RGBA_SWIZZLE is all permutations with repetition, of any subset
with length greater than ``1``, of ``r``, ``g``, ``b``, ``a``.
For example a four element ``sycl::vec`` provides permutations including
``rbga``, ``rggg`` and ``rb``.


``lo``
------

::

   __swizzled_vec__ lo() const

Available only when: ``NumElements > 1``.

Return an instance of the implementation-defined intermediate class
template ``__swizzled_vec__`` representing an index sequence made
up of the lower half of this SYCL ``sycl::vec`` which can be used to apply the
swizzle in a valid expression as described
in |SYCL_SPEC_SWIZZLED_VEC_CLASS|. When ``NumElements == 3``, this
SYCL ``sycl::vec`` is treated as though ``NumElements == 4``
with the fourth element undefined.

``hi``
------

::

   __swizzled_vec__ hi() const

Available only when: ``NumElements > 1``.

Return an instance of the implementation-defined intermediate class
template ``__swizzled_vec__`` representing an index sequence made
up of the upper half of this SYCL ``sycl::vec`` which can be used to apply the
swizzle in a valid expression as described
in |SYCL_SPEC_SWIZZLED_VEC_CLASS|. When ``NumElements == 3``, this
SYCL ``sycl::vec`` is treated as though ``NumElements == 4``
with the fourth element undefined.

``odd``
-------

::

   __swizzled_vec__ odd() const

Available only when: ``NumElements > 1``.

Return an instance of the implementation-defined intermediate class
template ``__swizzled_vec__`` representing an index sequence made
up of the odd indexes of this SYCL ``sycl::vec`` which can be used to apply the
swizzle in a valid expression as described
in |SYCL_SPEC_SWIZZLED_VEC_CLASS|. When ``NumElements == 3``, this
SYCL ``sycl::vec`` is treated as though ``NumElements == 4``
with the fourth element undefined.

``even``
--------

::

   __swizzled_vec__ even() const

Available only when: ``NumElements > 1``.

Return an instance of the implementation-defined intermediate class
template ``__swizzled_vec__`` representing an index sequence made
up of the even indexes of this SYCL ``sycl::vec`` which can be used to apply the
swizzle in a valid expression as described
in |SYCL_SPEC_SWIZZLED_VEC_CLASS|. When ``NumElements == 3``, this
SYCL ``sycl::vec`` is treated as though ``NumElements == 4``
with the fourth element undefined.

``load``
--------

::

   template <sycl::access::address_space AddressSpace, sycl::access::decorated IsDecorated>
   void load(size_t offset, sycl::multi_ptr<const DataT, AddressSpace, IsDecorated> ptr)

Loads the values at the address of ``ptr`` offset in elements of
type ``DataT`` by ``NumElements * offset``, into the components
of this SYCL ``sycl::vec``.

``store``
---------

::

   template <sycl::access::address_space AddressSpace, sycl::access::decorated IsDecorated>
   void store(size_t offset, sycl::multi_ptr<DataT, AddressSpace, IsDecorated> ptr) const

Stores the components of this SYCL ``sycl::vec`` into the values at the address
of ``ptr`` offset in elements of type ``DataT`` by ``NumElements * offset``.

``operator[]``
--------------

::

  DataT& operator[](int index)

Returns a reference to the element stored within this SYCL
``sycl::vec`` at the index specified by ``index``.


::

  const DataT& operator[](int index) const

Returns a ``const`` reference to the element stored within this SYCL
``sycl::vec`` at the index specified by ``index``.

``operator=``
-------------

::

  sycl::vec& operator=(const sycl::vec& rhs)

Assign each element of the ``rhs`` SYCL ``sycl::vec`` to each element
of this SYCL ``sycl::vec`` and return a reference to this SYCL ``sycl::vec``.


::

  sycl::vec& sycl::operator=(const DataT& rhs)

Assign each element of the ``rhs`` scalar to each element
of this SYCL ``sycl::vec`` and return a reference to this SYCL ``sycl::vec``.


Hidden friend functions
=======================

``operatorOP``
--------------

::

  sycl::vec operatorOP(const sycl::vec& lhs, const sycl::vec& rhs);

If ``OP`` is ``%``, available only when:
``DataT != float && DataT != double && DataT != half``.

Construct a new instance of the SYCL ``sycl::vec`` class template with the
same template parameters as ``lhs vec`` with each element of the new
SYCL ``sycl::vec`` instance the result of an element-wise ``OP``
arithmetic operation between each element of ``lhs vec``
and each element of the ``rhs`` SYCL ``sycl::vec``.

Where ``OP`` is: ``+``, ``-``, ``*``, ``/``, ``%``.

::

  sycl::vec operatorOP(const sycl::vec& lhs, const DataT& rhs);

If ``OP`` is ``%``, available only when:
``DataT != float && DataT != double && DataT != half``.

Construct a new instance of the SYCL ``sycl::vec`` class template with the
same template parameters as ``lhs vec`` with each element of the new
SYCL ``sycl::vec`` instance the result of an element-wise ``OP``
arithmetic operation between each element of ``lhs vec``
and the ``rhs`` scalar.

Where ``OP`` is: ``+``, ``-``, ``*``, ``/``, ``%``.

::

  sycl::vec& operatorOP(sycl::vec& lhs, const sycl::vec& rhs);

If ``OP`` is ``%=``, available only when:
``DataT != float && DataT != double && DataT != half``.

Perform an in-place element-wise ``OP`` arithmetic operation between
each element of ``lhs vec`` and each element of the ``rhs`` SYCL
``sycl::vec`` and return ``lhs vec``.

Where ``OP`` is: ``+=``, ``-=``, ``*=``, ``/=``, ``%=``.

::

  sycl::vec& operatorOP(sycl::vec& lhs, const DataT& rhs);

If ``OP`` is ``%=``, available only when:
``DataT != float && DataT != double && DataT != half``.

Perform an in-place element-wise ``OP`` arithmetic operation between
each element of ``lhs vec`` and ``rhs`` scalar and return ``lhs vec``.

Where ``OP`` is: ``+=``, ``-=``, ``*=``, ``/=``, ``%=``.

::

  sycl::vec& operatorOP(sycl::vec& v);

Available only when: ``DataT != bool``.

Perform an in-place element-wise ``OP`` prefix arithmetic operation
on each element of ``lhs vec``, assigning the result of each element
to the corresponding element of ``lhs vec`` and return ``lhs vec``.

Where ``OP`` is: ``++``, ``--``.

::

  sycl::vec operatorOP(sycl::vec& v, int);

Available only when: ``DataT != bool``.

Perform an in-place element-wise ``OP`` prefix arithmetic operation
on each element of ``lhs vec``, assigning the result of each element
to the corresponding element of ``lhs vec`` and returns a copy of
``lhs vec`` before the operation is performed.

Where ``OP`` is: ``++``, ``--``.

::

  sycl::vec operatorOP(const sycl::vec& v);

Construct a new instance of the SYCL ``sycl::vec`` class template with
the same template parameters as this SYCL ``sycl::vec`` with each element
of the new SYCL ``sycl::vec`` instance the result of an element-wise
``OP`` unary arithmetic operation on each element of this SYCL ``sycl::vec``.

Where ``OP`` is: ``+``, ``-``.

::

  sycl::vec operatorOP(const sycl::vec& lhs, const sycl::vec& rhs);

Available only when:
``DataT != float && DataT != double && DataT != half``.

Construct a new instance of the SYCL ``sycl::vec`` class template
with the same template parameters as ``lhs vec`` with each element
of the new SYCL ``sycl::vec`` instance the result of an element-wise
``OP`` bitwise operation between each element of ``lhs vec``
and each element of the ``rhs`` SYCL ``sycl::vec``.

Where ``OP`` is: ``&``, ``|``, ``^``.

::

  sycl::vec operatorOP(const sycl::vec& lhs, const DataT& rhs);

Available only when:
``DataT != float && DataT != double && DataT != half``.

Construct a new instance of the SYCL ``sycl::vec`` class template
with the same template parameters as ``lhs vec`` with each element
of the new SYCL ``sycl::vec`` instance the result of an element-wise
``OP`` bitwise operation between each element of ``lhs vec``
and the ``rhs`` scalar.

Where ``OP`` is: ``&``, ``|``, ``^``.

::

  sycl::vec& operatorOP(sycl::vec& lhs, const sycl::vec& rhs);

Available only when:
``DataT != float && DataT != double && DataT != half``.

Perform an in-place element-wise ``OP`` bitwise operation between
each element of ``lhs vec`` and the ``rhs`` SYCL
``sycl::vec`` and return ``lhs vec``.

Where ``OP`` is: ``&=``, ``|=``, ``^=``.

::

  sycl::vec& operatorOP(sycl::vec& lhs, const DataT& rhs);

Available only when:
``DataT != float && DataT != double && DataT != half``.

Perform an in-place element-wise ``OP`` bitwise operation between
each element of ``lhs vec`` and the ``rhs`` scalar and return a ``lhs vec``.

Where ``OP`` is: ``&=``, ``|=``, ``^=``.

::

  sycl::vec<RET, NumElements> operatorOP(const sycl::vec& lhs, const sycl::vec& rhs);

Construct a new instance of the SYCL ``sycl::vec`` class template with the
same template parameters as ``lhs vec`` with each element of the new
SYCL ``sycl::vec`` instance the result of an element-wise ``OP`` logical
operation between each element of ``lhs vec`` and each element
of the ``rhs`` SYCL ``sycl::vec``.

The ``DataT`` template parameter of the constructed SYCL ``sycl::vec``,
``RET``, varies depending on the ``DataT`` template parameter of this
SYCL ``sycl::vec``. For a SYCL ``sycl::vec`` with ``DataT`` of
type ``int8_t`` or ``uint8_t RET`` must be ``int8_t``. For a SYCL
``sycl::vec`` with ``DataT`` of type ``int16_t``, ``uint16_t``
or ``half RET`` must be ``int16_t``. For a SYCL ``sycl::vec`` with
``DataT`` of type ``int32_t``, ``uint32_t`` or ``float RET``
must be ``int32_t``. For a SYCL ``sycl::vec`` with ``DataT`` of
type ``int64_t``, ``uint64_t`` or ``double RET`` must be ``int64_t``.

Where ``OP`` is: ``&&``, ``||``.

::

  sycl::vec<RET, NumElements> operatorOP(const sycl::vec& lhs, const DataT& rhs);


Construct a new instance of the SYCL ``sycl::vec`` class template with the
same template parameters as this SYCL ``sycl::vec`` with each element of the
new SYCL ``sycl::vec`` instance the result of an element-wise ``OP`` logical
operation between each element of ``lhs vec`` and the ``rhs`` scalar.

The ``DataT`` template parameter of the constructed SYCL ``sycl::vec``,
``RET``, varies depending on the ``DataT`` template parameter of this
SYCL ``sycl::vec``. For a SYCL ``sycl::vec`` with ``DataT``
of type ``int8_t`` or ``uint8_t RET`` must be ``int8_t``. For a SYCL
``sycl::vec`` with ``DataT`` of type ``int16_t``, ``uint16_t`` or
``half RET`` must be ``int16_t``.
For a SYCL ``sycl::vec`` with ``DataT`` of type ``int32_t``, ``uint32_t``
or ``float RET`` must be ``int32_t``. For a SYCL ``sycl::vec`` with ``DataT``
of type ``int64_t``, ``uint64_t`` or ``double RET`` must be ``int64_t``.

Where ``OP`` is: ``&&``, ``||``.

::

  sycl::vec operatorOP(const sycl::vec& lhs, const sycl::vec& rhs);

Available only when:
``DataT != float && DataT != double && DataT != half``.

Construct a new instance of the SYCL ``sycl::vec`` class template with the
same template parameters as ``lhs vec`` with each element of the new
SYCL ``sycl::vec`` instance the result of an element-wise ``OP`` bitshift
operation between each element of ``lhs vec`` and each element of the
``rhs`` SYCL ``sycl::vec``. If ``OP`` is ``>>``, ``DataT``
is a signed type and ``lhs vec`` has a negative value any vacated
bits viewed as an unsigned integer must be assigned the value
``1``, otherwise any vacated bits viewed as an unsigned integer
must be assigned the value ``0``.

Where ``OP`` is:``<<``, ``>>``.

::

  sycl::vec operatorOP(const sycl::vec& lhs, const DataT& rhs);

Available only when:
``DataT != float && DataT != double && DataT != half``.

Construct a new instance of the SYCL ``sycl::vec`` class template with the
same template parameters as ``lhs vec`` with each element of the new
SYCL ``sycl::vec`` instance the result of an element-wise ``OP`` bitshift
operation between each element of ``lhs vec`` and the ``rhs`` scalar.
If ``OP`` is ``>>``, ``DataT`` is a signed type and ``lhs vec`` has
a negative value any vacated bits viewed as an unsigned integer must
be assigned the value ``1``, otherwise any vacated bits viewed as an
unsigned integer must be assigned the value ``0``.

Where ``OP`` is:``<<``, ``>>``.

::

  sycl::vec& operatorOP(sycl::vec& lhs, const sycl::vec& rhs);

Available only when:
``DataT != float && DataT != double && DataT != half``.

Perform an in-place element-wise ``OP`` bitshift operation between
each element of ``lhs vec`` and the ``rhs`` SYCL ``sycl::vec`` and returns
``lhs vec``. If ``OP`` is ``>>=``, ``DataT`` is a signed type and
``lhs vec`` has a negative value any vacated bits viewed as an
unsigned integer must be assigned the value ``1``, otherwise any
vacated bits viewed as an unsigned integer must be assigned the
value ``0``.

Where ``OP`` is: ``<<=``, ``>>=``.

::

  sycl::vec& operatorOP(sycl::vec& lhs, const DataT& rhs);

Available only when:
``DataT != float && DataT != double && DataT != half``.

Perform an in-place element-wise ``OP`` bitshift operation between
each element of ``lhs vec`` and the ``rhs`` scalar and returns a
reference to this SYCL ``sycl::vec``. If ``OP`` is ``>>=``, ``DataT``
is a signed type and ``lhs vec`` has a negative value any vacated
bits viewed as an unsigned integer must be assigned the value ``1``,
otherwise any vacated bits viewed as an unsigned integer must
be assigned the value ``0``.

Where ``OP`` is: ``<<=``, ``>>=``.

::

  sycl::vec<RET, NumElements> operatorOP(const sycl::vec& lhs, const sycl::vec& rhs);

Construct a new instance of the SYCL ``sycl::vec`` class template with the
element type ``RET`` with each element of the new SYCL ``sycl::vec``
instance the result of an element-wise ``OP`` relational operation
between each element of ``lhs vec`` and each element of the ``rhs``
SYCL ``sycl::vec``. Each element of the SYCL ``sycl::vec`` that is
returned must be ``-1`` if the operation results in ``true`` and ``0`` if the
operation results in ``false``. The ``==``, ``<``, ``>``, ``<=``
and ``>=`` operations result in ``false`` if either the ``lhs``
element or the ``rhs`` element is a ``NaN``. The ``!=`` operation results
in ``true`` if either the ``lhs`` element or the ``rhs`` element
is a ``NaN``.

The ``DataT`` template parameter of the constructed SYCL ``sycl::vec``,
``RET``, varies depending on the ``DataT`` template parameter of
this SYCL ``sycl::vec``. For a SYCL ``sycl::vec`` with ``DataT`` of type
``int8_t`` or ``uint8_t RET`` must be ``int8_t``. For a SYCL
``sycl::vec`` with ``DataT`` of type ``int16_t``, ``uint16_t`` or
``half RET`` must be ``int16_t``. For a SYCL ``sycl::vec`` with
``DataT`` of type ``int32_t``, ``uint32_t`` or ``float RET``
must be ``int32_t``. For a SYCL ``sycl::vec`` with ``DataT`` of type
``int64_t``, ``uint64_t`` or ``double RET`` must be ``uint64_t``.

Where ``OP`` is: ``==``, ``!=``, ``<``, ``>``, ``<=``, ``>=``.

::

  sycl::vec<RET, NumElements> operatorOP(const sycl::vec& lhs, const DataT& rhs);


Construct a new instance of the SYCL ``sycl::vec`` class template with the
same template parameters as this SYCL ``sycl::vec`` with each element of
the new SYCL ``sycl::vec`` instance the result of an element-wise
``OP`` logical operation between each element of ``lhs vec``
and the ``rhs`` scalar.

The ``DataT`` template parameter of the constructed SYCL ``sycl::vec``,
``RET``, varies depending on the ``DataT`` template parameter of
this SYCL ``sycl::vec``. For a SYCL ``sycl::vec`` with ``DataT`` of type
``int8_t`` or ``uint8_t RET`` must be ``int8_t``. For a SYCL
``sycl::vec`` with ``DataT`` of type ``int16_t``, ``uint16_t`` or
``half RET`` must be ``int16_t``. For a SYCL ``sycl::vec`` with
``DataT`` of type ``int32_t``, ``uint32_t`` or ``float RET``
must be ``int32_t``. For a SYCL ``sycl::vec`` with ``DataT`` of type
``int64_t``, ``uint64_t`` or ``double RET`` must be ``uint64_t``.

::

  sycl::vec operatorOP(const DataT& lhs, const sycl::vec& rhs);

If ``OP`` is ``%``, available only when:
``DataT != float && DataT != double && DataT != half``.

Construct a new instance of the SYCL ``sycl::vec`` class template with
the same template parameters as the ``rhs`` SYCL ``sycl::vec`` with each
element of the new SYCL ``sycl::vec`` instance the result of an
element-wise ``OP`` arithmetic operation between the ``lhs`` scalar
and each element of the ``rhs`` SYCL ``sycl::vec``.

Where ``OP`` is: ``+``, ``-``, ``*``, ``/``, ``%``.

::

  sycl::vec operatorOP(const DataT& lhs, const sycl::vec& rhs);

Available only when:
``DataT != float && DataT != double && DataT != half``.

Construct a new instance of the SYCL ``sycl::vec`` class template with the
same template parameters as the ``rhs`` SYCL ``sycl::vec`` with each element of
the new SYCL ``sycl::vec`` instance the result of an element-wise ``OP``
bitwise operation between the ``lhs`` scalar and each element of
the ``rhs`` SYCL ``sycl::vec``.

Where ``OP`` is: ``&``, ``|``, ``^``.

::

  sycl::vec<RET, NumElements> operatorOP(const DataT& lhs, const sycl::vec& rhs);

Available only when:
``DataT != float && DataT != double && DataT != half``.

Construct a new instance of the SYCL ``sycl::vec`` class template with the
same template parameters as the ``rhs`` SYCL ``sycl::vec`` with each element
of the new SYCL ``sycl::vec`` instance the result of an element-wise ``OP``
logical operation between the ``lhs`` scalar and each element of the
``rhs`` SYCL ``sycl::vec``.

The ``DataT`` template parameter of the constructed SYCL ``sycl::vec``,
``RET``, varies depending on the ``DataT`` template parameter of this
SYCL ``sycl::vec``. For a SYCL ``sycl::vec`` with ``DataT`` of
type ``int8_t`` or ``uint8_t RET`` must be ``int8_t``. For a SYCL
``sycl::vec`` with ``DataT`` of type ``int16_t``, ``uint16_t``
or ``half RET`` must be ``int16_t``.
For a SYCL ``sycl::vec`` with ``DataT`` of type ``int32_t``, ``uint32_t``
or ``float RET`` must be ``int32_t``. For a SYCL ``sycl::vec`` with ``DataT``
of type ``int64_t``, ``uint64_t`` or ``double RET`` must be ``int64_t``.

Where ``OP`` is: ``&&``, ``||``.

::

  sycl::vec operatorOP(const DataT& lhs, const sycl::vec& rhs);

Construct a new instance of the SYCL ``sycl::vec`` class template with the same
template parameters as the ``rhs`` SYCL ``sycl::vec`` with each element of the
new SYCL ``sycl::vec`` instance the result of an element-wise ``OP`` bitshift
operation between the ``lhs`` scalar and each element of the ``rhs`` SYCL
``sycl::vec``. If ``OP`` is ``>>``, ``DataT`` is a signed type
and this SYCL ``sycl::vec`` has a negative value any vacated bits viewed
as an unsigned integer must be assigned the value ``1``, otherwise any vacated
bits viewed as an unsigned integer must be assigned the value ``0``.

Where ``OP`` is: ``<<``, ``>>``.

::

  sycl::vec<RET, NumElements> operatorOP(const DataT& lhs, const sycl::vec& rhs);

Construct a new instance of the SYCL ``sycl::vec`` class template
with the element type ``RET`` with each element of the new SYCL
``sycl::vec`` instance the result of an element-wise ``OP`` relational
operation between the ``lhs`` scalar and each element of the ``rhs``
SYCL ``sycl::vec``. Each element of the SYCL ``sycl::vec``
that is returned must be ``-1`` if the operation results in ``true`` and ``0``
if the operation results in ``false``. The ``==``, ``<``, ``>``, ``<=`` and
``>=`` operations result in ``false`` if either the ``lhs`` or the ``rhs``
element is a ``NaN``. The ``!=`` operation results in ``true`` if either
the ``lhs`` or the ``rhs`` element is a ``NaN``.

The ``DataT`` template parameter of the constructed SYCL
``sycl::vec``, ``RET``, varies depending on the ``DataT`` template
parameter of this SYCL ``sycl::vec``.
For a SYCL ``sycl::vec`` with ``DataT`` of type ``int8_t`` or
``uint8_t RET`` must be ``int8_t``. For a SYCL ``sycl::vec`` with
``DataT`` of type ``int16_t``, ``uint16_t`` or ``half RET`` must be
``int16_t``. For a SYCL ``sycl::vec`` with ``DataT`` of type
``int32_t``, ``uint32_t`` or ``float RET`` must be ``int32_t``.
For a SYCL ``sycl::vec`` with
``DataT`` of type ``int64_t``, ``uint64_t`` or ``double RET``
must be ``int64_t``.

Where ``OP`` is: ``==``, ``!=``, ``<``, ``>``, ``<=``, ``>=``.

::

  sycl::vec& operator~(const sycl::vec& v);

Available only when:
``DataT != float && DataT != double && DataT != half``.

Construct a new instance of the SYCL ``sycl::vec`` class template with the
same template parameters as ``v vec`` with each element of the new
SYCL ``sycl::vec`` instance the result of an element-wise ``OP`` bitwise
operation on each element of ``v vec``.

::

  sycl::vec<RET, NumElements> operator!(const sycl::vec& v);

Construct a new instance of the SYCL ``sycl::vec`` class template with the
same template parameters as ``v vec`` with each element of the new
SYCL ``sycl::vec`` instance the result of an element-wise ``OP`` logical
operation on each element of ``v vec``. Each element of the SYCL
``sycl::vec`` that is returned must be ``-1`` if the operation results in
``true`` and ``0`` if the operation results in ``false`` or this
SYCL ``sycl::vec`` is a ``NaN``.

The ``DataT`` template parameter of the constructed SYCL ``sycl::vec``,
``RET``, varies depending on the ``DataT`` template parameter of
this SYCL ``sycl::vec``. For a SYCL ``sycl::vec`` with ``DataT``
of type ``int8_t`` or ``uint8_t RET`` must be ``int8_t``. For a SYCL
``sycl::vec`` with ``DataT`` of type ``int16_t``,
``uint16_t`` or ``half RET`` must be ``int16_t``.
For a SYCL ``sycl::vec`` with ``DataT`` of type
``int32_t``, ``uint32_t`` or ``float RET`` must be ``int32_t``.
For a SYCL ``sycl::vec`` with ``DataT`` of type ``int64_t``, ``uint64_t``
or ``double RET`` must be ``int64_t``.


=======
Aliases
=======

The SYCL programming API provides all permutations of the type alias:

``using <type><elems> = vec<<storage-type>, <elems>>``

where ``<elems>`` is ``2``, ``3``, ``4``, ``8`` and ``16``, and pairings
of ``<type>`` and ``<storage-type>`` for integral types are ``char`` and
``int8_t``, ``uchar`` and ``uint8_t``, ``short`` and ``int16_t``,
``ushort`` and ``uint16_t``, ``int`` and ``int32_t``, ``uint`` and
``uint32_t``, ``long`` and ``int64_t``, ``ulong`` and ``uint64_t``,
and for floating point types are both ``half``, ``float`` and ``double``.

For example ``uint4`` is the alias to ``vec<uint32_t, 4>`` and
``float16`` is the alias to ``vec<float, 16>``.

========
Swizzles
========

Swizzle operations can be performed in two ways. Firstly by calling the
``swizzle`` member function template, which takes a variadic number of
integer template arguments between ``0`` and ``NumElements-1``, specifying
swizzle indexes. Secondly by calling one of the simple swizzle member
functions defined as ``XYZW_SWIZZLE`` and ``RGBA_SWIZZLE``. Note that the
simple swizzle functions are only available for up to 4 element vectors and
are only available when the macro ``SYCL_SIMPLE_SWIZZLES`` is defined
before including ``<sycl/sycl.hpp>``.

In both cases the return type is always an instance of ``__swizzled_vec__``,
an implementation-defined temporary class representing the result of the
swizzle operation on the original ``sycl::vec`` instance. Since the swizzle
operation may result in a different number of elements, the
``__swizzled_vec__`` instance may represent a different number of elements
than the original ``sycl::vec``. Both kinds of swizzle member functions must
not perform the swizzle operation themselves, instead the swizzle operation
must be performed by the returned instance of ``__swizzled_vec__`` when used
within an expression, meaning if the returned ``__swizzled_vec__`` is never
used in an expression no swizzle operation is performed.

Both the ``swizzle`` member function template and the simple swizzle member
functions allow swizzle indexes to be repeated.

A series of static ``constexpr`` values are provided within the ``elem`` struct
to allow specifying named ``swizzle`` indexes when calling the swizzle
member function template.

============================
Swizzled ``sycl::vec`` class
============================

The ``__swizzled_vec__`` class must define an unspecified temporary which
provides the entire interface of the SYCL ``sycl::vec`` class template,
including swizzled member functions, with the additions and alterations
described below.
The member functions of the ``__swizzled_vec__`` class behave as though they
operate on a ``sycl::vec`` that is the result of the swizzle operation.

The ``__swizzled_vec__`` class template must be readable as an r-value
reference on the RHS of an expression. In this case the swizzle operation
is performed on the RHS of the expression and then the result is applied to
the LHS of the expression.

The ``__swizzled_vec__`` class template must be assignable as an l-value
reference on the LHS of an expression. In this case the RHS of the expression
is applied to the original SYCL ``sycl::vec`` which the ``__swizzled_vec__``
represents via the swizzle operation. Note that a ``__swizzled_vec__``
that is used in an l-value expression may not contain any repeated
element indexes.

For example: ``f4.xxxx() = fx.wzyx()`` would not be valid.

The ``__swizzled_vec__`` class template must be convertible to an instance of
SYCL ``sycl::vec`` with the type ``DataT`` and number of elements
specified by the swizzle member function, if ``NumElements > 1``, and must
be convertible to an instance of type
``DataT``, if ``NumElements == 1``.

The ``__swizzled_vec__`` class template must be non-copyable, non-moveable,
non-user constructible and may not be bound to a l-value or escape the
expression it was constructed in. For example ``auto x = f4.x()``
would not be valid.

The ``__swizzled_vec__`` class template should return ``__swizzled_vec__&``
for each operator inherited from the ``sycl::vec``
class template interface which would return
``vec<DataT``, ``NumElements>&``.

==============
Rounding modes
==============

.. rubric:: ``automatic``

Default rounding mode for the SYCL ``sycl::vec`` class element type.
``rtz`` (round toward zero) for integer types and ``rte``
(round to nearest even) for floating-point types.

.. rubric:: ``rte``

Round to nearest even.

.. rubric:: ``rtz``

Round toward zero.

.. rubric:: ``rtp``

Round toward positive infinity.

.. rubric:: ``rtn``

Round toward negative infinity.

===========================
Memory layout and alignment
===========================

The elements of an instance of the SYCL ``sycl::vec`` class template are
stored in memory sequentially and contiguously and are aligned to
the size of the element type in bytes multiplied by the number
of elements:

::

  sizeof(DataT)⋅NumElements

The exception to this is when the number of element is three in which
case the SYCL ``sycl::vec`` is aligned to the size of the element type in
bytes multiplied by four:

::

  sizeof(DataT)⋅4

This is true for both host and device code in order to allow for
instances of the ``sycl::vec`` class template to be passed to SYCL
kernel functions.

In no case, however, is the alignment guaranteed to be greater
than 64 bytes.

.. warning::

  The alignment guarantee is limited to 64 bytes because some host
  compilers (e.g. on Microsoft Windows) limit the maximum alignment
  of function parameters to this value.
