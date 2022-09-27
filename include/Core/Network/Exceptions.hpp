#pragma once

#include <Exception.hpp>

/**
 * \nobind
 */
namespace obe::network::exceptions
{
    class InvalidNetworkMessage : public Exception<InvalidNetworkMessage>
    {
    public:
        using Exception::Exception;
        InvalidNetworkMessage(std::string_view message_content, DebugInfo info)
            : Exception(info)
        {
            this->error("Message is not valid vili / msgpack"
                        "\n"
                        "Message content :\n",
                "{}", message_content);
        }
    };

    class NetworkMessageMissingEventFields : public Exception<NetworkMessageMissingEventFields>
    {
    public:
        using Exception::Exception;
        NetworkMessageMissingEventFields(
            std::string_view message_content, DebugInfo info)
            : Exception(info)
        {
            this->error("Message should both contain 'e' field (event) and 'g' field (event group) but is missing one or both"
                        "\n"
                        "Message content :\n",
                        "{}", message_content);
        }
    };

    class ForbiddenEventGroup : public Exception<ForbiddenEventGroup>
    {
    public:
        using Exception::Exception;
        ForbiddenEventGroup(std::string_view event_group_name, DebugInfo info)
            : Exception(info)
        {
            this->error("Can not use EventGroup '{}' for NetworkEvent", event_group_name);
        }
    };

    class ClientNotFound : public Exception<ClientNotFound>
    {
    public:
        using Exception::Exception;
        ClientNotFound(std::string_view client_name, DebugInfo info)
            : Exception(info)
        {
            this->error("Could not find client with name '{}'", client_name);
        }
    };

    class AlreadyConnected : public Exception<AlreadyConnected>
    {
    public:
        using Exception::Exception;
        AlreadyConnected(DebugInfo info)
            : Exception(info)
        {
            this->error("Already connected, please disconnect before hosting or connecting to a new client");
        }
    };
}