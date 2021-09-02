#include <Exception.hpp>

#include <string_view>

namespace obe::Config::Exceptions
{
    class InvalidVersionFormat : public Exception<InvalidVersionFormat>
    {
    public:
        using Exception::Exception;
        InvalidVersionFormat(std::string_view detail, DebugInfo info)
            : Exception(info)
        {
            this->error(
                "There is a problem with your version number : {}", detail);
        }
    };
}
