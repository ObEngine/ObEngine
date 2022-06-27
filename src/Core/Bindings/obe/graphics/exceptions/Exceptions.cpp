#include <Bindings/obe/graphics/exceptions/Exceptions.hpp>

#include <Graphics/Exceptions.hpp>

#include <Bindings/Config.hpp>

namespace obe::graphics::exceptions::bindings
{
    void load_class_canvas_element_already_exists(sol::state_view state)
    {
        sol::table exceptions_namespace = state["obe"]["graphics"]["exceptions"].get<sol::table>();
        sol::usertype<obe::graphics::exceptions::CanvasElementAlreadyExists>
            bind_canvas_element_already_exists = exceptions_namespace.new_usertype<
                obe::graphics::exceptions::CanvasElementAlreadyExists>("CanvasElementAlreadyExists",
                sol::call_constructor,
                sol::constructors<obe::graphics::exceptions::CanvasElementAlreadyExists(
                    std::string_view, std::string_view, std::string_view, obe::DebugInfo)>(),
                sol::base_classes,
                sol::bases<obe::Exception<obe::graphics::exceptions::CanvasElementAlreadyExists>,
                    obe::BaseException>());
    }
    void load_class_image_file_not_found(sol::state_view state)
    {
        sol::table exceptions_namespace = state["obe"]["graphics"]["exceptions"].get<sol::table>();
        sol::usertype<obe::graphics::exceptions::ImageFileNotFound> bind_image_file_not_found
            = exceptions_namespace.new_usertype<obe::graphics::exceptions::ImageFileNotFound>(
                "ImageFileNotFound", sol::call_constructor,
                sol::constructors<obe::graphics::exceptions::ImageFileNotFound(
                    std::string_view, obe::DebugInfo)>(),
                sol::base_classes,
                sol::bases<obe::Exception<obe::graphics::exceptions::ImageFileNotFound>,
                    obe::BaseException>());
    }
    void load_class_invalid_color_name(sol::state_view state)
    {
        sol::table exceptions_namespace = state["obe"]["graphics"]["exceptions"].get<sol::table>();
        sol::usertype<obe::graphics::exceptions::InvalidColorName> bind_invalid_color_name
            = exceptions_namespace.new_usertype<obe::graphics::exceptions::InvalidColorName>(
                "InvalidColorName", sol::call_constructor,
                sol::constructors<obe::graphics::exceptions::InvalidColorName(
                    std::string_view, obe::DebugInfo)>(),
                sol::base_classes,
                sol::bases<obe::Exception<obe::graphics::exceptions::InvalidColorName>,
                    obe::BaseException>());
    }
    void load_class_invalid_hex_format(sol::state_view state)
    {
        sol::table exceptions_namespace = state["obe"]["graphics"]["exceptions"].get<sol::table>();
        sol::usertype<obe::graphics::exceptions::InvalidHexFormat> bind_invalid_hex_format
            = exceptions_namespace.new_usertype<obe::graphics::exceptions::InvalidHexFormat>(
                "InvalidHexFormat", sol::call_constructor,
                sol::constructors<obe::graphics::exceptions::InvalidHexFormat(
                    std::string_view, obe::DebugInfo)>(),
                sol::base_classes,
                sol::bases<obe::Exception<obe::graphics::exceptions::InvalidHexFormat>,
                    obe::BaseException>());
    }
    void load_class_invalid_hsv_format(sol::state_view state)
    {
        sol::table exceptions_namespace = state["obe"]["graphics"]["exceptions"].get<sol::table>();
        sol::usertype<obe::graphics::exceptions::InvalidHsvFormat> bind_invalid_hsv_format
            = exceptions_namespace.new_usertype<obe::graphics::exceptions::InvalidHsvFormat>(
                "InvalidHsvFormat", sol::call_constructor,
                sol::constructors<obe::graphics::exceptions::InvalidHsvFormat(
                    const int, const double, const double, obe::DebugInfo)>(),
                sol::base_classes,
                sol::bases<obe::Exception<obe::graphics::exceptions::InvalidHsvFormat>,
                    obe::BaseException>());
    }
    void load_class_invalid_rgb_format(sol::state_view state)
    {
        sol::table exceptions_namespace = state["obe"]["graphics"]["exceptions"].get<sol::table>();
        sol::usertype<obe::graphics::exceptions::InvalidRgbFormat> bind_invalid_rgb_format
            = exceptions_namespace.new_usertype<obe::graphics::exceptions::InvalidRgbFormat>(
                "InvalidRgbFormat", sol::call_constructor,
                sol::constructors<obe::graphics::exceptions::InvalidRgbFormat(
                    const double, const double, const double, const double, obe::DebugInfo)>(),
                sol::base_classes,
                sol::bases<obe::Exception<obe::graphics::exceptions::InvalidRgbFormat>,
                    obe::BaseException>());
    }
    void load_class_invalid_sprite_color_type(sol::state_view state)
    {
        sol::table exceptions_namespace = state["obe"]["graphics"]["exceptions"].get<sol::table>();
        sol::usertype<obe::graphics::exceptions::InvalidSpriteColorType>
            bind_invalid_sprite_color_type
            = exceptions_namespace.new_usertype<obe::graphics::exceptions::InvalidSpriteColorType>(
                "InvalidSpriteColorType", sol::call_constructor,
                sol::constructors<obe::graphics::exceptions::InvalidSpriteColorType(
                    std::string_view, std::string_view, obe::DebugInfo)>(),
                sol::base_classes,
                sol::bases<obe::Exception<obe::graphics::exceptions::InvalidSpriteColorType>,
                    obe::BaseException>());
    }
    void load_class_read_only_texture(sol::state_view state)
    {
        sol::table exceptions_namespace = state["obe"]["graphics"]["exceptions"].get<sol::table>();
        sol::usertype<obe::graphics::exceptions::ReadOnlyTexture> bind_read_only_texture
            = exceptions_namespace.new_usertype<obe::graphics::exceptions::ReadOnlyTexture>(
                "ReadOnlyTexture", sol::call_constructor,
                sol::constructors<obe::graphics::exceptions::ReadOnlyTexture(
                    std::string_view, obe::DebugInfo)>(),
                sol::base_classes,
                sol::bases<obe::Exception<obe::graphics::exceptions::ReadOnlyTexture>,
                    obe::BaseException>());
    }
};