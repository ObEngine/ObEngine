#include <Bindings/TypesBindings.hpp>
#include <Types/Identifiable.hpp>
#include <Types/Selectable.hpp>
#include <Types/Togglable.hpp>

namespace obe
{
    namespace Bindings
    {
        namespace TypesBindings
        {
            void LoadIdentifiable(kaguya::State& lua)
            {
                lua["Core"]["Types"]["Identifiable"].setClass(kaguya::UserdataMetatable<Types::Identifiable>()
                    .addFunction("getId", &Types::Identifiable::getId)
                    .addFunction("setId", &Types::Identifiable::setId)
                );
            }
            void LoadSelectable(kaguya::State& lua)
            {
                lua["Core"]["Types"]["Selectable"].setClass(kaguya::UserdataMetatable<Types::Selectable>()
                    .addFunction("isSelected", &Types::Selectable::isSelected)
                    .addFunction("select", &Types::Selectable::select)
                    .addFunction("setSelected", &Types::Selectable::setSelected)
                    .addFunction("toggleSelected", &Types::Selectable::toggleSelected)
                    .addFunction("unselect", &Types::Selectable::unselect)
                );
            }
            void LoadTogglable(kaguya::State& lua)
            {
                lua["Core"]["Types"]["Togglable"].setClass(kaguya::UserdataMetatable<Types::Togglable>()
                    .addFunction("disable", &Types::Togglable::disable)
                    .addFunction("enable", &Types::Togglable::enable)
                    .addFunction("getState", &Types::Togglable::getState)
                    .addFunction("setState", &Types::Togglable::setState)
                    .addFunction("toggle", &Types::Togglable::toggle)
                );
            }

        }
    }
}