#include <Bindings/obe/Graphics/Exceptions/Exceptions.hpp>

#include <Graphics/Exceptions.hpp>

#include <Bindings/Config.hpp>

namespace obe::graphics::exceptions::Bindings
{
    void LoadClassCanvasElementAlreadyExists(sol::state_view state)
    {
        sol::table ExceptionsNamespace = state["obe"]["graphics"]["exceptions"].get<sol::table>();
        sol::usertype<obe::graphics::exceptions::CanvasElementAlreadyExists>
            bindCanvasElementAlreadyExists = ExceptionsNamespace.new_usertype<
                obe::graphics::exceptions::CanvasElementAlreadyExists>("CanvasElementAlreadyExists",
                sol::call_constructor,
                sol::constructors<obe::graphics::exceptions::CanvasElementAlreadyExists(
                    std::string_view, std::string_view, std::string_view, obe::DebugInfo)>(),
                sol::base_classes,
                sol::bases<obe::Exception<obe::graphics::exceptions::CanvasElementAlreadyExists>,
                    obe::BaseException>());
    }
    void LoadClassImageFileNotFound(sol::state_view state)
    {
        sol::table ExceptionsNamespace = state["obe"]["graphics"]["exceptions"].get<sol::table>();
        sol::usertype<obe::graphics::exceptions::ImageFileNotFound> bindImageFileNotFound
            = ExceptionsNamespace.new_usertype<obe::graphics::exceptions::ImageFileNotFound>(
                "ImageFileNotFound", sol::call_constructor,
                sol::constructors<obe::graphics::exceptions::ImageFileNotFound(
                    std::string_view, obe::DebugInfo)>(),
                sol::base_classes,
                sol::bases<obe::Exception<obe::graphics::exceptions::ImageFileNotFound>,
                    obe::BaseException>());
    }
    void LoadClassInvalidColorName(sol::state_view state)
    {
        sol::table ExceptionsNamespace = state["obe"]["graphics"]["exceptions"].get<sol::table>();
        sol::usertype<obe::graphics::exceptions::InvalidColorName> bindInvalidColorName
            = ExceptionsNamespace.new_usertype<obe::graphics::exceptions::InvalidColorName>(
                "InvalidColorName", sol::call_constructor,
                sol::constructors<obe::graphics::exceptions::InvalidColorName(
                    std::string_view, obe::DebugInfo)>(),
                sol::base_classes,
                sol::bases<obe::Exception<obe::graphics::exceptions::InvalidColorName>,
                    obe::BaseException>());
    }
    void LoadClassInvalidHexFormat(sol::state_view state)
    {
        sol::table ExceptionsNamespace = state["obe"]["graphics"]["exceptions"].get<sol::table>();
        sol::usertype<obe::graphics::exceptions::InvalidHexFormat> bindInvalidHexFormat
            = ExceptionsNamespace.new_usertype<obe::graphics::exceptions::InvalidHexFormat>(
                "InvalidHexFormat", sol::call_constructor,
                sol::constructors<obe::graphics::exceptions::InvalidHexFormat(
                    std::string_view, obe::DebugInfo)>(),
                sol::base_classes,
                sol::bases<obe::Exception<obe::graphics::exceptions::InvalidHexFormat>,
                    obe::BaseException>());
    }
    void LoadClassInvalidHsvFormat(sol::state_view state)
    {
        sol::table ExceptionsNamespace = state["obe"]["graphics"]["exceptions"].get<sol::table>();
        sol::usertype<obe::graphics::exceptions::InvalidHsvFormat> bindInvalidHsvFormat
            = ExceptionsNamespace.new_usertype<obe::graphics::exceptions::InvalidHsvFormat>(
                "InvalidHsvFormat", sol::call_constructor,
                sol::constructors<obe::graphics::exceptions::InvalidHsvFormat(
                    const int, const double, const double, obe::DebugInfo)>(),
                sol::base_classes,
                sol::bases<obe::Exception<obe::graphics::exceptions::InvalidHsvFormat>,
                    obe::BaseException>());
    }
    void LoadClassInvalidRgbFormat(sol::state_view state)
    {
        sol::table ExceptionsNamespace = state["obe"]["graphics"]["exceptions"].get<sol::table>();
        sol::usertype<obe::graphics::exceptions::InvalidRgbFormat> bindInvalidRgbFormat
            = ExceptionsNamespace.new_usertype<obe::graphics::exceptions::InvalidRgbFormat>(
                "InvalidRgbFormat", sol::call_constructor,
                sol::constructors<obe::graphics::exceptions::InvalidRgbFormat(
                    const double, const double, const double, const double, obe::DebugInfo)>(),
                sol::base_classes,
                sol::bases<obe::Exception<obe::graphics::exceptions::InvalidRgbFormat>,
                    obe::BaseException>());
    }
    void LoadClassInvalidSpriteColorType(sol::state_view state)
    {
        sol::table ExceptionsNamespace = state["obe"]["graphics"]["exceptions"].get<sol::table>();
        sol::usertype<obe::graphics::exceptions::InvalidSpriteColorType> bindInvalidSpriteColorType
            = ExceptionsNamespace.new_usertype<obe::graphics::exceptions::InvalidSpriteColorType>(
                "InvalidSpriteColorType", sol::call_constructor,
                sol::constructors<obe::graphics::exceptions::InvalidSpriteColorType(
                    std::string_view, std::string_view, obe::DebugInfo)>(),
                sol::base_classes,
                sol::bases<obe::Exception<obe::graphics::exceptions::InvalidSpriteColorType>,
                    obe::BaseException>());
    }
    void LoadClassReadOnlyTexture(sol::state_view state)
    {
        sol::table ExceptionsNamespace = state["obe"]["graphics"]["exceptions"].get<sol::table>();
        sol::usertype<obe::graphics::exceptions::ReadOnlyTexture> bindReadOnlyTexture
            = ExceptionsNamespace.new_usertype<obe::graphics::exceptions::ReadOnlyTexture>(
                "ReadOnlyTexture", sol::call_constructor,
                sol::constructors<obe::graphics::exceptions::ReadOnlyTexture(
                    std::string_view, obe::DebugInfo)>(),
                sol::base_classes,
                sol::bases<obe::Exception<obe::graphics::exceptions::ReadOnlyTexture>,
                    obe::BaseException>());
    }
};