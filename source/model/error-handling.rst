Error Handling
==============


C++ exception handling is the basis for handling error conditions in the
programming model. Some restrictions on exceptions are in place due to
the asynchronous nature of host and device execution. For example, it is
not possible to throw an exception in kernel scope and catch it (in the
traditional sense) in application scope. Instead, there are a set of
restrictions and expectations in place when performing error handling.
These include:

- At application scope, the full C++ exception handling mechanisms and
  capability are valid as long as there is no expectation that
  exceptions can cross to kernel scope.
- At the command group scope, exceptions are asynchronous with respect
  to the application scope. During command group construction, an
  ``async_handler`` can be declared to handle any exceptions occurring
  during execution in the command group.

.. seealso::

   * :ref:`iface-error-handling`
