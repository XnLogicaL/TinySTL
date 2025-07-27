//
// TinySTL
// Copyright (C) 2025 XnLogicaL
// Licensed under GNU GPL v3.0
//

#ifndef _TINYSTL_HAS_ARRAY_HPP
#define _TINYSTL_HAS_ARRAY_HPP

#include "internal/core.hpp"
#include "exception.hpp"

_TINYSTL_BEGIN

class out_of_range : public exception {
  using exception::exception;
};

template<typename T, const size_t Size>
  requires std::is_copy_constructible_v<T>
class array final {
public:
  using size_type = size_t;
  using value_type = T;
  using reference = T&;
  using rv_reference = T&&;
  using pointer = T*;

public:
  constexpr array() = default;

  // Copy constructor
  constexpr array(array& other)
    : m_array(other.m_array) {}

  // Move constructor
  constexpr array(array&& other)
    : m_array(other.m_array) {
    other.m_array = nullptr;
  }

  // Iterator compliance
  _TINYSTL_ITERATOR_IMPL(m_array, m_array + Size);

  // Move assignment operator
  constexpr array& operator=(array&& other) {
    m_array = other.m_array;
    other.m_array = nullptr;
  }

  constexpr reference at(size_type position) {
    if (!m_range_check(position)) {
      m_out_of_range_error();
    }

    return m_array[position];
  }

  void set(size_type position, rv_reference value) {
    if (!m_range_check(position)) {
      m_out_of_range_error();
    }

    m_array[position] = value;
  }

private:
  bool m_range_check(size_type position) {
    return position < Size;
  }

  [[noreturn]] void m_out_of_range_error() {
#ifdef _TINYSTL_EXCEPTIONS
    throw out_of_range("Array index out of range");
#else
    detail::_tinystl_error("Array index out of range");
#endif
  }

private:
  value_type m_array[Size];
};

_TINYSTL_END

#endif
