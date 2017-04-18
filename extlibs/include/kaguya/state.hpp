// Copyright satoren
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#pragma once

#include <string>
#include <iostream>

#include "kaguya/config.hpp"

#include "kaguya/utility.hpp"
#include "kaguya/metatable.hpp"
#include "kaguya/error_handler.hpp"

#include "kaguya/lua_ref_table.hpp"
#include "kaguya/lua_ref_function.hpp"

namespace kaguya {
/// @addtogroup State
/// @{

/// @brief Load library info type @see State::openlibs @see State::State(const
/// LoadLibs &libs)
typedef std::pair<std::string, lua_CFunction> LoadLib;

/// @brief Load libraries info @see State::openlibs @see State::State(const
/// LoadLibs &libs)
typedef std::vector<LoadLib> LoadLibs;

/// @brief return no load library type @see State::State(const LoadLibs &libs)
inline LoadLibs NoLoadLib() { return LoadLibs(); }

/// @brief All load standard libraries type @see State::openlibs
struct AllLoadLibs {};

template <typename Allocator>
void *AllocatorFunction(void *ud, void *ptr, size_t osize, size_t nsize) {
  Allocator *allocator = static_cast<Allocator *>(ud);
  if (nsize == 0) {
    allocator->deallocate(ptr, osize);
  } else if (ptr) {
    return allocator->reallocate(ptr, nsize);
  } else {
    return allocator->allocate(nsize);
  }
  return 0;
}

struct DefaultAllocator {
  typedef void *pointer;
  typedef size_t size_type;
  pointer allocate(size_type n) { return std::malloc(n); }
  pointer reallocate(pointer p, size_type n) { return std::realloc(p, n); }
  void deallocate(pointer p, size_type n) {
    KAGUYA_UNUSED(n);
    std::free(p);
  }
};

/// lua_State wrap class
class State {
  standard::shared_ptr<void> allocator_holder_;
  lua_State *state_;
  bool created_;

  // non copyable
  State(const State &);
  State &operator=(const State &);

  static int initializing_panic(lua_State *L) {
    ErrorHandler::throwDefaultError(lua_status(L), lua_tostring(L, -1));
    return 0; // return to Lua to abort
  }
  static int default_panic(lua_State *L) {
    if (ErrorHandler::handle(lua_status(L), L)) {
      return 0;
    }
    fprintf(stderr, "PANIC: unprotected error in call to Lua API (%s)\n",
            lua_tostring(L, -1));
    fflush(stderr);
    return 0; // return to Lua to abort
  }
  static void stderror_out(int status, const char *message) {
    KAGUYA_UNUSED(status);
    std::cerr << message << std::endl;
  }

  template <typename Libs> void init(const Libs &lib) {
    if (state_) {
      lua_atpanic(state_, &initializing_panic);
      try {
        if (!ErrorHandler::getHandler(state_)) {
          setErrorHandler(&stderror_out);
        }
        openlibs(lib);
        lua_atpanic(state_, &default_panic);
      } catch (const LuaException &) {
        lua_close(state_);
        state_ = 0;
      }
    }
  }

public:
  /// @brief create Lua state with lua standard library
  State() : allocator_holder_(), state_(luaL_newstate()), created_(true) {
    init(AllLoadLibs());
  }

  /// @brief create Lua state with lua standard library. Can not use this
  /// constructor at luajit. error message is 'Must use luaL_newstate() for 64
  /// bit target'
  /// @param allocator allocator for memory allocation @see DefaultAllocator
  template <typename Allocator>
  State(standard::shared_ptr<Allocator> allocator)
      : allocator_holder_(allocator),
        state_(lua_newstate(&AllocatorFunction<Allocator>,
                            allocator_holder_.get())),
        created_(true) {
    init(AllLoadLibs());
  }

  /// @brief create Lua state with (or without) libraries.
  /// @param libs load libraries
  /// e.g. LoadLibs libs;libs.push_back(LoadLib("libname",libfunction));State
  /// state(libs);
  /// e.g. State state({{"libname",libfunction}}); for c++ 11
  State(const LoadLibs &libs)
      : allocator_holder_(), state_(luaL_newstate()), created_(true) {
    init(libs);
  }

