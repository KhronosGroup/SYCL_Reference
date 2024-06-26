..
  Copyright 2024 The Khronos Group Inc.
  SPDX-License-Identifier: CC-BY-4.0

.. _properties:

**********
Properties
**********

Each of the following SYCL runtime classes: :ref:`command-accessor`,
:ref:`buffer`, :ref:`host_accessor`, :ref:`host_sampled_image_accessor`,
:ref:`host_unsampled_image_accessor`, :ref:`context`,
:ref:`local_accessor`, :ref:`queue`, :ref:`sampled_image`,
:ref:`sampled_image_accessor`, :ref:`stream`, :ref:`unsampled_image`,
:ref:`unsampled_image_accessor` and :ref:`usm_allocator`
provide an optional parameter in each of their constructors
to provide a ``sycl::property_list`` which contains zero or more properties.
Each of those properties augments the semantics of the class with
a particular feature. Each of those classes must also provide
``has_property`` and ``get_property`` member functions
for querying for a particular property.

Using properties does not affect the
type of the object, thus, does not prevent the usage of SYCL objects
in containers.

See :ref:`buffer-properties-example`.

.. seealso:: |SYCL_BUFF_PROP|

Each property is represented by a unique class and an instance of a property
is an instance of that type. Some properties can be default constructed while
others will require an argument on construction. A property may be applicable
to more than one class, however some properties may not be compatible
with each other.

.. _property_list:

=======================
``sycl::property_list``
=======================

Each of the runtime classes mentioned above must provide a common interface of
member functions in order to fulfill the property interface requirements.

A synopsis of the common properties interface, the ``sycl::property_list``
class and the SYCL property classes is provided below.

::

  namespace sycl {

  template <typename Property>
  struct is_property;

  template <typename Property>
  inline constexpr bool is_property_v = is_property<Property>::value;

  template <typename Property, typename SyclObject>
  struct is_property_of;

  template <typename Property, typename SyclObject>
  inline constexpr bool is_property_of_v = is_property_of<Property, SyclObject>::value;

  class T {
    ...

    template <typename Property>
    bool has_property() const noexcept;

    template <typename Property>
    Property get_property() const;

    ...
  };

  class property_list {
   public:
    template <typename... Properties>
    property_list(Properties... props);
  };

  } // namespace sycl

(constructor)
=============

::

  template <typename... PropertyN> property_list(PropertyN... props)

Available only when: ``sycl::is_property<property>::value`` evaluates to
``true`` where ``property`` is each property in ``PropertyN``.

Construct a ``sycl::property_list`` with zero or more properties.

.. _traits_for_properties:

=====================
Traits for properties
=====================

``sycl::is_property``
=====================

::

  template <typename Property>
  struct is_property;

An explicit specialization of ``sycl::is_property`` that inherits from
``std::true_type`` must be provided for each property, where
``Property`` is the class defining the property. This includes both
standard properties described in this specification and any additional
non-standard properties defined by an implementation. All other
specializations of ``sycl::is_property`` must inherit from ``std::false_type``.

``sycl::is_property_v``
=======================

::

  template <typename Property>
  inline constexpr bool is_property_v;

Variable containing value of ``sycl::is_property<Property>``.

``sycl::is_property_of``
========================

::

  template <typename Property, SyclObject>
  struct is_property_of;

An explicit specialization of ``sycl::is_property_of`` that inherits from
``std::true_type`` must be provided for each property that can be used
in constructing a given SYCL class, where ``Property`` is the class defining
the property and ``SyclObject`` is the SYCL class. This includes both standard
properties described in this specification and any additional non-standard
properties defined by an implementation. All other specializations of
``sycl::is_property_of`` must inherit from ``std::false_type``.

``sycl::is_property_of_v``
==========================

::

  template <typename Property, SyclObject>
  inline constexpr bool is_property_of_v;

Variable containing value of ``sycl::is_property_of<Property, SyclObject>``.

======================================================
Member functions of the SYCL common property interface
======================================================

``has_property``
================

::

  template <typename Property>
  bool has_property() const noexcept;

Returns true if ``T`` was constructed with the property specified
by ``Property``. Returns false if it was not.

``get_property``
================

::

  template <typename Property>
  Property get_property() const;

Returns a copy of the property of type ``Property`` that ``T`` was
constructed with. Must throw an ``sycl::exception`` with the
``sycl::errc::invalid`` error code if ``T`` was not constructed
with the ``Property`` property.

.. _buffer-properties-example:

==================================
Example of buffer properties usage
==================================

::

  {
    sycl::context myContext;

    std::vector<sycl::buffer<int, 1>> bufferList {
      sycl::buffer<int, 1> { ptr, rng },
      sycl::buffer<int, 1> { ptr, rng, sycl::property::use_host_ptr {} },
      sycl::buffer<int, 1> { ptr, rng, sycl::property::context_bound { myContext } }
    };

    for (auto& buf : bufferList) {
      if (buf.has_property<sycl::property::context_bound>()) {
        auto prop = buf.get_property<sycl::property::context_bound>();
        assert(myContext == prop.get_context());
      }
    }
  }
