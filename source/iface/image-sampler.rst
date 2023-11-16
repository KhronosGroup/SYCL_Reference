..
  Copyright 2020 The Khronos Group Inc.
  SPDX-License-Identifier: CC-BY-4.0

**************
Image samplers
**************

.. seealso:: |SYCL_SPEC_IMAGE_SAMPLER|

.. _image_sampler:

=======================
``sycl::image_sampler``
=======================

::

  namespace sycl {

  struct image_sampler {
    addressing_mode addressing;
    coordinate_normalization_mode coordinate;
    filtering_mode filtering;
  };

  } // namespace sycl

The ``sycl::image_sampler`` struct contains a configuration
for sampling a :ref:`sampled_image`.

The members of this struct are defined by the following tables.

=========================
``sycl::addressing_mode``
=========================

::

  namespace sycl {

  enum class addressing_mode : /* unspecified */ {
    mirrored_repeat,
    repeat,
    clamp_to_edge,
    clamp,
    none
  };

  } // namespace sycl

.. list-table::
  :header-rows: 1

  * - Addressing mode
    - Description
  * - ``sycl::addressing_mode::mirrored_repeat``
    - Out of range coordinates will be flipped at every integer junction.

      This addressing mode can only be used with normalized coordinates.
      If normalized coordinates are not used, this addressing mode may
      generate image coordinates that are undefined.
  * - ``sycl::addressing_mode::repeat``
    - Out of range image coordinates are wrapped to the valid range.

      This addressing mode can only be used with normalized coordinates.
      If normalized coordinates are not used, this addressing mode may
      generate image coordinates that are undefined.
  * - ``sycl::addressing_mode::clamp_to_edge``
    - Out of range image coordinates are clamped to the extent.
  * - ``sycl::addressing_mode::clamp``
    - Out of range image coordinates will return a border color.
  * - ``sycl::addressing_mode::none``
    - For this addressing mode the programmer guarantees that
      the image coordinates used to sample elements of the
      image refer to a location inside the image; otherwise
      the results are undefined.

========================
``sycl::filtering_mode``
========================

::

  namespace sycl {

  enum class filtering_mode : /* unspecified */ {
    nearest,
    linear
  };

  } //namespace sycl

.. list-table::
  :header-rows: 1

  * - Filtering mode
    - Description
  * - ``sycl::filtering_mode::nearest``
    - Chooses a color of nearest pixel.
  * - ``sycl::filtering_mode::linear``
    - Performs a linear sampling of adjacent pixels.

=======================================
``sycl::coordinate_normalization_mode``
=======================================

::

  namespace sycl {

  enum class coordinate_normalization_mode : /* unspecified */ {
    normalized,
    unnormalized
  };

  } // namespace sycl

.. list-table::
  :header-rows: 1

  * - Coordinate normalization mode
    - Description
  * - ``sycl::coordinate_normalization_mode::normalized``
    - Normalizes image coordinates.
  * - ``sycl::coordinate_normalization_mode::unnormalized``
    - Does not normalize image coordinates.
