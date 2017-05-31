#pragma once

#include <string>

namespace vili
{
    namespace Types
    {
        enum AttributeType
        {
            Attribute,
            ContainerAttribute,
            BaseAttribute,
            ListAttribute,
            ComplexAttribute,
            LinkAttribute
        };

        enum DataType
        {
            String,
            Int,
            Float,
            Bool,
            Range,
            Link,
            Template,
            Unknown
        };

        DataType stringToDataType(const std::string& type);
        DataType getVarType(const std::string& var);
        std::string getDefaultValueForType(DataType type);
        std::string dataTypeToString(DataType type);
        std::string attributeTypeToString(AttributeType type);
    }
}
