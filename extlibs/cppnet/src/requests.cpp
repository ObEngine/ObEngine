#include <stdexcept>

#include <cppnet/requests.hpp>
#include <cppnet/utils.hpp>

namespace cppnet::requests
{
    Request::Request(Method method, const std::string& url)
        : m_host(get_host_and_port_from_url(url).host)
        , m_port(get_host_and_port_from_url(url).port)
        , m_request(get_route_from_url(url), method)
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