// Copyright satoren
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#pragma once

#include <string>
#include <vector>
#include <map>

#include "kaguya/config.hpp"
#include "kaguya/optional.hpp"

namespace kaguya {
namespace traits {
using standard::integral_constant;
using standard::true_type;
using standard::false_type;
using standard::remove_reference;
using standard::remove_pointer;
using standard::remove_const;
using standard::remove_volatile;
using standard::remove_cv;
using standard::is_function;
using standard::is_floating_point;
using standard::is_integral;
using standard::is_enum;
using standard::is_convertible;
using standard::is_same;
using standard::is_arithmetic;
using standard::is_union;
using standard::is_class;
using standard::is_pointer;
using standard::is_lvalue_reference;
using standard::is_const;
using standard::is_void;
#if KAGUYA_USE_CPP11
using std::enable_if;
#else
template <bool B, class T = void>
struct enable_if : boost::enable_if_c<B, T> {};
#endif

class Helper {};
/// @brief Check if T_Mem is a member object of a type. That is true if it is
/// not a member function
/// Required as MSVC throws a COMDAT error when using is_member_object_pointer
template <typename T_Mem> struct is_object {
  typedef typename standard::is_member_function_pointer<T_Mem Helper::*>::type
      NotResult;
  enum { value = !NotResult::value };
};

/// @brief Similar to std::decay but also removes const and volatile modifiers
/// if T is neither an array nor a function
template <class T> struct decay {
private:
  ///@ If T is a reference type, the type referrered to by T.	Otherwise, T.
  typedef typename standard::remove_reference<T>::type U;

public:
  typedef typename standard::conditional<
      standard::is_array<U>::value, typename standard::remove_extent<U>::type *,
      typename standard::conditional<
          is_function<U>::value, typename standard::add_pointer<U>::type,
          typename standard::remove_cv<U>::type>::type>::type type;
};

/// @brief Trait class that identifies whether T is a const reference type.
template <class T> struct is_const_reference : false_type {};
template <class T> struct is_const_reference<const T &> : true_type {};

/// @brief Obtains the type T without top-level const and reference.
template <typename T> struct remove_const_and_reference {
  /// @brief If T is const or reference, the same type as T but with the const
  /// reference removed.Otherwise, T
  typedef T type;
};
/// @brief Obtains the type T without top-level const and reference.
template <typename T> struct remove_const_and_reference<T &> {
  /// @brief If T is const or reference, the same type as T but with the const
  /// reference removed.Otherwise, T
  typedef T type;
};
/// @brief Obtains the type T without top-level const and reference.
template <typename T> struct remove_const_and_reference<const T> {
  /// @brief If T is const or reference, the same type as T but with the const
  /// reference removed.Otherwise, T
  typedef T type;
};
/// @brief Obtains the type T without top-level const and reference.
template <typename T> struct remove_const_and_reference<const T &> {
  /// @brief If T is const or reference, the same type as T but with the const
  /// reference removed.Otherwise, T
  typedef T type;
};

/// @brief Obtains the type T without top-level const reference.
template <typename T> struct remove_const_reference {
  /// @brief If T is const reference, the same type as T but with the const
  /// reference removed.Otherwise, T
  typedef T type;
};
/// @brief Obtains the type T without top-level const reference.
template <typename T> struct remove_const_reference<const T &> {
  /// @brief If T is const reference, the same type as T but with the const
  /// reference removed.Otherwise, T
  typedef T type;
};

/// @brief Trait class that identifies whether T is a std::vector type.
template <class T> struct is_std_vector : false_type {};
template <class T, class A>
struct is_std_vector<std::vector<T, A> > : true_type {};

/// @brief Trait class that identifies whether T is a std::map type.
template <class T> struct is_std_map : false_type {};
template <class K, class V, class C, class A>
struct is_std_map<std::map<K, V, C, A> > : true_type {};
}

/// @addtogroup lua_type_traits

/// @ingroup lua_type_traits
/// @brief If you want to customize the conversion to type of lua yourself ,
///  implement specialize of this class
template <typename T, typename Enable = void> struct lua_type_traits {
  typedef void Registerable;

  typedef typename traits::decay<T>::type NCRT;
  typedef const NCRT &get_type;
  typedef optional<get_type> opt_type;
  typedef const NCRT &push_type;

  static bool checkType(lua_State *l, int index);
  static bool strictCheckType(lua_State *l, int index);

  static get_type get(lua_State *l, int index);
  static opt_type opt(lua_State *l, int index) KAGUYA_NOEXCEPT;
  static int push(lua_State *l, push_type v);
#if KAGUYA_USE_RVALUE_REFERENCE
  static int push(lua_State *l, NCRT &&v);
#endif
};

/// @brief Trait class that identifies whether T is a userdata type.
template <typename T, typename Enable = void>
struct is_usertype : traits::false_type {};
template <typename T>
struct is_usertype<T, typename lua_type_traits<T>::Registerable>
    : traits::true_type {};

/// @brief Trait class that identifies whether T is a registerable by
/// UserdataMetatable.
template <typename T> struct is_registerable : is_usertype<T> {};
}
