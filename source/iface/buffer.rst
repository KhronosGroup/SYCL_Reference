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
T                 Type of data in buffer
dimensions        Dimensionality of data: 1, 2, or 3
AllocatorT        Allocator for buffer data
================  ==========

Buffers are containers for data that can be read/written by both
kernel and host.  Data in a buffer cannot be directly via
pointers. Instead, a program creates an :ref:`buffer-accessor` that
references the buffer. The accessor provides array-like interfaces to
read/write actual data.  Accessors indicate when they read or write
data. When a program creates an accessor for a buffer, the SYCL
runtime copies the data to where it is needed, either the host or the
device. If the accessor is part of a device command group, then the
runtime delays execution of the kernel until the data movement is
complete. If the host creates an accessor, it will pause until the
data is available on the host. As a result data and kernels can
execute asynchronously and in parallel, only requiring the program to
specify the data dependencies.

Initialization

  Buffers can be automatically initialized via host data, iterator, or
  as a slice of another buffer. The constructor determines the
  initialization method.

Write back

  The destructor for a buffer can optionally write the data back to
  host memory, either by pointer or iterator. set_final_data_ and
  set_write_back_ control the write back of data.

Memory allocation

  The SYCL runtimes uses the default allocator for buffer memory
  allocation, unless the constructor provides an allocator.


.. rubric:: Member types
	    
================  ==========
value_type        type of buffer element
reference         reference type of buffer element
const_reference   const reference type of buffer element
allocator_type    type of allocator for buffer data
================  ==========

.. member-toc::


.. _buffer-constructors:

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

Construct a buffer.

Buffers can be initialized by a host data pointer. While the buffer
exists, it *owns* the host data and direct access of the host data
pointer during that time is undefined. The SYCL runtime performs a
write back of the buffer data back to the host data pointer when the
buffer is destroyed.  Buffers can also be initialized as a slice of
another buffer, by specifying the origin of the data and the
dimensions.

A constructor can also accept cl_mem or iterators to initialize a
buffer.

.. rubric:: Template parameters

================  ==========
InputIterator     type of iterator used to initialize the buffer
================  ==========

.. rubric:: Parameters

================  ==========
bufferRange       :ref:`range` specifies the dimensions of the buffer
allocator         Allocator for buffer data
propList          See `Buffer properties`_
hostData          Pointer to host memory to hold data
first             Iterator to initialize buffer
last              Iterator to initialize buffer
b                 Buffer used to initialize this buffer
baseIndx          Origin of sub-buffer
subRange          Dimensions of sub-buffer
================  ==========


get_range
=========

::
   
  range<dimensions> get_range() const;


Returns the dimensions of the buffer.

get_count
=========

::

  size_t get_count() const;

Returns the total number of elements in the buffer.  


get_size
========

::

  size_t get_size() const;


Returns the size of the buffer storage in bytes.


get_allocator
=============

::

  AllocatorT get_allocator() const;


Returns the allocator provided to the buffer.

.. _buffer-get_access:

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

Returns a accessor to the buffer.

.. rubric:: Template parameters

================  ==========
mode              See :ref:`access-mode`
target            See :ref:`access-target`
================  ==========

.. rubric:: Parameters

===================  ==========
commandGroupHandler  Command group that uses the accessor
accessRange          Dimensions of the sub-buffer that is accessed
accessOffset         Origin of the sub-buffer that is accessed
===================  ==========

	    
set_final_data
==============

::

  template <typename Destination = std::nullptr_t>
  void set_final_data(Destination finalData = nullptr);

.. rubric:: Template parameters

===================  ==========
Destination          std::weak_ptr<T> or output iterator
===================  ==========

.. rubric:: Parameters

===================  ==========
finalData            Indicates where data is copied at destruction time
===================  ==========

Set the final data location. Final data controls the location for
write back when the buffer is destroyed.


set_write_back
==============

::

  void set_write_back(bool flag = true);

.. rubric:: Parameters

===================  ==========
flag                 True to force write back
===================  ==========

Set the write back.

is_sub_buffer
=============

::

  bool is_sub_buffer() const;

Returns True if this is a sub-buffer.  

	    
reinterpret
===========

::

  template <typename ReinterpretT, int ReinterpretDim>
  buffer<ReinterpretT, ReinterpretDim, AllocatorT>
  reinterpret(range<ReinterpretDim> reinterpretRange) const;

.. rubric:: Template parameters

===================  ==========
ReinterpretT         Type of new buffer element
ReinterpretDim       Dimensions of new buffer
===================  ==========

.. rubric:: Parameters

===================  ==========
ReinterpretRange     Dimensionality of new buffer
===================  ==========

Creates a new buffer with the requested element type and
dimensionality, containing the data of the passed buffer or
sub-buffer.

.. rubric:: Exceptions

errc::invalid_object_error
  Size in bytes of new buffer does not match original buffer.

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
   
Use the provided host pointer and do not allocate new data on the
host.

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
   
Adds the requirement that the memory owned by the SYCL buffer can be
shared with the application via a std::mutex provided to the property.

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
   
The buffer can only be associated with a single SYCL context provided
to the property.

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

	    
