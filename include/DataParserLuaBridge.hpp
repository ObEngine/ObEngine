#pragma once

#include <kaguya/kaguya.hpp>
#include <vili/Vili.hpp>

#include "Functions.hpp"

namespace obe
{
    namespace Script
    {
        namespace DataBridge
        {
            void dataToLua(kaguya::LuaTable& target, vili::Attribute& convert);
            vili::Attribute* luaToData(kaguya::LuaRef& convert);
            void complexAttributeToLuaTable(kaguya::LuaTable& target, vili::ComplexAttribute& convert);
            void baseAttributeToLuaElement(kaguya::LuaTable& target, vili::BaseAttribute& convert);
            void listAttributeToLuaTable(kaguya::LuaTable& target, vili::ListAttribute& convert);
            vili::ComplexAttribute* luaTableToComplexAttribute(std::string id, kaguya::LuaRef& convert);
            vili::BaseAttribute* luaElementToBaseAttribute(std::string id, kaguya::LuaRef& convert);
            vili::ListAttribute* luaTableToListAttribute(std::string id, kaguya::LuaTable& convert);
        }
    }
}
