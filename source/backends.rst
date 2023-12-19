..
  Copyright 2023 The Khronos Group Inc.
  SPDX-License-Identifier: CC-BY-4.0

********
Backends
********

The SYCL backends that can be supported by a SYCL implementation
are identified using the ``enum class backend``.

=================
``sycl::backend``
=================

::

  class backend;

The ``enum class backend`` is implementation-defined and must be
populated with a unique identifier for each SYCL backend that the
SYCL implementation can support. Note that the SYCL backends listed
in the ``enum class backend`` are not guaranteed to be available
in a given installation.

Each named SYCL backend enumerated in the ``enum class backend``
must be associated with a SYCL backend specification. Many sections
of this specification will refer to the associated SYCL
backend specification.

==============
Backend macros
==============

As the identifiers defined in ``enum class backend`` are
implementation-defined, and the associated backends not
guaranteed to be available, a SYCL implementation must also
define a preprocessor macro for each of these identifiers.
If the SYCL backend is defined by the Khronos SYCL group, the
name of the macro has the form ``SYCL_BACKEND_<backend_name>``,
where backend_name is the associated identifier from ``backend``
in all upper-case.

For the name of the macro if the vendor defines the SYCL backend
outside of the Khronos SYCL group

.. seealso:: |SYCL_SPEC_EXTENSIONS|

If a backend listed in the ``enum class backend`` is not available,
the associated macro must be left undefined.
