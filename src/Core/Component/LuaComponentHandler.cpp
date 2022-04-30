#include <Component/Exceptions.hpp>
#include <Component/LuaComponentHandler.hpp>

namespace obe::Component
{
    LuaComponentHandler::LuaComponentHandler()
    {
        std::function<void(std::string_view, ComponentCaster<DerivedComponent>)> = 
        ComponentBase::OnRegister(&LuaComponentHandler::behaviour);
    }

    sol::lua_value LuaComponentHandler::cast(ComponentBase* component)
    {
        if (!ComponentCasters.count(component->type()))
        {
            throw Exceptions::UnknownComponentType(component->type(), EXC_INFO);
        }
        return ComponentCasters.at(this->type())(this);
    }
}
