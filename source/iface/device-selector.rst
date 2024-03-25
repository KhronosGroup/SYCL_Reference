..
  Copyright 2024 The Khronos Group Inc.
  SPDX-License-Identifier: CC-BY-4.0

.. _device-selectors:
.. _device_selector:

****************
Device selectors
****************

Device selectors allow the SYCL runtime to choose the device.

A device selector can be passed to :ref:`queue`, :ref:`platform`, and
other constructors to control the selection of a device. A program may
use `Built-in Device Selectors`_ or define its own device selector for
full control.

The interface for a device selector is any object that meets the C++ named
requirement ``Callable`` taking a ``const`` :ref:`device` reference and
returning a value implicitly convertible to a ``int``.

At any point where the SYCL runtime needs to select a SYCL device using
a device selector, the system queries all root devices from all SYCL
backends in the system, calls the device selector on each device and
selects the one which returns the highest score. If the highest
value is strictly negative no device is selected.

In places where only one device has to be picked and the high score is
obtained by more than one device, then one of the tied devices will be
returned, but which one is not defined and may depend on enumeration
order, for example, outside the control of the SYCL runtime.


.. _built-in-device-selectors:

=========================
Built-in Device Selectors
=========================

Standard device selectors included with all SYCL implementations:

.. list-table::

  * - ``sycl::default_selector_v``
    - Select a SYCL device from any supported SYCL backend based on an implementation-defined
      heuristic. Since all implementations must support at least one device, this selector must always return a device.
  * - ``sycl::gpu_selector_v``
    - Select a SYCL device from any supported SYCL backend for which the device type is ``info::device_type::gpu``.
  * - ``sycl::accelerator_selector_v``
    - Select a SYCL device from any supported SYCL backend for which the device type is ``info::device_type::accelerator``.
  * - ``sycl::cpu_selector_v``
    - Select a SYCL device from any supported SYCL backend for which the device type is ``info::device_type::cpu``.
  * - ::

        __unspecified_callable__
        sycl::aspect_selector(const std::vector<aspect>& aspectList,
                              const std::vector<aspect>& denyList = {});

        template <typename... AspectList>
        __unspecified_callable__
        sycl::aspect_selector(AspectList... aspectList);

        template <aspect... AspectList>
        __unspecified_callable__ sycl::aspect_selector();

    - The free function ``sycl::aspect_selector`` has several overloads, each of which returns a selector object that selects a SYCL
      device from any supported SYCL backend which contains all the requested aspects.
      If no aspects are passed in, the generated selector behaves like ``sycl::default_selector``.

      Required aspects can be passed in as a vector, as function arguments, or as template parameters, depending on the
      function overload. The function overload that takes ``aspectList`` as a vector takes another vector argument ``denyList``
      where the user can specify all the aspects that have to be avoided.

The SYCL class constructor using ``sycl::gpu_selector_v``,
``sycl::accelerator_selector_v``, ``sycl::cpu_selector_v``,
or ``sycl::aspect_selector`` must throw an exception with
the ``sycl::errc::runtime`` error code if no device matching
the requirement can be found.

.. _device-selector-SYCL121:

==============================
Device Selectors in SYCL 1.2.1
==============================

In SYCL 1.2.1 the predefined device selectors were
types that had to be instantiated to be used.

To simplify porting code using the old type instantiations, a
backward-compatible API is still provided, such as ``sycl::default_selector``.

The new predefined device selectors have their new names appended
with "_v" to avoid conflicts, thus following the naming style used by
traits in the C++ standard library.

.. seealso:: |SYCL_SPEC_DEVICE_SELECTORS|

.. _device-selector-example:

=========
Example 1
=========

.. literalinclude:: /examples/gpu-selector.cpp
   :lines: 5-
   :linenos:

Output on a system without a GPU:

.. literalinclude:: /examples/gpu-selector.out
   :lines: 5-
