..
  Copyright 2020 The Khronos Group Inc.
  SPDX-License-Identifier: CC-BY-4.0

.. _iface-kernel-bundle:

**************
Kernel Bundles
**************


Kernel bundles provide several features to a SYCL application.
For implementations that support an online compiler, they provide
fine grained control over the online compilation of device code.
For example, an application can use a kernel bundle to compile its
kernels at a specific time during the application’s execution
(such as during its initialization), rather than relying on the
implementation’s default behavior (which may not compile kernels
until they are submitted).

Kernel bundles also provide a way for the application to set the
values of specialization constants in many kernels before any of
them are submitted to a device, which could potentially be more
efficient in some cases.

Kernel bundles provide a way for the application to introspect its
kernels. For example, an application can use a bundle to query a
kernel’s work-group size when it is run on a specific device.

Finally, kernel bundles provide an extension point to interoperate
with backend and device specific features. Some examples of this
include invocation of device specific built-in kernels, online
compilation of kernel code with vendor specific options, or
interoperation with kernels created with backend APIs.

========
Overview
========

A kernel bundle is a high-level abstraction which represents
a set of kernels that are associated with a context and can
be executed on a number of devices, where each device is
associated with that same context. Depending on how a bundle
is obtained, it could represent all of the SYCL kernel functions
in the SYCL application, or a certain subset of them.

A kernel bundle is composed of one or more device images, where
each device image is an indivisible unit of compilation and/or
linking. When the SYCL runtime compiles or links one of the
kernels represented by the device image, it must also compile
or link any other kernels the device image represents. Once a
device image is compiled and linked, any of the other kernels
which that device image represents may be invoked without
further compilation or linking.

Each SYCL kernel function a bundle represents must reside in at
least one of the bundle’s device images. However, it is not
necessary for each device image to contain all of the kernel
functions that the bundle represents. The granularity in which
kernel functions are grouped into device images is
an implementation detail.

.. warning::

  To illustrate the intent of device images, a hypothetical
  implementation could represent an application’s kernel
  functions in both the SPIR-V format and also in a native
  device code format. The implementation’s ahead-of-time
  compiler in this example produces device images with native
  code for certain devices and also produces SPIR-V device
  images for use with other devices. Note that in such an
  implementation, a particular kernel function could be
  represented in more than one device image.

  An implementation could choose to have all kernel functions
  from all translation units grouped together in a single
  device image, to have each kernel function represented
  in its own device image, or to group kernel functions
  in some other way.

Each device associated with a kernel bundle must have at
least one compatible device image, meaning that the
implementation can either invoke the image’s kernel
functions directly on the device or that the implementation
can translate the device image into a format that
allows it to invoke the kernel functions.

An outcome of this definition is that each kernel function
in a bundle must be invocable on at least one of the devices
associated with the bundle. However, it is not necessary for
every kernel function in the bundle to be invocable on
every associated device.

.. warning::

  One common reason why a kernel function might not be
  invocable on every device associated with a bundle is if
  the kernel uses optional device features. It’s possible
  that these features are available to only some devices
  in the bundle.

  The use of optional device features could affect how the
  implementation groups kernels into device images,
  depending on how these features are represented. For
  example, consider an implementation where the optional
  feature is represented in SPIR-V but translation of that
  SPIR-V into native code will fail if the target device
  does not support the feature. In such an implementation,
  kernels that use optional features should not be grouped
  into the same device image as kernels that do not use
  these features. Since a device image is an indivisible
  unit of compilation, doing so would cause a compilation
  failure if a kernel K1 is invoked on a device D1 if K1
  happened to reside in the same device image as another
  kernel K2 that used a feature which is not supported
  on device D1.
.. seealso:: |SYCL_SPEC_OPTIONAL_KERNEL_FEATURES|

A SYCL application can obtain a kernel bundle by calling one of the
overloads of the ``get_kernel_bundle()`` free function. Certain
backends may provide additional mechanisms for obtaining bundles
with other representations. If this is supported, the backend
specification document will describe the details.

Once a kernel bundle has been obtained there are a number of free
functions for performing compilation, linking and joining. Once a
bundle is compiled and linked, the application can invoke kernels
from the bundle by calling ``sycl::handler::use_kernel_bundle()`` as
described in |SYCL_SPEC_USING_KERNEL_BUNDLE_FUNC|.


