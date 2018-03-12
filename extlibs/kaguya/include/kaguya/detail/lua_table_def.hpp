// Copyright satoren
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#pragma once

#include <vector>
#include <map>
#include <algorithm>
#include "kaguya/config.hpp"
#include "kaguya/error_handler.hpp"
#include "kaguya/type.hpp"
#include "kaguya/utility.hpp"

namespace kaguya {
class LuaRef;
class LuaStackRef;
class LuaTable;
template <typename KEY> class TableKeyReferenceProxy;
class MemberFunctionBinder;

namespace detail {

struct table_proxy {

#if KAGUYA_USE_CPP11
  template <typename V, typename KEY>
  static void set(lua_State *state, int table_index, KEY &&key, V &&value) {
    util::one_push(state, std::forward<KEY>(key));
    util::one_push(state, std::forward<V>(value));
    lua_settable(state, table_index);
  }
  template <typename V>
  static void set(lua_State *state, int table_index, const char *key,
                  V &&value) {
    util::one_push(state, std::forward<V>(value));
    lua_setfield(state, table_index, key);
  }
  template <typename V>
  static void set(lua_State *state, int table_index, const std::string &key,
                  V &&value) {
    set(state, table_index, key.c_str(), std::forward<V>(value));
  }

  template <typename V>
  static void set(lua_State *state, int table_index, luaInt key, V &&value) {
    util::one_push(state, std::forward<V>(value));
    lua_seti(state, table_index, key);
  }
  template <typename V, typename KEY>
  static void rawset(lua_State *state, int table_index, KEY &&key, V &&value) {
    util::one_push(state, std::forward<KEY>(key));
    util::one_push(state, std::forward<V>(value));
    lua_rawset(state, table_index);
  }
  template <typename V>
  static void rawset(lua_State *state, int table_index, luaInt key, V &&value) {
    util::one_push(state, std::forward<V>(value));
    lua_rawseti(state, table_index, key);
  }
#else
  template <typename V, typename KEY>
  static void set(lua_State *state, int table_index, const KEY &key,
                  const V &value) {
    util::one_push(state, key);
    util::one_push(state, value);
    lua_settable(state, table_index);
  }
  template <typename V>
  static void set(lua_State *state, int table_index, const char *key,
                  const V &value) {
    util::one_push(state, value);
    lua_setfield(state, table_index, key);
  }
  template <typename V>
  static void set(lua_State *state, int table_index, const std::string &key,
                  const V &value) {
    util::one_push(state, value);
    lua_setfield(state, table_index, key.c_str());
  }

  template <typename V>
  static void set(lua_State *state, int table_index, luaInt key,
                  const V &value) {
    util::one_push(state, value);
    lua_seti(state, table_index, key);
  }

