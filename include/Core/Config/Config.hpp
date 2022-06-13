#pragma once

#include <vili/node.hpp>

namespace obe::config
{
    class ConfigurationManager : public vili::node
    {
    public:
        ConfigurationManager();
        void load();
    };
} // namespace obe::system
