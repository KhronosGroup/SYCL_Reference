..
  Copyright 2020 The Khronos Group Inc.
  SPDX-License-Identifier: CC-BY-4.0

.. rst-class:: api-class

.. _command-accessor:

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

.. _access-targets:

==============
Access targets
==============

.. list-table::
  :header-rows: 1

  * - Accessor target
    - Meaning
  * - ``target::device``
    - Access a buffer from a SYCL kernel function via device global memory.
  * - ``target::host_task``
    - Access a buffer from a host task.


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

The previous version of ``get_pointer`` function deprecated in SYCL 2020.
Use ``get_multi_ptr`` instead.

::

  std::add_pointer_t<value_type> get_pointer() const noexcept

Available only when ``(AccessTarget == target::host_task)``.

Returns a pointer to the start of this accessor’s underlying buffer,
even if this is a ranged accessor whose range does not start at
the beginning of the buffer. The return value
is unspecified if the accessor is empty.

This function may only be called from within a command.

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

.. _tags_buff_accessors:

====================
Buffer accessor tags
====================

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
  * - ``not const-qualified``
    - ``access_mode::read``
  * - ``const-qualified``
    - ``access_mode::read``

The specializations of ``accessor`` with
``target::device`` or ``target::host_task`` that are read-only accessors.
There is an implicit conversion between any of these specializations,
provided that all other template parameters are the same.

``read-write accessors``
========================

.. list-table::
  :header-rows: 1

  * - Data type
    - Access mode
  * - ``not const-qualified``
    - ``access_mode::read_write``

The table present an implicit conversion from
the read-write specialization.

===================
Common member types
===================

``value_type``
==============

If the accessor is read-only, equal to ``const DataT``,
otherwise equal to ``DataT``.

See |SYCL_ACCESSOR_READ_ONLY_BUFF_CMD|, |SYCL_ACCESSOR_READ_ONLY_BUFF_HOST|
and |SYCL_ACCESSOR_READ_ONLY_LOCAL| for which accessors
are considered read-only.

``reference``
=============

Equal to ``value_type&``.

``const_reference``
===================

Equal to ``const DataT&``.

``iterator``
============

Iterator that can provide ranged access. Cannot be written to if the
``accessor`` is read-only. The underlying pointer is address space
qualified for accessor specializations with
``target::device`` and for ``local_accessor``.

``const_iterator``
==================

Iterator that can provide ranged access. Cannot be written to.
The underlying pointer is address space qualified for ``accessor``
specializations with ``target::device`` and for ``local_accessor``.

``reverse_iterator``
====================

Iterator adaptor that reverses the direction of ``iterator``.

``const_reverse_iterator``
==========================

Iterator adaptor that reverses the direction of ``const_iterator``.

``difference_type``
===================

Equal to ``typename std::iterator_traits<iterator>::difference_type``.

``size_type``
=============

Equal to ``size_t``.

======================
Common member function
======================

``byte_size``
=============

::

  size_type byte_size() const noexcept

Returns the size in bytes of the memory region this accessor may access.

For a buffer accessor this is the size of the underlying buffer,
unless it is a ranged accessor in which case it is the size of
the elements within the accessor’s range.

For a local accessor this is the size of the accessor’s local
memory allocation, per work-group.

``size``
========

::

  size_type size() const noexcept

Returns the number of ``DataT`` elements of the memory region this
accessor may access.

For a buffer accessor this is the number of elements in the underlying
buffer, unless it is a ranged accessor in which case it is the number
of elements within the accessor’s range.

For a local accessor this is the number of elements in the accessor’s
local memory allocation, per work-group.

``max_size``
============

::

  size_type max_size() const noexcept

Returns the maximum number of elements any accessor of this
type would be able to access.

``empty``
=========

::

  bool empty() const noexcept

Returns ``true`` if ``(size() == 0)``.

``get_range``
=============

::

  range<Dimensions> get_range() const

Available only when ``(Dimensions > 0)``.

Returns a ``range`` object which represents the number of elements of
``DataT`` per dimension that this accessor may access.

For a buffer accessor this is the range of the underlying buffer,
unless it is a ranged accessor in which case it is the range that
was specified when the accessor was constructed.

``reference``
=============

::

  operator reference() const

For ``accessor`` available only when
``(AccessMode != access_mode::atomic && Dimensions == 0)``.

For ``host_accessor`` and ``local_accessor``
available only when ``(Dimensions == 0)``.

Returns a reference to the single element that is accessed
by this accessor.

For ``accessor`` and ``local_accessor``, this function may only
be called from within a command.

``operator[]``
==============

::

  reference operator[](id<Dimensions> index) const

For ``accessor`` available only when
``(AccessMode != access_mode::atomic && Dimensions > 0)``.

