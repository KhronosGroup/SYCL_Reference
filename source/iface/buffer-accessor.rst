****************
Buffer accessors
****************

.. rst-class:: api-class
	       
.. _buffer-accessor:

===============
Buffer accessor
===============

::
   
   template <typename dataT, int dimensions, access::mode accessmode,
             access::target accessTarget = access::target::global_buffer,
             access::placeholder isPlaceholder = access::placeholder::false_t>
   class accessor;

Description

.. rubric:: Template parameters

===============  =======
dataT            Type of buffer element
dimensions       Number of buffer dimensions
accessmode       See :ref:`access-mode`
accessTarget     See :ref:`access-target`
isPlaceholder    True if accessor is a placeholder
===============  =======

.. rubric:: Member types

===============  =======
value_type       Type of buffer element
reference        Type of reference to buffer element
const_reference  Type of const reference to buffer element
===============  =======

.. member-toc::

(constructors)
==============

.. parsed-literal::
   
  *Available only when:
   ((isPlaceholder == access::placeholder::false_t && accessTarget == access::target::host_buffer)
    || (isPlaceholder == access::placeholder::true_t
        && (accessTarget == access::target::global_buffer
	    || accessTarget == access::target::constant_buffer)))
   && dimensions == 0*

  template <typename AllocatorT>
  accessor(buffer<dataT, 1, AllocatorT> &bufferRef,
           const property_list &propList = {});
   
  *Available only when:
   (isPlaceholder == access::placeholder::false_t
    && (accessTarget == access::target::global_buffer
        || accessTarget == access::target::constant_buffer))
   && dimensions == 0*

  template <typename AllocatorT>
  accessor(buffer<dataT, 1, AllocatorT> &bufferRef,
           handler &commandGroupHandlerRef, const property_list &propList = {});

  *Available only when:
   ((isPlaceholder == access::placeholder::false_t
     && accessTarget == access::target::host_buffer)
    || (isPlaceholder == access::placeholder::true_t
        && (accessTarget == access::target::global_buffer
	    || accessTarget == access::target::constant_buffer)))
   && dimensions > 0*
   
  template <typename AllocatorT>
  accessor(buffer<dataT, dimensions, AllocatorT> &bufferRef,
           const property_list &propList = {});
  template <typename AllocatorT>
  accessor(buffer<dataT, dimensions, AllocatorT> &bufferRef,
           range<dimensions> accessRange, const property_list &propList = {});
  template <typename AllocatorT>
  accessor(buffer<dataT, dimensions, AllocatorT> &bufferRef,
           range<dimensions> accessRange, id<dimensions> accessOffset,
           const property_list &propList = {});

  *Available only when:
   (isPlaceholder == access::placeholder::false_t
    && (accessTarget == access::target::global_buffer
        || accessTarget == access::target::constant_buffer))
    && dimensions > 0*

  template <typename AllocatorT>
  accessor(buffer<dataT, dimensions, AllocatorT> &bufferRef,
           handler &commandGroupHandlerRef, const property_list &propList = {});
  template <typename AllocatorT>
  accessor(buffer<dataT, dimensions, AllocatorT> &bufferRef,
           handler &commandGroupHandlerRef, range<dimensions> accessRange,
           const property_list &propList = {});
  template <typename AllocatorT>
  accessor(buffer<dataT, dimensions, AllocatorT> &bufferRef,
           handler &commandGroupHandlerRef, range<dimensions> accessRange,
           id<dimensions> accessOffset, const property_list &propList = {});


Construct an accessor for a buffer.

Programs typically find it more convenient to use
:ref:`buffer-get_access` to create an accessor for a buffer.

.. rubric:: Template parameters

============  ===
AllocatorT    Type of allocator for buffer element
============  ===

.. rubric:: Parameters

======================  ===
bufferRef               Associate accessor with this buffer
commandGroupHandlerRef  Associate accessor with this handler
propList                `Buffer accessor properties`_
accessRange             Dimensions of data to be accessed            
accessOffset            Coordinates of origin of data
======================  ===


is_placeholder
==============

::
   
  constexpr bool is_placeholder() const;

Return True if this is a placeholder accessor.

get_size
========

::
   
  size_t get_size() const;

Returns size in bytes of the buffer region that this accesses.

get_count
=========

::
   
  size_t get_count() const;

Returns number elements that this accesses.

get_range
=========

.. parsed-literal::
   
  *Available only when:
   dimensions > 0*
   
  range<dimensions> get_range() const;


.. rubric:: Template parameters

===============  ===
dimensions       number of dimensions
===============  ===

Returns dimensions of the asssociated buffer or range that was
provided when the accessor was created.

get_offset
==========

.. parsed-literal::
   
  *Available only when:
   dimensions > 0*
   
  id<dimensions> get_offset() const;


.. rubric:: Template parameters

===============  ===
dimensions       number of dimensions
===============  ===


Returns coordinates of the origin of the buffer or offset that was
provided when the accessor was created.

operator ()
===========

.. parsed-literal::
   
  *Available only when:
   accessMode == access::mode::write
    || accessMode == access::mode::read_write
    || accessMode == access::mode::discard_write
    || accessMode == access::mode::discard_read_write*

  operator dataT &() const;

  *Available only when:
   accessMode == access::mode::read*
   
  operator dataT() const;

  *Available only when:
   accessMode == access::mode::atomic*

  operator atomic<dataT, access::address_space::global_space> () const;

Returns reference or value of element in the associated buffer. 

The variants of this operator are only available when *dimensions ==
0*, which means that a buffer contains a single element.

operator[]
==========

.. parsed-literal::

  *Reference variants*
  dataT &operator[](size_t index) const;
  dataT &operator[](id<dimensions> index) const;

  *Value variants*
  dataT operator[](size_t index) const;
  dataT operator[](id<dimensions> index) const;

  *Atomic variants*
  atomic<dataT, access::address_space::global_space> operator[](
    size_t index) const;
  atomic<dataT, access::address_space::global_space> operator[](
    id<dimensions> index) const;

  *Single dimension in multi-dimensional buffer*
  __unspecified__ &operator[](size_t index) const;

Returns reference or value of element in the associated buffer at the
requested index.

One dimensional buffers are indexed by a data of type
size_t. Multi-dimensional buffers may be indexed by a data of type
``id<dimensions>``, or by a sequence of *[]*, 1 per dimension. For
example ``a[1][2]``.  The operator returns a reference when the
accessor allows writes, which requires that accessMode be one of
``access::mode::write``, ``accessMode == access::mode::read_write``,
``accessMode == access::mode::discard_write``, or ``accessMode ==
access::mode::discard_read_write``. The operator returns an atomic if
the accessMode is ``access::mode::atomic``.


get_pointer
===========

.. parsed-literal::
   
  *Available only when:
   accessTarget == access::target::host_buffer*
   
  dataT \*get_pointer() const;
   
  *Available only when:
   accessTarget == access::target::global_buffer*

  global_ptr<dataT> get_pointer() const;

  *Available only when:
   accessTarget == access::target::constant_buffer*

  constant_ptr<dataT> get_pointer() const;

Returns pointer to memory in a host buffer.

==========================
Buffer accessor properties
==========================

SYCL does not define any properties for the buffer specialization of
an accessor.
