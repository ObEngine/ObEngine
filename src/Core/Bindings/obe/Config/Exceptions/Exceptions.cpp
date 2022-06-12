#include <Bindings/obe/Config/Exceptions/Exceptions.hpp>

#include <Config/Exceptions.hpp>

#include <Bindings/Config.hpp>

namespace obe::config::Exceptions::Bindings
{
    void LoadClassConfigError(sol::state_view state)
    {
        sol::table ExceptionsNamespace = state["obe"]["config"]["exceptions"].get<sol::table>();
        sol::usertype<obe::config::Exceptions::ConfigError> bindConfigError
            = ExceptionsNamespace.new_usertype<obe::config::Exceptions::ConfigError>("ConfigError",
                sol::call_constructor,
                sol::constructors<obe::config::Exceptions::ConfigError(
                    std::vector<std::string>, obe::DebugInfo)>(),
                sol::base_classes,
                sol::bases<obe::Exception<obe::config::Exceptions::ConfigError>,
                    obe::BaseException>());
    }
    void LoadClassInvalidVersionFormat(sol::state_view state)
    {
        sol::table ExceptionsNamespace = state["obe"]["config"]["exceptions"].get<sol::table>();
        sol::usertype<obe::config::Exceptions::InvalidVersionFormat> bindInvalidVersionFormat
            = ExceptionsNamespace.new_usertype<obe::config::Exceptions::InvalidVersionFormat>(
                "InvalidVersionFormat", sol::call_constructor,
                sol::constructors<obe::config::Exceptions::InvalidVersionFormat(
                    std::string_view, obe::DebugInfo)>(),
                sol::base_classes,
                sol::bases<obe::Exception<obe::config::Exceptions::InvalidVersionFormat>,
                    obe::BaseException>());
    }
};