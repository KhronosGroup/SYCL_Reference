..
  Copyright 2024 The Khronos Group Inc.
  SPDX-License-Identifier: CC-BY-4.0

.. _iface-images:

******
Images
******

The classes :ref:`unsampled_image` and :ref:`sampled_image` define
shared image data of one, two or three dimensions, that can be used by
kernels in queues and have to be accessed using the
image :ref:`accessor <iface-accessors>` classes.

The allocator template parameter of the :ref:`unsampled_image` and
:ref:`sampled_image` classes can be any allocator type including a
custom allocator, however it must allocate in units of ``std::byte``.

For any image that is constructed with the range :math:`(r_1,r_2,r_3)`
with an element type size in bytes of :math:`s`, the image row pitch
and image slice pitch should be calculated as follows:

* Row pitch:  :math:`r_1 \cdot s`
* Image slice pitch: :math:`r_1 \cdot r_2 \cdot s`

The SYCL :ref:`unsampled_image` and :ref:`sampled_image` class templates
provide the :ref:`common-reference`.

.. seealso:: |SYCL_SPEC_IMAGE|

.. _image_allocator:

==========================
``sycl::image_allocator``
==========================

::

  class image_allocator;

The ``sycl::image_allocator`` class dfefines the default allocator that will be
used by a ``sycl::unsampled_buffer`` or ``sycl::sampled_buffer`` when one is not
provided by the user. The ``sycl::image_allocator`` allocates in elements of
``std::byte``.

.. _unsampled_image:

=========================
``sycl::unsampled_image``
=========================

::

  template <int Dimensions = 1, typename AllocatorT = sycl::image_allocator>
  class unsampled_image;

The ``sycl::unsampled_image`` class template takes a template
parameter ``AllocatorT`` for specifying an allocator which is
used by the SYCL runtime when allocating temporary memory on
the host. If no template argument is provided, the default
allocator for the SYCL ``sycl::unsampled_image`` class
``sycl::image_allocator`` is used (see :ref:`host-allocations`).

(constructors)
==============

Each constructor of the ``sycl::unsampled_image`` takes an
:ref:`image_format` to describe the data layout of the image data.

Each constructor additionally takes as the last parameter an
optional ``sycl::property_list`` to provide properties to the
``sycl::unsampled_image``.

.. rubric:: Constructors 1-2

::

  unsampled_image(sycl::image_format format,
                  const sycl::range<Dimensions>& rangeRef,
                  const sycl::property_list& propList = {});

  unsampled_image(sycl::image_format format,
                  const sycl::range<Dimensions>& rangeRef,
                  AllocatorT allocator,
                  const sycl::property_list& propList = {});

Construct a ``sycl::unsampled_image`` instance with
uninitialized memory.

When provided the constructed ``sycl::unsampled_image`` will use
the ``allocator`` parameter provided when allocating memory
on the host, otherwise it will use a default constructed ``AllocatorT``.

The element size of the constructed ``sycl::unsampled_image``
will be derived from the ``format`` parameter.

The pitch of the constructed ``sycl::unsampled_image`` will
be the default size determined by the SYCL runtime.

Unless the member function ``set_final_data()`` is called
with a valid non-null pointer, there will be no write back
on destruction.

.. rubric:: Constructors 3-4

::

  unsampled_image(sycl::image_format format,
                  const sycl::range<Dimensions>& rangeRef,
                  const sycl::range<Dimensions - 1>& pitch,
                  const sycl::property_list& propList = {});

  unsampled_image(sycl::image_format format,
                  const sycl::range<Dimensions>& rangeRef,
                  const sycl::range<Dimensions - 1>& pitch,
                  AllocatorT allocator,
                  const sycl::property_list& propList = {});

Available only when: ``Dimensions > 1``.

Construct a ``sycl::unsampled_image`` instance with
uninitialized memory.

When provided the constructed ``sycl::unsampled_image`` will use
the ``allocator`` parameter provided when allocating memory
on the host, otherwise it will use a default constructed ``AllocatorT``.

