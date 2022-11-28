#pragma once

#include <Exception.hpp>

/**
 * \nobind
 */
namespace obe::graphics::exceptions
{
    class ReadOnlyTexture : public Exception<ReadOnlyTexture>
    {
    public:
        using Exception::Exception;
        ReadOnlyTexture(std::string_view method, DebugInfo info)
            : Exception(info)
        {
            this->error(
                "Impossible to call method Texture::{} when Texture is in readonly-mode", method);
        }
    };

    class ImageFileNotFound : public Exception<ImageFileNotFound>
    {
    public:
        using Exception::Exception;
        ImageFileNotFound(std::string_view path, DebugInfo info)
            : Exception(info)
        {
            this->error("Image at path '{}' not found", path);
        }
    };

    class InvalidColorName : public Exception<InvalidColorName>
    {
    public:
        using Exception::Exception;
        InvalidColorName(std::string_view color, DebugInfo info)
            : Exception(info)
        {
            this->error("Impossible to find a color with the following name : '{}'", color);
        }
    };

    class InvalidRgbFormat : public Exception<InvalidRgbFormat>
    {
    public:
        using Exception::Exception;
        InvalidRgbFormat(
            const double r, const double g, const double b, const double a, DebugInfo info)
            : Exception(info)
        {
            this->error("Invalid RGB format, values should be between 0 and 255, got "
                        "[r={}, g={}, b={}, a={}]",
                r, g, b, a);
        }
    };

    class InvalidHsvFormat : public Exception<InvalidHsvFormat>
    {
    public:
        using Exception::Exception;
        InvalidHsvFormat(const int H, const double S, const double V, DebugInfo info)
            : Exception(info)
        {
            this->error("Invalid HSV format, values should be between 0 and 365 for Hue and 0.0 "
                        "and 1.0 for Saturation and Value, got [H={}, S={}, V={}]",
                H, S, V);
        }
    };

    class InvalidHexFormat : public Exception<InvalidHexFormat>
    {
    public:
        using Exception::Exception;
        InvalidHexFormat(std::string_view hex_code, DebugInfo info)
            : Exception(info)
        {
            this->error("Invalid Color hex code : '{}'", hex_code);
        }
    };

    class CanvasElementAlreadyExists : public Exception<CanvasElementAlreadyExists>
    {
    public:
        using Exception::Exception;
        CanvasElementAlreadyExists(std::string_view id, std::string_view new_element_type,
            std::string_view existing_element_type, DebugInfo info)
            : Exception(info)
        {
            this->error("Impossible to create a Canvas::{} with id '{}' as there is "
                        "already a Canvas::{} with the same id",
                new_element_type, id, existing_element_type);
        }
    };

    class InvalidSpriteColorType : public Exception<InvalidSpriteColorType>
    {
    public:
        using Exception::Exception;
        InvalidSpriteColorType(std::string_view type, std::string_view value, DebugInfo info)
            : Exception(info)
        {
            this->error("Invalid value for 'color' attribute, expected 'object' or "
                        "'string' and got '{}' (value: {})",
                type, value);
        }
    };

    class InvalidTexturePixelCoord : public Exception<InvalidTexturePixelCoord>
    {
    public:
        using Exception::Exception;
        InvalidTexturePixelCoord(uint32_t x, uint32_t y, uint32_t width, uint32_t height, DebugInfo info)
            : Exception(info)
        {
            this->error("Could not access pixel at coordinates (x: {}, y: {}) due to the texture size (width: {}, height: {})", x, y, width, height);
        }
    };
} // namespace obe::graphics::exceptions
