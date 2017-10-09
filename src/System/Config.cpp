#include <System/Config.hpp>
#include <System/Path.hpp>

#include <Debug/Logger.hpp>

namespace obe
{
    namespace System
    {
        vili::ViliParser Config;

        void InitConfiguration()
        {
            Config = vili::ViliParser();
            std::reverse(Path::MountedPaths.begin(), Path::MountedPaths.end());
            Path("Data/config.cfg.vili").loadResource(&Config, [](vili::ViliParser* obj, std::string path) -> int { obj->parseFile(path); return 0x002; });
            std::reverse(Path::MountedPaths.begin(), Path::MountedPaths.end());
        }
    }
}