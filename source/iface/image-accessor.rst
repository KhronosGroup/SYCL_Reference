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

| ``dataT`` -
| ``dimensions`` -
| ``accessmode`` -
| ``accessTarget`` -
| ``isPlaceholder`` -

.. rubric:: Member types

===============  =======
value_type
reference
const_reference
===============  =======

.. rubric:: Member functions

=================  =======
`(constructors)`_
get_count_
get_range_
read_
=================  =======

.. rubric:: Nonmember functions

=================  =======
`operator[]`_
=================  =======

(constructors)
==============

.. parsed-literal::
   
  template <typename AllocatorT>                            [#host_image]_
  accessor(image<dimensions, AllocatorT> &imageRef,
           const property_list &propList = {});

.. parsed-literal::
  
  template <typename AllocatorT>                            [#image]_
  accessor(image<dimensions, AllocatorT> &imageRef,
           handler &commandGroupHandlerRef, const property_list &propList = {});

.. parsed-literal::
   
  template <typename AllocatorT>                            [#image_arraydlt3]_
  accessor(image<dimensions + 1, AllocatorT> &imageRef,
           handler &commandGroupHandlerRef, const property_list &propList = {});

.. [#host_image] Available only when: accessTarget == access::target::host_image
.. [#image] Available only when: accessTarget == access::target::image
.. [#image_arraydlt3] Available only when: accessTarget ==
                      access::target::image_array && dimensions < 3

get_count
=========

::
   
  size_t get_count() const;

get_range
=========

.. parsed-literal::
   
  range<dimensions> get_range() const;                      [#not_image_array]_

.. parsed-literal::
   
  range<dimensions+1> get_range() const;                    [#image_array]_

.. [#not_image_array] Available only when: (accessTarget != access::target::image_array)
.. [#image_array] Available only when: (accessTarget == access::target::image_array)

.. rubric:: Template parameters

| ``dimensions`` -

.. rubric:: Returns

read
====

.. parsed-literal::
   
  template <typename coordT>                                [#a]_
  dataT read(const coordT &coords) const;

  template <typename coordT>                                [#b]_
  dataT read(const coordT &coords, const sampler &smpl) const;

.. [#a] Available only when: (accessTarget == access::target::image &&
        accessMode == access::mode::read) || (accessTarget ==
        access::target::host_image && (accessMode ==
        access::mode::read || accessMode == access::mode::read_write))
.. [#b] Available only when: (accessTarget == access::target::image &&
        accessMode == access::mode::read) || (accessTarget ==
        access::target::host_image && (accessMode ==
        access::mode::read || accessMode == access::mode::read_write))

.. rubric:: Template parameters

| `coordT` -

.. rubric:: Returns

operator[]
==========

::
   
  __image_array_slice__ operator[](size_t index) const;

Available only when: accessTarget == access::target::image_array && dimensions < 3 
  