  /// @brief create Lua state with (or without) libraries. Can not use this
  /// constructor at luajit. error message is 'Must use luaL_newstate() for 64
  /// bit target'
  /// @param libs load libraries
  /// @param allocator allocator for memory allocation @see DefaultAllocator
  template <typename Allocator>
  State(const LoadLibs &libs, standard::shared_ptr<Allocator> allocator)
      : allocator_holder_(allocator),
        state_(lua_newstate(&AllocatorFunction<Allocator>,
                            allocator_holder_.get())),
        created_(true) {
    init(libs);
  }

  /// @brief construct using created lua_State.
  /// @param lua created lua_State. It is not call lua_close() in this class
  State(lua_State *lua) : state_(lua), created_(false) {
    if (state_) {
      if (!ErrorHandler::getHandler(state_)) {
        setErrorHandler(&stderror_out);
      }
    }
  }
  ~State() {
    if (created_ && state_) {
      lua_close(state_);
    }
  }

  /// @brief set error handler for lua error.
  void
  setErrorHandler(standard::function<void(int statuscode, const char *message)>
                      errorfunction) {
    if (!state_) {
      return;
    }
    util::ScopedSavedStack save(state_);
    ErrorHandler::registerHandler(state_, errorfunction);
  }

  /// @brief load all lua standard library
  void openlibs(AllLoadLibs = AllLoadLibs()) {
    if (!state_) {
      return;
    }
    luaL_openlibs(state_);
  }

  /// @brief load lua library
  LuaStackRef openlib(const LoadLib &lib) {
    if (!state_) {
      return LuaStackRef();
    }
    luaL_requiref(state_, lib.first.c_str(), lib.second, 1);
    return LuaStackRef(state_, -1, true);
  }
  /// @brief load lua library
  LuaStackRef openlib(std::string name, lua_CFunction f) {
    return openlib(LoadLib(name, f));
  }

  /// @brief load lua libraries
  void openlibs(const LoadLibs &libs) {
    for (LoadLibs::const_iterator it = libs.begin(); it != libs.end(); ++it) {
      openlib(*it);
    }
  }

  /// @brief If there are no errors,compiled file as a Lua function and return.
  ///  Otherwise send error message to error handler and return nil reference
  /// @param file  file path of lua script
  /// @return reference of lua function
  LuaFunction loadfile(const std::string &file) {
    return LuaFunction::loadfile(state_, file);
  }
  /// @brief If there are no errors,compiled file as a Lua function and return.
  ///  Otherwise send error message to error handler and return nil reference
  /// @param file  file path of lua script
  /// @return reference of lua function
  LuaFunction loadfile(const char *file) {
    return LuaFunction::loadfile(state_, file);
  }

  /// @brief If there are no errors,compiled stream as a Lua function and
  /// return.
  ///  Otherwise send error message to error handler and return nil reference
  /// @param stream stream of lua script
  /// @param chunkname chunkname of lua script
  /// @return reference of lua function
  LuaFunction loadstream(std::istream &stream, const char *chunkname = 0) {
    return LuaFunction::loadstream(state_, stream, chunkname);
  }
  /// @brief Loads and runs the given stream.
  /// @param stream stream of lua script
  /// @param chunkname chunkname of lua script
  /// @param env execute env table
  /// @return If there are no errors, returns true.Otherwise return false
  bool dostream(std::istream &stream, const char *chunkname = 0,
                const LuaTable &env = LuaTable()) {
    util::ScopedSavedStack save(state_);
    LuaStackRef f = LuaFunction::loadstreamtostack(state_, stream, chunkname);
    if (!f) { // load failed
      return false;
    }
    if (!env.isNilref()) {
      f.setFunctionEnv(env);
    }

    FunctionResults ret = f.call<FunctionResults>();
    return !ret.resultStatus();
  }

