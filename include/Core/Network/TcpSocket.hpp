#pragma once

#include <SFML/Network/TcpSocket.hpp>

namespace obe::Network
{
    class LuaPacket
    {
    private:
        std::string m_serializedObject;

    public:
    };

    class TcpSocket : public sf::TcpSocket
    {
    public:
    };
} // namespace obe::Network