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
``T``             Type of data in buffer
``Dimensions``    Dimensionality of data: 1, 2, or 3
``AllocatorT``    Allocator for buffer data
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
pointer must point to at least _N_ bytes of memory where _N_ is
``sizeof(T) * bufferRange.size()``.
If _N_ is zero, ``hostData`` is permitted to be a null pointer.

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

``size``
=============

``get_count``
=============

``byte_size``
=============

``get_size``
============

``get_allocator``
=================

.. _buffer-get_access:

``get_access``
==============

::

  template <sycl::access::mode mode, sycl::access::target target = sycl::access::target::global_buffer>
  accessor<T, dimensions, mode, target> get_access(
      sycl::handler &commandGroupHandler);
  template <sycl::access::mode mode>
  accessor<T, dimensions, mode, sycl::access::target::host_buffer> get_access();
  template <sycl::access::mode mode, sycl::access::target target = sycl::access::target::global_buffer>
  accessor<T, dimensions, mode, target> get_access(
      sycl::handler &commandGroupHandler, sycl::range<dimensions> accessRange,
      id<dimensions> accessOffset = {});
  template <sycl::access::mode mode>
  accessor<T, dimensions, mode, sycl::access::target::host_buffer> get_access(
    sycl::range<dimensions> accessRange, sycl::id<dimensions> accessOffset = {});

Returns a accessor to the buffer.

.. rubric:: Template parameters

================  ==========
``mode``          See :ref:`access-mode`
``target``        See :ref:`access-target`
================  ==========

.. rubric:: Parameters

=======================  ==========
``commandGroupHandler``  Command group that uses the accessor
``accessRange``          Dimensions of the sub-buffer that is accessed
``accessOffset``         Origin of the sub-buffer that is accessed
=======================  ==========

``get_host_access``
===================

``set_final_data``
==================

::

  template <typename Destination = std::nullptr_t>
  void set_final_data(Destination finalData = nullptr);

.. rubric:: Template parameters

===================  ==========
``Destination``      ``std::weak_ptr<T>`` or output iterator
===================  ==========

.. rubric:: Parameters

===================  ==========
``finalData``        Indicates where data is copied at destruction time
===================  ==========

Set the final data location. Final data controls the location for
write back when the buffer is destroyed.


``set_write_back``
==================

``is_sub_buffer``
=================

::

  bool is_sub_buffer() const;

Returns True if this is a sub-buffer.


``reinterpret``
===============

::

  template <typename ReinterpretT, int ReinterpretDim>
  buffer<ReinterpretT, ReinterpretDim, AllocatorT>
  reinterpret(range<ReinterpretDim> reinterpretRange) const;

.. rubric:: Template parameters

===================  ==========
``ReinterpretT``     Type of new buffer element
``ReinterpretDim``   Dimensions of new buffer
===================  ==========

.. rubric:: Parameters

====================  ==========
``ReinterpretRange``  Dimensionality of new buffer
====================  ==========

Creates a new buffer with the requested element type and
dimensionality, containing the data of the passed buffer or
sub-buffer.

.. rubric:: Exceptions

``errc::invalid_object_error``
  Size in bytes of new buffer does not match original buffer.

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
