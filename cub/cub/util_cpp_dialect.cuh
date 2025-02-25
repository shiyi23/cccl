/******************************************************************************
 * Copyright (c) 2020, NVIDIA CORPORATION.  All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *     * Neither the name of the NVIDIA CORPORATION nor the
 *       names of its contributors may be used to endorse or promote products
 *       derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 *AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 *IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL NVIDIA CORPORATION BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 ******************************************************************************/

//! @file Detect the version of the C++ standard used by the compiler.

#pragma once

#include <cuda/__cccl_config>

#if defined(_CCCL_IMPLICIT_SYSTEM_HEADER_GCC)
#  pragma GCC system_header
#elif defined(_CCCL_IMPLICIT_SYSTEM_HEADER_CLANG)
#  pragma clang system_header
#elif defined(_CCCL_IMPLICIT_SYSTEM_HEADER_MSVC)
#  pragma system_header
#endif // no system header

#include <cub/util_compiler.cuh>

#ifndef DOXYGEN_SHOULD_SKIP_THIS // Do not document

// Deprecation warnings may be silenced by defining the following macros. These
// may be combined.
// - CUB_IGNORE_DEPRECATED_CPP_DIALECT:
//   Ignore all deprecated C++ dialects and outdated compilers.
// - CUB_IGNORE_DEPRECATED_CPP_11:
//   Ignore deprecation warnings when compiling with C++11. C++03 and outdated
//   compilers will still issue warnings.
// - CUB_IGNORE_DEPRECATED_COMPILER
//   Ignore deprecation warnings when using deprecated compilers. Compiling
//   with C++03 and C++11 will still issue warnings.

// Check for the thrust opt-outs as well:
#if !defined(CUB_IGNORE_DEPRECATED_CPP_DIALECT) && \
     defined(THRUST_IGNORE_DEPRECATED_CPP_DIALECT)
#  define    CUB_IGNORE_DEPRECATED_CPP_DIALECT
#endif
#if !defined(CUB_IGNORE_DEPRECATED_CPP_11) && \
     defined(THRUST_IGNORE_DEPRECATED_CPP_11)
#  define    CUB_IGNORE_DEPRECATED_CPP_11
#endif
#if !defined(CUB_IGNORE_DEPRECATED_COMPILER) && \
     defined(THRUST_IGNORE_DEPRECATED_COMPILER)
#  define    CUB_IGNORE_DEPRECATED_COMPILER
#endif

#ifdef CUB_IGNORE_DEPRECATED_CPP_DIALECT
#  define CUB_IGNORE_DEPRECATED_CPP_11
#  define CUB_IGNORE_DEPRECATED_COMPILER
#endif

#define CUB_CPP_DIALECT _CCCL_STD_VER

// Define CUB_COMPILER_DEPRECATION macro:
#if CUB_HOST_COMPILER == CUB_HOST_COMPILER_MSVC
#  define CUB_COMP_DEPR_IMPL(msg) \
    __pragma(message(__FILE__ ":" CUB_COMP_DEPR_IMPL0(__LINE__) ": warning: " #msg))
#  define CUB_COMP_DEPR_IMPL0(x) CUB_COMP_DEPR_IMPL1(x)
#  define CUB_COMP_DEPR_IMPL1(x) #x
#else // clang / gcc:
#  define CUB_COMP_DEPR_IMPL(msg) CUB_COMP_DEPR_IMPL0(GCC warning #msg)
#  define CUB_COMP_DEPR_IMPL0(expr) _Pragma(#expr)
#  define CUB_COMP_DEPR_IMPL1 /* intentionally blank */
#endif

#define CUB_COMPILER_DEPRECATION(REQ) \
  CUB_COMP_DEPR_IMPL(CUB requires at least REQ. Define CUB_IGNORE_DEPRECATED_COMPILER to suppress this message.)

#define CUB_COMPILER_DEPRECATION_SOFT(REQ, CUR) \
  CUB_COMP_DEPR_IMPL(CUB requires at least REQ. CUR is deprecated but still supported. CUR support will be removed in a future release. Define CUB_IGNORE_DEPRECATED_CPP_DIALECT to suppress this message.)

#ifndef CUB_IGNORE_DEPRECATED_COMPILER

// Compiler checks:
#  if CUB_HOST_COMPILER == CUB_HOST_COMPILER_GCC && CUB_GCC_VERSION < 50000
     CUB_COMPILER_DEPRECATION(GCC 5.0);
#  elif CUB_HOST_COMPILER == CUB_HOST_COMPILER_CLANG && CUB_CLANG_VERSION < 70000
     CUB_COMPILER_DEPRECATION(Clang 7.0);
#  elif CUB_HOST_COMPILER == CUB_HOST_COMPILER_MSVC && CUB_MSVC_VERSION < 1910
     // <2017. Hard upgrade message:
     CUB_COMPILER_DEPRECATION(MSVC 2019 (19.20/16.0/14.20));
#  elif CUB_HOST_COMPILER == CUB_HOST_COMPILER_MSVC && CUB_MSVC_VERSION < 1920
     // >=2017, <2019. Soft deprecation message:
     CUB_COMPILER_DEPRECATION_SOFT(MSVC 2019 (19.20/16.0/14.20), MSVC 2017);
#  endif

#endif // CUB_IGNORE_DEPRECATED_COMPILER

#ifndef CUB_IGNORE_DEPRECATED_DIALECT

// Dialect checks:
#  if _CCCL_STD_VER < 2011
     // <C++11. Hard upgrade message:
     CUB_COMPILER_DEPRECATION(C++14);
#  elif _CCCL_STD_VER == 2011 && !defined(CUB_IGNORE_DEPRECATED_CPP_11)
     // =C++11. Soft upgrade message:
     CUB_COMPILER_DEPRECATION_SOFT(C++14, C++11);
#  endif

#endif // CUB_IGNORE_DEPRECATED_DIALECT

#undef CUB_COMPILER_DEPRECATION_SOFT
#undef CUB_COMPILER_DEPRECATION
#undef CUB_COMP_DEPR_IMPL
#undef CUB_COMP_DEPR_IMPL0
#undef CUB_COMP_DEPR_IMPL1

#endif // !DOXYGEN_SHOULD_SKIP_THIS
