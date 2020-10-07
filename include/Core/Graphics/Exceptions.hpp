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

    class InvalidRgbFormat : public Exception
    {
    public:
        InvalidRgbFormat(const double r, const double g, const double b, const double a,
            DebugInfo info)
            : Exception("InvalidRgbFormat", info)
        {
            this->error("Invalid RGB format, values should be between 0 and 255, got "
                        "[r={}, g={}, b={}, a={}]",
                r, g, b, a);
        }
    };

    class InvalidHsvFormat : public Exception
    {
    public:
        InvalidHsvFormat(const int H, const double S, const double V, DebugInfo info)
            : Exception("InvalidHsvFormat", info)
        {
            this->error(
                "Invalid HSV format, values should be between 0 and 365 for Hue and 0.0 "
                "and 1.0 for Saturation and Value, got [H={}, S={}, V={}]",
                H, S, V);
        }
    };

    class InvalidHexFormat : public Exception
    {
    public:
        InvalidHexFormat(std::string_view hexCode, DebugInfo info)
            : Exception("InvalidHexFormat", info)
        {
            this->error(
                "Impossible to find a color with following hexadecimal code : '{}'",
                hexCode);
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
        InvalidSpriteColorType(
            std::string_view type, std::string_view value, DebugInfo info)
            : Exception("InvalidSpriteColorType ", info)
        {
            this->error("Invalid value for 'color' attribute, expected 'object' or "
                        "'string' and got '{}' (value: {})",
                type, value);
        }
    };
}