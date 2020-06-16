..
  // Copyright (c) 2011-2020 The Khronos Group, Inc.
  //
  // Licensed under the Apache License, Version 2.0 (the License);
  // you may not use this file except in compliance with the License.
  // You may obtain a copy of the License at
  //
  //     http://www.apache.org/licenses/LICENSE-2.0
  //
  // Unless required by applicable law or agreed to in writing, software
  // distributed under the License is distributed on an AS IS BASIS,
  // WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  // See the License for the specific language governing permissions and
  // limitations under the License.

************************
 Device selection class
************************

=========================
Device selector interface
=========================

::
   
  class device_selector();

``device_selector`` is an abstract class that cann

.. rubric:: Member functions
   
====================  =======================
`(constructor)`_      constructs a device_selector
(destructor)          destroys the device_selector
select_device_     
====================  =======================

.. rubric:: Nonmember functions

=================  =======================
operator()
=================  =======================


(constructor)
=============

::
   
  device_selector(const device_selector &rhs);

::
   
  device_selector &operator=(const device_selector &rhs);

Constructs a ``device_selector`` from another ``device_selector``

.. rubric:: Parameters

| ``rhs`` - device 

select_device
=============

::
   
  device select_device() const;

.. rubric:: Returns
   
operator()
==========

::
   
  virtual int operator()(const device &device) const = 0;

.. rubric:: Parameters

| ``device`` -

.. rubric:: Returns

=======================
Derived device selector
=======================

default_selector
=================

::
   
   class default_selector;

Selects a SYCL device based on a implementation-defined
heuristic. Selects a :term:`host device` if no other device can be
found.
   
gpu_selector
============

::
   
   class gpu_selector;

Selects a GPU.   

.. rubric:: Exceptions

Throws a ``runtime_error`` if a GPU device cannot be found

.. _gpu-selector-example:

.. rubric:: Example

.. literalinclude:: /examples/gpu-selector.cpp

Output on a system without a GPU

.. literalinclude:: /examples/gpu-selector.out
		    
accelerator_selector
====================

::
   
   class accelerator_selector;

Selects an accelerator.

.. rubric:: Exceptions

Throws a ``runtime_error`` if an accelerator device cannot be found.

.. rubric:: Example

See :ref:`gpu-selector-example` for the use of a pre-defined selector.

cpu_selector
============

::
   
   class cpu_selector;

Select a CPU device.

.. rubric:: Exceptions

Throws a ``runtime_error`` if a CPU device cannot be found.

.. rubric:: Example

See :ref:`gpu-selector-example` for the use of a pre-defined selector.


host_selector
=============

::
   
   class host_selector;

.. rubric:: Example

See :ref:`gpu-selector-example` for the use of a pre-defined selector.
	    
