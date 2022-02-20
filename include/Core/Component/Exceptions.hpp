#pragma once

#include <Exception.hpp>

namespace obe::Component::Exceptions
{
    class ComponentIdAlreadyTaken : public Exception<ComponentIdAlreadyTaken>
    {
    public:
        using Exception::Exception;
        ComponentIdAlreadyTaken(std::string_view id, DebugInfo info)
            : Exception(info)
        {
            this->error("Component with id '{}' already exists");
        }
    };

    class UnknownComponentType : public Exception<UnknownComponentType>
    {
    public:
        using Exception::Exception;
        UnknownComponentType(std::string_view componentType, DebugInfo info)
            : Exception(info)
        {
            this->error("Component with type '{}' does not exists or has not been registered");
        }
    };
}
