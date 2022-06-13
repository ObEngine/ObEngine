#pragma once

namespace sol
{
    class state_view;
};
namespace obe::events::network::Bindings
{
    void LoadClassConnected(sol::state_view state);
    void LoadClassDataReceived(sol::state_view state);
    void LoadClassDisconnected(sol::state_view state);
};