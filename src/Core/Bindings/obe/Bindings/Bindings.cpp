#include <Bindings/obe/Bindings/Bindings.hpp>

#include <Engine/Engine.hpp>

#include <Bindings/Config.hpp>

namespace obe::Bindings::Bindings
{
    void LoadFunctionIndexCoreBindings(sol::state_view state)
    {
        sol::table BindingsNamespace = state["obe"]["Bindings"].get<sol::table>();
        BindingsNamespace.set_function("IndexCoreBindings", &obe::Bindings::IndexCoreBindings);
    }
};