#pragma once

#include <vili/node.hpp>

namespace obe::Config
{
    class ConfigurationManager
    {
    private:
        vili::node m_config;

    public:
        ConfigurationManager();
        void load();
        vili::node get() const;
    };
} // namespace obe::System