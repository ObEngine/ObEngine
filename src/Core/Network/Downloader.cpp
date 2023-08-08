#include <fstream>

#include <cppnet/http.hpp>
#include <cppnet/utils.hpp>

#include <Network/Downloader.hpp>

namespace obe::network
{
    void download_file(const std::string& url, const std::string& dest)
    {
        cppnet::Http http;
        cppnet::Http::Request request;

        cppnet::HostAndPort host_and_port
            = cppnet::get_host_and_port_from_url(url);
        const std::string route = cppnet::get_route_from_url(url);

        http.set_host(host_and_port.host, host_and_port.port);
        request.set_method(cppnet::Http::Request::Method::GET);
        request.set_uri(route);

        cppnet::Http::Response response = http.send_request(request);

        const std::string& body = response.get_body();
        const uint64_t file_size = body.size();

        std::ofstream output_file(dest.c_str(), std::ios::out | std::ios::binary);
        output_file.write(body.c_str(), file_size);
        output_file.close();
    }
}