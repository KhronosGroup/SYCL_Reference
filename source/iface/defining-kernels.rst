..
  Copyright 2024 The Khronos Group Inc.
  SPDX-License-Identifier: CC-BY-4.0

.. _defining-kernels:

****************
Defining Kernels
****************

In SYCL, functions that are executed on a SYCL device
are referred to as SYCL kernel functions. A kernel
containing such a SYCL kernel function is enqueued on
a device queue in order to be executed on that particular device.

The return type of the SYCL kernel function is ``void``, and all
memory accesses between host and device are through
:ref:`accessors <iface-accessors>` or through
:ref:`USM pointers <iface-usm>`.

There are two ways of defining kernels:

* as named function objects;
* as lambda functions.

A backend may also provide interoperability
interfaces for defining kernels.

.. seealso:: |SYCL_SPEC_DEFINING_KERNELS|

==========================================
Defining kernels as named function objects
==========================================

A kernel can be defined as a named function object type.
These function objects provide the same functionality as
any C++ function object, with the restriction that they
need to follow SYCL rules to be device copyable
(see |SYCL_SPEC_DEVICE_COPYABLE|).

The kernel function can be templated via templating the
kernel function object type.
For details on restrictions for kernel naming,
please refer to |SYCL_SPEC_KERNEL_NAMING|.

The ``operator()`` member function must be ``const``-qualified,
and it may take different parameters depending on the data
accesses defined for the specific kernel. If the ``operator()``
function writes to any of the member variables, the behavior
is undefined.

The following example defines a SYCL kernel function,
``RandomFiller``, which initializes a :ref:`buffer` with a random
number.


.. literalinclude:: /examples/def_kernels_named_function_obj.cpp
  :lines: 5-
  :linenos:

Possible output:

.. literalinclude:: /examples/def_kernels_named_function_obj.out
  :lines: 5-

The random number is generated during the construction
of the function object while processing the command group.

The ``operator()`` member function of the function object receives
an :ref:`item` object. This member function will be called for each
work-item of the execution range. The value of the random number will
be assigned to each element of the :ref:`buffer`.

In this case, the :ref:`command-accessor`  and the scalar random number
are members of the function object and therefore will be arguments to the
device kernel. Usual restrictions of passing arguments to kernels apply.


====================================
Defining kernels as lambda functions
====================================

In C++, function objects can be defined using lambda functions. Kernels may
be defined as lambda functions in SYCL.

The name of a lambda function in SYCL may optionally be specified by passing
it as a template parameter to the invoking member function, and in that case,
the lambda name is a C++ typename which must be forward declarable at
namespace scope.

If the lambda function relies on template arguments, then if specified, the
name of the lambda function must contain those template arguments which must
also be forward declarable at namespace scope.

The class used for the name of a lambda function is only used for naming
purposes and is not required to be defined. For details on restrictions
for kernel naming, please refer to |SYCL_SPEC_KERNEL_NAMING|.

The kernel function for the lambda function is the lambda function itself.
The kernel lambda must use copy for all of its captures (i.e. ``[=]``),
and the lambda must not use the ``mutable`` specifier.

::

  // Explicit kernel names can be optionally forward declared at namespace scope
  class MyKernel;

  {
    ...

    myQueue.submit([&](sycl::handler& h) {
      // Explicitly name kernel with previously forward declared type
      h.single_task<MyKernel>([=] {
        // [kernel code]
      });

      // Explicitly name kernel without forward declaring type at
      // namespace scope.  Must still be forward declarable at
      // namespace scope, even if not declared at that scope
      h.single_task<class MyOtherKernel>([=] {
        // [kernel code]
      });
    });

    ...
  }

Explicit lambda naming is shown in the following code example,
including an illegal case that uses a class within the kernel
name which is not forward declarable (``std::complex``).

.. literalinclude:: /examples/def_kernels_lambda.cpp
  :lines: 5-
  :linenos:


.. _is_device_copyable:

============================
``sycl::is_device_copyable``
============================

::

  namespace sycl {

    template<typename T>
    struct is_device_copyable;

    template<typename T>
    inline constexpr bool is_device_copyable_v = is_device_copyable<T>::value;

  } // namespace sycl

``sycl::is_device_copyable`` is a user specializable class
template to indicate that a type ``T`` is device copyable
(see |SYCL_SPEC_DEVICE_COPYABLE|).

Requirements:

* ``sycl::is_device_copyable`` must meet the ``Cpp17UnaryTrait``
  requirements.
* If ``sycl::is_device_copyable`` is specialized such that
  ``sycl::is_device_copyable<T> == true`` on a ``T`` that
  does not satisfy all the requirements of a device copyable
  type, the results are unspecified.

If the application defines a type ``UDT`` that satisfies the
requirements of a device copyable type but the type is not
implicitly device copyable as defined in that section,
then the application must provide a specialization of
``sycl::is_device_copyable`` that derives from ``std:true_type``
in order to use that type in a context that requires a device
copyable type. Such a specialization can be declared like this:

::

  template<>
  struct sycl::is_device_copyable<UDT> : std::true_type {};

It is legal to provide this specialization even if the
implementation does not define ``SYCL_DEVICE_COPYABLE`` to ``1``,
but the type cannot be used as a device copyable type in that
case and the specialization is ignored.


======================================
Rules for parameter passing to kernels
======================================

A SYCL application passes parameters to a kernel in
different ways depending on whether the kernel is a
named function object or a lambda function.

If the kernel is a named function object, the
``operator()`` member function (or other member
functions that it calls) may reference member
variables inside the same named function object.
Any such member variables become parameters to
the kernel.

If the kernel is a lambda function, any variables
captured by the lambda become parameters to the kernel.

Regardless of how the parameter is passed, the following
rules define the allowable types for a kernel parameter:

* Any device copyable (see |SYCL_SPEC_DEVICE_COPYABLE|) type is
  a legal parameter type.
* The following SYCL types are legal parameter types:

  - :ref:`command-accessor` when templated with ``sycl::target::device``;
  - :ref:`command-accessor` when templated with any of the deprecated
    parameters: ``sycl::target::global_buffer``,
    ``sycl::target::constant_buffer``, or ``sycl::target::local``;
  - :ref:`local_accessor`;
  - :ref:`unsampled_image_accessor` when templated with
    ``sycl::image_target::device``;
  - :ref:`sampled_image_accessor` when templated with
    ``sycl::image_target::device``;
  - :ref:`stream`;
  - :ref:`id`;
  - :ref:`range`;
  - ``sycl::marray<T, NumElements>`` when ``T`` is device copyable;
  - ``sycl::vec<T, NumElements>``.

* An array of element types ``T`` is a legal parameter type if
  ``T`` is a legal parameter type.
* A class type ``S`` with a non-static member variable of type
  ``T`` is a legal parameter type if ``T`` is a legal parameter
  type and if ``S`` would otherwise be a legal parameter type
  aside from this member variable.
* A class type ``S`` with a non-virtual base class of type ``T``
  is a legal parameter type if ``T`` is a legal parameter type
  and if ``S`` would otherwise be a legal parameter type aside
  from this base class.

.. note::

  Pointer types are trivially copyable, so they may be passed
  as kernel parameters. However, only the pointer value itself
  is passed to the kernel. Dereferencing the pointer on the
  kernel results in undefined behavior unless the pointer points
  to an address within a USM memory region that is accessible on
  the device.

  Reference types are not trivially copyable, so they may not be
  passed as kernel parameters.

.. note::

  The ``sycl::reducer`` class is a special type of kernel parameter
  which is passed to a kernel in a different way. See :ref:`reduction-variables`
  for the description how this parameter type is used.
