..
  Copyright 2023 The Khronos Group Inc.
  SPDX-License-Identifier: CC-BY-4.0

.. _math-array-types:

****************
Math array types
****************

SYCL provides an ``marray<typename DataT, std::size_t NumElements>``
class template to represent a contiguous fixed-size container. This
type allows sharing of containers between the host and its SYCL devices.

The ``marray`` class is templated on its element type and number of
elements. The number of elements parameter, ``NumElements``, is a
positive value of the ``std::size_t`` type. The element type
parameter, ``DataT``, must be a numeric type as it is defined
by C++ standard.

An instance of the ``marray`` class template can also be implicitly
converted to an instance of the data type when the number of elements
is 1 in order to allow single element arrays and scalars to be
convertible with each other.

Logical and comparison operators for ``marray`` class template
return ``marray<bool``, ``NumElements>``.

================
``sycl::marray``
================

::

  template <typename DataT, std::size_t NumElements>
  class marray;

(constructors)
==============

.. rubric:: Constructor 1

::

  marray();

Default construct an array with element type ``DataT`` and with
``NumElements`` dimensions by default construction of each of its elements.

.. rubric:: Constructor 2

::

  explicit constexpr marray(const DataT& arg);

Construct an array of element type ``DataT`` and ``NumElements``
dimensions by setting each value to ``arg`` by assignment.

.. rubric:: Constructor 3

::

  template <typename... ArgTN>
  constexpr marray(const ArgTN&... args);

Construct a SYCL ``marray`` instance from any combination of scalar and
SYCL ``marray`` parameters of the same element type, providing the total
number of elements for all parameters sum to ``NumElements`` of this
``marray`` specialization.

.. rubric:: Constructor 4

::

  constexpr marray(const marray<DataT, NumElements>& rhs);

Construct an array of element type ``DataT`` and number of elements
``NumElements`` by copy from another similar vector.

.. rubric:: Constructor 5

::

  constexpr marray(marray<DataT, NumElements>&& rhs);

Construct an array of element type ``DataT`` and number of elements
``NumElements`` by moving from another similar vector.


================
Member functions
================

``DataT``
=========

::

  operator DataT() const

Available only when: ``NumElements == 1``.

Converts this SYCL ``marray`` instance to an instance of ``DataT`` with
the value of the single element in this SYCL ``marray`` instance.

The SYCL ``marray`` instance shall be implicitly convertible to the same
data types, to which ``DataT`` is implicitly convertible. Note that
conversion operator shall not be templated to allow standard conversion
sequence for implicit conversion.

``size``
========

::

  static constexpr std::size_t size() noexcept

Returns the size of this SYCL ``marray`` in bytes.

``operator[]``
==============

::

  DataT& operator[](std::size_t index);

Returns a reference to the element stored within this SYCL
``marray`` at the index specified by ``index``.

::

  const DataT& operator[](std::size_t index) const

Returns a reference to the element stored within this SYCL
``marray`` at the index specified by ``index``.

``operator=``
=============

::

  marray& operator=(const marray& rhs);

Assign each element of the ``rhs`` SYCL ``marray`` to each element of
this SYCL ``marray`` and return a reference to this SYCL ``marray``.

::

  marray& operator=(const DataT& rhs);

Assign each element of the ``rhs`` scalar to each element of this SYCL
``marray`` and return a reference to this SYCL ``marray``.

``begin``
=========

::

  iterator begin();

Returns an iterator referring to the first element stored within the
``v marray``.

::

  const_iterator begin() const

Returns a ``const`` iterator referring to the first element stored within the
``v marray``.

``end``
=======

::

  iterator begin();

Returns an iterator referring to the one past the last element stored
within the ``v marray``.

::

  const_iterator end() const

Returns a ``const`` iterator referring to the one past the last element
stored within the ``v marray``.

=======================
Hidden friend functions
=======================

::

  marray operatorOP(const marray& lhs, const marray& rhs);

If ``OP`` is ``%``, available only when:
``DataT != float && DataT != double && DataT != half``.

Construct a new instance of the SYCL ``marray`` class template with the
same template parameters as ``lhs marray`` with each element of the new
SYCL ``marray`` instance the result of an element-wise ``OP`` arithmetic
operation between each element of ``lhs marray`` and each element of
the ``rhs`` SYCL ``marray``.

Where ``OP`` is: ``+``, ``-``, ``*``, ``/``, ``%``.

::

  marray operatorOP(const marray& lhs, const DataT& rhs);

If ``OP`` is ``%``, available only when:
``DataT != float && DataT != double && DataT != half``.

