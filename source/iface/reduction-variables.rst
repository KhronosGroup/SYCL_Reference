..
  Copyright 2023 The Khronos Group Inc.
  SPDX-License-Identifier: CC-BY-4.0

.. _reduction-variables:

*******************
Reduction Variables
*******************

All functionality related to reductions is captured by the ``reducer``
class and the ``reduction`` function.

The example below demonstrates how to write a reduction kernel that
performs two reductions simultaneously on the same input values,
computing both the sum of all values in a buffer and the maximum
value in the buffer. For each reduction variable passed to
``parallel_for``, a reference to a ``reducer`` object is passed
as a parameter to the kernel function in the same order.

::

  buffer<int> valuesBuf { 1024 };
  {
    // Initialize buffer on the host with 0, 1, 2, 3, ..., 1023
    host_accessor a { valuesBuf };
    std::iota(a.begin(), a.end(), 0);
  }

  // Buffers with just 1 element to get the reduction results
  int sumResult = 0;
  buffer<int> sumBuf { &sumResult, 1 };
  int maxResult = 0;
  buffer<int> maxBuf { &maxResult, 1 };

  myQueue.submit([&](handler& cgh) {
    // Input values to reductions are standard accessors
    auto inputValues = valuesBuf.get_access<access_mode::read>(cgh);

    // Create temporary objects describing variables with reduction semantics
    auto sumReduction = reduction(sumBuf, cgh, plus<>());
    auto maxReduction = reduction(maxBuf, cgh, maximum<>());

    // parallel_for performs two reduction operations
    // For each reduction variable, the implementation:
    // - Creates a corresponding reducer
    // - Passes a reference to the reducer to the lambda as a parameter
    cgh.parallel_for(range<1> { 1024 }, sumReduction, maxReduction,
                     [=](id<1> idx, auto& sum, auto& max) {
                       // plus<>() corresponds to += operator, so sum can be
                       // updated via += or combine()
                       sum += inputValues[idx];

                       // maximum<>() has no shorthand operator, so max can only
                       // be updated via combine()
                       max.combine(inputValues[idx]);
                     });
  });

  // sumBuf and maxBuf contain the reduction results once the kernel completes
  assert(maxBuf.get_host_access()[0] == 1023 &&
         sumBuf.get_host_access()[0] == 523776);

Reductions are supported for all trivially copyable types (as defined
by the C++ core language). If the reduction operator is non-associative
or non-commutative, the behavior of a reduction may be non-deterministic.
If multiple reductions reference the same reduction variable, or a
reduction variable is accessed directly during the lifetime of a reduction
(e.g. via an ``accessor`` or USM pointer), the behavior is undefined.

Some of the overloads for the ``reduction`` function take an identity
value and some do not. An implementation is required to compute a correct
reduction even when the application does not specify an identity value.
However, the implementation may be more efficient when the identity value
is either provided by the application or is known by the implementation.
For reductions using standard binary operators and fundamental types
(e.g. ``plus`` and arithmetic types), an implementation can determine the
correct identity value automatically in order to avoid performance penalties.

If an implementation can identify an identity value for a given combination
of accumulator type and function object type, the value is defined as a member
of the ``known_identity`` trait class. Whether this member value exists can be
tested using the ``has_known_identity`` trait class.

::

  template <typename BinaryOperation, typename AccumulatorT>
  struct known_identity {
    static constexpr AccumulatorT value;
  };

  template <typename BinaryOperation, typename AccumulatorT>
  inline constexpr AccumulatorT known_identity_v =
      known_identity<BinaryOperation, AccumulatorT>::value;

  template <typename BinaryOperation, typename AccumulatorT>
  struct has_known_identity {
    static constexpr bool value;
  };

  template <typename BinaryOperation, typename AccumulatorT>
  inline constexpr bool has_known_identity_v =
      has_known_identity<BinaryOperation, AccumulatorT>::value;

================
Known identities
================

