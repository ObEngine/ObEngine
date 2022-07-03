#pragma once

namespace sol
{
    class state_view;
};
namespace obe::network::bindings
{
    void load_class_lua_packet(sol::state_view state);
    void load_class_network_handler(sol::state_view state);
    void load_class_tcp_server(sol::state_view state);
    void load_class_tcp_socket(sol::state_view state);
};