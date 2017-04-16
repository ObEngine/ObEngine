// Copyright satoren
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
#pragma once
#include <iostream>

#if KAGUYA_USE_CXX_ABI_DEMANGLE
#include <cxxabi.h>
#endif

#include "kaguya/config.hpp"
#include "kaguya/compatibility.hpp"
#include "kaguya/traits.hpp"
#include "kaguya/preprocess.hpp"
#include "kaguya/exception.hpp"

#if KAGUYA_USE_CPP11
#include "kaguya/utility_cxx11.hpp"
#else
#include "kaguya/utility_cxx03.hpp"
#endif

namespace kaguya {
namespace util {
/// @brief save stack count and restore on destructor
class ScopedSavedStack {
  lua_State *state_;
  int saved_top_index_;

public:
  /// @brief save stack count
  /// @param state
  explicit ScopedSavedStack(lua_State *state)
      : state_(state), saved_top_index_(state_ ? lua_gettop(state_) : 0) {}

  /// @brief save stack count
  /// @param state
  /// @param count stack count
  explicit ScopedSavedStack(lua_State *state, int count)
      : state_(state), saved_top_index_(count) {}

  /// @brief restore stack count
  ~ScopedSavedStack() {
    if (state_) {
      lua_settop(state_, saved_top_index_);
    }
  }

private:
  ScopedSavedStack(ScopedSavedStack const &);
  ScopedSavedStack &operator=(ScopedSavedStack const &);
};
inline void traceBack(lua_State *state, const char *message, int level = 0) {
#if LUA_VERSION_NUM >= 502
  luaL_traceback(state, state, message, level);
#else
  KAGUYA_UNUSED(level);
  lua_pushstring(state, message);
#endif
}

inline void stackDump(lua_State *L) {
  int i;
  int top = lua_gettop(L);
  for (i = 1; i <= top; i++) { /* repeat for each level */
    int t = lua_type(L, i);
    switch (t) {

    case LUA_TSTRING: /* strings */
      printf("`%s'", lua_tostring(L, i));
      break;

    case LUA_TBOOLEAN: /* booleans */
      printf(lua_toboolean(L, i) ? "true" : "false");
      break;

    case LUA_TNUMBER: /* numbers */
      printf("%g", lua_tonumber(L, i));
      break;
    case LUA_TUSERDATA:
      if (luaL_getmetafield(L, i, "__name") == LUA_TSTRING) {
        printf("userdata:%s", lua_tostring(L, -1));
        lua_pop(L, 1);
        break;
      }
    default: /* other values */
      printf("%s", lua_typename(L, t));
      break;
    }
    printf("  "); /* put a separator */
  }
  printf("\n"); /* end the listing */
}

inline void stackValueDump(std::ostream &os, lua_State *state, int stackIndex,
                           int max_recursive = 2) {
  stackIndex = lua_absindex(state, stackIndex);
  util::ScopedSavedStack save(state);
  int type = lua_type(state, stackIndex);
  switch (type) {
  case LUA_TNONE:
    os << "none";
    break;
  case LUA_TNIL:
    os << "nil";
    break;
  case LUA_TBOOLEAN:
    os << ((lua_toboolean(state, stackIndex) != 0) ? "true" : "false");
    break;
  case LUA_TNUMBER:
    os << lua_tonumber(state, stackIndex);
    break;
  case LUA_TSTRING:
    os << "'" << lua_tostring(state, stackIndex) << "'";
    break;
  case LUA_TTABLE: {
    os << "{";
    if (max_recursive <= 1) {
      os << "...";
    } else {
      lua_pushnil(state);
      if ((lua_next(state, stackIndex) != 0)) {
        stackValueDump(os, state, -2, max_recursive - 1);
        os << "=";
        stackValueDump(os, state, -1, max_recursive - 1);
        lua_pop(state, 1); // pop value

        while (lua_next(state, stackIndex) != 0) {
          os << ",";
          stackValueDump(os, state, -2, max_recursive - 1);
          os << "=";
          stackValueDump(os, state, -1, max_recursive - 1);
          lua_pop(state, 1); // pop value
        }
      }
    }
    os << "}";
  } break;
  case LUA_TUSERDATA:
  case LUA_TLIGHTUSERDATA:
  case LUA_TTHREAD:
    os << lua_typename(state, type) << "(" << lua_topointer(state, stackIndex)
       << ")";
    break;
  case LUA_TFUNCTION:
    os << lua_typename(state, type);
    break;
  default:
    os << "unknown type value";
    break;
  }
}

inline lua_State *toMainThread(lua_State *state) {
#if LUA_VERSION_NUM >= 502
  if (state) {
    lua_rawgeti(state, LUA_REGISTRYINDEX, LUA_RIDX_MAINTHREAD);
    lua_State *mainthread = lua_tothread(state, -1);
    lua_pop(state, 1);
    if (mainthread) {
      return mainthread;
    }
  }
#endif
  return state;
}

#if KAGUYA_USE_CPP11
inline int push_args(lua_State *) { return 0; }
template <class Arg, class... Args>
inline int push_args(lua_State *l, Arg &&arg, Args &&... args) {
  int c = lua_type_traits<typename traits::decay<Arg>::type>::push(
      l, std::forward<Arg>(arg));
  return c + push_args(l, std::forward<Args>(args)...);
}
template <class Arg, class... Args>
inline int push_args(lua_State *l, const Arg &arg, Args &&... args) {
  int c = lua_type_traits<Arg>::push(l, arg);
  return c + push_args(l, std::forward<Args>(args)...);
}
#else
inline int push_args(lua_State *) { return 0; }

#define KAGUYA_PUSH_DEF(N)                                                     \
  c += lua_type_traits<KAGUYA_PP_CAT(A, N)>::push(l, KAGUYA_PP_CAT(a, N));
#define KAGUYA_PUSH_ARG_DEF(N)                                                 \
  template <KAGUYA_PP_TEMPLATE_DEF_REPEAT(N)>                                  \
  inline int push_args(lua_State *l, KAGUYA_PP_ARG_CR_DEF_REPEAT(N)) {         \
    int c = 0;                                                                 \
    KAGUYA_PP_REPEAT(N, KAGUYA_PUSH_DEF)                                       \
    return c;                                                                  \
  }
KAGUYA_PP_REPEAT_DEF(KAGUYA_FUNCTION_MAX_ARGS, KAGUYA_PUSH_ARG_DEF)
#undef KAGUYA_PUSH_DEF
#undef KAGUYA_PUSH_ARG_DEF
#endif

#if KAGUYA_USE_CPP11
template <typename T> inline bool one_push(lua_State *state, T &&v) {
  int count = util::push_args(state, std::forward<T>(v));
  if (count > 1) {
    lua_pop(state, count - 1);
  }
  return count != 0;
}
#else
template <typename T> inline bool one_push(lua_State *state, const T &v) {
  int count = util::push_args(state, v);
  if (count > 1) {
    lua_pop(state, count - 1);
  }
  return count != 0;
}
#endif

inline std::string pretty_name(const std::type_info &t) {
#if KAGUYA_USE_CXX_ABI_DEMANGLE
  int status = 0;
  char *demangle_name = abi::__cxa_demangle(t.name(), 0, 0, &status);
  struct deleter {
    char *data;
    deleter(char *d) : data(d) {}
    ~deleter() { std::free(data); }
  } d(demangle_name);
  return demangle_name;
#else
  return t.name();
#endif
}
}
}
