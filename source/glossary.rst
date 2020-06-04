.. _glossary:

Glossary
========

.. glossary::

   accelerator

     Specialized component containing compute resources that can
     quickly execute a subset of operations. Examples include CPU,
     FPGA, GPU. See also: :term:`device`

   accessor

     Interface to read and write data contained in a buffer, image, or
     local memory. Accessors implicitly define the data dependences
     when kernels and the host access a buffer. See :ref:`model-accessors`.

   application scope

     Code that executes on the host.

   buffers

     Encapsulates data that is must be accessed by the device. See
     :ref:`iface-buffers`.

   command group scope

     Code that acts as the interface between the host and device.

   command queue

     Issues command groups concurrently.

   compute unit

     A grouping of processing elements into a ‘core’ that contains
     shared elements for use between the processing elements and with
     faster access than memory residing on other compute units on the
     device.

   device

     An accelerator or specialized component containing compute
     resources that can quickly execute a subset of operations. A CPU
     can be employed as a device, but when it is, it is being employed
     as an accelerator. Examples include CPU, FPGA, GPU. See also:
     :term:`accelerator`

   device code

     Code that executes on the device rather than the host. Device
     code is specified via lambda expression, functor, or kernel
     class.

   fat binary

     Application binary that contains device code for multiple
     devices.  The binary includes both the generic code (SPIR-V
     representation) and target specific executable code.

   fat library

     Archive or library of object code that contains object code for
     multiple devices. The fat library includes both the generic
     object (SPIR-V representation) and target specific object code.

   fat object

     File that contains object code for multiple devices. The fat
     object includes both the generic object (SPIR-V representation)
     and target specific object code.

   host

     A CPU-based system (computer) that executes the primary portion
     of a program, specifically the application scope and command
     group scope.

   host device

     A SYCL device that is always present and usually executes on the
     host CPU.
     
   host code

     Code that is compiled by the host compiler and executes on the
     host rather than the device.

   images

     Formatted opaque memory object that is accessed via built-in
     function. Typically pertains to pictures comprised of pixels
     stored in format like RGB.

   kernel scope

     Code that executes on the device.

   nd-range

     Short for N-Dimensional Range, a group of kernel instances, or
     work item, across one, two, or three dimensions.

   processing element

     Individual engine for computation that makes up a compute unit.

   single source

     Denotes that source code for device and host can be in the same file.

   SPIR-V

     Binary intermediate language for representing graphical-shader
     stages and compute kernels.

   sub-group

     Collection of work-items in a work-group. Arranging computations
     in sub-groups may enables the use of SIMD instructions.

   work-group

     Collection of work-items that execute on a compute unit.

   work-item

     Basic unit of computation for a single point in the index space
     processed by a kernel.

