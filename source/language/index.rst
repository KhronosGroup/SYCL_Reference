==========
 Language
==========

The host code can be compiled by C++11 and later compilers and take
advantage of supported C++11 and later language features. The device
code requires a compiler that accepts all C++03 language features and
the following C++11 features:

-  Lamdba expressions
-  Variadic templates
-  Alias templates
-  rvalue references
-  std::function, std::string, std::vector

In addition, the device code cannot use the following features:

-  Virtual Functions
-  Virtual Inheritance
-  Exceptions handling – throws and catches between host and device
-  Run Time Type Information (RTTI)
-  Object management employing new and delete operators

The device code is specified via one of three language constructs:
lambda expression, functor, or kernel class. The separation of host
code and device code via these language constructs is natural and
accomplished without language extensions. These different forms of
expressing kernels give the developer flexibility in enmeshing the
host code and device code. For example:

-  To put the kernel code in line with the host code, consider employing
   a lambda expression.
-  To have the device code separate from the host code, but still
   maintain the single source property, consider employing a functor.
-  To port code from OpenCL programs or to ensure a more rigid
   separation between host and device code, consider employing the
   kernel class.

Keywords
========

SYCL does not add any keywords to the C++ language.

Preprocessor Directives and Macros
==================================


Standard C++ preprocessing directives and macros are supported by the
compiler. In addition, the SYCL Specification defines the SYCL specific
preprocessor directives and macros.


The following preprocessor macros are supported by the compiler.


==============================  =================  ========
Macro                           Value              Description
==============================  =================  ========
``SYCL_DUMP_IMAGES``            |true| or |false|  Instructs the runtime to dump the device image       
``SYCL_USE_KERNEL_SPV``         <device binary>    Employ device binary to fulfill kernel launch request       
``SYCL_PROGRAM_BUILD_OPTIONS``  <options>          Used to pass additional options for device program building.    
==============================  =================  ========


Standard Library Classes Required for the Interface
===================================================


The SYCL specification documents a facility to enable vendors to provide
custom optimized implementations. Implementations require aliases for
several STL interfaces. These are summarized as follows:

.. todo:: add STL interfaces
