#include <vili/Types.hpp>
#include <Functions.hpp>

namespace vili
{
    namespace Types
    {
        std::string getDefaultValueForType(DataType type)
        {
            std::string value = "";
            if (type == String) value.clear();
            else if (type == Int) value = "0";
            else if (type == Float) value = "0.0";
            else if (type == Bool) value = "False";
            else if (type == Link) value = "&()";
            else if (type == Template) value = "T()";
            return value;
        }

        DataType getVarType(const std::string& var)
        {
            DataType attributeType;
            std::vector<std::string> boolType = {"True", "False"};
            if (Functions::Vector::isInList(var, boolType))
                attributeType = Bool;
            else if (Functions::String::occurencesInString(var, "..") == 1
                && Functions::String::isStringInt(Functions::String::split(var, "..")[0])
                && Functions::String::isStringInt(Functions::String::split(var, "..")[1]))
            {
                attributeType = Range;
            }
            else if (var.substr(0, 2) == "&(" && var.substr(var.size() - 1, 1) == ")")
                attributeType = Link;
            else if (isalpha(var[0]) && Functions::String::occurencesInString(var, "(") == 1 && var.substr(var.size() - 1, 1) == ")")
                attributeType = Template;
            else if (var.substr(0, 1) == "\"" && var.substr(var.size() - 1, 1) == "\"")
                attributeType = String;
            else if (Functions::String::isStringFloat(var))
                attributeType = Float;
            else if (Functions::String::isStringInt(var))
                attributeType = Int;
            else
                attributeType = Unknown;
            return attributeType;
        }

        DataType stringToDataType(const std::string& type)
        {
            if (type == "string" || type == "String")
                return String;
            if (type == "int" || type == "Int")
                return Int;
            if (type == "float" || type == "Float")
                return Float;
            if (type == "bool" || type == "Bool")
                return Bool;
            if (type == "range" || type == "Range")
                return Range;
            if (type == "template" || type == "Template")
                return Template;
            return Unknown;
        }

        std::string dataTypeToString(DataType type)
        {
            if (type == String) return "String";
            if (type == Int) return "Int";
            if (type == Float) return "Float";
            if (type == Bool) return "Bool";
            if (type == Range) return "Range";
            if (type == Template) return "Template";
            if (type == Unknown) return "Unknown";
            return "Error-Unknown";
        }

        std::string attributeTypeToString(AttributeType type)
        {
            if (type == Attribute) return "Attribute";
            if (type == ContainerAttribute) return "ContainerAttribute";
            if (type == BaseAttribute) return "BaseAttribute";
            if (type == ListAttribute) return "ListAttribute";
            if (type == ComplexAttribute) return "ComplexAttribute";
            if (type == LinkAttribute) return "LinkAttribute";
            return "Error-Unknown";
        }
    }
}
