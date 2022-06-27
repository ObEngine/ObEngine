#include <Bindings/obe/network/Network.hpp>

#include <Network/NetworkHandler.hpp>
#include <Network/TcpServer.hpp>
#include <Network/TcpSocket.hpp>

#include <Bindings/Config.hpp>

namespace obe::network::bindings
{
    void load_class_lua_packet(sol::state_view state)
    {
        sol::table network_namespace = state["obe"]["network"].get<sol::table>();
        sol::usertype<obe::network::LuaPacket> bind_lua_packet
            = network_namespace.new_usertype<obe::network::LuaPacket>(
                "LuaPacket", sol::call_constructor, sol::default_constructor);
    }
    void load_class_network_handler(sol::state_view state)
    {
        sol::table network_namespace = state["obe"]["network"].get<sol::table>();
        sol::usertype<obe::network::NetworkHandler> bind_network_handler
            = network_namespace.new_usertype<obe::network::NetworkHandler>("NetworkHandler",
                sol::call_constructor,
                sol::constructors<obe::network::NetworkHandler(obe::event::EventNamespace&)>());
        bind_network_handler["handle_events"] = &obe::network::NetworkHandler::handle_events;
    }
    void load_class_tcp_server(sol::state_view state)
    {
        sol::table network_namespace = state["obe"]["network"].get<sol::table>();
        sol::usertype<obe::network::TcpServer> bind_tcp_server
            = network_namespace.new_usertype<obe::network::TcpServer>("TcpServer",
                sol::call_constructor,
                sol::constructors<obe::network::TcpServer(
                    obe::event::EventNamespace&, unsigned short)>());
        bind_tcp_server["update"] = &obe::network::TcpServer::update;
        bind_tcp_server["set_buffer_size"] = &obe::network::TcpServer::set_buffer_size;
    }
    void load_class_tcp_socket(sol::state_view state)
    {
        sol::table network_namespace = state["obe"]["network"].get<sol::table>();
        sol::usertype<obe::network::TcpSocket> bind_tcp_socket
            = network_namespace.new_usertype<obe::network::TcpSocket>(
                "TcpSocket", sol::call_constructor, sol::default_constructor);
    }
};