..
  Copyright 2024 The Khronos Group Inc.
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
Zero or more properties can be provided to the
constructed ``sycl::buffer`` via an instance of ``sycl::property_list``.

For the overloads that do copy objects from host memory, the ``hostData``
pointer must point to at least `N` bytes of memory where `N` is
``sizeof(T) * bufferRange.size()``.
If `N` is zero, ``hostData`` is permitted to be a null pointer.

.. rubric:: Constructors 1-2

::

  buffer(const sycl::range<Dimensions>& bufferRange,
         const sycl::property_list& propList = {});

  buffer(const sycl::range<Dimensions>& bufferRange,
         AllocatorT allocator,
         const sycl::property_list& propList = {});

Construct a ``sycl::buffer`` instance with uninitialized memory.

The constructed ``sycl::buffer`` will use the ``allocator``
parameter provided when allocating memory on the host.
If this parameter is not specified, the constructed
``sycl::buffer`` will use a default constructed
``AllocatorT`` when allocating memory on the host.

Data is not written back to the host on destruction of the buffer
unless the buffer has a valid non-null pointer specified via
the member function ``set_final_data()``.


.. rubric:: Constructors 3-4

::

  buffer(T* hostData,
         const sycl::range<Dimensions>& bufferRange,
         const sycl::property_list& propList = {});

  buffer(T* hostData,
         const sycl::range<Dimensions>& bufferRange,
         AllocatorT allocator,
         const sycl::property_list& propList = {});

Construct a ``sycl::buffer`` instance with the
``hostData`` parameter provided.
The buffer is initialized with the memory specified by ``hostData``,
and the buffer assumes exclusive access to this memory for the
duration of its lifetime.

The constructed ``sycl::buffer`` will use the ``allocator``
parameter provided when allocating memory on the host.
If this parameter is not specified, the constructed
``sycl::buffer`` will use a default constructed
``AllocatorT`` when allocating memory on the host.


.. rubric:: Constructors 5-6

::

  buffer(const T* hostData,
         const sycl::range<Dimensions>& bufferRange,
         const sycl::property_list& propList = {});

  buffer(const T* hostData,
         const sycl::range<Dimensions>& bufferRange,
         AllocatorT allocator,
         const sycl::property_list& propList = {});

Construct a ``sycl::buffer`` instance with the ``hostData`` parameter
provided. The buffer assumes exclusive access to this memory for
the duration of its lifetime.

The constructed ``sycl::buffer`` will use the ``allocator``
parameter provided when allocating memory on the host.
If this parameter is not specified, the constructed
``sycl::buffer`` will use a default constructed
``AllocatorT`` when allocating memory on the host.

The host address is ``const T``, so the host accesses can be
read-only. However, the ``typename T`` is not ``const`` so the
device accesses can be both read and write accesses.

Since the ``hostData`` is ``const``, this buffer is only initialized
with this memory and there is no write back after its destruction,
unless the ``sycl::buffer`` has another valid non-null final data
address specified via the member function ``set_final_data()``
after construction of the ``sycl::buffer``.


.. rubric:: Constructors 7-8

::

  template <typename Container>
  buffer(Container& container,
         const sycl::property_list& propList = {});

  template <typename Container>
  buffer(Container& container,
         AllocatorT allocator,
         const sycl::property_list& propList = {});

Construct a one dimensional ``sycl::buffer`` instance from the
elements starting at ``std::data(container)`` and containing
``std::size(container)`` number of elements.
The buffer is initialized with the contents of ``container``,
and the buffer assumes exclusive access to ``container`` for
the duration of its lifetime.

Data is written back to ``container`` before the completion of
``sycl::buffer`` destruction if the return type of
``std::data(container)`` is not ``const``.

The constructed ``sycl::buffer`` will use the ``allocator``
parameter provided when allocating memory on the host.
If this parameter is not specified, the constructed
``sycl::buffer`` will use a default constructed
``AllocatorT`` when allocating memory on the host.

This constructor is only defined for a buffer parameterized
with ``Dimensions == 1``, and when ``std::data(container)``
is convertible to ``T*``.


.. rubric:: Constructors 9-12

::

  buffer(const std::shared_ptr<T>& hostData,
         const sycl::range<Dimensions>& bufferRange,
         const sycl::property_list& propList = {});

  buffer(const std::shared_ptr<T[]>& hostData,
         const sycl::range<Dimensions>&  bufferRange,
         const sycl::property_list& propList = {});

  buffer(const std::shared_ptr<T>& hostData,
         const sycl::range<Dimensions>& bufferRange,
         AllocatorT allocator,
         const sycl::property_list& propList = {});

  buffer(const std::shared_ptr<T[]>& hostData,
         const sycl::range<Dimensions>& bufferRange,
         AllocatorT allocator,
         const sycl::property_list& propList = {});

When ``hostData`` is not empty, construct a ``sycl::buffer``
with the contents of its stored pointer. The buffer assumes
exclusive access to this memory for the duration of its lifetime.

