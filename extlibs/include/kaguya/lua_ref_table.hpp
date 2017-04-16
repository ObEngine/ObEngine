// Copyright satoren
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#pragma once

#include <vector>
#include <map>
#include "kaguya/config.hpp"
#include "kaguya/lua_ref.hpp"
#include "kaguya/push_any.hpp"
#include "kaguya/detail/lua_ref_impl.hpp"
#include "kaguya/detail/lua_table_def.hpp"

namespace kaguya {
class State;

/**
* This class is the type returned by members of non-const LuaRef(Table) when
* directly accessing its elements.
*/
template <typename KEY>
class TableKeyReferenceProxy
    : public detail::LuaVariantImpl<TableKeyReferenceProxy<KEY> > {
public:
  int pushStackIndex(lua_State *state) const {
    push(state);
    return lua_gettop(state);
  }
  lua_State *state() const { return state_; }

  friend class LuaRef;
  friend class State;

  //! this is not copy.same assign from referenced value.
  TableKeyReferenceProxy &operator=(const TableKeyReferenceProxy &src) {
    detail::table_proxy::set(state_, table_index_, key_, src);
    return *this;
  }

  //! assign from T
  template <typename T> TableKeyReferenceProxy &operator=(const T &src) {
    detail::table_proxy::set(state_, table_index_, key_, src);
    return *this;
  }
#if KAGUYA_USE_CPP11
  template <typename T> TableKeyReferenceProxy &operator=(T &&src) {
    detail::table_proxy::set(state_, table_index_, key_, std::forward<T>(src));
    return *this;
  }
#endif

  bool isNilref() const {
    if (!state_) {
      return false;
    }
    util::ScopedSavedStack save(state_);
    push(state_);
    return lua_isnoneornil(state_, -1);
  }

  //! register class metatable to lua and set to table
  template <typename T, typename P>
  void setClass(const UserdataMetatable<T, P> &reg) {
    set_class(reg);
  }

  //! set function
  template <typename T> void setFunction(T f) {
    detail::table_proxy::set(state_, table_index_, key_, kaguya::function(f));
  }

  int push(lua_State *state) const {
    int type = lua_type(state_, table_index_);
    if (type != LUA_TTABLE && type != LUA_TUSERDATA) {
      lua_pushnil(state);
      return 1;
    }

    detail::table_proxy::get(state_, table_index_, key_);

    if (state_ != state) {
      lua_xmove(state_, state, 1);
    }
    return 1;
  }

  int push() const { return push(state_); }

  int type() const {
    util::ScopedSavedStack save(state_);
    push();
    return lua_type(state_, -1);
  }

  ~TableKeyReferenceProxy() {
    if (state_) {
      lua_settop(state_, stack_top_);
    }
  }

  ///!constructs the reference. Accessible only to kaguya::LuaRef itself
  TableKeyReferenceProxy(const TableKeyReferenceProxy &src)
      : state_(src.state_), stack_top_(src.stack_top_),
        table_index_(src.table_index_), key_(src.key_) {
    src.state_ = 0;
  }

  ///!constructs the reference. Accessible only to kaguya::LuaRef itself
  TableKeyReferenceProxy(lua_State *state, int table_index, KEY key,
                         int revstacktop)
      : state_(state), stack_top_(revstacktop), table_index_(table_index),
        key_(key) {}

private:
  template <typename T, typename P>
  void set_class(const UserdataMetatable<T, P> &reg) {
    detail::table_proxy::set(state_, table_index_, key_,
                             reg.createMatatable(state_));
  }

  ///!constructs the reference. Accessible only to kaguya::LuaRef itself
  TableKeyReferenceProxy(lua_State *state, int table_index, const KEY &key,
                         int revstacktop, const NoTypeCheck &)
      : state_(state), stack_top_(revstacktop), table_index_(table_index),
        key_(key) {}

  TableKeyReferenceProxy(const LuaTable &table, const KEY &key)
      : state_(table.state()), stack_top_(lua_gettop(state_)), key_(key) {
    util::one_push(state_, table);
    table_index_ = stack_top_ + 1;
  }
  TableKeyReferenceProxy(const LuaRef &table, const KEY &key)
      : state_(table.state()), stack_top_(lua_gettop(state_)), key_(key) {
    util::one_push(state_, table);
    table_index_ = stack_top_ + 1;
    int t = lua_type(state_, table_index_);
    if (t != LUA_TTABLE) {
      except::typeMismatchError(state_, lua_typename(state_, t) +
                                            std::string(" is not table"));
    }
  }

  mutable lua_State *state_; // mutable for RVO unsupported compiler
  int stack_top_;
  int table_index_;
  KEY key_;
};

template <typename KEY>
inline std::ostream &operator<<(std::ostream &os,
                                const TableKeyReferenceProxy<KEY> &ref) {
  lua_State *state = ref.state();
  util::ScopedSavedStack save(state);
  int stackIndex = ref.pushStackIndex(state);
  util::stackValueDump(os, state, stackIndex);
  return os;
}

namespace detail {
template <typename T>
inline bool LuaFunctionImpl<T>::setFunctionEnv(const LuaTable &env) {
  lua_State *state = state_();
  if (!state) {
    return false;
  }
  util::ScopedSavedStack save(state);
  int stackIndex = pushStackIndex_(state);
  int t = lua_type(state, stackIndex);
  if (t != LUA_TFUNCTION) {
    except::typeMismatchError(state, lua_typename(state, t) +
                                         std::string(" is not function"));
    return false;
  }
  env.push(state);
#if LUA_VERSION_NUM >= 502
  lua_setupvalue(state, stackIndex, 1);
#else
  lua_setfenv(state, stackIndex);
#endif
  return true;
}
template <typename T> inline bool LuaFunctionImpl<T>::setFunctionEnv(NewTable) {
  return setFunctionEnv(LuaTable(state_()));
}

template <typename T>
inline LuaTable LuaFunctionImpl<T>::getFunctionEnv() const {
  lua_State *state = state_();
  util::ScopedSavedStack save(state);
  if (!state) {
    except::typeMismatchError(state, "is nil");
    return LuaTable();
  }
  int stackIndex = pushStackIndex_(state);
  int t = lua_type(state, stackIndex);
  if (t != LUA_TFUNCTION) {
    except::typeMismatchError(state, lua_typename(state, t) +
                                         std::string(" is not function"));
    return LuaTable();
  }
#if LUA_VERSION_NUM >= 502
  lua_getupvalue(state, stackIndex, 1);
#else
  lua_getfenv(state, stackIndex);
#endif
  return LuaTable(state, StackTop());
}

template <typename T> void LuaThreadImpl<T>::setFunction(const LuaFunction &f) {
  lua_State *corstate = getthread();
  if (corstate) {
    lua_settop(corstate, 0);
    f.push(corstate);
  }
}

template <typename T>
bool LuaTableOrUserDataImpl<T>::setMetatable(const LuaTable &table) {
  lua_State *state = state_();
  if (!state) {
    except::typeMismatchError(state, "is nil");
    return false;
  }
  util::ScopedSavedStack save(state);
  int stackindex = pushStackIndex_(state);
  int t = lua_type(state, stackindex);
  if (t != LUA_TTABLE && t != LUA_TUSERDATA) {
    except::typeMismatchError(state, lua_typename(state, t) +
                                         std::string(" is not table"));
    return false;
  }
  table.push();
  return lua_setmetatable(state, stackindex) != 0;
}
template <typename T> LuaTable LuaTableOrUserDataImpl<T>::getMetatable() const {
  lua_State *state = state_();
  if (!state) {
    except::typeMismatchError(state, "is nil");
    return LuaTable();
  }
  util::ScopedSavedStack save(state);
  int stackindex = pushStackIndex_(state);
  int t = lua_type(state, stackindex);
  if (t != LUA_TTABLE && t != LUA_TUSERDATA) {
    except::typeMismatchError(state, lua_typename(state, t) +
                                         std::string(" is not table"));
    return LuaTable();
  }
  if (!lua_getmetatable(state, stackindex)) {
    lua_pushnil(state);
  }
  return LuaTable(state, StackTop());
}
template <typename T>
MemberFunctionBinder LuaTableOrUserDataImpl<T>::
operator->*(const char *function_name) {
  push_(state_());
  return MemberFunctionBinder(LuaRef(state_(), StackTop()), function_name);
}

template <typename T>
template <typename KEY>
LuaStackRef LuaTableOrUserDataImpl<T>::getField(const KEY &key) const {
  lua_State *state = state_();
  if (!state) {
    except::typeMismatchError(state, "is nil");
    return LuaStackRef();
  }
  push_(state);
  detail::table_proxy::get(state, lua_gettop(state), key);
  lua_remove(state, -2); // remove table
  return LuaStackRef(state, -1, true);
}
template <typename T>
template <typename KEY>
LuaStackRef LuaTableImpl<T>::getRawField(const KEY &key) const {
  lua_State *state = state_();
  if (!state) {
    except::typeMismatchError(state, "is nil");
    return LuaStackRef();
  }
  push_(state);
  detail::table_proxy::rawget(state, lua_gettop(state), key);
  lua_remove(state, -2); // remove table
  return LuaStackRef(state, -1, true);
}

template <typename T>
template <typename KEY>
LuaStackRef LuaTableOrUserDataImpl<T>::operator[](KEY key) const {
  return getField(key);
}

template <typename T> std::vector<LuaRef> LuaTableImpl<T>::values() const {
  return values<LuaRef>();
}
template <typename T> std::vector<LuaRef> LuaTableImpl<T>::keys() const {
  return keys<LuaRef>();
}
template <typename T> std::map<LuaRef, LuaRef> LuaTableImpl<T>::map() const {
  return map<LuaRef, LuaRef>();
}

template <typename T>
template <typename K>
TableKeyReferenceProxy<K> LuaTableOrUserDataImpl<T>::operator[](K key) {
  lua_State *state = state_();
  int stack_top = lua_gettop(state);
  int stackindex = pushStackIndex_(state);
  return TableKeyReferenceProxy<K>(state, stackindex, key, stack_top);
}
}

/// @ingroup lua_type_traits
/// @brief lua_type_traits for TableKeyReferenceProxy<KEY>
template <typename KEY> struct lua_type_traits<TableKeyReferenceProxy<KEY> > {
  static int push(lua_State *l, const TableKeyReferenceProxy<KEY> &ref) {
    return ref.push(l);
  }
};

#if KAGUYA_USE_CPP11
/// @ingroup lua_type_traits
/// @brief lua_type_traits for std::array<T, A>
template <typename T, size_t S> struct lua_type_traits<std::array<T, S> > {
  typedef std::array<T, S> get_type;
  typedef const std::array<T, S> &push_type;

  static bool checkType(lua_State *l, int index) {
    if (lua_type(l, index) != LUA_TTABLE) {
      return false;
    }

    LuaStackRef table(l, index);
    if (table.size() != S) {
      return false;
    } // TODO
    bool valid = true;
    table.foreach_table_breakable<LuaStackRef, LuaStackRef>(
        [&](const LuaStackRef &k, const LuaStackRef &v) {
          valid = valid && k.typeTest<size_t>() && v.typeTest<T>();
          return valid;
        });
    return valid;
  }
  static bool strictCheckType(lua_State *l, int index) {
    if (lua_type(l, index) != LUA_TTABLE) {
      return false;
    }

    LuaStackRef table(l, index);
    if (table.size() != S) {
      return false;
    } // TODO
    bool valid = true;
    table.foreach_table_breakable<LuaStackRef, LuaStackRef>(
        [&](const LuaStackRef &k, const LuaStackRef &v) {
          valid = valid && k.typeTest<size_t>() && v.typeTest<T>();
          return valid;
        });
    return valid;
  }
  static get_type get(lua_State *l, int index) {
    if (lua_type(l, index) != LUA_TTABLE) {
      except::typeMismatchError(l, std::string("type mismatch"));
      return get_type();
    }
    LuaStackRef t(l, index);
    if (t.size() != S) // TODO
    {
      except::typeMismatchError(l, std::string("type mismatch"));
    }
    get_type res;
    t.foreach_table<size_t, const T &>([&](size_t k, const T &v) {
      if (k > 0 && k <= S) {
        res[k - 1] = v;
      }
    });
    return res;
  }
  static int push(lua_State *l, push_type v) {
    lua_createtable(l, int(S), 0);
    for (size_t i = 0; i < S; ++i) {
      util::one_push(l, v[i]);
      lua_rawseti(l, -2, i + 1);
    }
    return 1;
  }
};
#endif
#ifndef KAGUYA_NO_STD_VECTOR_TO_TABLE

/// @ingroup lua_type_traits
/// @brief lua_type_traits for std::vector<T, A>
template <typename T, typename A> struct lua_type_traits<std::vector<T, A> > {
  typedef std::vector<T, A> get_type;
  typedef const std::vector<T, A> &push_type;
  struct checkTypeForEach {
    checkTypeForEach(bool &valid) : valid_(valid) {}
    bool &valid_;
    bool operator()(const LuaStackRef &k, const LuaStackRef &v) {
      valid_ = k.typeTest<size_t>() && v.weakTypeTest<T>();
      return valid_;
    }
  };
  struct strictCheckTypeForEach {
    strictCheckTypeForEach(bool &valid) : valid_(valid) {}
    bool &valid_;
    bool operator()(const LuaStackRef &k, const LuaStackRef &v) {
      valid_ = k.typeTest<size_t>() && v.typeTest<T>();
      return valid_;
    }
  };

  static bool checkType(lua_State *l, int index) {
    LuaStackRef table(l, index);
    if (table.type() != LuaRef::TYPE_TABLE) {
      return false;
    }

    bool valid = true;
    table.foreach_table_breakable<LuaStackRef, LuaStackRef>(
        checkTypeForEach(valid));
    return valid;
  }
  static bool strictCheckType(lua_State *l, int index) {
    LuaStackRef table(l, index);
    if (table.type() != LuaRef::TYPE_TABLE) {
      return false;
    }

    bool valid = true;
    table.foreach_table_breakable<LuaStackRef, LuaStackRef>(
        strictCheckTypeForEach(valid));
    return valid;
  }

  static get_type get(lua_State *l, int index) {
    if (lua_type(l, index) != LUA_TTABLE) {
      except::typeMismatchError(l, std::string("type mismatch"));
      return get_type();
    }
    return LuaStackRef(l, index).values<T>();
  }
#if KAGUYA_USE_CPP11
  typedef std::vector<T, A> &&move_push_type;
  static int push(lua_State *l, move_push_type v) {
    lua_createtable(l, int(v.size()), 0);
    int count = 1; // array is 1 origin in Lua
    for (typename std::vector<T, A>::iterator it = v.begin(); it != v.end();
         ++it) {
      util::one_push(l, static_cast<T &&>(*it));
      lua_rawseti(l, -2, count++);
    }
    return 1;
  }
#endif
  static int push(lua_State *l, push_type v) {
    lua_createtable(l, int(v.size()), 0);
    int count = 1; // array is 1 origin in Lua
    for (typename std::vector<T, A>::const_iterator it = v.begin();
         it != v.end(); ++it) {
      util::one_push(l, *it);
      lua_rawseti(l, -2, count++);
    }
    return 1;
  }
};
#endif

#ifndef KAGUYA_NO_STD_MAP_TO_TABLE
/// @ingroup lua_type_traits
/// @brief lua_type_traits for std::map<K, V, C, A>
template <typename K, typename V, typename C, typename A>
struct lua_type_traits<std::map<K, V, C, A> > {
  typedef std::map<K, V, C, A> get_type;
  typedef const std::map<K, V, C, A> &push_type;

