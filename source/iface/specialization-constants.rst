..
  Copyright 2024 The Khronos Group Inc.
  SPDX-License-Identifier: CC-BY-4.0

.. _specialization-constants:

************************
Specialization Constants
************************

Device code can make use of specialization constants which represent
constants whose values can be set dynamically during execution of the
SYCL application. The values of these constants are fixed when a SYCL
kernel function is invoked, and they do not change during the execution
of the kernel. However, the application is able to set a new value for
a specialization constant each time a kernel is invoked, so the values
can be tuned differently for each invocation.

There are two methods for an application to use specialization constants.
One method requires creating a ``sycl::kernel_bundle`` object and
the other does not.
The syntax for both methods is mostly the same. Both methods declare
specialization constants in the same way, and kernels read their values
in the same way. The main difference is whether their values are set
via ``sycl::handler::set_specialization_constant()`` or via
``sycl::kernel_bundle::set_specialization_constant()``.
These two methods are incompatible with one another,
so they may not both be used by the same command group.

.. warning::

  Implementations that support online compilation of kernel bundles
  will likely implement both methods of specialization constants using
  kernel bundles. Therefore, applications should expect that there is
  some overhead associated with invoking a kernel with new values for
  its specialization constants. A typical implementation records the values
  of specialization constants set via
  ``sycl::handler::set_specialization_constant()`` and remembers these values
  until a kernel is invoked (e.g. via ``sycl::parallel_for()``). At this point,
  the implementation determines the bundle that contains the invoked kernel.
  If that bundle has already been compiled for the handler’s device and compiled
  with the correct values for the specialization constants, the kernel is
  scheduled for invocation. Otherwise, the implementation compiles the bundle
  before scheduling the kernel for invocation. Therefore, applications that
  frequently change the values of specialization constants may see an overhead
  associated with recompilation of the kernel’s bundle.

.. seealso:: |SYCL_SPEC_SPECIAL_CONSTANTS|

.. _specialization_id:

===========================
``sycl::specialization_id``
===========================

::

   template <class... Args>
   explicit constexpr specialization_id(Args&&... args);

Constraints: Available only when
``std::is_constructible_v<T, Args...>`` evaluates to ``true``.

Effects: Constructs a ``specialization_id`` containing an instance of ``T``
initialized with ``args``..., which represents the specialization
constant’s default value.

========================
Special member functions
========================

::

  specialization_id(const specialization_id& rhs) = delete;            // (1)

  specialization_id(specialization_id&& rhs) = delete;                 // (2)

  specialization_id& operator=(const specialization_id& rhs) = delete; // (3)

  specialization_id& operator=(specialization_id&& rhs) = delete;      // (4)

1.Deleted copy constructor.

2.Deleted move constructor.

3.Deleted copy assignment operator.

4.Deleted move assignment operator.

===================================
Declaring a specialization constant
===================================

Specialization constants must be declared using the ``specialization_id`` class
with the following restrictions:

 - the template parameter ``T`` must be a device copyable type;

 - the ``specialization_id`` variable must be declared as ``constexpr``;

 - the ``specialization_id`` variable must be declared in either
   namespace scope or in class scope;

 - if the ``specialization_id`` variable is declared in class scope,
   it must have public accessibility when referenced from namespace scope;

 - the ``specialization_id`` variable may not be shadowed by another
   identifier ``X`` which has the same name and is declared in an
   ``inline`` namespace, such that the ``specialization_id`` variable is
   no longer accessible after the declaration of ``X``;

 - if the ``specialization_id`` variable is declared in a namespace,
   none of the enclosing namespace names ``N`` may be shadowed by another
   identifier ``X`` which has the same name as ``N`` and is declared
   in an ``inline`` namespace, such that ``N`` is no longer
   accessible after the declaration of ``X``.