The buffer also creates its own internal copy of the ``std::shared_ptr``
that shares ownership of the ``hostData`` memory, which means the
application can safely release ownership of this ``std::shared_ptr``
when the constructor returns.

When ``hostData`` is empty, construct a SYCL
buffer with uninitialized memory.

The constructed ``sycl::buffer`` will use the ``allocator``
parameter provided when allocating memory on the host.
If this parameter is not specified, the constructed
``sycl::buffer`` will use a default constructed
``AllocatorT`` when allocating memory on the host.


.. rubric:: Constructors 13-14

::

  template <typename InputIterator>
  buffer(InputIterator first, InputIterator last,
         const sycl::property_list& propList = {});

  template <typename InputIterator>
  buffer(InputIterator first, InputIterator last,
         AllocatorT allocator = {},
         const sycl::property_list& propList = {});

Create a new allocated one dimension ``sycl::buffer`` initialized
from the given elements ranging from ``first`` up to one before ``last``.

The data is copied to an intermediate memory position by the runtime.

Data is not written back to the same iterator set provided.
However, if the ``sycl::buffer`` has a valid non-constant iterator
specified via the member function ``set_final_data()``,
data will be copied back to that iterator.

The constructed ``sycl::buffer`` will use the ``allocator``
parameter provided when allocating memory on the host.
If this parameter is not specified, the constructed
``sycl::buffer`` will use a default constructed
``AllocatorT`` when allocating memory on the host.


.. rubric:: Constructor 15

::

  buffer(sycl::buffer& b,
         const sycl::id<Dimensions>& baseIndex,
         const sycl::range<Dimensions>& subRange)

Create a new sub-buffer without allocation to have
separate accessors later.

``b`` is the buffer with the real data, which must not
be a sub-buffer.

``baseIndex`` specifies the origin of the sub-buffer
inside the buffer ``b``.
``subRange`` specifies the size of the sub-buffer.
The offset and range specified by ``baseIndex`` and ``subRange``
together must represent a contiguous region of the
original ``sycl::buffer``.

The origin (based on ``baseIndex``) of the sub-buffer being
constructed must be a multiple of the memory base address
alignment of each :ref:`device` which accesses data from
the buffer. This value is retrievable via the :ref:`device`
class info query ``sycl::info::device::mem_base_addr_align``.

Violating this requirement causes the implementation to throw
an ``exception`` with the ``errc::invalid`` error code from
the :ref:`command-accessor` constructor (if the accessor
is not a placeholder) or from ``sycl::handler::require()``
(if the accessor is a placeholder).
If the accessor is bound to a command group with a secondary
queue, the sub-buffer's alignment must be compatible with
both the primary queue's device and the secondary queue's
device, otherwise this exception is thrown.

.. rubric:: Template parameters

=================  ==========
``Container``      Type of the ``container`` used to
                   initialize the buffer.
``InputIterator``  Type of iterator used to initialize the buffer.
=================  ==========

.. rubric:: Parameters

================  ==========
``bufferRange``   :ref:`range` specifies the dimensions of the buffer.
``allocator``     Allocator for the buffer data. In case this parameter
                  is absent, the ``sycl::buffer`` will use a default
                  constructed ``AllocatorT`` when allocating memory
                  on the host.
``propList``      See `Buffer properties`_.
``hostData``      Pointer to host memory to hold data.
``first``         Beginning iterator to initialize the buffer.
``last``          Ending iterator to initialize the buffer.
``b``             Parent buffer used to initialize this buffer.
``baseIndx``      Origin of the sub-buffer.
``subRange``      Dimensions of the sub-buffer.
================  ==========

.. rubric:: Exceptions

``errc::invalid``
  An exception with this error code will be thrown in
  the constructor 15 in such cases:

  1. If the sum of ``baseIndex`` and ``subRange`` in any dimension
     exceeds the parent buffer (``b``) size (``bufferRange``)
     in that dimension.
  2. If a non-contiguous region of a buffer is requested
     when constructing a sub-buffer.
  3. If ``b`` is a sub-buffer.

.. rubric:: Example

See :ref:`sub_buf_example`.

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

  template <typename... Ts>
  auto get_access(Ts... args);

Returns a valid :ref:`command-accessor` as if constructed via passing the
buffer and all provided arguments to the ``sycl::accessor`` constructor.

Possible implementation: ``return sycl::accessor{*this, args...};``

.. rubric:: Deprecated in SYCL 2020

::

  template <sycl::access_mode Mode>
  sycl::accessor<T, Dimensions, Mode, sycl::target::host_buffer> get_access();

Deprecated in SYCL 2020. Use ``get_host_access()`` instead.

Returns a valid host ``sycl::accessor`` to the buffer with the
specified access mode and target.

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

.. rubric:: Template parameters

================  ==========
``mode``          See :ref:`access-mode`.
``target``        See :ref:`buffer-access-targets`.
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

.. _buffer-synchronization-rules:

============================
Buffer synchronization rules
============================

Buffer lifetime and destruction
===============================

