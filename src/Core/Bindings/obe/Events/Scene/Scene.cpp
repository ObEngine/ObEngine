#include <Bindings/obe/events/scene/Scene.hpp>

#include <Scene/Scene.hpp>

#include <Bindings/Config.hpp>

namespace obe::events::scene::bindings
{
    void load_class_loaded(sol::state_view state)
    {
        sol::table scene_namespace = state["obe"]["events"]["scene"].get<sol::table>();
        sol::usertype<obe::events::Scene::Loaded> bind_loaded
            = scene_namespace.new_usertype<obe::events::Scene::Loaded>(
                "Loaded", sol::call_constructor, sol::default_constructor);
        bind_loaded["filename"] = &obe::events::Scene::Loaded::filename;
        bind_loaded["id"] = sol::var(&obe::events::Scene::Loaded::id);
    }
};