  /// @brief If there are no errors,compiled string as a Lua function and
  /// return.
  ///  Otherwise send error message to error handler and return nil reference
  /// @param str lua code
  /// @return reference of lua function
  LuaFunction loadstring(const std::string &str) {
    return LuaFunction::loadstring(state_, str);
  }
  /// @brief If there are no errors,compiled string as a Lua function and
  /// return.
  ///  Otherwise send error message to error handler and return nil reference
  /// @param str lua code
  /// @return reference of lua function
  LuaFunction loadstring(const char *str) {
    return LuaFunction::loadstring(state_, str);
  }

  /// @brief Loads and runs the given file.
  /// @param file file path of lua script
  /// @param env execute env table
  /// @return If there are no errors, returns true.Otherwise return false
  bool dofile(const std::string &file, const LuaTable &env = LuaTable()) {
    return dofile(file.c_str(), env);
  }

  /// @brief Loads and runs the given file.
  /// @param file file path of lua script
  /// @param env execute env table
  /// @return If there are no errors, returns true.Otherwise return false
  bool dofile(const char *file, const LuaTable &env = LuaTable()) {
    util::ScopedSavedStack save(state_);

    int status = luaL_loadfile(state_, file);

    if (status) {
      ErrorHandler::handle(status, state_);
      return false;
    }

    if (!env.isNilref()) { // register _ENV
      env.push();
#if LUA_VERSION_NUM >= 502
      lua_setupvalue(state_, -2, 1);
#else
      lua_setfenv(state_, -2);
#endif
    }

    status = lua_pcall_wrap(state_, 0, LUA_MULTRET);
    if (status) {
      ErrorHandler::handle(status, state_);
      return false;
    }
    return true;
  }

  /// @brief Loads and runs the given string.
  /// @param str lua script cpde
  /// @param env execute env table
  /// @return If there are no errors, returns true.Otherwise return false
  bool dostring(const char *str, const LuaTable &env = LuaTable()) {
    util::ScopedSavedStack save(state_);

    int status = luaL_loadstring(state_, str);
    if (status) {
      ErrorHandler::handle(status, state_);
      return false;
    }
    if (!env.isNilref()) { // register _ENV
      env.push();
#if LUA_VERSION_NUM >= 502
      lua_setupvalue(state_, -2, 1);
#else
      lua_setfenv(state_, -2);
#endif
    }
    status = lua_pcall_wrap(state_, 0, LUA_MULTRET);
    if (status) {
      ErrorHandler::handle(status, state_);
      return false;
    }
    return true;
  }
  /// @brief Loads and runs the given string.
  /// @param str lua script cpde
  /// @param env execute env table
  /// @return If there are no errors, returns true.Otherwise return false
  bool dostring(const std::string &str, const LuaTable &env = LuaTable()) {
    return dostring(str.c_str(), env);
  }

  /// @brief Loads and runs the given string.
  /// @param str lua script cpde
  /// @return If there are no errors, returns true.Otherwise return false
  bool operator()(const std::string &str) { return dostring(str); }

  /// @brief Loads and runs the given string.
  /// @param str lua script cpde
  /// @return If there are no errors, returns true.Otherwise return false
  bool operator()(const char *str) { return dostring(str); }

  /// @brief return element reference from global table
  /// @param str table key
  /// @return proxy class for reference to table.
  TableKeyReferenceProxy<std::string> operator[](const std::string &str) {
    int stack_top = lua_gettop(state_);
    util::push_args(state_, GlobalTable());
    int table_index = stack_top + 1;
    return TableKeyReferenceProxy<std::string>(state_, table_index, str,
                                               stack_top, NoTypeCheck());
  }

  /// @brief return element reference from global table
  /// @param str table key
  /// @return proxy class for reference to table.

  TableKeyReferenceProxy<const char *> operator[](const char *str) {
    int stack_top = lua_gettop(state_);
    util::push_args(state_, GlobalTable());
    int table_index = stack_top + 1;
    return TableKeyReferenceProxy<const char *>(state_, table_index, str,
                                                stack_top, NoTypeCheck());
  }

  /// @brief return global table
  /// @return global table.
  LuaTable globalTable() { return newRef(GlobalTable()); }

  /// @brief create new Lua reference from argument value
  /// @return Lua reference.
  template <typename T> LuaRef newRef(const T &value) {
    return LuaRef(state_, value);
  }
#if KAGUYA_USE_CPP11

