#pragma once

#include <string>

#include <cppnet/http.hpp>
#include <cppnet/json.hpp>

namespace cppnet::requests
{
    using Method = Http::Request::Method;

    class Response
    {
    private:
        Http::Response m_response;
    public:
        Response(Http::Response&& response);

        const std::string& body() const;
        const json::Json& json() const;

        const std::string& reason() const;
        void throw_for_status() const;
        uint16_t status_code() const;

        const std::map<std::string, std::string>& headers() const;
        const std::map<std::string, std::string>& cookies() const;

        operator bool() const;
        bool ok() const;
    };

    class Request
    {
    private:
        std::string m_host;
        uint16_t m_port;
        Http::Request m_request;

        std::string _get_host_from_url(const std::string& url);
        std::string _get_route_from_url(const std::string& url);
    public:
        Request(Method method, const std::string& url);

        Request& with_headers(const std::map<std::string, std::string>& headers);
        Request& with_body(const std::string& body);
        Request& with_body(const json::Json& body);
        Request& with_http_version(uint32_t major, uint32_t minor);

        Response call();
    };

    Request get(const std::string& url);
    Request post(const std::string& url);
    Request head(const std::string& url);
    Request patch(const std::string& url);
    Request put(const std::string& url);
    Request delete_(const std::string& url);
}