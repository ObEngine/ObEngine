// Copyright satoren
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#pragma once

#include <exception>
#include <stdexcept>

namespace kaguya {
class LuaException : public std::exception {
  int status_;
  std::string what_;
  const char *what_c_;

public:
  LuaException(int status, const char *what) throw()
      : status_(status), what_c_(what) {}
  LuaException(int status, const std::string &what)
      : status_(status), what_(what), what_c_(0) {}
  int status() const throw() { return status_; }
  const char *what() const throw() { return what_c_ ? what_c_ : what_.c_str(); }

  ~LuaException() throw() {}
};
class KaguyaException : public std::exception {
  std::string what_;
  const char *what_c_;

public:
  KaguyaException(const char *what) throw() : what_c_(what) {}
  KaguyaException(const std::string &what) : what_(what), what_c_(0) {}
  const char *what() const throw() { return what_c_ ? what_c_ : what_.c_str(); }

  ~KaguyaException() throw() {}
};
class LuaTypeMismatch : public LuaException {
public:
  LuaTypeMismatch() throw() : LuaException(0, "type mismatch!!") {}
  LuaTypeMismatch(const char *what) throw() : LuaException(0, what) {}
  LuaTypeMismatch(const std::string &what) : LuaException(0, what) {}
};
class LuaMemoryError : public LuaException {
public:
  LuaMemoryError(int status, const char *what) throw()
      : LuaException(status, what) {}
  LuaMemoryError(int status, const std::string &what)
      : LuaException(status, what) {}
};
class LuaRuntimeError : public LuaException {
public:
  LuaRuntimeError(int status, const char *what) throw()
      : LuaException(status, what) {}
  LuaRuntimeError(int status, const std::string &what)
      : LuaException(status, what) {}
};
class LuaErrorRunningError : public LuaException {
public:
  LuaErrorRunningError(int status, const char *what) throw()
      : LuaException(status, what) {}
  LuaErrorRunningError(int status, const std::string &what)
      : LuaException(status, what) {}
};
class LuaGCError : public LuaException {
public:
  LuaGCError(int status, const char *what) throw()
      : LuaException(status, what) {}
  LuaGCError(int status, const std::string &what)
      : LuaException(status, what) {}
};
class LuaUnknownError : public LuaException {
public:
  LuaUnknownError(int status, const char *what) throw()
      : LuaException(status, what) {}
  LuaUnknownError(int status, const std::string &what)
      : LuaException(status, what) {}
};

class LuaSyntaxError : public LuaException {
public:
  LuaSyntaxError(int status, const std::string &what)
      : LuaException(status, what) {}
};

namespace except {
void OtherError(lua_State *state, const std::string &message);
void typeMismatchError(lua_State *state, const std::string &message);
void memoryError(lua_State *state, const char *message);
bool checkErrorAndThrow(int status, lua_State *state);
}
}
