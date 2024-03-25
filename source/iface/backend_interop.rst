..
  Copyright 2024 The Khronos Group Inc.
  SPDX-License-Identifier: CC-BY-4.0

************************
Backend interoperability
************************

Many of the SYCL runtime classes may be implemented such that they
encapsulate an object unique to the SYCL backend that underpins the
functionality of that class. Where appropriate, these classes may
provide an interface for interoperating between the SYCL runtime
object and the native backend object in order to support
interoperability within an application between SYCL and the
associated SYCL backend API.

There are three forms of interoperability with SYCL runtime classes:
interoperability on the SYCL application with the SYCL backend API,
interoperability within a SYCL kernel function with the equivalent
kernel language types of the SYCL backend, and interoperability
within a host task with the :ref:`interop_handle`.

SYCL application interoperability, SYCL kernel function interoperability
and host task interoperability are provided via different interfaces
and may have different behavior for the same SYCL object.

SYCL application interoperability may be provided for :ref:`buffer`,
:ref:`context`, :ref:`device`, :ref:`device_image`, :ref:`event`,
:ref:`kernel`, :ref:`sycl::kernel_bundle <iface-kernel-bundle>`,
:ref:`platform`, :ref:`queue`, :ref:`sampled_image`, and
:ref:`unsampled_image`.

SYCL kernel function interoperability may be provided for
:ref:`command-accessor`, :ref:`device_event`, :ref:`local_accessor`,
:ref:`sampled_image_accessor`, :ref:`stream` and
:ref:`unsampled_image_accessor` inside kernel scope only and
is not available outside of that scope.

Host task interoperability may be provided for :ref:`command-accessor`,
:ref:`sampled_image_accessor`, :ref:`unsampled_image_accessor`, :ref:`queue`,
:ref:`device`, :ref:`context` inside the scope of a host task only.

.. seealso:: |SYCL_SPEC_BCK_INTEROP|

.. _backend_traits:

``sycl::backend_traits``
========================
::


  namespace sycl {

  template <backend Backend> class backend_traits {
   public:
    template <class T> using input_type = /* see below */;

    template <class T> using return_type = /* see below */;
  };

  template <backend Backend, typename SyclType>
  using backend_input_t =
      typename backend_traits<Backend>::template input_type<SyclType>;

  template <backend Backend, typename SyclType>
  using backend_return_t =
      typename backend_traits<Backend>::template return_type<SyclType>;

  } // namespace sycl

A series of type traits are provided for SYCL backend interoperability,
defined in the ``sycl::backend_traits`` class.

A specialization of ``sycl::backend_traits`` must be provided for each named
SYCL backend enumerated in the enum class ``backend`` that is
available at compile time.

The type alias ``sycl::backend_input_t`` is provided to enable less verbose
access to the ``input_type`` type within ``sycl::backend_traits`` for a
specific SYCL object of type ``T``. The type alias ``sycl::backend_return_t``
is provided to enable less verbose access to the ``return_type`` type within
``sycl::backend_traits`` for a specific SYCL object of type ``T``.

.. seealso:: |SYCL_SPEC_BCK_TRAITS|

.. _get_native:

``sycl::get_native``
====================
::


  namespace sycl {

  template <backend Backend, class T>
  backend_return_t<Backend, T> get_native(const T& syclObject);

  } // namespace sycl

For each SYCL runtime class ``T`` which supports SYCL application
interoperability, a specialization of ``sycl::get_native`` must be defined,
which takes an instance of ``T`` and returns a SYCL application
interoperability native backend object associated with ``syclObject``
which can be used for SYCL application interoperability. The lifetime
of the object returned are backend-defined and specified
in the backend specification.

For each SYCL runtime class ``T`` which supports kernel function
interoperability, a specialization of ``sycl::get_native`` must be defined,
which takes an instance of ``T`` and returns the kernel function
interoperability native backend object associated with ``syclObject``
which can be used for kernel function interoperability. The availability
and behavior of these template functions is defined
by the SYCL backend specification document.

The ``sycl::get_native`` function must throw an ``sycl::exception`` with the
``sycl::errc::backend_mismatch`` error code if the backend of the SYCL
object does not match the target backend.

.. seealso:: |SYCL_SPEC_GET_NATIVE|

