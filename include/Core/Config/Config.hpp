#pragma once

#include <vili/ViliParser.hpp>

namespace obe::Config
{
    /*
     * \brief Data Object containing the engine configuration
     */
    extern vili::ViliParser Config;
    /*
     * \brief Function to read the configuration from all config files
     */
    void InitConfiguration();
} // namespace obe::System