The element size of the constructed ``sycl::unsampled_image``
will be derived from the ``format`` parameter.

Unless the member function ``set_final_data()`` is called
with a valid non-null pointer, there will be no write back
on destruction.

.. rubric:: Constructors 5-6

::

  unsampled_image(void* hostPointer,
                  sycl::image_format format,
                  const sycl::range<Dimensions>& rangeRef,
                  const sycl::property_list& propList = {});

  unsampled_image(void* hostPointer,
                  sycl::image_format format,
                  const sycl::range<Dimensions>& rangeRef,
                  AllocatorT allocator,
                  const sycl::property_list& propList = {});

Construct a ``sycl::unsampled_image`` instance with
the ``hostPointer`` parameter provided.
The ``sycl::unsampled_image`` assumes exclusive access
to this memory for the duration of its lifetime.

When provided the constructed ``sycl::unsampled_image`` will use
the ``allocator`` parameter provided when allocating memory
on the host, otherwise it will use a default constructed ``AllocatorT``.

The element size of the constructed ``sycl::unsampled_image``
will be derived from the ``format`` parameter.

The pitch of the constructed ``sycl::unsampled_image`` will
be the default size determined by the SYCL runtime.

Unless the member function ``set_final_data()`` is called
with a valid non-null pointer, any memory allocated by the
SYCL runtime is written back to ``hostPointer``.

.. rubric:: Constructors 7-8

::

  unsampled_image(void* hostPointer,
                  sycl::image_format format,
                  const sycl::range<Dimensions>& rangeRef,
                  const sycl::range<Dimensions - 1>& pitch,
                  const sycl::property_list& propList = {});

  unsampled_image(void* hostPointer,
                  sycl::image_format format,
                  const sycl::range<Dimensions>& rangeRef,
                  const sycl::range<Dimensions - 1>& pitch,
                  AllocatorT allocator,
                  const sycl::property_list& propList = {});

Available only when: ``Dimensions > 1``.

Construct a ``sycl::unsampled_image`` instance with
the ``hostPointer`` parameter provided.
The ``sycl::unsampled_image`` assumes exclusive access
to this memory for the duration of its lifetime.

When provided the constructed ``sycl::unsampled_image`` will use
the ``allocator`` parameter provided when allocating memory
on the host, otherwise it will use a default constructed ``AllocatorT``.

The element size of the constructed ``sycl::unsampled_image``
will be derived from the ``format`` parameter.

Unless the member function ``set_final_data()`` is called
with a valid non-null pointer, any memory allocated by the
SYCL runtime is written back to ``hostPointer``.

.. rubric:: Constructors 9-10

::

  unsampled_image(std::shared_ptr<void>& hostPointer,
                  sycl::image_format format,
                  const range<Dimensions>& rangeRef,
                  const property_list& propList = {})

  unsampled_image(std::shared_ptr<void>& hostPointer,
                  sycl::image_format format,
                  const sycl::range<Dimensions>& rangeRef,
                  AllocatorT allocator,
                  const sycl::property_list& propList = {})

When ``hostPointer`` is not empty, construct a
``sycl::unsampled_image`` with the contents of its stored pointer.
The ``sycl::unsampled_image`` assumes exclusive
access to this memory for the duration of its lifetime.

The ``sycl::unsampled_image`` also creates its own internal
copy of the ``std::shared_ptr`` that shares ownership of the
``hostData`` memory, which means the application can safely
release ownership of this ``std::shared_ptr`` when the
constructor returns.

When ``hostPointer`` is empty, construct a
``sycl::unsampled_image`` with uninitialized memory.

When provided the constructed ``sycl::unsampled_image`` will use
the ``allocator`` parameter provided when allocating memory
on the host, otherwise it will use a default constructed ``AllocatorT``.

The element size of the constructed ``sycl::unsampled_image``
will be derived from the ``format`` parameter.

The pitch of the constructed ``sycl::unsampled_image`` will
be the default size determined by the SYCL runtime.

