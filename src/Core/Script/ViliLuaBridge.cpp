#include <Script/ViliLuaBridge.hpp>
#include <Utils/StringUtils.hpp>
#include <Utils/VectorUtils.hpp>
#include <sol/sol.hpp>

namespace obe::Script::ViliLuaBridge
{
    sol::object viliToLua(vili::node& convert)
    {
        if (convert.is<vili::array>())
        {
            return viliArrayToLuaTable(convert);
        }
        else if (convert.is<vili::object>())
        {
            return viliObjectToLuaTable(convert);
        }
        else if (convert.is_primitive())
        {
            // return viliPrimitiveToLuaValue(convert);
        }
    }

    vili::node luaToVili(sol::reference convert)
    {
        // return Attribute();
        return nullptr;
    }

    sol::table viliObjectToLuaTable(vili::node& convert)
    {
        sol::table result;
        for (auto [key, value] : convert.items())
        {
            if (value.is_primitive())
            {
                result[key] = viliPrimitiveToLuaValue(convert);
            }
            else if (value.is<vili::object>())
            {
                result[key] = viliObjectToLuaTable(value);
            }
            else if (value.is<vili::array>())
            {
                result[key] = viliArrayToLuaTable(value);
            }
        }
        return result;
    }

    sol::lua_value viliPrimitiveToLuaValue(vili::node& convert)
    {
        if (convert.is<vili::integer>())
            return convert.as<vili::integer>();
        else if (convert.is<vili::string>())
            return convert.as<vili::string>();
        else if (convert.is<vili::boolean>())
            return convert.as<vili::boolean>();
        else if (convert.is<vili::number>())
            return convert.as<vili::number>();
    }

    sol::table viliArrayToLuaTable(vili::node& convert)
    {
        sol::table result;
        std::size_t index = 0;
        for (vili::node& value : convert)
        {
            if (convert.is_primitive())
                result[++index] = viliPrimitiveToLuaValue(value);
            else if (convert.is<vili::array>())
                result[++index] = viliArrayToLuaTable(value);
            else if (convert.is<vili::object>())
                result[++index] = viliObjectToLuaTable(value);
        }
        return result;
    }

    vili::node luaTableToViliObject(sol::object convert)
    {
        /*if (convert.get_type() == sol::type:: || convert.type() == 5)
        {
            vili::ComplexNode* returnElement = new vili::ComplexNode(id);
            std::map<std::string, sol::object> tableMap
                = convert.as<std::map<std::string, sol::object>>();
            for (const std::pair<std::string, sol::object> tableItem : tableMap)
            {
                const std::string tableKey = tableItem.first;
                if (convert[tableKey].type() == 5)
                {
                    kaguya::LuaRef tempTableRef = convert[tableKey];
                    returnElement->pushComplexNode(
                        luaTableToComplexNode(tableKey, tempTableRef));
                }
                else if (Utils::Vector::contains(
                             convert[tableKey].type(), std::vector<int>({ 1, 3, 4 })))
                {
                    kaguya::LuaRef tempElemRef = convert[tableKey];
                    returnElement->pushDataNode(
                        luaElementToDataNode(tableKey, tempElemRef));
                }
            }

            return returnElement;
        }
        throw aube::ErrorHandler::Raise(
            "ObEngine.Script.ViliLuaBridge.NotATable", { { "id", id } });*/
        return nullptr;
    }

    vili::node luaValueToViliPrimitive(sol::object convert)
    {
        /*vili::DataNode* returnAttribute = nullptr;
        if (convert.is<int>())
        {
            returnAttribute = new vili::DataNode(id, vili::DataType::Int);
            returnAttribute->set(convert.as<int>());
        }
        else if (convert.is<double>())
        {
            returnAttribute = new vili::DataNode(id, vili::DataType::Float);
            returnAttribute->set(convert.as<double>());
        }
        else if (convert.is<bool>())
        {
            returnAttribute = new vili::DataNode(id, vili::DataType::Bool);
            returnAttribute->set(convert.as<bool>());
        }
        else if (convert.is<std::string>())
        {
            returnAttribute = new vili::DataNode(id, vili::DataType::String);
            returnAttribute->set(convert.as<std::string>());
        }

        return returnAttribute;*/
        return 0;
    }

    vili::node luaTableToViliArray(sol::table convert)
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
                    returnElement->pushComplexAttribute(luaTableToComplexAttribute(tableKey,
        tempTableRef));
                }
                else if (Utils::Vector::contains(convert[tableKey].type(),
        std::vector<int>({ 1, 3, 4 }))) { kaguya::LuaRef tempElemRef =
        convert[tableKey];
                    returnElement->pushBaseAttribute(luaElementToBaseAttribute(tableKey,
        tempElemRef));
                }
            }
        }
        else {
            std::cout <<
        "<Error:ViliLuaBridge:DataBridge>[luaTableToComplexAttribute] LuaElement
        " << id << " is not a table" << std::endl;
        }
        return returnElement;*/
        return nullptr;
    }
} // namespace obe::Script::DataBridge