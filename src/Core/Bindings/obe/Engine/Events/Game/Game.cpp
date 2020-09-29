#include <Bindings/obe/Engine/Events/Game/Game.hpp>

#include <Engine/Engine.hpp>

#include <Bindings/Config.hpp>

namespace obe::Engine::Events::Game::Bindings
{
    void LoadClassEnd(sol::state_view state)
    {
        sol::table GameNamespace
            = state["obe"]["Engine"]["Events"]["Game"].get<sol::table>();
        sol::usertype<obe::Engine::Events::Game::End> bindEnd
            = GameNamespace.new_usertype<obe::Engine::Events::Game::End>(
                "End", sol::call_constructor, sol::default_constructor);
    }
    void LoadClassRender(sol::state_view state)
    {
        sol::table GameNamespace
            = state["obe"]["Engine"]["Events"]["Game"].get<sol::table>();
        sol::usertype<obe::Engine::Events::Game::Render> bindRender
            = GameNamespace.new_usertype<obe::Engine::Events::Game::Render>(
                "Render", sol::call_constructor, sol::default_constructor);
    }
    void LoadClassStart(sol::state_view state)
    {
        sol::table GameNamespace
            = state["obe"]["Engine"]["Events"]["Game"].get<sol::table>();
        sol::usertype<obe::Engine::Events::Game::Start> bindStart
            = GameNamespace.new_usertype<obe::Engine::Events::Game::Start>(
                "Start", sol::call_constructor, sol::default_constructor);
    }
    void LoadClassUpdate(sol::state_view state)
    {
        sol::table GameNamespace
            = state["obe"]["Engine"]["Events"]["Game"].get<sol::table>();
        sol::usertype<obe::Engine::Events::Game::Update> bindUpdate
            = GameNamespace.new_usertype<obe::Engine::Events::Game::Update>(
                "Update", sol::call_constructor, sol::default_constructor);
        bindUpdate["dt"] = &obe::Engine::Events::Game::Update::dt;
    }
};