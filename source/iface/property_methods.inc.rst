..
  Copyright 2020 The Khronos Group Inc.
  SPDX-License-Identifier: CC-BY-4.0

``has_property``
================

::

  template <typename propertyT>
  bool has_property() const;

.. rubric:: Template parameters

=============  ===
``propertyT``
=============  ===

Returns True if the property type was passed to the constructor.

``get_property``
================

::

  template <typename propertyT>
  propertyT get_property() const;

.. rubric:: Template parameters

=============  ===
``propertyT``
=============  ===

Returns copy of property of passed to the constructor.
