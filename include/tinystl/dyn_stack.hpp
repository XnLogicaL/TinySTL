//
// TinySTL
// Copyright (C) 2025 XnLogicaL
// Licensed under GNU GPL v3.0
//

#ifndef _TINYSTL_HAS_DYN_STACK_HPP
#define _TINYSTL_HAS_DYN_STACK_HPP

#include "internal/core.hpp"
#include "stack.hpp"
#include <cstring>

_TINYSTL_BEGIN

template<typename T>
  requires std::is_copy_constructible_v<T> && std::is_trivially_move_assignable_v<T>
class dyn_stack final {
public:
  // Iterator compliance
  using size_type = size_t;
  using value_type = T;
  using reference = T&;
  using rv_reference = T&&;
  using pointer = T*;

  dyn_stack()
    : m_stack_array(new T[m_capacity]) {}

  // Copy constructor
  dyn_stack(dyn_stack& other) noexcept
    : m_stack_pointer(other.m_stack_pointer),
      m_capacity(other.m_capacity),
      m_stack_array(new T[m_capacity]) {
    std::memcpy(m_stack_array, other.m_stack_array, m_stack_pointer);
  }

  // Move constructor
  dyn_stack(dyn_stack&& other) noexcept
    : m_stack_pointer(other.m_stack_pointer),
      m_capacity(other.m_capacity),
      m_stack_array(other.m_stack_array) {
    other.m_stack_array = nullptr;
    other.m_stack_pointer = 0;
    other.m_capacity = 0;
  }

  // Move assignment operator
  dyn_stack& operator=(dyn_stack&& other) noexcept {
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

  ~dyn_stack() {
    delete[] m_stack_array;
  }

  // Iterator compliance
  _TINYSTL_ITERATOR_IMPL(m_stack_array, m_stack_array + m_capacity);

  // Returns the active size of the stack.
  _TINYSTL_INLINE size_type size() const noexcept {
    return m_stack_pointer;
  }

  // Returns a reference to the top element.
  _TINYSTL_INLINE reference top() {
    if (m_stack_pointer == 0) {
      m_underflow_error();
    }
    return m_stack_array[m_stack_pointer - 1];
  }

  // Pops the top element and returns it.
  _TINYSTL_INLINE value_type pop() {
    if (m_stack_pointer == 0) {
      m_underflow_error();
    }
    return std::move(m_stack_array[--m_stack_pointer]);
  }

  // Pushes an element onto the stack.
  _TINYSTL_INLINE void push(rv_reference val) {
    if (m_stack_pointer == m_capacity) {
      m_resize();
    }
    m_stack_array[m_stack_pointer++] = std::move(val);
  }

private:
  // Resizes the stack dynamically
  _TINYSTL_INLINE void m_resize() {
    size_type new_capacity = (m_capacity == 0) ? 1 : m_capacity * 2;
    pointer new_array = new T[new_capacity];

    for (size_type i = 0; i < m_stack_pointer; ++i) {
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

#endif // _TINYSTL_HAS_dyn_stack_HPP
