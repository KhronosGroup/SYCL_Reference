..
  Copyright 2023 The Khronos Group Inc.
  SPDX-License-Identifier: CC-BY-4.0

.. _atomic_ref:

********************
``sycl::atomic_ref``
********************

::

  template <typename T, sycl::memory_order DefaultOrder, sycl::memory_scope DefaultScope,
    sycl::access::address_space AddressSpace = sycl::access::address_space::generic_space>
  class atomic_ref;

The ``sycl::atomic_ref`` class provides the ability to perform
atomic operations in device code with a syntax similar to the
C++ standard ``std::atomic_ref``. The ``sycl::atomic_ref``
class must not be used in host code.

The atomic operations and member functions behave as described
in the C++ specification, barring the restrictions discussed below.

.. note::

  Care must be taken when using atomics for work-item coordination,
  because work-items are not required to provide stronger than weakly
  parallel forward progress guarantees. Operations that block a
  work-item, such as continuously checking the value of an atomic
  variable until some condition holds, or using atomic operations
  that are not lock-free, may prevent overall progress.

.. seealso:: |SYCL_SPEC_ATOMIC_REF|

===================
Template parameters
===================

``DefaultOrder``
================

Unlike ``std::atomic_ref``, ``sycl::atomic_ref`` does not provide
a default memory ordering for its operations. Instead, the
application must specify a default ordering via the ``DefaultOrder``
template parameter. This ordering is used as a default for most of
the atomic operations, but most member functions also provide an
optional parameter that allows the application to override this
default.

* The set of supported orderings is specific to a device, but every
  device is guaranteed to support at least
  ``sycl::memory_order::relaxed``.
* If the default order is set to ``sycl::memory_order::relaxed``,
  all memory order arguments default to ``sycl::memory_order::relaxed``.
* If the default order is set to ``sycl::memory_order::acq_rel``,
  memory order arguments default to ``sycl::memory_order::acquire``
  for load operations, ``sycl::memory_order::release`` for store
  operations and ``sycl::memory_order::acq_rel`` for read-modify-write
  operations.
* If the default order is set to ``sycl::memory_order::seq_cst``, all
  memory order arguments default to ``sycl::memory_order::seq_cst``.

``DefaultScope``
================

The ``sycl::atomic_ref`` class has a template parameter ``DefaultScope``,
which allows the application to define a default memory scope for the
atomic operations. Most member functions also provide an optional parameter
that allows the application to override this default.

``AddressSpace``
================

The ``sycl::atomic_ref`` class has a template parameter ``AddressSpace``,
which allows the application to make an assertion about the address space
of the object of type ``T`` that it references.

The default value for this
parameter is ``sycl::access::address_space::generic_space``, which indicates
that the object could be in either the global or local address spaces.

If the application knows the address space, it can set this template
parameter to either ``sycl::access::address_space::global_space`` or
``sycl::access::address_space::local_space`` as an assertion to
the implementation.

Specifying the address space via this template parameter may allow
the implementation to perform certain optimizations. Specifying an
address space that does not match the object's actual address space
results in undefined behavior.

Type ``T``
==========

The template parameter T must be one of the following types:

* ``int``
* ``unsigned int``
* ``long``
* ``unsigned long``
* ``long long``
* ``unsigned long long``
* ``float``
* ``double``

In addition, the type ``T`` must satisfy **one of** the
following conditions:

* ``sizeof(T) == 4``
* ``sizeof(T) == 8`` and the code containing this
  ``sycl::atomic_ref`` was submitted to a device
  that has ``sycl::aspect::atomic64``.

For floating-point types, the member functions of the ``sycl::atomic_ref``
class may be emulated, and they may use a different floating-point
environment from those defined by ``sycl::info::device::single_fp_config``
and ``sycl::info::device::double_fp_config`` (i.e. floating-point atomics
may use different rounding modes and may have different exception behavior).



==============
Static members
==============

1. The static member ``required_alignment`` describes the minimum
   required alignment in bytes of an object that can be referenced
   by an ``sycl::atomic_ref<T>``, which must be at least ``alignof(T)``.
2. The static member ``is_always_lock_free`` is ``true`` if all atomic
   operations for type ``T`` are always lock-free. A SYCL implementation
   is not guaranteed to support atomic operations that are not lock-free.
