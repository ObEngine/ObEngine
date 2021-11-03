#pragma once

#include <sol/sol.hpp>

#include <Types/Serializable.hpp>

namespace obe::Script
{
    class LuaState : public sol::state
    {
    public:
        void loadConfig(const vili::node& config);
    };
}