  struct checkTypeForEach {
    checkTypeForEach(bool &valid) : valid_(valid) {}
    bool &valid_;
    bool operator()(const LuaStackRef &k, const LuaStackRef &v) {
      valid_ = k.weakTypeTest<K>() && v.weakTypeTest<V>();
      return valid_;
    }
  };
  struct strictCheckTypeForEach {
    strictCheckTypeForEach(bool &valid) : valid_(valid) {}
    bool &valid_;
    bool operator()(const LuaStackRef &k, const LuaStackRef &v) {
      valid_ = k.typeTest<K>() && v.typeTest<V>();
      return valid_;
    }
  };
  static bool checkType(lua_State *l, int index) {
    LuaStackRef table(l, index);
    if (table.type() != LuaRef::TYPE_TABLE) {
      return false;
    }

    bool valid = true;
    table.foreach_table_breakable<LuaStackRef, LuaStackRef>(
        checkTypeForEach(valid));
    return valid;
  }
  static bool strictCheckType(lua_State *l, int index) {
    LuaStackRef table(l, index);
    if (table.type() != LuaRef::TYPE_TABLE) {
      return false;
    }

    bool valid = true;
    table.foreach_table_breakable<LuaStackRef, LuaStackRef>(
        strictCheckTypeForEach(valid));
    return valid;
  }

