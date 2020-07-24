.. _usm_allocator:

.. rst-class:: api-class

===============
 usm_allocator
===============

|2020|

::

   template <typename T, usm::alloc AllocKind, size_t Alignment = 0>
   class usm_allocator;

Allocator suitable for use with a C++ standard library container.

A ``usm_allocator`` enables using USM allocation for standard library
containers. It is typically passed as template parameter when
declaring standard library containers (e.g. vector).

.. rubric:: Template parameters

=============  ===	    
T              Type of allocated element
AllocKind      Type of allocation, see o
Alignment      Alignment of the allocation
=============  ===	    
	    
.. rubric:: Example

.. literalinclude:: /examples/std-vector.cpp
   :linenos:

.. rubric:: Member types

=============  ===	    
value_type
=============  ===	    

.. member-toc::

(constructors)
==============

::

  usm_allocator(const context &ctxt, const device &dev) noexcept;
  usm_allocator(const queue &q) noexcept;
  usm_allocator(const usm_allocator &other) noexcept;
  template <class U>
  usm_allocator(usm_allocator<U, AllocKind, Alignment> const &) noexcept;

allocate
========

::

  T *allocate(size_t Size);

Allocates memory

deallocate
==========

::
   
  void deallocate(T *Ptr, size_t size);

Deallocates memory  

construct
=========

::

  template <
      usm::alloc AllocT = AllocKind,
      typename std::enable_if<AllocT != usm::alloc::device, int>::type = 0,
      class U, class... ArgTs>
  void construct(U *Ptr, ArgTs &&... Args);
  template <
      usm::alloc AllocT = AllocKind,
      typename std::enable_if<AllocT == usm::alloc::device, int>::type = 0,
      class U, class... ArgTs>
  void construct(U *Ptr, ArgTs &&... Args);

Constructs an object on memory pointed by Ptr.

destroy
=======

::
   
  template <
      usm::alloc AllocT = AllocKind,
      typename std::enable_if<AllocT != usm::alloc::device, int>::type = 0>
  void destroy(T *Ptr);

  /// Throws an error when trying to destroy a device allocation
  /// on the host
  template <
      usm::alloc AllocT = AllocKind,
      typename std::enable_if<AllocT == usm::alloc::device, int>::type = 0>
  void destroy(T *Ptr);

Destroys an object.


(operators)
===========

::

   template <class T, usm::alloc AllocKindT, size_t AlignmentT, class U,
             usm::alloc AllocKindU, size_t AlignmentU>
   bool operator==(const usm_allocator<T, AllocKindT, AlignmentT> &,
                   const usm_allocator<U, AllocKindU, AlignmentU> &) noexcept;
   template <class T, class U, usm::alloc AllocKind, size_t Alignment = 0>
   bool operator!=(const usm_allocator<T, AllocKind, Alignment> &allocT,
                   const usm_allocator<U, AllocKind, Alignment> &allocU) noexcept;

Allocators only compare equal if they are of the same USM kind, alignment,
context, and device (when kind is not host).
