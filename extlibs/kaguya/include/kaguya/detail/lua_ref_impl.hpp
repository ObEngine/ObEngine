// Copyright satoren
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#pragma once

#include <vector>
#include <map>
#include <cassert>
#include <algorithm>
#include <ostream>
#include "kaguya/config.hpp"
#include "kaguya/error_handler.hpp"
#include "kaguya/type.hpp"
#include "kaguya/utility.hpp"

namespace kaguya {
/// @brief StackTop tag type
struct StackTop {};

namespace Ref {
/// @brief NoMainCheck tag type
struct NoMainCheck {};

/// @brief reference to Lua stack value
class StackRef {
protected:
  lua_State *state_;
  int stack_index_;
  mutable bool pop_;
#if KAGUYA_USE_CPP11
  StackRef(StackRef &&src)
      : state_(src.state_), stack_index_(src.stack_index_), pop_(src.pop_) {
    src.pop_ = false;
  }
  StackRef &operator=(StackRef &&src) {
    state_ = src.state_;
    stack_index_ = src.stack_index_;
    pop_ = src.pop_;

    src.pop_ = false;
    return *this;
  }

  StackRef(const StackRef &src) = delete;
  StackRef &operator=(const StackRef &src) = delete;
#else
  StackRef(const StackRef &src)
      : state_(src.state_), stack_index_(src.stack_index_), pop_(src.pop_) {
    src.pop_ = false;
  }
  StackRef &operator=(const StackRef &src) {
    if (this != &src) {
      state_ = src.state_;
      stack_index_ = src.stack_index_;
      pop_ = src.pop_;

      src.pop_ = false;
    }
    return *this;
  }
#endif
  StackRef(lua_State *s, int index)
      : state_(s), stack_index_(lua_absindex(s, index)), pop_(true) {}
  StackRef(lua_State *s, int index, bool pop)
      : state_(s), stack_index_(lua_absindex(s, index)), pop_(pop) {}
  StackRef() : state_(0), stack_index_(0), pop_(false) {}
  ~StackRef() {
    if (state_ && pop_) {
      if (lua_gettop(state_) >= stack_index_) {
        lua_settop(state_, stack_index_ - 1);
      }
    }
  }

public:
  bool isNilref() const {
    return state_ == 0 || lua_type(state_, stack_index_) == LUA_TNIL;
  }

  int push() const {
    lua_pushvalue(state_, stack_index_);
    return 1;
  }
  int push(lua_State *state) const {
    lua_pushvalue(state_, stack_index_);
    if (state_ != state) {
      lua_pushvalue(state_, stack_index_);
      lua_xmove(state_, state, 1);
    }
    return 1;
  }

  int pushStackIndex(lua_State *state) const {
    if (state_ != state) {
      lua_pushvalue(state_, stack_index_);
      lua_xmove(state_, state, 1);
      return lua_gettop(state);
    } else {
      return stack_index_;
    }
  }
  lua_State *state() const { return state_; }
};

/// @brief Reference to Lua value. Retain reference by LUA_REGISTRYINDEX
class RegistoryRef {
public:
#if KAGUYA_USE_SHARED_LUAREF
  struct RefHolder {
    struct RefDeleter {
      RefDeleter(lua_State *L) : state_(L) {}
      void operator()(int *ref) {
        luaL_unref(state_, LUA_REGISTRYINDEX, *ref);
        delete ref;
      }
      lua_State *state_;
    };
    RefHolder(lua_State *L, int ref)
        : state_(L), ref_(new int(ref), RefDeleter(L)) {}

    RefHolder(const RefHolder &src) : state_(src.state_), ref_(src.ref_) {}
    RefHolder &operator=(const RefHolder &src) {
      state_ = src.state_;
      ref_ = src.ref_;
      return *this;
    }
#if KAGUYA_USE_RVALUE_REFERENCE
    RefHolder(RefHolder &&src) : state_(0), ref_() { swap(src); }
    RefHolder &operator=(RefHolder &&src) throw() {
      swap(src);
      return *this;
    }
#endif
    void swap(RefHolder &other) throw() {
      std::swap(state_, other.state_);
      std::swap(ref_, other.ref_);
    }
    int ref() const {
      if (state_ && ref_) {
        return *ref_;
      }
      return LUA_REFNIL;
    }
    void reset() { ref_.reset(); }
    lua_State *state() const { return state_; }

