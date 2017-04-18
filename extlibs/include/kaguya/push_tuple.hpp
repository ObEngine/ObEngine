// Copyright satoren
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#pragma once

#include "kaguya/config.hpp"
#include "kaguya/traits.hpp"

namespace kaguya {
#if KAGUYA_USE_CPP11
namespace detail {
template <std::size_t... indexes> struct index_tuple {};
template <std::size_t first, std::size_t last, class result = index_tuple<>,
          bool flag = first >= last>
struct index_range {
  using type = result;
};
template <std::size_t step, std::size_t last, std::size_t... indexes>
struct index_range<step, last, index_tuple<indexes...>, false>
    : index_range<step + 1, last, index_tuple<indexes..., step> > {};

template <std::size_t... Indexes, class... Args>
int push_tuple(lua_State *l, index_tuple<Indexes...>, std::tuple<Args...> &&v) {
  return util::push_args(l, std::get<Indexes>(v)...);
}
}

/// @ingroup lua_type_traits
/// @brief lua_type_traits for std::tuple or boost::tuple
template <class... Args> struct lua_type_traits<standard::tuple<Args...> > {
  static int push(lua_State *l, std::tuple<Args...> &&v) {
    typename detail::index_range<0, sizeof...(Args)>::type index;
    return detail::push_tuple(l, index, std::forward<std::tuple<Args...> >(v));
  }
};
#else
#define KAGUYA_PP_GET_DATA(N) standard::get<N - 1>(v)
#define KAGUYA_PUSH_TUPLE_DEF(N)                                               \
  template <KAGUYA_PP_TEMPLATE_DEF_REPEAT(N)>                                  \
  struct lua_type_traits<standard::tuple<KAGUYA_PP_TEMPLATE_ARG_REPEAT(N)> > { \
    static int                                                                 \
    push(lua_State *l,                                                         \
         const standard::tuple<KAGUYA_PP_TEMPLATE_ARG_REPEAT(N)> &v) {         \
      return util::push_args(l, KAGUYA_PP_REPEAT_ARG(N, KAGUYA_PP_GET_DATA));  \
    }                                                                          \
  };
KAGUYA_PP_REPEAT_DEF(KAGUYA_FUNCTION_MAX_TUPLE_SIZE, KAGUYA_PUSH_TUPLE_DEF)
#undef KAGUYA_PP_GET_DATA
#undef KAGUYA_PUSH_TUPLE_DEF
#endif
}
