..
  Copyright 2020 The Khronos Group Inc.
  SPDX-License-Identifier: CC-BY-4.0

.. _iface-buffers:

*******
Buffers
*******

.. _buffer:

================
``sycl::buffer``
================

::

  template <typename T, int Dimensions = 1,
            typename AllocatorT = sycl::buffer_allocator<std::remove_const_t<T>>>
  class buffer;

.. rubric:: Template parameters

================  ==========
``T``             Type of data in buffer.
``Dimensions``    Dimensionality of data: 1, 2, or 3.
``AllocatorT``    Allocator for buffer data.
================  ==========

The ``sycl::buffer`` class defines a shared array of one,
two or three dimensions that can be used by the SYCL kernel
and has to be accessed using :ref:`accessor classes <iface-accessors>`.
Buffers are templated on both the type of their data, and the number
of dimensions that the data is stored and accessed through.

A ``sycl::buffer`` does not map to only one underlying backend object,
and all SYCL backend memory objects may be temporary for use within a
command group on a specific device.

The underlying data type of a buffer ``T`` must be device copyable.
Some overloads of the ``sycl::buffer`` constructor initialize the buffer
contents by copying objects from host memory while other overloads
construct the buffer without copying objects from the host. For the
overloads that do not copy host objects, the initial state of the
objects in the buffer depends on whether ``T`` is an implicit-lifetime
type (as defined in the C++ core language).

* If ``T`` is an implicit-lifetime type, objects of that type are
  implicitly created in the buffer with indeterminate values.
* For other types, these constructor overloads merely allocate uninitialized
  memory, and the application is responsible for constructing objects by
  calling placement-new and for destroying them later by manually calling
  the object's destructor.

The SYCL buffer class template provides the :ref:`common-reference`.

The ``sycl::buffer`` class template takes a template parameter ``AllocatorT``
for specifying an allocator which is used by the SYCL runtime when allocating
temporary memory on the host. If no template argument is provided,
then the default allocator for the ``sycl::buffer``
class ``buffer_allocator<T>`` will be used.

.. seealso:: |SYCL_SPEC_BUFFER|

Member Types
============

.. list-table::
  :header-rows: 1

  * - Type
    - Description
  * - ``value_type``
    - Type of buffer elements (``T``).
  * - ``reference``
    - Reference type of buffer elements (``value_type&``).
  * - ``const_reference``
    - Constant reference type of buffer element (``const value_type&``).
  * - ``allocator_type``
    - Type of allocator for buffer data (``AllocatorT``).

.. _buffer-constructors:

(constructors)
==============

Each constructor takes as the last parameter an optional
``sycl::property_list`` to provide properties to the ``sycl::buffer``.

For the overloads that do copy objects from host memory, the ``hostData``
pointer must point to at least `N` bytes of memory where `N` is
``sizeof(T) * bufferRange.size()``.
If `N` is zero, ``hostData`` is permitted to be a null pointer.

.. parsed-literal::

  buffer(const sycl::range<dimensions> &bufferRange,
         const sycl::property_list &propList = {});
  buffer(const sycl::range<dimensions> &bufferRange, AllocatorT allocator,
         const sycl::property_list &propList = {});
  buffer(T *hostData, const sycl::range<dimensions> &bufferRange,
         const sycl::property_list &propList = {});
  buffer(T *hostData, const sycl::range<dimensions> &bufferRange,
         AllocatorT allocator, const sycl::property_list &propList = {});
  buffer(const T *hostData, const sycl::range<dimensions> &bufferRange,
         const sycl::property_list &propList = {});
  buffer(const T *hostData, const sycl::range<dimensions> &bufferRange,
         AllocatorT allocator, const sycl::property_list &propList = {});
  buffer(const shared_ptr_class<T> &hostData,
         const sycl::range<dimensions> &bufferRange, AllocatorT allocator,
         const sycl::property_list &propList = {});
  buffer(const shared_ptr_class<T> &hostData,
         const sycl::range<dimensions> &bufferRange,
         const sycl::property_list &propList = {});
  buffer(buffer<T, dimensions, AllocatorT> b, const id<dimensions> &baseIndex,
         const sycl::range<dimensions> &subRange);

  *Available only when:
   dimensions == 1*

  template <class InputIterator>
  buffer<T, 1>(InputIterator first, InputIterator last, AllocatorT allocator,
               const sycl::property_list &propList = {});
  template <class InputIterator>
  buffer<T, 1>(InputIterator first, InputIterator last,
               const sycl::property_list &propList = {});
  buffer(cl_mem clMemObject, const sycl::context &syclContext,
         event availableEvent = {});



