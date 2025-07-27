//
// TinySTL
// Copyright (C) 2025 XnLogicaL
// Licensed under GNU GPL v3.0
//

#ifndef _TINYSTL_HAS_EXCEPTION_HPP
#define _TINYSTL_HAS_EXCEPTION_HPP

#include "internal/core.hpp"

_TINYSTL_BEGIN

#ifdef _TINYSTL_EXCEPTIONS

class exception {
public:
  constexpr explicit exception(const char* message)
    : message(message) {}

  virtual const char* what() const throw() {
    return message;
  }

private:
  const char* message;
};

#else
#include <iostream>

namespace detail {

void _tinystl_error(const char* message) {
  std::cerr << "TinySTL runtime error: " << message << std::flush;
  std::terminate();
}

} // namespace detail
#endif

_TINYSTL_END

#endif