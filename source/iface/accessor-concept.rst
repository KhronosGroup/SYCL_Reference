..
  Copyright 2020 The Khronos Group Inc.
  SPDX-License-Identifier: CC-BY-4.0

.. _accessor-concept:

************************
General Accessor Concept
************************

.. seealso:: |SYCL_SPEC_ACCESSORS|

==========
Data types
==========

All accessors have a ``DataT`` template parameter which specifies
the type of each element that the accessor accesses. For
:ref:`command-accessor` and :ref:`host_accessor`, this type must
either match the type of each element in the underlying :ref:`buffer`,
or it must be a ``const`` qualified version of that type.

For the image accessors (:ref:`unsampled-image-accessors`,
:ref:`sampled-image-accessors`), ``DataT`` must be one of:

* ``sycl::int4`` (``sycl::vec<int32_t, 4>``);
* ``sycl::uint4 `` (``sycl::vec<uint32_t, 4>``);
* ``sycl::float4 `` (``sycl::vec<float, 4>``);
* ``sycl::half4 `` (``sycl::vec<half, 4>``).

See :ref:`local_accessor` page for it's allowed ``DataT`` types.

.. _access-mode:

======================
``sycl::access::mode``
======================

Most accessors have an ``AccessMode`` template parameter which
specifies whether the accessor can read or write the underlying data.

This information is used by the runtime when defining the requirements
for the associated command, and it tells the runtime whether data
needs to be transferred to or from a device before data can be
accessed through the accessor.

.. note::

  Not all accessor classes support all modes, so see the description of each class for more details.

::

  namespace sycl {

  enum class access_mode : /* unspecified */ {
    read,
    write,
    read_write,
    discard_write,      // Deprecated in SYCL 2020
    discard_read_write, // Deprecated in SYCL 2020
    atomic              // Deprecated in SYCL 2020
  };

  namespace access {
  // The legacy type "access::mode" is deprecated.
  using mode = sycl::access_mode;
  } // namespace access

  } // namespace sycl

.. list-table::
  :header-rows: 1

  * - Access mode
    - Description
  * - ``sycl::access_mode::read``
    - Read-only access.
  * - ``sycl::access_mode::write``
    - Write-only access.
  * - ``sycl::access_mode::read_write``
    - Read and write access.

.. _deduction-tags:

==============
Deduction tags
==============

Some accessor constructors take a ``TagT`` parameter, which is
used to deduce template arguments for the constructor's class.

Each of the access modes in table above has an associated tag,
but there are additional tags which set other template parameters
in addition to the access mode. The synopsis below shows the
namespace scope variables that the implementation provides as
possible values for the ``TagT`` parameter.

::

  namespace sycl {

  inline constexpr __unspecified__ read_only;
  inline constexpr __unspecified__ read_write;
  inline constexpr __unspecified__ write_only;
  inline constexpr __unspecified__ read_only_host_task;
  inline constexpr __unspecified__ read_write_host_task;
  inline constexpr __unspecified__ write_only_host_task;

  } // namespace sycl

The precise meaning of these tags depends on the specific
accessor class that is being constructed, so they are
described more fully in the page that pertains
to each of the accessor types.

.. _accessor-properties:

==========
Properties
==========

All accessor constructors accept a ``sycl::property_list`` parameter,
which affects the semantics of the accessor.

::

  namespace sycl {
  namespace property {
  struct no_init {};
  } // namespace property

  inline constexpr property::no_init no_init;
  } // namespace sycl

Table below shows the set of all possible accessor properties and tells
which properties are allowed when constructing each accessor class.

``sycl::property::no_init``
===========================

**Allowed with:**
  * ``sycl::accessor``
  * ``sycl::host_accessor``
  * ``sycl::unsampled_image_accessor``
  * ``sycl::host_unsampled_image_accessor``

This property is useful when an application expects to write new
values to all of the accessor's elements without reading their
previous values. The implementation can use this information to
avoid copying the accessor's data in some cases.

Following is a more formal description:


This property is allowed only for accessors with
``sycl::access_mode::write`` or ``sycl::access_mode::read_write``
access modes. Attempting to construct an ``sycl::access_mode::read``
accessor with this property causes an ``exception`` with the
``errc::invalid`` error code to be thrown.

The usage of this property is different depending on whether
the accessor's underlying data type ``DataT`` is an
implicit-lifetime type (as defined in the C++ core language):

* If it is an implicit-lifetime type, the accessor implicitly
  creates objects of that type with indeterminate values.
  The application is not required to write values to each
  element of the accessor, but unwritten elements of the accessor's
  buffer or image receive indeterminate values, even if those buffer
  or image elements previously had defined values.
* If ``DataT`` is not an implicit-lifetime type, the accessor
  merely allocates uninitialized memory, and the application
  is responsible for constructing objects in that memory
  (e.g. by calling placement-new). The application must create an
  object in each element of the accessor unless the corresponding
  element of the underlying buffer did not previously contain an object.

If this is a :ref:`ranged accessor <ranged-accessors>`, this applies
only to the elements within the accessor's range. The content of objects
in the buffer outside of this range is preserved.

.. note::

  As stated above, the ``sycl::property::no_init`` property requires
  the application to construct an object for each accessor element
  when the element's type is not an implicit-lifetime type
  (except in the case when the corresponding buffer element
  did not previously contain an object).

  The reason for this requirement is to avoid the possibility of
  overwriting a valid object with indeterminate bytes, for example,
  when a command using the accessor completes. This means that the
  implementation can unconditionally copy memory from the device
  back to the host when the command completes, regardless of
  whether the ``DataT`` type is an implicit-lifetime type.

(constructor)
-------------

::

  sycl::property::no_init::no_init();

Constructs a ``sycl::property::no_init`` property instance.

===================
Read only accessors
===================


=================================
Accessing elements of an accessor
=================================

===================
Container interface
===================

.. _ranged-accessors:

================
Ranged accessors
================
