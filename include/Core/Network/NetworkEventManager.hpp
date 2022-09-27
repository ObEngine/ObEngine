#pragma once

#include <Event/EventGroup.hpp>
#include <Event/EventManager.hpp>
#include <Event/EventNamespace.hpp>
#include <SFML/Network.hpp>

namespace obe::events
{
    namespace Network
    {
        struct Connected
        {
            static constexpr std::string_view id = "Connected";
            const std::string ip;
            unsigned short port;
            unsigned short remote_port;
            const std::string client_name;
        };

        struct Disconnected
        {
            static constexpr std::string_view id = "Disconnected";
        };

        struct ClientRename
        {
            static constexpr std::string_view id = "ClientRename";
            const std::string client_name;
        };

        struct Message
        {
            static constexpr std::string_view id = "Message";
            const std::string sender;
            const std::string event_group_name;
            const std::string event_name;
            const vili::node data;
        };

        struct EventMessage
        {
            static constexpr std::string_view id = "EventMessage";
            const std::string sender;
            const vili::node data;
        };
    }
}

namespace obe::network
{
    class NetworkClient
    {
    private:
        std::string m_name;
        std::unique_ptr<sf::TcpSocket> m_socket;
    public:
        NetworkClient(const std::string& name, std::unique_ptr<sf::TcpSocket>&& socket);
        void rename(const std::string& name);
        sf::TcpSocket& socket() const;
    };

    class NetworkEventManager
    {
    private:
        sf::TcpListener m_tcp_listener;
        std::unordered_map<std::string, NetworkClient> m_clients;

        event::EventNamespace* m_namespace;
        std::unordered_map<std::string, event::EventGroupPtr> m_event_groups;
        event::EventGroupPtr e_client;

        std::string m_client_name;
        bool m_is_host = false;

        void _accept_new_clients();
        void _receive_messages();
        void _handle_message(const events::Network::Message& message);
        bool _handle_special_message(const events::Network::Message& message);
        [[nodiscard]] static std::string _build_message(const std::string& event_group_name, const std::string& event_name,
            const vili::node& data, bool check_for_forbidden_groups = true);
    public:
        NetworkEventManager(event::EventManager& manager, const std::string& event_namespace_name);
        void rename_client(const std::string& current_name, const std::string& new_name);
        void host(unsigned short port);
        void connect(const std::string& address, unsigned short port);

        void emit(const std::string& event_group_name, const std::string& event_name, const vili::node& data);
        void emit(const std::string& recipient, const std::string& event_group_name,
            const std::string& event_name, const vili::node& data) const;
        void handle_events();
    };
} // namespace obe::network
