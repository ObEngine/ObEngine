#pragma once

#include <vili/ViliParser.hpp>

namespace obe::Config
{
    class ConfigurationManager
    {
    private:
        vili::ViliParser m_config;

    public:
        ConfigurationManager();
        void load();
        vili::ComplexNode& get() const;
    };
} // namespace obe::System