===============================
Fixed-function built-in kernels
===============================

SYCL allows a SYCL backend to expose fixed functionality as
non-programmable built-in kernels. The availability and
behavior of these built-in kernels are backend specific
and are not required to follow the SYCL execution and
memory models. However, the basic interface is
common to all backends.

=============
Bundle states
=============

A kernel bundle can be in one of three different bundle states
which are represented by an enum class called ``sycl::bundle_state``.

The states form a progression. A bundle in
``sycl::bundle_state::input`` can be translated into
``sycl::bundle_state::object`` by online compilation of the bundle.
A bundle in ``sycl::bundle_state::object`` can be translated into
``sycl::bundle_state::executable`` by online linking.

There is no requirement that an implementation must expose kernels in
``sycl::bundle_state::input`` or ``sycl::bundle_state::object``. In fact,
an implementation could expose some kernels in these states but not
others. For example, this behavior could be controlled by
implementation specific options to the ahead-of-time compiler.
Kernels that are not exposed in these states cannot be
online compiled or online linked by the application.

All kernels defined in the SYCL application, however, must be
exposed in ``sycl::bundle_state::executable`` because this is the
only state that allows a kernel to be invoked on a device.
Device built-in kernels are also exposed in
``sycl::bundle_state::executable``.

If an application exposes a bundle in ``sycl::bundle_state::input``
for a device D, then the implementation must also provide an
online compiler for device D. Therefore, an application need
not explicitly test for ``sycl::aspect::online_compiler`` if it
successfully obtains a bundle in ``sycl::bundle_state::input``
for that device. Likewise, an implementation must provide
an online linker for device D if it exposes a bundle in
``sycl::bundle_state::object`` for device D.


``sycl::bundle_state::input``
=============================

::

  sycl::bundle_state::input

The device images in the kernel bundle have a format that must
be compiled and linked before their kernels can be invoked.
For example, an implementation could use this state for
device images that are stored in an intermediate language
format or for device images that are stored as source
code strings.

``sycl::bundle_state::object``
==============================

::

  sycl::bundle_state::object

The device images in the kernel bundle have a format that must
be linked before their kernels can be invoked.

``sycl::bundle_state::executable``
==================================

::

  sycl::bundle_state::executable

The device images in the kernel bundle are in a format that
allows them to be invoked on a device. For example, an
implementation could use this state for device images
that have been compiled into the device’s native code.


==================
Kernel identifiers
==================

Some of the functions related to kernel bundles take an input parameter
of type ``sycl::kernel_id`` which identifies a kernel.

As with all SYCL objects that have the common reference semantics,
kernel identifiers are equality comparable. Two ``sycl::kernel_id``
objects compare equal if and only if they refer to the same
application kernel or to the same device built-in kernel.

.. _kernel_id:

``sycl::kernel_id``
===================

::

 class kernel_id;

There is no public default constructor for this class.

A synopsis of the ``sycl::kernel_id`` class is shown below along with a
description of its member functions.

::

  namespace sycl {

  class kernel_id {
   public:
    kernel_id() = delete;

    const char* get_name() const noexcept;
  };

  } // namespace sycl

``get_name()``
--------------

::

  const char* get_name() const noexcept;

Returns an implementation-defined null-terminated string
containing the name of the kernel. There is no guarantee
that this name is unique amongst all the kernels, nor is
there a guarantee that the name is stable from one run of
the application to another. The lifetime of the memory
containing the name is unspecified.

=============================
Obtaining a kernel identifier
=============================

An application can obtain an identifier for a kernel that
is defined in the application by calling one of the following
free functions, or it may obtain an identifier for a device’s
built-in kernels by querying the device with
``sycl::info::device::built_in_kernel_ids``.

``sycl::get_kernel_id``
=======================

::

  template <typename KernelName>
  sycl::kernel_id get_kernel_id();

Preconditions: The template parameter ``KernelName`` must be the type
kernel name of a kernel that is defined in the SYCL application. Since
lambda functions have no standard type name, kernels defined as lambda
functions must specify a ``KernelName`` in their kernel invocation
command in order to obtain their identifier via this function.
Applications which call ``get_kernel_id()`` for a ``KernelName``
that is not defined are ill formed, and the implementation must
issue a diagnostic in this case.

