..
  Copyright 2020 The Khronos Group Inc.
  SPDX-License-Identifier: CC-BY-4.0

===================
 Atomic Operations
===================

.. rst-class:: api-class

``sycl::atomic_ref``
====================

::

  template <typename T, memory_order DefaultOrder, memory_scope DefaultScope,
            access::address_space Space = access::address_space::generic_space
           >
  class atomic_ref;

.. seealso:: `atomic_ref in SYCL Specification <https://www.khronos.org/registry/SYCL/specs/sycl-2020/html/sycl-2020.html#sec:atomic-references>`__


(constructors)
--------------

::

  explicit atomic_ref(T&);
  atomic_ref(const atomic_ref&) noexcept;

``is_lock_free``
----------------

::

   bool is_lock_free() const noexcept;

``store``
---------

::

    void store(T operand,
      memory_order order = default_write_order,
      memory_scope scope = default_scope) const noexcept;

``load``
--------

::

    T load(memory_order order = default_read_order,
           memory_scope scope = default_scope) const noexcept;

``exchange``
------------

::

   exchange(T operand,
            memory_order order = default_read_modify_write_order,
            memory_scope scope = default_scope) const noexcept;

``compare_exchange``
--------------------

::

   bool compare_exchange_weak(T &expected, T desired,
                              memory_order success,
                              memory_order failure,
                              memory_scope scope = default_scope) const noexcept;
   bool compare_exchange_weak(T &expected, T desired,
                              memory_order order = default_read_modify_write_order,
                              memory_scope scope = default_scope) const noexcept;
   bool compare_exchange_strong(T &expected, T desired,
                                memory_order success,
                                memory_order failure,
                                memory_scope scope = default_scope) const noexcept;
   bool compare_exchange_strong(T &expected, T desired,
                                memory_order order = default_read_modify_write_order,
                                memory_scope scope = default_scope) const noexcept;

(operators)
-----------

::

   atomic_ref& operator=(const atomic_ref&) = delete;
   T operator=(T desired) const noexcept;


.. rst-class:: api-class

``sycl::atomic_ref`` (integral specialization)
==============================================

::

   template <memory_order DefaultOrder, memory_scope DefaultScope,
             access::address_space Space = access::address_space::generic_space
            >
   class atomic_ref<Integral, DefaultOrder, DefaultScope, Space>;

``fetch_OP``
-------------

::

   Integral fetch_add(Integral operand,
                      memory_order order = default_read_modify_write_order,
                      memory_scope scope = default_scope) const noexcept;
   Integral fetch_sub(Integral operand,
                      memory_order order = default_read_modify_write_order,
                      memory_scope scope = default_scope) const noexcept;
   Integral fetch_and(Integral operand,
                      memory_order order = default_read_modify_write_order,
                      memory_scope scope = default_scope) const noexcept;
   Integral fetch_or(Integral operand,
                     memory_order order = default_read_modify_write_order,
                     memory_scope scope = default_scope) const noexcept;
   Integral fetch_min(Integral operand,
                      memory_order order = default_read_modify_write_order,
                      memory_scope scope = default_scope) const noexcept;
   Integral fetch_max(Integral operand,
                      memory_order order = default_read_modify_write_order,
                      memory_scope scope = default_scope) const noexcept;

(operators)
-----------

::

     Integral operator++(int) const noexcept;
     Integral operator--(int) const noexcept;
     Integral operator++() const noexcept;
     Integral operator--() const noexcept;
     Integral operator+=(Integral) const noexcept;
     Integral operator-=(Integral) const noexcept;
     Integral operator&=(Integral) const noexcept;
     Integral operator|=(Integral) const noexcept;
     Integral operator^=(Integral) const noexcept;

.. rst-class:: api-class

``sycl::atomic_ref`` (floating-point specialization)
====================================================

::

   template <memory_order DefaultOrder, memory_scope DefaultScope,
             access::address_space Space = access::address_space::generic_space
            >
   class atomic_ref<Floating, DefaultOrder, DefaultScope, Space>;

``fetch_OP``
-------------

::

   Floating fetch_add(Floating operand,
                      memory_order order = default_read_modify_write_order,
                      memory_scope scope = default_scope) const noexcept;
   Floating fetch_sub(Floating operand,
                      memory_order order = default_read_modify_write_order,
                      memory_scope scope = default_scope) const noexcept;
   Floating fetch_min(Floating operand,
                      memory_order order = default_read_modify_write_order,
                      memory_scope scope = default_scope) const noexcept;
   Floating fetch_max(Floating operand,
                      memory_order order = default_read_modify_write_order,
                      memory_scope scope = default_scope) const noexcept;


(operators)
-----------

::

   Floating operator+=(Floating) const noexcept;
   Floating operator-=(Floating) const noexcept;

.. rst-class:: api-class

``sycl::atomic_ref`` (pointer specialization)
=============================================

::

   template <typename T,
             memory_order DefaultOrder, memory_scope DefaultScope,
             access::address_space Space = access::address_space::generic_space>
   class atomic_ref<T*, DefaultOrder, DefaultScope, Space>;


(constructors)
--------------

::

   explicit atomic_ref(T*&);
   atomic_ref(const atomic_ref&) noexcept;

``is_lock_free``
----------------

::

   bool is_lock_free() const noexcept;


``store``
---------

::

   void store(T* operand,
              memory_order order = default_write_order,
              memory_scope scope = default_scope) const noexcept;

``load``
--------

::

   T* load(memory_order order = default_read_order,
           memory_scope scope = default_scope) const noexcept;

``exchange``
------------

::

   T* exchange(T* operand,
               memory_order order = default_read_modify_write_order,
               memory_scope scope = default_scope) const noexcept;

``compare_exchange``
--------------------

::

   bool compare_exchange_weak(T* &expected, T* desired,
                              memory_order success,
                              memory_order failure,
                              memory_scope scope = default_scope) const noexcept;
   bool compare_exchange_weak(T* &expected, T* desired,
                              memory_order order = default_read_modify_write_order,
                              memory_scope scope = default_scope) const noexcept;
   bool compare_exchange_strong(T* &expected, T* desired,
                                memory_order success,
                                memory_order failure,
                                memory_scope scope = default_scope) const noexcept;
   bool compare_exchange_strong(T* &expected, T* desired,
                                memory_order order = default_read_modify_write_order,
                                memory_scope scope = default_scope) const noexcept;


``fetch_OP``
------------

::

   T* fetch_add(difference_type,
                memory_order order = default_read_modify_write_order,
                memory_scope scope = default_scope) const noexcept;
   T* fetch_sub(difference_type,
                memory_order order = default_read_modify_write_order,
                memory_scope scope = default_scope) const noexcept;

(operators)
-----------

::

   atomic_ref& operator=(const atomic_ref&) = delete;
   T* operator=(T* desired) const noexcept;
   operator T*() const noexcept;
   T* operator++(int) const noexcept;
   T* operator--(int) const noexcept;
   T* operator++() const noexcept;
   T* operator--() const noexcept;
   T* operator+=(difference_type) const noexcept;
   T* operator-=(difference_type) const noexcept;

``sycl::memory_order``
======================

::

   enum class memory_order : /* unspecified */ {
                             relaxed,
                             acquire,
                             release,
                             acq_rel,
                             seq_cst
   };

``sycl::memory_scope``
======================

::

   enum class memory_scope : /* unspecified */ {
                             work_item,
                             sub_group,
                             work_group,
                             device,
                             system
   };


Examples
========

.. literalinclude:: /examples/atomic.cpp
   :lines: 5-
   :linenos:
   :caption: Thread-safe push/pop using atomic operations
