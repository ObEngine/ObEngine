#pragma once

#include <Types/Serializable.hpp>
#include <sol/sol.hpp>

namespace obe::script
{
    class LuaState : public sol::state
    {
    public:
        void load_config(const vili::node& config);
    };
} // namespace obe::script
