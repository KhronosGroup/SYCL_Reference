.. _programming-interface:

=====================
Programming Interface
=====================

For further details on SYCL, see the `SYCL
Specification <https://www.khronos.org/registry/SYCL/specs/sycl-1.2.1.pdf>`__.

.. tip::
   
   If you are unfamiliar with C++ templates and lambda functions,
   consult a C++ language references to gain a basic understanding
   before continuing.

Header File
===========

A single header file must be included::

  #include "sycl.hpp"


Namespaces
==========

Unless otherwise noted, all symbols should be prefixed with the
``cl::sycl`` namespace. ``buffer`` is ``cl::sycl::buffer``, and
``info::device::name`` is ``cl::sycl::info::device::name``.


Standard Library Classes
========================


.. _runtime-classes:

Runtime classes
===============

.. toctree::
   :maxdepth: 1

   device-selectors
   platform
   context
   device
   queue
   event
   param_traits

.. _data-access:

Data access
===========

.. toctree::
   :maxdepth: 2

   buffer
   image
   accessors
   address-space
   private_memory
   sampler


.. _expressing-parallelism:

Expressing parallelism
======================

.. toctree::

   range
   group
   id
   item
   h_item
   nd_item
   nd_range
   device-event
   command-group
   command-group-handler
   kernel
   program
   
.. _error-handling:

Error handling
==============

.. toctree::

   exception

Data types
==========

.. toctree::

   scalar-types
   vector-types

Synchronization and atomics
===========================

.. toctree::

   types

Stream class
============

.. toctree::

   stream

Built-in functions
==================

.. toctree::

   math
   integer
   common
   geometric
   relational
   vector
   synchronization
   printf



