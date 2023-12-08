..
  Copyright 2023 The Khronos Group Inc.
  SPDX-License-Identifier: CC-BY-4.0

.. _host_accessor:

***********************
``sycl::host_accessor``
***********************

::

  class host_accessor;

The ``host_accessor`` class provides access to data in a ``buffer``
from host code that is outside of a command (i.e. do not use this
class to access a buffer from inside device code or a host task).

As with ``accessor``, the dimensionality of ``host_accessor``
must match the underlying buffer, however, there is a special case
if the buffer is one-dimensional. In this case, the accessor may
either be one-dimensional or it may be zero-dimensional.
A zero-dimensional accessor has access to just the first element of
the buffer, whereas a one-dimensional accessor
has access to the entire buffer.

The ``host_accessor`` class supports the following access modes:
``access_mode::read``,``access_mode::write``
and ``access_mode::read_write``.

==============
(constructors)
==============

.. parsed-literal::

  host_accessor()

  template <typename AllocatorT>
  host_accessor(buffer<DataT, 1, AllocatorT>& bufferRef,
                const property_list& propList = {})

  template <typename AllocatorT>
  host_accessor(buffer<DataT, Dimensions, AllocatorT>& bufferRef,
                const property_list& propList = {})

  template <typename AllocatorT, typename TagT>
  host_accessor(buffer<DataT, Dimensions, AllocatorT>& bufferRef, TagT tag,
                const property_list& propList = {})

  template <typename AllocatorT>
  host_accessor(buffer<DataT, Dimensions, AllocatorT>& bufferRef,
                range<Dimensions> accessRange, const property_list& propList = {})

  template <typename AllocatorT, typename TagT>
  host_accessor(buffer<DataT, Dimensions, AllocatorT>& bufferRef,
                range<Dimensions> accessRange, TagT tag,
                const property_list& propList = {})

  template <typename AllocatorT>
  host_accessor(buffer<DataT, Dimensions, AllocatorT>& bufferRef,
                range<Dimensions> accessRange, id<Dimensions> accessOffset,
                const property_list& propList = {})

  template <typename AllocatorT, typename TagT>
  host_accessor(buffer<DataT, Dimensions, AllocatorT>& bufferRef,
                range<Dimensions> accessRange, id<Dimensions> accessOffset,
                TagT tag, const property_list& propList = {})

Constructors of the host_accessor class.
The descriptions are listed in |SYCL_ACCESS_HOST_CON|.

================
Member functions
================

``swap``
========

::

  void swap(host_accessor& other);

Swaps the contents of the current accessor with
the contents of ``other``.

``get_offset``
==============

::

  id<Dimensions> get_offset() const

Available only when ``(Dimensions > 0)``.

If this is a ranged accessor, returns the offset that was specified
when the accessor was constructed. For other accessors,
returns the default constructed ``id<Dimensions>{}``.

``get_pointer``
===============

::

  std::add_pointer_t<value_type> get_pointer() const noexcept

Returns a pointer to the start of this accessor’s underlying buffer,
even if this is a ranged accessor whose range does not start at the
beginning of the buffer. The return value is unspecified
if the accessor is empty.

``operator=``
=============

::

  const host_accessor& operator=(const value_type& other) const

Available only when ``(AccessMode != access_mode::read && Dimensions == 0)``.

Assignment to the single element that is accessed by this accessor.

::

  const host_accessor& operator=(value_type&& other) const

Available only when ``(AccessMode != access_mode::read && Dimensions == 0)``.

Assignment to the single element that is accessed by this accessor.


.. _deduction_tags_buff_host_accessors:

=========================
Buffer host accessor tags
=========================

Some ``host_accessor`` constructors take a ``TagT`` parameter,
which is used to deduce template arguments.
The permissible values for this parameter are listed in table below.

.. list-table::
  :header-rows: 1

  * - Tag value
    - Access mode
  * - ``read_write;``
    - ``access_mode::read_write``
  * - ``read_only;``
    - ``access_mode::read``
  * - ``write_only;``
    - ``access_mode::write``

``read-only host accessors``
============================

.. list-table::
  :header-rows: 1

  * - Data type
    - Access mode
  * - ``not const-qualified``
    - ``access_mode::read``
  * - ``const-qualified``
    - ``access_mode::read``

These specializations of ``host_accessor`` are read-only accessors.
There is an implicit conversion between any of these specializations,
provided that all other template parameters are the same.

``read-write host accessors``
=============================

