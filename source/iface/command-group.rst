**************
Command groups
**************

.. _command_group-function-object:

===============================
 Command group function object
===============================

.. todo:: Explain
	  
.. _command_group:

.. rst-class:: api-class

===============
 command_group
===============

::

   class command_group;

.. member-toc::

(constructors)
==============

::

  template <typename functorT>
  command_group(queue &primaryQueue, const functorT &lambda);
  template <typename functorT>
  command_group(queue &primaryQueue, queue &secondaryQueue,
                const functorT &lambda);

events
======

::
   
  event start_event();
  event kernel_event();
  event complete_event();

