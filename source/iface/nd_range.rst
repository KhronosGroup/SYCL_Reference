.. rst-class:: api-class
	       
.. _nd_range:


==========
 nd_range
==========

::

   template <int dimensions = 1>
   class nd_range;
   

The ``nd_range`` defines the index space for a work group as well as
the global index space. It is passed to :ref:`handler-parallel_for` to
execute a kernel on a set of work items.


.. rubric:: Template parameters

================  ===
dimensions        Number of dimensions
================  ===


.. member-toc::
   
(constructors)
==============

::

  nd_range(range<dimensions> globalSize, range<dimensions> localSize,
           id<dimensions> offset = id<dimensions>());

Construct an ``nd_range``.

.. rubric:: Parameters

==================  ===
globalSize          dimensions of the entire index space
localSize           dimensions of the work group
offset              Origin of the index space
==================  ===

get_global_range
================

::
   
  range<dimensions> get_global_range() const;

Returns a :ref:`range` defining the index space.

get_local_range
===============

::
   
  range<dimensions> get_local_range() const;

Returns a :ref:`range` defining the index space of a work group.

get_group_range
===============

::

  range<dimensions> get_group_range() const;

Returns a :ref:`range` defining the number of work groups in every dimension.


get_offset
==========

::

  id<dimensions> get_offset() const;

Returns a :ref:`id` defining the offset.
