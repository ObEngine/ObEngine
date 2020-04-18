#pragma once

#include <Exception.hpp>
#include <vector>

namespace obe::Engine::Exceptions
{
    class BootScriptMissing : public Exception
    {
    public:
        BootScriptMissing(const std::vector<std::string>& mountedPaths, DebugInfo info)
            : Exception("BootScriptMissing", info)
        {
            this->error(
                "Unable to find a 'boot.lua' file which is required to start the engine");
            this->hint("ObEngine tried to fetch the 'boot.lua' file from the following "
                       "locations : ({})",
                fmt::join(mountedPaths, ", "));
        }
    };
}
