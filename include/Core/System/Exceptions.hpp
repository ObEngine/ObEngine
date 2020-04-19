#pragma once

#include <Exception.hpp>
#include <vector>

namespace obe::System::Exceptions
{
    class ResourceNotFound : public Exception
    {
    public:
        ResourceNotFound(
            std::string_view path, std::vector<std::string> mounts, DebugInfo info)
            : Exception("ResourceNotFound", info)
        {
            this->error("Resource at path '{}' not found");
            this->hint("The following paths were used to search for the resource : ({})",
                fmt::join(mounts, ", "));
        }
    };
}