Returns the identifier of the kernel associated with ``KernelName``.

``sycl::get_kernel_ids``
========================

::

  std::vector<sycl::kernel_id> get_kernel_ids();

Returns a vector with the identifiers for all kernels defined
in the SYCL application. This does not include identifiers for
any device built-in kernels.

=========================
Obtaining a kernel bundle
=========================

A SYCL application can obtain a kernel bundle by calling one of the
overloads of the free function ``sycl::get_kernel_bundle()``. The
implementation may return a bundle that consists of device images
that were created by the ahead-of-time compiler, or it may call the
online compiler or linker to create the bundle’s device images in the
requested state. A bundle may also contain device images that
represent a device’s built-in kernels.

When ``sycl::get_kernel_bundle()`` is used to obtain a kernel bundle in
``sycl::bundle_state::object`` or ``sycl::bundle_state::executable``,
any specialization constants in the bundle will have their
default values.

``sycl::get_kernel_bundle``
===========================

::

  template <sycl::bundle_state State>
  sycl::kernel_bundle<State> get_kernel_bundle(const sycl::context& ctxt,
                                               const std::vector<sycl::device>& devs);

Returns: A kernel bundle in state ``State`` which contains all of the kernels
in the application which are compatible with at least one of the devices in
``devs``. This does not include any device built-in kernels. The bundle’s
set of associated devices is ``devs`` (with any duplicate devices removed).

Since the implementation may not represent all kernels in
``sycl::bundle_state::input`` or ``sycl::bundle_state::object``, calling
this function with one of those states may return a bundle that is missing
some of the application’s kernels.

Throws:

* A ``sycl::exception`` with the ``sycl::errc::invalid`` error code if any
  of the devices in ``devs`` is not one of devices contained by the context
  ``ctxt`` or is not a descendent device of some device in ``ctxt``.
* A ``sycl::exception`` with the ``sycl::errc::invalid`` error code if the
  ``devs`` vector is empty.
* A ``sycl::exception`` with the ``sycl::errc::invalid`` error code if
  ``Stat`` is ``sycl::bundle_state::input`` and any device in
  ``devs`` does not have ``sycl::aspect::online_compiler``.
* A ``sycl::exception`` with the ``sycl::errc::invalid`` error code if
  ``State`` is ``sycl::bundle_state::object`` and any device in
  ``devs`` does not have ``sycl::aspect::online_linker``.
* A ``sycl::exception`` with the ``sycl::errc::build`` error code if
  ``State`` is ``sycl::bundle_state::object`` or
  ``sycl::bundle_state::executable``, if the implementation needs
  to perform an online compile or link, and if the online
  compile or link fails.

::

  template <sycl::bundle_state State>
  sycl::kernel_bundle<State> get_kernel_bundle(const sycl::context& ctxt,
                                               const std::vector<sycl::device>& devs,
                                               const std::vector<sycl::kernel_id>& kernelIds);

Returns: A kernel bundle in state ``State`` which contains all of
the device images that are compatible with at least one of the
devices in ``devs``, further filtered to contain only those device
images that contain at least one of the kernels with the given
identifiers. These identifiers may represent kernels that are defined
in the application, device built-in kernels, or a mixture of the two.
Since the device images may group many kernels together,
the returned bundle may contain additional kernels beyond those
that are requested in ``kernelIds``. The bundle’s set of associated
devices is ``devs`` (with duplicate devices removed).

Since the implementation may not represent all kernels in
``sycl::bundle_state::input`` or ``sycl::bundle_state::object``,
calling this function with one of those states may return a
bundle that is missing some of the kernels in ``kernelIds``.
The application can test for this via
``sycl::kernel_bundle::has_kernel()``.

Throws:

* A ``sycl::exception`` with the ``sycl::errc::invalid`` error code if
  any of the kernels identified by ``kernelIds`` are incompatible with
  all devices in ``devs``.
* A ``sycl::exception`` with the ``sycl::errc::invalid`` error code if
  any of the devices in ``devs`` is not one of devices contained by the
  context ``ctxt`` or is not a descendent device of some device in ``ctxt``.
* A ``sycl::exception`` with the ``sycl::errc::invalid`` error code if
  the ``devs`` vector is empty.
