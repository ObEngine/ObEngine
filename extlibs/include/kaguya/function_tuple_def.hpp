// Copyright satoren
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
#pragma once

#include <string>

#include "kaguya/config.hpp"
#include "kaguya/utility.hpp"
#include "kaguya/preprocess.hpp"

namespace kaguya {
namespace fntuple {

#if KAGUYA_USE_CPP11 && !defined(KAGUYA_FUNCTION_MAX_OVERLOADS)
// In Clang with libstdc++.
// std::tuple elements is limited to 16 for template depth limit
using std::tuple;
using std::get;
using std::tuple_element;
using std::tuple_size;
#else
using util::null_type;
// boost::tuple is max
#define KAGUYA_PP_STRUCT_TDEF_REP(N) KAGUYA_PP_CAT(typename A, N) = null_type
#define KAGUYA_PP_STRUCT_TEMPLATE_DEF_REPEAT(N)                                \
  KAGUYA_PP_REPEAT_ARG(N, KAGUYA_PP_STRUCT_TDEF_REP)

template <KAGUYA_PP_STRUCT_TEMPLATE_DEF_REPEAT(
    KAGUYA_PP_INC(KAGUYA_FUNCTION_MAX_OVERLOADS))>
struct tuple {};
#undef KAGUYA_PP_STRUCT_TDEF_REP
#undef KAGUYA_PP_STRUCT_TEMPLATE_DEF_REPEAT

#define KAGUYA_FUNCTION_TUPLE_ELEMENT(N)                                       \
  KAGUYA_PP_CAT(A, N) KAGUYA_PP_CAT(elem, N);
#define KAGUYA_FUNCTION_TUPLE_ELEMENT_INIT(N)                                  \
  KAGUYA_PP_CAT(elem, N)(KAGUYA_PP_CAT(a, N))
#define KAGUYA_FUNCTION_TUPLE_IMPL_DEF(N)                                      \
  template <KAGUYA_PP_TEMPLATE_DEF_REPEAT(N)>                                  \
  struct tuple<KAGUYA_PP_TEMPLATE_ARG_REPEAT(N)> {                             \
    KAGUYA_PP_REPEAT(N, KAGUYA_FUNCTION_TUPLE_ELEMENT)                         \
    tuple(KAGUYA_PP_ARG_DEF_REPEAT(N))                                         \
        : KAGUYA_PP_REPEAT_ARG(N, KAGUYA_FUNCTION_TUPLE_ELEMENT_INIT) {}       \
  };

KAGUYA_PP_REPEAT_DEF(KAGUYA_FUNCTION_MAX_OVERLOADS,
                     KAGUYA_FUNCTION_TUPLE_IMPL_DEF)

template <typename Tuple> struct tuple_size;

#define KAGUYA_TUPLE_SIZE_DEF(N)                                               \
  template <KAGUYA_PP_TEMPLATE_DEF_REPEAT(N)>                                  \
  struct tuple_size<tuple<KAGUYA_PP_TEMPLATE_ARG_REPEAT(N)> > {                \
    static const size_t value = N;                                             \
  };

KAGUYA_TUPLE_SIZE_DEF(0)
KAGUYA_PP_REPEAT_DEF(KAGUYA_FUNCTION_MAX_OVERLOADS, KAGUYA_TUPLE_SIZE_DEF)
#undef KAGUYA_TUPLE_SIZE_DEF

template <std::size_t remain, class result, bool flag = remain <= 0>
struct tuple_element {};
#define KAGUYA_TUPLE_ELEMENT_DEF(N)                                            \
  template <std::size_t remain,                                                \
            class arg KAGUYA_PP_TEMPLATE_DEF_REPEAT_CONCAT(N)>                 \
  struct tuple_element<                                                        \
      remain, tuple<arg KAGUYA_PP_TEMPLATE_ARG_REPEAT_CONCAT(N)>, true> {      \
    typedef arg type;                                                          \
  };                                                                           \
  template <std::size_t remain,                                                \
            class arg KAGUYA_PP_TEMPLATE_DEF_REPEAT_CONCAT(N)>                 \
  struct tuple_element<                                                        \
      remain, tuple<arg KAGUYA_PP_TEMPLATE_ARG_REPEAT_CONCAT(N)>, false>       \
      : tuple_element<remain - 1, tuple<KAGUYA_PP_TEMPLATE_ARG_REPEAT(N)> > {  \
  };

KAGUYA_PP_REPEAT_DEF(KAGUYA_FUNCTION_MAX_OVERLOADS, KAGUYA_TUPLE_ELEMENT_DEF)

#undef KAGUYA_TUPLE_SIZE_DEF

template <size_t S, typename T> struct tuple_get_helper;
#define KAGUYA_TUPLE_GET_DEF(N)                                                \
  template <typename T> struct tuple_get_helper<N, T> {                        \
    static typename tuple_element<N - 1, T>::type &get(T &t) {                 \
      return t.KAGUYA_PP_CAT(elem, N);                                         \
    }                                                                          \
    static const typename tuple_element<N - 1, T>::type &cget(const T &t) {    \
      return t.KAGUYA_PP_CAT(elem, N);                                         \
    }                                                                          \
  };
KAGUYA_PP_REPEAT_DEF(KAGUYA_FUNCTION_MAX_OVERLOADS, KAGUYA_TUPLE_GET_DEF)

template <size_t S, typename T> typename tuple_element<S, T>::type &get(T &t) {
  return tuple_get_helper<S + 1, T>::get(t);
}
template <size_t S, typename T>
const typename tuple_element<S, T>::type &get(const T &t) {
  return tuple_get_helper<S + 1, T>::cget(t);
}
#endif
}
}
