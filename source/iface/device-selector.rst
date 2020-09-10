..
  Copyright 2020 The Khronos Group Inc.
  SPDX-License-Identifier: CC-BY-4.0

.. _device-selectors:

****************
Device selectors
****************

Devices selectors allow the SYCL runtime to choose the device.

A device selector can be passed to :ref:`queue`, :ref:`platform`, and
other constructors to control the selection of a device. A program may
use `Built-in Device Selectors`_ or define its own device_selector_
for full control.

.. _device_selector:

.. rst-class:: api-class
	       
===============
device_selector
===============

::
   
  class device_selector;

Abstract class for device selectors.

This is the base class for the `Built-in Device Selectors`_. To define
a custom device selector, create a derived class that defines the ()
operator.

.. todo:: Example Custom device selector	    

.. member-toc::


(constructors)
==============

::
   
  device_selector();
  device_selector(const device_selector &rhs);

Construct a device_selector.

A device selector can be created from another by passing ``rhs``.


select_device
=============

::
   
  device select_device() const;

   
Returns the device with the highest score as determined by calling
`operator()`_.

.. rubric:: Exceptions
   
Throws a runtime error if all devices have a negative score.

operator=
=========

::
   
  device_selector &operator=(const device_selector &rhs);

Create a device selector by copying another one.


operator()
==========

::
   
  virtual int operator()(const device &device) const = 0;

Scoring function for devices.

All derived device selectors must define this
operator. `select_device` calls this operator for every device, and
selects the device with highest score. Return a negative score if a
device should not be selected.


.. _built-in-device-selectors:
   
===========================
Built-in Device Selectors
===========================

SYCL provides built-in device selectors for convenience. They use
device_selector_ as a base class.

=====================  ===
default_selector       Selects device according to implementation-defined heuristic or host device if no device can be found.
gpu_selector           Select a GPU
accelerator_selector   Select an accelerator
cpu_selector           Select a CPU device
host_selector          Select the host device
=====================  ===


Create a device selector by copying another one.
		   
.. seealso:: |SYCL_SPEC_DEVICE_SELECTORS|

 .. rubric:: Example

.. literalinclude:: /examples/gpu-selector.cpp
   :lines: 5-
   :linenos:

Output on a system without a GPU:

.. literalinclude:: /examples/gpu-selector.out		    
   :lines: 5-
