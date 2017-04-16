// Copyright satoren
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#pragma once

#include "kaguya/detail/lua_function_def.hpp"
#include "kaguya/detail/lua_table_def.hpp"

namespace kaguya {
class LuaRef;
class LuaTable;
template <typename KEY> class TableKeyReferenceProxy;
class MemberFunctionBinder;

namespace detail {

template <typename Derived>
class LuaVariantImpl : public LuaTableImpl<Derived>,
                       public LuaTableOrUserDataImpl<Derived>,
                       public detail::LuaFunctionImpl<Derived>,
                       public detail::LuaThreadImpl<Derived>,
                       public LuaBasicTypeFunctions<Derived> {
private:
  lua_State *state_() const {
    return static_cast<const Derived *>(this)->state();
  }
  int pushStackIndex_(lua_State *state) const {
    return static_cast<const Derived *>(this)->pushStackIndex(state);
  }

public:
  using LuaBasicTypeFunctions<Derived>::type;
  using LuaBasicTypeFunctions<Derived>::typeName;

  /// @brief deprecated, use isType instead.
  template <typename T> bool typeTest() const { return isType<T>(); }

  /// @brief deprecated, use isConvertible instead.
  template <typename T> bool weakTypeTest() const { return isConvertible<T>(); }

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

  template <typename T> typename lua_type_traits<T>::get_type get() const {
    lua_State *state = state_();
    util::ScopedSavedStack save(state);
    return lua_type_traits<T>::get(state, state ? pushStackIndex_(state) : 0);
  }
  template <typename T, typename U>
  typename lua_type_traits<T>::get_type value_or(U v) const {
    lua_State *state = state_();
    util::ScopedSavedStack save(state);
    return lua_type_traits<optional<T> >::get(
               state, state ? pushStackIndex_(state) : 0)
        .value_or(v);
  }

  // deprecated. use get<kaguya::optional<T> >() instead;
  template <typename T>
  typename lua_type_traits<T>::get_type
  get(bool &was_valid, bool allow_convertible = true) const {
    lua_State *state = state_();
    util::ScopedSavedStack save(state);
    int stackindex = pushStackIndex_(state);
    if (allow_convertible) {
      was_valid = lua_type_traits<T>::checkType(state, stackindex);
    } else {
      was_valid = lua_type_traits<T>::strictCheckType(state, stackindex);
    }
    if (was_valid) {
      return lua_type_traits<T>::get(state, stackindex);
    } else {
      return T();
    }
  }
  template <typename T> operator T() const { return get<T>(); }

#if KAGUYA_USE_CPP11
  template <class... Args> FunctionResults operator()(Args &&... args);
#else
  inline FunctionResults operator()();

#define KAGUYA_OP_FN_DEF(N)                                                    \
  template <KAGUYA_PP_TEMPLATE_DEF_REPEAT(N)>                                  \
  inline FunctionResults operator()(KAGUYA_PP_ARG_CR_DEF_REPEAT(N));

  KAGUYA_PP_REPEAT_DEF(KAGUYA_FUNCTION_MAX_ARGS, KAGUYA_OP_FN_DEF)
#undef KAGUYA_OP_FN_DEF
#endif
};
}
}
