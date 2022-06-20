#include <Bindings/obe/Types/Types.hpp>

#include <Types/Identifiable.hpp>
#include <Types/Selectable.hpp>
#include <Types/Serializable.hpp>
#include <Types/SmartEnum.hpp>
#include <Types/Togglable.hpp>

#include <Bindings/Config.hpp>

namespace obe::Types::bindings
{
    void load_class_identifiable(sol::state_view state)
    {
        sol::table Types_namespace = state["obe"]["Types"].get<sol::table>();
        sol::usertype<obe::Types::Identifiable> bind_identifiable
            = Types_namespace.new_usertype<obe::Types::Identifiable>("Identifiable",
                sol::call_constructor,
                sol::constructors<obe::Types::Identifiable(const std::string&)>());
        bind_identifiable["set_id"] = &obe::Types::Identifiable::set_id;
        bind_identifiable["get_id"] = &obe::Types::Identifiable::get_id;
    }
    void load_class_protected_identifiable(sol::state_view state)
    {
        sol::table Types_namespace = state["obe"]["Types"].get<sol::table>();
        sol::usertype<obe::Types::ProtectedIdentifiable> bind_protected_identifiable
            = Types_namespace.new_usertype<obe::Types::ProtectedIdentifiable>(
                "ProtectedIdentifiable", sol::base_classes, sol::bases<obe::Types::Identifiable>());
    }
    void load_class_selectable(sol::state_view state)
    {
        sol::table Types_namespace = state["obe"]["Types"].get<sol::table>();
        sol::usertype<obe::Types::Selectable> bind_selectable
            = Types_namespace.new_usertype<obe::Types::Selectable>("Selectable",
                sol::call_constructor,
                sol::constructors<obe::Types::Selectable(), obe::Types::Selectable(bool)>());
        bind_selectable["set_selected"] = &obe::Types::Selectable::set_selected;
        bind_selectable["toggle_selected"] = &obe::Types::Selectable::toggle_selected;
        bind_selectable["select"] = &obe::Types::Selectable::select;
        bind_selectable["unselect"] = &obe::Types::Selectable::unselect;
        bind_selectable["is_selected"] = &obe::Types::Selectable::is_selected;
    }
    void load_class_serializable(sol::state_view state)
    {
        sol::table Types_namespace = state["obe"]["Types"].get<sol::table>();
        sol::usertype<obe::Types::Serializable> bind_serializable
            = Types_namespace.new_usertype<obe::Types::Serializable>("Serializable");
        bind_serializable["schema"] = &obe::Types::Serializable::schema;
        bind_serializable["dump"] = &obe::Types::Serializable::dump;
        bind_serializable["load"] = &obe::Types::Serializable::load;
        bind_serializable["validate_and_load"] = &obe::Types::Serializable::validate_and_load;
    }
    void load_class_togglable(sol::state_view state)
    {
        sol::table Types_namespace = state["obe"]["Types"].get<sol::table>();
        sol::usertype<obe::Types::Togglable> bind_togglable
            = Types_namespace.new_usertype<obe::Types::Togglable>("Togglable",
                sol::call_constructor, sol::constructors<obe::Types::Togglable(bool)>());
        bind_togglable["set_enabled"] = &obe::Types::Togglable::set_enabled;
        bind_togglable["toggle"] = &obe::Types::Togglable::toggle;
        bind_togglable["enable"] = &obe::Types::Togglable::enable;
        bind_togglable["disable"] = &obe::Types::Togglable::disable;
        bind_togglable["is_enabled"] = &obe::Types::Togglable::is_enabled;
    }
    void load_class_unknown_enum_entry(sol::state_view state)
    {
        sol::table Types_namespace = state["obe"]["Types"].get<sol::table>();
        sol::usertype<obe::Types::UnknownEnumEntry> bind_unknown_enum_entry
            = Types_namespace.new_usertype<obe::Types::UnknownEnumEntry>("UnknownEnumEntry",
                sol::call_constructor,
                sol::constructors<obe::Types::UnknownEnumEntry(std::string_view, std::string_view,
                    const std::vector<std::string>&, obe::DebugInfo)>(),
                sol::base_classes,
                sol::bases<obe::Exception<obe::Types::UnknownEnumEntry>, obe::BaseException>());
    }
};