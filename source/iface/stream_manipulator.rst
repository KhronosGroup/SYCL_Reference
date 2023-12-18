..
  Copyright 2023 The Khronos Group Inc.
  SPDX-License-Identifier: CC-BY-4.0

.. _iface-stream_manipulators:

*******************
Stream manipulators
*******************

.. seealso::

   |SYCL_SPEC_STREAM_CLASS|

   :ref:`stream`

.. _stream_manipulator:

============================
``sycl::stream_manipulator``
============================

::

  namespace sycl {

  enum class stream_manipulator : /* unspecified */ {
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

   } // namespace sycl

==========================
Stream manipulator aliases
==========================

::

   namespace sycl {

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

   } // namespace sycl

.. list-table::
  :header-rows: 1

  * - Stream manipulator
    - Description
  * - ``sycl::flush``
    - Triggers a flush operation, which synchronizes the
      work-item stream buffer with the global stream buffer,
      and then empties the work-item stream buffer. After a
      flush, the full ``workItemBufferSize`` is available
      again for subsequent streaming within the work-item.
  * - ``sycl::endl``
    - Outputs a new-line character and then triggers a flush operation.
  * - ``sycl::dec``
    - Outputs any subsequent values in the current statement
      in decimal base.
  * - ``sycl::hex``
    - Outputs any subsequent values in the current statement
      in hexadecimal base.
  * - ``sycl::oct``
    - Outputs any subsequent values in the current statement
      in octal base.
  * - ``sycl::noshowbase``
    - Outputs any subsequent values without the base prefix.
  * - ``sycl::showbase``
    - Outputs any subsequent values with the base prefix.
  * - ``sycl::noshowpos``
    - Outputs any subsequent values without a plus sign if
      the value is positive.
  * - ``sycl::showpos``
    - Outputs any subsequent values with a plus sign if
      the value is positive.
  * - ``sycl::setw(int)``
    - Sets the field width of any subsequent values
      in the current statement.
  * - ``sycl::setprecision(int)``
    - Sets the precision of any subsequent values in
      the current statement.
  * - ``sycl::fixed``
    - Outputs any subsequent floating-point values in the
      current statement in fixed notation.
  * - ``sycl::scientific``
    - Outputs any subsequent floating-point values in the
      current statement in scientific notation.
  * - ``sycl::hexfloat``
    - Outputs any subsequent floating-point values in the
      current statement in hexadecimal notation.
  * - ``sycl::defaultfloat``
    - Outputs any subsequent floating-point values in the
      current statement in the default notation.
