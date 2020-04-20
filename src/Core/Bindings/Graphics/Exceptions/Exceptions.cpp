#include <Bindings/Graphics/Exceptions/Exceptions.hpp>

#include <Graphics/Exceptions.hpp>

#include <sol/sol.hpp>

namespace obe::Graphics::Exceptions::Bindings
{
    void LoadClassCanvasElementAlreadyExists(sol::state_view state)
    {
        sol::table ExceptionsNamespace
            = state["obe"]["Graphics"]["Exceptions"].get<sol::table>();
        sol::usertype<obe::Graphics::Exceptions::CanvasElementAlreadyExists>
            bindCanvasElementAlreadyExists = ExceptionsNamespace.new_usertype<
                obe::Graphics::Exceptions::CanvasElementAlreadyExists>(
                "CanvasElementAlreadyExists", sol::call_constructor,
                sol::constructors<obe::Graphics::Exceptions::CanvasElementAlreadyExists(
                    std::string_view, std::string_view, std::string_view,
                    obe::DebugInfo)>(),
                sol::base_classes, sol::bases<obe::Exception>());
    }
    void LoadClassInvalidColorName(sol::state_view state)
    {
        sol::table ExceptionsNamespace
            = state["obe"]["Graphics"]["Exceptions"].get<sol::table>();
        sol::usertype<obe::Graphics::Exceptions::InvalidColorName> bindInvalidColorName
            = ExceptionsNamespace
                  .new_usertype<obe::Graphics::Exceptions::InvalidColorName>(
                      "InvalidColorName", sol::call_constructor,
                      sol::constructors<obe::Graphics::Exceptions::InvalidColorName(
                          std::string_view, obe::DebugInfo)>(),
                      sol::base_classes, sol::bases<obe::Exception>());
    }
    void LoadClassReadOnlyTexture(sol::state_view state)
    {
        sol::table ExceptionsNamespace
            = state["obe"]["Graphics"]["Exceptions"].get<sol::table>();
        sol::usertype<obe::Graphics::Exceptions::ReadOnlyTexture> bindReadOnlyTexture
            = ExceptionsNamespace
                  .new_usertype<obe::Graphics::Exceptions::ReadOnlyTexture>(
                      "ReadOnlyTexture", sol::call_constructor,
                      sol::constructors<obe::Graphics::Exceptions::ReadOnlyTexture(
                          std::string_view, obe::DebugInfo)>(),
                      sol::base_classes, sol::bases<obe::Exception>());
    }
};