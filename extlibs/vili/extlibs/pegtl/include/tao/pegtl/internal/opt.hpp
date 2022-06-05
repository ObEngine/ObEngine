// Copyright (c) 2014-2021 Dr. Colin Hirsch and Daniel Frey
// Please see LICENSE for license or visit https://github.com/taocpp/PEGTL/

#ifndef TAO_PEGTL_INTERNAL_OPT_HPP
#define TAO_PEGTL_INTERNAL_OPT_HPP

#include <type_traits>

#include "../config.hpp"

#include "enable_control.hpp"
#include "seq.hpp"
#include "success.hpp"

#include "../apply_mode.hpp"
#include "../rewind_mode.hpp"
#include "../type_list.hpp"

namespace TAO_PEGTL_NAMESPACE::internal
{
   template< typename... Rules >
   struct opt
      : opt< seq< Rules... > >
   {};

   template<>
   struct opt<>
      : success
   {};

   template< typename Rule >
   struct opt< Rule >
   {
      using rule_t = opt;
      using subs_t = type_list< Rule >;

      template< apply_mode A,
                rewind_mode,
                template< typename... >
                class Action,
                template< typename... >
                class Control,
                typename ParseInput,
                typename... States >
      [[nodiscard]] static bool match( ParseInput& in, States&&... st )
      {
         (void)Control< Rule >::template match< A, rewind_mode::required, Action, Control >( in, st... );
         return true;
      }
   };

   template< typename... Rules >
   inline constexpr bool enable_control< opt< Rules... > > = false;

}  // namespace TAO_PEGTL_NAMESPACE::internal

#endif
