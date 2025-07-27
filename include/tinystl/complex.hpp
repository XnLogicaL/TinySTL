//
// TinySTL
// Copyright (C) 2025 XnLogicaL
// Licensed under GNU GPL v3.0
//

#ifndef _TINYSTL_HAS_COMPLEX_HPP
#define _TINYSTL_HAS_COMPLEX_HPP

#include "internal/core.hpp"
#include <complex.h>

_TINYSTL_BEGIN

template<typename T>
  requires std::is_arithmetic_v<T>
class complex final {
public:
  using value_type = T;

public:
  constexpr complex() = default;
  constexpr complex(value_type r, value_type i)
    : m_base(r + i * I) {}

  // Returns the real component of the complex number.
  inline value_type real() const {
    return creal(m_base);
  }

  // Returns the imaginary component of the complex number.
  inline value_type imag() const {
    return cimag(m_base);
  }

private:
  value_type ::complex m_base;
};

_TINYSTL_END

#endif
