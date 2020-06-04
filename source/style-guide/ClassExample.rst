.. include:: ../include/defs.txt

.. |params2| replace:: Parameters


============
ClassExample
============

.. rubric:: |params|

.. rubric:: |params2|

::

   template<
       class T1
       class T2
   > class ClassExample;   

This is the description of the class. It is followed by a set of
tables for template parameters and class members. This is followed by
the member functions, one section each.


..  Tables begin and end with ===== =====. Text in the last column can
    be longer than the ====. Text in other columns cannot be longer
    than the ===== for their column. Wrap names in ```` so they will
    be in fixed width font.


.. rubric:: Template parameters

| ``T1`` - description of parameter
| ``T2`` - description of parameter

.. rubric:: Member functions


.. The _ suffix on the function name makes it into a link to a
   section that describes the function. The target must be in the same
   file. (Constructor) needs `` because of the special characters: ()
   
.. First word of the description is always a verb.

================  ===========================
`(constructor)`_  constructs a ClassExample
fun1              checks ...
================  ===========================

.. Non-member functions are static functions and operator overloads

.. rubric:: Non-member functions

   
=============  =============
`operator+`_   Adds ...
fun3_          Queries ...
=============  =============

.. rubric:: Example

Describe the example...

.. Using literalinclude pulls in the code from a separate file.  This
   makes it possible to use the cpp extension and then the editor will
   indent it correctly.

.. literalinclude:: /examples/get-platforms.cpp

.. Descriptions of all the member functions follows, each in their own
   section.

(constructor)
=============

.. Group all the overloads together. Use sphinx footnotes if you want
   to have text specific to one function.

::

  ClassExample();

.. parsed-literal::
   
  ClassExample(int a);            [#onearg]_

.. parsed-literal::
   
  ClassExample(int a, int b);     [#twoarg]_

Description of the function. The parameters are in a table below. We
have a single table for all the overloads.

.. [#onearg] Describe constructor with one arg
.. [#twoarg] Describe constructor with two args

.. rubric:: Parameters

| ``a`` - An argument called a
| ``b`` - An argument called b


Description of the functions. Overloads are grouped together and may
have footnotes for overload-specific description.

.. rubric:: Template parameters

| ``T`` - A parameter called T

.. rubric:: Parameters
   
| ``a`` - A parameter called a


.. rubric:: Example

A member function can have its own example
   
operator+
=========

fun3
====

::

  void set_write_back(bool flag = true);

Description

.. rubric:: Template parameters

| ``x`` -

.. rubric:: Parameters

| ``y`` -

.. rubric:: Returns
	    
.. _`cppreference style`: https://en.cppreference.com/w/Help:Manual_of_style
