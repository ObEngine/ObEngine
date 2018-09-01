#pragma once

#include <vili/ViliParser.hpp>

#include <Config.hpp>
#include <Types/Global.hpp>

namespace obe::System
{
    GLOBE(7, Config, vili::ViliParser);
    void InitConfiguration();
}
