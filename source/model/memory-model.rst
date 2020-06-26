.. _memory-model:

Memory Model
============


The memory model for oneAPI is based upon the SYCL\* memory model. It
defines how the host and devices interact with memory. It coordinates
the allocation and management of memory between the host and devices.
The memory model is an abstraction that aims to generalize across and
be adaptable to the different possible host and device
configurations. In this model, memory resides upon and is owned by
either the host or the device and is specified by declaring a memory
object. There are two different types of memory objects,
:term:`buffers` and :term:`images`.  Interaction of these memory
objects between the host and device is accomplished via an
:term:`accessor`, which communicates the desired location of access,
such as host or device, and the particular mode of access, such as
read or write.

Consider a case where memory is allocated on the host through a
traditional malloc call. Once the memory is allocated on the host, a
buffer object is created, which enables the host allocated memory to be
communicated to the device. The ``buffer`` class communicates the type
and number of items of that type to be communicated to the device for
computation. Once a buffer is created on the host, the type of access
allowed on the device is communicated via an ``accessor`` object, which
specifies the type of access to the buffer. The general steps are
summarized as:

#. Instantiate a ``buffer`` or ``image`` object.

   The host or device memory for the ``buffer`` or ``image`` is
   allocated as part of the instantiation or relies on previously
   allocated memory on the host.

#. Instantiate an ``accessor`` object.

   The ``accessor`` specifies the required location of access, such as
   host or device, and the particular mode of access, such as read or
   write. It represents dependencies between uses of memory objects.

The following code sample exercises different memory objects and
accessors. The highlighted lines are discussed below.

.. literalinclude:: /examples/memory-model.cpp
   :linenos:
   :emphasize-lines: 8,9,26-31

-  Lines 8 and 9 contain the host allocations of arrays ``a``, ``b``, &
   ``c``. The declaration of ``b`` is as a ``float4`` because it will be
   accessed as an image on the device side.
-  Lines 26 and 27 create an accessor for ``c_device`` that has an
   access mode of ``discard_write`` and a target of ``global_buffer``.
-  Lines 28 and 29 create an accessor for ``a_device`` that has an
   access mode of ``read`` and a target of ``constant_buffer``.
-  Lines 30 and 31 create an accessor for ``b_device`` that has an
   access mode of ``write`` and a target of ``image``.

The accessors specify where and how the kernel accesses these memory
objects. The runtime is responsible for placing the memory objects in
the correct location. Therefore, the runtime may copy data between
host and device to meet the requirements of the accessor target.

Designate accessor targets to optimize the locality of access for a
particular algorithm. For example, private memory can be used for data
that is only accessed by a single work item. Not all combinations of
access targets and access modes are compatible. For details, see the
`SYCL Specification`_.

.. toctree::

   
   memory-objects
   accessors
   synchronization
   unified-shared-memory
   memory-types


.. seealso::

   * :ref:`data-access`
