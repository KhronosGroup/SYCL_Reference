=========
Interface
=========

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
``sycl`` namespace. ``buffer`` is ``sycl::buffer``, and
``info::device::name`` is ``sycl::info::device::name``.


Standard Library Classes
========================


.. _common-interface:


Common Interface
================

In this section, we define methods that are common to multiple classes.

.. toctree::

   common-byval
   common-reference
   properties
   param_traits
   
.. _runtime-classes:

Runtime Classes
===============

.. toctree::
     
   device-selector
   platform
   context
   device
   queue
   event

.. _data-access:

Data access
===========

.. toctree::

   buffer
   image
   accessors
   address-space
   private_memory
   sampler


Unified shared memory (USM)
===========================

.. toctree::

   usm-malloc
   usm_allocator
   usm

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

IO
==

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



