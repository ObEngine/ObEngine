#include <vili/Types.hpp>
#include <Functions.hpp>

namespace vili
{
    namespace Types
    {
        std::string getDefaultValueForType(DataType type)
        {
            std::string value = "";
            if (type == DataType::String) value.clear();
            else if (type == DataType::Int) value = "0";
            else if (type == DataType::Float) value = "0.0";
            else if (type == DataType::Bool) value = "False";
            else if (type == DataType::Link) value = "&()";
            else if (type == DataType::Template) value = "T()";
            return value;
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

        std::string attributeTypeToString(AttributeType type)
        {
            if (type == AttributeType::Attribute) return "Attribute";
            if (type == AttributeType::ContainerAttribute) return "ContainerAttribute";
            if (type == AttributeType::BaseAttribute) return "BaseAttribute";
            if (type == AttributeType::ListAttribute) return "ListAttribute";
            if (type == AttributeType::ComplexAttribute) return "ComplexAttribute";
            if (type == AttributeType::LinkAttribute) return "LinkAttribute";
            return "Error-Unknown";
        }
    }

    std::ostream& operator<<(std::ostream& os, const AttributeType& m)
    {
        os << Types::attributeTypeToString(m);
        return os;
    }

    std::ostream& operator<<(std::ostream& os, const DataType& m)
    {
        os << Types::dataTypeToString(m);
        return os;
    }
}
