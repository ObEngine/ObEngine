#pragma once

#include <string>

namespace cppnet
{
    struct HostAndPort
    {
        std::string host;
        uint16_t port;
    };

    HostAndPort get_host_and_port_from_url(const std::string& url);
    std::string get_route_from_url(const std::string& url);
}