.. list-table::
  :header-rows: 1

  * - Operator
    - Available Only When
    - Identity
  * - ``sycl::plus``
    - ``std::is_arithmetic_v<AccumulatorT> || std::is_same_v<std::remove_cv_t<AccumulatorT>, sycl::half>``
    - ``AccumulatorT{}``
  * - ``sycl::multiplies``
    - ``std::is_arithmetic_v<AccumulatorT> || std::is_same_v<std::remove_cv_t<AccumulatorT>, sycl::half>``
    - ``AccumulatorT{1}``
  * - ``sycl::bit_and``
    - ``std::is_integral_v<AccumulatorT>``
    - ``~AccumulatorT{}``
  * - ``sycl::bit_or``
    - ``std::is_integral_v<AccumulatorT>``
    - ``AccumulatorT{}``
  * - ``sycl::bit_xor``
    - ``std::is_integral_v<AccumulatorT>``
    - ``AccumulatorT{}``
  * - ``sycl::logical_and``
    - ``std::is_same_v<std::remove_cv_t<AccumulatorT>, bool>``
    - ``true``
  * - ``sycl::logical_or``
    - ``std::is_same_v<std::remove_cv_t<AccumulatorT>, bool>``
    - ``false``
  * - ``sycl::minimum``
    - ``std::is_integral_v<AccumulatorT>``
    - ``std::numeric_limits<AccumulatorT>::max()``
  * - ``sycl::minimum``
    - ``std::is_floating_point_v<AccumulatorT> || std::is_same_v<std::remove_cv_t<AccumulatorT>, sycl::half>``
    - ``std::numeric_limits<AccumulatorT>::infinity()``
  * - ``sycl::maximum``
    - ``std::is_integral_v<AccumulatorT>``
    - ``std::numeric_limits<AccumulatorT>::lowest()``
  * - ``sycl::maximum``
    - ``std::is_floating_point_v<AccumulatorT> || std::is_same_v<std::remove_cv_t<AccumulatorT>, sycl::half>``
    - ``-std::numeric_limits<AccumulatorT>::infinity()``

The reduction interface is limited to reduction variables whose size can be
determined at compile-time. As such, ``buffer`` and USM pointer arguments
are interpreted by the reduction interface as describing a single variable.
A reduction operation associated with a ``span`` represents an array
reduction. An array reduction of size N is functionally equivalent to
specifying N independent scalar reductions. The combination operations
performed by an array reduction are limited to the extent of a USM
allocation described by a ``span``, and access to elements outside
of these regions results in undefined behavior.

``Known identities``
====================

The reduction interface is used to attach reduction semantics to a variable,
by specifying: the reduction variable, the reduction operator and an
optional identity value associated with the operator.
The return value of the reduction interface is an
implementation-defined object of unspecified type, which is interpreted
by parallel_for to construct an appropriate reducer type
as detailed in |SYCL_SPEC_REDUCER_CLASS|.
An implementation may use an unspecified number of temporary variables
inside of any ``reducer`` objects it creates. If an identity value
is supplied to a reduction, an implementation will use that value
to initialize any such temporary variables.

The initial value of the reduction variable is included in the reduction
operation, unless the ``property::reduction::initialize_to_identity``
property was specified when the ``reduction`` interface was invoked.

The reduction variable is updated so as to contain the result of the
reduction when the kernel finishes execution.

::

  template <typename BufferT, typename BinaryOperation>
  __unspecified__ reduction(BufferT vars, handler& cgh, BinaryOperation combiner,
                            const property_list& propList = {});

  template <typename T, typename BinaryOperation>
  __unspecified__ reduction(T* var, BinaryOperation combiner,
                            const property_list& propList = {});

  template <typename T, typename Extent, typename BinaryOperation>
  __unspecified__ reduction(span<T, Extent> vars, BinaryOperation combiner,
                            const property_list& propList = {});

  template <typename BufferT, typename BinaryOperation>
  __unspecified__
  reduction(BufferT vars, handler& cgh, const BufferT::value_type& identity,
            BinaryOperation combiner, const property_list& propList = {});

  template <typename T, typename BinaryOperation>
  __unspecified__ reduction(T* var, const T& identity, BinaryOperation combiner,
                            const property_list& propList = {});

  template <typename T, typename Extent, typename BinaryOperation>
  __unspecified__ reduction(span<T, Extent> vars, const T& identity,
                            BinaryOperation combiner,
                            const property_list& propList = {});

