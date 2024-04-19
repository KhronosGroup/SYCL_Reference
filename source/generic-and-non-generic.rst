..
  Copyright 2024 The Khronos Group Inc.
  SPDX-License-Identifier: CC-BY-4.0

***************************
Generic vs non-generic SYCL
***************************

The SYCL programming API is split into two categories; generic SYCL and
non-generic SYCL. Almost everything in the SYCL programming API is considered
generic SYCL. However any usage of the ``enum class backend`` is considered
non-generic SYCL and should only be used for SYCL backend specialized code
paths, as the identifiers defined in ``backend`` are implementation-defined.

To ensure portability of SYCL applications any non-generic SYCL application
code where the ``backend`` enum class is used, the expression must be guarded
with a preprocessor ``#ifdef`` guard using the associated preprocessor macro to
ensure that the SYCL application will compile even if the SYCL implementation
does not support that SYCL backend being specialized for.
