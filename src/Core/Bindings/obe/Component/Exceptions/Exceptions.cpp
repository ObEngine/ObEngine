#include <Bindings/obe/Component/Exceptions/Exceptions.hpp>

#include <Component/Exceptions.hpp>

#include <Bindings/Config.hpp>

namespace obe::Component::Exceptions::bindings
{
    void load_class_component_id_already_taken(sol::state_view state)
    {
        sol::table Exceptions_namespace = state["obe"]["Component"]["Exceptions"].get<sol::table>();
        sol::usertype<obe::Component::Exceptions::ComponentIdAlreadyTaken>
            bind_component_id_already_taken = Exceptions_namespace.new_usertype<
                obe::Component::Exceptions::ComponentIdAlreadyTaken>("ComponentIdAlreadyTaken",
                sol::call_constructor,
                sol::constructors<obe::Component::Exceptions::ComponentIdAlreadyTaken(
                    std::string_view, obe::DebugInfo)>(),
                sol::base_classes,
                sol::bases<obe::Exception<obe::Component::Exceptions::ComponentIdAlreadyTaken>,
                    obe::BaseException>());
    }
    void load_class_unknown_component_type(sol::state_view state)
    {
        sol::table Exceptions_namespace = state["obe"]["Component"]["Exceptions"].get<sol::table>();
        sol::usertype<obe::Component::Exceptions::UnknownComponentType> bind_unknown_component_type
            = Exceptions_namespace.new_usertype<obe::Component::Exceptions::UnknownComponentType>(
                "UnknownComponentType", sol::call_constructor,
                sol::constructors<obe::Component::Exceptions::UnknownComponentType(
                    std::string_view, obe::DebugInfo)>(),
                sol::base_classes,
                sol::bases<obe::Exception<obe::Component::Exceptions::UnknownComponentType>,
                    obe::BaseException>());
    }
};