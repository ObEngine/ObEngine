#include <Bindings/obe/network/Network.hpp>

#include <Network/Downloader.hpp>
#include <Network/NetworkEventManager.hpp>

#include <Bindings/Config.hpp>

namespace obe::network::bindings
{
    void load_class_network_client(sol::state_view state)
    {
        sol::table network_namespace = state["obe"]["network"].get<sol::table>();
        sol::usertype<obe::network::NetworkClient> bind_network_client
            = network_namespace.new_usertype<obe::network::NetworkClient>("NetworkClient");
        bind_network_client["rename"] = &obe::network::NetworkClient::rename;
        bind_network_client["name"] = &obe::network::NetworkClient::name;
        bind_network_client["host"] = &obe::network::NetworkClient::host;
        bind_network_client["socket"] = &obe::network::NetworkClient::socket;
    }
    void load_class_network_event_manager(sol::state_view state)
    {
        sol::table network_namespace = state["obe"]["network"].get<sol::table>();
        sol::usertype<obe::network::NetworkEventManager> bind_network_event_manager
            = network_namespace.new_usertype<obe::network::NetworkEventManager>(
                "NetworkEventManager", sol::call_constructor,
                sol::constructors<obe::network::NetworkEventManager(
                    obe::event::EventNamespace::Ptr, const vili::node&)>());
        bind_network_event_manager["rename_client"]
            = &obe::network::NetworkEventManager::rename_client;
        bind_network_event_manager["host"] = &obe::network::NetworkEventManager::host;
        bind_network_event_manager["connect"] = &obe::network::NetworkEventManager::connect;
        bind_network_event_manager["emit"] = sol::overload(
            static_cast<void (obe::network::NetworkEventManager::*)(const std::string&,
                const std::string&, const vili::node&)>(&obe::network::NetworkEventManager::emit),
            static_cast<void (obe::network::NetworkEventManager::*)(const std::string&,
                const std::string&, const std::string&, const vili::node&) const>(
                &obe::network::NetworkEventManager::emit));
        bind_network_event_manager["handle_events"]
            = &obe::network::NetworkEventManager::handle_events;
        bind_network_event_manager["get_event_namespace"]
            = &obe::network::NetworkEventManager::get_event_namespace;
        bind_network_event_manager["get_client_name"]
            = &obe::network::NetworkEventManager::get_client_name;
    }
    void load_function_download_file(sol::state_view state)
    {
        sol::table network_namespace = state["obe"]["network"].get<sol::table>();
        network_namespace.set_function("download_file", &obe::network::download_file);
    }
};