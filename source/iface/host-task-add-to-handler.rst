..
  Copyright 2024 The Khronos Group Inc.
  SPDX-License-Identifier: CC-BY-4.0

**********************************
Additions to the ``sycl::handler``
**********************************

This section describes member functions in the command group handler
class that are used with host tasks.

::

  class handler {
    ...

        public:
          template <typename T>
          void host_task(T&& hostTaskCallable); // (1)

    ...
  };

Effects: Enqueues an implementation-defined command to the SYCL runtime
to invoke ``hostTaskCallable`` exactly once. The scheduling of the
invocation of ``hostTaskCallable`` in relation to other commands
enqueued to the SYCL runtime must be in accordance with the dependency
model described in |SYCL_SPEC_MEM_MODEL|. Initializes an
``interop_handle`` object and passes it to ``hostTaskCallable``
when it is invoked if ``std::is_invocable_v<T, interop_handle>``
evaluates to true, otherwise invokes ``hostTaskCallable``
as a nullary function.

.. seealso::

  |SYCL_SPEC_ADDITION_TO_HANDLER|

  :ref:`handler`
