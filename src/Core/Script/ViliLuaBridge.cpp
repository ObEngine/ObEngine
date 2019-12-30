#include <Script/ViliLuaBridge.hpp>
#include <Utils/StringUtils.hpp>
#include <Utils/VectorUtils.hpp>

namespace obe::Script::DataBridge
{
    void dataToLua(kaguya::LuaTable& target, vili::Node* convert)
    {
        if (convert->getType() == vili::NodeType::ArrayNode)
        {
            arrayNodeToLuaTable(target, static_cast<vili::ArrayNode*>(convert));
        }
        else if (convert->getType() == vili::NodeType::ComplexNode)
        {
            complexNodeToLuaTable(target, static_cast<vili::ComplexNode*>(convert));
        }
        else if (convert->getType() == vili::NodeType::DataNode)
        {
            dataNodeToLuaElement(target, static_cast<vili::DataNode*>(convert));
        }
    }

    vili::Node* luaToData(kaguya::LuaRef& convert)
    {
        // return Attribute();
        return nullptr;
    }

    void complexNodeToLuaTable(kaguya::LuaTable& target, vili::ComplexNode* convert)
    {
        target[convert->getId()] = kaguya::NewTable();
        kaguya::LuaTable injectTable = target[convert->getId()];
        kaguya::State olol;
        for (vili::Node* node : convert->getAll())
        {
            if (node->getType() == vili::NodeType::DataNode)
            {
                dataNodeToLuaElement(injectTable, &convert->getDataNode(node->getId()));
            }
            else if (node->getType() == vili::NodeType::ComplexNode)
            {
                complexNodeToLuaTable(injectTable, &convert->getComplexNode(node->getId()));
            }
            else if (node->getType() == vili::NodeType::ArrayNode)
            {
                arrayNodeToLuaTable(injectTable, &convert->getArrayNode(node->getId()));
            }
        }
        target[convert->getId()] = injectTable;
    }

    void dataNodeToLuaElement(kaguya::LuaTable& target, vili::DataNode* convert)
    {
        if (convert->getDataType() == vili::DataType::Int)
            target[convert->getId()] = convert->get<int>();
        else if (convert->getDataType() == vili::DataType::String)
            target[convert->getId()] = convert->get<std::string>();
        else if (convert->getDataType() == vili::DataType::Bool)
            target[convert->getId()] = convert->get<bool>();
        else if (convert->getDataType() == vili::DataType::Float)
            target[convert->getId()] = convert->get<double>();
    }

    void arrayNodeToLuaTable(kaguya::LuaTable& target, vili::ArrayNode* convert)
    {
        target[convert->getId()] = kaguya::NewTable();
        kaguya::LuaTable mTable = target[convert->getId()];
        for (int i = 0; i < convert->size(); i++)
        {
            if (convert->get(i).getDataType() == vili::DataType::Int)
                mTable[i + 1] = convert->get(i).get<int>();
            else if (convert->get(i).getDataType() == vili::DataType::String)
                mTable[i + 1] = convert->get(i).get<std::string>();
            else if (convert->get(i).getDataType() == vili::DataType::Bool)
                mTable[i + 1] = convert->get(i).get<bool>();
            else if (convert->get(i).getDataType() == vili::DataType::Float)
                mTable[i + 1] = convert->get(i).get<double>();
        }
    }

    vili::ComplexNode* luaTableToComplexNode(const std::string& id, kaguya::LuaRef& convert)
    {
        if (convert.type() == 0 || convert.type() == 5)
        {
            vili::ComplexNode* returnElement = new vili::ComplexNode(id);
            std::map<std::string, kaguya::LuaRef> tableMap = convert;
            for (const std::pair<std::string, kaguya::LuaRef> tableItem : tableMap)
            {
                const std::string tableKey = tableItem.first;
                if (convert[tableKey].type() == 5)
                {
                    kaguya::LuaRef tempTableRef = convert[tableKey];
                    returnElement->pushComplexNode(luaTableToComplexNode(tableKey, tempTableRef));
                }
                else if (Utils::Vector::contains(
                             convert[tableKey].type(), std::vector<int>({ 1, 3, 4 })))
                {
                    kaguya::LuaRef tempElemRef = convert[tableKey];
                    returnElement->pushDataNode(luaElementToDataNode(tableKey, tempElemRef));
                }
            }

            return returnElement;
        }
        throw aube::ErrorHandler::Raise(
            "ObEngine.Script.ViliLuaBridge.NotATable", { { "id", id } });
    }

    vili::DataNode* luaElementToDataNode(const std::string& id, kaguya::LuaRef& convert)
    {
        vili::DataNode* returnAttribute = nullptr;
        if (convert.type() == 3 && Utils::String::isStringInt(convert))
        {
            returnAttribute = new vili::DataNode(id, vili::DataType::Int);
            returnAttribute->set(int(convert));
        }
        else if (convert.type() == 3 && Utils::String::isStringFloat(convert))
        {
            returnAttribute = new vili::DataNode(id, vili::DataType::Float);
            returnAttribute->set(double(convert));
        }
        else if (convert.type() == 1)
        {
            returnAttribute = new vili::DataNode(id, vili::DataType::Bool);
            returnAttribute->set(bool(convert));
        }
        else if (convert.type() == 4)
        {
            returnAttribute = new vili::DataNode(id, vili::DataType::String);
            const char* convertChar = convert;
            returnAttribute->set(convertChar);
        }

        return returnAttribute;
    }

    vili::ArrayNode* luaTableToArrayNode(const std::string& id, kaguya::LuaTable& convert)
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