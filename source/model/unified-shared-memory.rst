.. _unified-shared-memory:

Unified Shared Memory
=====================


Unified shared memory provides a pointer-based alternative to the
buffer and accessor programming model.  It provides both explicit and implicit
models for managing memory. In the explicit model, programmers are
responsible for specifying when data should be copied between memory
allocations on the host and allocations on a device. In the implicit
model, the underlying runtime and device drivers are responsible for
automatically migrating memory between the host and a device.

Since unified shared memory does not rely on accessors, dependencies
between operations must be specified using events. Programmers may
either explicitly wait on event objects or use the ``depends_on``
method inside a command group to specify a list of events that must
complete before a task may begin.



