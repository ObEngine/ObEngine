#pragma once

#include <SFML/Network.hpp>

#include <Event/EventGroup.hpp>
#include <Event/EventNamespace.hpp>

namespace obe::events::Network
{
    struct Connected
    {
        static constexpr std::string_view id = "Connected";
        const std::string ip;
    };

    struct Disconnected
    {
        static constexpr std::string_view id = "Disconnected";
    };

    struct DataReceived
    {
        static constexpr std::string_view id = "DataReceived";
        const std::string content;
    };
}

namespace obe::Network
{
    /**
     * \brief Handle the Network input / output (Will be remade)
     */
    class NetworkHandler
    {
    private:
        sf::TcpSocket m_client;
        sf::TcpListener m_listener;
        size_t m_received;
        sf::Socket::Status m_status;
        char m_data[4096];
        event::EventGroupPtr e_network;
        std::string m_ip;

    public:
        NetworkHandler(event::EventNamespace& eventNamespace);
        void handleTriggers();
    };
} // namespace obe::Network
