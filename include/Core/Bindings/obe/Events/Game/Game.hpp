#pragma once

namespace sol
{
    class state_view;
};
namespace obe::events::game::Bindings
{
    void LoadClassEnd(sol::state_view state);
    void LoadClassRender(sol::state_view state);
    void LoadClassStart(sol::state_view state);
    void LoadClassUpdate(sol::state_view state);
};