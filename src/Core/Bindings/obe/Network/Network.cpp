#include <Bindings/obe/Network/Network.hpp>

#include <Network/NetworkHandler.hpp>
#include <Network/TcpServer.hpp>
#include <Network/TcpSocket.hpp>

#include <Bindings/Config.hpp>

namespace obe::network::Bindings
{
    void LoadClassLuaPacket(sol::state_view state)
    {
        sol::table NetworkNamespace = state["obe"]["network"].get<sol::table>();
        sol::usertype<obe::network::LuaPacket> bindLuaPacket
            = NetworkNamespace.new_usertype<obe::network::LuaPacket>(
                "LuaPacket", sol::call_constructor, sol::default_constructor);
    }
    void LoadClassNetworkHandler(sol::state_view state)
    {
        sol::table NetworkNamespace = state["obe"]["network"].get<sol::table>();
        sol::usertype<obe::network::NetworkHandler> bindNetworkHandler
            = NetworkNamespace.new_usertype<obe::network::NetworkHandler>("NetworkHandler",
                sol::call_constructor,
                sol::constructors<obe::network::NetworkHandler(obe::event::EventNamespace&)>());
        bindNetworkHandler["handle_events"] = &obe::network::NetworkHandler::handle_events;
    }
    void LoadClassTcpServer(sol::state_view state)
    {
        sol::table NetworkNamespace = state["obe"]["network"].get<sol::table>();
        sol::usertype<obe::network::TcpServer> bindTcpServer = NetworkNamespace.new_usertype<
            obe::network::TcpServer>("TcpServer", sol::call_constructor,
            sol::constructors<obe::network::TcpServer(obe::event::EventNamespace&, unsigned short)>());
        bindTcpServer["update"] = &obe::network::TcpServer::update;
        bindTcpServer["set_buffer_size"] = &obe::network::TcpServer::set_buffer_size;
    }
    void LoadClassTcpSocket(sol::state_view state)
    {
        sol::table NetworkNamespace = state["obe"]["network"].get<sol::table>();
        sol::usertype<obe::network::TcpSocket> bindTcpSocket
            = NetworkNamespace.new_usertype<obe::network::TcpSocket>(
                "TcpSocket", sol::call_constructor, sol::default_constructor);
    }
};