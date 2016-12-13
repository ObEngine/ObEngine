#pragma once

#include <kaguya/kaguya.hpp>
#include "DataParser.hpp"

namespace mse {
	namespace Data {
		namespace DataBridge {
			kaguya::LuaRef* dataToLua(Attribute& convert);
			Attribute* luaToData(kaguya::LuaRef& convert);
			kaguya::LuaTable* complexAttributeToLuaTable(ComplexAttribute& convert);
			kaguya::LuaRef* baseAttributeToLuaElement(BaseAttribute& convert);
			kaguya::LuaTable* listAttributeToLuaTable(ListAttribute& convert);
			ComplexAttribute* luaTableToComplexAttribute(std::string id, kaguya::LuaRef& convert);
			BaseAttribute* luaElementToBaseAttribute(std::string id, kaguya::LuaRef& convert);
			ListAttribute* luaTableToListAttribute(kaguya::LuaTable& convert);
		}
	}
}