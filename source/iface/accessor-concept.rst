..
  Copyright 2020 The Khronos Group Inc.
  SPDX-License-Identifier: CC-BY-4.0

.. _accessor-concept:

************************
General Accessor Concept
************************

Accessors provide three different capabilities: they provide access to
the data managed by a :ref:`buffer` or :ref:`image <image>`, they provide
access to local memory on a :ref:`device`, and they define the requirements
to memory objects which determine the scheduling of kernels.

A memory object requirement is created when an accessor is constructed,
unless the accessor is a placeholder in which case the requirement is
created when the accessor is bound to a command by calling
``sycl::handler::require()``.

There are several different C++ classes that implement accessors:

* The :ref:`command-accessor` class provides access to data in a
  :ref:`buffer` from within a command.
* The :ref:`host_accessor` class provides access to data in a
  :ref:`buffer` from host code that is outside of a command.
  These accessors are typically used in application scope.
* The :ref:`local_accessor` class provides access to device
  local memory from within a SYCL kernel function.
* The ``sycl::unsampled_image_accessor`` and
  ``sycl::sampled_image_accessor`` classes provide access to
  data in an ``sycl::unsampled_image`` and ``sycl::sampled_image``
  from within a command.
* The ``sycl::host_unsampled_image_accessor`` and
  ``sycl::host_sampled_image_accessor`` classes provide access to
  data in an ``sycl::unsampled_image`` and ``sycl::sampled_image``
  from host code that is outside of a command. These accessors
  are typically used in application scope.

Accessor objects must always be constructed in host code,
either in command group scope or in application scope. Whether the
constructor blocks waiting for data to synchronize depends on the
type of accessor:

* Those accessors which provide access to data within a command do
  not block. Instead, these accessors define a requirement which
  influences the scheduling of the command.
* Those accessors which provide access to data from host code do
  block until the data is available on the host.

.. warning::

  For those accessors which provide access to data within a command,
  the member functions which access data should only be called from
  within the command. Programs which call these member functions
  from outside of the command are ill formed.

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
* ``sycl::uint4`` (``sycl::vec<uint32_t, 4>``);
* ``sycl::float4`` (``sycl::vec<float, 4>``);
* ``sycl::half4`` (``sycl::vec<half, 4>``).

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

======================
Accessor specification
======================

Accessing elements of an accessor
=================================

Accessors of type :ref:`command-accessor`, :ref:`host_accessor`,
and :ref:`local_accessor` can have zero, one, two, or three Dimensions.

A zero dimension accessor provides access to a single scalar element
via an implicit conversion operator to the underlying type of that
element and via an overloaded copy/move assignment operators from
the underlying type of the element.

One, two, or three dimensional specializations of these accessors
provide access to the elements they contain in two ways:

1. Through a subscript operator that takes an instance of an :ref:`id`
   class which has the same dimensionality as the accessor.
2. By passing a single ``size_t`` value to multiple consecutive
   subscript operators as specified in |SYCL_SPEC_MD_ACC_SUBSCRIPT_OP|.

In all these cases, the reference to the contained element is of
type ``const DataT&`` for read-only accessors and of type ``DataT&``
for other accessors.

Accessors of all types have a range that defines the set of indices
that may be used to access elements:

* For buffer accessors, this is the range of the underlying buffer,
  unless it is a :ref:`ranged accessor <ranged-accessors>` in which
  case the range comes from the accessor's constructor.
* For image accessors, this is the range of the underlying image.
* Local accessors specify the range when the accessor is constructed.

.. warning::

  Any attempt to access an element via an index that is outside of
  this range produces undefined behavior.

Container interface
===================

Accessors of type :ref:`command-accessor`, :ref:`host_accessor`,
and :ref:`local_accessor` meet the C++ requirement of
``ReversibleContainer``.

The exception to this is that only ``sycl::local_accessor`` owns
the underlying data, meaning that its destructor destroys elements
and frees the memory. The ``sycl::accessor`` and ``sycl::host_accessor``
types don't destroy any elements or free the memory on destruction.

The iterator for the container interface meets the C++ requirement
of ``LegacyRandomAccessIterator`` and the underlying
pointers/references correspond to the address space specified
by the accessor type. For multidimensional accessors the iterator
linearizes the data according to rules in the |SYCL_SPEC_MD_ACC_LINEAR_RULES|.

Read only accessors
===================

Accessors which have an ``AccessMode`` template parameter can be
declared as read-only by specifying ``sycl::access_mode::read``
for the template parameter. A read-only accessor provides
read-only access to the underlying data and provides a "read"
requirement for the memory object when it is constructed.

The ``DataT`` template parameter for a read-only accessor
can optionally be ``const`` qualified, and the semantics of
the accessor are unchanged. For example, an accessor declared
with ``const DataT`` and ``sycl::access_mode::read`` has the
same semantics as an accessor declared with ``DataT`` and
``sycl::access_mode::read``.

Some accessor types have a default value for ``AccessMode``,
which depends on whether the ``DataT`` parameter is ``const``
qualified. This provides a convenient way to declare a
read-only accessor without explicitly specifying the access mode.

A ``const`` qualified ``DataT`` is only allowed for a read-only
accessor. Programs which specify a ``const`` qualified ``DataT`` and
any access mode other than ``sycl::access_mode::read`` are ill
formed, and the implementation must issue a diagnostic in this case.

Each accessor class also provides implicit conversions between
the two forms of read-only accessors. This makes it possible,
for example, to assign an accessor whose type has ``const DataT``
and ``sycl::access_mode::read`` to an accessor whose type has
``DataT`` and ``sycl::access_mode::read``, so long as the other
template parameters are the same. There is also an implicit
conversion from a read-write accessor to either of the forms
of a read-only accessor.

.. _ranged-accessors:

Ranged accessors
================

Accessors of type :ref:`command-accessor`, :ref:`host_accessor`,
and :ref:`local_accessor` can be constructed from a sub-range of
a :ref:`buffer` by providing a range and offset to the constructor.

This limits the elements that can be accessed to the specified
sub-range, which allows the implementation to perform certain
optimizations such as reducing the amount of memory that needs
to be copied to or from a device.

If the ranged accessor is multi-dimensional, the sub-range is
allowed to describe a region of memory in the underlying buffer
that is not contiguous in the linear address space. It is also
legal to construct several ranged accessors for the same
underlying buffer, either overlapping or non-overlapping.

Accessing the underlying buffer
-------------------------------

A ranged accessor still creates a requisite for the entire
underlying buffer, even for the portions not within the range.
For example, if one command writes through a ranged accessor
to one region of a buffer and a second command reads through
a ranged accessor from a non-overlapping region of the same
buffer, the second command must still be scheduled after the
first because the requisites for the two commands are on the
entire buffer, not on the sub-ranges of the ranged accessors.

Most of the accessor member functions which provide a
reference to the underlying buffer elements are affected
by a ranged accessor's offset and range. For example, calling
``operator[](0)`` on a one-dimensional ranged accessor returns
a reference to the element at the position specified by the
accessor's offset, which is not necessarily the first element
in the buffer. In addition, the accessor's iterator functions
iterate only over the elements that are within the sub-range.

The only exceptions are the ``get_pointer`` and ``get_multi_ptr``
member functions, which return a pointer to the beginning of
the underlying buffer regardless of the accessor's offset.
Applications using these functions must take care to manually
add the offset before dereferencing the pointer because accessing
an element that is outside of the accessor's range results
in undefined behavior.

.. note::

  There is no change in behavior for ranged accessors with a range
  of zero. It still creates a requisite for the entire underlying
  buffer, and an attempt to access an element produces undefined
  behavior.
