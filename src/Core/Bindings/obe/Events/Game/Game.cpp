#include <Bindings/obe/events/Game/Game.hpp>

#include <Engine/Engine.hpp>

#include <Bindings/Config.hpp>

namespace obe::events::Game::bindings
{
    void load_class_end(sol::state_view state)
    {
        sol::table Game_namespace = state["obe"]["events"]["Game"].get<sol::table>();
        sol::usertype<obe::events::Game::End> bind_end
            = Game_namespace.new_usertype<obe::events::Game::End>(
                "End", sol::call_constructor, sol::default_constructor);
        bind_end["id"] = sol::var(&obe::events::Game::End::id);
    }
    void load_class_render(sol::state_view state)
    {
        sol::table Game_namespace = state["obe"]["events"]["Game"].get<sol::table>();
        sol::usertype<obe::events::Game::Render> bind_render
            = Game_namespace.new_usertype<obe::events::Game::Render>(
                "Render", sol::call_constructor, sol::default_constructor);
        bind_render["id"] = sol::var(&obe::events::Game::Render::id);
    }
    void load_class_start(sol::state_view state)
    {
        sol::table Game_namespace = state["obe"]["events"]["Game"].get<sol::table>();
        sol::usertype<obe::events::Game::Start> bind_start
            = Game_namespace.new_usertype<obe::events::Game::Start>(
                "Start", sol::call_constructor, sol::default_constructor);
        bind_start["id"] = sol::var(&obe::events::Game::Start::id);
    }
    void load_class_update(sol::state_view state)
    {
        sol::table Game_namespace = state["obe"]["events"]["Game"].get<sol::table>();
        sol::usertype<obe::events::Game::Update> bind_update
            = Game_namespace.new_usertype<obe::events::Game::Update>(
                "Update", sol::call_constructor, sol::default_constructor);
        bind_update["dt"] = &obe::events::Game::Update::dt;
        bind_update["id"] = sol::var(&obe::events::Game::Update::id);
    }
};