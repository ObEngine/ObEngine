#pragma once

namespace sol
{
    class state_view;
};
namespace obe::network::bindings
{
    void load_class_network_client(sol::state_view state);
    void load_class_network_event_manager(sol::state_view state);
    void load_function_download_file(sol::state_view state);
};