* A ``sycl::exception`` with the ``sycl::errc::invalid`` error code if
  ``State`` is ``sycl::bundle_state::input`` and any device in ``devs``
  does not have ``sycl::aspect::online_compiler``.
* A ``sycl::exception`` with the ``sycl::errc::invalid`` error code if
  ``State`` is ``sycl::bundle_state::object`` and any device in ``devs``
  does not have ``sycl::aspect::online_linker``.
* A ``sycl::exception`` with the ``sycl::errc::build`` error code if ``State``
  is ``sycl::bundle_state::object`` or ``sycl::bundle_state::executable``, if
  the implementation needs to perform an online compile or link, and
  if the online compile or link fails.

::

  template <sycl::bundle_state State, typename Selector>
  sycl::kernel_bundle<State> get_kernel_bundle(const sycl::context& ctxt,
                                               const std::vector<sycl::device>& devs,
                                               Selector selector);

Preconditions: The ``selector`` must be a unary predicate whose return
value is convertible to ``bool`` and whose parameter is
``const sycl::device_image<State>&``.

Effects: The predicate function ``selector`` is called once for every
device image in the application of state ``State`` which is compatible
with at least one of the devices in ``devs``. The function’s return
value determines whether a device image is included in the new
kernel bundle. The ``selector`` is called only for device images
that contain kernels defined in the application, not for device
images that contain device built-in kernels.

Returns: A kernel bundle in state ``State`` which contains all
of the device images for which the ``selecto`` returns ``true``.
The bundle’s set of associated devices is ``devs``
(with duplicate devices removed).

Throws:

* A ``sycl::exception`` with the ``sycl::errc::invalid`` error code if any of
  the devices in ``devs`` is not one of devices contained by the
  context ``ctxt`` or is not a descendent device of some device
  in ``ctxt``.
* A ``sycl::exception`` with the ``sycl::errc::invalid`` error code if
  the ``devs`` vector is empty.
* A ``sycl::exception`` with the ``sycl::errc::invalid`` error code if
  ``State`` is ``sycl::bundle_state::input`` and any device in
  ``devs`` does not have ``sycl::aspect::online_compiler``.
* A ``sycl::exception`` with the ``sycl::errc::invalid`` error code if
  ``State`` is ``sycl::bundle_state::object`` and any device in
  ``devs`` does not have ``sycl::aspect::online_linker``.

::

  template <sycl::bundle_state State> // (1)
  sycl::kernel_bundle<State> get_kernel_bundle(const sycl::context& ctxt);

  template <sycl::bundle_state State> // (2)
  sycl::kernel_bundle<State> get_kernel_bundle(const context& ctxt,
                                               const std::vector<kernel_id>& kernelIds);

  template <sycl::bundle_state State, typename Selector> // (3)
  sycl::kernel_bundle<State> get_kernel_bundle(const sycl::context& ctxt, Selector selector);

1. Equivalent to
   ``sycl::get_kernel_bundle<State>(ctxt, ctxt.get_devices())``.

2. Equivalent to
   ``sycl::get_kernel_bundle<State>(ctxt, ctxt.get_devices(), kernelIds)``.

3. Equivalent to
   ``sycl::get_kernel_bundle<State>(ctxt, ctxt.get_devices(), selector)``.

::

  template <typename KernelName, sycl::bundle_state State> // (1)
  sycl::kernel_bundle<State> get_kernel_bundle(const sycl::context& ctxt);

  template <typename KernelName, sycl::bundle_state State> // (2)
  sycl::kernel_bundle<State> get_kernel_bundle(const sycl::context& ctxt,
                                               const std::vector<sycl::device>& devs);

Preconditions: The template parameter ``KernelName`` must be the type
kernel name of a kernel that is defined in the SYCL application. Since
lambda functions have no standard type name, kernels defined as lambda
functions must specify a ``KernelName`` in their kernel invocation
command in order to use these functions. Applications which call
these functions for a ``KernelName`` that is not defined are ill
formed, and the implementation must issue a diagnostic in this case.

1. Equivalent to ``sycl::get_kernel_bundle<State>(ctxt, ctxt.get_devices(),
   {get_kernel_id<KernelName>()})``.

2. Equivalent to ``sycl::get_kernel_bundle<State>(ctxt, devs,
   {get_kernel_id<KernelName>()})``.

