// Copyright (c) 2011-2020 The Khronos Group, Inc.
//
// Licensed under the Apache License, Version 2.0 (the License);
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an AS IS BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

namespace sycl {

template <typename dataT, std::size_t numElements>
class marray {
 public:
  using value_type = dataT;
  using reference = dataT&;
  using const_reference = const dataT&;
  using iterator = dataT*;
  using const_iterator = const dataT*;

  marray();

  explicit marray(const dataT &arg);

  template <typename... argTN>
  marray(const argTN&... args);

  marray(const marray<dataT, numElements> &rhs);
  marray(marray<dataT, numElements> &&rhs);

  // Available only when: numElements == 1
  operator dataT() const;

  static constexpr std::size_t size();

  // subscript operator
  reference operator[](std::size_t index);
  const_reference operator[](std::size_t index) const;

  marray &operator=(const marray<dataT, numElements> &rhs);
  marray &operator=(const dataT &rhs);
};

// iterator functions
iterator begin(marray &v);
const_iterator begin(const marray &v);

iterator end(marray &v);
const_iterator end(const marray &v);

// OP is: +, -, *, /, %
/* When OP is % available only when: dataT != float && dataT != double && dataT != half. */
marray operatorOP(const marray &lhs, const marray &rhs) { /* ... */ }
marray operatorOP(const marray &lhs, const dataT &rhs) { /* ... */ }

// OP is: +=, -=, *=, /=, %=
/* When OP is %= available only when: dataT != float && dataT != double && dataT != half. */
marray &operatorOP(marray &lhs, const marray &rhs) { /* ... */ }
marray &operatorOP(marray &lhs, const dataT &rhs) { /* ... */ }

// OP is: ++, --
marray &operatorOP(marray &lhs) { /* ... */ }
marray operatorOP(marray& lhs, int) { /* ... */ }

// OP is: +, -
marray operatorOP(marray &lhs) const { /* ... */ }

// OP is: &, |, ^
/* Available only when: dataT != float && dataT != double && dataT != half. */
marray operatorOP(const marray &lhs, const marray &rhs) { /* ... */ }
marray operatorOP(const marray &lhs, const dataT &rhs) { /* ... */ }

// OP is: &=, |=, ^=
/* Available only when: dataT != float && dataT != double && dataT != half. */
marray &operatorOP(marray &lhs, const marray &rhs) { /* ... */ }
marray &operatorOP(marray &lhs, const dataT &rhs) { /* ... */ }

// OP is: &&, ||
marray<bool, numElements> operatorOP(const marray &lhs, const marray &rhs) { /* ... */ }
marray<bool, numElements> operatorOP(const marray& lhs, const dataT &rhs) { /* ... */ }

// OP is: <<, >>
/* Available only when: dataT != float && dataT != double && dataT != half. */
marray operatorOP(const marray &lhs, const marray &rhs) { /* ... */ }
marray operatorOP(const marray &lhs, const dataT &rhs) { /* ... */ }

// OP is: <<=, >>=
/* Available only when: dataT != float && dataT != double && dataT != half. */
marray &operatorOP(marray &lhs, const marray &rhs) { /* ... */ }
marray &operatorOP(marray &lhs, const dataT &rhs) { /* ... */ }

// OP is: ==, !=, <, >, <=, >=
marray<bool, numElements> operatorOP(const marray &lhs, const marray &rhs) { /* ... */ }
marray<bool, numElements> operatorOP(const marray &lhs, const dataT &rhs) { /* ... */ }

/* Available only when: dataT != float && dataT != double && dataT != half. */
marray operator~(const marray &v) { /* ... */ }
marray<bool, numElements> operator!(const marray &v) { /* ... */ }

// OP is: +, -, *, /, %
/* operator% is only available when: dataT != float && dataT != double && dataT != half. */
marray operatorOP(const dataT &lhs, const marray &rhs) { /* ... */ }

// OP is: &, |, ^
/* Available only when: dataT != float && dataT != double
&& dataT != half. */
marray operatorOP(const dataT &lhs, const marray &rhs) { /* ... */ }

// OP is: &&, ||
marray<bool, numElements> operatorOP(const dataT &lhs, const marray &rhs) { /* ... */ }

// OP is: <<, >>
/* Available only when: dataT != float && dataT != double && dataT != half. */
marray operatorOP(const dataT &lhs, const marray &rhs) { /* ... */ }

// OP is: ==, !=, <, >, <=, >=
marray<bool, numElements> operatorOP(const dataT &lhs, const marray &rhs) { /* ... */ }

marray operator~(const marray &v) const { /* ... */ }

marray<bool, numElements> operator!(const marray &v) const { /* ... */ }

}  // namespace sycl
