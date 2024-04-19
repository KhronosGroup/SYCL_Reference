..
  Copyright 2024 The Khronos Group Inc.
  SPDX-License-Identifier: CC-BY-4.0

==============
 Header Files
==============

SYCL provides a single standard header file:

::

   #include <sycl/sycl.hpp>

which needs to be included in every translation unit that uses the SYCL
programming API.

For compatibility with the earlier version; SYCL 1.2.1, SYCL also provides
another header file:

::

   #include <CL/sycl.hpp>

which can be used in place of ``sycl/sycl.hpp``, providing all of the same SYCL
programming API, though it is recommended to use ``sycl/sycl.hpp``.

Extension headers are available in ``sycl/ext/`` include paths and backend-
specific headers are available in ``sycl/backend/`` include paths.

.. seealso:: |SYCL_SPEC_HEADER_FILES|
