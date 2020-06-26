.. _iface-buffers:

*********
 Buffers
*********


.. rst-class:: api-class
	       
======
buffer
======

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

.. member-toc::


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

.. rst-class:: api-class
	       
use_host_ptr
============

::

   class use_host_ptr;

.. rubric:: Namespace

::

   property::buffer
   
Description

.. member-toc::

.. _use_host_ptr-constructors:

(constructors)
--------------

::

   use_host_ptr();


.. rst-class:: api-class
	       
use_mutex
=========

::

   class use_mutex;

.. rubric:: Namespace

::

   property::buffer
   
.. member-toc::

.. _use_mutex-constructors:

(constructors)
--------------

::

   use_mutex();


get_mutex_ptr
-------------

::

   mutex_class *get_mutex_ptr() const;


context_bound
=============


::

   context_bound;


.. rubric:: Namespace

::

   property::buffer
   
.. member-toc::

.. _context_bound-constructors:

(constructors)
--------------


::

   use_mutex();


get_context
-----------

::

   context get_context() const;

	    
