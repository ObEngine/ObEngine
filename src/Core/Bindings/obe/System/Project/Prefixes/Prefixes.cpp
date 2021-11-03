#include <Bindings/obe/System/Project/Prefixes/Prefixes.hpp>

#include <System/Project.hpp>

#include <Bindings/Config.hpp>

namespace obe::System::Project::Prefixes::Bindings
{
    void LoadGlobalObjects(sol::state_view state)
    {
        sol::table PrefixesNamespace
            = state["obe"]["System"]["Project"]["Prefixes"].get<sol::table>();
        PrefixesNamespace["objects"] = obe::System::Project::Prefixes::objects;
    }
    void LoadGlobalScenes(sol::state_view state)
    {
        sol::table PrefixesNamespace
            = state["obe"]["System"]["Project"]["Prefixes"].get<sol::table>();
        PrefixesNamespace["scenes"] = obe::System::Project::Prefixes::scenes;
    }
};