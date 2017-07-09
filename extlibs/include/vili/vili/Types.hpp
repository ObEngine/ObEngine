#pragma once

#include <string>

namespace vili
{
    enum class AttributeType
    {
        Attribute,
        ContainerAttribute,
        BaseAttribute,
        ListAttribute,
        ComplexAttribute,
        LinkAttribute
    };

    enum class DataType
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
    std::ostream& operator<<(std::ostream& os, const AttributeType& m);
    std::ostream& operator<<(std::ostream& os, const DataType& m);
    namespace Types
    {
        DataType stringToDataType(const std::string& type);
        DataType getVarType(const std::string& var);
        constexpr const char* getDefaultValueForType(DataType type);
        std::string dataTypeToString(DataType type);
        std::string attributeTypeToString(AttributeType type);
    }
}
