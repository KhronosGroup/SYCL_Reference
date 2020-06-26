.. _common-reference:

=====================
 Reference Semantics
=====================

Classes: device, context, queue, program, kernel, event, buffer, image,
sampler, accessor and stream

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
