#include <unordered_set>

#include <cppnet/packet.hpp>
#include <fmt/core.h>
#include <vili-msgpack/msgpack.hpp>
#include <vili/parser.hpp>

#include <Network/Exceptions.hpp>
#include <Network/NetworkEventManager.hpp>
#include <Utils/Encoding.hpp>

namespace obe::network
{
    std::unordered_set<std::string_view> FORBIDDEN_NETWORK_EVENT_GROUPS = { "Client" };

    NetworkClient::NetworkClient(const std::string& name, std::unique_ptr<cppnet::TcpSocket>&& socket)
        : m_name(name)
        , m_socket(std::move(socket))
    {
    }

    void NetworkClient::rename(const std::string& name)
    {
        m_name = name;
    }

    std::string NetworkClient::name() const
    {
        return m_name;
    }

    std::string NetworkClient::host() const
    {
        cppnet::IpAddress remote_address = m_socket->get_remote_address().value_or(cppnet::IpAddress::Any);
        return remote_address.to_string();
    }

    cppnet::TcpSocket& NetworkClient::socket() const
    {
        return *m_socket;
    }

    void NetworkEventManager::_build_events_from_spec()
    {
        for (const auto& [event_group_name, event_group_spec] : m_spec.items())
        {
            if (!m_namespace->does_group_exists(event_group_name))
            {
                const event::EventGroupPtr event_group
                    = m_namespace->create_group(event_group_name);
                m_event_groups.emplace(event_group_name, event_group);
                for (const auto& [event_name, event_spec] : event_group_spec.items())
                {
                    if (!event_group->contains(event_name))
                    {
                        event_group->add<events::Network::Message>(event_name);
                    }
                }
            }
        }
    }

    void NetworkEventManager::_accept_new_clients()
    {
        std::unique_ptr<cppnet::TcpSocket> new_socket = std::make_unique<cppnet::TcpSocket>();

        const cppnet::Socket::Status status = m_tcp_listener.accept(*new_socket);
        if (status == cppnet::Socket::Status::Done)
        {
            new_socket->set_blocking(false);
            const std::string random_client_name
                = utils::string::get_random_key(utils::string::Alphabet, 16);
            cppnet::IpAddress remote_address = new_socket->get_remote_address().value_or(cppnet::IpAddress::Any);
            // Prepare "Connected" event
            const auto evt = events::Network::Connected { remote_address.to_string(),
                new_socket->get_local_port(), new_socket->get_remote_port(), random_client_name };
            // Trigger "ClientRename" event
            const std::string client_rename_msg = _build_message(
                "Client", "ClientRename", vili::object { { "name", random_client_name } }, false);
            cppnet::Packet packet;
            packet << client_rename_msg;
            // TODO: handle error
            cppnet::Socket::Status _send_status = new_socket->send(packet);
            m_clients.emplace(
                random_client_name, NetworkClient(random_client_name, std::move(new_socket)));
            // Trigger "Connected" event
            e_client->trigger(evt);
        }
    }

    void NetworkEventManager::_receive_messages()
    {
        std::vector<std::string> clients_to_remove;
        for (auto& [client_name, client] : m_clients)
        {
            cppnet::Packet packet;
            std::string content;
            cppnet::Socket::Status status = client.socket().receive(packet);
            packet >> content;
            if (status == cppnet::Socket::Status::Done)
            {
                vili::node message;
                debug::Log->trace(
                    "Received NetworkEvent content (base64) '{}'", utils::base64::encode(content));
                try
                {
                    message = vili::msgpack::from_string(content);
                }
                catch (const std::exception& e)
                {
                    throw exceptions::InvalidNetworkMessage(content).nest(e);
                }
                debug::Log->debug("Received NetworkEvent content '{}'", message.dump());

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
                events::Network::Message message_event = events::Network::Message { client.name(),
                    event_group_name, event_name, message_data };
                _handle_message(message_event);
            }
            else if (status == cppnet::Socket::Status::Disconnected)
            {
                e_client->trigger(events::Network::Disconnected { client.name() });
                clients_to_remove.push_back(client_name);
                client.socket().disconnect();
            }
        }
        for (const std::string& client_to_remove : clients_to_remove)
        {
            m_clients.erase(client_to_remove);
        }
    }

