#include <Bindings/obe/Config/Exceptions/Exceptions.hpp>

#include <Config/Exceptions.hpp>

#include <Bindings/Config.hpp>

namespace obe::Config::Exceptions::Bindings
{
    void LoadClassInvalidVersionFormat(sol::state_view state)
    {
        sol::table ExceptionsNamespace
            = state["obe"]["Config"]["Exceptions"].get<sol::table>();
        sol::usertype<obe::Config::Exceptions::InvalidVersionFormat>
            bindInvalidVersionFormat
            = ExceptionsNamespace
                  .new_usertype<obe::Config::Exceptions::InvalidVersionFormat>(
                      "InvalidVersionFormat", sol::call_constructor,
                      sol::constructors<obe::Config::Exceptions::InvalidVersionFormat(
                          std::string_view, obe::DebugInfo)>(),
                      sol::base_classes, sol::bases<obe::Exception>());
    }
};