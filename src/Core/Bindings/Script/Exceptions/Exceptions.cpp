#include <Bindings/Script/Exceptions/Exceptions.hpp>

#include <Script/Exceptions.hpp>

#include <sol/sol.hpp>

namespace obe::Script::Exceptions::Bindings
{
    void LoadClassNoScriptComponent(sol::state_view state)
    {
        sol::table ExceptionsNamespace
            = state["obe"]["Script"]["Exceptions"].get<sol::table>();
        sol::usertype<obe::Script::Exceptions::NoScriptComponent> bindNoScriptComponent
            = ExceptionsNamespace
                  .new_usertype<obe::Script::Exceptions::NoScriptComponent>(
                      "NoScriptComponent", sol::call_constructor,
                      sol::constructors<obe::Script::Exceptions::NoScriptComponent(
                          std::string_view, std::string_view, obe::DebugInfo)>(),
                      sol::base_classes, sol::bases<obe::Exception>());
    }
};