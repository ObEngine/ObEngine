// Copyright satoren
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
#pragma once

#include "kaguya/config.hpp"

namespace kaguya {
// for lua version compatibility
namespace compat {
#if LUA_VERSION_NUM >= 503
inline int lua_rawgetp_rtype(lua_State *L, int idx, const void *ptr) {
  return lua_rawgetp(L, idx, ptr);
}
inline int lua_rawget_rtype(lua_State *L, int idx) {
  return lua_rawget(L, idx);
}
inline int lua_getfield_rtype(lua_State *L, int idx, const char *k) {
  return lua_getfield(L, idx, k);
}
inline int lua_gettable_rtype(lua_State *L, int idx) {
  return lua_gettable(L, idx);
}
#elif LUA_VERSION_NUM == 502
inline int lua_rawgetp_rtype(lua_State *L, int idx, const void *ptr) {
  lua_rawgetp(L, idx, ptr);
  return lua_type(L, -1);
}
#elif LUA_VERSION_NUM < 502
enum LUA_OPEQ { LUA_OPEQ, LUA_OPLT, LUA_OPLE };
inline int lua_compare(lua_State *L, int index1, int index2, int op) {
  switch (op) {
  case LUA_OPEQ:
    return lua_equal(L, index1, index2);
  case LUA_OPLT:
    return lua_lessthan(L, index1, index2);
  case LUA_OPLE:
    return lua_equal(L, index1, index2) || lua_lessthan(L, index1, index2);
  default:
    return 0;
  }
}

inline void lua_pushglobaltable(lua_State *L) {
  lua_pushvalue(L, LUA_GLOBALSINDEX);
}
inline size_t lua_rawlen(lua_State *L, int index) {
  int type = lua_type(L, index);
  if (type != LUA_TSTRING && type != LUA_TTABLE && type != LUA_TUSERDATA &&
      type != LUA_TLIGHTUSERDATA) {
    return 0;
  }
  return lua_objlen(L, index);
}

inline int lua_resume(lua_State *L, lua_State *from, int nargs) {
  KAGUYA_UNUSED(from);
  return ::lua_resume(L, nargs);
}
inline int lua_absindex(lua_State *L, int idx) {
  return (idx > 0 || (idx <= LUA_REGISTRYINDEX)) ? idx
                                                 : lua_gettop(L) + 1 + idx;
}
inline int lua_rawgetp_rtype(lua_State *L, int idx, const void *ptr) {
  int absidx = lua_absindex(L, idx);
  lua_pushlightuserdata(L, (void *)ptr);
  lua_rawget(L, absidx);
  return lua_type(L, -1);
}
inline void lua_rawsetp(lua_State *L, int idx, const void *ptr) {
  int absidx = lua_absindex(L, idx);
  lua_pushvalue(L, -1);
  lua_pushlightuserdata(L, (void *)ptr);
  lua_replace(L, -3);
  lua_rawset(L, absidx);
}
inline void luaL_requiref(lua_State *L, const char *modname,
                          lua_CFunction openf, int glb) {

  lua_pushcfunction(L, openf);
  lua_pushstring(L, modname);
  lua_call(L, 1, 1);

  if (glb) {
    lua_pushvalue(L, -1);
    lua_setglobal(L, modname);
  }
}
inline lua_Number lua_tonumberx(lua_State *L, int index, int *isnum) {
  if (isnum) {
    *isnum = lua_isnumber(L, index);
  }
  return lua_tonumber(L, index);
}
#endif
#if LUA_VERSION_NUM < 503
inline void lua_seti(lua_State *L, int index, lua_Integer n) {
  int absidx = lua_absindex(L, index);
  lua_pushvalue(L, -1);
  lua_pushinteger(L, n);
  lua_replace(L, -3);
  lua_rawset(L, absidx);
}
inline int lua_geti(lua_State *L, int index, lua_Integer i) {
  int absidx = lua_absindex(L, index);
  lua_pushinteger(L, i);
  lua_rawget(L, absidx);
  return lua_type(L, -1);
}
inline int lua_getfield_rtype(lua_State *L, int idx, const char *k) {
  lua_getfield(L, idx, k);
  return lua_type(L, -1);
}
inline int lua_gettable_rtype(lua_State *L, int idx) {
  lua_gettable(L, idx);
  return lua_type(L, -1);
}
inline int lua_rawget_rtype(lua_State *L, int idx) {
  lua_rawget(L, idx);
  return lua_type(L, -1);
}
#endif
#if LUA_VERSION_NUM < 501
void lua_createtable(lua_State *L, int narr, int nrec) { lua_newtable(L); }
#endif
}

using namespace compat;
}
