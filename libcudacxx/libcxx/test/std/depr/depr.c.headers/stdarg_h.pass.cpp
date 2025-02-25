//===----------------------------------------------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

// test <stdarg.h>

#include <stdarg.h>

#include "test_macros.h"

#ifndef va_arg
#error va_arg not defined
#endif

#  ifndef va_copy
#    error va_copy is not defined when c++ >= 11
#  endif

#ifndef va_end
#error va_end not defined
#endif

#ifndef va_start
#error va_start not defined
#endif

int main(int, char**)
{
    va_list va;
    ((void)va);

  return 0;
}
