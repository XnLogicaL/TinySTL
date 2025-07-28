//
// TinySTL
// Copyright (C) 2025 XnLogicaL
// Licensed under GNU GPL v3.0
//

#ifndef _TINYSTL_HAS_MATH_HPP
#define _TINYSTL_HAS_MATH_HPP

#include "internal/core.hpp"
#include "complex.hpp"
#include <cmath>

_TINYSTL_BEGIN

using std::acos;
using std::asin;
using std::atan;
using std::atan2;
using std::cos;
using std::cosh;
using std::sin;
using std::sinh;
using std::tan;
using std::tanh;

template<typename T = double>
inline complex<T> sin(complex<T> z) {
  return I<T> * cos(z.real()) * sinh(z.imag()) + sin(z.real()) * cosh(z.imag());
}

template<typename T = double>
inline complex<T> cos(complex<T> z) {
  return -(I<T> * sin(z.real()) * sinh(z.imag())) + cos(z.real()) * cosh(z.imag());
}

template<typename T = double>
inline complex<T> tan(complex<T> z) {
  return sin(z) / cos(z);
}

_TINYSTL_END

#endif
