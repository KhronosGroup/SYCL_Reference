..
  Copyright 2024 The Khronos Group Inc.
  SPDX-License-Identifier: CC-BY-4.0

*************************
Atomic types (deprecated)
*************************

====================
``cl::sycl::atomic``
====================

::

  /* Deprecated in SYCL 2020 */
  template <typename T, access::address_space AddressSpace =
                            access::address_space::global_space>
  class atomic;

The atomic types and operations on atomic types provided by SYCL 1.2.1
are deprecated in SYCL 2020, and will be removed in a future version
of SYCL. The types and operations are made available in the
``cl::sycl:: namespace`` for backwards compatibility.

.. seealso:: |SYCL_SPEC_ATOMIC_TYPES|

(constructor)
=============

::

  template <typename pointerT>
  atomic(multi_ptr<pointerT, AddressSpace> ptr)

Deprecated in SYCL 2020.

Permitted data types for ``pointerT`` are any valid scalar data type
which is the same size in bytes as ``T``. Constructs an instance of
SYCL ``atomic`` which is associated with the pointer ``ptr``,
converted to a pointer of data type ``T``.

Member functions
================

``store``
---------

::

  void store(T operand, memory_order memoryOrder = memory_order::relaxed);

Deprecated in SYCL 2020.

Atomically stores the value ``operand`` at the address of the
``multi_ptr`` associated with this SYCL ``atomic``. The memory
order of this atomic operation must be ``memory_order::relaxed``.
This function is only supported for 64-bit data types on devices
that have ``aspect::atomic64``.

``load``
--------

::

  T load(memory_order memoryOrder = memory_order::relaxed) const

Deprecated in SYCL 2020.

Atomically loads the value at the address of the ``multi_ptr``
associated with this SYCL ``atomic``. Returns the value at the
address of the ``multi_ptr`` associated with this SYCL ``atomic``
before the call. The memory order of this atomic operation must be
``memory_order::relaxed``. This function is only supported for 64-bit
data types on devices that have ``aspect::atomic64``.

``exchange``
------------

::

  T exchange(T operand, memory_order memoryOrder = memory_order::relaxed);

Deprecated in SYCL 2020.

Atomically replaces the value at the address of the ``multi_ptr``
associated with this SYCL ``atomic`` with value ``operand`` and
returns the value at the address of the ``multi_ptr`` associated
with this SYCL ``atomic`` before the call. The memory order of this
atomic operation must be ``memory_order::relaxed``. This function is
only supported for 64-bit data types on devices that have
``aspect::atomic64``.

``compare_exchange_strong``
---------------------------

::

  bool compare_exchange_strong(
    T& expected, T desired,
    memory_order successMemoryOrder = memory_order::relaxed,
    memory_order failMemoryOrder = memory_order::relaxed);

Deprecated in SYCL 2020.

Available only when: ``T != float``.

Atomically compares the value at the address of the ``multi_ptr``
associated with this SYCL ``atomic`` against the value of
``expected``. If the values are equal, replaces value at address of
the ``multi_ptr`` associated with this SYCL ``atomic`` with the value
of ``desired``; otherwise assigns the original value at the address
of the ``multi_ptr`` associated with this SYCL ``atomic`` to
``expected``. Returns ``true`` if the comparison operation was
successful. The memory order of this atomic operation must be
``memory_order::relaxed`` for both success and fail. This function
is only supported for 64-bit data types on devices that have
``aspect::atomic64``.

``fetch_add``
-------------

::

  T fetch_add(T operand, memory_order memoryOrder = memory_order::relaxed);

Deprecated in SYCL 2020.

Available only when: ``T != float``.

Atomically adds the value ``operand`` to the value at the address of the
``multi_ptr`` associated with this SYCL ``atomic`` and assigns the result
to the value at the address of the ``multi_ptr`` associated with this SYCL
``atomic``. Returns the value at the address of the ``multi_ptr``
associated with this SYCL ``atomic`` before the call. The memory order
of this atomic operation must be ``memory_order::relaxed``. This function
is only supported for 64-bit data types on devices that have
``aspect::atomic64``.

