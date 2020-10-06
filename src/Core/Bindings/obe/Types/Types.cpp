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
        bindIdentifiable["setId"] = &obe::Types::Identifiable::setId;
        bindIdentifiable["getId"] = &obe::Types::Identifiable::getId;
    }
    void LoadClassProtectedIdentifiable(sol::state_view state)
    {
        sol::table TypesNamespace = state["obe"]["Types"].get<sol::table>();
        sol::usertype<obe::Types::ProtectedIdentifiable> bindProtectedIdentifiable
            = TypesNamespace.new_usertype<obe::Types::ProtectedIdentifiable>(
                "ProtectedIdentifiable", sol::base_classes,
                sol::bases<obe::Types::Identifiable>());
    }
    void LoadClassSelectable(sol::state_view state)
    {
        sol::table TypesNamespace = state["obe"]["Types"].get<sol::table>();
        sol::usertype<obe::Types::Selectable> bindSelectable
            = TypesNamespace.new_usertype<obe::Types::Selectable>("Selectable",
                sol::call_constructor,
                sol::constructors<obe::Types::Selectable(),
                    obe::Types::Selectable(bool)>());
        bindSelectable["setSelected"] = &obe::Types::Selectable::setSelected;
        bindSelectable["toggleSelected"] = &obe::Types::Selectable::toggleSelected;
        bindSelectable["select"] = &obe::Types::Selectable::select;
        bindSelectable["unselect"] = &obe::Types::Selectable::unselect;
        bindSelectable["isSelected"] = &obe::Types::Selectable::isSelected;
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
            = TypesNamespace.new_usertype<obe::Types::Togglable>("Togglable",
                sol::call_constructor, sol::constructors<obe::Types::Togglable(bool)>());
        bindTogglable["setEnabled"] = &obe::Types::Togglable::setEnabled;
        bindTogglable["toggle"] = &obe::Types::Togglable::toggle;
        bindTogglable["enable"] = &obe::Types::Togglable::enable;
        bindTogglable["disable"] = &obe::Types::Togglable::disable;
        bindTogglable["isEnabled"] = &obe::Types::Togglable::isEnabled;
    }
};