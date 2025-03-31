//
// TinySTL
// Copyright (C) 2025 XnLogicaL
// Licensed under GNU GPL v3.0
//

#ifndef _TINYSTL_HAS_STACK_HPP
#define _TINYSTL_HAS_STACK_HPP

#include "core.hpp"
#include "stack-except.hpp"

_TINYSTL_BEGIN

#ifdef _TINYSTL_EXCEPTIONS

#endif

template<typename T, const size_t Capacity>
  requires std::is_copy_constructible_v<T> && std::is_trivially_move_assignable_v<T>
#ifdef _TINYSTL_EXCEPTIONS // clang-format off
    && std::is_nothrow_copy_constructible_v<T>
#endif // clang-format on
class stack final {
public:
  constexpr stack() = default;

  // Returns the active size of the stack.
  _TINYSTL_INLINE size_t size() const noexcept {
    return m_stack_pointer;
  }

  // Returns a reference to the top element.
  _TINYSTL_INLINE T& top() {
    if (!m_range_check(0)) {
      m_underflow_error();
    }
    return m_stack_array[m_stack_pointer - 1];
  }

  // Pops the top element and returns it.
  _TINYSTL_INLINE T pop() {
    if (!m_range_check(-1)) {
      m_underflow_error();
    }
    return std::move(m_stack_array[--m_stack_pointer]); // Move the element
  }

  // Pushes an element onto the stack.
  _TINYSTL_INLINE void push(T&& val) {
    if (!m_range_check(1)) {
      m_overflow_error();
    }
    m_stack_array[m_stack_pointer++] = std::move(val); // Move assignment
  }

private:
  // Checks if an operation is within valid stack bounds.
  _TINYSTL_INLINE bool m_range_check(int offset) const noexcept {
    return (m_stack_pointer + offset <= Capacity) && (m_stack_pointer + offset >= 0);
  }

  // Handles underflow error.
  [[noreturn]] void m_underflow_error() const {
#ifdef _TINYSTL_EXCEPTIONS
    throw underflow_error("Stack underflow");
#else
    _tinystl_error("Stack underflow");
#endif
  }

  // Handles overflow error.
  [[noreturn]] void m_overflow_error() const {
#ifdef _TINYSTL_EXCEPTIONS
    throw overflow_error("Stack overflow");
#else
    _tinystl_error("Stack overflow");
#endif
  }

private:
  size_t m_stack_pointer = 0;
  T m_stack_array[Capacity];
};

_TINYSTL_END

#endif
