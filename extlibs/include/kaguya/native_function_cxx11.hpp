// Copyright satoren
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
#pragma once

#include <string>

#include "kaguya/config.hpp"
#include "kaguya/utility.hpp"
#include "kaguya/object.hpp"

namespace kaguya {
namespace nativefunction {
template <std::size_t... indexes> struct index_tuple {};

template <std::size_t first, std::size_t last, class result = index_tuple<>,
          bool flag = first >= last>
struct index_range {
  using type = result;
};

template <std::size_t step, std::size_t last, std::size_t... indexes>
struct index_range<step, last, index_tuple<indexes...>, false>
    : index_range<step + 1, last, index_tuple<indexes..., step> > {};

template <class F, class Ret, class... Args, size_t... Indexes>
int _call_apply(lua_State *state, F &&f, index_tuple<Indexes...>,
                util::FunctionSignatureType<Ret, Args...>) {
  return util::push_args(
      state, util::invoke(f, lua_type_traits<Args>::get(state, Indexes)...));
}
template <class F, class... Args, size_t... Indexes>
int _call_apply(lua_State *state, F &&f, index_tuple<Indexes...>,
                util::FunctionSignatureType<void, Args...>) {
  KAGUYA_UNUSED(state);
  util::invoke(f, lua_type_traits<Args>::get(state, Indexes)...);
  return 0;
}

inline bool all_true() { return true; }
template <class Arg, class... Args>
bool all_true(Arg f, Args... args) { // check from backward and lazy evaluation
  return all_true(args...) && bool(f);
}

inline void join(std::string &, const char *) {}
template <class Arg, class... Args>
void join(std::string &result, const char *delim, const Arg &str,
          const Args &... args) {
  result += str;
  result += delim;
  join(result, delim, args...);
}

template <typename T> struct _wcheckeval {
  _wcheckeval(lua_State *s, int i, bool opt)
      : state(s), index(i), opt_arg(opt) {}
  lua_State *state;
  int index;
  bool opt_arg;
  operator bool() {
    return (opt_arg && lua_isnoneornil(state, index)) ||
           lua_type_traits<T>::checkType(state, index);
  }
};

template <typename T> struct _scheckeval {
  _scheckeval(lua_State *s, int i, bool opt)
      : state(s), index(i), opt_arg(opt) {}
  lua_State *state;
  int index;
  bool opt_arg;
  operator bool() {
    return (opt_arg && lua_isnoneornil(state, index)) ||
           lua_type_traits<T>::strictCheckType(state, index);
  }
};

template <class... Args, size_t... Indexes>
bool _ctype_apply(lua_State *state, index_tuple<Indexes...>,
                  util::TypeTuple<Args...>, int opt_count) {
  KAGUYA_UNUSED(state);
  KAGUYA_UNUSED(opt_count);
  return all_true(_wcheckeval<Args>(
      state, Indexes, sizeof...(Indexes) - opt_count < Indexes)...);
}
template <class... Args, size_t... Indexes>
bool _sctype_apply(lua_State *state, index_tuple<Indexes...>,
                   util::TypeTuple<Args...>, int opt_count) {
  KAGUYA_UNUSED(state);
  KAGUYA_UNUSED(opt_count);
  return all_true(_scheckeval<Args>(
      state, Indexes, sizeof...(Indexes) - opt_count < Indexes)...);
}

template <class... Args, size_t... Indexes>
std::string _type_name_apply(index_tuple<Indexes...>, util::TypeTuple<Args...>,
                             int opt_count) {
  KAGUYA_UNUSED(opt_count);
  std::string result;
  const int max_arg = sizeof...(Args);
  join(result, ",",
       (((max_arg - opt_count < int(Indexes)) ? std::string("[OPT]")
                                              : std::string("")) +
        util::pretty_name(typeid(Args)))...);
  return result;
}

template <class F> int call(lua_State *state, F &&f) {
  typedef typename traits::decay<F>::type ftype;
  typedef typename util::FunctionSignature<ftype>::type fsigtype;
  typedef typename index_range<1, fsigtype::argument_count + 1>::type index;
  return _call_apply(state, f, index(), fsigtype());
}
template <class F>
bool checkArgTypes(lua_State *state, const F &, int opt_count = 0) {
  typedef typename traits::decay<F>::type ftype;
  typedef typename util::FunctionSignature<ftype>::type fsigtype;
  typedef typename index_range<1, fsigtype::argument_count + 1>::type index;
  typedef typename fsigtype::argument_type_tuple argument_type_tuple;
  return _ctype_apply(state, index(), argument_type_tuple(), opt_count);
}
template <class F>
bool strictCheckArgTypes(lua_State *state, const F &, int opt_count = 0) {
  typedef typename traits::decay<F>::type ftype;
  typedef typename util::FunctionSignature<ftype>::type fsigtype;
  typedef typename index_range<1, fsigtype::argument_count + 1>::type index;
  typedef typename fsigtype::argument_type_tuple argument_type_tuple;
  return _sctype_apply(state, index(), argument_type_tuple(), opt_count);
}

template <class F> std::string argTypesName(const F &, int opt_count = 0) {
  typedef typename traits::decay<F>::type ftype;
  typedef typename util::FunctionSignature<ftype>::type fsigtype;
  typedef typename index_range<1, fsigtype::argument_count + 1>::type index;
  typedef typename fsigtype::argument_type_tuple argument_type_tuple;
  return _type_name_apply(index(), argument_type_tuple(), opt_count);
}
template <class F> int minArgCount(const F &) {
  typedef typename traits::decay<F>::type ftype;
  typedef typename util::FunctionSignature<ftype>::type fsigtype;
  return fsigtype::argument_count;
}
template <class F> int maxArgCount(const F &) {
  typedef typename traits::decay<F>::type ftype;
  typedef typename util::FunctionSignature<ftype>::type fsigtype;
  return fsigtype::argument_count;
}

// for constructor
template <typename T> struct ConstructorFunctor;

template <typename ClassType, typename... Args>
struct ConstructorFunctor<util::FunctionSignatureType<ClassType, Args...> > {
  typedef util::FunctionSignatureType<ClassType, Args...> signature_type;
  typedef typename index_range<1, sizeof...(Args) + 1>::type get_index;

