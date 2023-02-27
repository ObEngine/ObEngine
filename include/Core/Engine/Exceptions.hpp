#pragma once

#include <Exception.hpp>
#include <vector>

/**
 * \nobind
 */
namespace obe::engine::exceptions
{
    class BootScriptMissing : public Exception<BootScriptMissing>
    {
    public:
        using Exception::Exception;
        BootScriptMissing(const std::vector<std::string>& mounted_paths,
            std::source_location location = std::source_location::current())
            : Exception(location)
        {
            this->error("Unable to find a 'boot.lua' file which is required to start the engine");
            this->hint("ObEngine tried to fetch the 'boot.lua' file from the following "
                       "locations : ({})",
                fmt::join(mounted_paths, ", "));
        }
    };

    class BootScriptLoadingError : public Exception<BootScriptLoadingError>
    {
    public:
        using Exception::Exception;
        BootScriptLoadingError(std::string_view error_message,
            std::source_location location = std::source_location::current())
            : Exception(location)
        {
            this->error("Lua error while loading 'boot.lua' script file :\n{}", error_message);
        }
    };

    class BootScriptExecutionError : public Exception<BootScriptExecutionError>
    {
    public:
        using Exception::Exception;
        BootScriptExecutionError(std::source_location location = std::source_location::current())
            : Exception(location)
        {
            this->error("Lua error occured while running 'boot.lua'");
        }
    };

    class TextureNotFound : public Exception<TextureNotFound>
    {
    public:
        using Exception::Exception;
        TextureNotFound(
            std::string_view path, std::source_location location = std::source_location::current())
            : Exception(location)
        {
            this->error("Could not load Texture with path '{}'", path);
        }
    };

    class FontNotFound : public Exception<FontNotFound>
    {
    public:
        using Exception::Exception;
        FontNotFound(std::string_view path, std::vector<std::string> mounts,
            std::source_location location = std::source_location::current())
            : Exception(location)
        {
            this->error("Could not find Font with path '{}'", path);
            this->hint("The following paths were used to search for the Font ({})",
                fmt::join(mounts, ", "));
        }
    };

    class UnitializedEngine : public Exception<UnitializedEngine>
    {
    public:
        using Exception::Exception;
        UnitializedEngine(std::source_location location = std::source_location::current())
            : Exception(location)
        {
            this->error("Impossible to run Engine if not initialized beforehand");
        }
    };
} // namespace obe::engine::exceptions
