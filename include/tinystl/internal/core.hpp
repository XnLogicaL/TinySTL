//
// TinySTL
// Copyright (C) 2025 XnLogicaL
// Licensed under GNU GPL v3.0
//

#ifndef _TINYSTL_HAS_CORE_HPP
#define _TINYSTL_HAS_CORE_HPP

#include <type_traits>
#include <utility>
#include <cstddef>

#ifdef __cpp_exceptions
#define _TINYSTL_EXCEPTIONS
#endif

#define _TINYSTL_CXX_23_BEGIN inline namespace _cxx_23 {
#define _TINYSTL_CXX_23_END   }

#define _TINYSTL_BEGIN                                                                             \
  namespace tiny {                                                                                 \
  _TINYSTL_CXX_23_BEGIN

#define _TINYSTL_END                                                                               \
  _TINYSTL_CXX_23_END                                                                              \
  }

#ifdef __GNUC__
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wmultistatement-macros"
#endif

// clang-format off
#define _TINYSTL_ITERATOR_IMPL(begin_, end_)                                                 \
  inline constexpr pointer begin() { return begin_; }                                       \
  inline constexpr pointer end() { return end_; }
// clang-format on

#ifdef __GNUC__
#pragma GCC diagnostic pop
#endif

#endif
