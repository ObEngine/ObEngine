#pragma once

#include <brynet/net/EventLoop.hpp>
#include <brynet/net/TcpConnection.hpp>
#include <brynet/net/TcpService.hpp>
#include <brynet/net/wrapper/ServiceBuilder.hpp>

#include <Event/EventGroup.hpp>
#include <Event/EventManager.hpp>
#include <Event/EventNamespace.hpp>

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
            const std::string client_name;
        };

        struct ClientRename
        {
            static constexpr std::string_view id = "ClientRename";
            const std::string client_name;
        };

        struct Message
        {
            static constexpr std::string_view id = "Message";
            const std::string client_name;
            const std::string event_group_name;
            const std::string event_name;
            const vili::node data;
        };
    }
}

namespace obe::network
{
    class NetworkClient
    {
    private:
        brynet::net::TcpConnection::Ptr m_socket;
        std::string m_name;

    public:
        NetworkClient(const std::string& name, brynet::net::TcpConnection::Ptr socket);
        void rename(const std::string& name);
        [[nodiscard]] std::string name() const;
        [[nodiscard]] std::string host() const;
        brynet::net::TcpConnection::Ptr socket() const;
    };

    class NetworkEventManager
    {
    private:
        brynet::net::EventLoop::Ptr m_event_loop;
        brynet::net::ITcpService::Ptr m_net_service;
        brynet::net::wrapper::ListenerBuilder m_listener;

        std::unordered_map<std::string, NetworkClient> m_clients;

        event::EventNamespace* m_namespace;
        std::unordered_map<std::string, event::EventGroupPtr> m_event_groups;
        event::EventGroupPtr e_client;

        std::string m_client_name;
        bool m_is_host = false;

        vili::node m_spec;

        void _build_client_listener(unsigned short port);
        void _build_events_from_spec();
        void _handle_new_connection(const brynet::net::TcpConnection::Ptr& session);

        void _receive_messages();
        void _handle_message(const events::Network::Message& message);
        bool _handle_special_message(const events::Network::Message& message);
        [[nodiscard]] static std::string _build_message(const std::string& event_group_name,
            const std::string& event_name, const vili::node& data,
            bool check_for_forbidden_groups = true);

    public:
        NetworkEventManager(event::EventNamespace::Ptr event_namespace, const vili::node& spec);

        void rename_client(const std::string& current_name, const std::string& new_name);
        void host(unsigned short port);
        void connect(const std::string& host, unsigned short port);

        void emit(const std::string& event_group_name, const std::string& event_name,
            const vili::node& data);
        void emit(const std::string& recipient, const std::string& event_group_name,
            const std::string& event_name, const vili::node& data) const;
        void handle_events();

        [[nodiscard]] event::EventNamespaceView get_event_namespace() const;
        [[nodiscard]] std::string get_client_name() const;
    };
} // namespace obe::network
