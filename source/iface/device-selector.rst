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

****************
Device selectors
****************

.. rst-class:: api-class
	       
===============
device_selector
===============

::
   
  class device_selector();

.. rubric:: Member functions
   
====================  =======================
`(constructors)`_     constructs a device_selector
select_device_     
====================  =======================

.. rubric:: Nonmember functions

=================  ===
operator()
=================  ===


(constructors)
==============

::
   
  device_selector(const device_selector &rhs);
  device_selector &operator=(const device_selector &rhs);


.. rubric:: Parameters

=================  ===
rhs                device 
=================  ===

select_device
=============

::
   
  device select_device() const;

   
operator()
==========

::
   
  virtual int operator()(const device &device) const = 0;

.. rubric:: Parameters

=================  ===
device
=================  ===


.. rst-class:: api-class
	       
================
default_selector
================

::
   
   class default_selector;

Selects a SYCL device based on a implementation-defined
heuristic. Selects a :term:`host device` if no other device can be
found.
   
.. rst-class:: api-class
	       
============
gpu_selector
============

::
   
   class gpu_selector;

Selects a GPU.   

.. _gpu-selector-example:

.. rubric:: Example

.. literalinclude:: /examples/gpu-selector.cpp

Output on a system without a GPU

.. literalinclude:: /examples/gpu-selector.out
		    
.. rst-class:: api-class
	       
====================
accelerator_selector
====================

::
   
   class accelerator_selector;

Selects an accelerator.

.. rubric:: Example

See :ref:`gpu-selector-example` for the use of a pre-defined selector.

.. rst-class:: api-class
	       
============
cpu_selector
============

::
   
   class cpu_selector;

Select a CPU device.

.. rubric:: Example

See :ref:`gpu-selector-example` for the use of a pre-defined selector.


.. rst-class:: api-class
	       
=============
host_selector
=============

::
   
   class host_selector;

.. rubric:: Example

See :ref:`gpu-selector-example` for the use of a pre-defined selector.
	    
