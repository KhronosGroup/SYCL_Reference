.. rst-class:: api-class
	       
==============
Local accessor
==============

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
   dimensions == 0*
   
  accessor(handler &commandGroupHandlerRef, const property_list &propList = {});

   
  *Available only when:
   dimensions > 0*
   
  accessor(range<dimensions> allocationSize, handler &commandGroupHandlerRef,
           const property_list &propList = {});



get_size
========

::
   
  size_t get_size() const;

.. rubric:: Returns

get_count
=========

::
   
  size_t get_count() const;

.. rubric:: Returns

get_range
=========

::
   
  range<dimensions> get_range() const;

.. rubric:: Template parameters

===============  =======
dimensions
===============  =======

.. rubric:: Returns

get_pointer
===========

::
   
  local_ptr<dataT> get_pointer() const;

Available only when: accessTarget == access::target::local

operator[]
==========

.. parsed-literal::
   
  *Available only when:
   accessMode == access::mode::read_write && dimensions > 0*
    
  dataT &operator[](id<dimensions> index) const;

  *Available only when:
   accessMode == access::mode::read_write && dimensions == 1*
   
  dataT &operator[](size_t index) const

  *Available only when:
   accessMode == access::mode::atomic && dimensions > 0*
   
  atomic<dataT, access::address_space::local_space> operator[](
    id<dimensions> index) const;

  *Available only when:
   accessMode == access::mode::atomic && dimensions == 1*
   
  atomic<dataT, access::address_space::local_space> operator[](
    size_t index) const;

  *Available only when:
   dimensions > 1*
   
  __unspecified__ &operator[](size_t index) const;
	 

operator ()
===========

.. parsed-literal::
   
  *Available only when:
   accessMode == access::mode::read_write && dimensions == 0*

  operator dataT &() const;
   
  *Available only when:
   accessMode == access::mode::atomic && dimensions == 0*
   
  operator atomic<dataT,access::address_space::local_space> () const;
  

  
