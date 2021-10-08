#include <Bindings/obe/Events/Game/Game.hpp>

#include <Engine/Engine.hpp>

#include <Bindings/Config.hpp>

namespace obe::Events::Game::Bindings
{
    void LoadClassEnd(sol::state_view state)
    {
        sol::table GameNamespace = state["obe"]["Events"]["Game"].get<sol::table>();
        sol::usertype<obe::Events::Game::End> bindEnd
            = GameNamespace.new_usertype<obe::Events::Game::End>(
                "End", sol::call_constructor, sol::default_constructor);
        bindEnd["id"] = sol::var(&obe::Events::Game::End::id);
    }
    void LoadClassRender(sol::state_view state)
    {
        sol::table GameNamespace = state["obe"]["Events"]["Game"].get<sol::table>();
        sol::usertype<obe::Events::Game::Render> bindRender
            = GameNamespace.new_usertype<obe::Events::Game::Render>(
                "Render", sol::call_constructor, sol::default_constructor);
        bindRender["id"] = sol::var(&obe::Events::Game::Render::id);
    }
    void LoadClassStart(sol::state_view state)
    {
        sol::table GameNamespace = state["obe"]["Events"]["Game"].get<sol::table>();
        sol::usertype<obe::Events::Game::Start> bindStart
            = GameNamespace.new_usertype<obe::Events::Game::Start>(
                "Start", sol::call_constructor, sol::default_constructor);
        bindStart["id"] = sol::var(&obe::Events::Game::Start::id);
    }
    void LoadClassUpdate(sol::state_view state)
    {
        sol::table GameNamespace = state["obe"]["Events"]["Game"].get<sol::table>();
        sol::usertype<obe::Events::Game::Update> bindUpdate
            = GameNamespace.new_usertype<obe::Events::Game::Update>(
                "Update", sol::call_constructor, sol::default_constructor);
        bindUpdate["dt"] = &obe::Events::Game::Update::dt;
        bindUpdate["id"] = sol::var(&obe::Events::Game::Update::id);
    }
};
