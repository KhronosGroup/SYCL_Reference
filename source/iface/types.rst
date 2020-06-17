*********************
Synchronization types
*********************


=====================
 access::fence_space
=====================

::

   enum class fence_space : char {
       local_space,
       global_space,
       global_and_local
   };


==============
 memory_order
==============

::

   enum class memory_order : int {
       relaxed
   };

.. rst-class:: api-class
	       
========
 atomic
========

::

   template <typename T,
             access::address_space addressSpace = access::address_space::global_space
	    >
   class atomic;

(constructors)
==============

::
   
   template <typename pointerT>
   atomic(multi_ptr<pointerT, addressSpace> ptr);

store
=====

::
   
   void store(T operand, memory_order memoryOrder = memory_order::relaxed);


load
====

::

     T load(memory_order memoryOrder = memory_order::relaxed) const;

exchange
========

::

   T exchange(T operand, memory_order memoryOrder = memory_order::relaxed);

compare_exchange_strong
=======================

.. parsed-literal::

   *Available only when:
    T != float*
    
   bool compare_exchange_strong(T &expected, T desired,
                                memory_order successMemoryOrder = memory_order::relaxed,
                                memory_order failMemoryOrder = memory_order::relaxed);


fetch_add
=========

.. parsed-literal::

   *Available only when:
    T != float*
    
   T fetch_add(T operand, memory_order memoryOrder = memory_order::relaxed);


fetch_sub
=========

.. parsed-literal::

   *Available only when:
    T != float*
    
   T fetch_sub(T operand, memory_order memoryOrder = memory_order::relaxed);


fetch_and
=========

.. parsed-literal::
   
   *Available only when:
    T != float*
    
   T fetch_and(T operand, memory_order memoryOrder = memory_order::relaxed);
   


fetch_or
========

.. parsed-literal::
   
   *Available only when:
    T != float*

   T fetch_or(T operand, memory_order memoryOrder = memory_order::relaxed);


fetch_xor
=========

.. parsed-literal::
   
   *Available only when:
    T != float*
    
   T fetch_xor(T operand, memory_order memoryOrder = memory_order::relaxed);


fetch_min
=========

.. parsed-literal::
   
   *Available only when:
    T != float*
    
   T fetch_min(T operand, memory_order memoryOrder = memory_order::relaxed);
   

fetch_max
=========

.. parsed-literal::

   *Available only when:
    T != float*
    
   T fetch_max(T operand, memory_order memoryOrder = memory_order::relaxed);









