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
}