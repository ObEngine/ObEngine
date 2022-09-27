#include <unordered_set>

#include <fmt/core.h>
#include <vili/parser.hpp>

#include <Network/Exceptions.hpp>
#include <Network/NetworkEventManager.hpp>

namespace obe::network
{
    std::unordered_set<std::string_view> FORBIDDEN_NETWORK_EVENT_GROUPS = { "Client" };

    NetworkClient::NetworkClient(const std::string& name, std::unique_ptr<sf::TcpSocket>&& socket)
        : m_name(name)
        , m_socket(std::move(socket))
    {
    }

    void NetworkClient::rename(const std::string& name)
    {
        m_name = name;
    }

    sf::TcpSocket& NetworkClient::socket() const
    {
        return *m_socket;
    }

    void NetworkEventManager::_accept_new_clients()
    {
        std::unique_ptr<sf::TcpSocket> new_socket = std::make_unique<sf::TcpSocket>();

        const sf::Socket::Status status = m_tcp_listener.accept(*new_socket);
        if (status == sf::Socket::Status::Done)
        {
            new_socket->setBlocking(false);
            const std::string random_client_name
                = utils::string::get_random_key(utils::string::Alphabet, 16);
            // Trigger "Connected" event
            const auto evt = events::Network::Connected {
                new_socket->getRemoteAddress().toString(),
                new_socket->getLocalPort(),
                new_socket->getRemotePort()
            };
            e_client->trigger(evt);
            // Trigger "ClientRename" event
            const std::string client_rename_msg = _build_message(
                "Client", "ClientRename", vili::object { { "name", random_client_name } });
            new_socket->send(client_rename_msg.data(), client_rename_msg.size());
            m_clients.emplace(random_client_name, NetworkClient(random_client_name, std::move(new_socket)));
        }
    }

    void NetworkEventManager::_receive_messages()
    {
        for (auto& [client_name, client] : m_clients)
        {
            std::array<uint8_t, 2048> received_bytes = {};
            size_t real_size = 0;
            const sf::Socket::Status status
                = client.socket().receive(received_bytes.data(), received_bytes.size(), real_size);
            if (status == sf::Socket::Done)
            {
                const std::string content
                    = std::string(received_bytes.begin(), received_bytes.begin() + real_size);

                vili::node message;
                try
                {
                    message = vili::parser::from_string(content);
                }
                catch (const std::exception& e)
                {
                    throw exceptions::InvalidNetworkMessage(content, EXC_INFO).nest(e);
                }

                std::string event_group_name;
                std::string event_name;
                vili::node message_data = vili::object {};
                if (message.contains("g"))
                {
                    event_group_name = message.at("g");
                }
                if (message.contains("e"))
                {
                    event_name = message.at("e");
                }
                if (message.contains("d"))
                {
                    message_data = message.at("d");
                }
                events::Network::Message message_event
                    = events::Network::Message { client.socket().getRemoteAddress().toString(),
                          event_group_name, event_name, message_data };
                _handle_message(message_event);
            }
            else if (status == sf::Socket::Disconnected)
            {
                e_client->trigger(events::Network::Disconnected {});
            }
        }
    }

    void NetworkEventManager::_handle_message(const events::Network::Message& message)
    {
        if (message.event_group_name.empty() || message.event_name.empty())
        {
            throw exceptions::NetworkMessageMissingEventFields(message.data.dump(true), EXC_INFO);
        }
        if (m_is_host && FORBIDDEN_NETWORK_EVENT_GROUPS.contains(message.event_group_name))
        {
            return;
        }
        if (_handle_special_message(message))
        {
            return;
        }
        e_client->trigger(message);
        if (!m_namespace->does_group_exists(message.event_group_name))
        {
            m_event_groups.emplace(
                message.event_group_name, m_namespace->create_group(message.event_group_name));
        }
        const event::EventGroupPtr event_group = m_event_groups.at(message.event_group_name);
        if (!event_group->contains(message.event_name))
        {
            event_group->add<events::Network::EventMessage>(message.event_name);
        }
        event_group->trigger(
            message.event_name, events::Network::EventMessage { message.sender, message.data });
    }

    bool NetworkEventManager::_handle_special_message(const events::Network::Message& message)
    {
        if (message.event_group_name == "Client")
        {
            if (message.event_name == "ClientRename")
            {
                if (message.data.contains("name"))
                {
                    m_client_name = message.data.at("name");
                }
                return true;
            }
        }
        return false;
    }

    std::string NetworkEventManager::_build_message(const std::string& event_group_name,
        const std::string& event_name, const vili::node& data, bool check_for_forbidden_groups)
    {
        if (check_for_forbidden_groups && FORBIDDEN_NETWORK_EVENT_GROUPS.contains(event_group_name))
        {
            throw exceptions::ForbiddenEventGroup(event_group_name, EXC_INFO);
        }
        const vili::node message
            = vili::object { { "g", event_group_name }, { "e", event_name }, { "d", data } };
        return message.dump(true);
    }

    NetworkEventManager::NetworkEventManager(event::EventManager& manager,
        const std::string& event_namespace_name)
    {
        m_namespace = &manager.create_namespace(event_namespace_name);
        e_client = m_namespace->create_group("Client");
        e_client->add<events::Network::Connected>();
        e_client->add<events::Network::Disconnected>();
        e_client->add<events::Network::Message>();
        m_tcp_listener.setBlocking(false);
    }

    void NetworkEventManager::rename_client(const std::string& current_name,
        const std::string& new_name)
    {
        if (!m_clients.contains(current_name))
        {
            throw exceptions::ClientNotFound(current_name, EXC_INFO);
        }
        auto client = m_clients.extract(current_name);
        client.key() = new_name;
        client.mapped().rename(new_name);
        const std::string client_rename_msg = _build_message(
            "Client", "ClientRename", vili::object { { "name", new_name } });
        client.mapped().socket().send(client_rename_msg.data(), client_rename_msg.size());
        m_clients.insert(std::move(client));
    }

    void NetworkEventManager::host(const unsigned short port)
    {
        if (!m_client_name.empty())
        {
            throw exceptions::AlreadyConnected(EXC_INFO);
        }
        if (m_tcp_listener.listen(port) != sf::Socket::Done)
        {
            throw std::runtime_error(fmt::format("impossible to listen on port '{}'", port));
        }
        m_client_name = "host";
        m_is_host = true;
    }

    void NetworkEventManager::connect(const std::string& address, unsigned short port)
    {
        m_is_host = false;
    }

    void NetworkEventManager::emit(
        const std::string& event_group_name, const std::string& event_name, const vili::node& data)
    {
        const std::string message_dump = _build_message(event_group_name, event_name, data);
        for (const auto& [client_name, client] : m_clients)
        {
            client.socket().send(message_dump.data(), message_dump.size());
        }
    }

    void NetworkEventManager::emit(const std::string& recipient, const std::string& event_group_name, const std::string& event_name, const vili::node& data) const
    {
        if (!m_clients.contains(recipient))
        {
            throw exceptions::ClientNotFound(recipient, EXC_INFO);
        }
        const std::string message_dump = _build_message(event_group_name, event_name, data);
        m_clients.at(recipient).socket().send(message_dump.data(), message_dump.size());
    }

    void NetworkEventManager::handle_events()
    {
        _accept_new_clients();
        _receive_messages();
    }
}
