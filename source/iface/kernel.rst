..
  Copyright 2020 The Khronos Group Inc.
  SPDX-License-Identifier: CC-BY-4.0

.. _kernel:

****************
``sycl::kernel``
****************

::

  class kernel;

Abstraction of a kernel object.

The ``sycl::kernel`` class template provides the :ref:`common-reference`.

There is no public default constructor for this class.

.. seealso:: |SYCL_SPEC_KERNEL|

==============
Kernel queries
==============

The following member functions provide various queries for a kernel.

``get_backend``
===============

::

  sycl::backend get_backend() const noexcept;

Returns the ``sycl::backend`` associated with this kernel.


``get_context``
===============

::

  sycl::context get_context() const;

Returns the :ref:`context` associated with this kernel.


``get_kernel_bundle``
=====================

::

  sycl::kernel_bundle<sycl::bundle_state::executable> get_kernel_bundle() const;


Returns the :ref:`kernel bundle <iface-kernel-bundle>`
that contains this kernel.


``get_info``
============

Overload 1
----------

::

   template <typename Param>
   typename Param::return_type get_info() const;

The ``Param`` must be one of the `sycl::info::kernel`_ descriptors,
and the type alias ``Param::return_type`` must be defined in
accordance with its requirements.

Returns the information about the kernel that is
not specific to the device on which it is invoked.

.. rubric:: Template parameters

==================  ===
``Param``           See `sycl::info::kernel`_.
==================  ===

Overload 2
----------

::

  template <typename Param>
  typename Param::return_type get_info(const sycl::device& dev) const;


The ``Param`` must be one of the `sycl::info::kernel_device_specific`_
descriptors, and the type alias ``Param::return_type`` must be defined
in accordance with its requirements.

Returns the information about the kernel that applies
when the kernel is invoked on the :ref:`device` ``dev``.

.. rubric:: Template parameters

==================  ===
``Param``           See `sycl::info::kernel_device_specific`_.
==================  ===

.. rubric:: Exceptions

``errc::invalid``
   If the kernel is not compatible with device ``dev``
   (as defined by ``sycl::is_compatible()``).


``get_backend_info``
====================

::

   template <typename Param>
   typename Param::return_type get_backend_info() const;

The ``Param`` must be one of descriptors
defined by a SYCL backend specification.

Returns the backend specific information about
the kernel that is not specific to the device
on which it is invoked.

.. rubric:: Template parameters

==================  ===
``Param``           A descriptor defined by a SYCL
                    backend specification.
==================  ===

.. rubric:: Exceptions

``errc::backend_mismatch``
   If the SYCL backend that corresponds with
   ``Param`` is different from the SYCL backend
   that is associated with this kernel bundle.


======================
``sycl::info::kernel``
======================

::

  namespace sycl::info {

  namespace kernel {

  struct num_args;
  struct attributes;

  } // namespace kernel

  } // namespace sycl::info

A ``sycl::kernel`` can be queried for information using the
``get_info()`` member function, specifying one of the info
parameters in ``sycl::info::kernel``.

.. rubric:: ``sycl::info::kernel::num_args``

This descriptor may only be used to query a kernel that resides
in a :ref:`kernel bundle <iface-kernel-bundle>` that was
constructed using a backend specific interoperability
function or to query a device built-in kernel, and the semantics
of this descriptor are defined by each SYCL backend specification.

Attempting to use this descriptor for other kernels throws an
``exception`` with the ``errc::invalid`` error code.

+-----------------------------+
| Return type: ``uint32_t``   |
+-----------------------------+


.. rubric:: ``sycl::info::kernel::attributes``

Return any attributes specified on a kernel function
(as defined in the |SYCL_SPEC_DEVICE_CODE_ATTR|).

+------------------------------+
| Return type: ``std::string`` |
+------------------------------+

======================================
``sycl::info::kernel_device_specific``
======================================

::

  namespace sycl::info {

  namespace kernel_device_specific {

  struct global_work_size;
  struct work_group_size;
  struct compile_work_group_size;
  struct preferred_work_group_size_multiple;
  struct private_mem_size;
  struct max_num_sub_groups;
  struct compile_num_sub_groups;
  struct max_sub_group_size;
  struct compile_sub_group_size;

  } // namespace kernel_device_specific

  } // namespace sycl::info

A ``sycl::kernel`` can also be queried for device specific
information using the ``get_info()`` member function,
specifying one of the info parameters in
``sycl::info::kernel_device_specific``.

.. rubric:: ``sycl::info::kernel_device_specific::global_work_size``

This descriptor may only be used if the device type is
``sycl::device_type::custom`` or if the kernel is a
built-in kernel.

The exact semantics of this descriptor are defined by
each SYCL backend specification, but the intent is to
return the kernel's maximum global work size.

Attempting to use this descriptor for other devices or
kernels throws an ``exception`` with the ``errc::invalid``
error code.

+----------------------------------------------+
| Return type: :ref:`sycl::range\<3\> <range>` |
+----------------------------------------------+


.. rubric:: ``sycl::info::kernel_device_specific::work_group_size``

Returns the maximum number of work-items in a
work-group that can be used to execute a kernel
on a specific device.

+-------------------------+
| Return type: ``size_t`` |
+-------------------------+


.. rubric:: ``sycl::info::kernel_device_specific::compile_work_group_size``

Returns the work-group size specified by the device
compiler if applicable, otherwise returns ``{0,0,0}``.

+----------------------------------------------+
| Return type: :ref:`sycl::range\<3\> <range>` |
+----------------------------------------------+


.. rubric:: ``sycl::info::kernel_device_specific::preferred_work_group_size_multiple``

Returns a value, of which work-group size is preferred
to be a multiple, for executing a kernel on a particular
device. This is a performance hint.

The value must be less than or equal to that returned by
``sycl::info::kernel_device_specific::work_group_size``.

+-------------------------+
| Return type: ``size_t`` |
+-------------------------+


.. rubric:: ``sycl::info::kernel_device_specific::private_mem_size``

Returns the minimum amount of private memory, in bytes,
used by each work-item in the kernel.

This value may include any private memory needed by an
implementation to execute the kernel, including that
used by the language built-ins and variables declared
inside the kernel in the private address space.

+-------------------------+
| Return type: ``size_t`` |
+-------------------------+


.. rubric:: ``sycl::info::kernel_device_specific::max_num_sub_groups``

Returns the maximum number of sub-groups for this kernel.

+---------------------------+
| Return type: ``uint32_t`` |
+---------------------------+


.. rubric:: ``sycl::info::kernel_device_specific::compile_num_sub_groups``

Returns the number of sub-groups specified by the
kernel, or 0 (if not specified).

+---------------------------+
| Return type: ``uint32_t`` |
+---------------------------+


.. rubric:: ``sycl::info::kernel_device_specific::max_sub_group_size``

Returns the maximum sub-group size for this kernel.

+---------------------------+
| Return type: ``uint32_t`` |
+---------------------------+


.. rubric:: ``sycl::info::kernel_device_specific::compile_sub_group_size``

Returns the required sub-group size specified
by the kernel, or 0 (if not specified).

+---------------------------+
| Return type: ``uint32_t`` |
+---------------------------+
