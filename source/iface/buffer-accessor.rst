.. rst-class:: api-class
	       
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
dataT
dimensions
accessmode
accessTarget
isPlaceholder
===============  =======

.. rubric:: Member types

===============  =======
value_type
reference
const_reference
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


is_placeholder
==============

::
   
  constexpr bool is_placeholder() const;

get_size
========

::
   
  size_t get_size() const;

get_count
=========

::
   
  size_t get_count() const;

get_range
=========

.. parsed-literal::
   
  *Available only when:
   dimensions > 0*
   
  range<dimensions> get_range() const;


.. rubric:: Template parameters

===============  ===
dimensions
===============  ===

get_offset
==========

.. parsed-literal::
   
  *Available only when:
   dimensions > 0*
   
  id<dimensions> get_offset() const;


.. rubric:: Template parameters

===============  ===
dimensions
===============  ===

operator ()
===========

.. parsed-literal::
   
  *Available only when:
   (accessMode == access::mode::write
    || accessMode == access::mode::read_write
    || accessMode == access::mode::discard_write
    || accessMode == access::mode::discard_read_write)
   && dimensions == 0)*

  operator dataT &() const;

  *Available only when:
   accessMode == access::mode::read && dimensions == 0*
   
  operator dataT() const;

  *Available only when:
   accessMode == access::mode::atomic && dimensions == 0*

  operator atomic<dataT, access::address_space::global_space> () const;


operator[]
==========

.. parsed-literal::

  *Available only when:
   (accessMode == access::mode::write
    || accessMode == access::mode::read_write
    || accessMode == access::mode::discard_write
    ||accessMode == access::mode::discard_read_write)
   && dimensions > 0)*

  dataT &operator[](id<dimensions> index) const;

  *Available only when:
   (accessMode == access::mode::write
    || accessMode == access::mode::read_write
    || accessMode == access::mode::discard_write
    ||accessMode == access::mode::discard_read_write)
   && dimensions == 1)*

  dataT &operator[](size_t index) const;

  *Available only when:
   accessMode == access::mode::read && dimensions > 0*

  dataT operator[](id<dimensions> index) const;

  *Available only when:
   accessMode == access::mode::read && dimensions == 1*

  dataT operator[](size_t index) const;

  *Available only when:
   accessMode == access::mode::atomic && dimensions >  0*

  atomic<dataT, access::address_space::global_space> operator[](
    id<dimensions> index) const;

  *Available only when:
   accessMode == access::mode::atomic && dimensions == 1*
   
  atomic<dataT, access::address_space::global_space> operator[](
    size_t index) const;

  *Available only when:
   dimensions > 1*
  __unspecified__ &operator[](size_t index) const;


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



