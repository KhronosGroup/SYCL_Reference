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

   runtime/device-selectors
   runtime/platform
   runtime/context
   runtime/device
   runtime/queue
   runtime/event

.. _data-access:

Data access
===========

.. toctree::
   :maxdepth: 2

   data/buffer
   data/image
   data/accessors
   data/address-space
   data/sampler


.. _expressing-parallelism:

Expressing parallelism
======================

.. toctree::

   parallelism/range
   parallelism/command-group
   parallelism/command-group-handler
   parallelism/kernel
   parallelism/program
   
.. _error-handling:

Error handling
==============

.. toctree::

   error/exception

Data types
==========

.. toctree::

   types/scalar
   types/vector

Synchronization and atomics
===========================

.. toctree::

   synchronization/types

Stream class
============

.. toctree::

   stream/stream

Built-in functions
==================

.. toctree::

   built-in/math
   built-in/integer
   built-in/common
   built-in/geometric
   built-in/relational
   built-in/vector
   built-in/synchronization
   built-in/printf