``fetch_sub``
-------------

::

  T fetch_sub(T operand, memory_order memoryOrder = memory_order::relaxed);

Deprecated in SYCL 2020.

Available only when: ``T != float``.

Atomically subtracts the value ``operand`` to the value at the address
of the ``multi_ptr`` associated with this SYCL ``atomic`` and assigns
the result to the value at the address of the ``multi_ptr`` associated
with this SYCL ``atomic``. Returns the value at the address of the
``multi_ptr`` associated with this SYCL ``atomic`` before the call.
The memory order of this atomic operation must be
``memory_order::relaxed``. This function is only supported for 64-bit
data types on devices that have ``aspect::atomic64``.

``fetch_and``
-------------

::

  T fetch_and(T operand, memory_order memoryOrder = memory_order::relaxed);

Deprecated in SYCL 2020.

Available only when: ``T != float``.

Atomically performs a bitwise AND between the value ``operand`` and
the value at the address of the ``multi_ptr`` associated with this
SYCL ``atomic`` and assigns the result to the value at the address
of the ``multi_ptr`` associated with this SYCL atomic. Returns the value
at the address of the ``multi_ptr`` associated with this SYCL
``atomic`` before the call. The memory order of this atomic
operation must be ``memory_order::relaxed``. This function is
only supported for 64-bit data types on devices that have
``aspect::atomic64``.

``fetch_or``
-------------

::

  T fetch_or(T operand, memory_order memoryOrder = memory_order::relaxed);

Deprecated in SYCL 2020.

Available only when: ``T != float``.

Atomically performs a bitwise OR between the value ``operand``
and the value at the address of the ``multi_ptr`` associated with
this SYCL ``atomic`` and assigns the result to the value at the
address of the ``multi_ptr`` associated with this SYCL ``atomic``.
Returns the value at the address of the ``multi_ptr`` associated with
this SYCL atomic before the call. The memory order of this atomic
operation must be ``memory_order::relaxed``. This function is only
supported for 64-bit data types on devices that have
``aspect::atomic64``.

``fetch_xor``
-------------

::

  T fetch_xor(T operand, memory_order memoryOrder = memory_order::relaxed);

Deprecated in SYCL 2020.

Available only when: ``T != float``.

Atomically performs a bitwise XOR between the value ``operand`` and the
value at the address of the ``multi_ptr`` associated with this SYCL
``atomic`` and assigns the result to the value at the address of the
``multi_ptr`` associated with this SYCL ``atomic``. Returns the value
at the address of the ``multi_ptr`` associated with this SYCL
``atomic`` before the call. The memory order of this atomic operation
must be ``memory_order::relaxed``. This function is only supported
for 64-bit data types on devices that have ``aspect::atomic64``.

``fetch_min``
-------------

::

  T fetch_min(T operand, memory_order memoryOrder = memory_order::relaxed);

Deprecated in SYCL 2020.

Available only when: ``T != float``.

Atomically computes the minimum of the value ``operand`` and the value
at the address of the ``multi_ptr`` associated with this SYCL
``atomic`` and assigns the result to the value at the address
of the ``multi_ptr`` associated with this SYCL ``atomic``.
Returns the value at the address of the ``multi_ptr`` associated
with this SYCL ``atomic`` before the call. The memory order of
this atomic operation must be ``memory_order::relaxed``. This
function is only supported for 64-bit data types on devices that
have ``aspect::atomic64``.

``fetch_max``
-------------

::

  T fetch_max(T operand, memory_order memoryOrder = memory_order::relaxed);

Deprecated in SYCL 2020.

Available only when: ``T != float``.

Atomically computes the maximum of the value ``operand`` and the
value at the address of the ``multi_ptr`` associated with this
SYCL ``atomic`` and assigns the result to the value at the
address of the ``multi_ptr`` associated with this SYCL ``atomic``.
Returns the value at the address of the ``multi_ptr`` associated
with this SYCL ``atomic`` before the call. The memory order of
this atomic operation must be ``memory_order::relaxed``. This
function is only supported for 64-bit data types on devices
that have ``aspect::atomic64``.