Unless the member function ``set_final_data()`` is called
with a valid non-null pointer, any memory allocated by the
SYCL runtime is written back to ``hostPointer``.

.. rubric:: Constructors 11-12

::

  unsampled_image(std::shared_ptr<void>& hostPointer,
                  sycl::image_format format,
                  const sycl::range<Dimensions>& rangeRef,
                  const sycl::range<Dimensions - 1>& pitch,
                  const sycl::property_list& propList = {})

  unsampled_image(std::shared_ptr<void>& hostPointer,
                  sycl::image_format format,
                  const sycl::range<Dimensions>& rangeRef,
                  const sycl::range<Dimensions - 1>& pitch,
                  AllocatorT allocator,
                  const sycl::property_list& propList = {})

When ``hostPointer`` is not empty, construct a
``sycl::unsampled_image`` with the contents of its stored pointer.
The ``sycl::unsampled_image`` assumes exclusive
access to this memory for the duration of its lifetime.

The ``sycl::unsampled_image`` also creates its own internal
copy of the ``std::shared_ptr`` that shares ownership of the
``hostData`` memory, which means the application can safely
release ownership of this ``std::shared_ptr`` when the
constructor returns.

When ``hostPointer`` is empty, construct a
``sycl::unsampled_image`` with uninitialized memory.

When provided the constructed ``sycl::unsampled_image`` will use
the ``allocator`` parameter provided when allocating memory
on the host, otherwise it will use a default constructed ``AllocatorT``.

The element size of the constructed ``sycl::unsampled_image``
will be derived from the ``format`` parameter.

Unless the member function ``set_final_data()`` is called
with a valid non-null pointer, any memory allocated by the
SYCL runtime is written back to ``hostPointer``.

.. rubric:: Parameters

================  ==========
``hostPointer``   Pointer to host memory to hold data.
``format``        :ref:`image_format` that describe layout of the image.
``rangeRef``      The range of the constructed ``sycl::unsampled_image``.
``pitch``         The pitch of the constructed ``sycl::unsampled_image``.
``allocator``     Allocator for the buffer data. In case this parameter
                  is absent, the ``sycl::unsampled_image`` will use a
                  default constructed ``AllocatorT`` when allocating
                  memory on the host.
``propList``      See `Image properties`_.
================  ==========

Member functions
================

``get_range``
-------------

::

  sycl::range<Dimensions> get_range() const;

Return a :ref:`range` object representing the size
of the image in terms of the number of elements in
each dimension as passed to the constructor.

``get_pitch``
-------------

::

  sycl::range<Dimensions - 1> get_pitch() const;

Available only when: ``Dimensions > 1``.

Return a range object representing the pitch of the
image in bytes.

``size``
--------

::

  size_t size() const noexcept;

Returns the total number of elements in the image.

Equal to ``get_range()[0] * ... * get_range()[Dimensions-1]``.

``byte_size``
-------------

::

  size_t byte_size() const noexcept;

Returns the size of the image storage in bytes.

The number of bytes may be greater than ``size()*<element size>``
due to padding of elements, rows and slices of the image for
efficient access.

``get_allocator``
-----------------

::

  AllocatorT get_allocator() const;

Returns the allocator provided to the image.

``get_access``
--------------

::

  template <typename DataT,
            sycl::access_mode Mode = (std::is_const_v<DataT>
                                          ? sycl::access_mode::read
                                          : sycl::access_mode::read_write),
            sycl::image_target Targ = sycl::image_target::device>
  sycl::unsampled_image_accessor<DataT, Dimensions, Mode, Targ>
  get_access(sycl::handler& commandGroupHandler);

Returns a valid :ref:`unsampled_image_accessor` to the unsampled
image with the specified data type, access mode and target
in the command group.

``get_host_access``
-------------------

::

  template <typename DataT,
            sycl::access_mode Mode = (std::is_const_v<DataT>
                                              ? sycl::access_mode::read
                                              : sycl::access_mode::read_write)>
  sycl::host_unsampled_image_accessor<DataT, Dimensions, Mode> get_host_access();

