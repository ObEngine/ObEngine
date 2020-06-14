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

    class BootScriptLoadingError : public Exception
    {
    public:
        BootScriptLoadingError(std::string_view errorMessage, DebugInfo info)
            : Exception("BootScriptLoadingError", info)
        {
            this->error(
                "Lua error while loading 'boot.lua' script file :\n{}", errorMessage);
        }
    };

    class BootScriptExecutionError : public Exception
    {
    public:
        BootScriptExecutionError(
            std::string_view functionName, std::string_view errorMessage, DebugInfo info)
            : Exception("BootScriptExecutionError", info)
        {
            this->error(
                "Lua error while executing a function named '{}' in 'boot.lua' :\n{}",
                functionName, errorMessage);
        }
    };

    class TextureNotFound : public Exception
    {
    public:
        TextureNotFound(
            std::string_view path, std::vector<std::string> mounts, DebugInfo info)
            : Exception("TextureNotFound", info)
        {
            this->error("Could not find Texture with path '{}'", path);
            this->hint("The following paths were used to search for the Texture ({})",
                fmt::join(mounts, ", "));
        }
    };

    class FontNotFound : public Exception
    {
    public:
        FontNotFound(
            std::string_view path, std::vector<std::string> mounts, DebugInfo info)
            : Exception("FontNotFound", info)
        {
            this->error("Could not find Font with path '{}'", path);
            this->hint("The following paths were used to search for the Font ({})",
                fmt::join(mounts, ", "));
        }
    };

    class UnitializedEngine : public Exception
    {
    public:
        UnitializedEngine(DebugInfo info)
            : Exception("UnitializedEngine", info)
        {
            this->error("Impossible to run Engine if not initialized beforehand");
        }
    };
}
