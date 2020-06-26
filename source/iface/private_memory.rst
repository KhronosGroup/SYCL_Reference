================
 private_memory
================

::

   template <typename T, int Dimensions = 1>
   class private_memory;
   
.. member-toc::

(constructors)
==============

::

  private_memory(const group<Dimensions> &);

(operators)
===========

::

  T &operator()(const h_item<Dimensions> &id);
