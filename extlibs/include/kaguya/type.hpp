// Copyright satoren
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#pragma once

#include <string>
#include <cstring>

#include "kaguya/config.hpp"
#include "kaguya/optional.hpp"
#include "kaguya/traits.hpp"
#include "kaguya/object.hpp"
#include "kaguya/exception.hpp"
#include "kaguya/push_tuple.hpp"

namespace kaguya {

// default implements
template <typename T, typename Enable>
bool lua_type_traits<T, Enable>::checkType(lua_State *l, int index) {
  return object_wrapper<T>(l, index) != 0;
}
template <typename T, typename Enable>
bool lua_type_traits<T, Enable>::strictCheckType(lua_State *l, int index) {
  return object_wrapper<T>(l, index, false) != 0;
}
template <typename T, typename Enable>
typename lua_type_traits<T, Enable>::opt_type
lua_type_traits<T, Enable>::opt(lua_State *l, int index) KAGUYA_NOEXCEPT {
  const typename traits::remove_reference<T>::type *pointer = get_const_pointer(
      l, index, types::typetag<typename traits::remove_reference<T>::type>());
  if (!pointer) {
    return opt_type();
  }
  return *pointer;
}
template <typename T, typename Enable>
typename lua_type_traits<T, Enable>::get_type
lua_type_traits<T, Enable>::get(lua_State *l, int index) {
  const typename traits::remove_reference<T>::type *pointer = get_const_pointer(
      l, index, types::typetag<typename traits::remove_reference<T>::type>());
  if (!pointer) {
    throw LuaTypeMismatch();
  }
  return *pointer;
}
template <typename T, typename Enable>
int lua_type_traits<T, Enable>::push(lua_State *l, push_type v) {
  return util::object_push(l, v);
}

#if KAGUYA_USE_RVALUE_REFERENCE

template <typename T, typename Enable>
int lua_type_traits<T, Enable>::push(lua_State *l, NCRT &&v) {
  return util::object_push(l, std::forward<NCRT>(v));
}
#endif

/// @ingroup lua_type_traits
/// @brief lua_type_traits for const reference type
template <typename T>
struct lua_type_traits<
    T, typename traits::enable_if<traits::is_const_reference<T>::value>::type>
    : lua_type_traits<typename traits::remove_const_reference<T>::type> {};

/// @ingroup lua_type_traits
/// @brief lua_type_traits for lvalue reference type
template <typename REF>
struct lua_type_traits<
    REF, typename traits::enable_if<
             traits::is_lvalue_reference<REF>::value &&
             !traits::is_const<
                 typename traits::remove_reference<REF>::type>::value>::type> {
  typedef void Registerable;

  typedef REF get_type;
  typedef optional<get_type> opt_type;
  typedef REF push_type;
  typedef typename traits::remove_reference<REF>::type T;

  static bool strictCheckType(lua_State *l, int index) {
    return object_wrapper<T>(l, index, false) != 0;
  }
  static bool checkType(lua_State *l, int index) {
    if (lua_type(l, index) == LUA_TLIGHTUSERDATA) {
      return true;
    }
    return object_wrapper<T>(l, index) != 0;
  }
  static get_type get(lua_State *l, int index) {
    T *pointer = get_pointer(l, index, types::typetag<T>());
    if (!pointer) {
      throw LuaTypeMismatch();
    }
    return *pointer;
  }
  static opt_type opt(lua_State *l, int index) KAGUYA_NOEXCEPT {
    T *pointer = get_pointer(l, index, types::typetag<T>());
    if (!pointer) {
      return opt_type();
    }
    return opt_type(*pointer);
  }
  static int push(lua_State *l, push_type v) {
    if (!available_metatable<T>(l)) {
      lua_pushlightuserdata(
          l, const_cast<typename traits::remove_const<T>::type *>(&v));
    } else {
      typedef typename ObjectPointerWrapperType<T>::type wrapper_type;
      void *storage = lua_newuserdata(l, sizeof(wrapper_type));
      new (storage) wrapper_type(&v);
      class_userdata::setmetatable<T>(l);
    }
    return 1;
  }
};

/// @ingroup lua_type_traits
/// @brief lua_type_traits for pointer type
template <typename PTR>
struct lua_type_traits<
    PTR, typename traits::enable_if<
             traits::is_pointer<
                 typename traits::remove_const_reference<PTR>::type>::value &&
             !traits::is_function<
                 typename traits::remove_pointer<PTR>::type>::value>::type> {
  typedef void Registerable;

  typedef PTR get_type;
  typedef optional<get_type> opt_type;
  typedef PTR push_type;
  typedef typename traits::remove_pointer<PTR>::type T;

  static bool strictCheckType(lua_State *l, int index) {
    return object_wrapper<T>(l, index, false) != 0;
  }
  static bool checkType(lua_State *l, int index) {
    int type = lua_type(l, index);
    if (type == LUA_TLIGHTUSERDATA || type == LUA_TNIL || type == LUA_TNONE) {
      return true;
    }
    return object_wrapper<T>(l, index) != 0;
  }
  static get_type get(lua_State *l, int index) {
    int type = lua_type(l, index);
    if (type == LUA_TUSERDATA || type == LUA_TLIGHTUSERDATA) {
      return get_pointer(l, index, types::typetag<T>());
    }

    if (type == LUA_TNIL || type == LUA_TNONE) {
      return 0;
    }
    throw LuaTypeMismatch();
    return 0;
  }
  static opt_type opt(lua_State *l, int index) KAGUYA_NOEXCEPT {
    int type = lua_type(l, index);
    if (type == LUA_TUSERDATA || type == LUA_TLIGHTUSERDATA) {
      return get_pointer(l, index, types::typetag<T>());
    }
    if (type == LUA_TNIL || type == LUA_TNONE) {
      return opt_type(0);
    }
    return opt_type();
  }
  static int push(lua_State *l, push_type v) {
    if (!v) {
      lua_pushnil(l);
    } else if (!available_metatable<T>(l)) {
      lua_pushlightuserdata(
          l, const_cast<typename traits::remove_const<T>::type *>(v));
    } else {
      typedef typename ObjectPointerWrapperType<T>::type wrapper_type;
      void *storage = lua_newuserdata(l, sizeof(wrapper_type));
      new (storage) wrapper_type(v);
      class_userdata::setmetatable<T>(l);
    }
    return 1;
  }
};

/// @ingroup lua_type_traits
/// @brief lua_type_traits for bool
template <> struct lua_type_traits<bool> {
  typedef bool get_type;
  typedef optional<get_type> opt_type;
  typedef bool push_type;

  static bool strictCheckType(lua_State *l, int index) {
    return lua_type(l, index) == LUA_TBOOLEAN;
  }
  static bool checkType(lua_State *l, int index) {
    KAGUYA_UNUSED(l);
    KAGUYA_UNUSED(index);
    return true;
  }
  static bool get(lua_State *l, int index) {
    return l && lua_toboolean(l, index) != 0;
  }
  static opt_type opt(lua_State *l, int index) KAGUYA_NOEXCEPT {
    if (l) {
      return opt_type(lua_toboolean(l, index) != 0);
    } else {
      return opt_type();
    }
  }
  static int push(lua_State *l, bool s) {
    lua_pushboolean(l, s);
    return 1;
  }
};

/// @ingroup lua_type_traits
/// @brief lua_type_traits for void
template <> struct lua_type_traits<void> {
  typedef void *get_type;
  typedef void *push_type;

  static bool strictCheckType(lua_State *, int) { return true; }
  static bool checkType(lua_State *, int) { return true; }
  static get_type get(lua_State *, int) { return 0; }
  static int push(lua_State *, push_type) { return 0; }
};

/// @ingroup lua_type_traits
/// @brief lua_type_traits for reference_wrapper
template <typename T> struct lua_type_traits<standard::reference_wrapper<T> > {
  typedef const standard::reference_wrapper<T> &push_type;

  static int push(lua_State *l, push_type v) {
    return util::push_args(l, &v.get());
  }
};

namespace detail {

template <typename T, typename Enable = void>
struct has_optional_get : traits::false_type {};
template <typename T>
struct has_optional_get<
    T, typename traits::enable_if<!traits::is_same<
           void, typename lua_type_traits<T>::opt_type>::value>::type>
    : traits::true_type {};

template <typename T>
typename traits::enable_if<has_optional_get<T>::value, optional<T> >::type
opt_helper(lua_State *state, int index) KAGUYA_NOEXCEPT {
  return lua_type_traits<T>::opt(state, index);
}
template <typename T>
typename traits::enable_if<!has_optional_get<T>::value, optional<T> >::type
opt_helper(lua_State *state, int index) {
  try {
    return lua_type_traits<T>::get(state, index);
  } catch (...) {
    return optional<T>();
  }
}
}

/// @ingroup lua_type_traits
/// @brief lua_type_traits for optional
template <typename T> struct lua_type_traits<optional<T> > {
  typedef const optional<T> &push_type;
  typedef optional<T> get_type;

  static bool strictCheckType(lua_State *l, int index) {
    return lua_type_traits<T>::strictCheckType(l, index);
  }
  static bool checkType(lua_State *l, int index) {
    KAGUYA_UNUSED(l);
    KAGUYA_UNUSED(index);
    return true;
  }
  static get_type get(lua_State *l, int index) KAGUYA_NOEXCEPT {
    return detail::opt_helper<T>(l, index);
  }

  static int push(lua_State *l, push_type v) KAGUYA_NOEXCEPT {
    if (v) {
      return util::push_args(l, v.value());
    } else {
      lua_pushnil(l);
    }
    return 1;
  }
};

/// @ingroup lua_type_traits
/// @brief lua_type_traits for shared_ptr
template <typename T> struct lua_type_traits<standard::shared_ptr<T> > {
  typedef const standard::shared_ptr<T> &push_type;
  typedef standard::shared_ptr<T> get_type;

  static bool strictCheckType(lua_State *l, int index) {
    ObjectSharedPointerWrapper *wrapper =
        dynamic_cast<ObjectSharedPointerWrapper *>(object_wrapper(l, index));
    if (!wrapper) {
      return false;
    }
    const std::type_info &type =
        metatableType<standard::shared_ptr<typename traits::decay<T>::type> >();
#if KAGUYA_NAME_BASED_TYPE_CHECK
    return strcmp(wrapper->shared_ptr_type().name(), type.name()) == 0;
#else
    return wrapper->shared_ptr_type() == type;
#endif
  }
  static bool checkType(lua_State *l, int index) {
    return get_shared_pointer(l, index, types::typetag<T>()) ||
           lua_isnil(l, index);
  }
  static get_type get(lua_State *l, int index) {
    if (lua_isnil(l, index)) {
      return get_type();
    }
    return get_shared_pointer(l, index, types::typetag<T>());
  }

  static int push(lua_State *l, push_type v) {
    if (v) {
      typedef ObjectSharedPointerWrapper wrapper_type;
      void *storage = lua_newuserdata(l, sizeof(wrapper_type));
      new (storage) wrapper_type(v);
      class_userdata::setmetatable<T>(l);
    } else {
      lua_pushnil(l);
    }
    return 1;
  }
};
#if KAGUYA_USE_CPP11
/// @ingroup lua_type_traits
/// @brief lua_type_traits for unique_ptr
template <typename T, typename Deleter>
struct lua_type_traits<std::unique_ptr<T, Deleter> > {
  typedef std::unique_ptr<T, Deleter> &&push_type;
  typedef std::unique_ptr<T, Deleter> &get_type;
  typedef std::unique_ptr<T, Deleter> type;

