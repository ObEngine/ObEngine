#include <Bindings/obe/events/Network/Network.hpp>

#include <Network/NetworkHandler.hpp>

#include <Bindings/Config.hpp>

namespace obe::events::Network::bindings
{
    void load_class_connected(sol::state_view state)
    {
        sol::table Network_namespace = state["obe"]["events"]["Network"].get<sol::table>();
        sol::usertype<obe::events::Network::Connected> bind_connected
            = Network_namespace.new_usertype<obe::events::Network::Connected>(
                "Connected", sol::call_constructor, sol::default_constructor);
        bind_connected["ip"] = &obe::events::Network::Connected::ip;
        bind_connected["id"] = sol::var(&obe::events::Network::Connected::id);
    }
    void load_class_data_received(sol::state_view state)
    {
        sol::table Network_namespace = state["obe"]["events"]["Network"].get<sol::table>();
        sol::usertype<obe::events::Network::DataReceived> bind_data_received
            = Network_namespace.new_usertype<obe::events::Network::DataReceived>(
                "DataReceived", sol::call_constructor, sol::default_constructor);
        bind_data_received["content"] = &obe::events::Network::DataReceived::content;
        bind_data_received["id"] = sol::var(&obe::events::Network::DataReceived::id);
    }
    void load_class_disconnected(sol::state_view state)
    {
        sol::table Network_namespace = state["obe"]["events"]["Network"].get<sol::table>();
        sol::usertype<obe::events::Network::Disconnected> bind_disconnected
            = Network_namespace.new_usertype<obe::events::Network::Disconnected>(
                "Disconnected", sol::call_constructor, sol::default_constructor);
        bind_disconnected["id"] = sol::var(&obe::events::Network::Disconnected::id);
    }
};