  /// @brief create new Lua reference from argument value
  /// @return Lua reference.
  template <typename T> LuaRef newRef(T &&value) {
    return LuaRef(state_, std::forward<T>(value));
  }
#endif

  /// @brief create new Lua table
  /// @return Lua table reference.
  LuaTable newTable() { return LuaTable(state_); }

  /// @brief create new Lua table
  /// @param reserve_array reserved array count
  /// @param reserve_record reserved record count
  /// @return Lua table reference.
  LuaTable newTable(int reserve_array, int reserve_record) {
    return LuaTable(state_, NewTable(reserve_array, reserve_record));
  }

  /// @brief create new Lua thread
  /// @return Lua thread reference.
  LuaThread newThread() { return LuaThread(state_); }

  /// @brief create new Lua thread with lua function
  /// @param f function
  /// @return Lua thread reference.
  LuaThread newThread(const LuaFunction &f) {
    LuaThread cor(state_);
    cor.setFunction(f);
    return cor;
  }

  /// @brief argument value push to stack.
  /// @param value value
  template <typename T> void pushToStack(T value) {
    util::push_args(state_, value);
  }

  /// @brief pop from stack.
  /// @return reference to pop value.
  LuaRef popFromStack() { return LuaRef(state_, StackTop()); }

  /// @brief Garbage Collection of Lua
  struct GCType {
    GCType(lua_State *state) : state_(state) {}

    /// @brief Performs a full garbage-collection cycle.
    void collect() { lua_gc(state_, LUA_GCCOLLECT, 0); }
    /// @brief Performs an incremental step of garbage collection.
    /// @return If returns true,the step finished a collection cycle.
    bool step() { return lua_gc(state_, LUA_GCSTEP, 0) == 1; }

    /// @brief Performs an incremental step of garbage collection.
    /// @param size the collector will perform as if that amount of memory (in
    /// KBytes) had been allocated by Lua.
    bool step(int size) { return lua_gc(state_, LUA_GCSTEP, size) == 1; }

    /// @brief enable gc
    void restart() { enable(); }

    /// @brief disable gc
    void stop() { disable(); }

    /// @brief returns the total memory in use by Lua in Kbytes.
    int count() const { return lua_gc(state_, LUA_GCCOUNT, 0); }

    /// @brief sets arg as the new value for the pause of the collector. Returns
    /// the previous value for pause.
    int steppause(int value) { return lua_gc(state_, LUA_GCSETPAUSE, value); }

    ///  @brief sets arg as the new value for the step multiplier of the
    ///  collector. Returns the previous value for step.
    int setstepmul(int value) {
      return lua_gc(state_, LUA_GCSETSTEPMUL, value);
    }

    /// @brief enable gc
    void enable() { lua_gc(state_, LUA_GCRESTART, 0); }

    /// @brief disable gc
    void disable() { lua_gc(state_, LUA_GCSTOP, 0); }
#if LUA_VERSION_NUM >= 502

    /// @brief returns a boolean that tells whether the collector is running
    bool isrunning() const { return isenabled(); }

    /// @brief returns a boolean that tells whether the collector is running
    bool isenabled() const { return lua_gc(state_, LUA_GCISRUNNING, 0) != 0; }
#endif

  private:
    lua_State *state_;
  };

  // /@brief  return Garbage collection interface.
  GCType gc() const { return GCType(state_); }
  /// @brief performs a full garbage-collection cycle.
  void garbageCollect() { gc().collect(); }

  /// @brief returns the current amount of memory (in Kbytes) in use by Lua.
  size_t useKBytes() const { return size_t(gc().count()); }

  /// @brief create Table and push to stack.
  /// using for Lua module
  /// @return return Lua Table Reference
  LuaTable newLib() {
    LuaTable newtable = newTable();
    newtable.push(state_);
    return newtable;
  }

  /// @brief return lua_State*.
  /// @return lua_State*
  lua_State *state() { return state_; };

  /// @brief check valid lua_State.
  bool isInvalid() const { return !state_; }
};

/// @}
}
