#include <iterator>
#include <limits>
#include <ostream>
#include <sstream>

#include <cppnet/http.hpp>
#include <cppnet/log.hpp>

namespace cppnet
{
[[nodiscard]] inline std::string to_lower(std::string str)
{
    for (char& c : str)
        c = static_cast<char>(std::tolower(static_cast<unsigned char>(c)));
    return str;
}

////////////////////////////////////////////////////////////
Http::Request::Request(const std::string& uri, Method method, const std::string& body)
{
    set_method(method);
    set_uri(uri);
    set_http_version(1, 0);
    set_body(body);
}


////////////////////////////////////////////////////////////
void Http::Request::set_field(const std::string& field, const std::string& value)
{
    m_fields[to_lower(field)] = value;
}


////////////////////////////////////////////////////////////
void Http::Request::set_method(Http::Request::Method method)
{
    m_method = method;
}


////////////////////////////////////////////////////////////
void Http::Request::set_uri(const std::string& uri)
{
    m_uri = uri;

    // Make sure it starts with a '/'
    if (m_uri.empty() || (m_uri[0] != '/'))
        m_uri.insert(m_uri.begin(), '/');
}


////////////////////////////////////////////////////////////
void Http::Request::set_http_version(unsigned int major, unsigned int minor)
{
    m_major_version = major;
    m_minor_version = minor;
}


////////////////////////////////////////////////////////////
void Http::Request::set_body(const std::string& body)
{
    m_body = body;
}


////////////////////////////////////////////////////////////
std::string Http::Request::prepare() const
{
    std::ostringstream out;

    // Convert the method to its string representation
    std::string method;
    switch (m_method)
    {
        case Method::GET:
            method = "GET";
            break;
        case Method::POST:
            method = "POST";
            break;
        case Method::HEAD:
            method = "HEAD";
            break;
        case Method::PATCH:
            method = "PATCH";
            break;
        case Method::PUT:
            method = "PUT";
            break;
        case Method::DELETE:
            method = "DELETE";
            break;
    }

    // Write the first line containing the request type
    out << method << " " << m_uri << " ";
    out << "HTTP/" << m_major_version << "." << m_minor_version << "\r\n";

    // Write fields
    for (const auto& [field_key, field_value] : m_fields)
    {
        out << field_key << ": " << field_value << "\r\n";
    }

    // Use an extra \r\n to separate the header from the body
    out << "\r\n";

    // Add the body
    out << m_body;

    return out.str();
}


////////////////////////////////////////////////////////////
bool Http::Request::has_field(const std::string& field) const
{
    return m_fields.find(to_lower(field)) != m_fields.end();
}


////////////////////////////////////////////////////////////
const std::string& Http::Response::get_field(const std::string& field) const
{
    if (auto it = m_fields.find(to_lower(field)); it != m_fields.end())
    {
        return it->second;
    }

    static const std::string empty;
    return empty;
}


////////////////////////////////////////////////////////////
Http::Response::Status Http::Response::get_status() const
{
    return m_status;
}


////////////////////////////////////////////////////////////
unsigned int Http::Response::get_major_http_version() const
{
    return m_major_version;
}


////////////////////////////////////////////////////////////
unsigned int Http::Response::get_minor_http_version() const
{
    return m_minor_version;
}


////////////////////////////////////////////////////////////
const std::string& Http::Response::get_body() const
{
    return m_body;
}


////////////////////////////////////////////////////////////
void Http::Response::parse(const std::string& data)
{
    std::istringstream in(data);

    // Extract the HTTP version from the first line
    std::string version;
    if (in >> version)
    {
        if ((version.size() >= 8) && (version[6] == '.') && (to_lower(version.substr(0, 5)) == "http/") &&
            std::isdigit(version[5]) && std::isdigit(version[7]))
        {
            m_major_version = static_cast<unsigned int>(version[5] - '0');
            m_minor_version = static_cast<unsigned int>(version[7] - '0');
        }
        else
        {
            // Invalid HTTP version
            m_status = Status::InvalidResponse;
            return;
        }
    }

    // Extract the status code from the first line
    int status;
    if (in >> status)
    {
        m_status = static_cast<Status>(status);
    }
    else
    {
        // Invalid status code
        m_status = Status::InvalidResponse;
        return;
    }

    // Ignore the end of the first line
    in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    // Parse the other lines, which contain fields, one by one
    parse_fields(in);

    m_body.clear();

    // Determine whether the transfer is chunked
    if (to_lower(get_field("transfer-encoding")) != "chunked")
    {
        // Not chunked - just read everything at once
        std::copy(std::istreambuf_iterator<char>(in), std::istreambuf_iterator<char>(), std::back_inserter(m_body));
    }
    else
    {
        // Chunked - have to read chunk by chunk
        std::size_t length;

        // Read all chunks, identified by a chunk-size not being 0
        while (in >> std::hex >> length)
        {
            // Drop the rest of the line (chunk-extension)
            in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            // Copy the actual content data
            std::istreambuf_iterator<char> it(in);
            std::istreambuf_iterator<char> it_end;
            for (std::size_t i = 0; ((i < length) && (it != it_end)); ++i)
            {
                m_body.push_back(*it);
                ++it; // Iterate in separate expression to work around false positive -Wnull-dereference warning in GCC 12.1.0
            }
        }

        // Drop the rest of the line (chunk-extension)
        in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        // Read all trailers (if present)
        parse_fields(in);
    }
}


////////////////////////////////////////////////////////////
void Http::Response::parse_fields(std::istream& in)
{
    std::string line;
    while (std::getline(in, line) && (line.size() > 2))
    {
        std::string::size_type pos = line.find(": ");
        if (pos != std::string::npos)
        {
            // Extract the field name and its value
            std::string field = line.substr(0, pos);
            std::string value = line.substr(pos + 2);

            // Remove any trailing \r
            if (!value.empty() && (*value.rbegin() == '\r'))
                value.erase(value.size() - 1);

            // Add the field
            m_fields[to_lower(field)] = value;
        }
    }
}

////////////////////////////////////////////////////////////
Http::Http(const std::string& host, unsigned short port)
{
    set_host(host, port);
}


////////////////////////////////////////////////////////////
void Http::set_host(const std::string& host, unsigned short port)
{
    // Check the protocol
    if (to_lower(host.substr(0, 7)) == "http://")
    {
        // HTTP protocol
        m_host_name = host.substr(7);
        m_port     = (port != 0 ? port : 80);
    }
    else if (to_lower(host.substr(0, 8)) == "https://")
    {
        // HTTPS protocol -- unsupported (requires encryption and certificates and stuff...)
        err() << "HTTPS protocol is not supported by cppnet::Http" << std::endl;
        m_host_name.clear();
        m_port = 0;
    }
    else
    {
        // Undefined protocol - use HTTP
        m_host_name = host;
        m_port     = (port != 0 ? port : 80);
    }

    // Remove any trailing '/' from the host name
    if (!m_host_name.empty() && (*m_host_name.rbegin() == '/'))
        m_host_name.erase(m_host_name.size() - 1);

    m_host = IpAddress::resolve(m_host_name);
}


////////////////////////////////////////////////////////////
Http::Response Http::send_request(const Http::Request& request, Time timeout)
{
    // First make sure that the request is valid -- add missing mandatory fields
    Request to_send(request);
    if (!to_send.has_field("From"))
    {
        to_send.set_field("From", "cppnet");
    }
    if (!to_send.has_field("User-Agent"))
    {
        to_send.set_field("User-Agent", "cppnet/1.x");
    }
    if (!to_send.has_field("Host"))
    {
        to_send.set_field("Host", m_host_name);
    }
    if (!to_send.has_field("Content-Length"))
    {
        std::ostringstream out;
        out << to_send.m_body.size();
        to_send.set_field("Content-Length", out.str());
    }
    if ((to_send.m_method == Request::Method::POST) && !to_send.has_field("Content-Type"))
    {
        to_send.set_field("Content-Type", "application/x-www-form-urlencoded");
    }
    if ((to_send.m_major_version * 10 + to_send.m_minor_version >= 11) && !to_send.has_field("Connection"))
    {
        to_send.set_field("Connection", "close");
    }

    // Prepare the response
    Response received;

    // Connect the socket to the host
    if (m_connection.connect(m_host.value(), m_port, timeout) == Socket::Status::Done)
    {
        // Convert the request to string and send it through the connected socket
        std::string request_str = to_send.prepare();

        if (!request_str.empty())
        {
            // Send it through the socket
            if (m_connection.send(request_str.c_str(), request_str.size()) == Socket::Status::Done)
            {
                // Wait for the server's response
                std::string received_str;
                std::size_t size = 0;
                char        buffer[1024];
                while (m_connection.receive(buffer, sizeof(buffer), size) == Socket::Status::Done)
                {
                    received_str.append(buffer, buffer + size);
                }

                // Build the Response object from the received data
                received.parse(received_str);
            }
        }

        // Close the connection
        m_connection.disconnect();
    }

    return received;
}

} // namespace cppnet