Construct a new instance of the SYCL ``marray`` class template with the
same template parameters as ``lhs marray`` with each element of the new
SYCL ``marray`` instance the result of an element-wise ``OP`` arithmetic
operation between each element of ``lhs marray`` and the ``rhs`` scalar.

Where ``OP`` is: ``+``, ``-``, ``*``, ``/``, ``%``.

::

  marray& operatorOP(marray& lhs, const marray& rhs);

If ``OP`` is ``%=``, available only when:
``DataT != float && DataT != double &&
DataT != half``.

Perform an in-place element-wise ``OP`` arithmetic operation between
each element of ``lhs marray`` and each element of the ``rhs``
SYCL ``marray`` and return ``lhs marray``.

Where ``OP`` is: ``+=``, ``-=``, ``*=``, ``/=``, ``%=``.

::

  marray& operatorOP(marray& lhs, const DataT& rhs);

If ``OP`` is ``%=``, available only when:
``DataT != float && DataT != double && DataT != half``.

Perform an in-place element-wise ``OP`` arithmetic operation between
each element of ``lhs marray`` and ``rhs`` scalar and return
``lhs marray``.

Where ``OP`` is: ``+=``, ``-=``, ``*=``, ``/=``, ``%=``.

::

  marray& operatorOP(marray& v);

Perform an in-place element-wise ``OP`` prefix arithmetic operation on
each element of ``v marray``, assigning the result of each element to
the corresponding element of ``v marray`` and return ``v marray``.

Where ``OP`` is: ``++``, ``--``.

::

  marray operatorOP(marray& v, int);

Perform an in-place element-wise ``OP`` postfix arithmetic operation on
each element of ``v marray``, assigning the result of each element to
the corresponding element of ``v marray`` and returns a copy of
``v marray`` before the operation is performed.

Where ``OP`` is: ``++``, ``--``.

::

  marray operatorOP(marray& v);

Construct a new instance of the SYCL ``marray`` class template with the
same template parameters as this SYCL ``marray`` with each element of
the new SYCL ``marray`` instance the result of an element-wise ``OP``
unary arithmetic operation on each element of this SYCL ``marray``.

Where ``OP`` is: ``+``, ``-``.

::

  marray operatorOP(const marray& lhs, const marray& rhs);

Available only when:
``DataT != float && DataT != double && DataT != half``.

Construct a new instance of the SYCL ``marray`` class template with the
same template parameters as ``lhs marray`` with each element of the new
SYCL ``marray`` instance the result of an element-wise ``OP`` bitwise
operation between each element of ``lhs marray`` and each element of
the ``rhs`` SYCL ``marray``.

Where ``OP`` is: ``&``, ``|``, ``^``.

::

  marray operatorOP(const marray& lhs, const DataT& rhs);

Available only when:
``DataT != float && DataT != double && DataT != half``.

Construct a new instance of the SYCL ``marray`` class template with the
same template parameters as ``lhs marray`` with each element of the new
SYCL ``marray`` instance the result of an element-wise ``OP`` bitwise
operation between each element of ``lhs marray`` and the ``rhs`` scalar.

Where ``OP`` is: ``&``, ``|``, ``^``.

::

  marray& operatorOP(marray& lhs, const marray& rhs);

Available only when:
``DataT != float && DataT != double && DataT != half``.

Perform an in-place element-wise ``OP`` bitwise operation between each
element of ``lhs marray`` and the ``rhs`` SYCL ``marray`` and return
``lhs marray``.

Where ``OP`` is: ``&=``, ``|=``, ``^=``.

::

  marray& operatorOP(marray& lhs, const DataT& rhs);

Available only when:
``DataT != float && DataT != double && DataT != half``.

Perform an in-place element-wise ``OP`` bitwise operation between each
element of ``lhs marray`` and the ``rhs`` scalar and return a
``lhs marray``.

Where ``OP`` is: ``&=``, ``|=``, ``^=``.

::

  marray<bool, NumElements> operatorOP(const marray& lhs, const marray& rhs);

Construct a new instance of the ``marray`` class template with
``DataT = bool`` and same NumElements as ``lhs marray`` with each element
of the new ``marray`` instance the result of an element-wise ``OP`` logical
operation between each element of ``lhs marray`` and each element of the
``rhs marray``.

Where ``OP`` is: ``&&``, ``||``.

::

  marray<bool, NumElements> operatorOP(const marray& lhs, const DataT& rhs);