========================================
Overloads of the ``reduction`` interface
========================================

``reduction``
=============

::

  reduction<BufferT, BinaryOperation>(BufferT vars, handler& cgh,
                                      BinaryOperation combiner,
                                      const property_list& propList = {})

Construct an unspecified object representing a reduction of the variable(s)
described by ``vars`` using the combination operation specified by
``combiner``. Zero or more properties can be provided via an instance of
``property_list``. Throws an ``exception`` with the ``errc::invalid``
error code if the range of the ``vars`` buffer is not 1.

::

  reduction<T, BinaryOperation>(T* var, BinaryOperation combiner,
                              const property_list& propList = {})

Construct an unspecified object representing a reduction of the variable
described by ``var`` using the combination operation specified
by ``combiner``. Zero or more properties can be provided via
an instance of ``property_list``.

::

  reduction<T, BinaryOperation>(span<T, Extent> vars, BinaryOperation combiner,
                              const property_list& propList = {})

Available only when ``Extent != sycl::dynamic_extent``. Construct
an unspecified object representing a reduction of the variable(s)
described by ``vars`` using the combination operation specified
by ``combiner``. Zero or more properties can be provided via an
instance of ``property_list``.

::

  reduction<BufferT, BinaryOperation>(BufferT vars, handler& cgh,
                                    const BufferT::value_type& identity,
                                    BinaryOperation combiner,
                                    const property_list& propList = {})

Construct an unspecified object representing a reduction of the
variable(s) described by ``vars`` using the combination operation
specified by ``combiner``. The value of ``identity`` may be used
by the implementation to initialize an unspecified number of
temporary accumulation variables. Zero or more properties can
be provided via an instance of ``property_list``. Throws an
``exception`` with the ``errc::invalid`` error code if the
range of the ``vars`` buffer is not 1.

::

  reduction<T, BinaryOperation>(T* var, const T& identity,
                              BinaryOperation combiner,
                              const property_list& propList = {})

Construct an unspecified object representing a reduction of the
variable described by ``var`` using the combination operation
specified by ``combiner``. The value of ``identity`` may be
used by the implementation to initialize an unspecified number
of temporary accumulation variables. Zero or more properties
can be provided via an instance of ``property_list``.

::

  reduction<T, BinaryOperation>(span<T, Extent> vars, const T& identity,
                              BinaryOperation combiner,
                              const property_list& propList = {})

Available only when ``Extent != sycl::dynamic_extent``. Construct
an unspecified object representing a reduction of the variable(s)
described by ``vars`` using the combination operation specified by
``combiner``. The value of ``identity`` may be used by the
implementation to initialize an unspecified number of temporary
accumulation variables. Zero or more properties can be provided
via an instance of ``property_list``.

=====================
 Reduction properties
=====================

``initialize_to_identity``
==========================

::

  property::reduction::initialize_to_identity

The ``initialize_to_identity`` property adds the requirement that the SYCL
runtime must initialize the ``reduction`` variable to the identity value
passed to the reduction interface, or to the identity value determined
by the ``known_identity`` trait if no identity value was specified.
If no identity value was specified and an identity value cannot
be determined by the ``known_identity`` trait, the compiler must
raise a diagnostic. When this property is set, the original value
of the reduction variable is not included in the reduction.

Constructors of the ``reduction property`` classes
==================================================

::

  property::reduction::initialize_to_identity::initialize_to_identity()

Constructs an initialize_to_identity property instance.

``reducer class``
=================

::

  // Exposition only
  template <typename T, typename BinaryOperation, int Dimensions,
            /* unspecified */>
  class reducer;

The ``reducer`` class defines the interface between a work-item
and a reduction variable during the execution of a SYCL kernel,
restricting access to the underlying reduction variable.
The intermediate values of a reduction variable cannot be
inspected during kernel execution, and the variable cannot be
updated using anything other than the reduction’s specified
combination operation. The combination order of different
reducers is unspecified, as are when and how the value of
each reducer is combined with the original reduction variable.

