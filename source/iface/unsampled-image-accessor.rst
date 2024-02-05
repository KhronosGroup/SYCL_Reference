..
  Copyright 2020 The Khronos Group Inc.
  SPDX-License-Identifier: CC-BY-4.0

.. _unsampled_image_accessors:

*************************
Unsampled image accessors
*************************

There are two classes which implement accessors for unsampled images,
``sycl::unsampled_image_accessor`` and ``sycl::host_unsampled_image_accessor``.
The former provides access from within a SYCL kernel function or from
within a host task. The latter provides access from host
code that is outside of a host task.

The dimensionality of an unsampled image accessor must match the
dimensionality of the underlying image to which it provides access.
Both unsampled image accessor classes support the
``access_mode::read`` and ``access_mode::write`` access modes.
In addition, the ``sycl::host_unsampled_image_accessor``
class supports ``access_mode::read_write``.

The AccessTarget template parameter dictates how the
``sycl::unsampled_image_accessor`` can be used: ``image_target::device``
means the accessor can be used in a SYCL kernel function while
``image_target::host_task`` means the accessor can be used in
a host task. Programs which specify this template parameter as
``image_target::device`` and then use the ``sycl::unsampled_image_accessor``
from a host task are ill formed. Likewise, programs which specify this
template parameter as ``image_target::host_task`` and then use the
``sycl::unsampled_image_accessor`` from a SYCL kernel function are ill formed.

.. _unsampled_image_accessor:

==================================
``sycl::unsampled_image_accessor``
==================================

::

  template <typename DataT, int Dimensions, access_mode AccessMode,
          image_target AccessTarget = image_target::device>
  class unsampled_image_accessor;

(constructor of the `unsampled_image_accessor`)
===============================================

.. parsed-literal::

  template <typename AllocatorT>
  unsampled_image_accessor(unsampled_image<Dimensions, AllocatorT>& imageRef,
                           handler& commandGroupHandlerRef,
                           const property_list& propList = {})

Constructs an ``sycl::unsampled_image_accessor`` for accessing an
``unsampled_image`` within a command on the :ref:`queue`
associated with ``commandGroupHandlerRef``. The optional
``property_list`` provides properties
for the constructed object.

If ``AccessTarget`` is ``image_target::device``,
throws an ``exception`` with the ``errc::feature_not_supported``
error code if the device associated with ``commandGroupHandlerRef``
does not have ``aspect::image``.

.. _host_unsampled_image_accessor:

=======================================
``sycl::host_unsampled_image_accessor``
=======================================

::

  template <typename DataT, int Dimensions = 1,
          access_mode AccessMode =
              (std::is_const_v<DataT> ? access_mode::read
                                      : access_mode::read_write)>
  class host_unsampled_image_accessor;

(constructor of the `host_unsampled_image_accessor`)
====================================================

.. parsed-literal::

  template <typename AllocatorT>
  host_unsampled_image_accessor(unsampled_image<Dimensions, AllocatorT>& imageRef,
                                const property_list& propList = {})

Constructs a ``sycl::host_unsampled_image_accessor`` for accessing an
``unsampled_image`` immediately on the host. The optional
``property_list`` provides properties for the constructed object.

===============================================
Member functions of the unsampled image classes
===============================================

Both classes have member functions with the same name,
which are described below.

``size``
========

::

  size_t size() const noexcept

Returns the number of elements of the underlying
``unsampled_image`` that this accessor is accessing.

``read``
========

::

  template <typename CoordT> DataT read(const CoordT& coords) const

Available only when
``(AccessMode == access_mode::read
|| AccessMode == access_mode::read_write)``.

Reads and returns an element of the ``unsampled_image`` at the
coordinates specified by ``coords``. Permitted types for ``CoordT``
are ``int`` when ``Dimensions == 1``, ``int2`` when
``Dimensions == 2`` and ``int4`` when ``Dimensions == 3``.

For ``sycl::unsampled_image_accessor``, this function may
only be called from within a command.

``write``
=========

::

  template <typename CoordT>
  void write(const CoordT& coords, const DataT& color) const

Available only when
``(AccessMode == access_mode::write
|| AccessMode == access_mode::read_write)``.