.. list-table::
  :header-rows: 1

  * - Data type
    - Access mode
  * - ``not const-qualified``
    - ``access_mode::read_write``

There is also an implicit conversion from the
``read-write host_accessor`` type to any of the
``read-only host accessors``, provided that all
other template parameters are the same.

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

=======================
Common member functions
=======================

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

===================================
Interface for buffer host accessors
===================================

A synopsis of the ``host_accessor`` class is provided below.

::

  namespace sycl {
  template <typename DataT, int Dimensions = 1,
            access_mode AccessMode =
                (std::is_const_v<DataT> ? access_mode::read
                                      : access_mode::read_write)>
  class host_accessor {
   public:
    using value_type = // const DataT for read-only accessors, DataT otherwise
        __value_type__;
    using reference = value_type&;
    using const_reference = const DataT&;
    using iterator = __unspecified_iterator__<value_type>;
    using const_iterator = __unspecified_iterator__<const value_type>;
    using reverse_iterator = std::reverse_iterator<iterator>;
    using const_reverse_iterator = std::reverse_iterator<const_iterator>;
    using difference_type =
        typename std::iterator_traits<iterator>::difference_type;
    using size_type = size_t;

    host_accessor();

    /* Available only when: (Dimensions == 0) */
    template <typename AllocatorT>
    host_accessor(buffer<DataT, 1, AllocatorT>& bufferRef,
                  const property_list& propList = {});

    /* Available only when: (Dimensions > 0) */
    template <typename AllocatorT>
    host_accessor(buffer<DataT, Dimensions, AllocatorT>& bufferRef,
                  const property_list& propList = {});

    /* Available only when: (Dimensions > 0) */
    template <typename AllocatorT, typename TagT>
    host_accessor(buffer<DataT, Dimensions, AllocatorT>& bufferRef, TagT tag,
                  const property_list& propList = {});

    /* Available only when: (Dimensions > 0) */
    template <typename AllocatorT>
    host_accessor(buffer<DataT, Dimensions, AllocatorT>& bufferRef,
                  range<Dimensions> accessRange,
                  const property_list& propList = {});

    /* Available only when: (Dimensions > 0) */
    template <typename AllocatorT, typename TagT>
    host_accessor(buffer<DataT, Dimensions, AllocatorT>& bufferRef,
                  range<Dimensions> accessRange, TagT tag,
                  const property_list& propList = {});

    /* Available only when: (Dimensions > 0) */
    template <typename AllocatorT>
    host_accessor(buffer<DataT, Dimensions, AllocatorT>& bufferRef,
                  range<Dimensions> accessRange, id<Dimensions> accessOffset,
                  const property_list& propList = {});

    /* Available only when: (Dimensions > 0) */
    template <typename AllocatorT, typename TagT>
    host_accessor(buffer<DataT, Dimensions, AllocatorT>& bufferRef,
                  range<Dimensions> accessRange, id<Dimensions> accessOffset,
                  TagT tag, const property_list& propList = {});

    /* -- common interface members -- */

    void swap(host_accessor& other);

    size_type byte_size() const noexcept;

    size_type size() const noexcept;

    size_type max_size() const noexcept;

    bool empty() const noexcept;

    /* Available only when: (Dimensions > 0) */
    range<Dimensions> get_range() const;

    /* Available only when: (Dimensions > 0) */
    id<Dimensions> get_offset() const;

    /* Available only when: (Dimensions == 0) */
    operator reference() const;

    /* Available only when: (AccessMode != access_mode::read && Dimensions == 0) */
    const host_accessor& operator=(const value_type& other) const;

    /* Available only when: (AccessMode != access_mode::read && Dimensions == 0) */
    const host_accessor& operator=(value_type&& other) const;

    /* Available only when: (Dimensions > 0) */
    reference operator[](id<Dimensions> index) const;

    /* Available only when: (Dimensions > 1) */
    __unspecified__ operator[](size_t index) const;

    /* Available only when: (Dimensions == 1) */
    reference operator[](size_t index) const;

    std::add_pointer_t<value_type> get_pointer() const noexcept;

    iterator begin() const noexcept;

    iterator end() const noexcept;

    const_iterator cbegin() const noexcept;

    const_iterator cend() const noexcept;

    reverse_iterator rbegin() const noexcept;

    reverse_iterator rend() const noexcept;

    const_reverse_iterator crbegin() const noexcept;

    const_reverse_iterator crend() const noexcept;
  };
  } // namespace sycl
