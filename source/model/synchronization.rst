.. _synchronization:

Synchronization
===============

It is possible to access a ``buffer`` without employing an
``accessor``, however it should be the rare case. To do so safely, a
``mutex_class`` should be passed when a ``buffer`` is
instantiated. For further details on this method, see the `SYCL
Specification`_.

.. rubric:: Access Targets

===================  =================
Target               Description     
===================  =================
``host_buffer``      Access the buffer on the host.     
``global_buffer``    Access the buffer through global memory on the device.          
``constant_buffer``  | Access the buffer from constant memory on the device.
                     | This may enable some optimization.    
``local``            Access the buffer from local memory on the device.          
``image``            Access the image.     
``image_array``      Access an array of images.     
``host_image``       Access the image on the host.     
===================  =================


.. rubric:: Access Modes

======================  =================
Memory Access Mode      Description     
======================  =================
``read``                Read-only     
``write``               Write-only     
``read_write``          Read and write     
``discard_write``       Write-only access. Previous value is discarded.          
``discard_read_write``  Read and write. Previous value is discarded.     
``atomic``              Provide atomic, one at a time, access.     
======================  =================



.. seealso::

   * :ref:`iface-buffers`
   * :ref:`iface-images`
     
