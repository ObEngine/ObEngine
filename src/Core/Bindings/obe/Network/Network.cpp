#include <Bindings/obe/Network/Network.hpp>

#include <Network/NetworkHandler.hpp>
#include <Network/TcpServer.hpp>
#include <Network/TcpSocket.hpp>

#include <Bindings/Config.hpp>

namespace obe::Network::Bindings
{
    void LoadClassLuaPacket(sol::state_view state)
    {
        sol::table NetworkNamespace = state["obe"]["Network"].get<sol::table>();
        sol::usertype<obe::Network::LuaPacket> bindLuaPacket
            = NetworkNamespace.new_usertype<obe::Network::LuaPacket>(
                "LuaPacket", sol::call_constructor, sol::default_constructor);
    }
    void LoadClassNetworkHandler(sol::state_view state)
    {
        sol::table NetworkNamespace = state["obe"]["Network"].get<sol::table>();
        sol::usertype<obe::Network::NetworkHandler> bindNetworkHandler
            = NetworkNamespace.new_usertype<obe::Network::NetworkHandler>(
                "NetworkHandler", sol::call_constructor,
                sol::constructors<obe::Network::NetworkHandler(
                    obe::Triggers::TriggerManager&)>());
        bindNetworkHandler["handleTriggers"]
            = &obe::Network::NetworkHandler::handleTriggers;
    }
    void LoadClassTcpServer(sol::state_view state)
    {
        sol::table NetworkNamespace = state["obe"]["Network"].get<sol::table>();
        sol::usertype<obe::Network::TcpServer> bindTcpServer
            = NetworkNamespace.new_usertype<obe::Network::TcpServer>("TcpServer",
                sol::call_constructor,
                sol::constructors<obe::Network::TcpServer(
                                      obe::Triggers::TriggerManager&, unsigned short),
                    obe::Network::TcpServer(
                        obe::Triggers::TriggerManager&, unsigned short, std::string),
                    obe::Network::TcpServer(obe::Triggers::TriggerManager&,
                        unsigned short, std::string, std::string)>());
        bindTcpServer["update"] = &obe::Network::TcpServer::update;
        bindTcpServer["setBufferSize"] = &obe::Network::TcpServer::setBufferSize;
    }
    void LoadClassTcpSocket(sol::state_view state)
    {
        sol::table NetworkNamespace = state["obe"]["Network"].get<sol::table>();
        sol::usertype<obe::Network::TcpSocket> bindTcpSocket
            = NetworkNamespace.new_usertype<obe::Network::TcpSocket>(
                "TcpSocket", sol::call_constructor, sol::default_constructor);
    }
};