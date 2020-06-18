.. _sample-program:

============================
 Anatomy of a DPC++ Program
============================

The following example uses the oneAPI programming model to add 2
vectors. When compiled and executed, the sample program computes the
1024 element vector add in parallel on the accelerator. This assumes
the accelerator has multiple compute elements capable of executing in
parallel.  This sample illustrates the models that software
developers need to employ in their program. We identify sections
of code by line number and discuss their role, highlighting their
relation to the programming and execution models.

.. note::

   This sample code is intended to illustrate the models that comprise
   the oneAPI program model; it is not intended to be a typical
   program.

.. literalinclude:: /examples/vector-add.cpp
   :linenos:

With the following output:

.. literalinclude:: /examples/vector-add.out
		    
DPC++ is :term:`single source`, which means the :term:`host code` and
the :term:`device code` can be placed in the same file and compiled
with a single invocation of the compiler.  Therefore, when examining a
DPC++ program, the first step is to understand the delineation between
host code and device code.  DPC++ programs have 3 different scopes.

- :term:`kernel scope`: Function that executes on the device
- :term:`command group scope`: Kernel function and host code to launch
  it on the device
- :term:`application scope`: Code that executes on the host

Application scope includes all program lines not in the command group
scope. The application scope is responsible for creating DPC++ queues
that are connected to devices (line 32), allocating data that can be
accessed from the device (lines 28-30), and submit tasks to the queues
(line 34).

Kernel scope is the body of the lambda function found on lines
40-42. Each invocation of the kernel function adds a single element of
the ``a`` and ``b`` vectors.

.. literalinclude:: /examples/vector-add.cpp
   :lines: 39-42
   :lineno-match:
   :emphasize-lines: 2-3

Command group scope can be found on lines 34-43. A command group
contains a single kernel function and code to coordinate the passing
of data and control between the host and the device. Lines 35-37
create accessors, which enable the kernel to access the data in the
buffers created on lines 28-30. The ``parallel_for`` on line 39
launches an instance of the kernel on every element of an index space
and passes the coordinates of the point in the index space to the
function. The index space is defined on line 26. It is a one-dimensional
space that ranges from 0 to 1023.

.. literalinclude:: /examples/vector-add.cpp
   :lines: 34-43
   :lineno-match:

Now we walk through line by line. Every DPC++ program must include
sycl.hpp (line 3). All types are in the ``cl::sycl`` namespace and the
line 4 namespace command is a convenience.

Lines 8-23 illustrate the use of the **platform model** by enumerating all
the platforms available on the system and the devices contained in the
platform.

Lines 28-30 and 35-37 show the role of the **memory model**. Device
and host do not access the same memory by default. The memory model
defines the rules for access. Lines 47 allocates memory on the host
for the vectors. Lines 28-30 wrap buffers around that memory. Kernels
read/write buffer data via the accessors that are created on lines 35-37. The
accessor on line 35 gives the kernel write access to buffer names as
`c_device`, and the accessors on lines 36 & 37 give the kernel read
access to the other buffers.

.. literalinclude:: /examples/vector-add.cpp
   :lines: 28-37
   :lineno-match:
   :emphasize-lines: 1-3,8-10

Lines 32-34 demonstrate the use of the **application execution
model**. A command group is submitted to a queue on line 34. The SYCL
runtime launches the kernel function in the command group on the
device connected to the queue when the requirements of the command
group are met. For this example, the accessors create the requirement
that the buffers be accessible on the device. Queueing the command
group triggers the copying of the data contained in the buffer from
host memory to the device. The runtime launches the kernel when the
data movements complete.

Lines 40-42 illustrate the function of **kernel execution model**. The
``parallel_for`` launches an instance of the kernel function for every
point in the index space denoted by ``a_size``. The instances are
distributed among the processing elements of the device.

DPC++ uses C++ scopes and object models to
concisely express synchronization. The vectors start in host
memory. When the host memory for the vector is passed to the buffer
constructor on lines 28-30, the buffers take *ownership* of the host
memory and any use of the original host memory is undefined. When the
destructor for the buffer runs because the containing scope ends, the
runtime ensures that kernel accessing the buffer has ended and syncs
the data back to the original host memory.

The next sections discuss in more details those four models:
Platform model, Execution model, Memory model, and Kernel model.


