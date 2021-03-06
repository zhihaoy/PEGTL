// Copyright (c) 2014-2019 Dr. Colin Hirsch and Daniel Frey
// Please see LICENSE for license or visit https://github.com/taocpp/PEGTL/

#ifndef TAO_PEGTL_INTERNAL_NOT_AT_HPP
#define TAO_PEGTL_INTERNAL_NOT_AT_HPP

#include "../config.hpp"

#include "skip_control.hpp"
#include "trivial.hpp"

#include "../apply_mode.hpp"
#include "../rewind_mode.hpp"

#include "../analysis/generic.hpp"

namespace tao
{
   namespace TAO_PEGTL_NAMESPACE
   {
      namespace internal
      {
         template< typename... Rules >
         struct not_at;

         template<>
         struct not_at<>
            : trivial< false >
         {
         };

         template< typename... Rules >
         struct not_at
         {
            using analyze_t = analysis::generic< analysis::rule_type::opt, Rules... >;

            template< apply_mode,
                      rewind_mode,
                      template< typename... >
                      class Action,
                      template< typename... >
                      class Control,
                      typename Input,
                      typename... States >
            [[nodiscard]] static bool match( Input& in, States&&... st )
            {
               const auto m = in.template mark< rewind_mode::required >();
               return !( Control< Rules >::template match< apply_mode::nothing, rewind_mode::active, Action, Control >( in, st... ) && ... );
            }
         };

         template< typename... Rules >
         inline constexpr bool skip_control< not_at< Rules... > > = true;

      }  // namespace internal

   }  // namespace TAO_PEGTL_NAMESPACE

}  // namespace tao

#endif
