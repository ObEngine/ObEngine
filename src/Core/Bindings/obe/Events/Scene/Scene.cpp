#include <Bindings/obe/Events/Scene/Scene.hpp>

#include <Scene/Scene.hpp>

#include <Bindings/Config.hpp>

namespace obe::Events::Scene::Bindings
{
    void LoadClassLoaded(sol::state_view state)
    {
        sol::table SceneNamespace = state["obe"]["Events"]["Scene"].get<sol::table>();
        sol::usertype<obe::Events::Scene::Loaded> bindLoaded
            = SceneNamespace.new_usertype<obe::Events::Scene::Loaded>(
                "Loaded", sol::call_constructor, sol::default_constructor);
        bindLoaded["filename"] = &obe::Events::Scene::Loaded::filename;
        // bindLoaded["id"] = sol::var(obe::Events::Scene::Loaded::id);
    }
};