.. rubric:: Template parameters

=================  ==========
``InputIterator``  type of iterator used to initialize the buffer
=================  ==========

.. rubric:: Parameters

================  ==========
``bufferRange``   :ref:`range` specifies the dimensions of the buffer
``allocator``     Allocator for buffer data
``propList``      See `Buffer properties`_
``hostData``      Pointer to host memory to hold data
``first``         Iterator to initialize buffer
``last``          Iterator to initialize buffer
``b``             Buffer used to initialize this buffer
``baseIndx``      Origin of sub-buffer
``subRange``      Dimensions of sub-buffer
================  ==========

================
Member functions
================

``get_range``
=============

::

  sycl::range<Dimensions> get_range() const;

Return a :ref:`range` object representing the size of the
buffer in terms of number of elements in each dimension as
passed to the constructor.


``size``
========

::

  size_t size() const noexcept;

Returns the total number of elements in the buffer.

Equal to ``get_range()[0] * ... * get_range()[Dimensions-1]``.


``get_count``
=============

::

  size_t get_count() const;

Deprecated. Returns the same value as size().


``byte_size``
=============

::

  size_t byte_size() const noexcept;

Returns the size of the buffer storage in bytes.

Equal to ``size()*sizeof(T)``.


``get_size``
============

::

  size_t get_size() const;

Deprecated. Returns the same value as ``byte_size()``.


``get_allocator``
=================

::

  AllocatorT get_allocator() const

Returns the allocator provided to the buffer.


.. _buffer-get_access:

``get_access``
==============

::

  template <sycl::access_mode Mode = sycl::access_mode::read_write,
            sycl::target Targ = sycl::target::device>
  sycl::accessor<T, Dimensions, Mode, Targ> get_access(sycl::handler& commandGroupHandler);

Returns a valid :ref:`command-accessor` to the buffer with the specified access
mode and target in the command group buffer.

The value of target can be ``sycl::target::device`` or
``sycl::target::constant_buffer``.

::

  template <sycl::access_mode Mode>
  sycl::accessor<T, Dimensions, Mode, sycl::target::host_buffer> get_access();

Deprecated in SYCL 2020. Use ``get_host_access()`` instead.

Returns a valid host ``sycl::accessor`` to the buffer with the
specified access mode and target.

::

  template <sycl::access_mode Mode = sycl::access_mode::read_write,
            sycl::target Targ = sycl::target::device>
  sycl::accessor<T, Dimensions, Mode, Targ> get_access(sycl::handler& commandGroupHandler,
                                                       sycl::range<Dimensions> accessRange,
                                                       sycl::id<Dimensions> accessOffset = {});

Returns a valid :ref:`command-accessor` to the buffer with the specified
access mode and target in the command group buffer.
The accessor is a ranged accessor, where the range starts at the given
offset from the beginning of the buffer.

The value of target can be ``sycl::target::device`` or
``sycl::target::constant_buffer``.

::

  template <sycl::access_mode Mode>
  sycl::accessor<T, Dimensions, Mode, sycl::target::host_buffer>
  get_access(sycl::range<Dimensions> accessRange,
             sycl::id<Dimensions> accessOffset = {});

Deprecated in SYCL 2020. Use ``get_host_access()`` instead.

Returns a valid host ``sycl::accessor`` to the buffer with the specified
access mode and target.
The accessor is a ranged accessor, where the range starts at the given
offset from the beginning of the buffer.

The value of target can only be ``sycl::target::host_buffer``.

::

  template <typename... Ts>
  auto get_access(Ts... args);

Returns a valid :ref:`command-accessor` as if constructed via passing the
buffer and all provided arguments to the ``sycl::accessor`` constructor.

Possible implementation: ``return sycl::accessor{*this, args...};``