  static get_type get(lua_State *l, int index) {
    if (lua_type(l, index) != LUA_TTABLE) {
      except::typeMismatchError(l, std::string("type mismatch"));
      return get_type();
    }
    return LuaStackRef(l, index).map<K, V>();
  }
  static int push(lua_State *l, push_type v) {
    lua_createtable(l, 0, int(v.size()));
    for (typename std::map<K, V, C, A>::const_iterator it = v.begin();
         it != v.end(); ++it) {
      util::one_push(l, it->first);
      util::one_push(l, it->second);
      lua_rawset(l, -3);
    }
    return 1;
  }
};
#endif

struct TableDataElement {
  typedef std::pair<AnyDataPusher, AnyDataPusher> keyvalue_type;

  template <typename Value>
  TableDataElement(Value value)
      : keyvalue(keyvalue_type(AnyDataPusher(), value)) {}

  template <typename Key, typename Value>
  TableDataElement(Key key, Value value)
      : keyvalue(keyvalue_type(key, value)) {}
  std::pair<AnyDataPusher, AnyDataPusher> keyvalue;
};

struct TableData {
  typedef std::pair<AnyDataPusher, AnyDataPusher> data_type;

#if KAGUYA_USE_CPP11
  TableData(std::initializer_list<TableDataElement> list)
      : elements(list.begin(), list.end()) {}
#endif
  template <typename IT> TableData(IT beg, IT end) : elements(beg, end) {}

  TableData() {}
  std::vector<TableDataElement> elements;
};

/// @ingroup lua_type_traits
/// @brief lua_type_traits for TableData
template <> struct lua_type_traits<TableData> {
  static int push(lua_State *l, const TableData &list) {
    lua_createtable(l, int(list.elements.size()), int(list.elements.size()));
    int count = 1; // array is 1 origin in Lua
    for (std::vector<TableDataElement>::const_iterator it =
             list.elements.begin();
         it != list.elements.end(); ++it) {
      const TableDataElement &v = *it;
      if (v.keyvalue.first.empty()) {
        util::one_push(l, v.keyvalue.second);
        lua_rawseti(l, -2, count++);
      } else {
        util::one_push(l, v.keyvalue.first);
        util::one_push(l, v.keyvalue.second);
        lua_rawset(l, -3);
      }
    }
    return 1;
  }
};
}
