..
  Copyright 2020 The Khronos Group Inc.
  SPDX-License-Identifier: CC-BY-4.0

.. _properties:

**********
Properties
**********

Each of the following SYCL runtime classes: ``accessor``, ``buffer``,
``host_accessor``, ``host_sampled_image_accessor``,
``host_unsampled_image_accessor``, ``context``,
``local_accessor``, ``queue``, ``sampled_image``,
``sampled_image_accessor``, ``stream``, ``unsampled_image``,
``unsampled_image_accessor`` and ``usm_allocator``
provide an optional parameter in each of their constructors
to provide a ``property_list`` which contains zero or more properties.
Each of those properties augments the semantics of the class with
a particular feature. Each of those classes must also provide
``has_property`` and ``get_property`` member functions
for querying for a particular property.

The example below illustrates how using properties does not affect the
type of the object, thus, does not prevent the usage of SYCL objects
in containers.

See `buffer-properties-example`_.

.. seealso:: |SYCL_BUFF_PROP|

Each property is represented by a unique class and an instance of a property
is an instance of that type. Some properties can be default constructed while
others will require an argument on construction. A property may be applicable
to more than one class, however some properties may not be compatible
with each other.

.. _property_list`:

``sycl::property_list``
=======================

Each of the runtime classes mentioned above must provide a common interface of
member functions in order to fulfill the property interface requirements.

A synopsis of the common properties interface, the SYCL ``property_list``
class and the SYCL property classes is provided below.

::


  namespace sycl {

  template <typename Property> struct is_property;

  template <typename Property>
  inline constexpr bool is_property_v = is_property<Property>::value;

  template <typename Property, typename SyclObject> struct is_property_of;

  template <typename Property, typename SyclObject>
  inline constexpr bool is_property_of_v =
      is_property_of<Property, SyclObject>::value;

  class T {
    ...

        template <typename Property>
        bool has_property() const noexcept;

    template <typename Property> Property get_property() const;

    ...
  };

  class property_list {
   public:
    template <typename... Properties> property_list(Properties... props);
  };
  } // namespace sycl

(constructor)
==============

::

  template <typename... PropertyN> property_list(PropertyN... props)

Available only when: ``is_property<property>::value`` evaluates to
``true`` where ``property`` is each property in ``PropertyN``.

Construct a SYCL ``property_list`` with zero or more properties.

.. _traits_for_properties :

Traits for properties
=====================

``is_property``
===============

::

  template <typename Property> struct is_property

An explicit specialization of ``is_property`` that inherits from
``std::true_type`` must be provided for each property, where
``Property`` is the class defining the property. This includes both
standard properties described in this specification and any additional
non-standard properties defined by an implementation. All other
specializations of ``is_property`` must inherit from ``std::false_type``.

``is_property_v``
=================

::

  template <typename Property> inline constexpr bool is_property_v;

Variable containing value of ``is_property<Property>``.

``is_property_of``
==================

::

  template <typename Property, SyclObject> struct is_property_of

An explicit specialization of ``is_property_of`` that inherits from
``std::true_type`` must be provided for each property that can be used
in constructing a given SYCL class, where ``Property`` is the class defining
the property and ``SyclObject`` is the SYCL class. This includes both standard
properties described in this specification and any additional non-standard
properties defined by an implementation. All other specializations of
``is_property_of`` must inherit from ``std::false_type``.

``is_property_of_v``
====================

::

  template <typename Property, SyclObject> inline constexpr bool is_property_of_v;

Variable containing value of ``is_property_of<Property, SyclObject>``.

Member functions
================

``has_property``
================

::

  template <typename Property> bool has_property() const noexcept

Returns true if ``T`` was constructed with the property specified
by ``Property``. Returns false if it was not.

``get_property``
================

::

  template <typename Property> Property get_property() const

Returns a copy of the property of type ``Property`` that ``T`` was
constructed with. Must throw an ``exception`` with the
``errc::invalid`` error code if ``T`` was not constructed
with the ``Property`` property.

.. _ buffer-properties-example:

``buffer-properties-example``
=============================

::

  {
    context myContext;

    std::vector<buffer<int, 1>> bufferList {
      buffer<int, 1> { ptr, rng },
      buffer<int, 1> { ptr, rng, property::use_host_ptr {} },
      buffer<int, 1> { ptr, rng, property::context_bound { myContext } }
    };

    for (auto& buf : bufferList) {
      if (buf.has_property<property::context_bound>()) {
        auto prop = buf.get_property<property::context_bound>();
        assert(myContext == prop.get_context());
      }
    }
  }
