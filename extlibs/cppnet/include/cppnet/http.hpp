#pragma once

#include <map>
#include <optional>
#include <string>

#include <cppnet/ip_address.hpp>
#include <cppnet/tcp_socket.hpp>
#include <cppnet/time.hpp>

namespace cppnet
{
////////////////////////////////////////////////////////////
/// \brief A HTTP client
///
////////////////////////////////////////////////////////////
class Http
{
public:
    ////////////////////////////////////////////////////////////
    /// \brief Define a HTTP request
    ///
    ////////////////////////////////////////////////////////////
    class Request
    {
    public:
        ////////////////////////////////////////////////////////////
        /// \brief Enumerate the available HTTP methods for a request
        ///
        ////////////////////////////////////////////////////////////
        enum class Method
        {
            GET,   //!< Request in get mode, standard method to retrieve a page
            POST,  //!< Request in post mode, usually to send data to a page
            HEAD,  //!< Request a page's header only
            PATCH, //!< Request in patch mode, useful for a REST API
            PUT,   //!< Request in put mode, useful for a REST API
            DELETE //!< Request in delete mode, useful for a REST API
        };

        ////////////////////////////////////////////////////////////
        /// \brief Default constructor
        ///
        /// This constructor creates a GET request, with the root
        /// URI ("/") and an empty body.
        ///
        /// \param uri    Target URI
        /// \param method Method to use for the request
        /// \param body   Content of the request's body
        ///
        ////////////////////////////////////////////////////////////
        Request(const std::string& uri = "/", Method method = Method::GET, const std::string& body = "");

        ////////////////////////////////////////////////////////////
        /// \brief Set the value of a field
        ///
        /// The field is created if it doesn't exist. The name of
        /// the field is case-insensitive.
        /// By default, a request doesn't contain any field (but the
        /// mandatory fields are added later by the HTTP client when
        /// sending the request).
        ///
        /// \param field Name of the field to set
        /// \param value Value of the field
        ///
        ////////////////////////////////////////////////////////////
        void set_field(const std::string& field, const std::string& value);

        ////////////////////////////////////////////////////////////
        /// \brief Set the request method
        ///
        /// See the Method enumeration for a complete list of all
        /// the availale methods.
        /// The method is Http::Request::Method::Get by default.
        ///
        /// \param method Method to use for the request
        ///
        ////////////////////////////////////////////////////////////
        void set_method(Method method);

        ////////////////////////////////////////////////////////////
        /// \brief Set the requested URI
        ///
        /// The URI is the resource (usually a web page or a file)
        /// that you want to get or post.
        /// The URI is "/" (the root page) by default.
        ///
        /// \param uri URI to request, relative to the host
        ///
        ////////////////////////////////////////////////////////////
        void set_uri(const std::string& uri);

        ////////////////////////////////////////////////////////////
        /// \brief Set the HTTP version for the request
        ///
        /// The HTTP version is 1.0 by default.
        ///
        /// \param major Major HTTP version number
        /// \param minor Minor HTTP version number
        ///
        ////////////////////////////////////////////////////////////
        void set_http_version(unsigned int major, unsigned int minor);

        ////////////////////////////////////////////////////////////
        /// \brief Set the body of the request
        ///
        /// The body of a request is optional and only makes sense
        /// for POST requests. It is ignored for all other methods.
        /// The body is empty by default.
        ///
        /// \param body Content of the body
        ///
        ////////////////////////////////////////////////////////////
        void set_body(const std::string& body);

    private:
        friend class Http;

        ////////////////////////////////////////////////////////////
        /// \brief Prepare the final request to send to the server
        ///
        /// This is used internally by Http before sending the
        /// request to the web server.
        ///
        /// \return String containing the request, ready to be sent
        ///
        ////////////////////////////////////////////////////////////
        [[nodiscard]] std::string prepare() const;

        ////////////////////////////////////////////////////////////
        /// \brief Check if the request defines a field
        ///
        /// This function uses case-insensitive comparisons.
        ///
        /// \param field Name of the field to test
        ///
        /// \return True if the field exists, false otherwise
        ///
        ////////////////////////////////////////////////////////////
        bool has_field(const std::string& field) const;

        ////////////////////////////////////////////////////////////
        // Types
        ////////////////////////////////////////////////////////////
        using FieldTable = std::map<std::string, std::string>; // Use an ordered map for predictable payloads

        ////////////////////////////////////////////////////////////
        // Member data
        ////////////////////////////////////////////////////////////
        FieldTable   m_fields;       //!< Fields of the header associated to their value
        Method       m_method;       //!< Method to use for the request
        std::string  m_uri;          //!< Target URI of the request
        unsigned int m_major_version; //!< Major HTTP version
        unsigned int m_minor_version; //!< Minor HTTP version
        std::string  m_body;         //!< Body of the request
    };