Construct a new instance of the ``marray`` class template with ``DataT = bool``
and same NumElements as ``lhs marray`` with each element of the new ``marray``
instance the result of an element-wise ``OP`` logical operation between
each element of ``lhs marray`` and the ``rhs`` scalar.

Where ``OP`` is: ``&&``, ``||``.

::

  marray operatorOP(const marray& lhs, const marray& rhs);

Available only when:
``DataT != float && DataT != double && DataT != half``.

Construct a new instance of the SYCL ``marray`` class template with the
same template parameters as ``lhs marray`` with each element of the new
SYCL ``marray`` instance the result of an element-wise ``OP`` bitshift
operation between each element of ``lhs marray`` and each element of the
``rhs`` SYCL ``marray``. If ``OP`` is ``>>``, ``DataT`` is a signed type
and ``lhs marray`` has a negative value any vacated bits viewed as an
unsigned integer must be assigned the value ``1``, otherwise any vacated
bits viewed as an unsigned integer must be assigned the value ``0``.

Where ``OP`` is: ``<<``, ``>>``.

::

  marray operatorOP(const marray& lhs, const DataT& rhs);

Available only when:
``DataT != float && DataT != double && DataT != half``.

Construct a new instance of the SYCL ``marray`` class template with the same
template parameters as ``lhs marray`` with each element of the new SYCL
``marray`` instance the result of an element-wise ``OP`` bitshift operation
between each element of ``lhs marray`` and the ``rhs`` scalar. If ``OP`` is
``>>``, ``DataT`` is a signed type and ``lhs marray`` has a negative value
any vacated bits viewed as an unsigned integer must be assigned the value
``1``, otherwise any vacated bits viewed as an unsigned integer must be
assigned the value ``0``.

Where ``OP`` is: ``<<``, ``>>``.

::

  marray& operatorOP(marray& lhs, const marray& rhs);

Available only when: ``DataT != float && DataT != double && DataT != half``.

Perform an in-place element-wise ``OP`` bitshift operation between each
element of ``lhs marray`` and the ``rhs`` SYCL ``marray`` and returns
``lhs marray``. If ``OP`` is ``>>=``, ``DataT`` is a signed type and
``lhs marray`` has a negative value any vacated bits viewed as an unsigned
integer must be assigned the value ``1``, otherwise any vacated bits viewed
as an unsigned integer must be assigned the value ``0``.

Where ``OP`` is: ``<<=``, ``>>=``.

::

  marray& operatorOP(marray& lhs, const DataT& rhs);

Available only when:
``DataT != float && DataT != double && DataT != half``.

Perform an in-place element-wise ``OP`` bitshift operation between each
element of ``lhs marray`` and the ``rhs`` scalar and returns a reference
to this SYCL ``marray``. If ``OP`` is ``>>=``, ``DataT`` is a signed type
and ``lhs marray`` has a negative value any vacated bits viewed as an
unsigned integer must be assigned the value ``1``, otherwise any vacated
bits viewed as an unsigned integer must be assigned the value ``0``.

Where ``OP`` is: ``<<=``, ``>>=``.

::

  marray<bool, NumElements> operatorOP(const marray& lhs, const marray& rhs);

Construct a new instance of the ``marray`` class template with
``DataT = bool`` and same NumElements as ``lhs marray`` with each element of
the new ``marray`` instance is the result of an element-wise ``OP`` relational
operation between each element of ``lhs marray`` and each element of the
``rhs marray``. The ``==``, ``<``, ``>``, ``<=`` and ``>=`` operations result
in ``false`` if either the ``lhs`` element or the ``rhs`` element is a
``NaN``. The ``!=`` operation results in ``true`` if either the ``lhs``
element or the ``rhs`` element is a ``NaN``.

Where ``OP`` is: ``==``, ``!=``, ``<``, ``>``, ``<=``, ``>=``.

::

  marray<bool, NumElements> operatorOP(const marray& lhs, const DataT& rhs);

Construct a new instance of the ``marray`` class template with
``DataT = bool`` and same NumElements as ``lhs marray`` with each element
of the new ``marray`` instance the result of an element-wise ``OP``
relational operation between each element of ``lhs marray`` and the ``rhs``
scalar. The ``==``, ``<``, ``>``, ``<=`` and ``>=`` operations result in
``false`` if either the ``lhs`` element or the ``rhs`` is a ``NaN``. The
``!=`` operation results in ``true`` if either the ``lhs`` element or the
``rhs`` is a ``NaN``.

Where ``OP`` is: ``==``, ``!=``, ``<``, ``>``, ``<=``, ``>=``.

::

  marray operatorOP(const DataT& lhs, const marray& rhs);

