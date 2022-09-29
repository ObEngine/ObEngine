#include <Bindings/obe/network/Network.hpp>

#include <Network/NetworkEventManager.hpp>
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
    void load_class_network_client(sol::state_view state)
    {
        sol::table network_namespace = state["obe"]["network"].get<sol::table>();
        sol::usertype<obe::network::NetworkClient> bind_network_client
            = network_namespace.new_usertype<obe::network::NetworkClient>("NetworkClient");
        bind_network_client["rename"] = &obe::network::NetworkClient::rename;
        bind_network_client["socket"] = &obe::network::NetworkClient::socket;
    }
    void load_class_network_event_manager(sol::state_view state)
    {
        sol::table network_namespace = state["obe"]["network"].get<sol::table>();
        sol::usertype<obe::network::NetworkEventManager> bind_network_event_manager
            = network_namespace.new_usertype<obe::network::NetworkEventManager>(
                "NetworkEventManager", sol::call_constructor,
                sol::constructors<obe::network::NetworkEventManager(
                    obe::event::EventManager&, const std::string&, const vili::node&)>());
        bind_network_event_manager["rename_client"]
            = &obe::network::NetworkEventManager::rename_client;
        bind_network_event_manager["host"] = &obe::network::NetworkEventManager::host;
        bind_network_event_manager["get_event_namespace"]
            = &obe::network::NetworkEventManager::get_event_namespace;
        bind_network_event_manager["connect"] = &obe::network::NetworkEventManager::connect;
        bind_network_event_manager["emit"] = sol::overload(
            static_cast<void (obe::network::NetworkEventManager::*)(const std::string&,
                const std::string&, const vili::node&)>(&obe::network::NetworkEventManager::emit),
            static_cast<void (obe::network::NetworkEventManager::*)(const std::string&,
                const std::string&, const std::string&, const vili::node&) const>(
                &obe::network::NetworkEventManager::emit));
        bind_network_event_manager["handle_events"]
            = &obe::network::NetworkEventManager::handle_events;
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