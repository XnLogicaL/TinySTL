//
// TinySTL
// Copyright (C) 2025 XnLogicaL
// Licensed under GNU GPL v3.0
//

#ifndef _TINYSTL_UTILITY
#define _TINYSTL_UTILITY

#include "internal/core.hpp"

_TINYSTL_BEGIN

template<typename T>
concept is_iterator_complaint = requires(T t) {
                                  { t.begin() } -> std::same_as<typename T::pointer>;
                                  { t.end() } -> std::same_as<typename T::pointer>;
                                };

_TINYSTL_END

#endif
