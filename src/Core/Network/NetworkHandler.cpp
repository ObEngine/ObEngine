#include <Network/NetworkHandler.hpp>

namespace obe::Network
{
    NetworkHandler::NetworkHandler(event::EventNamespace& eventNamespace)
        : m_received(0)
        , m_status()
        , m_data {}
        , e_network(eventNamespace.create_group("Network"))
    {
        m_listener.setBlocking(false);
        m_listener.listen(53000);
        m_client.setBlocking(false);

        e_network->add<events::Network::Connected>();
        e_network->add<events::Network::Disconnected>();
        e_network->add<events::Network::DataReceived>();
    }

    void NetworkHandler::handleTriggers()
    {
        if (m_listener.accept(m_client) == sf::Socket::Done)
        {
            m_ip = m_client.getRemoteAddress().toString();
            e_network->trigger(events::Network::Connected { m_ip });
            std::cout << "[Network] Client Accepted" << std::endl;
        }
        m_status = m_client.receive(m_data, 100, m_received);
        if (m_status == sf::Socket::Done)
        {
            const std::string content = std::string(m_data).substr(0, m_received);
            e_network->trigger(events::Network::DataReceived { content });
        }
        else if (m_status == sf::Socket::Disconnected)
        {
            e_network->trigger(events::Network::Disconnected {});
        }
    }
} // namespace obe::Network
