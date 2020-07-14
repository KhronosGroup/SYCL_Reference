===============
 malloc_device
===============

|2020|

::

   void* sycl::malloc_device(size_t num_bytes,
                             const sycl::device& dev,
                             const sycl::context& ctxt);
   template <typename T>
   T* sycl::malloc_device(size_t count,
                          const sycl::device& dev,
                          const sycl::context& ctxt);

.. rubric:: Parameters

==================  ===
num_bytes           allocation size in bytes
count               number of elements
dev                 See :ref:`device`
ctxt                See :ref:`context`
==================  ===


Allocate memory on the device


			  
