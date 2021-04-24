#pragma once

#include <vili/node.hpp>

namespace obe::Config
{
    class ConfigurationManager : public vili::node
    {
    public:
        ConfigurationManager();
        void load();
    };
} // namespace obe::System