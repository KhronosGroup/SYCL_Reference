..
  Copyright 2023 The Khronos Group Inc.
  SPDX-License-Identifier: CC-BY-4.0

.. _sampled_image_accessors:

***********************
Sampled image accessors
***********************

There are two classes which implement accessors for sampled images,
``sampled_image_accessor`` and ``host_sampled_image_accessor``.
The former provides access from within a SYCL kernel function or from
within a host task. The latter provides access from host
code that is outside of a host task.

The dimensionality of a sampled image accessor must match the
dimensionality of the underlying image to which it provides access.
Sampled image accessors are always read-only.

The ``AccessTarget`` template parameter dictates how the
``sampled_image_accessor`` can be used: ``image_target::device``
means the accessor can be used in a SYCL kernel function while
``image_target::host_task`` means the accessor can be used in
a host task. Programs which specify this template parameter as
``image_target::device`` and then use the ``sampled_image_accessor``
from a host task are ill formed. Likewise, programs which specify this
template parameter as ``image_target::host_task`` and then use the
``sampled_image_accessor`` from a SYCL kernel function are ill formed.

.. _sampled_image_accessor:

================================
``sycl::sampled_image_accessor``
================================

::

  template <typename DataT, int Dimensions,
            image_target AccessTarget = image_target::device>
  class sampled_image_accessor;

(constructor of the `sampled_image_accessor`)
=============================================

.. parsed-literal::

  template <typename AllocatorT>
  sampled_image_accessor(sampled_image<Dimensions, AllocatorT>& imageRef,
                         handler& commandGroupHandlerRef,
                         const property_list& propList = {})

Constructs a ``sampled_image_accessor`` for accessing a
``sampled_image`` within a command on the ``queue``
associated with ``commandGroupHandlerRef``. The optional
``property_list`` provides properties
for the constructed object.

If ``AccessTarget`` is ``image_target::device``,
throws an ``exception`` with the ``errc::feature_not_supported``
error code if the device associated with ``commandGroupHandlerRef``
does not have ``aspect::image``.

.. _host_sampled_image_accessor:

=======================================
``sycl::host_sampled_image_accessor``
=======================================

::

  template <typename DataT, int Dimensions>
  class host_sampled_image_accessor;

(constructor of the `host_sampled_image_accessor`)
====================================================

.. parsed-literal::

  template <typename AllocatorT>
  host_sampled_image_accessor(sampled_image<Dimensions, AllocatorT>& imageRef,
                              const property_list& propList = {})

Constructs a ``host_sampled_image_accessor`` for accessing an
``sampled_image`` immediately on the host. The optional
``property_list`` provides properties for the constructed object.

=============================================
Member functions of the sampled image classes
=============================================

Both classes have member functions with the same name,
which are described below.

``size``
========

::

  size_t size() const noexcept

Returns the number of elements of the underlying
``sampled_image`` that this accessor is accessing.

``read``
========

::

  template <typename CoordT>
  DataT read(const CoordT& coords) const

Reads and returns an element of the ``sampled_image`` at the
coordinates specified by ``coords``. Permitted types for ``CoordT``
are ``float`` when ``Dimensions == 1``, ``float2`` when
``Dimensions == 2`` and ``float4`` when ``Dimensions == 3``.

For ``sampled_image_accessor``, this function may
only be called from within a command.

=========================================
Member types of the sampled image classes
=========================================

Both classes have member types with the same name,
which are described below.

``value_type``
==============

Equal to ``const DataT``.

``reference``
=============

Equal to ``const DataT&``.

``const_reference``
===================

Equal to ``const DataT&``.

=====================================
Interface for sampled image accessors
=====================================

The additional common special member functions and common member
functions are listed in |SYCL_SPEC_COMMON_REFERENCE|.

Two ``sampled_image_accessor`` objects of the same type must be
equality comparable in both the host code and in SYCL kernel functions.
Two ``host_sampled_image_accessor`` objects of the same type must be
equality comparable in the host code.

For valid implicit conversions between sampled
accessor types refer to :ref:`read_only_sia`

::

  namespace sycl {

  enum class image_target : /* unspecified */ { device, host_task };

  template <typename DataT, int Dimensions,
            image_target AccessTarget = image_target::device>
  class sampled_image_accessor {
   public:
    using value_type = const DataT;
    using reference = const DataT&;
    using const_reference = const DataT&;

    template <typename AllocatorT>
    sampled_image_accessor(sampled_image<Dimensions, AllocatorT>& imageRef,
                           handler& commandGroupHandlerRef,
                           const property_list& propList = {});


    /* -- common interface members -- */

    /* -- property interface members -- */

    size_t size() const noexcept;

    /* if Dimensions == 1, CoordT = float
       if Dimensions == 2, CoordT = float2
       if Dimensions == 3, CoordT = float4 */
    template <typename CoordT> DataT read(const CoordT& coords) const noexcept;
  };

  template <typename DataT, int Dimensions> class host_sampled_image_accessor {
   public:
    using value_type = const DataT;
    using reference = const DataT&;
    using const_reference = const DataT&;

    template <typename AllocatorT>
    host_sampled_image_accessor(sampled_image<Dimensions, AllocatorT>& imageRef,
                                const property_list& propList = {});

    /* -- common interface members -- */

    /* -- property interface members -- */

    size_t size() const noexcept;

    /* if Dimensions == 1, CoordT = float
       if Dimensions == 2, CoordT = float2
       if Dimensions == 3, CoordT = float4 */
    template <typename CoordT> DataT read(const CoordT& coords) const noexcept;
  };

  } // namespace sycl

.. _read_only_sia:

==========================================================
Read only sampled image accessors and implicit conversions
==========================================================

All specializations of sampled image accessors are read-only regardless
of whether ``DataT`` is ``const`` qualified. There is an implicit conversion
between the ``const`` qualified and non-``const`` qualified specializations,
provided that all other template parameters are the same.
