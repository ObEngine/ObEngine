#pragma once

// for c++03 implement

#define KAGUYA_VA_ARG(...) __VA_ARGS__

#define KAGUYA_PP_CAT(F, B) F##B

#include "kaguya/preprocess_repeate.hpp"

#define KAGUYA_PP_VARIADIC_TARG_CONCAT_REP(N) , KAGUYA_PP_CAT(A, N)
#define KAGUYA_PP_VARIADIC_TARG_REP(N) KAGUYA_PP_CAT(A, N)

#define KAGUYA_PP_TEMPLATE_ARG_REPEAT_CONCAT(N)                                \
  KAGUYA_PP_REPEAT(N, KAGUYA_PP_VARIADIC_TARG_CONCAT_REP)
#define KAGUYA_PP_TEMPLATE_ARG_REPEAT(N)                                       \
  KAGUYA_PP_REPEAT_ARG(N, KAGUYA_PP_VARIADIC_TARG_REP)

#define KAGUYA_PP_ARG_DEF_CONCAT_REP(N)                                        \
  , KAGUYA_PP_CAT(A, N) KAGUYA_PP_CAT(a, N)
#define KAGUYA_PP_ARG_DEF_REP(N) KAGUYA_PP_CAT(A, N) KAGUYA_PP_CAT(a, N)

#define KAGUYA_PP_ARG_DEF_REPEAT_CONCAT(N)                                     \
  KAGUYA_PP_REPEAT(N, KAGUYA_PP_ARG_DEF_CONCAT_REP)
#define KAGUYA_PP_ARG_DEF_REPEAT(N)                                            \
  KAGUYA_PP_REPEAT_ARG(N, KAGUYA_PP_ARG_DEF_REP)

#define KAGUYA_PP_ARG_CR_DEF_CONCAT_REP(N)                                     \
  , const KAGUYA_PP_CAT(A, N) & KAGUYA_PP_CAT(a, N)
#define KAGUYA_PP_ARG_CR_DEF_REP(N)                                            \
  const KAGUYA_PP_CAT(A, N) & KAGUYA_PP_CAT(a, N)

#define KAGUYA_PP_ARG_CR_DEF_REPEAT_CONCAT(N)                                  \
  KAGUYA_PP_REPEAT(N, KAGUYA_PP_ARG_CR_DEF_CONCAT_REP)
#define KAGUYA_PP_ARG_CR_DEF_REPEAT(N)                                         \
  KAGUYA_PP_REPEAT_ARG(N, KAGUYA_PP_ARG_CR_DEF_REP)

#define KAGUYA_PP_ARG_CONCAT_REP(N) , KAGUYA_PP_CAT(a, N)
#define KAGUYA_PP_ARG_REP(N) KAGUYA_PP_CAT(a, N)

#define KAGUYA_PP_ARG_REPEAT_CONCAT(N)                                         \
  KAGUYA_PP_REPEAT(N, KAGUYA_PP_ARG_CONCAT_REP)
#define KAGUYA_PP_ARG_REPEAT(N) KAGUYA_PP_REPEAT_ARG(N, KAGUYA_PP_ARG_REP)

#define KAGUYA_PP_VARIADIC_TDEF_CONCAT_REP(N) , KAGUYA_PP_CAT(typename A, N)
#define KAGUYA_PP_VARIADIC_TDEF_REP(N) KAGUYA_PP_CAT(typename A, N)

#define KAGUYA_PP_TEMPLATE_DEF_REPEAT_CONCAT(N)                                \
  KAGUYA_PP_REPEAT(N, KAGUYA_PP_VARIADIC_TDEF_CONCAT_REP)
#define KAGUYA_PP_TEMPLATE_DEF_REPEAT(N)                                       \
  KAGUYA_PP_REPEAT_ARG(N, KAGUYA_PP_VARIADIC_TDEF_REP)

#define KAGUYA_PP_ADD(X, Y) KAGUYA_PP_WHILE(Y, X, KAGUYA_PP_INC)
#define KAGUYA_PP_SUB(X, Y) KAGUYA_PP_WHILE(Y, X, KAGUYA_PP_DEC)
