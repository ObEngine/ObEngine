#include <Bindings/obe/Events/Network/Network.hpp>

#include <Network/NetworkHandler.hpp>

#include <Bindings/Config.hpp>

namespace obe::Events::Network::Bindings
{
    void LoadClassConnected(sol::state_view state)
    {
        sol::table NetworkNamespace = state["obe"]["Events"]["Network"].get<sol::table>();
        sol::usertype<obe::Events::Network::Connected> bindConnected
            = NetworkNamespace.new_usertype<obe::Events::Network::Connected>("Connected");
        bindConnected["ip"] = &obe::Events::Network::Connected::ip;
        bindConnected["id"] = sol::var(&obe::Events::Network::Connected::id);
    }
    void LoadClassDataReceived(sol::state_view state)
    {
        sol::table NetworkNamespace = state["obe"]["Events"]["Network"].get<sol::table>();
        sol::usertype<obe::Events::Network::DataReceived> bindDataReceived
            = NetworkNamespace.new_usertype<obe::Events::Network::DataReceived>(
                "DataReceived");
        bindDataReceived["content"] = &obe::Events::Network::DataReceived::content;
        bindDataReceived["id"] = sol::var(&obe::Events::Network::DataReceived::id);
    }
    void LoadClassDisconnected(sol::state_view state)
    {
        sol::table NetworkNamespace = state["obe"]["Events"]["Network"].get<sol::table>();
        sol::usertype<obe::Events::Network::Disconnected> bindDisconnected
            = NetworkNamespace.new_usertype<obe::Events::Network::Disconnected>(
                "Disconnected");
        bindDisconnected["id"] = sol::var(&obe::Events::Network::Disconnected::id);
    }
};