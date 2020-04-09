#include <Network/NetworkHandler.hpp>
#include <Triggers/TriggerManager.hpp>

#include <iostream>

namespace obe::Network
{
    NetworkHandler::NetworkHandler(Triggers::TriggerManager& triggers)
        : m_received(0)
        , m_status()
        , m_data {}
        , t_socket(triggers.createTriggerGroup("Event", "Network"))
    {
        m_listener.setBlocking(false);
        m_listener.listen(53000);
        m_client.setBlocking(false);
        t_socket->add("DataReceived").add("Connected").add("Disconnected");
    }

    void NetworkHandler::handleTriggers()
    {
        if (m_listener.accept(m_client) == sf::Socket::Done)
        {
            t_socket->pushParameter(
                "Connected", "IP", m_client.getRemoteAddress().toString());
            t_socket->trigger("Connected");
            std::cout << "[Network] Client Accepted" << std::endl;
        }
        m_status = m_client.receive(m_data, 100, m_received);
        if (m_status == sf::Socket::Done)
        {
            t_socket->pushParameter(
                "DataReceived", "Content", std::string(m_data).substr(0, m_received));
            t_socket->trigger("DataReceived");
        }
        else if (m_status == sf::Socket::Disconnected)
        {
            t_socket->trigger("Disconnected");
        }
    }
} // namespace obe::Network
