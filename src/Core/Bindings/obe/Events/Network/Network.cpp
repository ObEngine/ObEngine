#include <Bindings/obe/Events/Network/Network.hpp>

#include <Network/NetworkHandler.hpp>

#include <Bindings/Config.hpp>

namespace obe::events::Network::Bindings
{
    void LoadClassConnected(sol::state_view state)
    {
        sol::table NetworkNamespace = state["obe"]["events"]["Network"].get<sol::table>();
        sol::usertype<obe::events::Network::Connected> bindConnected
            = NetworkNamespace.new_usertype<obe::events::Network::Connected>(
                "Connected", sol::call_constructor, sol::default_constructor);
        bindConnected["ip"] = &obe::events::Network::Connected::ip;
        bindConnected["id"] = sol::var(&obe::events::Network::Connected::id);
    }
    void LoadClassDataReceived(sol::state_view state)
    {
        sol::table NetworkNamespace = state["obe"]["events"]["Network"].get<sol::table>();
        sol::usertype<obe::events::Network::DataReceived> bindDataReceived
            = NetworkNamespace.new_usertype<obe::events::Network::DataReceived>(
                "DataReceived", sol::call_constructor, sol::default_constructor);
        bindDataReceived["content"] = &obe::events::Network::DataReceived::content;
        bindDataReceived["id"] = sol::var(&obe::events::Network::DataReceived::id);
    }
    void LoadClassDisconnected(sol::state_view state)
    {
        sol::table NetworkNamespace = state["obe"]["events"]["Network"].get<sol::table>();
        sol::usertype<obe::events::Network::Disconnected> bindDisconnected
            = NetworkNamespace.new_usertype<obe::events::Network::Disconnected>(
                "Disconnected", sol::call_constructor, sol::default_constructor);
        bindDisconnected["id"] = sol::var(&obe::events::Network::Disconnected::id);
    }
};