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
get_size_
get_count_
get_range_
get_pointer_
=================  =======

.. rubric:: Nonmember functions

=================  =======
`operator[]`_
`operator ()`_
=================  =======

(constructors)
==============

.. parsed-literal::
   
  accessor(handler &commandGroupHandlerRef,                                    [#dim0]_
           const property_list &propList = {});

.. parsed-literal::
   
  accessor(range<dimensions> allocationSize, handler &commandGroupHandlerRef,  [#dimgtr0]_
           const property_list &propList = {});

.. [#dim0] Available only when: dimensions == 0

.. [#dimgtr0] Available only when: dimensions > 0

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

| ``dimensions`` -

.. rubric:: Returns

get_pointer
===========

::
   
  local_ptr<dataT> get_pointer() const;

Available only when: accessTarget == access::target::local

operator[]
==========

  dataT &operator[](id<dimensions> index) const;            [#a1]_

  dataT &operator[](size_t index) const;                    [#a2]_

  atomic<dataT, access::address_space::local_space> operator[](
    id<dimensions> index) const;                            [#a3]_

  atomic<dataT, access::address_space::local_space> operator[](
    size_t index) const;                                    [#a4]_

  __unspecified__ &operator[](size_t index) const;          [#a5]_

.. [#a1] Available only when: accessMode == access::mode::read_write && dimensions > 0)

.. [#a2] Available only when: accessMode == access::mode::read_write && dimensions == 1)

.. [#a3] Available only when: accessMode == access::mode::atomic && dimensions > 0

.. [#a4] Available only when: accessMode == access::mode::atomic && dimensions == 1

.. [#a5] Available only when: dimensions > 1

	 

operator ()
===========

.. parsed-literal::
   
  operator dataT &() const;                                            [#b1]_

.. parsed-literal::
   
  operator atomic<dataT,access::address_space::local_space> () const;  [#b2]_
  
.. [#b1] Available only when: accessMode == access::mode::read_write && dimensions == 0)
.. [#b2] Available only when: accessMode == access::mode::atomic && dimensions == 0

  
