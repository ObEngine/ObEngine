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
class LuaTable;
class LuaFunction;

class FunctionResults;

/**
* status of coroutine
*/
enum coroutine_status {
  COSTAT_RUNNING,   //!< coroutine is running
  COSTAT_SUSPENDED, //!< coroutine is suspended
  COSTAT_NORMAL,    //!<
  COSTAT_DEAD       //!< coroutine is dead
};

namespace detail {
class FunctionResultProxy {
public:
  template <typename RetType>
  static RetType ReturnValue(lua_State *state, int restatus, int retindex,
                             types::typetag<RetType> tag);
  static FunctionResults ReturnValue(lua_State *state, int restatus,
                                     int retindex,
                                     types::typetag<FunctionResults> tag);
  static void ReturnValue(lua_State *state, int restatus, int retindex,
                          types::typetag<void> tag);
};

template <typename Derived> class LuaFunctionImpl {
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
  /**
  * set function environment table
  */
  bool setFunctionEnv(const LuaTable &env);
  /**
  * set function environment to new table
  */
  bool setFunctionEnv(NewTable env);
  /**
  * get function environment table
  */
  LuaTable getFunctionEnv() const;

#if KAGUYA_USE_CPP11
  template <class Result, class... Args> Result call(Args &&... args) {
    lua_State *state = state_();
    if (!state) {
      except::typeMismatchError(state, "nil");
      return Result();
    }
    int argstart = lua_gettop(state) + 1;
    push_(state);
    int argnum = util::push_args(state, std::forward<Args>(args)...);
    int result = lua_pcall_wrap(state, argnum, LUA_MULTRET);
    except::checkErrorAndThrow(result, state);
    return detail::FunctionResultProxy::ReturnValue(state, result, argstart,
                                                    types::typetag<Result>());
  }

  template <class... Args> FunctionResults operator()(Args &&... args);
#else

#define KAGUYA_CALL_DEF(N)                                                     \
  template <class Result KAGUYA_PP_TEMPLATE_DEF_REPEAT_CONCAT(N)>              \
  Result call(KAGUYA_PP_ARG_CR_DEF_REPEAT(N)) {                                \
    lua_State *state = state_();                                               \
    if (!state) {                                                              \
      except::typeMismatchError(state, "attempt to call nil value");           \
      return Result();                                                         \
    }                                                                          \
    int argstart = lua_gettop(state) + 1;                                      \
    push_(state);                                                              \
    int argnum = util::push_args(state KAGUYA_PP_ARG_REPEAT_CONCAT(N));        \
    int result = lua_pcall_wrap(state, argnum, LUA_MULTRET);                   \
    except::checkErrorAndThrow(result, state);                                 \
    return detail::FunctionResultProxy::ReturnValue(state, result, argstart,   \
                                                    types::typetag<Result>()); \
  }

  KAGUYA_CALL_DEF(0)
  KAGUYA_PP_REPEAT_DEF(KAGUYA_FUNCTION_MAX_ARGS, KAGUYA_CALL_DEF)

#undef KAGUYA_RESUME_DEF

  inline FunctionResults operator()();

#define KAGUYA_OP_FN_DEF(N)                                                    \
  template <KAGUYA_PP_TEMPLATE_DEF_REPEAT(N)>                                  \
  inline FunctionResults operator()(KAGUYA_PP_ARG_CR_DEF_REPEAT(N));

#define KAGUYA_FUNCTION_ARGS_DEF(N)
#define KAGUYA_CALL_ARGS(N) KAGUYA_PP_ARG_REPEAT(N)

  KAGUYA_PP_REPEAT_DEF(KAGUYA_FUNCTION_MAX_ARGS, KAGUYA_OP_FN_DEF)
#undef KAGUYA_OP_FN_DEF

#undef KAGUYA_CALL_ARGS
#undef KAGUYA_FUNCTION_ARGS_DEF
#undef KAGUYA_CALL_DEF
#endif
};

template <typename Derived> class LuaThreadImpl {
private:
  lua_State *state_() const {
    return static_cast<const Derived *>(this)->state();
  }
  int pushStackIndex_(lua_State *state) const {
    return static_cast<const Derived *>(this)->pushStackIndex(state);
  }

public:
#if KAGUYA_USE_CPP11
  template <class Result, class... Args> Result resume(Args &&... args) {
    lua_State *state = state_();
    if (!state) {
      except::typeMismatchError(state, "attempt to call nil value");
      return Result();
    }
    util::ScopedSavedStack save(state);
    int corStackIndex = pushStackIndex_(state);
    lua_State *thread = lua_tothread(state, corStackIndex);
    if (!thread) {
      except::typeMismatchError(state, "not thread");
      return Result();
    }
    int argstart = 1; // exist function in stack at first resume.
    if (lua_status(thread) == LUA_YIELD) {
      argstart = 0;
    }
    util::push_args(thread, std::forward<Args>(args)...);
    int argnum = lua_gettop(thread) - argstart;
    if (argnum < 0) {
      argnum = 0;
    }
    int result = lua_resume(thread, state, argnum);
    except::checkErrorAndThrow(result, thread);
    return detail::FunctionResultProxy::ReturnValue(thread, result, 1,
                                                    types::typetag<Result>());
  }
  template <class... Args> FunctionResults operator()(Args &&... args);
#else

#define KAGUYA_RESUME_DEF(N)                                                   \
  template <class Result KAGUYA_PP_TEMPLATE_DEF_REPEAT_CONCAT(N)>              \
  Result resume(KAGUYA_PP_ARG_CR_DEF_REPEAT(N)) {                              \
    lua_State *state = state_();                                               \
    if (!state) {                                                              \
      except::typeMismatchError(state, "attempt to call nil value");           \
      return Result();                                                         \
    }                                                                          \
    util::ScopedSavedStack save(state);                                        \
    int corStackIndex = pushStackIndex_(state);                                \
    lua_State *thread = lua_tothread(state, corStackIndex);                    \
    if (!thread) {                                                             \
      except::typeMismatchError(state, "not thread");                          \
      return Result();                                                         \
    }                                                                          \
    int argstart = 1;                                                          \
    if (lua_status(thread) == LUA_YIELD) {                                     \
      argstart = 0;                                                            \
    }                                                                          \
    util::push_args(thread KAGUYA_PP_ARG_REPEAT_CONCAT(N));                    \
    int argnum = lua_gettop(thread) - argstart;                                \
    if (argnum < 0) {                                                          \
      argnum = 0;                                                              \
    }                                                                          \
    int result = lua_resume(thread, state, argnum);                            \
    except::checkErrorAndThrow(result, thread);                                \
    return detail::FunctionResultProxy::ReturnValue(thread, result, 1,         \
                                                    types::typetag<Result>()); \
  }

  KAGUYA_RESUME_DEF(0)
  KAGUYA_PP_REPEAT_DEF(KAGUYA_FUNCTION_MAX_ARGS, KAGUYA_RESUME_DEF)

#undef KAGUYA_RESUME_DEF

  inline FunctionResults operator()();

#define KAGUYA_OP_FN_DEF(N)                                                    \
  template <KAGUYA_PP_TEMPLATE_DEF_REPEAT(N)>                                  \
  inline FunctionResults operator()(KAGUYA_PP_ARG_CR_DEF_REPEAT(N));

  KAGUYA_PP_REPEAT_DEF(KAGUYA_FUNCTION_MAX_ARGS, KAGUYA_OP_FN_DEF)

#undef KAGUYA_OP_FN_DEF
#endif

  //!
  //! @return state status
  //!
  int threadStatus() const {
    lua_State *state = state_();
    if (!state) {
      except::typeMismatchError(state, "attempt to call nil value");
      return LUA_ERRRUN;
    }
    util::ScopedSavedStack save(state);
    int corStackIndex = pushStackIndex_(state);
    lua_State *thread = lua_tothread(state, corStackIndex);

    if (!thread) {
      except::typeMismatchError(state, "not thread");
      return LUA_ERRRUN;
    }
    return lua_status(thread);
  }

  //! deprecate
  int thread_status() const { return threadStatus(); }

  //!
  //! @return coroutine status
  //!
  coroutine_status costatus(lua_State *l = 0) const {
    lua_State *state = state_();
    if (!state) {
      return COSTAT_DEAD;
    }
    util::ScopedSavedStack save(state);
    int corStackIndex = pushStackIndex_(state);
    lua_State *thread = lua_tothread(state, corStackIndex);

    if (!thread) {
      except::typeMismatchError(state, "not thread");
      return COSTAT_DEAD;
    } else if (thread == l) {
      return COSTAT_RUNNING;
    } else {
      switch (lua_status(thread)) {
      case LUA_YIELD:
        return COSTAT_SUSPENDED;
      case 0: // LUA_OK
      {
        if (lua_gettop(thread) == 0) {
          return COSTAT_DEAD;
        } else {
          return COSTAT_SUSPENDED;
        }
      }
      default:
        break;
      }
    }
    return COSTAT_DEAD;
  }

  //!
  //! @return if coroutine status is dead, return true. Otherwise return false
  //!
  bool isThreadDead() const { return costatus() == COSTAT_DEAD; }

  /// @brief set function for thread running.
  void setFunction(const LuaFunction &f);

  /// @brief get lua thread
  lua_State *getthread() {
    lua_State *state = state_();
    util::ScopedSavedStack save(state);
    int corStackIndex = pushStackIndex_(state);
    return lua_tothread(state, corStackIndex);
  }
};
}
}
