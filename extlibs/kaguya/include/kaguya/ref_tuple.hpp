// Copyright satoren
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#pragma once

#include "kaguya/config.hpp"

namespace kaguya {

template <typename RefTuple, typename GetTuple> struct ref_tuple {
  RefTuple tref;
  ref_tuple(const RefTuple &va) : tref(va) {}
  void operator=(const FunctionResults &fres) {
    tref = fres.get_result(types::typetag<GetTuple>());
  }
  template <class T> void operator=(const T &fres) { tref = fres; }
};
#if KAGUYA_USE_CPP11
template <class... Args>
ref_tuple<standard::tuple<Args &...>, standard::tuple<Args...> >
tie(Args &... va) {
  typedef standard::tuple<Args &...> RefTuple;
  typedef standard::tuple<Args...> GetTuple;
  return ref_tuple<RefTuple, GetTuple>(RefTuple(va...));
}
#else
#define KAGUYA_VARIADIC_REFARG_REP(N) KAGUYA_PP_CAT(A, N) & KAGUYA_PP_CAT(a, N)
#define KAGUYA_VARIADIC_TREFARG_REP(N) KAGUYA_PP_CAT(A, N) &
#define KAGUYA_TEMPLATE_REFARG_REPEAT(N)                                       \
  KAGUYA_PP_REPEAT_ARG(N, KAGUYA_VARIADIC_TREFARG_REP)
#define KAGUYA_REF_TUPLE(N) standard::tuple<KAGUYA_TEMPLATE_REFARG_REPEAT(N)>
#define KAGUYA_GET_TUPLE(N) standard::tuple<KAGUYA_PP_TEMPLATE_ARG_REPEAT(N)>
#define KAGUYA_REF_TUPLE_DEF(N)                                                \
  template <KAGUYA_PP_TEMPLATE_DEF_REPEAT(N)>                                  \
  ref_tuple<KAGUYA_REF_TUPLE(N), KAGUYA_GET_TUPLE(N)> tie(                     \
      KAGUYA_PP_REPEAT_ARG(N, KAGUYA_VARIADIC_REFARG_REP)) {                   \
    return ref_tuple<KAGUYA_REF_TUPLE(N), KAGUYA_GET_TUPLE(N)>(                \
        KAGUYA_REF_TUPLE(N)(KAGUYA_PP_ARG_REPEAT(N)));                         \
  }

KAGUYA_PP_REPEAT_DEF(KAGUYA_FUNCTION_MAX_TUPLE_SIZE, KAGUYA_REF_TUPLE_DEF)
#undef KAGUYA_VARIADIC_REFARG_REP
#undef KAGUYA_TEMPLATE_REFARG_REPEAT
#undef KAGUYA_REF_TUPLE
#undef KAGUYA_GET_TUPLE
#undef KAGUYA_REF_TUPLE_DEF
#endif
}
