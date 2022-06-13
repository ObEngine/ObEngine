#include <Bindings/obe/Events/Network/Network.hpp>

#include <Network/NetworkHandler.hpp>

#include <Bindings/Config.hpp>

namespace obe::events::network::Bindings
{
    void LoadClassConnected(sol::state_view state)
    {
        sol::table NetworkNamespace = state["obe"]["events"]["network"].get<sol::table>();
        sol::usertype<obe::events::network::Connected> bindConnected
            = NetworkNamespace.new_usertype<obe::events::network::Connected>(
                "Connected", sol::call_constructor, sol::default_constructor);
        bindConnected["ip"] = &obe::events::network::Connected::ip;
        bindConnected["id"] = sol::var(&obe::events::network::Connected::id);
    }
    void LoadClassDataReceived(sol::state_view state)
    {
        sol::table NetworkNamespace = state["obe"]["events"]["network"].get<sol::table>();
        sol::usertype<obe::events::network::DataReceived> bindDataReceived
            = NetworkNamespace.new_usertype<obe::events::network::DataReceived>(
                "DataReceived", sol::call_constructor, sol::default_constructor);
        bindDataReceived["content"] = &obe::events::network::DataReceived::content;
        bindDataReceived["id"] = sol::var(&obe::events::network::DataReceived::id);
    }
    void LoadClassDisconnected(sol::state_view state)
    {
        sol::table NetworkNamespace = state["obe"]["events"]["network"].get<sol::table>();
        sol::usertype<obe::events::network::Disconnected> bindDisconnected
            = NetworkNamespace.new_usertype<obe::events::network::Disconnected>(
                "Disconnected", sol::call_constructor, sol::default_constructor);
        bindDisconnected["id"] = sol::var(&obe::events::network::Disconnected::id);
    }
};