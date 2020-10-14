..
  Copyright 2020 The Khronos Group Inc.
  SPDX-License-Identifier: CC-BY-4.0

.. _access-mode:

==================
sycl::access::mode
==================

::

  enum class mode {
    read = 1024,
    write,
    read_write,
    discard_write,
    discard_read_write,
    atomic
  };

.. _access-target:

====================
sycl::access::target
====================

::
   
  enum class target {
    global_buffer = 2014,
    constant_buffer,
    local,
    image,
    host_buffer,
    host_image,
    image_array
  };


  
