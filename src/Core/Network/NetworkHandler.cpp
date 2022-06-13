#include <Network/NetworkHandler.hpp>

namespace obe::network
{
    NetworkHandler::NetworkHandler(event::EventNamespace& event_namespace)
        : m_received(0)
        , m_status()
        , m_data {}
        , e_network(event_namespace.create_group("network"))
    {
        m_listener.setBlocking(false);
        m_listener.listen(53000);
        m_client.setBlocking(false);

        e_network->add<events::network::Connected>();
        e_network->add<events::network::Disconnected>();
        e_network->add<events::network::DataReceived>();
    }

    void NetworkHandler::handle_events()
    {
        if (m_listener.accept(m_client) == sf::Socket::Done)
        {
            m_ip = m_client.getRemoteAddress().toString();
            e_network->trigger(events::network::Connected { m_ip });
            std::cout << "[network] Client Accepted" << std::endl;
        }
        m_status = m_client.receive(m_data, 100, m_received);
        if (m_status == sf::Socket::Done)
        {
            const std::string content = std::string(m_data).substr(0, m_received);
            e_network->trigger(events::network::DataReceived { content });
        }
        else if (m_status == sf::Socket::Disconnected)
        {
            e_network->trigger(events::network::Disconnected {});
        }
    }
} // namespace obe::network
