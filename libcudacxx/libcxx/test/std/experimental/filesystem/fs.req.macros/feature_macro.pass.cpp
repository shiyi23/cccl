//===----------------------------------------------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

// <experimental/filesystem>

// #define __cpp_lib_experimental_filesystem 201406L

#include <experimental/filesystem>
#include "test_macros.h"

#ifndef __cpp_lib_experimental_filesystem
#error Filesystem feature test macro is not defined  (__cpp_lib_experimental_filesystem)
#elif __cpp_lib_experimental_filesystem != 201406L
#error Filesystem feature test macro has an incorrect value (__cpp_lib_experimental_filesystem)
#endif


int main(int, char**) {
  return 0;
}