    void NetworkEventManager::_handle_message(const events::Network::Message& message)
    {
        if (message.event_group_name.empty() || message.event_name.empty())
        {
            throw exceptions::NetworkMessageMissingEventFields(message.data.dump(true));
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
            throw exceptions::EventGroupNotInSpec(message.event_group_name);
        }
        const event::EventGroupPtr event_group = m_event_groups.at(message.event_group_name);
        if (!event_group->contains(message.event_name))
        {
            throw exceptions::EventNotInSpec(message.event_name);
        }
        event_group->trigger(message.event_name, message);
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
            throw exceptions::ReservedEventGroup(event_group_name);
        }
        const vili::node message
            = vili::object { { "g", event_group_name }, { "e", event_name }, { "d", data } };
        return vili::msgpack::to_string(message);
    }

    NetworkEventManager::NetworkEventManager(
        event::EventNamespace::Ptr event_namespace, const vili::node& spec)
        : m_spec(spec)
        , m_namespace(event_namespace)
    {
        e_client = m_namespace->create_group("Client");
        e_client->add<events::Network::Connected>();
        e_client->add<events::Network::Disconnected>();
        e_client->add<events::Network::Message>();

        _build_events_from_spec();

        m_tcp_listener.set_blocking(false);
    }

    void NetworkEventManager::rename_client(
        const std::string& current_name, const std::string& new_name)
    {
        if (!m_clients.contains(current_name))
        {
            throw exceptions::ClientNotFound(current_name);
        }
        auto client = m_clients.extract(current_name);
        client.key() = new_name;
        client.mapped().rename(new_name);
        const std::string client_rename_msg = _build_message(
            "Client", "ClientRename", vili::object { { "name", new_name } }, false);
        cppnet::Packet packet;
        packet << client_rename_msg;
        // TODO: handle error
        cppnet::Socket::Status _send_status = client.mapped().socket().send(packet);
        m_clients.insert(std::move(client));
    }

    void NetworkEventManager::host(const unsigned short port)
    {
        if (!m_client_name.empty())
        {
            throw exceptions::AlreadyConnected();
        }
        if (m_tcp_listener.listen(port) != cppnet::Socket::Status::Done)
        {
            throw std::runtime_error(fmt::format("impossible to listen on port '{}'", port));
        }
        m_client_name = "host";
        m_is_host = true;
        debug::Log->debug("<NetworkEventManager> Listening on port {}", port);
    }

    void NetworkEventManager::connect(const std::string& host, unsigned short port)
    {
        m_is_host = false;
        std::unique_ptr<cppnet::TcpSocket> new_socket = std::make_unique<cppnet::TcpSocket>();
        if (auto host_ip = cppnet::IpAddress::resolve(host); host_ip)
        {
            const cppnet::Socket::Status status = new_socket->connect(*host_ip, port);
            if (status != cppnet::Socket::Status::Done)
            {
                throw exceptions::CannotConnectToHost(host, port);
            }
            new_socket->set_blocking(false);
            m_clients.emplace("host", NetworkClient("host", std::move(new_socket)));
        }
        else
        {
            throw exceptions::CannotConnectToHost(host, port);
        }
    }

    void NetworkEventManager::emit(
        const std::string& event_group_name, const std::string& event_name, const vili::node& data)
    {
        const std::string message_dump = _build_message(event_group_name, event_name, data);
        for (const auto& [client_name, client] : m_clients)
        {
            cppnet::Packet packet;
            packet << message_dump;
            // TODO: Handle error
            cppnet::Socket::Status _send_status = client.socket().send(packet);
        }
    }

    void NetworkEventManager::emit(const std::string& recipient,
        const std::string& event_group_name, const std::string& event_name,
        const vili::node& data) const
    {
        if (!m_clients.contains(recipient))
        {
            throw exceptions::ClientNotFound(recipient);
        }
        const std::string message_dump = _build_message(event_group_name, event_name, data);
        cppnet::Packet packet;
        packet << message_dump;
        // TODO: Handle error
        cppnet::Socket::Status _send_status = m_clients.at(recipient).socket().send(packet);
    }

    void NetworkEventManager::handle_events()
    {
        if (m_is_host)
        {
            _accept_new_clients();
        }
        _receive_messages();
    }

    event::EventNamespaceView NetworkEventManager::get_event_namespace() const
    {
        return m_namespace->get_view();
    }

    std::string NetworkEventManager::get_client_name() const
    {
        return m_client_name;
    }
}
