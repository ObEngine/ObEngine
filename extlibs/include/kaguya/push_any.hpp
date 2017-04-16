// Copyright satoren
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
#pragma once
#include <memory>

#include "kaguya/config.hpp"
#include "kaguya/traits.hpp"
#include "kaguya/utility.hpp"

namespace kaguya {
/// @brief any data holder class for push to lua
class AnyDataPusher {
public:
  int pushToLua(lua_State *state) const {
    if (empty()) {
      lua_pushnil(state);
      return 1;
    } else {
      return holder_->pushToLua(state);
    }
  }

  AnyDataPusher() : holder_() {}

  template <typename DataType>
  AnyDataPusher(const DataType &v) : holder_(new DataHolder<DataType>(v)) {}

#if KAGUYA_USE_CPP11
  AnyDataPusher(AnyDataPusher &&other) : holder_(std::move(other.holder_)) {}
  AnyDataPusher &operator=(AnyDataPusher &&rhs) {
    holder_ = std::move(rhs.holder_);
    return *this;
  }
  template <typename DataType>
  AnyDataPusher(DataType &&v)
      : holder_(new DataHolder<DataType>(std::move(v))) {}
#endif
  AnyDataPusher(const AnyDataPusher &other) : holder_(other.holder_) {}
  AnyDataPusher &operator=(const AnyDataPusher &other) {
    holder_ = other.holder_;
    return *this;
  }

  bool empty() const { return !holder_.get(); }

private:
  struct DataHolderBase {
    virtual int pushToLua(lua_State *data) const = 0;
    //			virtual DataHolderBase * clone(void) = 0;
    virtual ~DataHolderBase() {}
  };
  template <typename Type> class DataHolder : public DataHolderBase {
    typedef typename traits::decay<Type>::type DataType;

  public:
#if KAGUYA_USE_CPP11
    explicit DataHolder(DataType &&v) : data_(std::forward<DataType>(v)) {}
#else
    explicit DataHolder(const DataType &v) : data_(v) {}
#endif
    virtual int pushToLua(lua_State *state) const {
      return util::push_args(state, data_);
    }

  private:
    DataType data_;
  };
  // specialize for string literal
  template <int N> struct DataHolder<const char[N]> : DataHolder<std::string> {
    explicit DataHolder(const char *v)
        : DataHolder<std::string>(
              std::string(v, v[N - 1] != '\0' ? v + N : v + N - 1)) {}
  };
  template <int N> struct DataHolder<char[N]> : DataHolder<std::string> {
    explicit DataHolder(const char *v)
        : DataHolder<std::string>(
              std::string(v, v[N - 1] != '\0' ? v + N : v + N - 1)) {}
  };
  standard::shared_ptr<DataHolderBase> holder_;
};

/// @ingroup lua_type_traits
/// @brief lua_type_traits for AnyDataPusher
template <> struct lua_type_traits<AnyDataPusher> {
  static int push(lua_State *l, const AnyDataPusher &data) {
    return data.pushToLua(l);
  }
};
}
