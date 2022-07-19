#include <Bindings/obe/types/Types.hpp>

#include <Types/Identifiable.hpp>
#include <Types/Selectable.hpp>
#include <Types/Serializable.hpp>
#include <Types/SmartEnum.hpp>
#include <Types/Togglable.hpp>
#include <Types/UniqueIdentifiable.hpp>

#include <Bindings/Config.hpp>

namespace obe::types::bindings
{
    void load_class_identifiable(sol::state_view state)
    {
        sol::table types_namespace = state["obe"]["types"].get<sol::table>();
        sol::usertype<obe::types::Identifiable> bind_identifiable
            = types_namespace.new_usertype<obe::types::Identifiable>("Identifiable",
                sol::call_constructor,
                sol::constructors<obe::types::Identifiable(const std::string&)>());
        bind_identifiable["set_id"] = &obe::types::Identifiable::set_id;
        bind_identifiable["get_id"] = &obe::types::Identifiable::get_id;
    }
    void load_class_protected_identifiable(sol::state_view state)
    {
        sol::table types_namespace = state["obe"]["types"].get<sol::table>();
        sol::usertype<obe::types::ProtectedIdentifiable> bind_protected_identifiable
            = types_namespace.new_usertype<obe::types::ProtectedIdentifiable>(
                "ProtectedIdentifiable", sol::base_classes, sol::bases<obe::types::Identifiable>());
    }
    void load_class_selectable(sol::state_view state)
    {
        sol::table types_namespace = state["obe"]["types"].get<sol::table>();
        sol::usertype<obe::types::Selectable> bind_selectable
            = types_namespace.new_usertype<obe::types::Selectable>("Selectable",
                sol::call_constructor,
                sol::constructors<obe::types::Selectable(), obe::types::Selectable(bool)>());
        bind_selectable["set_selected"] = &obe::types::Selectable::set_selected;
        bind_selectable["toggle_selected"] = &obe::types::Selectable::toggle_selected;
        bind_selectable["select"] = &obe::types::Selectable::select;
        bind_selectable["unselect"] = &obe::types::Selectable::unselect;
        bind_selectable["is_selected"] = &obe::types::Selectable::is_selected;
    }
    void load_class_serializable(sol::state_view state)
    {
        sol::table types_namespace = state["obe"]["types"].get<sol::table>();
        sol::usertype<obe::types::Serializable> bind_serializable
            = types_namespace.new_usertype<obe::types::Serializable>("Serializable");
        bind_serializable["dump"] = &obe::types::Serializable::dump;
        bind_serializable["load"] = &obe::types::Serializable::load;
        bind_serializable["load_from_file"] = &obe::types::Serializable::load_from_file;
        bind_serializable["validate_and_load"] = &obe::types::Serializable::validate_and_load;
    }
    void load_class_togglable(sol::state_view state)
    {
        sol::table types_namespace = state["obe"]["types"].get<sol::table>();
        sol::usertype<obe::types::Togglable> bind_togglable
            = types_namespace.new_usertype<obe::types::Togglable>("Togglable",
                sol::call_constructor, sol::constructors<obe::types::Togglable(bool)>());
        bind_togglable["set_enabled"] = &obe::types::Togglable::set_enabled;
        bind_togglable["toggle"] = &obe::types::Togglable::toggle;
        bind_togglable["enable"] = &obe::types::Togglable::enable;
        bind_togglable["disable"] = &obe::types::Togglable::disable;
        bind_togglable["is_enabled"] = &obe::types::Togglable::is_enabled;
    }
    void load_class_unique_identifiable(sol::state_view state)
    {
        sol::table types_namespace = state["obe"]["types"].get<sol::table>();
        sol::usertype<obe::types::UniqueIdentifiable> bind_unique_identifiable
            = types_namespace.new_usertype<obe::types::UniqueIdentifiable>("UniqueIdentifiable",
                sol::call_constructor, sol::constructors<obe::types::UniqueIdentifiable()>());
        bind_unique_identifiable["get_unique_id"] = &obe::types::UniqueIdentifiable::get_unique_id;
    }
    void load_class_unknown_enum_entry(sol::state_view state)
    {
        sol::table types_namespace = state["obe"]["types"].get<sol::table>();
        sol::usertype<obe::types::UnknownEnumEntry> bind_unknown_enum_entry
            = types_namespace.new_usertype<obe::types::UnknownEnumEntry>("UnknownEnumEntry",
                sol::call_constructor,
                sol::constructors<obe::types::UnknownEnumEntry(std::string_view, std::string_view,
                    const std::vector<std::string>&, obe::DebugInfo)>(),
                sol::base_classes,
                sol::bases<obe::Exception<obe::types::UnknownEnumEntry>, obe::BaseException>());
    }
};