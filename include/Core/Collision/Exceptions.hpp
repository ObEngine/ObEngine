#pragma once

#include <Exception.hpp>

/**
 * \nobind
 */
namespace obe::collision::exceptions
{
    class InvalidTagFormat : public Exception<InvalidTagFormat>
    {
    public:
        using Exception::Exception;
        InvalidTagFormat(std::string_view collider_id, std::string_view tag_type,
            std::string_view data_type,
            std::source_location location = std::source_location::current())
            : Exception(location)
        {
            this->error("Tried to set '{}' tags field with value of type '{}' on collider '{}'",
                tag_type, data_type, collider_id);
            this->hint("The field should either be a string (for a unique tag) or an "
                       "array of strings (for multiple tags)");
        }
    };

    class TooManyPolygonColliderPoints : public Exception<TooManyPolygonColliderPoints>
    {
    public:
        using Exception::Exception;
        TooManyPolygonColliderPoints(std::string_view collider_id, std::string_view tag_type,
            std::string_view data_type,
            std::source_location location = std::source_location::current())
            : Exception(location)
        {
            this->error("Tried to set '{}' tags field with value of type '{}' on collider '{}'",
                tag_type, data_type, collider_id);
            this->hint("The field should either be a string (for a unique tag) or an "
                       "array of strings (for multiple tags)");
        }
    };

    class InvalidColliderComponentType : public Exception<InvalidColliderComponentType>
    {
    public:
        using Exception::Exception;
        InvalidColliderComponentType(std::string_view component_id, std::string_view collider_type,
            std::source_location location = std::source_location::current())
            : Exception(location)
        {
            this->error("Tried to use incompatible ColliderType '{}' for Component '{}'",
                collider_type, component_id);
        }
    };

    class InvalidColliderType : public Exception<InvalidColliderType>
    {
    public:
        using Exception::Exception;
        InvalidColliderType(std::string_view collider_type,
            std::source_location location = std::source_location::current())
            : Exception(location)
        {
            this->error("Tried to use incompatible ColliderType '{}'", collider_type);
        }
    };

    class TrajectoryAlreadyExists : public Exception<TrajectoryAlreadyExists>
    {
    public:
        using Exception::Exception;
        TrajectoryAlreadyExists(std::string_view trajectory_name,
            std::source_location location = std::source_location::current())
            : Exception(location)
        {
            this->error("Trajectory with name '{}' already exists", trajectory_name);
        }
    };
} // namespace obe::collision::exceptions
