..
  Copyright 2020 The Khronos Group Inc.
  SPDX-License-Identifier: CC-BY-4.0

*******
Streams
*******


Kernels may not use std streams for input/output. ``sycl::stream`` provides similar functionality.

.. _stream-example:

.. rubric:: Example

Output to stdout in a kernel.

.. literalinclude:: /examples/stream.cpp
   :linenos:		    
   :start-after: SPDX-License

.. rst-class:: api-class
	       
==============
 sycl::stream
==============

::

   class stream;


(constructors)
==============

::
   
    stream(size_t totalBufferSize, size_t workItemBufferSize, sycl::handler& cgh);


get_size
========

::
   
  size_t get_size() const;


get_work_item_buffer_size
=========================

::

   size_t get_work_item_buffer_size() const;

get_max_statement_size
======================

::
   
   size_t get_max_statement_size() const;

get_max_statement_size() has the same functionality as
get_work_item_buffer_size(), and is provided for backward
compatibility.  get_max_statement_size() is a deprecated query.


operator<<
==========

::
   
   template <typename T>
   const sycl::stream& operator<<(const sycl::stream& os, const T &rhs);


========================
sycl::stream_manipulator
========================

::

   enum class stream_manipulator {
       flush,
       dec,
       hex,
       oct,
       noshowbase,
       showbase,
       noshowpos,
       showpos,
       endl,
       fixed,
       scientific,
       hexfloat,
       defaultfloat
    };


=====================
 Stream manipulators
=====================

::
   
   const sycl::stream_manipulator flush = sycl::stream_manipulator::flush;
   const sycl::stream_manipulator dec = sycl::stream_manipulator::dec;
   const sycl::stream_manipulator hex = sycl::stream_manipulator::hex;
   const sycl::stream_manipulator oct = sycl::stream_manipulator::oct;
   const sycl::stream_manipulator noshowbase = sycl::stream_manipulator::noshowbase;
   const sycl::stream_manipulator showbase = sycl::stream_manipulator::showbase;
   const sycl::stream_manipulator noshowpos = sycl::stream_manipulator::noshowpos;
   const sycl::stream_manipulator showpos = sycl::stream_manipulator::showpos;
   const sycl::stream_manipulator endl = sycl::stream_manipulator::endl;
   const sycl::stream_manipulator fixed = sycl::stream_manipulator::fixed;
   const sycl::stream_manipulator scientific = sycl::stream_manipulator::scientific;
   const sycl::stream_manipulator hexfloat = sycl::stream_manipulator::hexfloat;
   const sycl::stream_manipulator defaultfloat = sycl::stream_manipulator::defaultfloat;
   __precision_manipulator__ setprecision(int precision);
   __width_manipulator__ setw(int width);