Returns a valid :ref:`host_unsampled_image_accessor` to the unsampled
image with the specified data type and access mode.

``set_final_data``
------------------

::

  template <typename Destination = std::nullptr_t>
  void set_final_data(Destination finalData = nullptr)

The ``finalData`` point to where the output of all the
image processing is going to be copied to at destruction
time, if the image was involved with a write accessor.

Destination can be either an output iterator, or a ``std::weak_ptr<T>``.

.. note::

  A raw pointer is a special case of output iterator
  and thus defines the host memory to which the result
  is to be copied.

In the case of a weak pointer, the output is not
copied if the weak pointer has expired.

If ``Destination`` is ``std::nullptr_t``,
then the copy back will not happen.

``set_write_back``
------------------

::

  void set_write_back(bool flag = true);

This member function allows dynamically forcing
or canceling the write-back of the data of an
image on destruction according to the value of ``flag``.

Forcing the write-back is similar to what happens during
a normal write-back.

If there is nowhere to write-back, using this function
does not have any effect.

.. _sampled_image:

=======================
``sycl::sampled_image``
=======================

::

  template <int Dimensions = 1, typename AllocatorT = sycl::image_allocator>
  class sampled_image;

(constructors)
==============

Each constructor of the ``sycl::sampled_image`` class requires
a pointer to the host data the image will sample, an
:ref:`image_format` to describe the data layout and an
:ref:`image_sampler` to describe how to sample the image data.

Each constructor additionally takes as the last parameter
an optional SYCL property_list to provide properties to
the ``sycl::sampled_image``.

.. rubric:: Constructor 1

::

  sampled_image(const void* hostPointer,
                sycl::image_format format,
                sycl::image_sampler sampler,
                const sycl::range<Dimensions>& rangeRef,
                const sycl::property_list& propList = {});

Construct a ``sycl::sampled_image`` instance with the
``hostPointer`` parameter provided.

The ``sycl::sampled_image`` assumes exclusive access
to this memory for the duration of its lifetime.

The host address is ``const``, so the host accesses
must be read-only. Since, the ``hostPointer`` is ``const``,
this image is only initialized with this memory and
there is no write after its destruction.

The element size of the constructed ``sycl::sampled_image``
will be derived from the ``format`` parameter.

The pitch of the constructed ``sycl::sampled_image`` will
be the default size determined by the SYCL runtime.

.. rubric:: Constructor 2

::

  sampled_image(const void* hostPointer,
                sycl::image_format format,
                sycl::image_sampler sampler,
                const sycl::range<Dimensions>& rangeRef,
                const sycl::range<Dimensions - 1>& pitch,
                const sycl::property_list& propList = {});

Available only when: ``Dimensions > 1``.

Construct a ``sycl::sampled_image`` instance with the
``hostPointer`` parameter provided.

The ``sycl::sampled_image`` assumes exclusive access
to this memory for the duration of its lifetime.

The host address is ``const``, so the host accesses
must be read-only. Since, the ``hostPointer`` is ``const``,
this image is only initialized with this memory and
there is no write after its destruction.

The element size of the constructed ``sycl::sampled_image``
will be derived from the ``format`` parameter.

.. rubric:: Constructor 3

::

  sampled_image(std::shared_ptr<const void>& hostPointer,
                sycl::image_format format,
                sycl::image_sampler sampler,
                const sycl::range<Dimensions>& rangeRef,
                const sycl::property_list& propList = {});

When ``hostPointer`` is not empty, construct a
``sycl::sampled_image`` with the contents of its stored pointer.

The ``sycl::sampled_image`` assumes exclusive access to this
memory for the duration of its lifetime. The ``sycl::sampled_image``
also creates its own internal copy of the ``std::shared_ptr`` that
shares ownership of the ``hostData`` memory, which means the
application can safely release ownership of this ``std::shared_ptr``
when the constructor returns.

