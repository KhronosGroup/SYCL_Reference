.. _access-mode:

======
 mode
======

::

  enum class mode {
    read = 1024,
    write,
    read_write,
    discard_write,
    discard_read_write,
    atomic
  };

.. rubric:: Namespace

::

   access

   
.. _access-target:

========
 target
========

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

.. rubric:: Namespace

::

   access

  
