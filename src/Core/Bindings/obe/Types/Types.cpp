#include <Bindings/obe/Types/Types.hpp>

#include <Types/Identifiable.hpp>
#include <Types/Selectable.hpp>
#include <Types/Serializable.hpp>
#include <Types/Togglable.hpp>

#include <Bindings/Config.hpp>

namespace obe::Types::Bindings
{
    void LoadClassIdentifiable(sol::state_view state)
    {
        sol::table TypesNamespace = state["obe"]["Types"].get<sol::table>();
        sol::usertype<obe::Types::Identifiable> bindIdentifiable
            = TypesNamespace.new_usertype<obe::Types::Identifiable>("Identifiable",
                sol::call_constructor,
                sol::constructors<obe::Types::Identifiable(const std::string&)>());
        bindIdentifiable["set_id"] = &obe::Types::Identifiable::set_id;
        bindIdentifiable["get_id"] = &obe::Types::Identifiable::get_id;
    }
    void LoadClassProtectedIdentifiable(sol::state_view state)
    {
        sol::table TypesNamespace = state["obe"]["Types"].get<sol::table>();
        sol::usertype<obe::Types::ProtectedIdentifiable> bindProtectedIdentifiable
            = TypesNamespace.new_usertype<obe::Types::ProtectedIdentifiable>(
                "ProtectedIdentifiable", sol::base_classes, sol::bases<obe::Types::Identifiable>());
    }
    void LoadClassSelectable(sol::state_view state)
    {
        sol::table TypesNamespace = state["obe"]["Types"].get<sol::table>();
        sol::usertype<obe::Types::Selectable> bindSelectable
            = TypesNamespace.new_usertype<obe::Types::Selectable>("Selectable",
                sol::call_constructor,
                sol::constructors<obe::Types::Selectable(), obe::Types::Selectable(bool)>());
        bindSelectable["set_selected"] = &obe::Types::Selectable::set_selected;
        bindSelectable["toggle_selected"] = &obe::Types::Selectable::toggle_selected;
        bindSelectable["select"] = &obe::Types::Selectable::select;
        bindSelectable["unselect"] = &obe::Types::Selectable::unselect;
        bindSelectable["is_selected"] = &obe::Types::Selectable::is_selected;
    }
    void LoadClassSerializable(sol::state_view state)
    {
        sol::table TypesNamespace = state["obe"]["Types"].get<sol::table>();
        sol::usertype<obe::Types::Serializable> bindSerializable
            = TypesNamespace.new_usertype<obe::Types::Serializable>("Serializable");
        bindSerializable["dump"] = &obe::Types::Serializable::dump;
        bindSerializable["load"] = &obe::Types::Serializable::load;
    }
    void LoadClassTogglable(sol::state_view state)
    {
        sol::table TypesNamespace = state["obe"]["Types"].get<sol::table>();
        sol::usertype<obe::Types::Togglable> bindTogglable
            = TypesNamespace.new_usertype<obe::Types::Togglable>("Togglable", sol::call_constructor,
                sol::constructors<obe::Types::Togglable(bool)>());
        bindTogglable["set_enabled"] = &obe::Types::Togglable::set_enabled;
        bindTogglable["toggle"] = &obe::Types::Togglable::toggle;
        bindTogglable["enable"] = &obe::Types::Togglable::enable;
        bindTogglable["disable"] = &obe::Types::Togglable::disable;
        bindTogglable["is_enabled"] = &obe::Types::Togglable::is_enabled;
    }
};