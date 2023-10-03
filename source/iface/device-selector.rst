..
  Copyright 2020 The Khronos Group Inc.
  SPDX-License-Identifier: CC-BY-4.0

.. _device-selectors:
.. _device_selector:

****************
Device selectors
****************

Device selectors allow the SYCL runtime to choose the device.

A device selector can be passed to :ref:`queue`, :ref:`platform`, and
other constructors to control the selection of a device. A program may
use `Built-in Device Selectors`_ or define its own device_selector for
full control.

Interface for a device selector is any object that meets the C++ named
requirement ``Callable`` taking a const :ref:`device` reference and
returning a value implicitly convertible to a int.

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

===========================
Built-in Device Selectors
===========================

Standard device selectors included with all SYCL implementations:

.. list-table::

  * - ``default_selector_v``
    - Select a SYCL device from any supported SYCL backend based on an implementation-defined
      heuristic. Must select the host device if no other suitable device can be found.
  * - ``gpu_selector_v``
    - Select a SYCL device from any supported SYCL backend for which the device type is ``info::device::device_type::gpu``.
  * - ``accelerator_selector_v``
    - Select a SYCL device from any supported SYCL backend for which the device type is ``info::device_type::accelerator``.
  * - ``cpu_selector_v``
    - Select a SYCL device from any supported SYCL backend for which the device type is ``info::device_type::cpu``.
  * - ::

        __unspecified_callable__
        aspect_selector(const std::vector<aspect>& aspectList,
                        const std::vector<aspect>& denyList = {});

        template <typename... AspectList>
        __unspecified_callable__ aspect_selector(AspectList... aspectList);

        template <aspect... AspectList>
        __unspecified_callable__ aspect_selector();

    - The free function ``aspect_selector`` has several overloads, each of which returns a selector object that selects a SYCL
      device from any supported SYCL backend which contains all the requested aspects.
      If no aspects are passed in, the generated selector behaves like ``default_selector``.

      Required aspects can be passed in as a vector, as function arguments, or as template parameters, depending on the
      function overload. The function overload that takes aspectList as a vector takes another vector argument denyList
      where the user can specify all the aspects that have to be avoided.

The SYCL class constructor using ``gpu_selector_v``,
``accelerator_selector_v``, ``cpu_selector_v``, and ``aspect_selector``
must throw an exception with the ``errc::runtime`` error code if no
device matching the requirement can be found.

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