When ``hostPointer`` is empty, construct a SYCL
``sycl::sampled_image`` with uninitialized memory.

The host address is ``const``, so the host accesses
must be read-only. Since, the ``hostPointer`` is ``const``,
this image is only initialized with this memory and
there is no write after its destruction.

The element size of the constructed ``sycl::sampled_image``
will be derived from the ``format`` parameter.

The pitch of the constructed ``sycl::sampled_image`` will
be the default size determined by the SYCL runtime.

.. rubric:: Constructor 4

::

  sampled_image(std::shared_ptr<const void>& hostPointer,
                sycl::image_format format,
                sycl::image_sampler sampler,
                const sycl::range<Dimensions>& rangeRef,
                const sycl::range<Dimensions - 1>& pitch,
                const sycl::property_list& propList = {});

Available only when: ``Dimensions > 1``.

When ``hostPointer`` is not empty, construct a
``sycl::sampled_image`` with the contents of its stored pointer.

The ``sycl::sampled_image`` assumes exclusive access to this
memory for the duration of its lifetime. The ``sycl::sampled_image``
also creates its own internal copy of the ``std::shared_ptr`` that
shares ownership of the ``hostData`` memory, which means the
application can safely release ownership of this ``std::shared_ptr``
when the constructor returns.

When ``hostPointer`` is empty, construct a SYCL
``sycl::sampled_image`` with uninitialized memory.

The host address is ``const``, so the host accesses
must be read-only. Since, the ``hostPointer`` is ``const``,
this image is only initialized with this memory and
there is no write after its destruction.

The element size of the constructed ``sycl::sampled_image``
will be derived from the ``format`` parameter.

.. rubric:: Parameters

================  ==========
``hostPointer``   Pointer to host memory to hold data.
``format``        :ref:`image_format` that describe layout of the image.
``sampler``       :ref:`image_sampler` that will be used by the
                  accessors to sample the image.
``rangeRef``      The range of the constructed ``sycl::sampled_image``.
``pitch``         The pitch of the constructed ``sycl::sampled_image``.
``propList``      See `Image properties`_.
================  ==========

Member functions
================

``get_range``
-------------

::

  sycl::range<Dimensions> get_range() const;

Return a :ref:`range` object representing the size
of the image in terms of the number of elements in
each dimension as passed to the constructor.

``get_pitch``
-------------

::

  sycl::range<Dimensions - 1> get_pitch() const;

Available only when: ``Dimensions > 1``.

Return a range object representing the pitch of the
image in bytes.

``size``
--------

::

  size_t size() const noexcept;

Returns the total number of elements in the image.

Equal to ``get_range()[0] * ... * get_range()[Dimensions-1]``.

``byte_size``
-------------

::

  size_t byte_size() const noexcept;

Returns the size of the image storage in bytes.

The number of bytes may be greater than ``size()*<element size>``
due to padding of elements, rows and slices of the image for
efficient access.

``get_access``
--------------

::

  template <typename DataT, sycl::image_target Targ = sycl::image_target::device>
  sycl::sampled_image_accessor<DataT, Dimensions, Targ>
  get_access(sycl::handler& commandGroupHandler);

Returns a valid :ref:`sampled_image_accessor` to the sampled
image with the specified data type and target in the command group.

``get_host_access``
-------------------

::

  template <typename DataT>
  sycl::host_sampled_image_accessor<DataT, Dimensions> get_host_access();

Returns a valid :ref:`host_sampled_image_accessor` to the
sampled image with the specified data type in the command group.


.. _image_format:

======================
``sycl::image_format``
======================

Class ``sycl::image_format`` is used in the :ref:`unsampled_image`
and :ref:`sampled_image` constructors to describe the data layout
of the image data.

::

  namespace sycl {

  enum class image_format : /* unspecified */ {
    r8g8b8a8_unorm,
    r16g16b16a16_unorm,
    r8g8b8a8_sint,
    r16g16b16a16_sint,
    r32b32g32a32_sint,
    r8g8b8a8_uint,
    r16g16b16a16_uint,
    r32b32g32a32_uint,
    r16b16g16a16_sfloat,
    r32g32b32a32_sfloat,
    b8g8r8a8_unorm
  };

  } // namespace sycl

