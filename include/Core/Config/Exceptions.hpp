#include <Exception.hpp>

#include <string_view>

namespace obe::Config::Exceptions
{
    class InvalidVersionNumber : public Exception
    {
    public:
        InvalidVersionNumber(std::string_view detail, DebugInfo info)
            : Exception("InvalidVersionNumber", info)
        {
            this->error(
                "There is a problem with your version number : {}", detail);
        }
    };
}