  private:
    lua_State *state_;
    standard::shared_ptr<int> ref_;
  };
#else
  struct RefHolder {
    RefHolder(lua_State *L, int ref) : state_(L), ref_(ref) {}
    RefHolder(const RefHolder &src) : state_(src.state_), ref_(LUA_REFNIL) {
      if (state_) {
        lua_rawgeti(state_, LUA_REGISTRYINDEX, src.ref_);
        ref_ = luaL_ref(state_, LUA_REGISTRYINDEX);
      }
    }
    RefHolder &operator=(const RefHolder &src) {
      reset();
      state_ = src.state_;
      if (state_) {
        lua_rawgeti(state_, LUA_REGISTRYINDEX, src.ref_);
        ref_ = luaL_ref(state_, LUA_REGISTRYINDEX);
      } else {
        ref_ = LUA_REFNIL;
      }
      return *this;
    }
#if KAGUYA_USE_RVALUE_REFERENCE
    RefHolder(RefHolder &&src) throw() : state_(src.state_), ref_(src.ref_) {
      src.ref_ = LUA_REFNIL;
    }
    RefHolder &operator=(RefHolder &&src) throw() {
      swap(src);
      return *this;
    }
#endif
    void swap(RefHolder &other) throw() {
      std::swap(state_, other.state_);
      std::swap(ref_, other.ref_);
    }
    int ref() const {
      if (state_) {
        return ref_;
      }
      return LUA_REFNIL;
    }
    void reset() {
      if (ref_ != LUA_REFNIL && state_) {
        luaL_unref(state_, LUA_REGISTRYINDEX, ref_);
        ref_ = LUA_REFNIL;
      }
    }
    ~RefHolder() { reset(); }

    lua_State *state() const { return state_; }

  private:
    lua_State *state_;
    int ref_;
  };
#endif
  RegistoryRef(const RegistoryRef &src) : ref_(src.ref_) {}
  RegistoryRef &operator=(const RegistoryRef &src) {
    if (this != &src) {
      ref_ = src.ref_;
    }
    return *this;
  }

  static int ref_from_stacktop(lua_State *state) {
    if (state) {
      return luaL_ref(state, LUA_REGISTRYINDEX);
    } else {
      return LUA_REFNIL;
    }
  }
#if KAGUYA_USE_RVALUE_REFERENCE
  RegistoryRef(RegistoryRef &&src) throw() : ref_(0, LUA_REFNIL) { swap(src); }
  RegistoryRef &operator=(RegistoryRef &&src) throw() {
    swap(src);
    return *this;
  }
#endif

  RegistoryRef() : ref_(0, LUA_REFNIL) {}
  RegistoryRef(lua_State *state) : ref_(state, LUA_REFNIL) {}

  RegistoryRef(lua_State *state, StackTop, NoMainCheck)
      : ref_(state, ref_from_stacktop(state)) {}

  RegistoryRef(lua_State *state, StackTop)
      : ref_(util::toMainThread(state), ref_from_stacktop(state)) {}

  void swap(RegistoryRef &other) throw() { ref_.swap(other.ref_); }

  template <typename T>
  RegistoryRef(lua_State *state, const T &v, NoMainCheck)
      : ref_(0, LUA_REFNIL) {
    if (!state) {
      return;
    }
    util::ScopedSavedStack save(state);
    util::one_push(state, v);
    ref_ = RefHolder(state, ref_from_stacktop(state));
  }
  template <typename T>
  RegistoryRef(lua_State *state, const T &v) : ref_(0, LUA_REFNIL) {
    if (!state) {
      return;
    }
    util::ScopedSavedStack save(state);
    util::one_push(state, v);
    ref_ = RefHolder(util::toMainThread(state), ref_from_stacktop(state));
  }
#if KAGUYA_USE_CPP11
  template <typename T>
  RegistoryRef(lua_State *state, T &&v, NoMainCheck) : ref_(0, LUA_REFNIL) {
    if (!state) {
      return;
    }
    util::ScopedSavedStack save(state);
    util::one_push(state, standard::forward<T>(v));
    ref_ = RefHolder(state, ref_from_stacktop(state));
  }
  template <typename T>
  RegistoryRef(lua_State *state, T &&v) : ref_(0, LUA_REFNIL) {
    if (!state) {
      return;
    }
    util::ScopedSavedStack save(state);
    util::one_push(state, standard::forward<T>(v));
    ref_ = RefHolder(util::toMainThread(state), ref_from_stacktop(state));
  }
#endif
  ~RegistoryRef() {
    try {
      unref();
    } catch (...) {
    } // can't throw at Destructor
  }

  /// @brief push to Lua stack
  int push() const { return push(ref_.state()); }
  /// @brief push to Lua stack
  int push(lua_State *state) const {
    if (isNilref()) {
      lua_pushnil(state);
      return 1;
    }
#if LUA_VERSION_NUM >= 502
    if (state != ref_.state()) { // state check
      assert(util::toMainThread(state) == util::toMainThread(ref_.state()));
    }
#endif
    lua_rawgeti(state, LUA_REGISTRYINDEX, ref_.ref());
    return 1;
  }

  int pushStackIndex(lua_State *state) const {
    push(state);
    return lua_gettop(state);
  }
  lua_State *state() const { return ref_.state(); }

  bool isNilref() const { return ref_.ref() == LUA_REFNIL; }

  void unref() { ref_.reset(); }

private:
  RefHolder ref_;
};
}
}
