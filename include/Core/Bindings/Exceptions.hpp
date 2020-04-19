#pragma once

#include <Exception.hpp>
#include <vector>

namespace obe::Bindings::Exceptions
{
    class BindingTreeNodeNotFound : public Exception
    {
    public:
        BindingTreeNodeNotFound(std::string_view id, std::string_view childId,
            std::vector<std::string> children, DebugInfo info)
            : Exception("BindingTreeNodeNotFound", info)
        {
            this->error(
                "BindingTree node '{}' could not find a child with id '{}'", id, childId);
            this->hint("BindingTree Node '{}' contains the following children ({})", id,
                fmt::join(children, ", "));
        }
    };
}