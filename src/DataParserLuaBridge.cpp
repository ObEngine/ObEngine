#include "DataParserLuaBridge.hpp"

namespace mse {
	namespace Data {
		namespace DataBridge {
			void dataToLua(kaguya::LuaTable& target, Attribute& convert)
			{
			}
			Attribute* luaToData(kaguya::LuaRef& convert)
			{
				//return Attribute();
				return nullptr;
			}
			void complexAttributeToLuaTable(kaguya::LuaTable& target, ComplexAttribute& convert)
			{
				target[convert.getID()] = kaguya::NewTable();
				kaguya::LuaTable injectTable = target[convert.getID()];
				kaguya::State olol;
				for (std::string elementName : convert.getAllAttributes()) {
					if (convert.getAttributeType(elementName) == Types::BaseAttribute) {
						std::cout << "ofid::" << convert.getBaseAttribute(elementName)->getID() << std::endl;
						std::cout << "oftype::" << convert.getBaseAttribute(elementName)->getDataType() << std::endl;
						baseAttributeToLuaElement(injectTable, *convert.getBaseAttribute(elementName));
					}
					else if (convert.getAttributeType(elementName) == Types::ComplexAttribute) {
						complexAttributeToLuaTable(injectTable, *convert.getComplexAttribute(elementName));
					}
					else if (convert.getAttributeType(elementName) == Types::ListAttribute) {
						listAttributeToLuaTable(injectTable, *convert.getListAttribute(elementName));
					}
				}
				target[convert.getID()] = injectTable;
			}
			void baseAttributeToLuaElement(kaguya::LuaTable& target, BaseAttribute& convert)
			{
				std::cout << "ofin:" << convert.getID() << std::endl;
				if (convert.getDataType() == "int")
					target[convert.getID()] = convert.get<int>();
				else if (convert.getDataType() == "string")
					target[convert.getID()] = convert.get<std::string>();
				else if (convert.getDataType() == "bool")
					target[convert.getID()] = convert.get<bool>();
				else if (convert.getDataType() == "float")
				{
					double val = convert.get<double>();
					std::string vid = convert.getID();
					std::cout << "ofval::" << vid << ", " << val << std::endl;
					target[vid] = val;
				}
					
			}
			void listAttributeToLuaTable(kaguya::LuaTable& target, ListAttribute& convert)
			{
				kaguya::LuaTable injectList;
				for (int i = 0; i < convert.getSize(); i++) {
					injectList[i] = convert.get(i);
				}
				target[convert.getID()] = injectList;
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
			ListAttribute* luaTableToListAttribute(std::string id, kaguya::LuaTable& convert)
			{
				/*ListAttribute* returnElement = new ListAttribute(id, dataType);
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
				return returnElement;*/
				return nullptr;
			}
		}
	}
}
