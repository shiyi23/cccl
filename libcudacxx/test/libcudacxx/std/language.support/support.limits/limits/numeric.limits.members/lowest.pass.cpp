//===----------------------------------------------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

// test numeric_limits

// lowest()

#include <cuda/std/limits>
#include <cuda/std/climits>
#include <cuda/std/cfloat>
#include <cuda/std/cassert>

#include "test_macros.h"

template <class T>
__host__ __device__
void
test(T expected)
{
    assert(cuda::std::numeric_limits<T>::lowest() == expected);
    assert(cuda::std::numeric_limits<T>::is_bounded);
    assert(cuda::std::numeric_limits<const T>::lowest() == expected);
    assert(cuda::std::numeric_limits<const T>::is_bounded);
    assert(cuda::std::numeric_limits<volatile T>::lowest() == expected);
    assert(cuda::std::numeric_limits<volatile T>::is_bounded);
    assert(cuda::std::numeric_limits<const volatile T>::lowest() == expected);
    assert(cuda::std::numeric_limits<const volatile T>::is_bounded);
}

int main(int, char**)
{
    test<bool>(false);
    test<char>(CHAR_MIN);
    test<signed char>(SCHAR_MIN);
    test<unsigned char>(0);
#ifndef _LIBCUDACXX_COMPILER_NVRTC
    test<wchar_t>(WCHAR_MIN);
#endif
#if TEST_STD_VER > 2017 && defined(__cpp_char8_t)
    test<char8_t>(0);
#endif
#ifndef _LIBCUDACXX_HAS_NO_UNICODE_CHARS
    test<char16_t>(0);
    test<char32_t>(0);
#endif  // _LIBCUDACXX_HAS_NO_UNICODE_CHARS
    test<short>(SHRT_MIN);
    test<unsigned short>(0);
    test<int>(INT_MIN);
    test<unsigned int>(0);
    test<long>(LONG_MIN);
    test<unsigned long>(0);
    test<long long>(LLONG_MIN);
    test<unsigned long long>(0);
#ifndef _LIBCUDACXX_HAS_NO_INT128
    test<__int128_t>(-__int128_t(__uint128_t(-1)/2) - 1);
    test<__uint128_t>(0);
#endif
    test<float>(-FLT_MAX);
    test<double>(-DBL_MAX);
#ifndef _LIBCUDACXX_HAS_NO_LONG_DOUBLE
    test<long double>(-LDBL_MAX);
#endif

    return 0;
}