.. rubric:: Template parameters

================  ==========
``mode``          See :ref:`access-mode`.
``target``        See :ref:`access-target`.
================  ==========

.. rubric:: Parameters

=======================  ==========
``commandGroupHandler``  Command group that uses the accessor.
``accessRange``          Dimensions of the sub-buffer that is accessed.
``accessOffset``         Origin of the sub-buffer that is accessed.
=======================  ==========

.. rubric:: Exceptions

``errc::invalid``
  If the sum of ``accessRange`` and ``accessOffset`` exceeds
  the range of the buffer in any dimension.


``get_host_access``
===================

::

  template <typename... Ts>
  auto get_host_access(Ts... args);

Returns a valid :ref:`host_accessor` as if constructed via passing the
buffer and all provided arguments to the ``sycl::host_accessor`` constructor.

Possible implementation: ``return sycl::host_accessor{*this, args...};``

``set_final_data``
==================

::

  template <typename Destination = std::nullptr_t>
  void set_final_data(Destination finalData = nullptr);

The ``finalData`` points to where the outcome of all the buffer
processing is going to be copied to at destruction time, if the buffer
was involved with a write accessor

Note that a raw pointer is a special case of output iterator and thus
defines the host memory to which the result is to be copied.

In the case of a weak pointer, the output is not updated if the weak
pointer has expired.

If ``Destination`` is ``std::nullptr_t``, then the copy back will not happen.

.. rubric:: Template parameters

===================  ==========
``Destination``      Output iterator or ``std::weak_ptr<T>``.
===================  ==========

.. rubric:: Parameters

===================  ==========
``finalData``        Indicates where data is copied at destruction time.
===================  ==========


``set_write_back``
==================

::

  void set_write_back(bool flag = true);

This member function allows dynamically forcing or canceling the
write-back of the data of a buffer on destruction according to
the value of ``flag``.

Forcing the write-back is similar to what happens during a normal write-back.

If there is nowhere to write-back, using this function does
not have any effect.


``is_sub_buffer``
=================

::

  bool is_sub_buffer() const;

Returns ``true`` if this ``sycl::buffer`` is a sub-buffer,
otherwise returns ``false``.


``reinterpret``
===============

A ``sycl::buffer`` can construct an instance of a ``sycl::buffer``
that reinterprets the original ``sycl::buffer`` with a different
type, dimensionality and range using the member function ``reinterpret``.

::

  template <typename ReinterpretT, int ReinterpretDim>
  sycl::buffer<ReinterpretT, ReinterpretDim,
               typename std::allocator_traits<AllocatorT>::template rebind_alloc<
                   std::remove_const_t<ReinterpretT>>>
  reinterpret(sycl::range<ReinterpretDim> reinterpretRange) const;

Creates and returns a reinterpreted ``sycl::buffer`` with the
type specified by ``ReinterpretT``, dimensions specified by
``ReinterpretDim`` and range specified by ``reinterpretRange``.

The buffer object being reinterpreted can be a SYCL sub-buffer
that was created from a ``sycl::buffer``.

Reinterpreting a sub-buffer provides a reinterpreted view of the
sub-buffer only, and does not change the offset or size of the
sub-buffer view (in bytes) relative to the parent ``sycl::buffer``.

::

  template <typename ReinterpretT, int ReinterpretDim = Dimensions>
  sycl::buffer<ReinterpretT, ReinterpretDim,
               typename std::allocator_traits<AllocatorT>::template rebind_alloc<
                   std::remove_const_t<ReinterpretT>>>
  reinterpret() const;

Creates and returns a reinterpreted ``sycl::buffer`` with the type specified by
``ReinterpretT`` and dimensions specified by ``ReinterpretDim``.

Only valid when ``(ReinterpretDim == 1)`` or when
``((ReinterpretDim == Dimensions) && (sizeof(ReinterpretT) == sizeof(T)))``.

The buffer object being reinterpreted can be a SYCL sub-buffer that was created
from a SYCL buffer.

Reinterpreting a sub-buffer provides a reinterpreted view of the
sub-buffer only, and does not change the offset or size of the
sub-buffer view (in bytes) relative to the parent ``sycl::buffer``.

