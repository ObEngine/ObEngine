#pragma once

namespace sol
{
    class state_view;
};
namespace obe::Events::Game::Bindings
{
    void LoadClassEnd(sol::state_view state);
    void LoadClassRender(sol::state_view state);
    void LoadClassStart(sol::state_view state);
    void LoadClassUpdate(sol::state_view state);
};