    ////////////////////////////////////////////////////////////
    /// \brief Define a HTTP response
    ///
    ////////////////////////////////////////////////////////////
    class Response
    {
    public:
        ////////////////////////////////////////////////////////////
        /// \brief Enumerate all the valid status codes for a response
        ///
        ////////////////////////////////////////////////////////////
        enum class Status
        {
            // 2xx: success
            Ok        = 200, //!< Most common code returned when operation was successful
            Created   = 201, //!< The resource has successfully been created
            Accepted  = 202, //!< The request has been accepted, but will be processed later by the server
            NoContent = 204, //!< The server didn't send any data in return
            ResetContent = 205, //!< The server informs the client that it should clear the view (form) that caused the request to be sent
            PartialContent = 206, //!< The server has sent a part of the resource, as a response to a partial GET request

            // 3xx: redirection
            MultipleChoices  = 300, //!< The requested page can be accessed from several locations
            MovedPermanently = 301, //!< The requested page has permanently moved to a new location
            MovedTemporarily = 302, //!< The requested page has temporarily moved to a new location
            NotModified = 304, //!< For conditional requests, means the requested page hasn't changed and doesn't need to be refreshed

            // 4xx: client error
            BadRequest          = 400, //!< The server couldn't understand the request (syntax error)
            Unauthorized        = 401, //!< The requested page needs an authentication to be accessed
            Forbidden           = 403, //!< The requested page cannot be accessed at all, even with authentication
            NotFound            = 404, //!< The requested page doesn't exist
            RangeNotSatisfiable = 407, //!< The server can't satisfy the partial GET request (with a "Range" header field)

            // 5xx: server error
            InternalServerError = 500, //!< The server encountered an unexpected error
            NotImplemented      = 501, //!< The server doesn't implement a requested feature
            BadGateway          = 502, //!< The gateway server has received an error from the source server
            ServiceNotAvailable = 503, //!< The server is temporarily unavailable (overloaded, in maintenance, ...)
            GatewayTimeout      = 504, //!< The gateway server couldn't receive a response from the source server
            VersionNotSupported = 505, //!< The server doesn't support the requested HTTP version

            // 10xx: CppNet custom codes
            InvalidResponse  = 1000, //!< Response is not a valid HTTP one
            ConnectionFailed = 1001  //!< Connection with server failed
        };

        ////////////////////////////////////////////////////////////
        /// \brief Get the value of a field
        ///
        /// If the field \a field is not found in the response header,
        /// the empty string is returned. This function uses
        /// case-insensitive comparisons.
        ///
        /// \param field Name of the field to get
        ///
        /// \return Value of the field, or empty string if not found
        ///
        ////////////////////////////////////////////////////////////
        const std::string& get_field(const std::string& field) const;

        ////////////////////////////////////////////////////////////
        /// \brief Get the response status code
        ///
        /// The status code should be the first thing to be checked
        /// after receiving a response, it defines whether it is a
        /// success, a failure or anything else (see the Status
        /// enumeration).
        ///
        /// \return Status code of the response
        ///
        ////////////////////////////////////////////////////////////
        Status get_status() const;

        ////////////////////////////////////////////////////////////
        /// \brief Get the major HTTP version number of the response
        ///
        /// \return Major HTTP version number
        ///
        /// \see get_minor_http_version
        ///
        ////////////////////////////////////////////////////////////
        unsigned int get_major_http_version() const;

        ////////////////////////////////////////////////////////////
        /// \brief Get the minor HTTP version number of the response
        ///
        /// \return Minor HTTP version number
        ///
        /// \see get_major_http_version
        ///
        ////////////////////////////////////////////////////////////
        unsigned int get_minor_http_version() const;

        ////////////////////////////////////////////////////////////
        /// \brief Get the body of the response
        ///
        /// The body of a response may contain:
        /// \li the requested page (for GET requests)
        /// \li a response from the server (for POST requests)
        /// \li nothing (for HEAD requests)
        /// \li an error message (in case of an error)
        ///
        /// \return The response body
        ///
        ////////////////////////////////////////////////////////////
        const std::string& get_body() const;

    private:
        friend class Http;

        ////////////////////////////////////////////////////////////
        /// \brief Construct the header from a response string
        ///
        /// This function is used by Http to build the response
        /// of a request.
        ///
        /// \param data Content of the response to parse
        ///
        ////////////////////////////////////////////////////////////
        void parse(const std::string& data);


        ////////////////////////////////////////////////////////////
        /// \brief Read values passed in the answer header
        ///
        /// This function is used by Http to extract values passed
        /// in the response.
        ///
        /// \param in String stream containing the header values
        ///
        ////////////////////////////////////////////////////////////
        void parse_fields(std::istream& in);

        ////////////////////////////////////////////////////////////
        // Types
        ////////////////////////////////////////////////////////////
        using FieldTable = std::map<std::string, std::string>; // Use an ordered map for predictable payloads

