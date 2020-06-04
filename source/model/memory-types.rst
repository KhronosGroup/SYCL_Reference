.. _memory-types:

Memory Types
============


===============  ============
Memory Type      Description     
===============  ============
Constant Memory  | A region of global memory that remains constant during the
                 | execution of a kernel. The host allocates and initializes memory
		 | objects placed into constant memory.    
Global Memory    | Accessible to all work-items in all work-groups. Read/write,
                 | may be cached, persistent across kernel invocations.      
Local Memory     | Shared between work-items in a single work-group and inaccessible
                 | to work-items in other work-groups. 
Private Memory   | A region of memory private to a work-item. Variables defined in
                 | one work-item’s private memory are not visible to another work-item.
===============  ============



.. seealso::

   * :ref:`multipointer`
