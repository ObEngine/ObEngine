#include <stdexcept>

#include <cppnet/requests.hpp>

namespace cppnet::requests
{
    std::string Request::_get_host_from_url(const std::string& url)
    {
        std::string host = url;

        if (url.compare(0, 7, "http://") == 0)
        {
            m_port = 80;
        }
        else if (url.compare(0, 8, "https://") == 0)
        {
            m_port = 443;
        }
        else
        {
            throw std::runtime_error("unknown protocol"); // TODO: throw proper exception
        }

        size_t path_pos = host.find("/");
        if (path_pos != std::string::npos) {
            host = host.substr(0, path_pos);
        }

        return host;
    }

    std::string Request::_get_route_from_url(const std::string& url)
    {
        std::string route = "/";

        size_t path_pos = url.find("/");
        if (path_pos != std::string::npos) {
            route = url.substr(path_pos);
        }

        return route;
    }

    Request::Request(Method method, const std::string& url)
        : m_host(_get_host_from_url(url))
        , m_request(_get_route_from_url(url), method)
    {
    }

    Request& Request::with_headers(const std::map<std::string, std::string>& headers)
    {
        for (const auto& [field_name, field_value] : headers)
        {
            m_request.set_field(field_name, field_value);
        }

        return *this;
    }

    Request& Request::with_body(const std::string& body)
    {
        m_request.set_field("Content-Type", "application/json");
        m_request.set_body(body);

        return *this;
    }

    Request& Request::with_http_version(uint32_t major, uint32_t minor)
    {
        m_request.set_http_version(major, minor);

        return *this;
    }

    Response Request::call()
    {
        Http http(m_host, m_port);
        Http::Response response = http.send_request(m_request);
        return Response(std::move(response));
    }

    Request get(const std::string& url)
    {
        return Request(Method::GET, url);
    }

    Request post(const std::string& url)
    {
        return Request(Method::POST, url);
    }

    Request put(const std::string& url)
    {
        return Request(Method::PUT, url);
    }

    Request patch(const std::string& url)
    {
        return Request(Method::PATCH, url);
    }

    Request head(const std::string& url)
    {
        return Request(Method::HEAD, url);
    }

    Request delete_(const std::string& url)
    {
        return Request(Method::DELETE, url);
    }
}