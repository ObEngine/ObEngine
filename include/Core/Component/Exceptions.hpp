#pragma once

#include <Exception.hpp>

namespace obe::Component::Exceptions
{
    class ComponentIdAlreadyTaken : public Exception
    {
    public:
        ComponentIdAlreadyTaken(std::string_view id, DebugInfo info)
            : Exception("ComponentIdAlreadyTaken", info)
        {
            this->error("Component with id '{}' already exists");
        }
    };
}