#include <Bindings/obe/config/Exceptions/Exceptions.hpp>

#include <Config/Exceptions.hpp>

#include <Bindings/Config.hpp>

namespace obe::config::Exceptions::bindings
{
    void load_class_config_error(sol::state_view state)
    {
        sol::table Exceptions_namespace = state["obe"]["config"]["Exceptions"].get<sol::table>();
        sol::usertype<obe::config::Exceptions::ConfigError> bind_config_error
            = Exceptions_namespace.new_usertype<obe::config::Exceptions::ConfigError>("ConfigError",
                sol::call_constructor,
                sol::constructors<obe::config::Exceptions::ConfigError(
                    std::vector<std::string>, obe::DebugInfo)>(),
                sol::base_classes,
                sol::bases<obe::Exception<obe::config::Exceptions::ConfigError>,
                    obe::BaseException>());
    }
    void load_class_invalid_version_format(sol::state_view state)
    {
        sol::table Exceptions_namespace = state["obe"]["config"]["Exceptions"].get<sol::table>();
        sol::usertype<obe::config::Exceptions::InvalidVersionFormat> bind_invalid_version_format
            = Exceptions_namespace.new_usertype<obe::config::Exceptions::InvalidVersionFormat>(
                "InvalidVersionFormat", sol::call_constructor,
                sol::constructors<obe::config::Exceptions::InvalidVersionFormat(
                    std::string_view, obe::DebugInfo)>(),
                sol::base_classes,
                sol::bases<obe::Exception<obe::config::Exceptions::InvalidVersionFormat>,
                    obe::BaseException>());
    }
};