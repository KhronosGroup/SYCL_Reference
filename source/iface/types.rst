..
  Copyright 2020 The Khronos Group Inc.
  SPDX-License-Identifier: CC-BY-4.0

*********************
Synchronization types
*********************


=========================
sycl::access::fence_space
=========================

::

   enum class fence_space : char {
       local_space,
       global_space,
       global_and_local
   };


==================
sycl::memory_order
==================

::

   enum class memory_order : int {
       relaxed
   };

.. rst-class:: api-class
	       
============
sycl::atomic
============

::

   template <typename T,
             sycl::access::address_space addressSpace = sycl::access::address_space::global_space
	    >
   class atomic;

(constructors)
==============

::
   
   template <typename pointerT>
   atomic(sycl::multi_ptr<pointerT, addressSpace> ptr);

store
=====

::
   
   void store(T operand, sycl::memory_order memoryOrder = sycl::memory_order::relaxed);


load
====

::

     T load(sycl::memory_order memoryOrder = sycl::memory_order::relaxed) const;

exchange
========

::

   T exchange(T operand, sycl::memory_order memoryOrder = sycl::memory_order::relaxed);

compare_exchange_strong
=======================

.. parsed-literal::

   *Available only when:
    T != float*
    
   bool compare_exchange_strong(T &expected, T desired,
                                sycl::memory_order successMemoryOrder = sycl::memory_order::relaxed,
                                sycl::memory_order failMemoryOrder = sycl::memory_order::relaxed);


fetch_add
=========

.. parsed-literal::

   *Available only when:
    T != float*
    
   T fetch_add(T operand, sycl::memory_order memoryOrder = sycl::memory_order::relaxed);


fetch_sub
=========

.. parsed-literal::

   *Available only when:
    T != float*
    
   T fetch_sub(T operand, sycl::memory_order memoryOrder = sycl::memory_order::relaxed);


fetch_and
=========

.. parsed-literal::
   
   *Available only when:
    T != float*
    
   T fetch_and(T operand, sycl::memory_order memoryOrder = sycl::memory_order::relaxed);
   


fetch_or
========

.. parsed-literal::
   
   *Available only when:
    T != float*

   T fetch_or(T operand, sycl::memory_order memoryOrder = sycl::memory_order::relaxed);


fetch_xor
=========

.. parsed-literal::
   
   *Available only when:
    T != float*
    
   T fetch_xor(T operand, sycl::memory_order memoryOrder = sycl::memory_order::relaxed);


fetch_min
=========

.. parsed-literal::
   
   *Available only when:
    T != float*
    
   T fetch_min(T operand, sycl::memory_order memoryOrder = sycl::memory_order::relaxed);
   

fetch_max
=========

.. parsed-literal::

   *Available only when:
    T != float*
    
   T fetch_max(T operand, sycl::memory_order memoryOrder = sycl::memory_order::relaxed);









