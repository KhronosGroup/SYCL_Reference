..
  Copyright 2024 The Khronos Group Inc.
  SPDX-License-Identifier: CC-BY-4.0

.. _iface-exceptions:

**********
Exceptions
**********

===================
``sycl::exception``
===================

::

  class exception : public virtual std::exception;

Errors can occur both in the SYCL library and SYCL host side,
or may come directly from a SYCL backend. The member functions
on these exceptions provide the corresponding information. SYCL
backends can provide additional exception class objects as long
as they derive from ``sycl::exception`` object, or any of its
derived classes.

.. seealso::

  |SYCL_SPEC_EXCEPTION|

  :ref:`iface-error-handling-rules`

  :ref:`iface-async-error-handler`

(constructors)
==============

.. rubric:: Constructor 1

::

  exception(std::error_code ec);

Constructs a ``sycl::exception``.

.. rubric:: Constructors 2-3

::

  exception(std::error_code ec, const std::string& what_arg);

  exception(std::error_code ec, const char* what_arg);

Constructs a ``sycl::exception``. The string returned by
``what()`` is guaranteed to contain ``what_arg`` as a substring.

.. rubric:: Constructor 4

::

  exception(int ev, const std::error_category& ecat);

Constructs a ``sycl::exception`` with the error code ``ev``
and the underlying error category ``ecat``.

.. rubric:: Constructors 5-6

::

  exception(int ev, const std::error_category& ecat, const std::string& what_arg);

  exception(int ev, const std::error_category& ecat, const char* what_arg);

Constructs a ``sycl::exception`` with the error code ``ev``
and the underlying error category ``ecat``. The string
returned by ``what()`` is guaranteed to contain ``what_arg``
as a substring.

.. rubric:: Constructor 7

::

  exception(sycl::context ctx, std::error_code ec);

Constructs a ``sycl::exception`` with an associated :ref:`context` ``ctx``.

.. rubric:: Constructors 8-9

::

  exception(sycl::context ctx, std::error_code ec, const std::string& what_arg);

  exception(sycl::context ctx, std::error_code ec, const char* what_arg);

Constructs a ``sycl::exception`` with an associated
:ref:`context` ``ctx``. The string returned by ``what()``
is guaranteed to contain ``what_arg`` as a substring.

.. rubric:: Constructor 10

::

  exception(sycl::context ctx, int ev, const std::error_category& ecat);

Constructs a ``sycl::exception`` with an associated :ref:`context` ``ctx``,
the error code ``ev`` and the underlying error category ``ecat``.

.. rubric:: Constructors 11-12

::

  exception(sycl::context ctx, int ev, const std::error_category& ecat,
            const std::string& what_arg);

  exception(sycl::context ctx, int ev, const std::error_category& ecat,
            const char* what_arg);

Constructs a ``sycl::exception`` with an associated :ref:`context` ``ctx``,
the error code ``ev`` and the underlying error category ``ecat``. The string
returned by ``what()`` is guaranteed to contain ``what_arg`` as a substring.


Member functions
================

``code``
--------

::

  const std::error_code& code() const noexcept;

Returns the error code stored inside the ``sycl::exception``.

``category``
------------

::

  const std::error_category& category() const noexcept;

Returns the error category of the error code
stored inside the ``sycl::exception``.

``what``
--------

::

  const char* what() const;

Returns an implementation-defined non-null constant
C-style string that describes the error that
triggered the ``sycl::exception``.

``has_context``
---------------

::

  bool has_context() const noexcept;

Returns ``true`` if this ``sycl::exception`` has an
associated :ref:`context` and ``false`` if it does not.

``get_context``
---------------

::

  sycl::context get_context() const;

Returns the :ref:`context` that is associated with this
``sycl::exception`` if one is available. Must throw an
``sycl::exception`` with the ``sycl::errc::invalid``
error code if this ``sycl::exception`` does not
have a :ref:`context`.

========================
``sycl::exception_list``
========================

::

  namespace sycl {

  // Used as a container for a list of asynchronous exceptions
  class exception_list {
  public:
    using value_type = std::exception_ptr;
    using reference = value_type&;
    using const_reference = const value_type&;
    using size_type = std::size_t;
    using iterator = /*unspecified*/;
    using const_iterator = /*unspecified*/;

    size_type size() const;
    iterator begin() const; // first asynchronous exception
    iterator end() const;   // refer to past-the-end last asynchronous exception
  };

  } // namespace sycl

