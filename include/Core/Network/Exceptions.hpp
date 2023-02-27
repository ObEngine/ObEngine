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
        InvalidNetworkMessage(std::string_view message_content,
            std::source_location location = std::source_location::current())
            : Exception(location)
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
        NetworkMessageMissingEventFields(std::string_view message_content,
            std::source_location location = std::source_location::current())
            : Exception(location)
        {
            this->error("Message should both contain 'e' field (event) and 'g' field (event group) "
                        "but is missing one or both"
                        "\n"
                        "Message content :\n",
                "{}", message_content);
        }
    };

    class ReservedEventGroup : public Exception<ReservedEventGroup>
    {
    public:
        using Exception::Exception;
        ReservedEventGroup(std::string_view event_group_name,
            std::source_location location = std::source_location::current())
            : Exception(location)
        {
            this->error("Can not use reserved EventGroup '{}' for NetworkEvent", event_group_name);
        }
    };

    class ClientNotFound : public Exception<ClientNotFound>
    {
    public:
        using Exception::Exception;
        ClientNotFound(std::string_view client_name,
            std::source_location location = std::source_location::current())
            : Exception(location)
        {
            this->error("Could not find client with name '{}'", client_name);
        }
    };

    class AlreadyConnected : public Exception<AlreadyConnected>
    {
    public:
        using Exception::Exception;
        AlreadyConnected(std::source_location location = std::source_location::current())
            : Exception(location)
        {
            this->error("Already connected, please disconnect before hosting or connecting to a "
                        "new client");
        }
    };

    class EventGroupNotInSpec : public Exception<EventGroupNotInSpec>
    {
    public:
        using Exception::Exception;
        EventGroupNotInSpec(std::string_view event_group_name,
            std::source_location location = std::source_location::current())
            : Exception(location)
        {
            this->error("EventGroup '{}' is not in NetworkEvent spec", event_group_name);
        }
    };

    class EventNotInSpec : public Exception<EventNotInSpec>
    {
    public:
        using Exception::Exception;
        EventNotInSpec(std::string_view event_name,
            std::source_location location = std::source_location::current())
            : Exception(location)
        {
            this->error("Event '{}' is not in NetworkEvent spec", event_name);
        }
    };

    class CannotConnectToHost : public Exception<CannotConnectToHost>
    {
    public:
        using Exception::Exception;
        CannotConnectToHost(std::string_view host, const unsigned short port,
            std::source_location location = std::source_location::current())
            : Exception(location)
        {
            this->error("Impossible to connect to host at '{}:{}'", host, port);
        }
    };
}