#pragma once

namespace sol
{
    class state_view;
};
namespace obe::events::Game::bindings
{
    void load_class_end(sol::state_view state);
    void load_class_render(sol::state_view state);
    void load_class_start(sol::state_view state);
    void load_class_update(sol::state_view state);
}; // namespace obe::events::Game::bindings