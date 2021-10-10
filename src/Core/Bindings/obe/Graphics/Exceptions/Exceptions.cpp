#include <Bindings/obe/Graphics/Exceptions/Exceptions.hpp>

#include <Graphics/Exceptions.hpp>

#include <Bindings/Config.hpp>

namespace obe::Graphics::Exceptions::Bindings
{
    void LoadClassCanvasElementAlreadyExists(sol::state_view state)
    {
        sol::table ExceptionsNamespace = state["obe"]["Graphics"]["Exceptions"].get<sol::table>();
        sol::usertype<obe::Graphics::Exceptions::CanvasElementAlreadyExists>
            bindCanvasElementAlreadyExists
            = ExceptionsNamespace
                  .new_usertype<obe::Graphics::Exceptions::CanvasElementAlreadyExists>(
                      "CanvasElementAlreadyExists", sol::call_constructor,
                      sol::constructors<obe::Graphics::Exceptions::CanvasElementAlreadyExists(
                          std::string_view, std::string_view, std::string_view, obe::DebugInfo)>(),
                      sol::base_classes,
                      sol::bases<obe::Exception<CanvasElementAlreadyExists>, obe::BaseException>());
    }
    void LoadClassImageFileNotFound(sol::state_view state)
    {
        sol::table ExceptionsNamespace = state["obe"]["Graphics"]["Exceptions"].get<sol::table>();
        sol::usertype<obe::Graphics::Exceptions::ImageFileNotFound> bindImageFileNotFound
            = ExceptionsNamespace.new_usertype<obe::Graphics::Exceptions::ImageFileNotFound>(
                "ImageFileNotFound", sol::call_constructor,
                sol::constructors<obe::Graphics::Exceptions::ImageFileNotFound(
                    std::string_view, obe::DebugInfo)>(),
                sol::base_classes,
                sol::bases<obe::Exception<ImageFileNotFound>, obe::BaseException>());
    }
    void LoadClassInvalidColorName(sol::state_view state)
    {
        sol::table ExceptionsNamespace = state["obe"]["Graphics"]["Exceptions"].get<sol::table>();
        sol::usertype<obe::Graphics::Exceptions::InvalidColorName> bindInvalidColorName
            = ExceptionsNamespace.new_usertype<obe::Graphics::Exceptions::InvalidColorName>(
                "InvalidColorName", sol::call_constructor,
                sol::constructors<obe::Graphics::Exceptions::InvalidColorName(
                    std::string_view, obe::DebugInfo)>(),
                sol::base_classes,
                sol::bases<obe::Exception<InvalidColorName>, obe::BaseException>());
    }
    void LoadClassInvalidHexFormat(sol::state_view state)
    {
        sol::table ExceptionsNamespace = state["obe"]["Graphics"]["Exceptions"].get<sol::table>();
        sol::usertype<obe::Graphics::Exceptions::InvalidHexFormat> bindInvalidHexFormat
            = ExceptionsNamespace.new_usertype<obe::Graphics::Exceptions::InvalidHexFormat>(
                "InvalidHexFormat", sol::call_constructor,
                sol::constructors<obe::Graphics::Exceptions::InvalidHexFormat(
                    std::string_view, obe::DebugInfo)>(),
                sol::base_classes,
                sol::bases<obe::Exception<InvalidHexFormat>, obe::BaseException>());
    }
    void LoadClassInvalidHsvFormat(sol::state_view state)
    {
        sol::table ExceptionsNamespace = state["obe"]["Graphics"]["Exceptions"].get<sol::table>();
        sol::usertype<obe::Graphics::Exceptions::InvalidHsvFormat> bindInvalidHsvFormat
            = ExceptionsNamespace.new_usertype<obe::Graphics::Exceptions::InvalidHsvFormat>(
                "InvalidHsvFormat", sol::call_constructor,
                sol::constructors<obe::Graphics::Exceptions::InvalidHsvFormat(
                    const int, const double, const double, obe::DebugInfo)>(),
                sol::base_classes,
                sol::bases<obe::Exception<InvalidHsvFormat>, obe::BaseException>());
    }
    void LoadClassInvalidRgbFormat(sol::state_view state)
    {
        sol::table ExceptionsNamespace = state["obe"]["Graphics"]["Exceptions"].get<sol::table>();
        sol::usertype<obe::Graphics::Exceptions::InvalidRgbFormat> bindInvalidRgbFormat
            = ExceptionsNamespace.new_usertype<obe::Graphics::Exceptions::InvalidRgbFormat>(
                "InvalidRgbFormat", sol::call_constructor,
                sol::constructors<obe::Graphics::Exceptions::InvalidRgbFormat(
                    const double, const double, const double, const double, obe::DebugInfo)>(),
                sol::base_classes,
                sol::bases<obe::Exception<InvalidRgbFormat>, obe::BaseException>());
    }
    void LoadClassInvalidSpriteColorType(sol::state_view state)
    {
        sol::table ExceptionsNamespace = state["obe"]["Graphics"]["Exceptions"].get<sol::table>();
        sol::usertype<obe::Graphics::Exceptions::InvalidSpriteColorType> bindInvalidSpriteColorType
            = ExceptionsNamespace.new_usertype<obe::Graphics::Exceptions::InvalidSpriteColorType>(
                "InvalidSpriteColorType", sol::call_constructor,
                sol::constructors<obe::Graphics::Exceptions::InvalidSpriteColorType(
                    std::string_view, std::string_view, obe::DebugInfo)>(),
                sol::base_classes,
                sol::bases<obe::Exception<InvalidSpriteColorType>, obe::BaseException>());
    }
    void LoadClassReadOnlyTexture(sol::state_view state)
    {
        sol::table ExceptionsNamespace = state["obe"]["Graphics"]["Exceptions"].get<sol::table>();
        sol::usertype<obe::Graphics::Exceptions::ReadOnlyTexture> bindReadOnlyTexture
            = ExceptionsNamespace.new_usertype<obe::Graphics::Exceptions::ReadOnlyTexture>(
                "ReadOnlyTexture", sol::call_constructor,
                sol::constructors<obe::Graphics::Exceptions::ReadOnlyTexture(
                    std::string_view, obe::DebugInfo)>(),
                sol::base_classes,
                sol::bases<obe::Exception<ReadOnlyTexture>, obe::BaseException>());
    }
};