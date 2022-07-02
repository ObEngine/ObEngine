#include <Bindings/obe/Component/Exceptions/Exceptions.hpp>

#include <Component/Exceptions.hpp>

#include <Bindings/Config.hpp>

namespace obe::component::exceptions::bindings
{
    void load_class_component_id_already_taken(sol::state_view state)
    {
        sol::table Exceptions_namespace = state["obe"]["component"]["exceptions"].get<sol::table>();
        sol::usertype<obe::component::exceptions::ComponentIdAlreadyTaken>
            bind_component_id_already_taken = Exceptions_namespace.new_usertype<
                obe::component::exceptions::ComponentIdAlreadyTaken>("ComponentIdAlreadyTaken",
                sol::call_constructor,
                sol::constructors<obe::component::exceptions::ComponentIdAlreadyTaken(
                    std::string_view, obe::DebugInfo)>(),
                sol::base_classes,
                sol::bases<obe::Exception<obe::component::exceptions::ComponentIdAlreadyTaken>,
                    obe::BaseException>());
    }
    void load_class_unknown_component_type(sol::state_view state)
    {
        sol::table Exceptions_namespace = state["obe"]["component"]["exceptions"].get<sol::table>();
        sol::usertype<obe::component::exceptions::UnknownComponentType> bind_unknown_component_type
            = Exceptions_namespace.new_usertype<obe::component::exceptions::UnknownComponentType>(
                "UnknownComponentType", sol::call_constructor,
                sol::constructors<obe::component::exceptions::UnknownComponentType(
                    std::string_view, obe::DebugInfo)>(),
                sol::base_classes,
                sol::bases<obe::Exception<obe::component::exceptions::UnknownComponentType>,
                    obe::BaseException>());
    }
};