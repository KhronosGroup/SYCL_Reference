..
  Copyright 2020 The Khronos Group Inc.
  SPDX-License-Identifier: CC-BY-4.0

.. _device_event:

**********************
``sycl::device_event``
**********************

::

  namespace sycl {

  class device_event {
    device_event(__unspecified__);

   public:
    void wait() noexcept;
  };

  } // namespace sycl

The ``sycl::device_event`` class encapsulates a single SYCL
device event which is available only within SYCL kernel
functions and can be used to wait for asynchronous operations
within a SYCL kernel function to complete.

All member functions of the ``sycl::device_event`` class must
not throw a ``sycl::exception``.

.. seealso:: |SYCL_SPEC_DEVICE_EVENT|

==============
(constructors)
==============

::

  device_event(___unspecified___);

Unspecified implementation-defined constructor.

================
Member functions
================

``wait``
========

::

   void wait() noexcept;

Waits for the asynchronous operation associated with this
``sycl::device_event`` to complete.
