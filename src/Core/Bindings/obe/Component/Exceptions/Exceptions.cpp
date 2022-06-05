#include <Bindings/obe/Component/Exceptions/Exceptions.hpp>

#include <Component/Exceptions.hpp>

#include <Bindings/Config.hpp>

namespace obe::Component::Exceptions::Bindings
{
    void LoadClassComponentIdAlreadyTaken(sol::state_view state)
    {
        sol::table ExceptionsNamespace = state["obe"]["Component"]["Exceptions"].get<sol::table>();
        sol::usertype<obe::Component::Exceptions::ComponentIdAlreadyTaken>
            bindComponentIdAlreadyTaken
            = ExceptionsNamespace.new_usertype<obe::Component::Exceptions::ComponentIdAlreadyTaken>(
                "ComponentIdAlreadyTaken", sol::call_constructor,
                sol::constructors<obe::Component::Exceptions::ComponentIdAlreadyTaken(
                    std::string_view, obe::DebugInfo)>(),
                sol::base_classes,
                sol::bases<obe::Exception<obe::Component::Exceptions::ComponentIdAlreadyTaken>,
                    obe::BaseException>());
    }
    void LoadClassUnknownComponentType(sol::state_view state)
    {
        sol::table ExceptionsNamespace = state["obe"]["Component"]["Exceptions"].get<sol::table>();
        sol::usertype<obe::Component::Exceptions::UnknownComponentType> bindUnknownComponentType
            = ExceptionsNamespace.new_usertype<obe::Component::Exceptions::UnknownComponentType>(
                "UnknownComponentType", sol::call_constructor,
                sol::constructors<obe::Component::Exceptions::UnknownComponentType(
                    std::string_view, obe::DebugInfo)>(),
                sol::base_classes,
                sol::bases<obe::Exception<obe::Component::Exceptions::UnknownComponentType>,
                    obe::BaseException>());
    }
};