3. The static members ``default_read_order``, ``default_write_order`` and
   ``default_read_modify_write_order`` reflect the default memory order
   values for each type of atomic operation, consistent with the
   ``DefaultOrder`` template.







==============
(constructors)
==============

::

  atomic_ref(T& ref);

Constructs an instance of ``sycl::atomic_ref`` which is
associated with the reference ``ref``.

================
Member functions
================

Available on any ``sycl::atomic_ref<T>`` object
===============================================

``is_lock_free``
----------------

::

  bool is_lock_free() const;

Return ``true`` if the atomic operations provided
by this ``sycl::atomic_ref`` are lock-free.

``store``
---------

::

  void store(T operand,
             sycl::memory_order order = default_write_order,
             sycl::memory_scope scope = default_scope) const;

Atomically stores ``operand`` to the object referenced by
this ``sycl::atomic_ref``. The memory order of this atomic
operation must be ``sycl::memory_order::relaxed``,
``sycl::memory_order::release`` or ``sycl::memory_order::seq_cst``.
This function is only supported for 64-bit data types on devices
that have ``sycl::aspect::atomic64``.

``operator=``
-------------

::

  T operator=(T desired) const;

Equivalent to ``store(desired)``. Returns ``desired``.

``load``
--------

::

  T load(sycl::memory_order order = default_read_order,
         sycl::memory_scope scope = default_scope) const

Atomically loads the value of the object referenced by this
``sycl::atomic_ref``. The memory order of this atomic
operation must be ``sycl::memory_order::relaxed``,
``sycl::memory_order::acquire``, or ``sycl::memory_order::seq_cst``.
This function is only supported for 64-bit data types on devices
that have ``sycl::aspect::atomic64``.

Cast operator to ``T``
----------------------

::

  operator T() const;

Equivalent to ``load()``.

``exchange``
------------

::

  T exchange(T operand,
             sycl::memory_order order = default_read_modify_write_order,
             sycl::memory_scope scope = default_scope) const

Atomically replaces the value of the object referenced by this
``sycl::atomic_ref`` with value ``operand`` and returns the
original value of the referenced object. This function is only
supported for 64-bit data types on devices that have
``sycl::aspect::atomic64``.

``compare_exchange_weak``
-------------------------

.. rubric:: Overload 1

::

  bool compare_exchange_weak(T& expected, T desired,
                             sycl::memory_order success,
                             sycl::memory_order failure,
                             sycl::memory_scope scope = default_scope) const;

Atomically compares the value of the object referenced by
this ``sycl::atomic_ref`` against the value of ``expected``.
If the values are equal, attempts to replace the value of the
referenced object with the value of ``desired``; otherwise assigns
the original value of the referenced object to ``expected``.

Returns ``true`` if the comparison operation and replacement
operation were successful. The ``failure`` memory order of
this atomic operation must be ``sycl::memory_order::relaxed``,
``sycl::memory_order::acquire`` or ``sycl::memory_order::seq_cst``.

This function is only supported for 64-bit data types on devices
that have ``sycl::aspect::atomic64``.

.. rubric:: Overload 2

::

  bool compare_exchange_weak(T& expected, T desired,
                             sycl::memory_order order = default_read_modify_write_order,
                             sycl::memory_scope scope = default_scope) const;

Equivalent to
``compare_exchange_weak(expected, desired, order, order, scope)``.

``compare_exchange_strong``
---------------------------

.. rubric:: Overload 1

::

  bool compare_exchange_strong(T& expected, T desired,
                               sycl::memory_order success,
                               sycl::memory_order failure,
                               sycl::memory_scope scope = default_scope) const;

Atomically compares the value of the object referenced by
this ``sycl::atomic_ref`` against the value of expected.
If the values are equal, replaces the value of the referenced
object with the value of ``desired``; otherwise assigns the
original value of the referenced object to ``expected``.

Returns ``true`` if the comparison operation and replacement
operation were successful. The ``failure`` memory order of
this atomic operation must be ``sycl::memory_order::relaxed``,
``sycl::memory_order::acquire`` or ``sycl::memory_order::seq_cst``.

This function is only supported for 64-bit data types on devices
that have ``sycl::aspect::atomic64``.

.. rubric:: Overload 2

::

  bool compare_exchange_strong(T& expected, T desired,
                               sycl::memory_order order = default_read_modify_write_order,
                               sycl::memory_scope scope = default_scope) const;