        ////////////////////////////////////////////////////////////
        // Member data
        ////////////////////////////////////////////////////////////
        FieldTable   m_fields;                           //!< Fields of the header
        Status       m_status{Status::ConnectionFailed}; //!< Status code
        unsigned int m_major_version{};                   //!< Major HTTP version
        unsigned int m_minor_version{};                   //!< Minor HTTP version
        std::string  m_body;                             //!< Body of the response
    };

    ////////////////////////////////////////////////////////////
    /// \brief Default constructor
    ///
    ////////////////////////////////////////////////////////////
    Http() = default;

    ////////////////////////////////////////////////////////////
    /// \brief Construct the HTTP client with the target host
    ///
    /// This is equivalent to calling set_host(host, port).
    /// The port has a default value of 0, which means that the
    /// HTTP client will use the right port according to the
    /// protocol used (80 for HTTP). You should leave it like
    /// this unless you really need a port other than the
    /// standard one, or use an unknown protocol.
    ///
    /// \param host Web server to connect to
    /// \param port Port to use for connection
    ///
    ////////////////////////////////////////////////////////////
    Http(const std::string& host, unsigned short port = 0);

    ////////////////////////////////////////////////////////////
    /// \brief Deleted copy constructor
    ///
    ////////////////////////////////////////////////////////////
    Http(const Http&) = delete;

    ////////////////////////////////////////////////////////////
    /// \brief Deleted copy assignment
    ///
    ////////////////////////////////////////////////////////////
    Http& operator=(const Http&) = delete;

    ////////////////////////////////////////////////////////////
    /// \brief Set the target host
    ///
    /// This function just stores the host address and port, it
    /// doesn't actually connect to it until you send a request.
    /// The port has a default value of 0, which means that the
    /// HTTP client will use the right port according to the
    /// protocol used (80 for HTTP). You should leave it like
    /// this unless you really need a port other than the
    /// standard one, or use an unknown protocol.
    ///
    /// \param host Web server to connect to
    /// \param port Port to use for connection
    ///
    ////////////////////////////////////////////////////////////
    void set_host(const std::string& host, unsigned short port = 0);

    ////////////////////////////////////////////////////////////
    /// \brief Send a HTTP request and return the server's response.
    ///
    /// You must have a valid host before sending a request (see see_host).
    /// Any missing mandatory header field in the request will be added
    /// with an appropriate value.
    /// Warning: this function waits for the server's response and may
    /// not return instantly; use a thread if you don't want to block your
    /// application, or use a timeout to limit the time to wait. A value
    /// of 0s means that the client will use the system default timeout
    /// (which is usually pretty long).
    ///
    /// \param request Request to send
    /// \param timeout Maximum time to wait
    ///
    /// \return Server's response
    ///
    ////////////////////////////////////////////////////////////
    [[nodiscard]] Response send_request(const Request& request, Time timeout = 0s);

private:
    ////////////////////////////////////////////////////////////
    // Member data
    ////////////////////////////////////////////////////////////
    TcpSocket                m_connection; //!< Connection to the host
    std::optional<IpAddress> m_host;       //!< Web host address
    std::string              m_host_name;   //!< Web host name
    unsigned short           m_port{};     //!< Port used for connection with host
};

} // namespace cppnet


////////////////////////////////////////////////////////////
/// \class cppnet::Http
/// \ingroup network
///
/// cppnet::Http is a very simple HTTP client that allows you
/// to communicate with a web server. You can retrieve
/// web pages, send data to an interactive resource,
/// download a remote file, etc. The HTTPS protocol is
/// not supported.
///
/// The HTTP client is split into 3 classes:
/// \li cppnet::Http::Request
/// \li cppnet::Http::Response
/// \li cppnet::Http
///
/// cppnet::Http::Request builds the request that will be
/// sent to the server. A request is made of:
/// \li a method (what you want to do)
/// \li a target URI (usually the name of the web page or file)
/// \li one or more header fields (options that you can pass to the server)
/// \li an optional body (for POST requests)
///
/// cppnet::Http::Response parse the response from the web server
/// and provides getters to read them. The response contains:
/// \li a status code
/// \li header fields (that may be answers to the ones that you requested)
/// \li a body, which contains the contents of the requested resource
///
/// cppnet::Http provides a simple function, SendRequest, to send a
/// cppnet::Http::Request and return the corresponding cppnet::Http::Response
/// from the server.
///
/// Usage example:
/// \code
/// // Create a new HTTP client
/// cppnet::Http http;
///
/// // We'll work on http://cppnet.org
/// http.set_host("http://cppnet.org");
///
/// // Prepare a request to get the 'features.php' page
/// cppnet::Http::Request request("features.php");
///
/// // Send the request
/// cppnet::Http::Response response = http.send_request(request);
///
/// // Check the status code and display the result
/// cppnet::Http::Response::Status status = response.get_status();
/// if (status == cppnet::Http::Response::Status::Ok)
/// {
///     std::cout << response.get_body() << std::endl;
/// }
/// else
/// {
///     std::cout << "Error " << status << std::endl;
/// }
/// \endcode
///
////////////////////////////////////////////////////////////
