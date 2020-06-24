==========
 nd_range
==========

::

   template <int dimensions = 1>
   class nd_range;
   
(constructors)
==============

::

  nd_range(range<dimensions> globalSize, range<dimensions> localSize,
           id<dimensions> offset = id<dimensions>());

get_global_range
================

::
   
  range<dimensions> get_global_range() const;

get_local_range
===============

::
   
  range<dimensions> get_local_range() const;

get_group_range
===============

::

  range<dimensions> get_group_range() const;

get_offset
==========

::

  id<dimensions> get_offset() const;
