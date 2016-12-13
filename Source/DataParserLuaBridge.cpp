#include "DataParserLuaBridge.hpp"

namespace mse {
	namespace Data {
		namespace DataBridge {
			kaguya::LuaRef* dataToLua(Attribute& convert)
			{
				//return kaguya::LuaRef();
				return nullptr;
			}
			Attribute* luaToData(kaguya::LuaRef& convert)
			{
				//return Attribute();
				return nullptr;
			}
			kaguya::LuaTable* complexAttributeToLuaTable(ComplexAttribute& convert)
			{
				//return kaguya::LuaTable();
				return nullptr;
			}
			kaguya::LuaRef* baseAttributeToLuaElement(BaseAttribute& convert)
			{
				//return kaguya::LuaRef();
				return nullptr;
			}
			kaguya::LuaTable* listAttributeToLuaTable(ListAttribute& convert)
			{
				//return kaguya::LuaTable();
				return nullptr;
			}
			ComplexAttribute* luaTableToComplexAttribute(std::string id, kaguya::LuaRef& convert)
			{
				ComplexAttribute* returnElement = new ComplexAttribute(id);
				std::cout << "Table Type : " << convert.type() << std::endl;
				if (convert.type() == 0 || convert.type() == 5) {
					std::map<std::string, kaguya::LuaRef> tableMap = convert;
					for (std::pair<std::string, kaguya::LuaRef> tableItem : tableMap) {
						std::string tableKey = tableItem.first;
						std::cout << "Current Table Key : " << tableKey << std::endl;
						if (convert[tableKey].type() == 5) {
							kaguya::LuaRef tempTableRef = convert[tableKey];
							returnElement->pushComplexAttribute(luaTableToComplexAttribute(tableKey, tempTableRef));
						}
						else if (Functions::Vector::isInList(convert[tableKey].type(), std::vector<int>({ 1, 3, 4 }))) {
							kaguya::LuaRef tempElemRef = convert[tableKey];
							returnElement->pushBaseAttribute(luaElementToBaseAttribute(tableKey, tempElemRef));
						}
					}
				}
				else {
					std::cout << "<Error:DataParserLuaBridge:DataBridge>[luaTableToComplexAttribute] LuaElement " << id << " is not a table" << std::endl;
				}
				return returnElement;
			}
			BaseAttribute* luaElementToBaseAttribute(std::string id, kaguya::LuaRef& convert)
			{
				std::string luaElement = convert;
				std::string convertType = "";
				if (convert.type() == 3 && Functions::String::isStringInt(luaElement)) {
					convertType = "int";
				}
				else if (convert.type() == 3 && Functions::String::isStringFloat(luaElement)) {
					convertType = "float";
				}
				else if (convert.type() == 1) {
					convertType = "bool";
				}
				else if (convert.type() == 4) {
					convertType = "string";
				}
				return new BaseAttribute(id, convertType, convert);
			}
			ListAttribute* luaTableToListAttribute(kaguya::LuaTable& convert)
			{
				//return ListAttribute();
				return nullptr;
			}
		}
	}
}
