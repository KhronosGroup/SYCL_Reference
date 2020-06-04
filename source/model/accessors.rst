.. _model-accessors:

Accessors
=========

Accessors provide access to buffers and images in the host or inside
the kernel and also communicate data dependencies between the
application and different kernels. The accessor communicates the data
type, size, target, and access mode. To enable good performance, pay
particular attention to the target because the accessor specifies the
memory type from the choices in the SYCL memory model.

The targets associated with buffers are:

-  global_buffer
-  host_buffer
-  constant_buffer
-  local

The targets associated with images are:

-  image
-  host_image
-  image_array

Image access must also specify a channel order to communicate the format
of the data being read. For example, an image may be specified as a
``float4``, but accessed with a channel order of RGBA.

The access mode impacts correctness as well as performance and is one
of ``read``, ``write``, ``read_write``, ``discard_write``,
``discard_read_write``, or ``atomic``. Mismatches in access mode and
actual memory operations such as a ``write`` to a ``buffer`` with
access mode ``read`` can result in compiler diagnostics as well as
erroneous program state. The ``discard_write`` and
``discard_read_write`` access modes can provide performance benefits
for some implementations. For further details on accessors, see the
`SYCL Specification`_.

.. seealso::

   * :ref:`iface-accessors`
