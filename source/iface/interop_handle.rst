..
  Copyright 2023 The Khronos Group Inc.
  SPDX-License-Identifier: CC-BY-4.0

.. _interop_handle:

************************
``sycl::interop_handle``
************************

::

  class interop_handle;

The ``sycl::interop_handle`` class is an abstraction over the
:ref:`queue` which is being used to invoke the :ref:`host_task-basic`
and its associated :ref:`device` and :ref:`context`. It also represents
the state of the SYCL runtime dependency model at the point the host
task is invoked.

The ``sycl::interop_handle`` class provides access to the native
backend object associated with the :ref:`queue`, :ref:`device`,
:ref:`context` and any buffers or images that are captured in
the callable being invoked in order to allow a host task to
be used for interoperability purposes.

An ``sycl::interop_handle`` cannot be constructed by user-code,
only by the SYCL runtime.

(constructors)
==============

.. rubric:: Constructor 1

::

  private:
  interop_handle(__unspecified__);

Private implementation-defined constructor with unspecified arguments
so that the SYCL runtime can construct a ``sycl::interop_handle``.

.. rubric:: Constructor 2

::

  public:
  interop_handle() = delete;

Explicitly deleted default constructor.

================
Member functions
================

``get_backend``
===============

::

  sycl::backend get_backend() const noexcept;

Returns: Returns a ``sycl::backend`` identifying the SYCL
backend associated with the :ref:`queue` associated with
this ``sycl::interop_handle``.

======================================
Template member functions get_native_*
======================================

``get_native_mem``
==================

::

  template <sycl::backend Backend, typename DataT, int Dims, sycl::access_mode AccMode,
                sycl::target AccTarget, sycl::access::placeholder IsPlaceholder>
      sycl::backend_return_t<Backend, sycl::buffer<DataT, Dims>>
      get_native_mem(const sycl::accessor<DataT, Dims, AccMode, AccTarget,
                                    IsPlaceholder>& bufferAcc) const;

Constraints: Available only if the optional interoperability function
``sycl::get_native`` taking a ``sycl:buffer`` is available and
if ``sycl::accTarget`` is ``sycl::target::device``.

Returns: The native backend object associated with the underlying
:ref:`buffer` of accessor ``sycl::bufferAcc``. The native backend object
returned must be in a state where it represents the memory in its
current state within the SYCL runtime dependency model and is capable of
being used in a way appropriate for the associated SYCL backend.
It is undefined behavior to use the native backend object outside of
the scope of the host task.

Throws: An ``sycl::exception`` with the ``sycl::errc::invalid``
error code if the accessor ``sycl::bufferAcc`` was not
registered with the command group which contained the host task.
Must throw an ``sycl::exception`` with the
``sycl::errc::backend_mismatch`` error code if
``Backend != sycl::get_backend()``.

::

  template <sycl::backend Backend, typename DataT, int Dims, sycl::access_mode AccMode>
  sycl::backend_return_t<Backend, sycl::unsampled_image<Dims>> get_native_mem( // (2)
      const unsampled_image_accessor<DataT, Dims, AccMode, sycl::image_target::device>&
          imageAcc) const;

Constraints: Available only if the optional interoperability function
``sycl::get_native`` taking an ``sycl::unsampled_image`` is available.

Returns: The native backend object associated with with the underlying
``sycl::unsampled_image`` of accessor ``sycl::imageAcc``.
The native backend object returned must be in a state where it represents
the memory in its current state within the SYCL runtime dependency model
and is capable of being used in a way appropriate for the associated SYCL
backend. It is undefined behavior to use the native backend object outside
of the scope of the host task.

Throws: An ``sycl::exception`` with the ``sycl::errc::invalid``
error code if the accessor ``sycl::imageAcc`` was not registered with
the command group which contained the host task.

::

  template <sycl::backend Backend, typename DataT, int Dims>
  sycl::backend_return_t<Backend, sycl::sampled_image<Dims>> get_native_mem( // (3)
      const sampled_image_accessor<DataT, Dims, sycl::image_target::device>& imageAcc)
      const;

Constraints: Available only if the optional interoperability function
``sycl::get_native`` taking an ``sycl::sampled_image`` is available.

Returns: The native backend object associated with with the underlying
``sycl::sampled_image`` of accessor ``sycl::imageAcc``.
The native backend object returned must be in a state where it
represents the memory in its current state within the SYCL runtime
dependency model and is capable of being used in a way appropriate for
the associated SYCL backend. It is undefined behavior to use the native
backend object outside of the scope of the host task.

Throws: An ``sycl::exception`` with the ``sycl::errc::invalid`` error
code if the accessor ``sycl::imageAcc`` was not registered with the
command group which contained the host task. Must throw an
``sycl::exception`` with the ``errc::backend_mismatch``
error code if ``Backend != sycl::get_backend()``.

``get_native_queue``
====================

::

  template <sycl::backend Backend>
  sycl::backend_return_t<Backend, sycl::queue> get_native_queue() const;

Constraints: Available only if the optional interoperability function
``get_native`` taking a :ref:`queue` is available.

Returns: The native backend object associated with the :ref:`queue` that
the host task was submitted to. If the command group was submitted with
a secondary :ref:`queue` and the fall-back was triggered,the :ref:`queue`
that is associated with the ``sycl::interop_handle`` must be the
fall-back :ref:`queue`. The native backend object returned must be in
a state where it is capable of being used in a way appropriate for the
associated SYCL backend. It is undefined behavior to use the native backend
object outside of the scope of the host task.

Throws: Must throw an ``sycl::exception`` with the
``sycl::errc::backend_mismatch`` error code if
``Backend != sycl::get_backend()``.

``get_native_device``
=====================

::

  template <sycl::backend Backend>
  sycl::backend_return_t<Backend, sycl::device> get_native_device() const;

Constraints: Available only if the optional interoperability function
``sycl::get_native`` taking a ``sycl::device`` is available.

Returns: The native backend object associated with the device that is
associated with the :ref:`queue` that the host task was submitted to.
The native backend object returned must be in a state where it is
capable of being used in a way appropriate for the associated SYCL backend.
It is undefined behavior to use the native backend object outside
of the scope of the host task.

Throws: Must throw an ``sycl::exception`` with the
``sycl::errc::backend_mismatch`` error code if
``Backend != sycl::get_backend()``.

``get_native_context``
======================

::

  template <sycl::backend Backend>
  sycl::backend_return_t<Backend, sycl::context> get_native_context() const;

Constraints: Available only if the optional interoperability function
``sycl::get_native`` taking a ``sycl::context`` is available.

Returns: The native backend object associated with the context that
is associated with the :ref:`queue` that the host task was submitted to. The
native backend object returned must be in a state where it is capable
of being used in a way appropriate for the associated SYCL backend. It
is undefined behavior to use the native backend object outside of the
scope of the host task.

Throws: Must throw an ``sycl::exception`` with the
``sycl::errc::backend_mismatch`` error code if
``Backend != sycl::get_backend()``.
