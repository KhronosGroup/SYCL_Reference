..
  Copyright 2024 The Khronos Group Inc.
  SPDX-License-Identifier: CC-BY-4.0

.. _stream:

****************
``sycl::stream``
****************

::

  class stream;

The ``sycl::stream`` class is a buffered output stream
that allows outputting the values of built-in, vector
and SYCL types to the console. The implementation of
how values are streamed to the console is left as an
implementation detail.

The way in which values are output by an instance of
the ``sycl::stream`` class can also be altered using
a range of manipulators.

There are two limits that are relevant for the
``sycl::stream`` class. The ``totalBufferSize`` limit
specifies the maximum size of the overall character
stream that can be output during a kernel invocation, and
the ``workItemBufferSize`` limit specifies the maximum
size of the character stream that can be output within a
work-item before a flush must be performed. Both of these
limits are specified in bytes. The ``totalBufferSize`` limit
must be sufficient to contain the characters output by all
stream statements during execution of a kernel invocation
(the aggregate of outputs from all work-items), and the
``workItemBufferSize`` limit must be sufficient to contain
the characters output within a work-item between stream
flush operations.

If the ``totalBufferSize`` or ``workItemBufferSize`` limits
are exceeded, it is implementation-defined whether the streamed
characters exceeding the limit are output, or silently
ignored/discarded, and if output it is implementation-defined
whether those extra characters exceeding the ``workItemBufferSize``
limit count toward the ``totalBufferSize`` limit. Regardless of
this implementation defined behavior of output exceeding the
limits, no undefined or erroneous behavior is permitted of an
implementation when the limits are exceeded. Unused characters
within ``workItemBufferSize`` (any portion of the
``workItemBufferSize`` capacity that has not been used at the
time of a stream flush) do not count toward the ``totalBufferSize``
limit, in that only characters flushed count toward the
``totalBufferSize`` limit.

The ``sycl::stream`` class provides the :ref:`common-reference`.

.. seealso:: |SYCL_SPEC_STREAM_CLASS|

==============
(constructors)
==============

::

  stream(size_t totalBufferSize, size_t workItemBufferSize,
         sycl::handler& cgh, const sycl::property_list& propList = {});

Constructs a ``sycl::stream`` instance associated with the
command group specified by ``cgh``, with a maximum buffer
size in bytes per kernel invocation specified by the
parameter ``totalBufferSize``, and a maximum stream size
that can be buffered by a work-item between stream flushes
specified by the parameter ``workItemBufferSize``.

Zero or more properties can be provided to the constructed
``sycl::stream`` via an instance of ``sycl::property_list``.


================
Member functions
================

``size``
========

::

  size_t size() const noexcept;

Returns the total buffer size, in bytes.

``get_size``
============

::

  size_t get_size() const;

Deprecated in SYCL 2020.

Returns the same value as ``size()``.


``get_work_item_buffer_size``
=============================

::

   size_t get_work_item_buffer_size() const;

Returns the buffer size per work-item, in bytes.

``get_max_statement_size``
==========================

::

   size_t get_max_statement_size() const;

Deprecated in SYCL 2020.

Query with same functionality as ``get_work_item_buffer_size()``.


================
Global functions
================

``operator<<``
==============

::

   template <typename T>
   const sycl::stream& operator<<(const sycl::stream& os, const T& rhs);

Outputs any valid values (see :ref:`stream-operands`) as a
stream of characters and applies any valid manipulator
(see :ref:`stream_manipulator`) to the current stream.


.. _stream-operands:

==================
Supported operands
==================

.. list-table::
  :header-rows: 1

  * - Stream operand type
    - Description
  * - ``char``, ``signed char``, ``unsigned char``, ``int``,
      ``unsigned int``, ``short``, ``unsigned short``, ``long int``,
      ``unsigned long int``, ``long long int``, ``unsigned long long int``
    - Outputs the value as a stream of characters.
  * - ``float``, ``double``, ``half``
    - Outputs the value according to the precision of the
      current statement as a stream of characters.
  * - ``char*``, ``const char*``
    - Outputs the string.
  * - ``T*``, ``const T*``, ``sycl::multi_ptr``
    - Outputs the address of the pointer as a stream of characters.
  * - ``sycl::vec``
    - Outputs the value of each component of the
      vector as a stream of characters.
  * - ``sycl::id``, ``sycl::range``, ``sycl::item``,
      ``sycl::nd_item``, ``sycl::group``,
      ``sycl::nd_range``, ``sycl::h_item``
    - Outputs the value of each component of each
      id or range as a stream of characters.


===============
Synchronization
===============

An instance of the ``sycl::stream`` class is required to
synchronize with the host, and must output everything
that is streamed to it via the ``operator<<()`` operator
before a flush operation (that doesn't exceed the
``workItemBufferSize`` or ``totalBufferSize`` limits) within
a SYCL kernel function by the time that the event associated
with a command group submission enters the completed state.

The point at which this synchronization occurs and the member
function by which this synchronization is performed are
implementation-defined. For example it is valid for an
implementation to use ``printf()``.

The ``sycl::stream`` class is required to output the content
of each stream, between flushes (up to ``workItemBufferSize``),
without mixing with content from the same stream in other
work-items. There are no other output order guarantees between
work-items or between streams. The stream flush operation
therefore delimits the unit of output that is guaranteed to
be displayed without mixing with other work-items, with
respect to a single stream.

==============
Implicit flush
==============

There is guaranteed to be an implicit flush of each stream
used by a kernel, at the end of kernel execution, from the
perspective of each work-item. There is also an implicit
flush when the ``sycl::endl`` stream manipulator is executed.
No other implicit flushes are permitted in an implementation.

================
Performance note
================

The usage of the ``sycl::stream`` class is designed for
debugging purposes and is therefore not recommended for
performance critical applications.


.. _stream-example:

=========
Example 1
=========

Output text to the console in a kernel.

.. literalinclude:: /examples/stream.cpp
   :lines: 5-
   :linenos:

Output:

.. literalinclude:: /examples/stream.out
   :language: none
   :lines: 5-
