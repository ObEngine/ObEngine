#include "DataParserLuaBridge.hpp"

namespace obe
{
    namespace Data
    {
        namespace DataBridge
        {
            void dataToLua(kaguya::LuaTable& target, vili::Attribute& convert)
            {
            }

            vili::Attribute* luaToData(kaguya::LuaRef& convert)
            {
                //return Attribute();
                return nullptr;
            }

            void complexAttributeToLuaTable(kaguya::LuaTable& target, vili::ComplexAttribute& convert)
            {
                target[convert.getID()] = kaguya::NewTable();
                kaguya::LuaTable injectTable = target[convert.getID()];
                kaguya::State olol;
                for (std::string elementName : convert.getAll())
                {
                    if (convert.getAttributeType(elementName) == vili::Types::BaseAttribute)
                    {
                        baseAttributeToLuaElement(injectTable, convert.getBaseAttribute(elementName));
                    }
                    else if (convert.getAttributeType(elementName) == vili::Types::ComplexAttribute)
                    {
                        complexAttributeToLuaTable(injectTable, convert.getComplexAttribute(elementName));
                    }
                    else if (convert.getAttributeType(elementName) == vili::Types::ListAttribute)
                    {
                        listAttributeToLuaTable(injectTable, convert.getListAttribute(elementName));
                    }
                }
                target[convert.getID()] = injectTable;
            }

            void baseAttributeToLuaElement(kaguya::LuaTable& target, vili::BaseAttribute& convert)
            {
                if (convert.getDataType() == vili::Types::Int)
                    target[convert.getID()] = convert.get<int>();
                else if (convert.getDataType() == vili::Types::String)
                    target[convert.getID()] = convert.get<std::string>();
                else if (convert.getDataType() == vili::Types::Bool)
                    target[convert.getID()] = convert.get<bool>();
                else if (convert.getDataType() == vili::Types::Float)
                {
                    double val = convert.get<double>();
                    std::string vid = convert.getID();
                    target[vid] = val;
                }
            }

            void listAttributeToLuaTable(kaguya::LuaTable& target, vili::ListAttribute& convert)
            {
                kaguya::LuaTable injectList;
                for (int i = 0; i < convert.size(); i++)
                {
                    injectList[i] = &convert.get(i);
                }
                target[convert.getID()] = injectList;
            }

            vili::ComplexAttribute* luaTableToComplexAttribute(std::string id, kaguya::LuaRef& convert)
            {
                std::cout << "Convert table : " << id << std::endl;
                vili::ComplexAttribute* returnElement = new vili::ComplexAttribute(id);
                if (convert.type() == 0 || convert.type() == 5)
                {
                    std::map<std::string, kaguya::LuaRef> tableMap = convert;
                    for (std::pair<std::string, kaguya::LuaRef> tableItem : tableMap)
                    {
                        std::string tableKey = tableItem.first;
                        if (convert[tableKey].type() == 5)
                        {
                            std::cout << "Push subtable : " << tableKey << std::endl;
                            kaguya::LuaRef tempTableRef = convert[tableKey];
                            returnElement->pushComplexAttribute(luaTableToComplexAttribute(tableKey, tempTableRef));
                        }
                        else if (Functions::Vector::isInList(convert[tableKey].type(), std::vector<int>({1, 3, 4})))
                        {
                            std::cout << "Push subelement : " << tableKey << std::endl;
                            kaguya::LuaRef tempElemRef = convert[tableKey];
                            returnElement->pushBaseAttribute(luaElementToBaseAttribute(tableKey, tempElemRef));
                        }
                    }
                }
                else
                    throw aube::ErrorHandler::Raise("ObEngine.DataParserLuaBridge.LuaTableToComplexAttribute.NotATable", {{"id", id}});
                return returnElement;
            }

            vili::BaseAttribute* luaElementToBaseAttribute(std::string id, kaguya::LuaRef& convert)
            {
                std::string convertType = "";
                if (convert.type() == 3 && Functions::String::isStringInt(convert))
                {
                    convertType = "int";
                }
                else if (convert.type() == 3 && vili::Functions::String::isStringFloat(convert))
                {
                    convertType = "float";
                }
                else if (convert.type() == 1)
                {
                    convertType = "bool";
                }
                else if (convert.type() == 4)
                {
                    convertType = "string";
                }
                vili::BaseAttribute* returnAttribute = new vili::BaseAttribute(id, vili::Types::stringToDataType(convertType));
                returnAttribute->autoset(convert);
                return returnAttribute;
            }

            vili::ListAttribute* luaTableToListAttribute(std::string id, kaguya::LuaTable& convert)
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
