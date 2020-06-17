.. _iface-buffers:

*********
 Buffers
*********

==================
 Buffer class
==================

::
   
   template <typename T, int dimensions = 1,
             typename AllocatorT = cl::sycl::buffer_allocator>
   class buffer;

.. rubric:: Template parameters

================  ==========
T
dimensions
AllocatorT
================  ==========

.. rubric:: Member types
	    
================  ==========
value_type      
reference       
const_reference 
allocator_type 
================  ==========

.. rubric:: Member functions
	    
====================  ==========
:ref:`buffer-buffer`
get_range_
get_count_
get_size_
get_allocator_
get_access_
set_final_data_
set_write_back_
is_sub_buffer_
reinterpret_
====================  ==========


.. _buffer-buffer:

(constructors)
==============

.. parsed-literal::
   
  buffer(const range<dimensions> &bufferRange,
         const property_list &propList = {});
  buffer(const range<dimensions> &bufferRange, AllocatorT allocator,
         const property_list &propList = {});
  buffer(T *hostData, const range<dimensions> &bufferRange,
         const property_list &propList = {});
  buffer(T *hostData, const range<dimensions> &bufferRange,
         AllocatorT allocator, const property_list &propList = {});
  buffer(const T *hostData, const range<dimensions> &bufferRange,
         const property_list &propList = {});
  buffer(const T *hostData, const range<dimensions> &bufferRange,
         AllocatorT allocator, const property_list &propList = {});
  buffer(const shared_ptr_class<T> &hostData,
         const range<dimensions> &bufferRange, AllocatorT allocator,
         const property_list &propList = {});
  buffer(const shared_ptr_class<T> &hostData,
         const range<dimensions> &bufferRange,
         const property_list &propList = {});
  buffer(buffer<T, dimensions, AllocatorT> b, const id<dimensions> &baseIndex,
         const range<dimensions> &subRange);

  *Available only when:
   dimensions == 1*
   
  template <class InputIterator>
  buffer<T, 1>(InputIterator first, InputIterator last, AllocatorT allocator,
               const property_list &propList = {});
  template <class InputIterator>
  buffer<T, 1>(InputIterator first, InputIterator last,
               const property_list &propList = {});
  buffer(cl_mem clMemObject, const context &syclContext,
         event availableEvent = {});

.. rubric:: Template parameters

================  ==========
InputIterator
================  ==========

.. rubric:: Parameters

================  ==========
bufferRange
allocator
propList          See `Buffer properties`_
hostData
first
last
b
baseIndx
subRange
================  ==========


get_range
=========

::
   
  range<dimensions> get_range() const;


get_count
=========

::

  size_t get_count() const;


get_size
========

::

  size_t get_size() const;


get_allocator
=============

::

  AllocatorT get_allocator() const;


get_access
==========

::

  template <access::mode mode, access::target target = access::target::global_buffer>
  accessor<T, dimensions, mode, target> get_access(
      handler &commandGroupHandler);
  template <access::mode mode>
  accessor<T, dimensions, mode, access::target::host_buffer> get_access();
  template <access::mode mode, access::target target = access::target::global_buffer>
  accessor<T, dimensions, mode, target> get_access(
      handler &commandGroupHandler, range<dimensions> accessRange,
      id<dimensions> accessOffset = {});
  template <access::mode mode>
  accessor<T, dimensions, mode, access::target::host_buffer> get_access(
    range<dimensions> accessRange, id<dimensions> accessOffset = {});

.. rubric:: Template parameters

================  ==========
mode
target
================  ==========

.. rubric:: Parameters

===================  ==========
commandGroupHandler
accessRange
accessOffset
===================  ==========

	    
set_final_data
==============

::

  template <typename Destination = std::nullptr_t>
  void set_final_data(Destination finalData = nullptr);

.. rubric:: Template parameters

===================  ==========
Destination
===================  ==========

.. rubric:: Parameters

===================  ==========
finalData
===================  ==========


set_write_back
==============

::

  void set_write_back(bool flag = true);

.. rubric:: Parameters

===================  ==========
flag
===================  ==========

is_sub_buffer
=============

::

  bool is_sub_buffer() const;

	    
reinterpret
===========

::

  template <typename ReinterpretT, int ReinterpretDim>
  buffer<ReinterpretT, ReinterpretDim, AllocatorT>
  reinterpret(range<ReinterpretDim> reinterpretRange) const;

.. rubric:: Template parameters

===================  ==========
ReinterpretT
ReinterpretDim
===================  ==========

.. rubric:: Parameters

===================  ==========
ReinterpretRange
===================  ==========

==================
 Buffer properties
==================

==================================  ======
`property::buffer::use_host_ptr`_
`property::buffer::use_mutex`_
`property::buffer::context_bound`_
==================================  ======

property::buffer::use_host_ptr
==============================

::

   class property::buffer::use_host_ptr;

Description

.. rubric:: Member functions

==========================  =======
:ref:`buffer-use_host_ptr`
==========================  =======

.. _buffer-use_host_ptr:

(constructors)
--------------

::

   use_host_ptr();


property::buffer::use_mutex
===========================

::

   class property::buffer::use_mutex;

.. rubric:: Member functions

===============  =======
(constructors)_
get_mutex_ptr_
===============  =======

   
(constructors)
--------------

::

   use_mutex();


get_mutex_ptr
-------------

::

   mutex_class *get_mutex_ptr() const;


property::buffer::context_bound
===============================


::

   property::buffer::context_bound;


.. rubric:: Member functions

===============  =======
(constructors)_
get_context_
===============  =======

(constructors)
--------------


::

   use_mutex();


get_context
-----------

::

   context get_context() const;

	    