If ``OP`` is ``%``, available only when:
``DataT != float && DataT != double && DataT != half``.

Construct a new instance of the SYCL ``marray`` class template with the same
template parameters as the ``rhs`` SYCL ``marray`` with each element of the
new SYCL ``marray`` instance the result of an element-wise ``OP`` arithmetic
operation between the ``lhs`` scalar and each element of the ``rhs``
SYCL ``marray``.

Where ``OP`` is: ``+``, ``-``, ``*``, ``/``, ``%``.

::

  marray operatorOP(const DataT& lhs, const marray& rhs);

Available only when:
``DataT != float && DataT != double && DataT != half``.

Construct a new instance of the SYCL ``marray`` class template with the same
template parameters as the ``rhs`` SYCL ``marray`` with each element of the
new SYCL ``marray`` instance the result of an element-wise ``OP`` bitwise
operation between the ``lhs`` scalar and each element of the ``rhs`` SYCL
``marray``.

Where ``OP`` is: ``&``, ``|``, ``^``.

::

  marray<bool, NumElements> operatorOP(const DataT& lhs, const marray& rhs);

Construct a new instance of the ``marray`` class template with ``DataT = bool``
and same NumElements as ``rhs marray`` with each element of the new ``marray``
instance the result of an element-wise ``OP`` logical operation between the
``lhs`` scalar and each element of the ``rhs marray``.

Where ``OP`` is: ``&&``, ``||``.

::

  marray operatorOP(const DataT& lhs, const marray& rhs);

Construct a new instance of the SYCL ``marray`` class template with the same
template parameters as the ``rhs`` SYCL ``marray`` with each element of the
new SYCL ``marray`` instance the result of an element-wise ``OP`` bitshift
operation between the ``lhs`` scalar and each element of the ``rhs`` SYCL
``marray``. If ``OP`` is ``>>``, ``DataT`` is a signed type and this SYCL
``marray`` has a negative value any vacated bits viewed as an unsigned
integer must be assigned the value ``1``, otherwise any vacated bits viewed
as an unsigned integer must be assigned the value ``0``.

Where ``OP`` is: ``<<``, ``>>``.

::

  marray<bool, NumElements> operatorOP(const DataT& lhs, const marray& rhs);

Construct a new instance of the ``marray`` class template with ``DataT = bool``
and same NumElements as ``rhs marray`` with each element of the new SYCL
``marray`` instance the result of an element-wise ``OP`` relational operation
between the ``lhs`` scalar and each element of the ``rhs marray``. The ``==``,
``<``, ``>``, ``<=`` and ``>=`` operations result in ``false`` if either the
``lhs`` or the ``rhs`` element is a ``NaN``. The ``!=`` operation results in
``true`` if either the ``lhs`` or the ``rhs`` element is a ``NaN``.

Where ``OP`` is: ``==``, ``!=``, ``<``, ``>``, ``<=``, ``>=``.

::

  marray& operator~(const marray& v);

Available only when:
``DataT != float && DataT != double && DataT != half``.

Construct a new instance of the SYCL ``marray`` class template with the same
template parameters as ``v marray`` with each element of the new SYCL
``marray`` instance the result of an element-wise ``OP`` bitwise operation
on each element of ``v marray``.

::

  marray<bool, NumElements> operator!(const marray& v);

Construct a new instance of the ``marray`` class template with
``DataT = bool`` and same NumElements as ``v marray`` with each element of
the new ``marray`` instance the result of an element-wise logical ``!``
operation on each element of ``v marray``.

=======
Aliases
=======

The SYCL programming API provides all permutations of the type alias:

``using m<type><elems> = marray<<storage-type>, <elems>>``

where ``<elems>`` is ``2``, ``3``, ``4``, ``8`` and ``16``, and pairings
of ``<type>`` and ``<storage-type>`` for integral types are ``char`` and
``int8_t``, ``uchar`` and ``uint8_t``, ``short`` and ``int16_t``,
``ushort`` and ``uint16_t``, ``int`` and ``int32_t``, ``uint`` and
``uint32_t``, ``long`` and ``int64_t``, ``ulong`` and ``uint64_t``,
for floating point types are both ``half``, ``float`` and ``double``,
and for boolean type ``bool``.

For example ``muint4`` is the alias to ``marray<uint32_t, 4>``
and ``mfloat16`` is the alias to ``marray<float, 16>``.

===========================
Memory layout and alignment
===========================

The elements of an instance of the ``marray`` class template as if
stored in ``std::array<DataT, NumElements>``.
