.. _memory-objects:

Memory Objects
==============


Memory objects are either buffers or images.


- :ref:`iface-buffers` object - a one, two, or three dimensional array of elements.
  Buffers can be accessed via lower level C++ pointer types. For
  further information on buffers, see the `SYCL Specification`_.
- :ref:`iface-images` object - a formatted opaque memory object stored in a type
  specific and optimized fashion. Access occurs through built-in
  functions. Image objects typically pertain to pictures comprised of
  pixels stored in a format such as RGB (red, green, blue intensity).
  For further information on images, see the `SYCL Specification`_.

.. seealso::

   * :ref:`data-access`
