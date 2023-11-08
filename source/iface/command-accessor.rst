..
  Copyright 2020 The Khronos Group Inc.
  SPDX-License-Identifier: CC-BY-4.0

.. rst-class:: api-class

.. _buffer-accessor:

==================
``sycl::accessor``
==================

::

  class accessor;

The ``accessor`` class provides access to data in a ``buffer`` from within a
SYCL kernel function or from within a host task. When used in a SYCL kernel
function, it accesses the contents of the buffer via the device’s
global memory. These two forms of the accessor are distinguished
by the ``AccessTarget`` template parameter. Both forms support
the following values for the ``AccessMode`` template parameter:
``access_mode::read``, ``access_mode::write`` and
``access_mode::read_write``.

.. seealso:: SYCL Specification |SYCL_SPEC_BUFFER_ACCESSOR|

============
Member types
============

``accessor_ptr``
================

::

  template <access::decorated IsDecorated> accessor_ptr

If ``(AccessTarget == target::device):
multi_ptr<value_type, access::address_space::global_space, IsDecorated>.``

The definition of this type is not specified when
``(AccessTarget == target::host_task)``.


(constructors)
==============

.. parsed-literal::

  accessor()

  template <typename AllocatorT>
  accessor(buffer<DataT, 1, AllocatorT>& bufferRef,
           const property_list& propList = {})

  template <typename AllocatorT>
  accessor(buffer<DataT, 1, AllocatorT>& bufferRef,
           handler& commandGroupHandlerRef, const property_list& propList = {})

  template <typename AllocatorT>
  accessor(buffer<DataT, Dimensions, AllocatorT>& bufferRef,
           const property_list& propList = {})

  template <typename AllocatorT, typename TagT>
  accessor(buffer<DataT, Dimensions, AllocatorT>& bufferRef, TagT tag,
           const property_list& propList = {})

  template <typename AllocatorT>
  accessor(buffer<DataT, Dimensions, AllocatorT>& bufferRef,
           handler& commandGroupHandlerRef, const property_list& propList = {})

  template <typename AllocatorT, typename TagT>
  accessor(buffer<DataT, Dimensions, AllocatorT>& bufferRef,
           handler& commandGroupHandlerRef, TagT tag,
           const property_list& propList = {})

  template <typename AllocatorT>
  accessor(buffer<DataT, Dimensions, AllocatorT>& bufferRef,
           range<Dimensions> accessRange, const property_list& propList = {})

  template <typename AllocatorT, typename TagT>
  accessor(buffer<DataT, Dimensions, AllocatorT>& bufferRef,
           range<Dimensions> accessRange, TagT tag,
           const property_list& propList = {})

  template <typename AllocatorT>
  accessor(buffer<DataT, Dimensions, AllocatorT>& bufferRef,
           range<Dimensions> accessRange, id<Dimensions> accessOffset,
           const property_list& propList = {})

  template <typename AllocatorT, typename TagT>
  accessor(buffer<DataT, Dimensions, AllocatorT>& bufferRef,
           range<Dimensions> accessRange, id<Dimensions> accessOffset, TagT tag,
           const property_list& propList = {})

  template <typename AllocatorT>
  accessor(buffer<DataT, Dimensions, AllocatorT>& bufferRef,
           handler& commandGroupHandlerRef, range<Dimensions> accessRange,
           const property_list& propList = {})

  template <typename AllocatorT, typename TagT>
  accessor(buffer<DataT, Dimensions, AllocatorT>& bufferRef,
           handler& commandGroupHandlerRef, range<Dimensions> accessRange,
           TagT tag, const property_list& propList = {})

  template <typename AllocatorT>
  accessor(buffer<DataT, Dimensions, AllocatorT>& bufferRef,
           handler& commandGroupHandlerRef, range<Dimensions> accessRange,
           id<Dimensions> accessOffset, const property_list& propList = {})

  template <typename AllocatorT, typename TagT>
  accessor(buffer<DataT, Dimensions, AllocatorT>& bufferRef,
           handler& commandGroupHandlerRef, range<Dimensions> accessRange,
           id<Dimensions> accessOffset, TagT tag,
           const property_list& propList = {})

Constructors of the accessor class.
The descriptions are listed in |SYCL_ACCESS_CON|.

================
Member functions
================

``swap``
========

::

  void swap(accessor& other);

Swaps the contents of the current accessor with
the contents of ``other``.

``is_placeholder``
==================

::

  bool is_placeholder() const

Returns ``true`` if the accessor is a placeholder.
Otherwise returns ``false``.

``get_offset``
==============

::

  id<Dimensions> get_offset() const

Available only when ``(Dimensions > 0)``.

If this is a ranged accessor, returns the offset
that was specified when the accessor was constructed.
For other accessors, returns the default
constructed ``id<Dimensions>{}``.

``get_pointer``
===============

::

  global_ptr<access::decorated::legacy> get_pointer() const noexcept

Deprecated in SYCL 2020. Use ``get_multi_ptr`` instead.

``get_multi_ptr``
=================

::

  template <access::decorated IsDecorated>
  accessor_ptr<IsDecorated> get_multi_ptr() const noexcept

Available only when ``(AccessTarget == target::device)``.

Returns a ``multi_ptr`` to the start of this accessor’s
underlying buffer, even if this is a ranged accessor
whose range does not start at the beginning of the buffer.
The return value is unspecified if the accessor is empty.

This function may only be called from within a command.

``operator=``
=============

::

  const accessor& operator=(const value_type& other) const

  const accessor& operator=(value_type&& other) const

Available only when
``(AccessMode != access_mode::atomic &&
AccessMode != access_mode::read && Dimensions == 0)``.

Assignment to the single element that is accessed by this accessor.

This function may only be called from within a command.

.. _tags_buff_accessors:

=============================
Buffer command accessors tags
=============================

Some ``accessor`` constructors take a ``TagT`` parameter,
which is used to deduce template arguments.
The permissible values for this parameter are listed in table below.

.. list-table::
  :header-rows: 1

  * - Tag value
    - Access mode
    - Accessor target
  * - ``read_write;``
    - ``access_mode::read_write``
    - ``target::device``
  * - ``read_only;``
    - ``access_mode::read``
    - ``target::device``
  * - ``write_only;``
    - ``access_mode::write``
    - ``target::device``
  * - ``read_write_host_task;``
    - ``access_mode::read_write``
    - ``target::host_task``
  * - ``read_only_host_task;``
    - ``access_mode::read``
    - ``target::host_task``
  * - ``write_only_host_task;``
    - ``access_mode::write``
    - ``target::host_task``


``read-only accessors``
=======================

.. list-table::
  :header-rows: 1

  * - Data type
    - Access mode
  * - not const-qualified
    - ``access_mode::read``
  * - const-qualified
    - ``access_mode::read``

The specializations of ``accessor`` with
``target::device or target::host_task`` that are read-only accessors.
There is an implicit conversion between any of these specializations,
provided that all other template parameters are the same.

``read-write accessors``
========================

.. list-table::
  :header-rows: 1

  * - Data type
    - Access mode
  * - not const-qualified
    - ``access_mode::read_write``

The table present an implicit conversion from
the read-write specialization.

========================
Common types and members
========================

The ``accessor``, ``host_accessor``, and ``local_accessor``
classes have many member types and member functions with the
same name and meaning.

|SYCL_ACCESSOR_COMMON_TYPES| describes these common types and
|SYCL_ACCESSOR_COMMON_MEMBERS| describes the common member functions.