.. rubric:: Template parameters

===================  ==========
``ReinterpretT``     Type of the new buffer element.
``ReinterpretDim``   Dimensions of the new buffer.
===================  ==========

.. rubric:: Parameters

====================  ==========
``reinterpretRange``  Dimensionality of the new buffer.
====================  ==========

.. rubric:: Exceptions

``errc::invalid``
  1. If the total size in bytes represented by the type and range of
     the reinterpreted ``sycl::buffer`` (or sub-buffer) does not equal
     the total size in bytes represented by the type and range of this
     ``sycl::buffer`` (or sub-buffer).
  2. If the total size in bytes represented by this ``sycl::buffer``
     (or sub-buffer) is not evenly divisible by ``sizeof(ReinterpretT)``.

=================
Buffer properties
=================

The properties that can be provided when
constructing the ``sycl::buffer``.

::

  namespace sycl::property {

  namespace buffer {

  class use_host_ptr;

  class use_mutex;

  class context_bound;

  } // namespace buffer

  } // namespace sycl::property


``sycl::property::buffer::use_host_ptr``
========================================

::

  namespace sycl::property::buffer {

  class use_host_ptr {
  public:
    use_host_ptr() = default;
  };

  } // namespace sycl::property::buffer

The ``sycl::property::buffer::use_host_ptr`` property adds the requirement
that the SYCL runtime must not allocate any memory for the ``sycl::buffer``
and instead uses the provided host pointer directly. This prevents the SYCL
runtime from allocating additional temporary storage on the host.

This property has a special guarantee for buffers that are constructed
from a ``hostData`` pointer. If a ``sycl::host_accessor`` is constructed from
such a buffer, then the address of the reference type returned from the
accessor's member functions such as ``operator[](id<>)`` will be the same
as the corresponding ``hostData`` address.

.. _use_host_ptr-constructors:

(constructors)
--------------

::

  sycl::property::buffer::use_host_ptr::use_host_ptr();

Constructs a ``sycl::property::buffer::use_host_ptr`` property instance.


``sycl::property::buffer::use_mutex``
=====================================

::

  namespace sycl::property::buffer {

  class use_mutex {
  public:
    use_mutex(std::mutex& mutexRef);

    std::mutex* get_mutex_ptr() const;
  };

  } // namespace sycl::property::buffer

The ``sycl::property::buffer::use_mutex`` property is valid for the
``sycl::buffer``, `unsampled_image` and `sampled_image` classes.

The property adds the requirement that the memory which is owned by
the ``sycl::buffer`` can be shared with the application via a
``std::mutex`` provided to the property.

The mutex is locked by the runtime whenever the data is in use and
unlocked otherwise. Data is synchronized with ``hostData``, when
the mutex is unlocked by the runtime.

.. _use_mutex-constructors:

(constructors)
--------------

::

  sycl::property::buffer::use_mutex::use_mutex(std::mutex& mutexRef);

Constructs a ``sycl::property::buffer::use_mutex`` property instance
with a reference to ``mutexRef`` parameter provided.

``get_mutex_ptr``
-----------------

::

  std::mutex* sycl::property::buffer::use_mutex::get_mutex_ptr() const;

Returns the ``std::mutex`` which was specified when constructing
this ``sycl::property::buffer::use_mutex`` property.


``sycl::property::buffer::context_bound``
=========================================

::

  namespace sycl::property::buffer {

  class context_bound {
  public:
    context_bound(context boundContext);

    context get_context() const;
  };

  } // namespace sycl::property::buffer


The ``sycl::property::buffer::context_bound`` property adds the
requirement that the ``sycl::buffer`` can only be associated
with a single :ref:`context` that is provided to the property.

.. _context_bound-constructors:

(constructors)
--------------

::

  sycl::property::buffer::context_bound(sycl::context boundContext);

Constructs a ``sycl::property::buffer::context_bound`` property
instance with a copy of a :ref:`context`.

``get_context``
---------------

::

  sycl::context sycl::property::buffer::context_bound::get_context() const;

Returns the :ref:`context` which was specified when constructing
this ``sycl::property::buffer::context_bound`` property.

============================
Buffer synchronization rules
============================
