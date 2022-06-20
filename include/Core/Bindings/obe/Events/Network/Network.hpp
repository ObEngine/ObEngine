#pragma once

namespace sol
{
    class state_view;
};
namespace obe::events::network::bindings
{
    void load_class_connected(sol::state_view state);
    void load_class_data_received(sol::state_view state);
    void load_class_disconnected(sol::state_view state);
};