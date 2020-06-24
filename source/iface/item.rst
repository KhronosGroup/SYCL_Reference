======
 item
======

::

   template <int dimensions = 1, bool with_offset = true>
   class item;

.. rubric:: Member functions

=================  ===
get_id_
get_range_
get_offset_
get_linear_id_
=================  ===

.. rubric:: Nonmmber functions

=================  ===
`(operators)`_
=================  ===

get_id
======

::
   
  id<dimensions> get_id() const;
  size_t get_id(int dimension) const;


get_range
=========

::
   
  range<dimensions> get_range() const;
  size_t get_range(int dimension) const;


get_offset
==========

::
   
  *Only available when:
   with_offset is true*
   
  id<dimensions> get_offset() const;


get_linear_id
=============

::
   
  size_t get_linear_id() const;

(operators)
===========

::
   
  size_t operator[](int dimension) const;

  *Only available when:
   with_offset is false*
   
  operator item<dimensions, true>() const;
