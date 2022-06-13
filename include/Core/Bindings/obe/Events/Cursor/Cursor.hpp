#pragma once

namespace sol
{
    class state_view;
};
namespace obe::events::cursor::Bindings
{
    void LoadClassHold(sol::state_view state);
    void LoadClassMove(sol::state_view state);
    void LoadClassPress(sol::state_view state);
    void LoadClassRelease(sol::state_view state);
};