For ``host_accessor`` and ``local_accessor`` available only
when ``(Dimensions > 0)``.

Returns a reference to the element at the location specified by ``index``.
If this is a ranged accessor, the element is determined by
adding ``index`` to the accessor’s offset.

For ``accessor`` and ``local_accessor``, this function may
only be called from within a command.

::

  __unspecified__ operator[](size_t index) const

Available only when ``(Dimensions > 1)``.

Returns an instance of an undefined intermediate type representing
this accessor, with the dimensionality ``Dimensions-1`` and containing
an implicit ``id`` with index ``Dimensions`` set to ``index``.
The intermediate type returned must provide all available subscript
operators which take a ``size_t`` parameter defined by this accessor
class that are appropriate for the type it represents
(including this subscript operator).

If this is a ranged accessor, the implicit ``id`` in the returned
instance also includes the accessor’s offset.

For ``accessor`` and ``local_accessor``, this function may only
be called from within a command.

::

  reference operator[](size_t index) const

For ``accessor`` available only when
``(AccessMode != access_mode::atomic && Dimensions == 1)``.

For ``host_accessor`` and ``local_accessor`` available
only when ``(Dimensions == 1)``.

Returns a reference to the element at the location specified by ``index``.
If this is a ranged accessor, the element is
determined by adding ``index`` to the accessor’s offset.

For ``accessor`` and ``local_accessor``, this function may
only be called from within a command.

``begin``
=========

::

  iterator begin() const noexcept

Returns an iterator to the first element of the memory this
accessor may access.

For a buffer accessor this is an iterator to the first element
of the underlying buffer, unless this is a ranged accessor in which
case it is an iterator to first element within the accessor’s range.

For ``accessor`` and ``local_accessor``, this function may
only be called from within a command.

``end``
=======

::

  iterator end() const noexcept

Returns an iterator to one element past the last element
of the memory this accessor may access.

For a buffer accessor this is an iterator to one element past
the last element in the underlying buffer, unless this is a ranged
accessor in which case it is an iterator to one element past the
last element within the accessor’s range.

For ``accessor`` and ``local_accessor``, this function may
only be called from within a command.

``cbegin``
==========

::

  const_iterator cbegin() const noexcept

Returns a ``const`` iterator to the first element of the
memory this accessor may access.

For a buffer accessor this is a ``const`` iterator to the first element
of the underlying buffer, unless this is a ranged accessor in which
case it is a ``const`` iterator to first element within the accessor’s range.

For ``accessor`` and ``local_accessor``, this function may
only be called from within a command.

``cend``
========

::

  const_iterator cend() const noexcept

Returns a ``const`` iterator to one element past the last element
of the memory this accessor may access.

For a buffer accessor this is a ``const`` iterator to one element past
the last element in the underlying buffer, unless this is a ranged
accessor in which case it is a ``const`` iterator to one element past the
last element within the accessor’s range.

For ``accessor`` and ``local_accessor``, this function may
only be called from within a command.

``rbegin``
==========

::

  reverse_iterator rbegin() const noexcept

Returns an iterator adaptor to the last element
of the memory this accessor may access.

For a buffer accessor this is an iterator adaptor to the
last element of the underlying buffer, unless this is a ranged
accessor in which case it is an iterator adaptor to the last
element within the accessor’s range.

For ``accessor`` and ``local_accessor``, this function may
only be called from within a command.

``rend``
========

::

  reverse_iterator rend() const noexcept

Returns an iterator adaptor to one element before the first element
of the memory this accessor may access.

For a buffer accessor this is an iterator adaptor to one element
before the first element in the underlying buffer, unless this is
a ranged accessor in which case it is an iterator adaptor to one
element before the first element within the accessor’s range.

For ``accessor`` and ``local_accessor``, this function may
only be called from within a command.

``crbegin``
===========

::

  const_reverse_iterator crbegin() const noexcept

Returns a ``const`` iterator adaptor to the last element of the memory
this accessor may access.

For a buffer accessor this is a ``const`` iterator adaptor to the last
element of the underlying buffer, unless this is a ranged accessor
in which case it is an ``const`` iterator adaptor to last
element within the accessor’s range.

For ``accessor`` and ``local_accessor``, this function may
only be called from within a command.

``crend``
=========

::

  const_reverse_iterator crend() const noexcept

Returns a ``const`` iterator adaptor to one element before the first
element of the memory this accessor may access.

For a buffer accessor this is a ``const`` iterator adaptor to one element
before the first element in the underlying buffer, unless this is
a ranged accessor in which case it is a ``const`` iterator adaptor to one
element before the first element within the accessor’s range.

For ``accessor`` and ``local_accessor``, this function may
only be called from within a command.
