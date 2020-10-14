..
  Copyright 2020 The Khronos Group Inc.
  SPDX-License-Identifier: CC-BY-4.0

**************
Command groups
**************

.. _command_group-function-object:

===============================
 Command group function object
===============================

.. todo:: Explain
	  
.. _command_group:

.. rst-class:: api-class

===================
sycl::command_group
===================

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

events
======

::
   
  sycl::event start_event();
  sycl::event kernel_event();
  sycl::event complete_event();

