..
  Copyright 2020 The Khronos Group Inc.
  SPDX-License-Identifier: CC-BY-4.0

.. _common-reference:

=====================
 Reference Semantics
=====================

Classes: :ref:`sycl::accessor<iface-accessors>`,
:ref:`sycl::buffer<iface-buffers>`, :ref:`context`, :ref:`device`,
`device_image`, :ref:`event`, `host_accessor`, `host_sampled_image_accessor`,
`host_unsampled_image_accessor`, :ref:`kernel`, `kernel_id`, `kernel_bundle`,
`local_accessor`, :ref:`platform`, :ref:`queue`, `sampled_image`,
`sampled_image_accessor`, `unsampled_image` and `unsampled_image_accessor`.

Classes with reference semantics support the following methods. An
instance that is constructed as a copy of another instance must behave
as-if it were the same instance.

::

  class T {
  public:
    T(const T &rhs);
    T(T &&rhs);
    T &operator=(const T &rhs);
    T &operator=(T &&rhs);
    ~T();
    friend bool operator==(const T &lhs, const T &rhs) { /* ... */ }
    friend bool operator!=(const T &lhs, const T &rhs) { /* ... */ }
  };
