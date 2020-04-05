#include <Bindings/Obe/obe.hpp>

#include <ObEngineCore.hpp>

#include <sol/sol.hpp>

namespace obe::Bindings
{
    void LoadFunctionInitEngine(sol::state_view state)
    {
        sol::table obeNamespace = state["obe"].get<sol::table>();
        obeNamespace.set_function("InitEngine", obe::InitEngine);
    }
};