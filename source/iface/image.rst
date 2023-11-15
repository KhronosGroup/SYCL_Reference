..
  Copyright 2020 The Khronos Group Inc.
  SPDX-License-Identifier: CC-BY-4.0

.. _iface-images:

******
Images
******

The classes `unsampled_image`_ and `sampled_image`_ define shared 
image data of one, two or three dimensions, that can be used by 
kernels in queues and have to be accessed using the 
image :ref:`accessor <iface-accessors>` classes.

The allocator template parameter of the `unsampled_image`_ and 
`sampled_image`_ classes can be any allocator type including a 
custom allocator, however it must allocate in units of ``std::byte``.

For any image that is constructed with the range :math:`(r_1,r_2,r_3)`
with an element type size in bytes of :math:`s`, the image row pitch 
and image slice pitch should be calculated as follows:

* Row pitch:  :math:`r_1 \cdot s`
* Image slice pitch: :math:`r_1 \cdot r_2 \cdot s`

The SYCL `unsampled_image`_ and `sampled_image`_ class templates 
provide the :ref:`common-reference`.

.. seealso:: |SYCL_SPEC_IMAGE|


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
--------------

Each constructor of the ``sycl::unsampled_image`` takes an 
`image_format`_ to describe the data layout of the image data.

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

.. rubric:: Constructors 7-10

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

Member functions
================



.. _sampled_image:

=======================
``sycl::sampled_image``
=======================


.. _image_format:

======================
``sycl::image_format``
======================

Class ``sycl::image_format`` is used in the `unsampled_image`_ 
and `sampled_image`_ constructors to describe the data layout 
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

The properties that can be provided when constructing
the ``sycl::unsampled_image`` and ``syc::sampled_image`` classes.

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
=========================================

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

===========================
Image synchronization rules
===========================
