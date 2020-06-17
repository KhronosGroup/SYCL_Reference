.. _iface-error-handling:

**********
Exceptions
**********

=========
exception
=========

::
   
   class exception;

.. rubric:: Member functions

============  ===	    
what_
has_context_
get_context_
get_cl_code_
============  ===	    

   
what
====

::
   
   const char *what() const;

has_context
===========

::

   bool has_context() const;


get_context
===========

::

   context get_context() const;


get_cl_code
===========

::

   cl_int get_cl_code() const;


==============
exception_list
==============

::

   class exception_list;

.. rubric:: Member types

===============  ===
value_type
reference
const_reference
size_type
iterator
const_iterator
===============  ===

.. rubric:: Member functions

============  ===	    
size_
begin_
end_
============  ===	    

size
====

::

   size_type size() const;

begin
=====

::

   iterator begin() const;

first asynchronous exception

end
===

::

   iterator end() const;

Refers to past-the-end last asynchronous exception

==================
Derived exceptions
==================

::

   class runtime_error : public exception;
   class kernel_error : public runtime_error;
   class accessor_error : public runtime_error;
   class nd_range_error : public runtime_error;
   class event_error : public runtime_error;
   class invalid_parameter_error : public runtime_error;
   class device_error : public exception;
   class compile_program_error : public device_error;
   class link_program_error : public device_error;
   class invalid_object_error : public device_error;
   class memory_allocation_error : public device_error;
   class platform_error : public device_error;
   class profiling_error : public device_error;
   class feature_not_supported : public device_error;

   

