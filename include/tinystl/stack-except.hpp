//
// TinySTL
// Copyright (C) 2025 XnLogicaL
// Licensed under GNU GPL v3.0
//

#ifndef _TINYSTL_HAS_STACK_EXCEPT_HPP
#define _TINYSTL_HAS_STACK_EXCEPT_HPP

#include "core.hpp"

_TINYSTL_BEGIN

class underflow_error final : public exception {
public:
  underflow_error(const char* message)
    : message(message) {}

  const char* what() const throw() override {
    return message;
  }

private:
  const char* message;
};

class overflow_error final : public exception {
public:
  overflow_error(const char* message)
    : message(message) {}

  const char* what() const throw() override {
    return message;
  }

private:
  const char* message;
};

_TINYSTL_END

#endif
