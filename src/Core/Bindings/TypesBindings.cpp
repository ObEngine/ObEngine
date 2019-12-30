#include <Bindings/TypesBindings.hpp>
#include <Types/Identifiable.hpp>
#include <Types/Selectable.hpp>
#include <Types/Serializable.hpp>
#include <Types/Togglable.hpp>

#include <kaguya/kaguya.hpp>

namespace obe::Bindings::TypesBindings
{
    void LoadIdentifiable(kaguya::State* lua)
    {
        (*lua)["obe"]["Identifiable"].setClass(
            kaguya::UserdataMetatable<Types::Identifiable>()
                .addFunction("getId", &Types::Identifiable::getId)
                .addFunction("setId", &Types::Identifiable::setId));

        (*lua)["obe"]["ProtectedIdentifiable"].setClass(
            kaguya::UserdataMetatable<Types::ProtectedIdentifiable>());
    }

    void LoadSelectable(kaguya::State* lua)
    {
        (*lua)["obe"]["Selectable"].setClass(
            kaguya::UserdataMetatable<Types::Selectable>()
                .addFunction("isSelected", &Types::Selectable::isSelected)
                .addFunction("select", &Types::Selectable::select)
                .addFunction("setSelected", &Types::Selectable::setSelected)
                .addFunction("toggleSelected", &Types::Selectable::toggleSelected)
                .addFunction("unselect", &Types::Selectable::unselect));
    }

    void LoadSerializable(kaguya::State* lua)
    {
        (*lua)["obe"]["Serializable"].setClass(
            kaguya::UserdataMetatable<Types::Serializable>()
                .addFunction("dump", &Types::Serializable::dump)
                .addFunction("load", &Types::Serializable::load));
    }

    void LoadTogglable(kaguya::State* lua)
    {
        (*lua)["obe"]["Togglable"].setClass(
            kaguya::UserdataMetatable<Types::Togglable>()
                .addFunction("disable", &Types::Togglable::disable)
                .addFunction("enable", &Types::Togglable::enable)
                .addFunction("isEnabled", &Types::Togglable::isEnabled)
                .addFunction("setEnabled", &Types::Togglable::setEnabled)
                .addFunction("toggle", &Types::Togglable::toggle));
    }
} // namespace obe::Bindings::TypesBindings