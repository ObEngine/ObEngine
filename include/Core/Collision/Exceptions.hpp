#pragma once

#include <Exception.hpp>

namespace obe::collision::Exceptions
{
    class InvalidTagFormat : public Exception<InvalidTagFormat>
    {
    public:
        using Exception::Exception;
        InvalidTagFormat(std::string_view collider_id, std::string_view tagType,
            std::string_view dataType, DebugInfo info)
            : Exception(info)
        {
            this->error("Tried to set '{}' tags field with value of type '{}' on collider '{}'",
                tagType, dataType, collider_id);
            this->hint("The field should either be a string (for a unique tag) or an "
                       "array of strings (for multiple tags)");
        }
    };
}