Writes the value specified by ``color`` to the element of the image at the
coordinates specified by ``coords``. Permitted types for ``CoordT``
are ``int`` when ``Dimensions == 1``, ``int2`` when
``Dimensions == 2`` and ``int4`` when ``Dimensions == 3``.

For ``sycl::unsampled_image_accessor``, this function may
only be called from within a command.

===========================================
Member types of the unsampled image classes
===========================================

Both classes have member types with the same name,
which are described below.

``value_type``
==============

If the accessor is read-only,
equal to ``const DataT``, otherwise equal to ``DataT``.

``reference``
=============

Equal to ``value_type&``.

``const_reference``
===================

Equal to ``const DataT&``.

=======================================
Interface for unsampled image accessors
=======================================

The additional common special member functions and common member
functions are listed in |SYCL_SPEC_COMMON_REFERENCE|.

Two ``sycl::unsampled_image_accessor`` objects of the same type must be
equality comparable in both the host code and in SYCL kernel functions.
Two ``sycl::host_unsampled_image_accessor`` objects of the same type must be
equality comparable in the host code.

For valid implicit conversions between unsampled
accessor types refer to :ref:`read_only_uia`

A synopsis of the two unsampled image accessor classes is provided below.

::

  namespace sycl {

  enum class image_target : /* unspecified */ { device, host_task };

  template <typename DataT, int Dimensions, access_mode AccessMode,
          image_target AccessTarget = image_target::device>
  class unsampled_image_accessor {
   public:
    using value_type = // const DataT for read-only accessors, DataT otherwise
        __value_type__;
    using reference = value_type&;
    using const_reference = const DataT&;

    template <typename AllocatorT>
    unsampled_image_accessor(unsampled_image<Dimensions, AllocatorT>& imageRef,
                             handler& commandGroupHandlerRef,
                             const property_list& propList = {});

    /* -- common interface members -- */

    /* -- property interface members -- */

    size_t size() const noexcept;

    /* Available only when: AccessMode == access_mode::read
    if Dimensions == 1, CoordT = int
    if Dimensions == 2, CoordT = int2
    if Dimensions == 3, CoordT = int4 */
    template <typename CoordT> DataT read(const CoordT& coords) const noexcept;

    /* Available only when: AccessMode == access_mode::write
    if Dimensions == 1, CoordT = int
    if Dimensions == 2, CoordT = int2
    if Dimensions == 3, CoordT = int4 */
    template <typename CoordT>
    void write(const CoordT& coords, const DataT& color) const;
  };

  template <typename DataT, int Dimensions = 1,
            access_mode AccessMode =
                (std::is_const_v<DataT> ? access_mode::read
                                        : access_mode::read_write)>
  class host_unsampled_image_accessor {
   public:
    using value_type = // const DataT for read-only accessors, DataT otherwise
        __value_type__;
    using reference = value_type&;
    using const_reference = const DataT&;

    template <typename AllocatorT>
    host_unsampled_image_accessor(
        unsampled_image<Dimensions, AllocatorT>& imageRef,
        const property_list& propList = {});

    /* -- common interface members -- */

    /* -- property interface members -- */

    size_t size() const noexcept;

    /* Available only when: (AccessMode == access_mode::read ||
                             AccessMode == access_mode::read_write)
    if Dimensions == 1, CoordT = int
    if Dimensions == 2, CoordT = int2
    if Dimensions == 3, CoordT = int4 */
    template <typename CoordT> DataT read(const CoordT& coords) const noexcept;

    /* Available only when: (AccessMode == access_mode::write ||
                             AccessMode == access_mode::read_write)
    if Dimensions == 1, CoordT = int
    if Dimensions == 2, CoordT = int2
    if Dimensions == 3, CoordT = int4 */
    template <typename CoordT>
    void write(const CoordT& coords, const DataT& color) const;
  };

  } // namespace sycl

.. _read_only_uia:

============================================================
Read only unsampled image accessors and implicit conversions
============================================================

All specializations of unsampled image accessors with ``access_mode::read``
are read-only regardless of whether ``DataT`` is ``const`` qualified.
There is an implicit conversion between the ``const`` qualified and
non-``const`` qualified specializations, provided that
all other template parameters are the same.
