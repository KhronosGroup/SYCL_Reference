..
  Copyright 2023 The Khronos Group Inc.
  SPDX-License-Identifier: CC-BY-4.0

.. _syncronization-primitives:

**************************
Synchronization primitives
**************************

When the user wants to use the :ref:`buffer` simultaneously
in the SYCL runtime and their own code (e.g. a multi-threaded
mechanism) and wants to use manual synchronization without
using a :ref:`host_accessor`, a ``std::mutex`` can be passed
to the :ref:`buffer` constructor via the right property.

The runtime promises to lock the mutex whenever the data is
in use and unlock it when it no longer needs it:

::

  {
    std::mutex m;
    auto shD = std::make_shared<int>(42)
    sycl::buffer b { shD, { sycl::property::buffer::use_mutex { m } } };
    {
      std::lock_guard lck { m };
      // User accesses the data
      do_something(shD);
      /* m is unlocked when lck goes out of scope, by normal end of this
        block but also if an exception is thrown for example */
    }
  }

When the runtime releases the ``std::mutex`` the user is guaranteed that the
data was copied back on the ``std::shared_pointer``, unless the final data
destination has been changed using the member function ``set_final_data()``.

.. seealso:: |SYCL_SYNC_PRIMITIVES|
