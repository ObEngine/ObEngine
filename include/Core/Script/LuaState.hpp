#pragma once

#include <sol/sol.hpp>

#include <Types/Serializable.hpp>

namespace obe::script
{
    class LuaState : public sol::state
    {
    public:
        void load_config(const vili::node& config);
    };
}
