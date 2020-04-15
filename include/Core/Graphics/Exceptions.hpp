#pragma once

#include <Exception.hpp>

namespace obe::Graphics::Exceptions
{
    class ReadOnlyTexture : public Exception
    {
    public:
        ReadOnlyTexture(std::string_view method, DebugInfo info)
            : Exception("ReadOnlyTexture", info)
        {
            this->error(
                "Impossible to call method Texture::{} when Texture is in readonly-mode",
                method);
        }
    };

    class InvalidColorName : public Exception
    {
    public:
        InvalidColorName(std::string_view color, DebugInfo info)
            : Exception("InvalidColorName", info)
        {
            this->error(
                "Impossible to find a color with the following name : '{}'", color);
        }
    };
}