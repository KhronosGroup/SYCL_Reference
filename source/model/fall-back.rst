.. _fall-back:

Fall Back
=========


Typically, a command group is submitted and executed on the designated
command queue; however, there may be cases where the command queue is
unable to execute the group. In these cases, it is possible to specify a
fall back command queue for the command group to be executed upon. This
capability is handled by the runtime. This fallback mechanism is
detailed in the SYCL Specification.

The following code fails due to the size of the workgroup when executed
on Intel Processor Graphics, such as Intel HD Graphics 530. The SYCL
specification allows specifying a secondary queue as a parameter to the
submit function and this secondary queue is used if the device kernel
runs into issues with submission to the first device.

.. literalinclude:: /examples/fall-back.cpp
   :linenos:		    

.. seealso::

   * :ref:`queue`
