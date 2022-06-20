#include <Bindings/obe/system/project/Prefixes/Prefixes.hpp>

#include <System/Project.hpp>

#include <Bindings/Config.hpp>

namespace obe::system::project::Prefixes::bindings
{
    void load_global_objects(sol::state_view state)
    {
        sol::table Prefixes_namespace
            = state["obe"]["system"]["project"]["Prefixes"].get<sol::table>();
        Prefixes_namespace["objects"] = obe::system::project::Prefixes::objects;
    }
    void load_global_scenes(sol::state_view state)
    {
        sol::table Prefixes_namespace
            = state["obe"]["system"]["project"]["Prefixes"].get<sol::table>();
        Prefixes_namespace["scenes"] = obe::system::project::Prefixes::scenes;
    }
};