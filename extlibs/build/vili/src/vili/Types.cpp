#include <vili/Types.hpp>
#include <Functions.hpp>

namespace vili
{
    namespace Types
    {
        std::string getDefaultValueForType(DataType type)
        {
            switch (type)
            {
            case DataType::String: return "\"\"";
            case DataType::Int: return "0";
            case DataType::Float: return "0.0";
            case DataType::Bool: return "False";
            case DataType::Range: return "0..1";
            case DataType::Link: return "&()";
            case DataType::Template: return "T()";
            case DataType::Unknown: return "";
            default: return "";
            }
        }

        DataType getVarType(const std::string& var)
        {
            DataType attributeType;
            std::vector<std::string> boolType = {"True", "False"};
            if (Functions::Vector::isInList(var, boolType))
                attributeType = DataType::Bool;
            else if (Functions::String::occurencesInString(var, "..") == 1
                && Functions::String::isStringInt(Functions::String::split(var, "..")[0])
                && Functions::String::isStringInt(Functions::String::split(var, "..")[1]))
            {
                attributeType = DataType::Range;
            }
            else if (var.substr(0, 2) == "&(" && var.substr(var.size() - 1, 1) == ")")
                attributeType = DataType::Link;
            else if (isalpha(var[0]) && Functions::String::occurencesInString(var, "(") == 1 && var.substr(var.size() - 1, 1) == ")")
                attributeType = DataType::Template;
            else if (var.substr(0, 1) == "\"" && var.substr(var.size() - 1, 1) == "\"")
                attributeType = DataType::String;
            else if (Functions::String::isStringFloat(var))
                attributeType = DataType::Float;
            else if (Functions::String::isStringInt(var))
                attributeType = DataType::Int;
            else
                attributeType = DataType::Unknown;
            return attributeType;
        }

        DataType stringToDataType(const std::string& type)
        {
            if (type == "string" || type == "String")
                return DataType::String;
            if (type == "int" || type == "Int")
                return DataType::Int;
            if (type == "float" || type == "Float")
                return DataType::Float;
            if (type == "bool" || type == "Bool")
                return DataType::Bool;
            if (type == "range" || type == "Range")
                return DataType::Range;
            if (type == "template" || type == "Template")
                return DataType::Template;
            return DataType::Unknown;
        }

        std::string dataTypeToString(DataType type)
        {
            if (type == DataType::String) return "String";
            if (type == DataType::Int) return "Int";
            if (type == DataType::Float) return "Float";
            if (type == DataType::Bool) return "Bool";
            if (type == DataType::Range) return "Range";
            if (type == DataType::Template) return "Template";
            if (type == DataType::Unknown) return "Unknown";
            return "Error-Unknown";
        }

        std::string nodeTypeToString(NodeType type)
        {
            if (type == NodeType::Node) return "Attribute";
            if (type == NodeType::ContainerNode) return "ContainerAttribute";
            if (type == NodeType::DataNode) return "BaseAttribute";
            if (type == NodeType::ArrayNode) return "ListAttribute";
            if (type == NodeType::ComplexNode) return "ComplexAttribute";
            if (type == NodeType::LinkNode) return "LinkAttribute";
            return "Error-Unknown";
        }
    }

    std::ostream& operator<<(std::ostream& os, const NodeType& m)
    {
        os << Types::nodeTypeToString(m);
        return os;
    }

    std::ostream& operator<<(std::ostream& os, const DataType& m)
    {
        os << Types::dataTypeToString(m);
        return os;
    }
}