Global functions
================

``atomic_load``
---------------

::

  template <typename T, access::address_space AddressSpace>
  T atomic_load(atomic<T, AddressSpace> object,
                memory_order memoryOrder = memory_order::relaxed);

Deprecated in SYCL 2020.

Equivalent to calling ``object.load(memoryOrder)``.

``atomic_store``
----------------

::

  template <typename T, access::address_space AddressSpace>
  void atomic_store(atomic<T, AddressSpace> object, T operand,
                    memory_order memoryOrder = memory_order::relaxed);

Deprecated in SYCL 2020.

Equivalent to calling ``object.store(operand, memoryOrder)``.

``atomic_exchange``
-------------------

::

  template <typename T, access::address_space AddressSpace>
  T atomic_exchange(atomic<T, AddressSpace> object, T operand,
                    memory_order memoryOrder = memory_order::relaxed);

Deprecated in SYCL 2020.

Equivalent to calling ``object.exchange(operand, memoryOrder)``.

``atomic_compare_exchange_strong``
----------------------------------

::

  template <typename T, access::address_space AddressSpace>
  bool atomic_compare_exchange_strong(
      atomic<T, AddressSpace> object, T& expected, T desired,
      memory_order successMemoryOrder = memory_order::relaxed memory_order
          failMemoryOrder = memory_order::relaxed);

Deprecated in SYCL 2020.

Equivalent to calling
``object.compare_exchange_strong(expected, desired,
successMemoryOrder, failMemoryOrders)``.

``atomic_fetch_add``
--------------------

::

  template <typename T, access::address_space AddressSpace>
  T atomic_fetch_add(atomic<T, AddressSpace> object, T operand,
                     memory_order memoryOrder = memory_order::relaxed);

Deprecated in SYCL 2020.

Equivalent to calling ``object.fetch_add(operand, memoryOrder)``.

``atomic_fetch_sub``
--------------------

::

  template <typename T, access::address_space AddressSpace>
  T atomic_fetch_sub(atomic<T, AddressSpace> object, T operand,
                     memory_order memoryOrder = memory_order::relaxed);

Deprecated in SYCL 2020.

Equivalent to calling ``object.fetch_sub(operand, memoryOrder)``.

``atomic_fetch_and``
--------------------

::

  template <typename T, access::address_space AddressSpace>
  T atomic_fetch_and(atomic<T> operand, T object,
                     memory_order memoryOrder = memory_order::relaxed);

Deprecated in SYCL 2020.

Equivalent to calling ``object.fetch_add(operand, memoryOrder)``.

``atomic_fetch_or``
-------------------

::

  template <typename T, access::address_space AddressSpace>
  T atomic_fetch_or(atomic<T, AddressSpace> object, T operand,
                    memory_order memoryOrder = memory_order::relaxed);

Deprecated in SYCL 2020.

Equivalent to calling ``object.fetch_or(operand, memoryOrder)``.

``atomic_fetch_xor``
--------------------

::

  template <typename T, access::address_space AddressSpace>
  T atomic_fetch_xor(atomic<T, AddressSpace> object, T operand,
                     memory_order memoryOrder = memory_order::relaxed);

Deprecated in SYCL 2020.

Equivalent to calling ``object.fetch_xor(operand, memoryOrder)``.

``atomic_fetch_min``
--------------------

::

  template <typename T, access::address_space AddressSpace>
  T atomic_fetch_min(atomic<T, AddressSpace> object, T operand,
                     memory_order memoryOrder = memory_order::relaxed);

Deprecated in SYCL 2020.

Equivalent to calling ``object.fetch_min(operand, memoryOrder)``.

``atomic_fetch_max``
--------------------

::

  template <typename T, access::address_space AddressSpace>
  T atomic_fetch_max(atomic<T, AddressSpace> object, T operand,
                     memory_order memoryOrder = memory_order::relaxed);

Deprecated in SYCL 2020.

Equivalent to calling ``object.fetch_max(operand, memoryOrder)``.
