..
  Copyright 2020 The Khronos Group Inc.
  SPDX-License-Identifier: CC-BY-4.0

.. _address_space_classes:

*********************
Address space classes
*********************

There are five different address spaces (see also :ref:`address_space`):

* global;
* local;
* constant;
* private;
* generic.

In a SYCL generic implementation, types are not affected by the
address spaces. However, there are situations where users need
to explicitly carry address spaces in the type.

For example:

* For performance tuning and genericness. Even if the platform
  supports the representation of the generic address space,
  this may come at some performance sacrifice. In order to help
  the target compiler, it can be useful to track specifically
  which address space a pointer is addressing.

* When linking SYCL kernels with SYCL backend-specific functions.
  In this case, it might be necessary to specify the address
  space for any pointer parameters.

Direct declaration of pointers with address spaces is discouraged
as the definition is implementation-defined. Users must rely on
the :ref:`multi_ptr` class to handle address space boundaries
and interoperability.

.. seealso:: |SYCL_SPEC_ADDRESS_SPACE|

.. _address_space:

===============================
``sycl::access::address_space``
===============================

::

  namespace sycl::access {

    enum class address_space : /* unspecified */ {
      global_space,
      local_space,
      constant_space, // Deprecated in SYCL 2020
      private_space,
      generic_space
    };

  } // namespace sycl::access

.. _access-decorated:

===========================
``sycl::access::decorated``
===========================

::

  namespace sycl {

  namespace access {

  enum class decorated : /* unspecified */ {
    no,
    yes,
    legacy // Deprecated in SYCL 2020
  };

  } // namespace access

  template <typename T> struct remove_decoration {
    using type = /* ... */;
  };

  template <typename T> using remove_decoration_t = remove_decoration<T>::type;

  } // namespace sycl

The :ref:`multi_ptr` class exposes 3 flavors of the
same interface:

* If the value of ``sycl::access::decorated`` is
  ``sycl::access::decorated::no``, the interface exposes pointers and
  references type that are not decorated by an address space.
* If the value of ``sycl::access::decorated`` is
  ``sycl::access::decorated::yes``, the interface exposes pointers and
  references type that are decorated by an address space.
* If the value of  ``sycl::access::decorated`` is
  ``sycl::access::decorated::legacy``, the 1.2.1 interface is exposed.
  This interface is deprecated.

The decoration is implementation dependent and relies
on device compiler extensions.

The decorated type may be distinct from the non-decorated one.

For interoperability with the SYCL backend, users
should rely on types exposed by the decorated version.

The template traits ``sycl::remove_decoration`` and type alias
``sycl::remove_decoration_t`` retrieve the non-decorated pointer
or reference from a decorated one. Using this template trait
with a non-decorated type is safe and returns the same type.

.. _multi_ptr:

===================
``sycl::multi_ptr``
===================

::

  template <typename ElementType, access::address_space Space,
            access::decorated DecorateAddress = access::decorated::legacy>
  class multi_ptr;

  // Specialization of multi_ptr for void and const void
  // VoidType can be either void or const void
  template <access::address_space Space, access::decorated DecorateAddress>
  class multi_ptr<VoidType, Space, DecorateAddress>;

The ``sycl::multi_ptr`` class is the common interface for the explicit
pointer classes, defined in :ref:`explicit_pointer_aliases`.

There are situations where a user may want to make their type address
space dependent. This allows performing generic programming that depends
on the address space associated with their data.
An example might be wrapping a pointer inside a class, where a user may
need to template the class according to the address space of the pointer
the class is initialized with. In this case, the ``sycl::multi_ptr``
class enables users to do this in a portable and stable way.

You can select address space via :ref:`address_space` ``Space`` template
parameter and also interface type via :ref:`access-decorated`
``DecorateAddress`` template parameter.

.. _explicit_pointer_aliases:

========================
Explicit pointer aliases
========================
