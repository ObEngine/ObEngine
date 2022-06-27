#pragma once

#include <Exception.hpp>

/**
 * \nobind
 */
namespace obe::collision::Exceptions
{
    class InvalidTagFormat : public Exception<InvalidTagFormat>
    {
    public:
        using Exception::Exception;
        InvalidTagFormat(std::string_view collider_id, std::string_view tag_type,
            std::string_view data_type, DebugInfo info)
            : Exception(info)
        {
            this->error("Tried to set '{}' tags field with value of type '{}' on collider '{}'",
                tag_type, data_type, collider_id);
            this->hint("The field should either be a string (for a unique tag) or an "
                       "array of strings (for multiple tags)");
        }
    };
}
