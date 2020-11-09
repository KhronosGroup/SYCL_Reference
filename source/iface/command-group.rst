..
  Copyright 2020 The Khronos Group Inc.
  SPDX-License-Identifier: CC-BY-4.0

.. _command_group:

.. rst-class:: api-class

=======================
``sycl::command_group``
=======================
::

   class command_group;

(constructors)
==============

::

  template <typename functorT>
  command_group(sycl::queue &primaryQueue, const functorT &lambda);
  template <typename functorT>
  command_group(sycl::queue &primaryQueue, sycl::queue &secondaryQueue,
                const functorT &lambda);

``start_event``
===============

::

  sycl::event start_event();

``kernel_event``
================

::

  sycl::event kernel_event();

``complete_event``
==================

::

  sycl::event complete_event();