An implementation must guarantee that it is safe for multiple
work-items in a kernel to call the combine function of a
``reducer`` concurrently. An implementation is free to re-use
reducer variables (e.g. across work-groups scheduled to the
same compute unit) if it can guarantee that it is safe to do so.

===================================================
Member types and constants of the ``reducer`` class
===================================================

::

  value_type

The data type of the reduction variable. If this reducer object was
created from a buffer type ``BufferT``, this type is
``BufferT::value_type``. If this reducer object was created from
a USM pointer ``T*`` or a ``span span<T``, ``Extent>``,
this type is ``T``.

::

  binary_operation

The type of the combiner operator ``BinaryOperation`` that was
passed to the reduction function that created this reducer object.

::

  static constexpr int dimensions

The number of dimensions of the reduction variable.
If this reducer object was created from a buffer or a USM pointer,
the number of dimensions is ``0``. If this reducer object was
created from a span, the number of dimensions is ``1``.

=========================================
Member functions of the ``reducer`` class
=========================================

``combine``
===========

::

  reducer& combine(const T& partial)

Available only when: ``Dimensions == 0``. Combine the value
of ``partial`` with the reduction variable associated with
this ``reducer``. Returns ``*this``.

``operator[]``
==============

::

  __unspecified__ operator[](size_t index)

Available only when: ``Dimensions > 0``. Returns an instance of
an undefined intermediate type representing a ``reducer`` of
the same type as this ``reducer``, with the dimensionality
``Dimensions-1`` and containing an implicit SYCL ``id``
with index ``Dimensions`` set to ``index``. The intermediate
type returned must provide all member functions and operators
defined by the ``reducer`` class that are appropriate for the
type it represents (including this subscript operator).

``identity``
============

::

  T identity() const

Return the identity value of the combination operation
associated with this ``reducer``. Only available if the
identity value is known to the implementation.

============================================
Hidden friend operators of the reducer class
============================================

``operator+=``
==============

::

  reducer& operator+=(reducer& accum, const T& partial)

Equivalent to calling ``accum.combine(partial)``. Available only when:
``Dimensions == 0 && (std::is_same_v<BinaryOperation, plus<>>
|| std::is_same_v<BinaryOperation, plus<T>>)``.

``operator*=``
==============

::

  reducer& operator*=(reducer& accum, const T& partial)

Equivalent to calling ``accum.combine(partial)``. Available only when:
``Dimensions == 0 && (std::is_same_v<BinaryOperation, multiplies<>>
|| std::is_same_v<BinaryOperation, multiplies<T>>)``.

``operator&=``
==============

::

  reducer& operator&=(reducer& accum, const T& partial)

Equivalent to calling ``accum.combine(partial)``. Available only when:
``Dimensions == 0 && is_integral_v<T> &&
(std::is_same_v<BinaryOperation, bit_and<>> ||
std::is_same_v<BinaryOperation, bit_and<T>>)``.

``operator|=``
==============

::

  reducer& operator|=(reducer& accum, const T& partial)

Equivalent to calling ``accum.combine(partial)``. Available only when:
``Dimensions == 0 && is_integral_v<T> &&
(std::is_same_v<BinaryOperation, bit_or<>> ||
std::is_same_v<BinaryOperation, bit_or<T>>)``.

``operator^=``
==============

::

  reducer& operator^=(reducer& accum, const T& partial)

Equivalent to calling ``accum.combine(partial)``. Available only when:
``Dimensions == 0 && is_integral_v<T> &&
(std::is_same_v<BinaryOperation, bit_xor<>> |
std::is_same_v<BinaryOperation, bit_xor<T>>)``.

``operator++``
==============

::

  reducer& operator++(reducer& accum)

Equivalent to calling ``accum.combine(1)``. Available only when:
``Dimensions == 0 && std::is_integral_v<T> &&
!std::is_same_v<T, bool> && (std::is_same_v<BinaryOperation, plus<>> ||
std::is_same_v<BinaryOperation, plus<T>>)``.