.. note::

  Where relevant, it is the responsibility of the
  user to ensure that the format of the data
  matches the format described by the ``sycl::image_format``.

.. _image-properties:

================
Image properties
================

The properties that can be provided when constructing the
``sycl::unsampled_image`` and ``sycl::sampled_image`` classes
via ``sycl::property_list``.

::

  namespace sycl::property {

  namespace image {

  class use_host_ptr;

  class use_mutex;

  class context_bound;

  } // namespace image

  } // namespace sycl::property



``sycl::property::image::use_host_ptr``
=======================================

::

  namespace sycl::property::image {

  class use_host_ptr {
  public:
    use_host_ptr() = default;
  };

  } // namespace sycl::property::image

The ``sycl::property::image::use_host_ptr`` property adds the
requirement that the SYCL runtime must not allocate any memory
for the image and instead uses the provided host pointer directly.

This prevents the SYCL runtime from allocating additional temporary
storage on the host.


(constructors)
--------------

::

  sycl::property::image::use_host_ptr::use_host_ptr();

Constructs a ``sycl::property::image::use_host_ptr`` property instance.


``sycl::property::image::use_mutex``
====================================

::

  namespace sycl::property::image {

  class use_mutex {
  public:
    use_mutex(std::mutex& mutexRef);

    std::mutex* get_mutex_ptr() const;
  };

  } // namespace sycl::property::image

The property adds the requirement that the memory which is
owned by the SYCL image can be shared with the application
via a ``std::mutex`` provided to the property.

The ``std::mutex`` is locked by the runtime whenever the data
is in use and unlocked otherwise.

Data is synchronized with ``hostData``,
when the ``std::mutex`` is unlocked by the runtime.

(constructors)
--------------

::

  sycl::property::image::use_mutex::use_mutex(std::mutex& mutexRef);

Constructs a ``sycl::property::image::use_mutex`` property instance
with a reference to ``mutexRef`` parameter provided.

``get_mutex_ptr``
-----------------

::

  std::mutex* sycl::property::image::use_mutex::get_mutex_ptr() const;

Returns the ``std::mutex`` which was specified when constructing
this ``sycl::property::image::use_mutex`` property.


``sycl::property::image::context_bound``
========================================

::

  namespace sycl::property::image {

  class context_bound {
  public:
    context_bound(context boundContext);

    context get_context() const;
  };

  } // namespace sycl::property::image


The ``sycl::property::image::context_bound`` property adds the
requirement that the ``sycl::image`` can only be associated
with a single :ref:`context` that is provided to the property.


(constructors)
--------------

::

  sycl::property::image::context_bound(sycl::context boundContext);

Constructs a ``sycl::property::image::context_bound`` property
instance with a copy of a :ref:`context`.

``get_context``
---------------

::

  sycl::context sycl::property::image::context_bound::get_context() const;

Returns the :ref:`context` which was specified when constructing
this ``sycl::property::image::context_bound`` property.

.. _image-synchronization-rules:

===========================
Image synchronization rules
===========================

The rules are similar to those described in
:ref:`buffer-synchronization-rules`.

For the lifetime of the image object, the associated host memory must be
left available to the SYCL runtime and the contents of the associated
host memory is unspecified until the image object is destroyed.
If an image object value is copied, then only a reference to the underlying
image object is copied. The underlying image object is reference-counted.
Only after all image value references to the underlying image object have
been destroyed is the actual image object itself destroyed.

If an image object is constructed with associated host memory, then its
destructor blocks until all operations in all SYCL queues on that image
object have completed.
Any modifications to the image data will be copied back, if necessary,
to the associated host memory.
Any errors occurring during destruction are reported to any
associated context's asynchronous error handler.

If an image object is constructed with a storage object,
then the storage object defines what synchronization or
copying behavior occurs on image object destruction.
