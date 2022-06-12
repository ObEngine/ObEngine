#include <Bindings/obe/Events/Scene/Scene.hpp>

#include <Scene/Scene.hpp>

#include <Bindings/Config.hpp>

namespace obe::events::Scene::Bindings
{
    void LoadClassLoaded(sol::state_view state)
    {
        sol::table SceneNamespace = state["obe"]["events"]["Scene"].get<sol::table>();
        sol::usertype<obe::events::Scene::Loaded> bindLoaded
            = SceneNamespace.new_usertype<obe::events::Scene::Loaded>(
                "Loaded", sol::call_constructor, sol::default_constructor);
        bindLoaded["filename"] = &obe::events::Scene::Loaded::filename;
        bindLoaded["id"] = sol::var(&obe::events::Scene::Loaded::id);
    }
};