  template <size_t... Indexes>
  int invoke(lua_State *L, index_tuple<Indexes...>) const {
    typedef ObjectWrapper<ClassType> wrapper_type;
    void *storage = lua_newuserdata(L, sizeof(wrapper_type));
    try {
      new (storage) wrapper_type(lua_type_traits<Args>::get(L, Indexes)...);
    } catch (...) {
      lua_pop(L, 1);
      throw;
    }

    class_userdata::setmetatable<ClassType>(L);
    return 1;
  }

  int operator()(lua_State *L) const { return invoke(L, get_index()); }

  bool checkArgTypes(lua_State *L, int opt_count = 0) const {
    return _ctype_apply(L, get_index(),
                        typename signature_type::argument_type_tuple(),
                        opt_count);
  }
  bool strictCheckArgTypes(lua_State *L, int opt_count = 0) const {
    return _sctype_apply(L, get_index(),
                         typename signature_type::argument_type_tuple(),
                         opt_count);
  }
  std::string argTypesName(int opt_count = 0) const {
    return _type_name_apply(
        get_index(), typename signature_type::argument_type_tuple(), opt_count);
  }
};

template <typename ClassType, typename... Args> struct ConstructorFunction;
template <typename ClassType, typename... Args>
struct ConstructorFunction<ClassType(Args...)> {
  typedef ConstructorFunctor<util::FunctionSignatureType<ClassType, Args...> >
      type;
};
template <typename ClassType, typename RetType, typename... Args>
struct ConstructorFunction<ClassType,
                           RetType(Args...)> // class type check version
{
  typedef ConstructorFunctor<util::FunctionSignatureType<ClassType, Args...> >
      type;
};
}
using nativefunction::ConstructorFunction;
}
