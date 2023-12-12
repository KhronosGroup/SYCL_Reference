..
  Copyright 2020 The Khronos Group Inc.
  SPDX-License-Identifier: CC-BY-4.0

.. _stream:

****************
``sycl::stream``
****************

::

   class stream;

==============
(constructors)
==============

::

    stream(size_t totalBufferSize, size_t workItemBufferSize, sycl::handler& cgh);


================
Member functions
================

``get_size``
============

::

  size_t get_size() const;


``get_work_item_buffer_size``
=============================

::

   size_t get_work_item_buffer_size() const;

``get_max_statement_size``
==========================

::

   size_t get_max_statement_size() const;

get_max_statement_size() has the same functionality as
get_work_item_buffer_size(), and is provided for backward
compatibility.  get_max_statement_size() is a deprecated query.


``operator<<``
==============

::

   template <typename T>
   const sycl::stream& operator<<(const sycl::stream& os, const T &rhs);


.. _stream-example:

=========
Example 1
=========

Output text to the console in a kernel.

.. literalinclude:: /examples/stream.cpp
   :linenos:
   :start-after: SPDX-License

Output:

.. literalinclude:: /examples/stream.out
   :lines: 5-
