//
// TinySTL
// Copyright (C) 2025 XnLogicaL
// Licensed under GNU GPL v3.0
//

#ifndef _TINYSTL_HAS_LIMITS_HPP
#define _TINYSTL_HAS_LIMITS_HPP

#include "internal/core.hpp"
#include <cfloat>
#include <climits>

#define _LIMIT_FIELD static constexpr

_TINYSTL_BEGIN

template<typename T>
struct limits;

template<>
struct limits<char> {
  _LIMIT_FIELD auto min = SCHAR_MIN;
  _LIMIT_FIELD auto max = SCHAR_MAX;
};

template<>
struct limits<int> {
  _LIMIT_FIELD auto min = INT_MIN;
  _LIMIT_FIELD auto max = INT_MAX;
};

template<>
struct limits<short> {
  _LIMIT_FIELD auto min = SHRT_MIN;
  _LIMIT_FIELD auto max = SHRT_MAX;
};

template<>
struct limits<float> {
  _LIMIT_FIELD auto min = FLT_MIN;
  _LIMIT_FIELD auto max = FLT_MAX;
};

template<>
struct limits<double> {
  _LIMIT_FIELD auto min = DBL_MIN;
  _LIMIT_FIELD auto max = DBL_MAX;
};

template<>
struct limits<long> {
  _LIMIT_FIELD auto min = LONG_MIN;
  _LIMIT_FIELD auto max = LONG_MAX;
};

template<>
struct limits<long long> {
  _LIMIT_FIELD auto min = LLONG_MIN;
  _LIMIT_FIELD auto max = LLONG_MAX;
};

template<>
struct limits<unsigned> {
  _LIMIT_FIELD auto min = 0U;
  _LIMIT_FIELD auto max = UINT_MAX;
};

template<>
struct limits<unsigned char> {
  _LIMIT_FIELD auto min = SCHAR_MIN;
  _LIMIT_FIELD auto max = SCHAR_MAX;
};

template<>
struct limits<unsigned short> {
  _LIMIT_FIELD auto min = 0U;
  _LIMIT_FIELD auto max = USHRT_MAX;
};

template<>
struct limits<unsigned long> {
  _LIMIT_FIELD auto min = 0UL;
  _LIMIT_FIELD auto max = ULONG_MAX;
};

template<>
struct limits<unsigned long long> {
  _LIMIT_FIELD auto min = 0ULL;
  _LIMIT_FIELD auto max = ULLONG_MAX;
};

template<>
struct limits<long double> {
  _LIMIT_FIELD auto min = LDBL_MIN;
  _LIMIT_FIELD auto max = LDBL_MAX;
};

#undef _LIMIT_FIELD

_TINYSTL_END

#endif
