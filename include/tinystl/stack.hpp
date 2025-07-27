//
// TinySTL
// Copyright (C) 2025 XnLogicaL
// Licensed under GNU GPL v3.0
//

#ifndef _TINYSTL_HAS_STACK_HPP
#define _TINYSTL_HAS_STACK_HPP

#include "internal/core.hpp"
#include "exception.hpp"
#include <cstddef>

_TINYSTL_BEGIN

class underflow_error : public exception {
  using exception::exception;
};

class overflow_error : public exception {
  using exception::exception;
};

template<typename T, const size_t Capacity>
  requires std::is_copy_constructible_v<T> && std::is_trivially_move_assignable_v<T>
class stack final {
public:
  using size_type = size_t;
  using value_type = T;
  using reference = T&;
  using rv_reference = T&&;
  using pointer = T*;

  constexpr stack() = default;

  // Copy constructor
  constexpr stack(stack& other)
    : m_stack_pointer(other.m_stack_pointer),
      m_stack_array(other.m_stack_array) {}

  // Move constructor
  constexpr stack(stack&& other)
    : m_stack_pointer(other.m_stack_pointer),
      m_stack_array(other.m_stack_array) {
    other.m_stack_pointer = 0;
    other.m_stack_array = nullptr;
  }

  // Move assignement operator
  constexpr stack& operator=(stack&& other) {
    m_stack_pointer = other.m_stack_pointer;
    m_stack_array = other.m_stack_array;
    other.m_stack_pointer = 0;
    other.m_stack_array = nullptr;
  }

  // Iterator compliance
  _TINYSTL_ITERATOR_IMPL(m_stack_array, m_stack_array + Capacity);

  // Returns the active size of the stack.
  inline size_type size() const noexcept {
    return m_stack_pointer;
  }

  // Returns a reference to the top element.
  inline reference top() {
    if (!m_range_check(0)) {
      m_underflow_error();
    }
    return m_stack_array[m_stack_pointer - 1];
  }

  // Pops the top element and returns it.
  inline value_type pop() {
    if (!m_range_check(-1)) {
      m_underflow_error();
    }
    return std::move(m_stack_array[--m_stack_pointer]); // Move the element
  }

  // Pushes an element onto the stack.
  inline void push(T&& val) {
    if (!m_range_check(1)) {
      m_overflow_error();
    }
    m_stack_array[m_stack_pointer++] = std::move(val); // Move assignment
  }

private:
  // Checks if an operation is within valid stack bounds.
  inline bool m_range_check(int offset) const noexcept {
    return (m_stack_pointer + offset <= Capacity) && (m_stack_pointer + offset >= 0);
  }

  // Handles underflow error.
  [[noreturn]] void m_underflow_error() const {
#ifdef _TINYSTL_EXCEPTIONS
    throw underflow_error("Stack underflow");
#else
    detail::_tinystl_error("Stack underflow");
#endif
  }

  // Handles overflow error.
  [[noreturn]] void m_overflow_error() const {
#ifdef _TINYSTL_EXCEPTIONS
    throw overflow_error("Stack overflow");
#else
    detail::_tinystl_error("Stack overflow");
#endif
  }

private:
  size_type m_stack_pointer = 0;
  value_type m_stack_array[Capacity];
};

_TINYSTL_END

#endif
