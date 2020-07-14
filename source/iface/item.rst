.. rst-class:: api-class
	       
.. _item:

======
 item
======

::

   template <int dimensions = 1, bool with_offset = true>
   class item;


Similar to an :ref:`id`, the ``item`` describes the location of a
point in a ``range``. It can be used as an argument to a kernel
function in a :ref:`handler-parallel_for` to identify the work
item. The ``item`` carries more information than than :ref:`id`, such
as the ``range`` of an index space. The interface does not include a
constructor because only the SYCL runtime needs to construct an
``item``.

.. rubric:: Template parameters

==============  ===
dimensions      Number of dimensions in index space
with_offset     True if item has offset
==============  ===

.. member-toc::

get_id
======

::
   
  id<dimensions> get_id() const;
  size_t get_id(int dimension) const;


Returns :ref:`id` associated with ``item``.

get_range
=========

::
   
  range<dimensions> get_range() const;
  size_t get_range(int dimension) const;

Returns :ref:`range` associated with ``item``.


get_offset
==========

::
   
  *Only available when:
   with_offset is true*
   
  id<dimensions> get_offset() const;

Returns offset associated with ``item``.

get_linear_id
=============

::
   
  size_t get_linear_id() const;

Returns the linear id, suitable for mapping the ``id`` to a 1
dimensional array.


operator[]
==========

::
   
  size_t operator[](int dimension) const;

Returns id for dimension ``dimension``.

   
operator()
==========

::
   
  operator item<dimensions, true>() const;

Returns item with offset set to 0.

Only available when ``with_offset`` is False.
