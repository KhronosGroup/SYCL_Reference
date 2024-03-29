..
  Copyright 2024 The Khronos Group Inc.
  SPDX-License-Identifier: CC-BY-4.0

.. _common-reference:

**************************
Common Reference Semantics
**************************

Each of the following SYCL runtime classes: 
:ref:`command-accessor`, :ref:`buffer`, :ref:`context`, :ref:`device`,
:ref:`device_image`, :ref:`event`, :ref:`host_accessor`, 
:ref:`host_sampled_image_accessor`, :ref:`host_unsampled_image_accessor`, 
:ref:`kernel`, :ref:`kernel_id`, :ref:`sycl::kernel_bundle <iface-kernel-bundle>`, 
:ref:`local_accessor`, :ref:`platform`, :ref:`queue`, :ref:`sampled_image`, 
:ref:`sampled_image_accessor`, :ref:`unsampled_image` and :ref:`unsampled_image_accessor`
must obey the following statements, where ``T`` is the runtime class type:

* ``T`` must be copy constructible and copy assignable in the host application 
  and within SYCL kernel functions in the case that ``T`` is a valid kernel argument. 
  Any instance of ``T`` that is constructed as a copy of another instance, 
  via either the copy constructor or copy assignment operator, must behave as-if it 
  were the original instance and as-if any action performed on it were also performed 
  on the original instance and must represent the same underlying native backend object 
  as the original instance where applicable.
* ``T`` must be destructible in the host application and within SYCL kernel functions 
  in the case that ``T`` is a valid kernel argument. When any instance of ``T`` is 
  destroyed, including as a result of the copy assignment operator, any behavior 
  specific to T that is specified as performed on destruction is only performed 
  if this instance is the last remaining host copy, in accordance with the above 
  definition of a copy.
* ``T`` must be move constructible and move assignable in the host application 
  and within SYCL kernel functions in the case that T is a valid kernel argument. 
  Any instance of T that is constructed as a move of another instance, via either 
  the move constructor or move assignment operator, must replace the original 
  instance rendering said instance invalid and must represent the same underlying 
  native backend object as the original instance where applicable.
* ``T`` must be equality comparable in the host application. Equality between two 
  instances of T (i.e. ``a == b``) must be true if one instance is a copy of the 
  other and non-equality between two instances of ``T`` (i.e. ``a != b``) must 
  be true if neither instance is a copy of the other, in accordance with the 
  above definition of a copy, unless either instance has become invalidated 
  by a move operation. By extension of the requirements above, equality on ``T`` 
  must guarantee to be reflexive (i.e. ``a == a``), symmetric (i.e. ``a == b`` 
  implies ``b == a`` and ``a != b`` implies ``b != a``) and 
  transitive (i.e. ``a == b && b == c`` implies ``c == a``).
* A specialization of ``std::hash`` for ``T`` must exist on the host application 
  that returns a unique value such that if two instances of T are equal, in 
  accordance with the above definition, then their resulting hash values are 
  also equal and subsequently if two hash values are not equal, then their 
  corresponding instances are also not equal, in accordance with the above definition.

Some SYCL runtime classes will have additional behavior associated with copy, 
movement, assignment or destruction semantics. If these are specified they are 
in addition to those specified above unless stated otherwise.

Each of the runtime classes mentioned above must provide a common interface 
of special member functions in order to fulfill the copy, move, destruction
requirements and hidden friend functions in order to fulfill the equality 
requirements.

::

  namespace sycl {

  class T {
    ...

    public: 

    T(const T& rhs);

    T(T&& rhs);

    T& operator=(const T& rhs);

    T& operator=(T&& rhs);

    ~T();

    ...

    friend bool operator==(const T& lhs, const T& rhs) { /* ... */ }

    friend bool operator!=(const T& lhs, const T& rhs) { /* ... */ }

    ...
  };

  } // namespace sycl

.. seealso:: |SYCL_SPEC_COMMON_REFERENCE|

.. _ref_special_member_func:

=======================================================
Common special member functions for reference semantics
=======================================================

.. list-table::
  :header-rows: 1

  * - Special member function
    - Description
  * - ``T(const T& rhs);``
    - Constructs a SYCL ``T`` instance as a copy of the RHS SYCL 
      ``T`` in accordance with the requirements set out above.
  * - ``T(T&& rhs);``
    - Constructs a SYCL ``T`` instance as a move of the RHS SYCL 
      ``T`` in accordance with the requirements set out above.
  * - ``T& operator=(const T& rhs);``
    - Assigns this SYCL ``T`` instance with a copy of the RHS 
      SYCL ``T`` in accordance with the requirements set out above.
  * - ``T& operator=(T&& rhs);``
    - Assigns this SYCL ``T`` instance with a move of the RHS SYCL 
      ``T`` in accordance with the requirements set out above.
  * - ``~T();``
    - Destroys this SYCL ``T`` instance in accordance with the 
      requirements set out above. 
      On destruction of the last copy, may perform additional 
      lifetime related operations required for the underlying 
      native backend object specified in the SYCL backend specification 
      document, if this SYCL T instance was originally constructed 
      using one of the backend interoperability ``sycl::make_*`` functions. 
      See the relevant backend specification for details.


.. _ref_hidden_friend_func:

======================================================
Common hidden friend functions for reference semantics
======================================================

A hidden friend function is a function first declared via a ``friend`` 
declaration with no additional out of class or namespace scope declarations. 

Hidden friend functions are only visible to ADL (Argument Dependent Lookup) 
and are hidden from qualified and unqualified lookup. 

Hidden friend functions have the benefits of avoiding accidental implicit 
conversions and faster compilation.

.. list-table::
  :header-rows: 1

  * - Hidden friend function
    - Description
  * - ::

        friend bool operator==(const T& lhs, const T& rhs);

    - Returns ``true`` if this LHS SYCL ``T`` is equal to the RHS 
      SYCL ``T`` in accordance with the requirements set out above, 
      otherwise returns ``false``.
  * - ::

        friend bool operator!=(const T& lhs, const T& rhs);

    - Returns ``true`` if this LHS SYCL ``T`` is not equal to the 
      RHS SYCL ``T`` in accordance with the requirements set out 
      above, otherwise returns ``false``.
