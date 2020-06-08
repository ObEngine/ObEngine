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

    class ImageFileNotFound : public Exception
    {
    public:
        ImageFileNotFound(std::string_view path, DebugInfo info)
            : Exception("ImageFileNotFound", info)
        {
            this->error("Image at path '{}' not found", path);
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

    class CanvasElementAlreadyExists : public Exception
    {
    public:
        CanvasElementAlreadyExists(std::string_view id, std::string_view newElementType,
            std::string_view existingElementType, DebugInfo info)
            : Exception("CanvasElementAlreadyExists", info)
        {
            this->error("Impossible to create a Canvas::{} with id '{}' as there is "
                        "already a Canvas::{} with the same id");
        }
    };

    class InvalidSpriteColorType : public Exception
    {
    public:
        InvalidSpriteColorType(std::string_view type, std::string_view value, DebugInfo info)
            : Exception("InvalidSpriteColorType ", info)
        {
            this->error("Invalid value for 'color' attribute, expected 'object' or 'string' and got '{}' (value: {})", type, value);
        }
    };
}