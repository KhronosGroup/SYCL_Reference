..
  Copyright 2020 The Khronos Group Inc.
  SPDX-License-Identifier: CC-BY-4.0

.. _local_accessor:

.. _buffer-local_accessor:

========================
``sycl::local_accessor``
========================

::

  class local_accessor;

The ``local_accessor`` class allocates device local memory and provides
access to this memory from within a SYCL kernel function. The local
memory that is allocated is shared between all work-items of a work-group.
If multiple work-groups execute simultaneously in an implementation,
each work-group receives its own independent copy
of the allocated local memory.

The underlying ``DataT`` type can be any C++ type that the device supports.
If ``DataT`` is an implicit-lifetime type (as defined in the C++ core
language), the local accessor implicitly creates objects of that type with
indeterminate values. For other types, the local accessor merely allocates
uninitialized memory, and the application is responsible for constructing
objects in that memory (e.g. by calling placement-new).

A local accessor must not be used in a SYCL kernel function that is invoked
via ``single_task`` or via the simple form of ``parallel_for`` that takes
a ``range`` parameter. In these cases submitting the kernel to a queue must
throw a synchronous ``exception`` with the
``errc::kernel_argument`` error code.

(constructors)
==============

.. parsed-literal::

  local_accessor()

  local_accessor(handler& commandGroupHandlerRef,
                 const property_list& propList = {})

  local_accessor(range<Dimensions> allocationSize,
                 handler& commandGroupHandlerRef,
                 const property_list& propList = {})


Constructors of the local_accessor class.
The descriptions are listed in |SYCL_ACCESS_LOCAL_CON|.

Member functions
================

``swap``
========

::

  void swap(local_accessor& other);

Swaps the contents of the current accessor with
the contents of ``other``.

``get_pointer``
===============

::

  local_ptr<DataT> get_pointer() const noexcept

Returns a ``multi_ptr`` to the start of this accessor’s local memory
region which corresponds to the calling work-group.
The return value is unspecified if the accessor is empty.

This function may only be called from within a command.

Deprecated in SYCL 2020. Use ``get_multi_ptr`` instead.

``get_multi_ptr``
=================

::

  template <access::decorated IsDecorated>
  accessor_ptr<IsDecorated> get_multi_ptr() const noexcept

Returns a ``multi_ptr`` to the start of the accessor’s local memory
region which corresponds to the calling work-group.
The return value is unspecified if the accessor is empty.

This function may only be called from within a SYCL kernel function.

``operator=``
=============

::

  const local_accessor& operator=(const value_type& other) const

Available only when ``(!std::is_const_v<DataT> && Dimensions == 0)``.

Assignment to the single element that is accessed by this accessor.

This function may only be called from within a command.

::

  const local_accessor& operator=(const value_type&& other) const

Available only when ``(!std::is_const_v<DataT> && Dimensions == 0)``.

Assignment to the single element that is accessed by this accessor.

This function may only be called from within a command.

Member types
============

``accessor_ptr``
================

::

  template <access::decorated IsDecorated> accessor_ptr

Equal to ``multi_ptr<value_type,
access::address_space::local_space, IsDecorated>``.

=========================
Read-only local accessors
=========================

Since ``local_accessor`` has no template parameter for the access
mode, the only specialization for a read-only local accessor is by
providing a ``const`` qualified ``DataT`` parameter. Specializations
with a non-``const`` qualified ``DataT`` parameter are read-write.
There is an implicit conversion from the read-write specialization to
the read-only specialization, provided that all other
template parameters are the same.

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

====================================
Interface for buffer local accessors
====================================

A synopsis of the ``local_accessor`` class is provided below.

::

  namespace sycl {
  template <typename DataT, int Dimensions = 1> class local_accessor {
   public:
    using value_type = // const DataT for read-only accessors, DataT otherwise
        __value_type__;
    using reference = value_type&;
    using const_reference = const DataT&;
    template <access::decorated IsDecorated>
    using accessor_ptr =
        multi_ptr<value_type, access::address_space::local_space, IsDecorated>;
    using iterator = __unspecified_iterator__<value_type>;
    using const_iterator = __unspecified_iterator__<const value_type>;
    using reverse_iterator = std::reverse_iterator<iterator>;
    using const_reverse_iterator = std::reverse_iterator<const_iterator>;
    using difference_type =
        typename std::iterator_traits<iterator>::difference_type;
    using size_type = size_t;

    local_accessor();

    /* Available only when: (Dimensions == 0) */
    local_accessor(handler& commandGroupHandlerRef,
                   const property_list& propList = {});

    /* Available only when: (Dimensions > 0) */
    local_accessor(range<Dimensions> allocationSize,
                   handler& commandGroupHandlerRef,
                   const property_list& propList = {});

    /* -- common interface members -- */

    void swap(accessor& other);

    size_type byte_size() const noexcept;

    size_type size() const noexcept;

    size_type max_size() const noexcept;

    bool empty() const noexcept;

    range<Dimensions> get_range() const;

    /* Available only when: (Dimensions == 0) */
    operator reference() const;

    /* Available only when: (!std::is_const_v<DataT> && Dimensions == 0) */
    const local_accessor& operator=(const value_type& other) const;

    /* Available only when: (!std::is_const_v<DataT> && Dimensions == 0) */
    const local_accessor& operator=(value_type&& other) const;

    /* Available only when: (Dimensions > 0) */
    reference operator[](id<Dimensions> index) const;

    /* Available only when: (Dimensions > 1) */
    __unspecified__ operator[](size_t index) const;

    /* Available only when: (Dimensions == 1) */
    reference operator[](size_t index) const;

    /* Deprecated in SYCL 2020 */
    local_ptr<DataT> get_pointer() const noexcept;

    template <access::decorated IsDecorated>
    accessor_ptr<IsDecorated> get_multi_ptr() const noexcept;

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
