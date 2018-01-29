#pragma once

#include <SFML/Network/TcpSocket.hpp>

namespace obe
{
    namespace Network
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
    }
}