  static bool strictCheckType(lua_State *l, int index) {
    return object_wrapper<type>(l, index, false) != 0;
  }
  static bool checkType(lua_State *l, int index) {
    return object_wrapper<type>(l, index) != 0 || lua_isnil(l, index);
  }
  static get_type get(lua_State *l, int index) {
    type *pointer = get_pointer(l, index, types::typetag<type>());
    if (!pointer) {
      throw LuaTypeMismatch();
    }
    return *pointer;
  }

  static int push(lua_State *l, push_type v) {
    if (v) {
      typedef ObjectSmartPointerWrapper<type> wrapper_type;
      void *storage = lua_newuserdata(l, sizeof(wrapper_type));
      new (storage) wrapper_type(std::forward<push_type>(v));
      class_userdata::setmetatable<T>(l);
    } else {
      lua_pushnil(l);
    }
    return 1;
  }
};
/// @ingroup lua_type_traits
/// @brief lua_type_traits for nullptr
template <> struct lua_type_traits<std::nullptr_t> {
  typedef const std::nullptr_t &push_type;
  typedef std::nullptr_t get_type;
  typedef optional<get_type> opt_type;

  static bool checkType(lua_State *l, int index) {
    return lua_isnoneornil(l, index);
  }
  static bool strictCheckType(lua_State *l, int index) {
    return lua_isnil(l, index);
  }
  static opt_type opt(lua_State *l, int index) {
    if (!lua_isnoneornil(l, index)) {
      return opt_type();
    }
    return nullptr;
  }
  static get_type get(lua_State *l, int index) {
    if (!lua_isnoneornil(l, index)) {
      throw LuaTypeMismatch();
    }
    return nullptr;
  }

  static int push(lua_State *l, const std::nullptr_t &) {
    lua_pushnil(l);
    return 1;
  }
};
#endif

/// @ingroup lua_type_traits
/// @brief lua_type_traits for ObjectWrapperBase*
template <> struct lua_type_traits<ObjectWrapperBase *> {
  typedef ObjectWrapperBase *get_type;
  typedef ObjectWrapperBase *push_type;

  static bool strictCheckType(lua_State *l, int index) {
    return object_wrapper(l, index) != 0;
  }
  static bool checkType(lua_State *l, int index) {
    return object_wrapper(l, index) != 0;
  }
  static get_type get(lua_State *l, int index) {
    return object_wrapper(l, index);
  }
};

/// @ingroup lua_type_traits
/// @brief lua_type_traits for native type of luathread(lua_State*)
template <> struct lua_type_traits<lua_State *> {
  typedef lua_State *get_type;
  typedef lua_State *push_type;

  static bool strictCheckType(lua_State *l, int index) {
    return lua_isthread(l, index);
  }
  static bool checkType(lua_State *l, int index) {
    return lua_isthread(l, index);
  }
  static lua_State *get(lua_State *l, int index) {
    return lua_tothread(l, index);
  }
};

/// @ingroup lua_type_traits
/// @brief lua_type_traits for floating point number value
template <typename T>
struct lua_type_traits<
    T, typename traits::enable_if<traits::is_floating_point<T>::value>::type> {
  typedef typename traits::remove_const_reference<T>::type get_type;
  typedef optional<get_type> opt_type;
  typedef lua_Number push_type;

  static bool strictCheckType(lua_State *l, int index) {
    return lua_type(l, index) == LUA_TNUMBER;
  }
  static bool checkType(lua_State *l, int index) {
    return lua_isnumber(l, index) != 0;
  }
  static opt_type opt(lua_State *l, int index) KAGUYA_NOEXCEPT {
    int isnum = 0;
    get_type num = static_cast<T>(lua_tonumberx(l, index, &isnum));
    if (!isnum) {
      return opt_type();
    }
    return num;
  }
  static get_type get(lua_State *l, int index) {
    int isnum = 0;
    get_type num = static_cast<T>(lua_tonumberx(l, index, &isnum));
    if (!isnum) {
      throw LuaTypeMismatch();
    }
    return num;
  }
  static int push(lua_State *l, lua_Number s) {
    lua_pushnumber(l, s);
    return 1;
  }
};

/// @ingroup lua_type_traits
/// @brief lua_type_traits for integral number value
template <typename T>
struct lua_type_traits<
    T, typename traits::enable_if<traits::is_integral<T>::value>::type> {
  typedef typename traits::remove_const_reference<T>::type get_type;
  typedef optional<get_type> opt_type;
#if LUA_VERSION_NUM >= 503
  typedef lua_Integer push_type;

  static bool strictCheckType(lua_State *l, int index) {
    return lua_isinteger(l, index) != 0;
  }
  static bool checkType(lua_State *l, int index) {
    return lua_isnumber(l, index) != 0;
  }
  static opt_type opt(lua_State *l, int index) KAGUYA_NOEXCEPT {
    int isnum = 0;
    get_type num = static_cast<T>(lua_tointegerx(l, index, &isnum));
    if (!isnum) {
      return opt_type();
    }
    return num;
  }
  static get_type get(lua_State *l, int index) {
    int isnum = 0;
    get_type num = static_cast<T>(lua_tointegerx(l, index, &isnum));
    if (!isnum) {
      throw LuaTypeMismatch();
    }
    return num;
  }
  static int push(lua_State *l, lua_Integer s) {
    lua_pushinteger(l, s);
    return 1;
  }
#else
  typedef typename lua_type_traits<lua_Number>::push_type push_type;

  static bool strictCheckType(lua_State *l, int index) {
    return lua_type_traits<lua_Number>::strictCheckType(l, index);
  }
  static bool checkType(lua_State *l, int index) {
    return lua_type_traits<lua_Number>::checkType(l, index);
  }
  static get_type get(lua_State *l, int index) {
    return static_cast<get_type>(lua_type_traits<lua_Number>::get(l, index));
  }
  static opt_type opt(lua_State *l, int index) KAGUYA_NOEXCEPT {
    lua_type_traits<lua_Number>::opt_type v =
        lua_type_traits<lua_Number>::opt(l, index);
    if (!v) {
      return opt_type();
    }
    return static_cast<get_type>(*v);
  }
  static int push(lua_State *l, push_type s) { return util::push_args(l, s); }
#endif
};

/// @ingroup lua_type_traits
/// @brief lua_type_traits for enum
template <typename T>
struct lua_type_traits<
    T, typename traits::enable_if<traits::is_enum<T>::value>::type> {
  typedef typename traits::remove_const_reference<T>::type get_type;
  typedef optional<get_type> opt_type;
  typedef typename traits::remove_const_reference<T>::type push_type;

  static bool strictCheckType(lua_State *l, int index) {
    return lua_type_traits<luaInt>::strictCheckType(l, index);
  }
  static bool checkType(lua_State *l, int index) {
    return lua_type_traits<luaInt>::checkType(l, index);
  }
  static opt_type opt(lua_State *l, int index) KAGUYA_NOEXCEPT {
    if (lua_type_traits<luaInt>::opt_type t =
            lua_type_traits<luaInt>::opt(l, index)) {
      return opt_type(static_cast<get_type>(*t));
    }
    return opt_type();
  }
  static get_type get(lua_State *l, int index) {
    return static_cast<get_type>(lua_type_traits<luaInt>::get(l, index));
  }
  static int push(lua_State *l, push_type s) {
    return util::push_args(
        l, static_cast<typename lua_type_traits<int64_t>::push_type>(s));
  }
};

/// @ingroup lua_type_traits
/// @brief lua_type_traits for cstring
template <> struct lua_type_traits<const char *> {
  typedef const char *get_type;
  typedef optional<get_type> opt_type;
  typedef const char *push_type;

  static bool strictCheckType(lua_State *l, int index) {
    return lua_type(l, index) == LUA_TSTRING;
  }
  static bool checkType(lua_State *l, int index) {
    return lua_isstring(l, index) != 0;
  }
  static get_type get(lua_State *l, int index) {
    const char *buffer = lua_tostring(l, index);
    if (!buffer) {
      throw LuaTypeMismatch();
    }
    return buffer;
  }
  static opt_type opt(lua_State *l, int index) {
    const char *buffer = lua_tostring(l, index);
    if (!buffer) {
      return opt_type();
    }
    return buffer;
  }
  static int push(lua_State *l, const char *s) {
    lua_pushstring(l, s);
    return 1;
  }
};

/// @ingroup lua_type_traits
/// @brief lua_type_traits for cstring
template <int N> struct lua_type_traits<char[N]> {
  typedef std::string get_type;
  typedef const char *push_type;

  static bool strictCheckType(lua_State *l, int index) {
    return lua_type(l, index) == LUA_TSTRING;
  }
  static bool checkType(lua_State *l, int index) {
    return lua_isstring(l, index) != 0;
  }
  static const char *get(lua_State *l, int index) {
    const char *buffer = lua_tostring(l, index);
    if (!buffer) {
      throw LuaTypeMismatch();
    }
    return buffer;
  }
  static int push(lua_State *l, const char s[N]) {
    lua_pushlstring(l, s, s[N - 1] != '\0' ? N : N - 1);
    return 1;
  }
};
/// @ingroup lua_type_traits
/// @brief lua_type_traits for cstring
template <int N>
struct lua_type_traits<const char[N]> : lua_type_traits<char[N]> {};

/// @ingroup lua_type_traits
/// @brief lua_type_traits for std::string
template <> struct lua_type_traits<std::string> {
  typedef std::string get_type;
  typedef optional<get_type> opt_type;
  typedef const std::string &push_type;

  static bool strictCheckType(lua_State *l, int index) {
    return lua_type(l, index) == LUA_TSTRING;
  }
  static bool checkType(lua_State *l, int index) {
    return lua_isstring(l, index) != 0;
  }
  static opt_type opt(lua_State *l, int index) KAGUYA_NOEXCEPT {
    size_t size = 0;
    const char *buffer = lua_tolstring(l, index, &size);
    if (!buffer) {
      return opt_type();
    }
    return std::string(buffer, size);
  }
  static get_type get(lua_State *l, int index) {
    if (opt_type o = opt(l, index)) {
      return *o;
    }
    throw LuaTypeMismatch();
  }
  static int push(lua_State *l, const std::string &s) {
    lua_pushlstring(l, s.c_str(), s.size());
    return 1;
  }
};

struct NewTable {
  NewTable() : reserve_array_(0), reserve_record_(0) {}
  NewTable(int reserve_array, int reserve_record_)
      : reserve_array_(reserve_array), reserve_record_(reserve_record_) {}
  int reserve_array_;
  int reserve_record_;
};
struct NewThread {};
struct GlobalTable {};
struct NilValue {};

struct NoTypeCheck {};

/// @ingroup lua_type_traits
/// @brief lua_type_traits for NewTable, push only
template <> struct lua_type_traits<NewTable> {
  static int push(lua_State *l, const NewTable &table) {
    lua_createtable(l, table.reserve_array_, table.reserve_record_);
    return 1;
  }
};

/// @ingroup lua_type_traits
/// @brief lua_type_traits for NewThread, push only
template <> struct lua_type_traits<NewThread> {
  static int push(lua_State *l, const NewThread &) {
    lua_newthread(l);
    return 1;
  }
};
/// @ingroup lua_type_traits
/// @brief lua_type_traits for NilValue, similar to nullptr_t
/// If you using C++11, recommend use nullptr instead.
template <> struct lua_type_traits<NilValue> {
  typedef NilValue get_type;
  typedef optional<get_type> opt_type;
  typedef NilValue push_type;

  static bool checkType(lua_State *l, int index) {
    return lua_isnoneornil(l, index);
  }
  static bool strictCheckType(lua_State *l, int index) {
    return lua_isnil(l, index);
  }

  static opt_type opt(lua_State *l, int index) {
    if (!checkType(l, index)) {
      return opt_type();
    }
    return NilValue();
  }
  static get_type get(lua_State *l, int index) {
    if (!checkType(l, index)) {
      throw LuaTypeMismatch();
    }
    return NilValue();
  }
  static int push(lua_State *l, const NilValue &) {
    lua_pushnil(l);
    return 1;
  }
};
inline std::ostream &operator<<(std::ostream &os, const NilValue &) {
  return os << "nil";
}
inline bool operator==(const NilValue &, const NilValue &) { return true; }
inline bool operator!=(const NilValue &, const NilValue &) { return false; }

/// @ingroup lua_type_traits
/// @brief lua_type_traits for GlobalTable, push only
template <> struct lua_type_traits<GlobalTable> {
  static int push(lua_State *l, const GlobalTable &) {
    lua_pushglobaltable(l);
    return 1;
  }
};

namespace detail {
template <typename Derived> class LuaBasicTypeFunctions {
  template <class Other> friend class LuaBasicTypeFunctions;
  typedef void (LuaBasicTypeFunctions::*bool_type)() const;
  void this_type_does_not_support_comparisons() const {}

public:
  enum value_type {
    TYPE_NONE = LUA_TNONE,                   //!< none type
    TYPE_NIL = LUA_TNIL,                     //!< nil type
    TYPE_BOOLEAN = LUA_TBOOLEAN,             //!< boolean type
    TYPE_LIGHTUSERDATA = LUA_TLIGHTUSERDATA, //!< light userdata type
    TYPE_NUMBER = LUA_TNUMBER,               //!< number type
    TYPE_STRING = LUA_TSTRING,               //!< string type
    TYPE_TABLE = LUA_TTABLE,                 //!< table type
    TYPE_FUNCTION = LUA_TFUNCTION,           //!< function type
    TYPE_USERDATA = LUA_TUSERDATA,           //!< userdata type
    TYPE_THREAD = LUA_TTHREAD                //!< thread(coroutine) type
  };

  /// @brief If reference value is none or nil return true. Otherwise false.
  bool isNilref_() const {
    int t = type();
    return t == LUA_TNIL || t == LUA_TNONE;
  }

  /// @brief Equivalent to `#` operator for strings and tables with no
  /// metamethods.
  /// Follows Lua's reference manual documentation of `lua_rawlen`, ie. types
  /// other
  /// than tables, strings or userdatas return 0.
  /// @return Size of table, string length or userdata memory block size.
  size_t size() const {
    lua_State *state = state_();
    if (!state) {
      return 0;
    }
    util::ScopedSavedStack save(state);
    int index = pushStackIndex_(state);

    return lua_rawlen(state, index);
  }

  // return type
  int type() const {
    lua_State *state = state_();
    if (!state) {
      return LUA_TNONE;
    }
    util::ScopedSavedStack save(state);
    return lua_type(state, pushStackIndex_(state));
  }

  // return type name
  const char *typeName() const { return lua_typename(state_(), type()); }

  operator bool_type() const {
    lua_State *state = state_();
    if (!state) {
      return 0; // hasn't lua_State
    }
    util::ScopedSavedStack save(state);
    int stackindex = pushStackIndex_(state);
    int t = lua_type(state, stackindex);
    if (t == LUA_TNONE) {
      return 0; // none
    }
    return lua_toboolean(state, stackindex)
               ? &LuaBasicTypeFunctions::this_type_does_not_support_comparisons
               : 0;
  }

  /**
  * @name relational operators
  * @brief
  */
  //@{
  template <typename OtherDrived>
  inline bool operator==(const LuaBasicTypeFunctions<OtherDrived> &rhs) const {
    if (isNilref_() || rhs.isNilref_()) {
      return !isNilref_() == !rhs.isNilref_();
    }
    lua_State *state = state_();
    util::ScopedSavedStack save(state);
    int index = pushStackIndex_(state);
    int rhsindex = rhs.pushStackIndex_(state);
    return lua_compare(state, index, rhsindex, LUA_OPEQ) != 0;
  }
  template <typename OtherDrived>
  inline bool operator<(const LuaBasicTypeFunctions<OtherDrived> &rhs) const {
    if (isNilref_() || rhs.isNilref_()) {
      return !isNilref_() != !rhs.isNilref_();
    }
    lua_State *state = state_();
    util::ScopedSavedStack save(state);
    int index = pushStackIndex_(state);
    int rhsindex = rhs.pushStackIndex_(state);
    return lua_compare(state, index, rhsindex, LUA_OPLT) != 0;
  }
  template <typename OtherDrived>
  inline bool operator<=(const LuaBasicTypeFunctions<OtherDrived> &rhs) const {
    if (isNilref_() || rhs.isNilref_()) {
      return !isNilref_() == !rhs.isNilref_();
    }
    lua_State *state = state_();
    util::ScopedSavedStack save(state);
    int index = pushStackIndex_(state);
    int rhsindex = rhs.pushStackIndex_(state);
    return lua_compare(state, index, rhsindex, LUA_OPLE) != 0;
  }
  template <typename OtherDrived>
  inline bool operator>=(const LuaBasicTypeFunctions<OtherDrived> &rhs) const {
    return rhs <= (*this);
  }
  template <typename OtherDrived>
  inline bool operator>(const LuaBasicTypeFunctions<OtherDrived> &rhs) const {
    return rhs < (*this);
  }
  template <typename OtherDrived>
  inline bool operator!=(const LuaBasicTypeFunctions<OtherDrived> &rhs) const {
    return !this->operator==(rhs);
  }

  template <typename T>
  inline typename traits::enable_if<
      !traits::is_convertible<T *, LuaBasicTypeFunctions<T> *>::value,
      bool>::type
  operator==(const T &rhs) const {
    if (optional<typename lua_type_traits<T>::get_type> d = checkGet_<T>()) {
      return *d == rhs;
    }
    return false;
  }
  template <typename T>
  inline typename traits::enable_if<
      !traits::is_convertible<T *, LuaBasicTypeFunctions<T> *>::value,
      bool>::type
  operator!=(const T &rhs) const {
    return !((*this) == rhs);
  }
  //@}

  void dump(std::ostream &os) const {
    lua_State *state = state_();
    util::ScopedSavedStack save(state);
    int stackIndex = pushStackIndex_(state);
    util::stackValueDump(os, state, stackIndex);
  }

private:
  lua_State *state_() const {
    return static_cast<const Derived *>(this)->state();
  }
  int pushStackIndex_(lua_State *state) const {
    return static_cast<const Derived *>(this)->pushStackIndex(state);
  }
  template <typename T>
  optional<typename lua_type_traits<T>::get_type> checkGet_() const {
    lua_State *state = state_();
    util::ScopedSavedStack save(state);
    int stackindex = pushStackIndex_(state);
    return lua_type_traits<
        optional<typename lua_type_traits<T>::get_type> >::get(state,
                                                               stackindex);
  }
};
template <typename D>
inline std::ostream &operator<<(std::ostream &os,
                                const LuaBasicTypeFunctions<D> &ref) {
  ref.dump(os);
  return os;
}
/**
* @name relational operators
* @brief
*/
//@{

#define KAGUYA_ENABLE_IF_NOT_LUAREF(RETTYPE)                                   \
  typename traits::enable_if<                                                  \
      !traits::is_convertible<T *, LuaBasicTypeFunctions<T> *>::value,         \
      RETTYPE>::type
template <typename D, typename T>
inline KAGUYA_ENABLE_IF_NOT_LUAREF(bool)
operator==(const T &lhs, const LuaBasicTypeFunctions<D> &rhs) {
  return rhs == lhs;
}
template <typename D, typename T>
inline KAGUYA_ENABLE_IF_NOT_LUAREF(bool)
operator!=(const T &lhs, const LuaBasicTypeFunctions<D> &rhs) {
  return !(rhs == lhs);
}
#undef KAGUYA_ENABLE_IF_NOT_LUAREF
//@}
}
}
