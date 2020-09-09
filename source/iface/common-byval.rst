.. _common-byval:

====================
 By-value Semantics
====================

Types: id, range, item, nd_item, h_item, group and nd_range.

Classes with reference semantics support the following methods.

::

  class T {
    T(const T &rhs);
    T(T &&rhs);
    T &operator=(const T &rhs);
    T &operator=(T &&rhs);
    ~T();
    friend bool operator==(const T &lhs, const T &rhs) { /* ... */ }
    friend bool operator!=(const T &lhs, const T &rhs) { /* ... */ }
  };
   
