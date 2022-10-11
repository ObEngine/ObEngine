#include <Bindings/obe/events/Network/Network.hpp>

#include <Network/NetworkEventManager.hpp>

#include <Bindings/Config.hpp>

namespace obe::events::Network::bindings
{
    void load_class_client_rename(sol::state_view state)
    {
        sol::table Network_namespace = state["obe"]["events"]["Network"].get<sol::table>();
        sol::usertype<obe::events::Network::ClientRename> bind_client_rename
            = Network_namespace.new_usertype<obe::events::Network::ClientRename>(
                "ClientRename", sol::call_constructor, sol::default_constructor);
        bind_client_rename["client_name"] = &obe::events::Network::ClientRename::client_name;
        bind_client_rename["id"] = sol::var(&obe::events::Network::ClientRename::id);
    }
    void load_class_connected(sol::state_view state)
    {
        sol::table Network_namespace = state["obe"]["events"]["Network"].get<sol::table>();
        sol::usertype<obe::events::Network::Connected> bind_connected
            = Network_namespace.new_usertype<obe::events::Network::Connected>(
                "Connected", sol::call_constructor, sol::default_constructor);
        bind_connected["ip"] = &obe::events::Network::Connected::ip;
        bind_connected["port"] = &obe::events::Network::Connected::port;
        bind_connected["remote_port"] = &obe::events::Network::Connected::remote_port;
        bind_connected["client_name"] = &obe::events::Network::Connected::client_name;
        bind_connected["id"] = sol::var(&obe::events::Network::Connected::id);
    }
    void load_class_disconnected(sol::state_view state)
    {
        sol::table Network_namespace = state["obe"]["events"]["Network"].get<sol::table>();
        sol::usertype<obe::events::Network::Disconnected> bind_disconnected
            = Network_namespace.new_usertype<obe::events::Network::Disconnected>(
                "Disconnected", sol::call_constructor, sol::default_constructor);
        bind_disconnected["id"] = sol::var(&obe::events::Network::Disconnected::id);
    }
    void load_class_message(sol::state_view state)
    {
        sol::table Network_namespace = state["obe"]["events"]["Network"].get<sol::table>();
        sol::usertype<obe::events::Network::Message> bind_message
            = Network_namespace.new_usertype<obe::events::Network::Message>(
                "Message", sol::call_constructor, sol::default_constructor);
        bind_message["client_name"] = &obe::events::Network::Message::client_name;
        bind_message["event_group_name"] = &obe::events::Network::Message::event_group_name;
        bind_message["event_name"] = &obe::events::Network::Message::event_name;
        bind_message["data"] = &obe::events::Network::Message::data;
        bind_message["id"] = sol::var(&obe::events::Network::Message::id);
    }
};