.. rst-class:: api-class
	       
===============
Image accessor
===============

::
   
   template <typename dataT, int dimensions, access::mode accessmode,
             access::target accessTarget = access::target::global_buffer,
             access::placeholder isPlaceholder = access::placeholder::false_t>
   class accessor;

Description

.. rubric:: Template parameters

================  ===
dataT
dimensions
accessmode
accessTarget
isPlaceholder
================  ===

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
   accessTarget == access::target::host_image*

  template <typename AllocatorT>
  accessor(image<dimensions, AllocatorT> &imageRef,
           const property_list &propList = {});

  *Available only when:
   accessTarget == access::target::image*

  template <typename AllocatorT>
  accessor(image<dimensions, AllocatorT> &imageRef,
           handler &commandGroupHandlerRef, const property_list &propList = {});

  *Available only when:
   accessTarget == access::target::image_array && dimensions < 3*
   
  template <typename AllocatorT>
  accessor(image<dimensions + 1, AllocatorT> &imageRef,
           handler &commandGroupHandlerRef, const property_list &propList = {});


get_count
=========

::
   
  size_t get_count() const;

get_range
=========

.. parsed-literal::
   
   *Available only when:
    (accessTarget != access::target::image_array)*
    
   range<dimensions> get_range() const;

   *Available only when:
    (accessTarget == access::target::image_array)*
    
   range<dimensions+1> get_range() const;

.. rubric:: Template parameters

================  ===
dimensions
================  ===

read
====

.. parsed-literal::
   
  *Available only when:
   (accessTarget == access::target::image && accessMode == access::mode::read)
   || (accessTarget ==
        access::target::host_image && (accessMode ==
        access::mode::read || accessMode == access::mode::read_write))*

  template <typename coordT>
  dataT read(const coordT &coords) const;

  *Available only when:
   (accessTarget == access::target::image && accessMode == access::mode::read)
   || (accessTarget ==
        access::target::host_image && (accessMode ==
        access::mode::read || accessMode == access::mode::read_write))*

  template <typename coordT>
  dataT read(const coordT &coords, const sampler &smpl) const;


.. rubric:: Template parameters

================  ===
coordT
================  ===


operator[]
==========

::
   
  *Available only when:
   accessTarget == access::target::image_array && dimensions < 3*
   
  __image_array_slice__ operator[](size_t index) const;

  
