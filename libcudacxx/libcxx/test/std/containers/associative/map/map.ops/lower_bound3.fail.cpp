//===----------------------------------------------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

// <map>

// class map

//       iterator lower_bound(const key_type& k);
// const_iterator lower_bound(const key_type& k) const;
//
//   The member function templates find, count, lower_bound, upper_bound, and
// equal_range shall not participate in overload resolution unless the
// qualified-id Compare::is_transparent is valid and denotes a type


#include <map>
#include <cassert>

#include "test_macros.h"
#include "is_transparent.h"

#if TEST_STD_VER <= 2011
#error "This test requires is C++14 (or later)"
#else

int main(int, char**)
{
    {
    typedef std::map<int, double, transparent_less_not_a_type> M;

    TEST_IGNORE_NODISCARD M().lower_bound(C2Int{5});
    }
}
#endif