==================================
Querying if a kernel bundle exists
==================================

Most overloads of ``sycl::get_kernel_bundle()`` have a matching overload of
the free function ``sycl::has_kernel_bundle()`` which checks to
see if a kernel bundle with the requested characteristics exists.

``sycl::has_kernel_bundle``
===========================

::

  template <sycl::bundle_state State>
  bool has_kernel_bundle(const sycl::context& ctxt, const std::vector<sycl::device>& devs);

Returns ``true`` only if all of the following are true:

* The application defines at least one kernel that is compatible with at
  least one of the devices in ``devs``, and that kernel can be represented
  in a device image of state ``State``.
* If ``State`` is ``sycl::bundle_state::input``, all devices in
  ``devs`` have ``sycl::aspect::online_compiler``.
* If ``State`` is ``sycl::bundle_state::object``, all devices in
  ``devs`` have ``sycl::aspect::online_linker``.

Throws:

* A ``sycl::exception`` with the ``sycl::errc::invalid`` error code if any of
  the devices in ``devs`` is not one of devices contained by the
  context ``ctxt`` or is not a descendent device of some device in ``ctxt``.
* A ``sycl::exception`` with the ``sycl::errc::invalid`` error code if the
  ``devs`` vector is empty.

::

  template <sycl::bundle_state State>
  bool has_kernel_bundle(const sycl::context& ctxt,
                         const std::vector<sycl::device>& devs,
                         const std::vector<sycl::kernel_id>& kernelIds);

Returns ``true`` only if all of the following are true:

* Each of the kernels in ``kernelIds`` can be represented in a
  device image of state ``State``.
* Each of the kernels in ``kernelIds`` is compatible with at
  least one of the devices in ``devs``.
* If ``State`` is ``sycl::bundle_state::input``, all devices in
  ``devs`` have ``sycl::aspect::online_compiler``.
* If ``State`` is ``sycl::bundle_state::object``, all devices in
  ``devs`` have ``sycl::aspect::online_linker``.

Throws:

* A ``sycl::exception`` with the ``sycl::errc::invalid`` error code if any
  of the devices in ``devs`` is not one of devices contained by
  the context ``ctxt`` or is not a descendent device of some
  device in ``ctxt``.
* A ``sycl::exception`` with the ``sycl::errc::invalid`` error code if
  the ``devs`` vector is empty.

::

  template <sycl::bundle_state State> // (1)
  bool has_kernel_bundle(const sycl::context& ctxt);

  template <sycl::bundle_state State> // (2)
  bool has_kernel_bundle(const sycl::context& ctxt,
                         const std::vector<sycl::kernel_id>& kernelIds);

1. Equivalent to
   ``sycl::has_kernel_bundle(ctxt, ctxt.get_devices())``.

2. Equivalent to
   ``sycl::has_kernel_bundle<State>(ctxt, ctxt.get_devices(), kernelIds)``.

::

  template <typename KernelName, bundle_state State> // (1)
  bool has_kernel_bundle(const sycl::context& ctxt);

  template <typename KernelName, sycl::bundle_state State> // (2)
  bool has_kernel_bundle(const sycl::context& ctxt,
                         const std::vector<sycl::device>& devs);

Preconditions: The template parameter ``KernelName`` must be the
type kernel name of a kernel that is defined in the SYCL
application. Since lambda functions have no standard type
name, kernels defined as lambda functions must specify a
``KernelName`` in their kernel invocation command in order
to use these functions. Applications which call these functions
for a ``KernelName`` that is not defined are ill formed, and
the implementation must issue a diagnostic in this case.

1. Equivalent to
   ``sycl::has_kernel_bundle<State>(ctxt, {get_kernel_id<KernelName>()})``.

2. Equivalent to
   ``sycl::has_kernel_bundle<State>(ctxt, devs, {get_kernel_id<KernelName>()})``.

================================================
Querying if a kernel is compatible with a device
================================================

The following free functions allow an application to test whether
a particular kernel is compatible with a device. A kernel that is
defined in the application is compatible with a device unless:

It uses optional features which are not supported on the device, as
described in |SYCL_SPEC_OPTIONAL_KERNEL_FEATURES|; or

It is decorated with a ``[[sycl::device_has()]]`` C++ attribute that
lists an aspect that is not supported by the device

