#include <Bindings/Script/Exceptions/Exceptions.hpp>

#include <Script/Exceptions.hpp>

#include <sol/sol.hpp>

namespace obe::Script::Exceptions::Bindings
{
    void LoadClassNoScriptComponent(sol::state_view state)
    {
        sol::table ExceptionsNamespace
            = state["obe"]["Script"]["Exceptions"].get<sol::table>();
    }
};