Equivalent to
``compare_exchange_strong(expected, desired, order, order, scope)``.


Available on ``sycl::atomic_ref<T>`` object for integral ``T``
==============================================================

``fetch_add``
-------------

::

  T fetch_add(T operand,
              sycl::memory_order order = default_read_modify_write_order,
              sycl::memory_scope scope = default_scope) const;

Atomically adds ``operand`` to the value of the object
referenced by this ``sycl::atomic_ref`` and assigns the
result to the value of the referenced object. Returns
the original value of the referenced object. This function
is only supported for 64-bit data types on devices that
have ``sycl::aspect::atomic64``.

``operator+=``
--------------

::

  T operator+=(ptrdiff_t operand) const;

Equivalent to ``fetch_add(operand) + operand``.

``operator++``
--------------

::

  T operator++(int) const;

Equivalent to ``fetch_add(1)``.

::

  T operator++() const;

Equivalent to ``fetch_add(1) + 1``.


``fetch_sub``
-------------

::

  T fetch_sub(T operand,
              sycl::memory_order order = default_read_modify_write_order,
              sycl::memory_scope scope = default_scope) const;

Atomically subtracts ``operand`` from the value of the
object referenced by this ``sycl::atomic_ref`` and
assigns the result to the value of the referenced
object. Returns the original value of the referenced
object. This function is only supported for 64-bit
pointers on devices that have ``sycl::aspect::atomic64``.

``operator-=``
--------------

::

  T operator-=(ptrdiff_t operand) const;

Equivalent to ``fetch_sub(operand) - operand``.

``operator--``
--------------

::

  T operator--(int) const;

Equivalent to ``fetch_sub(1)``.

::

  T operator--() const;

Equivalent to ``fetch_sub(1) - 1``.

``fetch_and``
-------------

::

  T fetch_or(T operand,
              sycl::memory_order order = default_read_modify_write_order,
              sycl::memory_scope scope = default_scope) const

Atomically performs a bitwise AND between ``operand`` and the
value of the object referenced by this ``sycl::atomic_ref``,
and assigns the result to the value of the referenced object.
Returns the original value of the referenced object.
This function is only supported for 64-bit data types on
devices that have ``sycl::aspect::atomic64``.


``operator&=``
--------------

::

  T operator&=(T operand) const;

Equivalent to ``fetch_and(operand) & operand``.

``fetch_or``
-------------

::

  T fetch_or(T operand,
              sycl::memory_order order = default_read_modify_write_order,
              sycl::memory_scope scope = default_scope) const

Atomically performs a bitwise OR between ``operand`` and the
value of the object referenced by this ``sycl::atomic_ref``,
and assigns the result to the value of the referenced object.
Returns the original value of the referenced object.
This function is only supported for 64-bit data types on
devices that have ``sycl::aspect::atomic64``.


``operator|=``
--------------

::

  T operator|=(T operand) const;

Equivalent to ``fetch_or(operand) | operand``.

``fetch_xor``
-------------

::

  T fetch_xor(T operand,
              sycl::memory_order order = default_read_modify_write_order,
              sycl::memory_scope scope = default_scope) const

Atomically performs a bitwise XOR between ``operand`` and the
value of the object referenced by this ``sycl::atomic_ref``,
and assigns the result to the value of the referenced object.
Returns the original value of the referenced object.
This function is only supported for 64-bit data types on
devices that have ``sycl::aspect::atomic64``.


``operator^=``
--------------

::

  T operator^=(T operand) const;

Equivalent to ``fetch_xor(operand) ^ operand``.


``fetch_min``
-------------

::

  T fetch_min(T operand,
              sycl::memory_order order = default_read_modify_write_order,
              sycl::memory_scope scope = default_scope) const;

Atomically computes the minimum of ``operand`` and the value
of the object referenced by this ``sycl::atomic_ref``, and
assigns the result to the value of the referenced object.
Returns the original value of the referenced object. This
function is only supported for 64-bit data types on devices
that have ``sycl::aspect::atomic64``.

``fetch_max``
-------------

::

  T fetch_max(T operand,
              sycl::memory_order order = default_read_modify_write_order,
              sycl::memory_scope scope = default_scope) const;