.. warning::

  The expectation is that some implementations may conceptually insert
  code at the end of a translation unit which references each
  ``specialization_id`` variable that is declared in that translation
  unit. The restrictions listed above make this possible by ensuring
  that these variables are accessible at the end of the translation unit.

==========================================================
Setting and getting the value of a specialization constant
==========================================================

If the application uses specialization constants without creating a
``sycl::kernel_bundle`` object, it can set and get their values from
command group scope by calling member functions of the ``handler`` class.
These member functions have a template parameter ``SpecName`` whose
value must be a reference to a variable of type ``specialization_id``,
which defines the type and default value of the specialization constant.

When not using a kernel bundle, the value of a specialization constant
that is used in a kernel invoked from a command group is affected by
calls to set its value from that same command group, but it is not
affected by calls from other command groups even if those calls are
from another invocation of the same command group function object.


``sycl::set_specialization_constant``
=====================================

::

   template <auto& SpecName>
   void set_specialization_constant(
       typename std::remove_reference_t<decltype(SpecName)>::value_type value);

Effects: Sets the value of the specialization constant whose address is
``SpecName`` for this handler’s command group. If the specialization
constant’s value was previously set in this same command group,
the value is overwritten.

This function may be called even if the specialization constant
``SpecName`` is not used by the kernel that is invoked by this
handler’s command group. Doing so has no effect on the invoked kernel.

Throws:

An ``exception`` with the ``sycl::errc::invalid`` error code
if a kernel bundle has been bound to the
``sycl::handler`` via ``use_kernel_bundle()``.

``sycl::get_specialization_constant``
=====================================

::

   template <auto& SpecName>
   typename std::remove_reference_t<decltype(SpecName)>::value_type
   get_specialization_constant();

Returns: The value of the specialization constant whose address is
``SpecName`` for this handler’s command group. If the value was
previously set in this handler’s command group, that value is returned.
Otherwise, the specialization constant’s default value is returned.

Throws:

An ``exception`` with the ``sycl::errc::invalid`` error code if a kernel
bundle has been bound to the
``sycl::handler`` via ``use_kernel_bundle()``.

===============================================================
Reading the value of a specialization constant from device code
===============================================================

In order to read the value of a specialization constant from device
code, the SYCL kernel function must be declared to take an object of
type ``kernel_handler`` as its last parameter. The SYCL runtime
constructs this object, which has a member function for reading
the specialization constant’s value.

.. _kernel_handler:

========================
``sycl::kernel_handler``
========================

::

  class kernel_handler;

In order to read the value of a specialization constant from
device code, the SYCL kernel function must be declared to take
an object of type ``sycl::kernel_handler`` as its last parameter. The
SYCL runtime constructs this object, which has a member
function for reading the specialization constant's value.

A synopsis of this class is shown below.

::

  namespace sycl {

  class kernel_handler {
   public:
    template <auto& SpecName>
    typename std::remove_reference_t<decltype(SpecName)>::value_type
    get_specialization_constant();
  };

  } // namespace sycl

================
Member functions
================

``sycl::get_specialization_constant``
=====================================

::

   template<auto& SpecName>
   typename std::remove_reference_t<decltype(SpecName)>::value_type
   get_specialization_constant();

Returns: The value of the specialization constant whose address is
``SpecName``. For a kernel invoked from a command group that was
not bound to a kernel bundle, the value is the same as what would
have been returned if ``sycl::handler::get_specialization_constant()``
was called immediately before invoking the kernel. For a kernel
invoked from a command group that was bound to a kernel bundle,
the value is the same as what would be returned if
``sycl::kernel_bundle::get_specialization_constant()``
was called on the bound bundle.

.. _specialization-constants-example:

=========
Example 1
=========

The following example performs a convolution and uses
specialization constants to set the values of the coefficients.

.. literalinclude:: /examples/specialization-constants.cpp
   :lines: 5-
   :linenos:

Output:

.. literalinclude:: /examples/specialization-constants.out
   :language: none
   :lines: 5-
