#pragma once

#include <functional>
#include <unordered_map>

#include <sol/sol.hpp>

#include <Component/Component.hpp>

namespace obe::Component
{
    class LuaComponentHandler
    {
    private:
        std::unordered_map<std::string, std::function<sol::lua_value(ComponentBase*)>> m_casters;
    public:
        LuaComponentHandler();
        template <class DerivedComponent>
        void behaviour(std::string_view component_type, ComponentBase::ComponentCaster<DerivedComponent> caster);
        sol::lua_value cast(ComponentBase* component);
    };

    template <class DerivedComponent>
    void LuaComponentHandler::behaviour(std::string_view component_type, ComponentBase::ComponentCaster<DerivedComponent> caster)
    {
        m_casters[component_type]
            = [caster](ComponentBase* component) -> sol::lua_value { return caster(component);
        };
    }
}
