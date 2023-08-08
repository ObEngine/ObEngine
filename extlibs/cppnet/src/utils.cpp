#include <stdexcept>

#include <cppnet/utils.hpp>

namespace cppnet
{
	HostAndPort get_host_and_port_from_url(const std::string& url)
    {
        HostAndPort host_and_port;
        host_and_port.host = url;

        if (url.compare(0, 7, "http://") == 0)
        {
            host_and_port.port = 80;
        }
        else if (url.compare(0, 8, "https://") == 0)
        {
            host_and_port.port = 443;
        }
        else
        {
            throw std::runtime_error("unknown protocol"); // TODO: throw proper exception
        }

        size_t path_pos = host_and_port.host.find("/");
        if (path_pos != std::string::npos) {
            host_and_port.host = host_and_port.host.substr(0, path_pos);
        }

        return host_and_port;
    }

    std::string get_route_from_url(const std::string& url)
    {
        std::string route = "/";

        size_t path_pos = url.find("/");
        if (path_pos != std::string::npos) {
            route = url.substr(path_pos);
        }

        return route;
    }
}