The translation unit containing the kernel was compiled in a
compilation environment that does not support the device. Each
implementation defines the specific criteria for which devices
are supported in its compilation environment. For example, this
might be dependent on options passed to the compiler.

A device built-in kernel is only compatible with the device for
which it is built-in.

``sycl::is_compatible``
=======================

::

  bool is_compatible(const std::vector<sycl::kernel_id>& kernelIds,
                     const sycl::device& dev);

Returns ``true`` if all of the kernels identified by ``kernelIds``
are compatible with the device ``dev``.

::

  template <typename KernelName>
  bool is_compatible(const sycl::device& dev);

Preconditions: The template parameter ``KernelName`` must be the type
kernel name of a kernel that is defined in the SYCL application. Since
lambda functions have no standard type name, kernels defined as lambda
functions must specify a ``KernelName`` in their kernel invocation
command in order to use this function. Applications which call this
function for a ``KernelName`` that is not defined are ill formed,
and the implementation must issue a diagnostic in this case.

Equivalent to
``sycl::is_compatible<State>({get_kernel_id<KernelName>()}, dev)``.

======================
Joining kernel bundles
======================

Two or more kernel bundles of the same state may be joined together into
a single composite bundle. Joining bundles together is not the same as
online compiling or linking because it produces a new bundle in the same
state as its inputs. Rather, joining creates the union of all the
devices images from the input bundles, eliminates duplicate copies
of the same device image, and creates a new bundle from the result.

``sycl::join``
==============

::

  template <sycl::bundle_state State>
  sycl::kernel_bundle<State> join(const std::vector<sycl::kernel_bundle<State>>& bundles);

Returns: A new kernel bundle that contains a copy of all the device
images in the input ``bundles`` with duplicates removed. The new
bundle has the same associated context and the same set of
associated devices as those in ``bundles``.

Throws a ``sycl::exception`` with the ``sycl::errc::invalid``
error code if the bundles in ``bundles`` do not all have the
same associated context or do not all have the same set of
associated devices.

============================
Online compiling and linking
============================

If the implementation provides an online compiler or linker, a SYCL
application can use the free functions defined in this section to
transform a kernel bundle from ``sycl::bundle_state::input`` into a
bundle of state ``sycl::bundle_state::object`` or to transform a bundle
from ``sycl::bundle_state::object`` into a bundle of state
``sycl::bundle_state::executable``.

An application can query whether the implementation provides an
online compiler or linker by querying a device for
``sycl::aspect::online_compiler`` or ``sycl::aspect::online_linker``.

All of the functions in this section accept a ``sycl::property_list``
parameter, which can affect the semantics of the compilation or
linking operation. The core SYCL specification does not currently
define any such properties, but vendors may specify these
properties as an extension.

``sycl::compile``
=================

::

  sycl::kernel_bundle<sycl::bundle_state::object>
  compile(const sycl::kernel_bundle<sycl::bundle_state::input>& inputBundle,
          const std::vector<sycl::device>& devs,
          const sycl::property_list& propList = {});

Effects: The device images from ``inputBundle`` are translated into
one or more new device images of state ``sycl::bundle_state::object``,
and a new kernel bundle is created to contain these new device
images. The new bundle represents all of the kernels in
``inputBundles`` that are compatible with at least one of the
devices in ``devs``. Any remaining kernels (those that are not
compatible with any of the devices ``devs``) are not compiled
and not represented in the new kernel bundle.

The new bundle has the same associated context as ``inputBundle``,
and the new bundle’s set of associated devices is ``devs`` (with
duplicate devices removed).

Returns the new kernel bundle.

Throws:

* A ``sycl::exception`` with the ``sycl::errc::invalid`` error code if
  any of the devices in ``devs`` are not in the set of associated
  devices for ``inputBundle`` (as defined by
  ``sycl::kernel_bundle::get_devices()``)
  or if the ``devs`` vector is empty.
* A ``sycl::exception`` with the ``sycl::errc::build`` error code if the online
  compile operation fails.

``sycl::link``
==============

::

  sycl::kernel_bundle<sycl::bundle_state::executable>
  link(const std::vector<sycl::kernel_bundle<sycl::bundle_state::object>>& objectBundles,
       const std::vector<sycl::device>& devs,
       const sycl::property_list& propList = {});

