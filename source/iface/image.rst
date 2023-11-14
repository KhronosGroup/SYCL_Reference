..
  Copyright 2020 The Khronos Group Inc.
  SPDX-License-Identifier: CC-BY-4.0

.. _iface-images:

******
Images
******


.. seealso:: |SYCL_SPEC_IMAGE|

.. _unsampled_image:

=========================
``sycl::unsampled_image``
=========================


.. _sampled_image:

=======================
``sycl::sampled_image``
=======================


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
