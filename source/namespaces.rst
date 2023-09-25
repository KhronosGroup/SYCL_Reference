..
  Copyright 2020 The Khronos Group Inc.
  SPDX-License-Identifier: CC-BY-4.0

Namespaces
==========

Unless otherwise noted, all SYCL classes, constants, types and functions should be prefixed with the ``sycl::`` namespace. 

For example: ``buffer`` is ``sycl::buffer``, and ``info::device::name`` is ``sycl::info::device::name``.

All SYCL backend-specific functionality is made available in the namespace ``sycl::<backend_name>`` where ``<backend_name>`` is the name of the SYCL
backend as defined in the SYCL backend specification.
