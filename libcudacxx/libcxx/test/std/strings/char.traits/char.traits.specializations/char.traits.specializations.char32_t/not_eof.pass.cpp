//===----------------------------------------------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

// <string>

// template<> struct char_traits<char32_t>

// static constexpr int_type not_eof(int_type c);

#include <string>
#include <cassert>

#include "test_macros.h"

int main(int, char**)
{
#ifndef _LIBCUDACXX_HAS_NO_UNICODE_CHARS
    assert(std::char_traits<char32_t>::not_eof(U'a') == U'a');
    assert(std::char_traits<char32_t>::not_eof(U'A') == U'A');
    assert(std::char_traits<char32_t>::not_eof(0) == 0);
    assert(std::char_traits<char32_t>::not_eof(std::char_traits<char32_t>::eof()) !=
           std::char_traits<char32_t>::eof());
#endif  // _LIBCUDACXX_HAS_NO_UNICODE_CHARS

  return 0;
}
