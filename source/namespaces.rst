..
  Copyright 2024 The Khronos Group Inc.
  SPDX-License-Identifier: CC-BY-4.0

==========
Namespaces
==========

All SYCL classes, constants, types and functions are available in the
``sycl::`` namespace, unless the ``CL/sycl.hpp`` header is used in which case
they are all available in the ``cl::sycl::`` namespace.

All SYCL backend-specific functionality is made available in the
namespace ``sycl::<backend_name>`` where ``<backend_name>`` is the
name of the SYCL backend as defined in the SYCL backend specification.

.. seealso:: |SYCL_SPEC_HEADER_FILES|