Buffers are reference-counted. When a buffer value is constructed
from another buffer, the two values reference the same buffer and
a reference count is incremented. When a buffer value is destroyed,
the reference count is decremented. Only when there are no more
buffer values that reference a specific buffer is the actual buffer
destroyed and the buffer destruction behavior defined below is followed.

If any error occurs on buffer destruction, it is reported via the
associated queue's asynchronous error handling mechanism.

The basic rule for the blocking behavior of a buffer destructor is that
it blocks if there is some data to write back because a write accessor
on it has been created, or if the buffer was constructed with attached
host memory and is still in use.

More precisely:

  1. A buffer can be constructed from a :ref:`range`
     (and without a ``hostData`` pointer). The memory
     management for this type of buffer is entirely handled
     by the SYCL system. The destructor for this type of buffer
     does not need to block, even if work on the buffer has not
     completed. Instead, the SYCL system frees any storage
     required for the buffer asynchronously when it is no longer
     in use in queues. The initial contents of the buffer are unspecified.
  2. A buffer can be constructed from a ``hostData`` pointer. The buffer
     will use this host memory for its full lifetime, but the contents of
     this host memory are unspecified for the lifetime of the buffer.
     If the host memory is modified on the host or if it is used to
     construct another buffer or image during the lifetime of this
     buffer, then the results are undefined. The initial contents of
     the buffer will be the contents of the host memory at the time
     of construction.

     When the buffer is destroyed, the destructor will block until all
     work in queues on the buffer have completed, then copy the contents
     of the buffer back to the host memory (if required) and then return.

     a. If the type of the host data is ``const``, then the buffer is
        read-only; only read accessors are allowed on the buffer and
        no-copy-back to host memory is performed (although the host
        memory must still be kept available for use by SYCL). When
        using the default buffer allocator, the constantness of the
        type will be removed in order to allow host allocation of
        memory, which will allow temporary host copies of the data
        by the SYCL runtime, for example for speeding up host accesses.
     b. If the type of the host data is not ``const`` but the pointer
        to host data is ``const``, then the read-only restriction
        applies only on host and not on device accesses.

        When the buffer is destroyed, the destructor will block until
        all work in queues on the buffer have completed.
  3. A buffer can be constructed using a ``std::shared_ptr`` to host
     data. This pointer is shared between the SYCL application and
     the runtime. In order to allow synchronization between the
     application and the runtime a ``std::mutex`` is used which will be
     locked by the runtime whenever the data is in use, and unlocked
     when it is no longer needed.

     The ``std::shared_ptr`` reference counting is used in order to
     prevent destroying the buffer host data prematurely. If the
     ``std::shared_ptr`` is deleted from the user application
     before buffer destruction, the buffer can continue securely
     because the pointer hasn't been destroyed yet. It will not
     copy data back to the host before destruction, however, as
     the application side has already deleted its copy.

     .. note::
       Since there is an implicit conversion of a ``std::unique_ptr``
       to a ``std::shared_ptr``, a ``std::unique_ptr`` can also be
       used to pass the ownership to the SYCL runtime.
  4. A buffer can be constructed from a pair of iterator values. In this
     case, the buffer construction will copy the data from the data range
     defined by the iterator pair. The destructor will not copy back any
     data and does not need to block.
  5. A buffer can be constructed from a container on which
     ``std::data(container)`` and ``std::size(container)`` are well-formed.
     The initial contents of the buffer will be the contents of the
     container at the time of construction.

     The buffer may use the memory within the container for its
     full lifetime, and the contents of this memory are unspecified
     for the lifetime of the buffer. If the container memory is modified
     by the host during the lifetime of this buffer, then the results are
     undefined.

     When the buffer is destroyed, the destructor will block until all
     work in queues on the buffer have completed. If the return type of
     ``std::data(container)`` is not ``const`` then the destructor will
     also copy the contents of the buffer to the container (if required).

If ``set_final_data()`` is used to change where to write the data
back to, then the destructor of the buffer will block if a write
accessor on it has been created.

Sub-buffers
===========

A sub-buffer object can be created, which is a sub-range reference
to a base buffer. This sub-buffer can be used to create accessors
to the base buffer, which have access to the range specified at
time of construction of the sub-buffer. Sub-buffers cannot be
created from sub-buffers, but only from a base buffer which is
not already a sub-buffer.

Sub-buffers must be constructed from a contiguous region of
memory in a buffer. This requirement is potentially non-intuitive
when working with buffers that have dimensionality larger than one,
but maps to one-dimensional SYCL backend native allocations without
performance cost due to index mapping computation.

.. rubric:: Example

See :ref:`sub_buf_example`.

.. _sub_buf_example:

=========
Example 1
=========

An example of creating sub-buffers from a parent buffer:

.. literalinclude:: /examples/creating-sub-buffers.cpp
   :lines: 5-
   :linenos:

Output:

.. literalinclude:: /examples/creating-sub-buffers.out
   :language: none
   :lines: 5-
