..
  Copyright 2020 The Khronos Group Inc.
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
within a host task with the ``interop_handle``.

SYCL application interoperability, SYCL kernel function interoperability
and host task interoperability are provided via different interfaces
and may have different behavior for the same SYCL object.

SYCL application interoperability may be provided for ``buffer``, ``context``,
``device``, ``device_image``, ``event``,`` kernel``, ``kernel_bundle``,
``platform``, ``queue``, ``sampled_image``, and ``unsampled_image``.

SYCL kernel function interoperability may be provided for ``accessor``,
``device_event``, ``local_accessor``, ``sampled_image_accessor``, ``tream``
and ``unsampled_image_accessor`` inside kernel scope only and
is not available outside of that scope.

host task interoperability may be provided for ``accessor``,
``sampled_image_accessor``, ``unsampled_image_accessor``, ``queue``,
``device``, ``context`` inside the scope of a host task only.

.. seealso:: |SYCL_SPEC_HOST_TASK|



.. backend_traits`:

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
defined in the ``backend_traits`` class.

A specialization of ``backend_traits`` must be provided for each named
SYCL backend enumerated in the enum class ``backend`` that is
available at compile time.

The type alias ``backend_input_t`` is provided to enable less verbose access
to the ``input_type`` type within ``backend_traits`` for a specific SYCL
object of type ``T``. The type alias ``backend_return_t`` is provided to
enable less verbose access to the ``return_type`` type within
``backend_traits`` for a specific SYCL object of type ``T``.

.. seealso:: |SYCL_SPEC_BCK_TRAITS|

.. get_native`:

``sycl::get_native``
====================
::


  namespace sycl {

  template <backend Backend, class T>
  backend_return_t<Backend, T> get_native(const T& syclObject);

  } // namespace sycl

The ``get_native`` function must throw an ``exception`` with the
``errc::backend_mismatch`` error code if the backend of the SYCL
object does not match the target backend.

.. seealso:: |SYCL_SPEC_GET_NATIVE|

.. make_*`:

``sycl::make_*``
================
::


  namespace sycl {

  template <backend Backend>
  platform make_platform(const backend_input_t<Backend, platform>& backendObject);

  template <backend Backend>
  device make_device(const backend_input_t<Backend, device>& backendObject);

  template <backend Backend>
  context make_context(const backend_input_t<Backend, context>& backendObject,
                       const async_handler asyncHandler = {});

  template <backend Backend>
  queue make_queue(const backend_input_t<Backend, queue>& backendObject,
                   const context& targetContext,
                   const async_handler asyncHandler = {});

  template <backend Backend>
  event make_event(const backend_input_t<Backend, event>& backendObject,
                   const context& targetContext);

  template <backend Backend, typename T, int Dimensions = 1,
            typename AllocatorT = buffer_allocator<std::remove_const_t<T>>>
  buffer<T, Dimensions, AllocatorT>
  make_buffer(const backend_input_t<Backend, buffer<T, Dimensions, AllocatorT>>&
                  backendObject,
              const context& targetContext, event availableEvent);

  template <backend Backend, typename T, int Dimensions = 1,
            typename AllocatorT = buffer_allocator<std::remove_const_t<T>>>
  buffer<T, Dimensions, AllocatorT>
  make_buffer(const backend_input_t<Backend, buffer<T, Dimensions, AllocatorT>>&
                  backendObject,
              const context& targetContext);

  template <backend Backend, int Dimensions = 1,
            typename AllocatorT = sycl::image_allocator>
  sampled_image<Dimensions, AllocatorT> make_sampled_image(
      const backend_input_t<Backend, sampled_image<Dimensions, AllocatorT>>&
          backendObject,
      const context& targetContext, image_sampler imageSampler,
      event availableEvent);

  template <backend Backend, int Dimensions = 1,
            typename AllocatorT = sycl::image_allocator>
  sampled_image<Dimensions, AllocatorT> make_sampled_image(
      const backend_input_t<Backend, sampled_image<Dimensions, AllocatorT>>&
          backendObject,
      const context& targetContext, image_sampler imageSampler);

  template <backend Backend, int Dimensions = 1,
            typename AllocatorT = sycl::image_allocator>
  unsampled_image<Dimensions, AllocatorT> make_unsampled_image(
      const backend_input_t<Backend, unsampled_image<Dimensions, AllocatorT>>&
          backendObject,
      const context& targetContext, event availableEvent);

  template <backend Backend, int Dimensions = 1,
            typename AllocatorT = sycl::image_allocator>
  unsampled_image<Dimensions, AllocatorT> make_unsampled_image(
      const backend_input_t<Backend, unsampled_image<Dimensions, AllocatorT>>&
          backendObject,
      const context& targetContext);

  template <backend Backend, bundle_state State>
  kernel_bundle<State> make_kernel_bundle(
      const backend_input_t<Backend, kernel_bundle<State>>& backendObject,
      const context& targetContext);

  template <backend Backend>
  kernel make_kernel(const backend_input_t<Backend, kernel>& backendObject,
                     const context& targetContext);

  } // namespace sycl

For each SYCL runtime class ``T`` which supports SYCL application
interoperability, a specialization of the appropriate template function
``make_{sycl_class}`` where ``{sycl_class}`` is the class name of
``T``, must be defined, which takes a SYCL application interoperability
``native backend object`` and constructs and returns an instance of
``T``. The availability and behavior of these template functions
is defined by the SYCL backend specification document.

Overloads of the ``make_{sycl_class}`` function which take a SYCL
``context`` object as an argument must throw an ``exception`` with the
``errc::backend_mismatch`` error code if the backend of the provided SYCL
context does not match the target backend.