Effects: Duplicate device images from ``objectBundles`` are
into one or more new device images of state ``sycl::bundle_state::executable``,
and a new kernel bundle is created to contain these new device images.
The new bundle represents all of the kernels in ``objectBundles`` that
are compatible with at least one of the devices in ``devs``. Any
remaining kernels (those that are not compatible with any of the devices
in ``devs``) are not linked and not represented in the new bundle.

The new bundle has the same associated context as those in
``objectBundles``, and the new bundle’s set of associated devices
is ``devs`` (with duplicate devices removed).

Returns the new kernel bundle.

Throws:

* A ``sycl::exception`` with the ``sycl::errc::invalid`` error code if the
  bundles in ``objectBundles`` do not all have the same associated context.
* A ``sycl::exception`` with the ``sycl::errc::invalid`` error code if any
  of the devices in ``devs`` are not in the set of associated devices for
  any of the bundles in ``objectBundles`` (as defined by
  ``sycl::kernel_bundle::get_devices()``) or if the ``devs`` vector is empty.
* A ``sycl::exception`` with the ``sycl::errc::build`` error code if the online
  link operation fails.

``sycl::build``
===============

::

  sycl::kernel_bundle<sycl::bundle_state::executable>
  build(const sycl::kernel_bundle<sycl::bundle_state::input>& inputBundle,
        const std::vector<sycl::device>& devs,
        const sycl::property_list& propList = {});

Effects: This function performs both an online compile and link operation,
translating a kernel bundle of state ``sycl::bundle_state::input`` into
a bundle of state ``sycl::bundle_state::executable``. The device images
from ``inputBundle`` are translated into one or more new device images of
state ``sycl::bundle_state::executable``, and a new bundle is created to
contain these new device images. The new bundle represents all of the
kernels in ``inputBundle`` that are compatible with at least one of the
devices in ``devs``. Any remaining kernels (those that are not compatible
with any of the devices ``devs``) are not compiled or linked and are not
represented in the new bundle.

The new bundle has the same associated context as ``inputBundle``,
and the new bundle’s set of associated devices is ``devs`` (with
duplicate devices removed).

Returns the new kernel bundle.

Throws:

* An ``sycl::exception`` with the ``sycl::errc::invalid`` error code if any
  of the devices in ``devs`` are not in the set of associated devices for
  ``inputBundle`` (as defined by ``sycl::kernel_bundle::get_devices()``)
  or if the ``devs`` vector is empty.
* An ``sycl::exception`` with the ``sycl::errc::build`` error code if the
  online compile or link operations fail.

Additional overloads
====================

::

  sycl::kernel_bundle<sycl::bundle_state::object> // (1)
  compile(const sycl::kernel_bundle<sycl::bundle_state::input>& inputBundle,
          const sycl::property_list& propList = {});

  sycl::kernel_bundle<sycl::bundle_state::executable> // (2)
  link(const sycl::kernel_bundle<sycl::bundle_state::object>& objectBundle,
       const std::vector<sycl::device>& devs,
       const sycl::property_list& propList = {});

  sycl::kernel_bundle<sycl::bundle_state::executable> // (3)
  link(const std::vector<sycl::kernel_bundle<sycl::bundle_state::object>>& objectBundles,
       const sycl::property_list& propList = {});

  sycl::kernel_bundle<sycl::bundle_state::executable> // (4)
  link(const sycl::kernel_bundle<sycl::bundle_state::object>& objectBundle,
       const sycl::property_list& propList = {});

  sycl::kernel_bundle<sycl::bundle_state::executable> // (5)
  build(const sycl::kernel_bundle<sycl::bundle_state::input>& inputBundle,
        const sycl::property_list& propList = {});

1. Equivalent to
   ``sycl::compile(inputBundle, inputBundle.get_devices(), propList)``.
2. Equivalent to
   ``sycl::link({objectBundle}, devs, propList)``.
3. Equivalent to
   ``sycl::link(objectBundles, devs, propList)``, where
   ``devs`` is the intersection of associated
   devices in common for all bundles in ``objectBundles``.
4. Equivalent to
   ``sycl::link({objectBundle}, objectBundle.get_devices(), propList)``.
5. Equivalent to
   ``sycl::build(inputBundle, inputBundle.get_devices(), propList)``.