Atomically computes the maximum of ``operand`` and the value
of the object referenced by this ``sycl::atomic_ref``, and
assigns the result to the value of the referenced object.
Returns the original value of the referenced object. This
function is only supported for 64-bit data types on devices
that have ``sycl::aspect::atomic64``.


Available on ``sycl::atomic_ref<T>`` object for floating-point ``T``
====================================================================

``fetch_add``
-------------

::

  T fetch_add(T operand,
              sycl::memory_order order = default_read_modify_write_order,
              sycl::memory_scope scope = default_scope) const;

Atomically adds ``operand`` to the value of the object referenced
by this ``sycl::atomic_ref`` and assigns the result to the value
of the referenced object. Returns the original value of the
referenced object. This function is only supported for 64-bit data
types on devices that have ``sycl::aspect::atomic64``.

``operator+=``
--------------

::

  T operator+=(T operand) const;

Equivalent to ``fetch_add(operand) + operand``.

``fetch_sub``
-------------

::

  T fetch_sub(T operand,
              sycl::memory_order order = default_read_modify_write_order,
              sycl::memory_scope scope = default_scope) const

Atomically subtracts ``operand`` from the value of the object
referenced by this ``sycl::atomic_ref`` and assigns the result to
the value of the referenced object. Returns the original value of
the referenced object. This function is only supported for 64-bit
data types on devices that have ``sycl::aspect::atomic64``.

``operator-=``
--------------

::

  T operator-=(T operand) const;

Equivalent to ``fetch_sub(operand) - operand``.

``fetch_min``
-------------

::

  T fetch_min(T operand,
              sycl::memory_order order = default_read_modify_write_order,
              sycl::memory_scope scope = default_scope) const;

Atomically computes the minimum of ``operand`` and the value
of the object referenced by this ``sycl::atomic_ref``, and
assigns the result to the value of the referenced object.
Returns the original value of the referenced object. This
function is only supported for 64-bit data types on devices
that have ``sycl::aspect::atomic64``.

``fetch_max``
-------------

::

  T fetch_max(T operand,
              sycl::memory_order order = default_read_modify_write_order,
              sycl::memory_scope scope = default_scope) const;

Atomically computes the maximum of ``operand`` and the value
of the object referenced by this ``sycl::atomic_ref``, and
assigns the result to the value of the referenced object.
Returns the original value of the referenced object. This
function is only supported for 64-bit data types on devices
that have ``sycl::aspect::atomic64``.


Available on ``sycl::atomic_ref<T*>`` object
============================================

``fetch_add``
-------------

::

  T* fetch_add(ptrdiff_t operand,
               sycl::memory_order order = default_read_modify_write_order,
               sycl::memory_scope scope = default_scope) const;

Atomically adds ``operand`` to the value of the object
referenced by this ``sycl::atomic_ref`` and assigns the
result to the value of the referenced object. Returns
the original value of the referenced object. This function
is only supported for 64-bit pointers on devices that
have ``sycl::aspect::atomic64``.

``operator+=``
--------------

::

  T* operator+=(ptrdiff_t operand) const;

Equivalent to ``fetch_add(operand) + operand``.

``operator++``
--------------

::

  T* operator++(int) const;

Equivalent to ``fetch_add(1)``.

::

  T* operator++() const;

Equivalent to ``fetch_add(1) + 1``.


``fetch_sub``
-------------

::

  T* fetch_sub(ptrdiff_t operand,
               sycl::memory_order order = default_read_modify_write_order,
               sycl::memory_scope scope = default_scope) const;

Atomically subtracts ``operand`` from the value of the
object referenced by this ``sycl::atomic_ref`` and
assigns the result to the value of the referenced
object. Returns the original value of the referenced
object. This function is only supported for 64-bit
pointers on devices that have ``sycl::aspect::atomic64``.

``operator-=``
--------------

::

  T* operator-=(ptrdiff_t operand) const;

Equivalent to ``fetch_sub(operand) - operand``.

``operator--``
--------------

::

  T* operator--(int) const;

Equivalent to ``fetch_sub(1)``.

::

  T* operator--() const;

Equivalent to ``fetch_sub(1) - 1``.

========
Examples
========

.. literalinclude:: /examples/atomic.cpp
   :lines: 5-
   :linenos:
   :caption: Thread-safe push/pop using atomic operations.

.. literalinclude:: /examples/atomic.out
   :lines: 5-
   :caption: Output.
