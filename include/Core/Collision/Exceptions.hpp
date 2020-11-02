#pragma once

#include <Exception.hpp>

namespace obe::Collision::Exceptions
{
    class InvalidTagFormat : public Exception
    {
    public:
        InvalidTagFormat(std::string_view colliderId, std::string_view tagType,
            std::string_view dataType, DebugInfo info)
            : Exception("InvalidTagFormat", info)
        {
            this->error(
                "Tried to set '{}' tags field with value of type '{}' on collider '{}'",
                tagType, dataType, colliderId);
            this->hint("The field should either be a string (for a unique tag) or an "
                       "array of strings (for multiple tags)");
        }
    };
}
