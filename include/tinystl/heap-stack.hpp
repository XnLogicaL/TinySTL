//
// TinySTL
// Copyright (C) 2025 XnLogicaL
// Licensed under GNU GPL v3.0
//

#ifndef _TINYSTL_HAS_HEAP_STACK_HPP
#define _TINYSTL_HAS_HEAP_STACK_HPP

#include "core.hpp"
#include "stack-except.hpp"

_TINYSTL_BEGIN

template<typename T>
  requires std::is_copy_constructible_v<T> && std::is_trivially_move_assignable_v<T>
#ifdef _TINYSTL_EXCEPTIONS // clang-format off
    && std::is_nothrow_copy_constructible_v<T>
#endif // clang-format on
class heap_stack final {
public:
  constexpr heap_stack()
    : m_stack_array(new T[m_capacity]) {}

  ~heap_stack() {
    delete[] m_stack_array;
  }

  // Move constructor
  heap_stack(heap_stack&& other) noexcept
    : m_stack_pointer(other.m_stack_pointer),
      m_capacity(other.m_capacity),
      m_stack_array(other.m_stack_array) {
    other.m_stack_array = nullptr;
    other.m_stack_pointer = 0;
    other.m_capacity = 0;
  }

  // Move assignment operator
  heap_stack& operator=(heap_stack&& other) noexcept {
    if (this != &other) {
      delete[] m_stack_array; // Free old memory
      m_stack_pointer = other.m_stack_pointer;
      m_capacity = other.m_capacity;
      m_stack_array = other.m_stack_array;
      other.m_stack_array = nullptr;
      other.m_stack_pointer = 0;
      other.m_capacity = 0;
    }
    return *this;
  }

  // Returns the active size of the stack.
  _TINYSTL_INLINE size_t size() const noexcept {
    return m_stack_pointer;
  }

  // Returns a reference to the top element.
  _TINYSTL_INLINE T& top() {
    if (m_stack_pointer == 0) {
      m_underflow_error();
    }
    return m_stack_array[m_stack_pointer - 1];
  }

  // Pops the top element and returns it.
  _TINYSTL_INLINE T pop() {
    if (m_stack_pointer == 0) {
      m_underflow_error();
    }
    return std::move(m_stack_array[--m_stack_pointer]);
  }

  // Pushes an element onto the stack.
  _TINYSTL_INLINE void push(T&& val) {
    if (m_stack_pointer == m_capacity) {
      m_resize();
    }
    m_stack_array[m_stack_pointer++] = std::move(val);
  }

private:
  // Resizes the stack dynamically
  _TINYSTL_INLINE void m_resize() {
    size_t new_capacity = (m_capacity == 0) ? 1 : m_capacity * 2;
    T* new_array = new T[new_capacity];

    for (size_t i = 0; i < m_stack_pointer; ++i) {
      new_array[i] = std::move(m_stack_array[i]);
    }

    delete[] m_stack_array;
    m_stack_array = new_array;
    m_capacity = new_capacity;
  }

  // Handles underflow error.
  [[noreturn]] void m_underflow_error() const {
#ifdef _TINYSTL_EXCEPTIONS
    throw underflow_error("Stack underflow");
#else
    _tinystl_error("Stack underflow");
#endif
  }

private:
  size_t m_stack_pointer = 0;
  size_t m_capacity = 64;
  T* m_stack_array = nullptr;
};

_TINYSTL_END

#endif // _TINYSTL_HAS_HEAP_STACK_HPP
