********
Samplers
********

==============
 address_mode
==============

::

  enum class addressing_mode: unsigned int {
      mirrored_repeat,
      repeat,
      clamp_to_edge,
      clamp,
      none
  };


================
 filtering_mode
================

::
   
  enum class filtering_mode: unsigned int {
     nearest,
     linear
  };

===============================
 coordinate_normalization_mode
===============================

::

  enum class coordinate_normalization_mode : unsigned int {
     normalized,
     unnormalized
  };

.. rst-class:: api-class
	       
=========
 sampler
=========

::

   class sampler;

================
 (constructors)
================

::
   
  sampler(coordinate_normalization_mode normalizationMode,
          addressing_mode addressingMode, filtering_mode filteringMode,
          const property_list &propList = {});

  sampler(cl_sampler clSampler, const context &syclContext);

get_address_mode
================

::

  addressing_mode get_addressing_mode() const;


get_filtering_mode
==================

::

   filtering_mode get_filtering_mode() const;


get_coordinate_normalization_mode
=================================

::

   coordinate_normalization_mode get_coordinate_normalization_mode() const;
