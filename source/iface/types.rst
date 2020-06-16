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

::

   bool compare_exchange_strong(T &expected, T desired,
                                memory_order successMemoryOrder = memory_order::relaxed,
                                memory_order failMemoryOrder = memory_order::relaxed);

Available only when: T != float

fetch_add
=========

::

   T fetch_add(T operand, memory_order memoryOrder = memory_order::relaxed);

Available only when: T != float

fetch_sub
=========

::

   T fetch_sub(T operand, memory_order memoryOrder = memory_order::relaxed);

Available only when: T != float

fetch_and
=========

::
   
   T fetch_and(T operand, memory_order memoryOrder = memory_order::relaxed);
   
Available only when: T != float

fetch_or
========

::
   
   T fetch_or(T operand, memory_order memoryOrder = memory_order::relaxed);

Available only when: T != float

fetch_xor
=========

::
   
   T fetch_xor(T operand, memory_order memoryOrder = memory_order::relaxed);

Available only when: T != float

fetch_min
=========

::
   
   T fetch_min(T operand, memory_order memoryOrder = memory_order::relaxed);
   
Available only when: T != float

fetch_max
=========

::

   T fetch_max(T operand, memory_order memoryOrder = memory_order::relaxed);

Available only when: T != float








