#include <Bindings/obe/bindings/Bindings.hpp>

#include <Engine/Engine.hpp>

#include <Bindings/Config.hpp>

namespace obe::bindings::bindings
{
    void load_function_index_core_bindings(sol::state_view state)
    {
        sol::table bindings_namespace = state["obe"]["bindings"].get<sol::table>();
        bindings_namespace.set_function("index_core_bindings", &obe::bindings::index_core_bindings);
    }
};