  template <typename V, typename KEY>
  static void rawset(lua_State *state, int table_index, const KEY &key,
                     const V &value) {
    util::one_push(state, key);
    util::one_push(state, value);
    lua_rawset(state, table_index);
  }
  template <typename V>
  static void rawset(lua_State *state, int table_index, luaInt key,
                     const V &value) {
    util::one_push(state, value);
    lua_rawseti(state, table_index, key);
  }
#endif

#if KAGUYA_USE_CPP11
  template <typename KEY>
  static void get(lua_State *state, int table_index, KEY &&key) {
    util::one_push(state, std::forward<KEY>(key));
    lua_gettable(state, table_index);
  }
#endif
  template <typename KEY>
  static void get(lua_State *state, int table_index, const KEY &key) {
    util::one_push(state, key);
    lua_gettable(state, table_index);
  }
  static void get(lua_State *state, int table_index, const char *key) {
    lua_getfield(state, table_index, key);
  }
  static void get(lua_State *state, int table_index, const std::string &key) {
    lua_getfield(state, table_index, key.c_str());
  }
  static void get(lua_State *state, int table_index, luaInt key) {
    lua_geti(state, table_index, key);
  }
#if KAGUYA_USE_CPP11
  template <typename KEY>
  static void rawget(lua_State *state, int table_index, KEY &&key) {
    util::one_push(state, std::forward<KEY>(key));
    lua_rawget(state, table_index);
  }
#endif
  template <typename KEY>
  static void rawget(lua_State *state, int table_index, const KEY &key) {
    util::one_push(state, key);
    lua_rawget(state, table_index);
  }
  static void rawget(lua_State *state, int table_index, luaInt key) {
    lua_rawgeti(state, table_index, key);
  }
};

template <typename Derived> class LuaTableOrUserDataImpl {
private:
  lua_State *state_() const {
    return static_cast<const Derived *>(this)->state();
  }
  int pushStackIndex_(lua_State *state) const {
    return static_cast<const Derived *>(this)->pushStackIndex(state);
  }
  int push_(lua_State *state) const {
    return static_cast<const Derived *>(this)->push(state);
  }

public:
  /// @brief set metatable
  /// @param table metatable
  bool setMetatable(const LuaTable &table);

  /// @brief get metatable
  LuaTable getMetatable() const;

  /// @brief table->*"function_name"() in c++ and table:function_name(); in lua
  /// is same
  /// @param function_name function_name in table
  MemberFunctionBinder operator->*(const char *function_name);

  /// @brief value = table[key];
  /// @param key key of table
  /// @return reference of field value
  template <typename T, typename KEY>
  typename lua_type_traits<T>::get_type getField(const KEY &key) const {
    lua_State *state = state_();
    typedef typename lua_type_traits<T>::get_type get_type;
    if (!state) {
      except::typeMismatchError(state, "is nil");
      return get_type();
    }
    util::ScopedSavedStack save(state);
    int stackIndex = pushStackIndex_(state);

    table_proxy::get(state, stackIndex, key);

    return lua_type_traits<T>::get(state, -1);
  }

  /// @brief value = table[key];
  /// @param key key of table
  /// @return reference of field value
  template <typename KEY> LuaStackRef getField(const KEY &key) const;

#if KAGUYA_USE_CPP11
  /// @brief table[key] = value;
  template <typename K, typename V> bool setField(K &&key, V &&value) {
    lua_State *state = state_();
    if (!state) {
      except::typeMismatchError(state, "is nil");
      return false;
    }
    util::ScopedSavedStack save(state);
    int stackIndex = pushStackIndex_(state);

    table_proxy::set(state, stackIndex, std::forward<K>(key),
                     std::forward<V>(value));
    return true;
  }
#else
  /// @brief table[key] = value;
  template <typename K, typename V>
  bool setField(const K &key, const V &value) {
    lua_State *state = state_();
    if (!state) {
      except::typeMismatchError(state, "is nil");
      return false;
    }
    util::ScopedSavedStack save(state);
    int stackIndex = pushStackIndex_(state);

    table_proxy::set(state, stackIndex, key, value);

    return true;
  }
#endif

  /// @brief value = table[key];
  /// @param key key of table
  /// @return reference of field value
  template <typename K> LuaStackRef operator[](K key) const;

  /// @brief value = table[key];or table[key] = value;
  /// @param key key of table
  /// @return reference of field value
  template <typename K> TableKeyReferenceProxy<K> operator[](K key);
};

template <typename Derived> class LuaTableImpl {
private:
  lua_State *state_() const {
    return static_cast<const Derived *>(this)->state();
  }
  int pushStackIndex_(lua_State *state) const {
    return static_cast<const Derived *>(this)->pushStackIndex(state);
  }
  int push_(lua_State *state) const {
    return static_cast<const Derived *>(this)->push(state);
  }

  template <typename K, typename A> struct gettablekey {
    typedef K key_type;
    typedef void value_type;
    std::vector<K, A> &v_;
    gettablekey(std::vector<K, A> &v) : v_(v) {}
    void operator()(K key, const void *) { v_.push_back(key); }
  };
  template <typename V, typename A> struct gettablevalue {
    typedef void key_type;
    typedef V value_type;
    std::vector<V, A> &v_;
    gettablevalue(std::vector<V, A> &v) : v_(v) {}
    void operator()(const void *, V value) { v_.push_back(value); }
  };
  template <typename K, typename V, typename C, typename A> struct gettablemap {
    typedef K key_type;
    typedef V value_type;
    std::map<K, V, C, A> &m_;
    gettablemap(std::map<K, V, C, A> &m) : m_(m) {}
    void operator()(K key, V value) { m_[key] = value; }
  };

public:
#if KAGUYA_USE_CPP11
  /// @brief rawset(table,key,value)
  template <typename K, typename V> bool setRawField(K &&key, V &&value) {
    lua_State *state = state_();
    if (!state) {
      except::typeMismatchError(state, "is nil");
      return false;
    }
    util::ScopedSavedStack save(state);
    int stackIndex = pushStackIndex_(state);

    table_proxy::rawset(state, stackIndex, std::forward<K>(key),
                        std::forward<V>(value));

    return true;
  }
#else
  /// @brief rawset(table,key,value)
  template <typename K, typename V>
  bool setRawField(const K &key, const V &value) {
    lua_State *state = state_();
    if (!state) {
      except::typeMismatchError(state, "is nil");
      return false;
    }
    util::ScopedSavedStack save(state);
    int stackIndex = pushStackIndex_(state);
    table_proxy::rawset(state, stackIndex, key, value);
    return true;
  }
#endif
  /// @brief value = rawget(table,key);
  /// @param key key of table
  /// @return reference of field value
  template <typename T, typename KEY>
  typename lua_type_traits<T>::get_type getRawField(const KEY &key) const {
    lua_State *state = state_();
    typedef typename lua_type_traits<T>::get_type get_type;
    if (!state) {
      except::typeMismatchError(state, "is nil");
      return get_type();
    }
    util::ScopedSavedStack save(state);
    int stackIndex = pushStackIndex_(state);

    table_proxy::rawget(state, stackIndex, key);

    return lua_type_traits<T>::get(state, -1);
  }
  /// @brief value = rawget(table,key);
  /// @param key key of table
  /// @return reference of field value
  template <typename KEY> LuaStackRef getRawField(const KEY &key) const;

  /// @brief foreach table fields
  template <class K, class V, class Fun> void foreach_table(Fun f) const {
    lua_State *state = state_();
    if (!state) {
      except::typeMismatchError(state, "is nil");
      return;
    }
    util::ScopedSavedStack save(state);
    int stackIndex = pushStackIndex_(state);
    lua_pushnil(state);
    while (lua_next(state, stackIndex) != 0) {
      // backup key
      lua_pushvalue(state, -2);

      f(lua_type_traits<K>::get(state, -1), lua_type_traits<V>::get(state, -2));
      lua_pop(state, 2); // pop key and value
    }
  }

  /// @brief foreach table fields
  template <class K, class V, class Fun>
  void foreach_table_breakable(Fun f) const {
    lua_State *state = state_();
    if (!state) {
      except::typeMismatchError(state, "is nil");
      return;
    }
    util::ScopedSavedStack save(state);
    int stackIndex = pushStackIndex_(state);
    lua_pushnil(state);
    while (lua_next(state, stackIndex) != 0) {
      lua_pushvalue(state, -2); // backup key

      bool cont = f(lua_type_traits<K>::get(state, -1),
                    lua_type_traits<V>::get(state, -2));
      lua_pop(state, 2); // pop key and value
      if (!cont) {
        break;
      }
    }
  }

  /// @brief If type is table or userdata, return keys.
  /// @return field keys
  template <typename K, typename A> std::vector<K, A> keys() const {
    std::vector<K, A> res;
    util::ScopedSavedStack save(state_());
    int stackIndex = pushStackIndex_(state_());
    size_t size = lua_rawlen(state_(), stackIndex);
    res.reserve(size);
    foreach_table<K, void>(gettablekey<K, A>(res));
    return res;
  }

  /// @brief If type is table or userdata, return keys.
  /// @return field keys
  template <typename K> std::vector<K> keys() const {
    return keys<K, std::allocator<K> >();
  }
  std::vector<LuaRef> keys() const;

  /// @brief If type is table or userdata, return values.
  /// @return field value
  template <typename V, typename A> std::vector<V, A> values() const {
    std::vector<V, A> res;
    util::ScopedSavedStack save(state_());
    int stackIndex = pushStackIndex_(state_());
    size_t size = lua_rawlen(state_(), stackIndex);
    res.reserve(size);
    foreach_table<void, V>(gettablevalue<V, A>(res));
    return res;
  }

  /// @brief If type is table or userdata, return values.
  /// @return field value
  template <typename V> std::vector<V> values() const {
    return values<V, std::allocator<V> >();
  }
  std::vector<LuaRef> values() const;

  /// @brief If type is table or userdata, return key value pair.
  /// @return key value pair
  template <typename K, typename V, typename C, typename A>
  std::map<K, V, C, A> map() const {
    std::map<K, V, C, A> res;
    foreach_table<K, V>(gettablemap<K, V, C, A>(res));
    return res;
  }

  /// @brief If type is table or userdata, return key value pair.
  /// @return key value pair
  template <typename K, typename V, typename C> std::map<K, V, C> map() const {
    return map<K, V, C, std::allocator<std::pair<const K, V> > >();
  }

  /// @brief If type is table or userdata, return key value pair.
  /// @return key value pair
  template <typename K, typename V> std::map<K, V> map() const {
    return map<K, V, std::less<K> >();
  }
  std::map<LuaRef, LuaRef> map() const;
};

template <typename Derived> class LuaUserDataImpl {
private:
  lua_State *state_() const {
    return static_cast<const Derived *>(this)->state();
  }
  int pushStackIndex_(lua_State *state) const {
    return static_cast<const Derived *>(this)->pushStackIndex(state);
  }
  int push_(lua_State *state) const {
    return static_cast<const Derived *>(this)->push(state);
  }

public:
  /// @brief is type test
  template <typename T> bool isType() const {
    lua_State *state = state_();
    util::ScopedSavedStack save(state);
    return lua_type_traits<T>::strictCheckType(state, pushStackIndex_(state));
  }

  template <typename T> bool isConvertible() const {
    lua_State *state = state_();
    util::ScopedSavedStack save(state);
    return lua_type_traits<T>::checkType(state, pushStackIndex_(state));
  }

  template <typename T> bool typeTest() const { return isType<T>(); }
  template <typename T> bool weakTypeTest() const { return isConvertible<T>(); }

  template <typename T> typename lua_type_traits<T>::get_type get() const {
    lua_State *state = state_();
    util::ScopedSavedStack save(state);
    return lua_type_traits<T>::get(state, state ? pushStackIndex_(state) : 0);
  }

  template <typename T> operator T() const { return get<T>(); }
};
}
}