The ``sycl::exception_list`` class is also available
in order to provide a list of synchronous and
asynchronous exceptions.


Member functions
================

``size``
--------

::

  size_t size() const;

Returns the size of the list.

``begin``
---------

::

  iterator begin() const;

Returns an iterator to the beginning of the list
of asynchronous exceptions.


``end``
-------

::

  iterator end() const;

Returns an iterator to the end of the list of
asynchronous exceptions.


==============
``sycl::errc``
==============

::

  enum class errc : /* unspecified */ {
    success = 0,
    runtime,
    kernel,
    accessor,
    nd_range,
    event,
    kernel_argument,
    build,
    invalid,
    memory_allocation,
    platform,
    profiling,
    feature_not_supported,
    kernel_not_supported,
    backend_mismatch
  };

  std::error_code make_error_code(errc e) noexcept;

  const std::error_category& sycl_category() noexcept;

  } // namespace sycl

  namespace std {

  template <> struct is_error_code_enum</* see below */> : true_type {};

  } // namespace std


A specialization of ``std::is_error_code_enum`` must be
defined for ``sycl::errc`` that inherits from ``std::true_type``.



Standard SYCL Error Codes
=========================

.. list-table::
  :header-rows: 1

  * - Standard SYCL Error Code
    - Description
  * - ``success``
    - The implementation never throws an ``sycl::exception`` with
      this error code, but it is defined to ensure that no other
      error code has the value zero. An application can construct
      an ``std::error_code`` with this code to indicate "not an error".
  * - ``runtime``
    - Generic runtime error.
  * - ``kernel``
    - Error that occurred before or while enqueuing the :ref:`kernel`.
  * - ``nd_range``
    - Error regarding the :ref:`nd_range` specified for the :ref:`kernel`.
  * - ``accessor``
    - Error regarding the :ref:`command-accessor` objects defined.
  * - ``event``
    - Error regarding associated ``sycl::event`` objects.
  * - ``kernel_argument``
    - The application has passed an invalid argument to a SYCL
      kernel function. This includes captured variables if the
      SYCL kernel function is a lambda function.
  * - ``build``
    - Error from an online compile or link operation when compiling,
      linking, or building a kernel bundle for a device.
  * - ``invalid``
    - A catchall error which is used when the application passes an
      invalid value as a parameter to a SYCL API function or calls
      a SYCL API function in some invalid way.
  * - ``memory_allocation``
    - Error on memory allocation on the :ref:``device`` for a :ref:`kernel`.
  * - ``platform``
    - The :ref:`platform` will trigger this exception on error.
  * - ``profiling``
    - The SYCL runtime will trigger this error if there is an
      error when profiling info is enabled.
  * - ``feature_not_supported``
    - Exception thrown when host code uses an optional feature
      that is not supported by a device.
  * - ``kernel_not_supported``
    - Exception thrown when a kernel uses an optional feature
      that is not supported on the device to which it is
      enqueued. This exception is also thrown if a command group
      is bound to a kernel bundle, and the bundle does not
      contain the kernel invoked by the command group.
  * - ``backend_mismatch``
    - The application has called a backend interoperability
      function with mismatched backend information. For example,
      requesting information specific to backend A from a SYCL
      object that comes from backend B causes this error.


Helper functions
================

``sycl_category``
-----------------

::

  const std::error_category& sycl_category() noexcept;

Obtains a reference to the static error category object for
SYCL errors. This object overrides the virtual function
``std::error_category::name()`` to return a pointer to
the string ``"sycl"``. When the implementation throws
an ``sycl::exception`` object ``ex`` with this category,
the error code value contained by the exception
(``ex.code().value()``) is one of the enumerated values
in ``sycl::errc``.

``make_error_code``
-------------------

::

  std::error_code make_error_code(sycl::errc e) noexcept;

Constructs an error code using ``e`` and ``sycl::sycl_category()``.

.. _exception-handling-example:

=========
Example 1
=========

Catching asynchronous exceptions for incorrect range construction.

.. literalinclude:: /examples/exception-handling.cpp
   :lines: 5-
   :linenos:

Output:

.. literalinclude:: /examples/exception-handling.out
   :language: none
   :lines: 5-
