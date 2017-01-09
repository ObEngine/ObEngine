#pragma once

#include <kaguya/kaguya.hpp>
#include "DataParser.hpp"

namespace mse {
	namespace Data {
		namespace DataBridge {
			void dataToLua(kaguya::LuaTable& target, Attribute& convert);
			Attribute* luaToData(kaguya::LuaRef& convert);
			void complexAttributeToLuaTable(kaguya::LuaTable& target, ComplexAttribute& convert);
			void baseAttributeToLuaElement(kaguya::LuaTable& target, BaseAttribute& convert);
			void listAttributeToLuaTable(kaguya::LuaTable& target, ListAttribute& convert);
			ComplexAttribute* luaTableToComplexAttribute(std::string id, kaguya::LuaRef& convert);
			BaseAttribute* luaElementToBaseAttribute(std::string id, kaguya::LuaRef& convert);
			ListAttribute* luaTableToListAttribute(std::string id, kaguya::LuaTable& convert);
		}
	}
}