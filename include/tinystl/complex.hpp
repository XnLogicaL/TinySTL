//
// TinySTL
// Copyright (C) 2025 XnLogicaL
// Licensed under GNU GPL v3.0
//

#ifndef _TINYSTL_HAS_COMPLEX_HPP
#define _TINYSTL_HAS_COMPLEX_HPP

#include "internal/core.hpp"

_TINYSTL_BEGIN

template<typename T>
  requires std::is_arithmetic_v<T>
class complex final {
public:
  using value_type = T;

public:
  constexpr complex() = default;
  constexpr complex(value_type r, value_type i)
    : m_real(r),
      m_imag(i) {}

  // Returns the real component of the complex number.
  inline value_type real() const {
    return m_real;
  }

  // Returns the imaginary component of the complex number.
  inline value_type imag() const {
    return m_imag;
  }

  template<typename U>
  inline auto operator+(U x) {
    return complex(m_real + x, m_imag);
  }

  template<typename U>
  inline auto operator+(complex<U> z) {
    return complex(m_real + z.m_real, m_imag + z.m_imag);
  }

  template<typename U>
  inline auto operator-(U x) {
    return complex(m_real - x, m_imag);
  }

  template<typename U>
  inline auto operator-(complex<U> z) {
    return complex(m_real - z.m_real, m_imag - z.m_imag);
  }

  template<typename U>
  inline auto operator*(U x) {
    return complex(m_real * x, m_imag);
  }

  template<typename U>
  inline auto operator*(complex<U> z) {
    return complex(m_real * z.m_real, m_imag * z.m_imag);
  }

  template<typename U>
  inline auto operator/(U x) {
    return complex(m_real / x, m_imag);
  }

  template<typename U>
  inline auto operator/(complex<U> z) {
    return complex(m_real / z.m_real, m_imag / z.m_imag);
  }

private:
  const value_type m_real;
  const value_type m_imag;
};

inline const complex<double> I{0.0, 1.0};

_TINYSTL_END

#endif
