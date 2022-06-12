#include <Bindings/obe/Events/Game/Game.hpp>

#include <Engine/Engine.hpp>

#include <Bindings/Config.hpp>

namespace obe::events::game::Bindings
{
    void LoadClassEnd(sol::state_view state)
    {
        sol::table GameNamespace = state["obe"]["events"]["game"].get<sol::table>();
        sol::usertype<obe::events::game::End> bindEnd
            = GameNamespace.new_usertype<obe::events::game::End>(
                "End", sol::call_constructor, sol::default_constructor);
        bindEnd["id"] = sol::var(&obe::events::game::End::id);
    }
    void LoadClassRender(sol::state_view state)
    {
        sol::table GameNamespace = state["obe"]["events"]["game"].get<sol::table>();
        sol::usertype<obe::events::game::Render> bindRender
            = GameNamespace.new_usertype<obe::events::game::Render>(
                "Render", sol::call_constructor, sol::default_constructor);
        bindRender["id"] = sol::var(&obe::events::game::Render::id);
    }
    void LoadClassStart(sol::state_view state)
    {
        sol::table GameNamespace = state["obe"]["events"]["game"].get<sol::table>();
        sol::usertype<obe::events::game::Start> bindStart
            = GameNamespace.new_usertype<obe::events::game::Start>(
                "Start", sol::call_constructor, sol::default_constructor);
        bindStart["id"] = sol::var(&obe::events::game::Start::id);
    }
    void LoadClassUpdate(sol::state_view state)
    {
        sol::table GameNamespace = state["obe"]["events"]["game"].get<sol::table>();
        sol::usertype<obe::events::game::Update> bindUpdate
            = GameNamespace.new_usertype<obe::events::game::Update>(
                "Update", sol::call_constructor, sol::default_constructor);
        bindUpdate["dt"] = &obe::events::game::Update::dt;
        bindUpdate["id"] = sol::var(&obe::events::game::Update::id);
    }
};