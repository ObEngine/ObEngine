#include <Bindings/obe/Events/Scene/Scene.hpp>

#include <Scene/Scene.hpp>

#include <Bindings/Config.hpp>

namespace obe::events::scene::Bindings
{
    void LoadClassLoaded(sol::state_view state)
    {
        sol::table SceneNamespace = state["obe"]["events"]["scene"].get<sol::table>();
        sol::usertype<obe::events::scene::Loaded> bindLoaded
            = SceneNamespace.new_usertype<obe::events::scene::Loaded>(
                "Loaded", sol::call_constructor, sol::default_constructor);
        bindLoaded["filename"] = &obe::events::scene::Loaded::filename;
        bindLoaded["id"] = sol::var(&obe::events::scene::Loaded::id);
    }
};