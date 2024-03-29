..
  Copyright 2024 The Khronos Group Inc.
  SPDX-License-Identifier: CC-BY-4.0

.. _device_image:

**********************
``sycl::device_image``
**********************

::

  template <sycl::bundle_state State>
  class device_image;

.. seealso:: |SYCL_SPEC_DEVICE_IMAGE|

(constructors)
==============

::

  bool has_kernel(const sycl::kernel_id& kernelId) const noexcept; // (1)

  bool has_kernel(const sycl::kernel_id& kernelId,
                  const sycl::device& dev) const noexcept; // (2)

There is no public constructor for this class.

1. Returns: ``true`` only if the device image contains the kernel
identified by ``kernelId``.

2. Returns: ``true`` only if the device image contains the kernel
identified by ``kernelId`` and if that kernel
is compatible with the device ``dev``.

A synopsis of the ``sycl::device_image`` class is shown below.

::

  namespace sycl {

  template <sycl::bundle_state State>
  class device_image {
   public:
    device_image() = delete;

    bool has_kernel(const sycl::kernel_id& kernelId) const noexcept;

    bool has_kernel(const sycl::kernel_id& kernelId,
                    const sycl::device& dev) const noexcept;
  };

  } // namespace sycl
