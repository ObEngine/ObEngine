// Copyright satoren
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
#pragma once

#include <string>

#include "kaguya/config.hpp"
#include "kaguya/utility.hpp"
#include "kaguya/object.hpp"

namespace kaguya {
namespace nativefunction {

#define KAGUYA_INVOKE_SIG_TARG_DEF_CONCAT_REP(N)                               \
  , typename util::ArgumentType<N - 1, F>::type
#define KAGUYA_INVOKE_SIG_TARG_DEF_REPEAT_CONCAT(N)                            \
  KAGUYA_PP_REPEAT(N, KAGUYA_INVOKE_SIG_TARG_DEF_CONCAT_REP)

#define KAGUYA_GET_REP(N) , lua_type_traits<KAGUYA_PP_CAT(A, N)>::get(state, N)
#define KAGUYA_FUNC_DEF(N)                                                     \
  const util::FunctionSignatureType<Ret KAGUYA_PP_TEMPLATE_ARG_REPEAT_CONCAT(  \
      N)> &fsig
#define KAGUYA_TYPENAME_REP(N)                                                 \
  +((MAX_ARG - opt_count < N) ? "[OPT]" : "") +                                \
      util::pretty_name(typeid(KAGUYA_PP_CAT(A, N))) + ","
#define KAGUYA_TYPECHECK_REP(N)                                                \
  &&(((MAX_ARG - opt_count < N) && lua_isnoneornil(state, N)) ||               \
     lua_type_traits<KAGUYA_PP_CAT(A, N)>::checkType(state, N))
#define KAGUYA_STRICT_TYPECHECK_REP(N)                                         \
  &&(((MAX_ARG - opt_count < N) && lua_isnoneornil(state, N)) ||               \
     lua_type_traits<KAGUYA_PP_CAT(A, N)>::strictCheckType(state, N))
#define KAGUYA_CALL_FN_DEF(N)                                                  \
  template <typename F, typename Ret KAGUYA_PP_TEMPLATE_DEF_REPEAT_CONCAT(N)>  \
  inline typename traits::enable_if<!traits::is_same<void, Ret>::value,        \
                                    int>::type                                 \
  _call_apply(lua_State *state, F &f, KAGUYA_FUNC_DEF(N)) {                    \
    KAGUYA_UNUSED(fsig);                                                       \
    return util::push_args(                                                    \
        state, util::invoke<F KAGUYA_INVOKE_SIG_TARG_DEF_REPEAT_CONCAT(N)>(    \
                   f KAGUYA_PP_REPEAT(N, KAGUYA_GET_REP)));                    \
  }                                                                            \
  template <typename F, typename Ret KAGUYA_PP_TEMPLATE_DEF_REPEAT_CONCAT(N)>  \
  inline                                                                       \
      typename traits::enable_if<traits::is_same<void, Ret>::value, int>::type \
      _call_apply(lua_State *state, F &f, KAGUYA_FUNC_DEF(N)) {                \
    KAGUYA_UNUSED(state);                                                      \
    KAGUYA_UNUSED(fsig);                                                       \
    util::invoke<F KAGUYA_INVOKE_SIG_TARG_DEF_REPEAT_CONCAT(N)>(               \
        f KAGUYA_PP_REPEAT(N, KAGUYA_GET_REP));                                \
    return 0;                                                                  \
  }                                                                            \
  template <typename Ret KAGUYA_PP_TEMPLATE_DEF_REPEAT_CONCAT(N)>              \
  bool _ctype_apply(lua_State *state, KAGUYA_FUNC_DEF(N), int opt_count = 0) { \
    KAGUYA_UNUSED(state);                                                      \
    KAGUYA_UNUSED(opt_count);                                                  \
    KAGUYA_UNUSED(fsig);                                                       \
    const int MAX_ARG = N;                                                     \
    (void)MAX_ARG;                                                             \
    return true KAGUYA_PP_REVERSE_REPEAT(N, KAGUYA_TYPECHECK_REP);             \
  }                                                                            \
  template <typename Ret KAGUYA_PP_TEMPLATE_DEF_REPEAT_CONCAT(N)>              \
  bool _sctype_apply(lua_State *state, KAGUYA_FUNC_DEF(N),                     \
                     int opt_count = 0) {                                      \
    KAGUYA_UNUSED(state);                                                      \
    KAGUYA_UNUSED(opt_count);                                                  \
    KAGUYA_UNUSED(fsig);                                                       \
    const int MAX_ARG = N;                                                     \
    (void)MAX_ARG;                                                             \
    return true KAGUYA_PP_REVERSE_REPEAT(N, KAGUYA_STRICT_TYPECHECK_REP);      \
  }                                                                            \
  template <typename Ret KAGUYA_PP_TEMPLATE_DEF_REPEAT_CONCAT(N)>              \
  std::string _type_name_apply(KAGUYA_FUNC_DEF(N), int opt_count) {            \
    KAGUYA_UNUSED(fsig);                                                       \
    KAGUYA_UNUSED(opt_count);                                                  \
    const int MAX_ARG = N;                                                     \
    (void)MAX_ARG;                                                             \
    return std::string() KAGUYA_PP_REPEAT(N, KAGUYA_TYPENAME_REP);             \
  }

KAGUYA_CALL_FN_DEF(0)
KAGUYA_PP_REPEAT_DEF(KAGUYA_FUNCTION_MAX_ARGS, KAGUYA_CALL_FN_DEF)
#undef KAGUYA_CALL_FN_DEF

#undef KAGUYA_CALL_FN_DEF
#undef KAGUYA_FUNC_DEF

template <class F> int call(lua_State *state, F f) {
  typedef typename traits::decay<F>::type ftype;
  typedef typename util::FunctionSignature<ftype>::type fsigtype;
  return _call_apply(state, f, fsigtype());
}
template <class F>
bool checkArgTypes(lua_State *state, const F &, int opt_count = 0) {
  typedef typename traits::decay<F>::type ftype;
  typedef typename util::FunctionSignature<ftype>::type fsigtype;
  return _ctype_apply(state, fsigtype(), opt_count);
}
template <class F>
bool strictCheckArgTypes(lua_State *state, const F &, int opt_count = 0) {
  typedef typename traits::decay<F>::type ftype;
  typedef typename util::FunctionSignature<ftype>::type fsigtype;
  return _sctype_apply(state, fsigtype(), opt_count);
}

template <class F> std::string argTypesName(const F &f, int opt_count = 0) {
  KAGUYA_UNUSED(f);
  typedef typename traits::decay<F>::type ftype;
  typedef typename util::FunctionSignature<ftype>::type fsigtype;
  return _type_name_apply(fsigtype(), opt_count);
}
template <class F> int minArgCount(const F &f) {
  KAGUYA_UNUSED(f);
  typedef typename traits::decay<F>::type ftype;
  typedef typename util::FunctionSignature<ftype>::type fsigtype;
  return fsigtype::argument_count;
}
template <class F> int maxArgCount(const F &f) {
  KAGUYA_UNUSED(f);
  typedef typename traits::decay<F>::type ftype;
  typedef typename util::FunctionSignature<ftype>::type fsigtype;
  return fsigtype::argument_count;
}

///! for constructor
template <typename T> struct ConstructorFunctor;

#define KAGUYA_CONSTRUCTOR_GET_REP(N)                                          \
  lua_type_traits<KAGUYA_PP_CAT(A, N)>::get(L, N)
#define KAGUYA_CONSTRUCTOR_CALL_FN_DEF(N)                                      \
  template <typename ClassType KAGUYA_PP_TEMPLATE_DEF_REPEAT_CONCAT(N)>        \
  struct ConstructorFunctor<util::FunctionSignatureType<                       \
      ClassType KAGUYA_PP_TEMPLATE_ARG_REPEAT_CONCAT(N)> > {                   \
    typedef util::FunctionSignatureType<                                       \
        ClassType KAGUYA_PP_TEMPLATE_ARG_REPEAT_CONCAT(N)>                     \
        signature_type;                                                        \
    int operator()(lua_State *L) const {                                       \
      typedef ObjectWrapper<ClassType> wrapper_type;                           \
      void *storage = lua_newuserdata(L, sizeof(wrapper_type));                \
      try {                                                                    \
        new (storage)                                                          \
            wrapper_type(KAGUYA_PP_REPEAT_ARG(N, KAGUYA_CONSTRUCTOR_GET_REP)); \
      } catch (...) {                                                          \
        lua_pop(L, 1);                                                         \
        throw;                                                                 \
      }                                                                        \
      class_userdata::setmetatable<ClassType>(L);                              \
      return 1;                                                                \
    }                                                                          \
    bool checkArgTypes(lua_State *L, int opt_count = 0) const {                \
      return _ctype_apply(L, signature_type(), opt_count);                     \
    }                                                                          \
    bool strictCheckArgTypes(lua_State *L, int opt_count = 0) const {          \
      return _sctype_apply(L, signature_type(), opt_count);                    \
    }                                                                          \
    std::string argTypesName(int opt_count = 0) const {                        \
      KAGUYA_UNUSED(opt_count);                                                \
      return _type_name_apply(signature_type(), 0);                            \
    }                                                                          \
  };

KAGUYA_CONSTRUCTOR_CALL_FN_DEF(0)
KAGUYA_PP_REPEAT_DEF(KAGUYA_FUNCTION_MAX_ARGS, KAGUYA_CONSTRUCTOR_CALL_FN_DEF)
#undef KAGUYA_CONSTRUCTOR_CALL_FN_DEF

template <class ClassType, class FunType = void> struct ConstructorFunction;

#define KAGUYA_F_TO_CONSIG_TYPE_DEF(N)                                         \
  ConstructorFunctor<util::FunctionSignatureType<                              \
      ClassType KAGUYA_PP_TEMPLATE_ARG_REPEAT_CONCAT(N)> >
#define KAGUYA_F_TO_CONSIG_DEF(N)                                              \
  template <typename ClassType KAGUYA_PP_TEMPLATE_DEF_REPEAT_CONCAT(N)>        \
  struct ConstructorFunction<ClassType(KAGUYA_PP_TEMPLATE_ARG_REPEAT(N))> {    \
    typedef KAGUYA_F_TO_CONSIG_TYPE_DEF(N) type;                               \
  };                                                                           \
  template <typename ClassType,                                                \
            typename RetType KAGUYA_PP_TEMPLATE_DEF_REPEAT_CONCAT(N)>          \
  struct ConstructorFunction<ClassType,                                        \
                             RetType(KAGUYA_PP_TEMPLATE_ARG_REPEAT(N))> {      \
    typedef KAGUYA_F_TO_CONSIG_TYPE_DEF(N) type;                               \
  };

KAGUYA_F_TO_CONSIG_DEF(0)
KAGUYA_PP_REPEAT_DEF(KAGUYA_FUNCTION_MAX_ARGS, KAGUYA_F_TO_CONSIG_DEF)
#undef KAGUYA_F_TO_CONSIG_DEF
}
using nativefunction::ConstructorFunction;
}
