#include <Network/NetworkHandler.hpp>
#include <Triggers/TriggerDatabase.hpp>

#include <iostream>

namespace obe::Network
{
    NetworkHandler::NetworkHandler()
        : m_socketTriggers(
              Triggers::TriggerDatabase::GetInstance().createTriggerGroup("Global", "Network"),
              Triggers::TriggerGroupPtrRemover)
    {
        m_listener.setBlocking(false);
        m_listener.listen(53000);
        m_client.setBlocking(false);
        m_socketTriggers->addTrigger("DataReceived")
            ->addTrigger("Connected")
            ->addTrigger("Disconnected");
    }

    void NetworkHandler::handleTriggers()
    {
        if (m_listener.accept(m_client) == sf::Socket::Done)
        {
            m_socketTriggers->pushParameter(
                "Connected", "IP", m_client.getRemoteAddress().toString());
            m_socketTriggers->trigger("Connected");
            std::cout << "[Network] Client Accepted" << std::endl;
        }
        m_status = m_client.receive(m_data, 100, m_received);
        if (m_status == sf::Socket::Done)
        {
            m_socketTriggers->pushParameter(
                "DataReceived", "Content", std::string(m_data).substr(0, m_received));
            m_socketTriggers->trigger("DataReceived");
        }
        else if (m_status == sf::Socket::Disconnected)
        {
            m_socketTriggers->trigger("Disconnected");
        }
    }
} // namespace obe::Network
