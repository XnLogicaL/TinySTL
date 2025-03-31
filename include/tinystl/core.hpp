//
// TinySTL
// Copyright (C) 2025 XnLogicaL
// Licensed under GNU GPL v3.0
//

#ifndef _TINYSTL_HAS_CORE_HPP
#define _TINYSTL_HAS_CORE_HPP

#include <type_traits>
#include <utility>

#ifdef __cpp_exceptions
#define _TINYSTL_EXCEPTIONS
#endif

#define _TINYSTL_CXX_23_BEGIN inline namespace _cxx_23 {
#define _TINYSTL_CXX_23_END   }

#define _TINYSTL_BEGIN                                                                             \
  namespace tinystl {                                                                              \
  _TINYSTL_CXX_23_BEGIN

#define _TINYSTL_END                                                                               \
  _TINYSTL_CXX_23_END                                                                              \
  }

#ifdef _MSC_VER
#define _TINYSTL_INLINE __forceinline
#else
#define _TINYSTL_INLINE inline
#endif

_TINYSTL_BEGIN

#ifdef _TINYSTL_EXCEPTIONS

class exception {
public:
  virtual ~exception() = default;
  virtual const char* what() const throw() {
    return "";
  }
};

#else
#include <iostream>

void _tinystl_error(const char* message) {
  std::cerr << "TinySTL runtime error: " << message << std::flush;
  std::terminate();
}
#endif

_TINYSTL_END

#endif
