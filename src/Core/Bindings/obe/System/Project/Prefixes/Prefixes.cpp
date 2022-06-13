#include <Bindings/obe/System/Project/Prefixes/Prefixes.hpp>

#include <System/Project.hpp>

#include <Bindings/Config.hpp>

namespace obe::system::project::Prefixes::Bindings
{
    void LoadGlobalObjects(sol::state_view state)
    {
        sol::table PrefixesNamespace
            = state["obe"]["system"]["project"]["prefixes"].get<sol::table>();
        PrefixesNamespace["objects"] = obe::system::project::Prefixes::objects;
    }
    void LoadGlobalScenes(sol::state_view state)
    {
        sol::table PrefixesNamespace
            = state["obe"]["system"]["project"]["prefixes"].get<sol::table>();
        PrefixesNamespace["scenes"] = obe::system::project::Prefixes::scenes;
    }
};