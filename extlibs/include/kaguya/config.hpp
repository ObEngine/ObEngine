// Copyright satoren
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
#pragma once

#include<string>
extern "C" {
#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>
}

#ifndef KAGUYA_USE_CPP11
#if defined(__cpp_decltype) || __cplusplus >= 201103L || (defined(_MSC_VER) && _MSC_VER >= 1800)
#define KAGUYA_USE_CPP11 1
#else
#define KAGUYA_USE_CPP11 0
#endif
#endif


#if KAGUYA_USE_CPP11
#include <functional>
#include <tuple>
#include <memory>
#include <utility>
#include <type_traits>
#include <initializer_list>
#include <array>
#else
#include <boost/function.hpp>
#include <boost/tuple/tuple.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>
#include <boost/type_traits.hpp>
#include <boost/static_assert.hpp>
#include <boost/utility/result_of.hpp>
#endif



#ifndef KAGUYA_NO_USERDATA_TYPE_CHECK
#define KAGUYA_NO_USERDATA_TYPE_CHECK 0
#endif

#ifndef KAGUYA_USE_RVALUE_REFERENCE
#if KAGUYA_USE_CPP11
#define KAGUYA_USE_RVALUE_REFERENCE 1
#else
#define KAGUYA_USE_RVALUE_REFERENCE 0
#endif
#endif


#ifdef KAGUYA_NO_VECTOR_AND_MAP_TO_TABLE
#define KAGUYA_NO_STD_VECTOR_TO_TABLE
#define KAGUYA_NO_STD_MAP_TO_TABLE
#endif


#if !KAGUYA_USE_CPP11
#ifndef KAGUYA_FUNCTION_MAX_ARGS
///! max argumeent number for binding function. this define used C++03 only.
#define KAGUYA_FUNCTION_MAX_ARGS 9
#endif

#ifndef KAGUYA_FUNCTION_MAX_TUPLE_SIZE
///! this define used C++03 only.
#define KAGUYA_FUNCTION_MAX_TUPLE_SIZE 9
#endif

#ifndef KAGUYA_FUNCTION_MAX_OVERLOADS
#define KAGUYA_FUNCTION_MAX_OVERLOADS 9
#endif

#endif

#ifndef KAGUYA_CLASS_MAX_BASE_CLASSES
#define KAGUYA_CLASS_MAX_BASE_CLASSES 9
#endif


#ifndef KAGUYA_USE_CXX_ABI_DEMANGLE
#if defined(__GNUC__) || defined(__clang__)
#define KAGUYA_USE_CXX_ABI_DEMANGLE 1
#else
#define KAGUYA_USE_CXX_ABI_DEMANGLE 0
#endif
#endif


#ifndef KAGUYA_USE_SHARED_LUAREF
#define KAGUYA_USE_SHARED_LUAREF 0
#endif



#ifndef KAGUYA_NOEXCEPT
# if KAGUYA_USE_CPP11 && (!defined(_MSC_VER) || _MSC_VER >= 1900)
#  define KAGUYA_NOEXCEPT noexcept
# else
#  define KAGUYA_NOEXCEPT throw()
# endif
#endif

#ifndef KAGUYA_DEPRECATED_FEATURE
#if __cplusplus >= 201402L && defined(__has_cpp_attribute)
#if  __has_cpp_attribute(deprecated)
//C++ standard depecated
#define KAGUYA_DEPRECATED_FEATURE(MSG) [[deprecated(MSG)]]
#endif
#endif
#endif
#ifndef KAGUYA_DEPRECATED_FEATURE
#if defined(_MSC_VER)
//MSVC depecated
#define KAGUYA_DEPRECATED_FEATURE(MSG) __declspec(deprecated(MSG)) 
#elif defined(__GNUC__) || defined(__clang__)
#define KAGUYA_DEPRECATED_FEATURE(MSG) __attribute__((deprecated))
#else
#define KAGUYA_DEPRECATED_FEATURE(MSG)
#endif

#endif

#define KAGUYA_UNUSED(V) (void)(V)

namespace kaguya
{
#if defined(_MSC_VER) && _MSC_VER <= 1500
	typedef unsigned char uint8_t;
	typedef int int32_t;
	typedef long long int64_t;
#endif

	namespace standard
	{
#if KAGUYA_USE_CPP11
		using namespace std;
#define KAGUYA_STATIC_ASSERT static_assert

#else
		using namespace boost;
#define KAGUYA_STATIC_ASSERT BOOST_STATIC_ASSERT_MSG
#endif
	}

#if LUA_VERSION_NUM > 502
	typedef lua_Integer luaInt;
#else
	typedef int32_t luaInt;
#endif
}

