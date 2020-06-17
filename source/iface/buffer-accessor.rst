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

.. rubric:: Member functions

=================  =======
`(constructors)`_
is_placeholder_
get_size_
get_count_
get_range_
get_offset_
=================  =======

.. rubric:: Nonmember functions

=================  =======
`operator ()`_
`operator[]`_
get_pointer_
=================  =======

(constructors)
==============

.. parsed-literal::
   
  template <typename AllocatorT>                            [#host_dim0]_
  accessor(buffer<dataT, 1, AllocatorT> &bufferRef,
           const property_list &propList = {});

.. parsed-literal::
   
  template <typename AllocatorT>                            [#global_dim0]_
  accessor(buffer<dataT, 1, AllocatorT> &bufferRef,
           handler &commandGroupHandlerRef, const property_list &propList = {});

.. parsed-literal::
   
  template <typename AllocatorT>                            [#host_gtr0]_
  accessor(buffer<dataT, dimensions, AllocatorT> &bufferRef,
           const property_list &propList = {});

.. parsed-literal::
   
  template <typename AllocatorT>                            [#global_gtr0]_
  accessor(buffer<dataT, dimensions, AllocatorT> &bufferRef,
           handler &commandGroupHandlerRef, const property_list &propList = {});

.. parsed-literal::
   
  template <typename AllocatorT>                            [#host_gtr0]_
  accessor(buffer<dataT, dimensions, AllocatorT> &bufferRef,
           range<dimensions> accessRange, const property_list &propList = {});

.. parsed-literal::
   
  template <typename AllocatorT>                            [#host_gtr0]_
  accessor(buffer<dataT, dimensions, AllocatorT> &bufferRef,
           range<dimensions> accessRange, id<dimensions> accessOffset,
           const property_list &propList = {});

.. parsed-literal::
   
  template <typename AllocatorT>                            [#global_gtr0]_
  accessor(buffer<dataT, dimensions, AllocatorT> &bufferRef,
           handler &commandGroupHandlerRef, range<dimensions> accessRange,
           const property_list &propList = {});

.. parsed-literal::
   
  template <typename AllocatorT>                            [#global_gtr0]_
  accessor(buffer<dataT, dimensions, AllocatorT> &bufferRef,
           handler &commandGroupHandlerRef, range<dimensions> accessRange,
           id<dimensions> accessOffset, const property_list &propList = {});

.. [#host_dim0] Available only when: ((isPlaceholder == access::placeholder::false_t &&
		accessTarget == access::target::host_buffer) || (isPlaceholder ==
		access::placeholder::true_t && (accessTarget == access::target::global_buffer
		|| accessTarget == access::target::constant_buffer))) && dimensions == 0

.. [#global_dim0] Available only when: (isPlaceholder == access::placeholder::false_t &&
		  (accessTarget == access::target::global_buffer || accessTarget ==
		  access::target::constant_buffer)) && dimensions == 0
		
.. [#host_gtr0] Available only when: ((isPlaceholder == access::placeholder::false_t &&
		accessTarget == access::target::host_buffer) || (isPlaceholder ==
		access::placeholder::true_t && (accessTarget == access::target::global_buffer
		|| accessTarget == access::target::constant_buffer))) && dimensions > 0

.. [#global_gtr0] Available only when: (isPlaceholder == access::placeholder::false_t &&
		  (accessTarget == access::target::global_buffer || accessTarget ==
		  access::target::constant_buffer)) && dimensions > 0

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

::
   
  range<dimensions> get_range() const;

Available only when: dimensions > 0

.. rubric:: Template parameters

| ``dimensions`` -

.. rubric:: Returns

get_offset
==========

::
   
  id<dimensions> get_offset() const;

Available only when: dimensions > 0

.. rubric:: Template parameters

| ``dimensions`` -

.. rubric:: Returns


operator ()
===========

.. parsed-literal::
   
  operator dataT &() const;                                              [#a1]_

.. parsed-literal::
   
  operator dataT() const;                                                [#a2]_

.. parsed-literal::
   
  operator atomic<dataT, access::address_space::global_space> () const;  [#a3]_

.. [#a1] Available only when: (accessMode == access::mode::write || accessMode ==
	access::mode::read_write || accessMode == access::mode::discard_write ||
	accessMode == access::mode::discard_read_write) && dimensions == 0)

.. [#a2] Available only when: accessMode == access::mode::read && dimensions == 0

.. [#a3] Available only when: accessMode == access::mode::atomic && dimensions == 0


operator[]
==========

.. parsed-literal::

  dataT &operator[](id<dimensions> index) const;                         [#b1]_

.. parsed-literal::

  dataT &operator[](size_t index) const;                                 [#b2]_

.. parsed-literal::

  dataT operator[](id<dimensions> index) const;                          [#b3]_

.. parsed-literal::

  dataT operator[](size_t index) const;                                  [#b4]_

.. parsed-literal::

  atomic<dataT, access::address_space::global_space> operator[](         [#b5]_
    id<dimensions> index) const;

.. parsed-literal::

  atomic<dataT, access::address_space::global_space> operator[](         [#b6]_
    size_t index) const;
  __unspecified__ &operator[](size_t index) const;                       [#b7]_
  
.. [#b1] Available only when: (accessMode == access::mode::write || accessMode ==
	access::mode::read_write || accessMode == access::mode::discard_write ||
	accessMode == access::mode::discard_read_write) && dimensions > 0)

.. [#b2] Available only when: (accessMode == access::mode::write || accessMode ==
	access::mode::read_write || accessMode == access::mode::discard_write ||
	accessMode == access::mode::discard_read_write) && dimensions == 1)

.. [#b3] Available only when: accessMode == access::mode::read && dimensions > 0

.. [#b4] Available only when: accessMode == access::mode::read && dimensions == 1

.. [#b5] Available only when: accessMode == access::mode::atomic && dimensions >  0

.. [#b6] Available only when: accessMode == access::mode::atomic && dimensions == 1 

.. [#b7] Available only when: dimensions > 1 

get_pointer
===========

.. parsed-literal::
   
  dataT \*get_pointer() const;                [#c1]_

.. parsed-literal::
   
  global_ptr<dataT> get_pointer() const;      [#c2]_

.. parsed-literal::
   
  constant_ptr<dataT> get_pointer() const;    [#c3]_

.. [#c1] Available only when: accessTarget == access::target::host_buffer

.. [#c2] Available only when: accessTarget == access::target::global_buffer

.. [#c3] Available only when: accessTarget == access::target::constant_buffer
