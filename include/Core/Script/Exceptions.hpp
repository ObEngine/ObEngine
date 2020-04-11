#pragma once

#include <fmt/format.h>
#include <string_view>

#include <Animation/Animation.hpp>
#include <Exception.hpp>

namespace obe::Script::Exceptions
{
    class NoScriptComponent : public Exception
    {
    public:
        NoScriptComponent(std::string_view type, std::string_view id, DebugInfo info)
            : Exception("NoScriptComponent", info)
        {
            this->error("GameObject '{}' (type: '{}') has no Script component", type, id);
            this->hint("Try to check in the {}.obj.vili if you correctly created the "
                       "Script section",
                type);
        }
    };
}