``sycl::make_*``
================
::

  namespace sycl {

  template <sycl::backend Backend>
  sycl::platform make_platform(const sycl::backend_input_t<Backend,
                                                           sycl::platform>& backendObject);

  template <sycl::backend Backend>
  sycl::device make_device(const sycl::backend_input_t<Backend,
                                                       sycl::device>& backendObject);

  template <sycl::backend Backend>
  sycl::context make_context(const sycl::backend_input_t<Backend,
                                                   sycl::context>& backendObject,
                             const sycl::async_handler asyncHandler = {});

  template <sycl::backend Backend>
  queue make_queue(const sycl::backend_input_t<Backend,
                                         sycl::queue>& backendObject,
                   const sycl::context& targetContext,
                   const sycl::async_handler asyncHandler = {});

  template <sycl::backend Backend>
  event make_event(const sycl::backend_input_t<Backend,
                                               sycl::event>& backendObject,
                   const sycl::context& targetContext);

  template <sycl::backend Backend, typename T, int Dimensions = 1,
            typename AllocatorT = sycl::buffer_allocator<std::remove_const_t<T>>>
  sycl::buffer<T, Dimensions, AllocatorT>
  make_buffer(const sycl::backend_input_t<Backend,
                                          sycl::buffer<T, Dimensions, AllocatorT>>& backendObject,
              const sycl::context& targetContext,
              sycl::event availableEvent);

  template <sycl::backend Backend, typename T, int Dimensions = 1,
            typename AllocatorT = buffer_allocator<std::remove_const_t<T>>>
  sycl::buffer<T, Dimensions, AllocatorT>
  make_buffer(const sycl::backend_input_t<Backend,
                                          sycl::buffer<T, Dimensions, AllocatorT>>& backendObject,
              const sycl::context& targetContext);

  template <sycl::backend Backend, int Dimensions = 1,
            typename AllocatorT = sycl::image_allocator>
  sycl::sampled_image<Dimensions, AllocatorT> make_sampled_image(
      const sycl::backend_input_t<Backend,
                                  sycl::sampled_image<Dimensions, AllocatorT>>& backendObject,
      const sycl::context& targetContext,
      sycl::image_sampler imageSampler,
      sycl::event availableEvent);

  template <sycl::backend Backend, int Dimensions = 1,
            typename AllocatorT = sycl::image_allocator>
  sycl::sampled_image<Dimensions, AllocatorT> make_sampled_image(
      const sycl::backend_input_t<Backend,
                                  sycl::sampled_image<Dimensions, AllocatorT>>& backendObject,
      const sycl::context& targetContext,
      sycl::image_sampler imageSampler);

  template <sycl::backend Backend, int Dimensions = 1,
            typename AllocatorT = sycl::image_allocator>
  sycl::unsampled_image<Dimensions, AllocatorT> make_unsampled_image(
      const sycl::backend_input_t<Backend,
                                  sycl::unsampled_image<Dimensions, AllocatorT>>& backendObject,
      const sycl::context& targetContext,
      sycl::event availableEvent);

  template <sycl::backend Backend, int Dimensions = 1,
            typename AllocatorT = sycl::image_allocator>
  sycl::unsampled_image<Dimensions, AllocatorT> make_unsampled_image(
      const sycl::backend_input_t<Backend,
                                  sycl::unsampled_image<Dimensions, AllocatorT>>& backendObject,
      const sycl::context& targetContext);

  template <sycl::backend Backend, sycl::bundle_state State>
  sycl::kernel_bundle<State> make_kernel_bundle(
      const sycl::backend_input_t<Backend,
                                  sycl::kernel_bundle<State>>& backendObject,
      const sycl::context& targetContext);

  template <sycl::backend Backend>
  sycl::kernel make_kernel(const sycl::backend_input_t<Backend,
                                                       sycl::kernel>& backendObject,
                           const sycl::context& targetContext);

  } // namespace sycl

For each SYCL runtime class ``T`` which supports SYCL application
interoperability, a specialization of the appropriate template function
``sycl::make_{sycl_class}`` where ``{sycl_class}`` is the class name of
``T``, must be defined, which takes a SYCL application interoperability
`native backend object` and constructs and returns an instance of
``T``. The availability and behavior of these template functions
is defined by the SYCL backend specification document.

Overloads of the ``sycl::make_{sycl_class}`` function which take a SYCL
``sycl::context`` object as an argument must throw an ``sycl::exception``
with the ``sycl::errc::backend_mismatch`` error code if the backend of
the provided SYCL context does not match the target backend.
