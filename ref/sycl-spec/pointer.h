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

template <typename ElementType, access::address_space Space, access::decorated IsDecorated>
class multi_ptr;

// Template specialization aliases for different pointer address spaces

template <typename ElementType, access::decorated IsDecorated = access::decorated::legacy>
using global_ptr = multi_ptr<ElementType, access::address_space::global_space,
                             IsDecorated>;

template <typename ElementType, access::decorated IsDecorated = access::decorated::legacy>
using local_ptr = multi_ptr<ElementType, access::address_space::local_space,
                            IsDecorated>;

template <typename ElementType, access::decorated IsDecorated = access::decorated::legacy>
using constant_ptr = multi_ptr<ElementType, access::address_space::constant_space,
                               IsDecorated>;

template <typename ElementType, access::decorated IsDecorated = access::decorated::legacy>
using private_ptr = multi_ptr<ElementType, access::address_space::private_space,
                              IsDecorated>;

// Template specialization aliases for different pointer address spaces.
// The interface exposes non-decorated pointer while keeping the
// address space information internally.

template <typename ElementType>
using raw_global_ptr = multi_ptr<ElementType, access::address_space::global_space,
                                 access::decorated::no>;

template <typename ElementType>
using raw_local_ptr = multi_ptr<ElementType, access::address_space::local_space,
                                access::decorated::no>;

template <typename ElementType>
using raw_constant_ptr = multi_ptr<ElementType, access::address_space::constant_space,
                                   access::decorated::no>;

template <typename ElementType>
using raw_private_ptr = multi_ptr<ElementType, access::address_space::private_space,
                                  access::decorated::no>;

// Template specialization aliases for different pointer address spaces.
// The interface exposes decorated pointer.

template <typename ElementType>
using decorated_global_ptr = multi_ptr<ElementType, access::address_space::global_space,
                                       access::decorated::yes>;

template <typename ElementType>
using decorated_local_ptr = multi_ptr<ElementType, access::address_space::local_space,
                                      access::decorated::yes>;

template <typename ElementType>
using decorated_constant_ptr = multi_ptr<ElementType, access::address_space::constant_space,
                                         access::decorated::yes>;

template <typename ElementType>
using decorated_private_ptr = multi_ptr<ElementType, access::address_space::private_space,
                                        access::decorated::yes>;

}  // namespace sycl
