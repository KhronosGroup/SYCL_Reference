..
  Copyright 2020 The Khronos Group Inc.
  SPDX-License-Identifier: CC-BY-4.0

********
Samplers
********

.. seealso:: |SYCL_SPEC_SAMPLER|

=====================
sycl::addressing_mode
=====================

::

  enum class addressing_mode: unsigned int {
      mirrored_repeat,
      repeat,
      clamp_to_edge,
      clamp,
      none
  };


====================
sycl::filtering_mode
====================

::
   
  enum class filtering_mode: unsigned int {
     nearest,
     linear
  };

===================================
sycl::coordinate_normalization_mode
===================================

::

  enum class coordinate_normalization_mode : unsigned int {
     normalized,
     unnormalized
  };

.. rst-class:: api-class
	       
=============
sycl::sampler
=============

::

   class sampler;

(constructors)
==============

::
   
  sampler(sycl::coordinate_normalization_mode normalizationMode,
          sycl::addressing_mode addressingMode, sycl::filtering_mode filteringMode,
          const sycl::property_list &propList = {});

  sampler(cl_sampler clSampler, const sycl::context &syclContext);

get_address_mode
================

::

  sycl::addressing_mode get_addressing_mode() const;


get_filtering_mode
==================

::

   sycl::filtering_mode get_filtering_mode() const;


get_coordinate_normalization_mode
=================================

::

   sycl::coordinate_normalization_mode get_coordinate_normalization_mode() const;
