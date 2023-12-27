..
  Copyright 2023 The Khronos Group Inc.
  SPDX-License-Identifier: CC-BY-4.0

************************
``sycl::interop_handle``
************************

::

  class interop_handle;

The ``interop_handle`` class is an abstraction over the queue which is being
used to invoke the host task and its associated device and context. It also
represents the state of the SYCL runtime dependency model at the point the
host task is invoked.

The ``interop_handle`` class provides access to the native backend object
associated with the queue, device, context and any buffers or images that
are captured in the callable being invoked in order to allow a host task
to be used for interoperability purposes.

An ``interop_handle`` cannot be constructed by user-code, only by the
SYCL runtime.

(constructors)
==============

.. rubric:: Constructor 1

::

  private:
  interop_handle(__unspecified__);

Private implementation-defined constructor with unspecified arguments
so that the SYCL runtime can construct a ``interop_handle``.

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

  backend get_backend() const noexcept;

Returns: Returns a ``backend`` identifying the SYCL backend associated
with the queue associated with this ``interop_handle``.

======================================
Template member functions get_native_*
======================================

``get_native_mem``
==================

::

  template <backend Backend, typename DataT, int Dims, access_mode AccMode,
                target AccTarget, access::placeholder IsPlaceholder>
      backend_return_t<Backend, buffer<DataT, Dims>>
      get_native_mem(const accessor<DataT, Dims, AccMode, AccTarget,
                                    IsPlaceholder>& bufferAcc) const;

Constraints: Available only if the optional interoperability function
``get_native`` taking a ``buffer`` is available and if ``accTarget``
is ``target::device``.

Returns: The native backend object associated with the underlying
buffer of accessor ``bufferAcc``. The native backend object returned must
be in a state where it represents the memory in its current state within
the SYCL runtime dependency model and is capable of being used in a way
appropriate for the associated SYCL backend. It is undefined behavior to
use the native backend object outside of the scope of the host task.

Throws: An ``exception`` with the ``errc::invalid``
error code if the accessor ``bufferAcc`` was not registered with the
command group which contained the host task. Must throw an ``exception``
with the ``errc::backend_mismatch`` error
code if ``Backend != get_backend()``.

::

  template <backend Backend, typename DataT, int Dims, access_mode AccMode>
  backend_return_t<Backend, unsampled_image<Dims>> get_native_mem( // (2)
      const unsampled_image_accessor<DataT, Dims, AccMode, image_target::device>&
          imageAcc) const;

Constraints: Available only if the optional interoperability function
``get_native`` taking an ``unsampled_image`` is available.

Returns: The native backend object associated with with the underlying
``unsampled_image`` of accessor ``imageAcc``. The native backend object
returned must be in a state where it represents the memory in its current
state within the SYCL runtime dependency model and is capable of being used
in a way appropriate for the associated SYCL backend. It is undefined behavior
to use the native backend object outside of the scope of the host task.

Throws: An ``exception`` with the ``errc::invalid`` error code if the
accessor ``imageAcc`` was not registered with the command group
which contained the host task.

::

  template <backend Backend, typename DataT, int Dims>
  backend_return_t<Backend, sampled_image<Dims>> get_native_mem( // (3)
      const sampled_image_accessor<DataT, Dims, image_target::device>& imageAcc)
      const;

Constraints: Available only if the optional interoperability function
``get_native`` taking an ``sampled_image`` is available.

Returns: The native backend object associated with with the underlying
``sampled_image`` of accessor ``imageAcc``. The native backend object returned
must be in a state where it represents the memory in its current state within
the SYCL runtime dependency model and is capable of being used in a way
appropriate for the associated SYCL backend. It is undefined behavior to
use the native backend object outside of the scope of the host task.

Throws: An ``exception`` with the ``errc::invalid`` error code if the
accessor ``imageAcc`` was not registered with the command group which
contained the host task. Must throw an ``exception`` with the
``errc::backend_mismatch`` error code if
``Backend != get_backend()``.

``get_native_queue``
====================

::

  template <backend Backend>
  backend_return_t<Backend, queue> get_native_queue() const;

Constraints: Available only if the optional interoperability function
``get_native`` taking a ``queue`` is available.

Returns: The native backend object associated with the queue that the host
task was submitted to. If the command group was submitted with a secondary
queue and the fall-back was triggered, the queue that is associated with
the ``interop_handle`` must be the fall-back queue. The native backend
object returned must be in a state where it is capable of being used in
a way appropriate for the associated SYCL backend. It is undefined behavior
to use the native backend object outside of the scope of the host task.

Throws: Must throw an ``exception`` with the
``errc::backend_mismatch`` error code if
``Backend != get_backend()``.

``get_native_device``
=====================

::

  template <backend Backend>
  backend_return_t<Backend, device> get_native_device() const;

Constraints: Available only if the optional interoperability function
``get_native`` taking a ``device`` is available.

Returns: The native backend object associated with the device that is
associated with the queue that the host task was submitted to. The native
backend object returned must be in a state where it is capable of being
used in a way appropriate for the associated SYCL backend. It is undefined
behavior to use the native backend object outside of the scope of the
host task.

Throws: Must throw an ``exception`` with the
``errc::backend_mismatch`` error code if
``Backend != get_backend()``.

``get_native_context``
======================

::

  template <backend Backend>
  backend_return_t<Backend, context> get_native_context() const;

Constraints: Available only if the optional interoperability function
``get_native`` taking a ``context`` is available.

Returns: The native backend object associated with the context that
is associated with the queue that the host task was submitted to. The
native backend object returned must be in a state where it is capable
of being used in a way appropriate for the associated SYCL backend. It
is undefined behavior to use the native backend object outside of the
scope of the host task.

Throws: Must throw an ``exception`` with the
``errc::backend_mismatch`` error code if
``Backend != get_backend()``.
