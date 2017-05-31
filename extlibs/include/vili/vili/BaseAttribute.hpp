#pragma once

#include "../ErrorHandler.hpp"

#include "Attribute.hpp"

namespace vili
{
    //BaseAttribute
    class BaseAttribute : public Attribute
    {
    protected:
        union
        {
            int Int;
            double Float;
            bool Bool;
            std::string String;
        };

        Types::DataType m_dataType;
        friend std::ostream& operator<<(std::ostream& stream, const BaseAttribute& attribute);
    public:
        const static Types::AttributeType ClassType = Types::BaseAttribute;
        BaseAttribute(ContainerAttribute* parent, const std::string& id, const Types::DataType& dataType);
        BaseAttribute(const std::string& id, const Types::DataType& dataType);

        virtual ~BaseAttribute()
        {
        }

        std::string returnData() const;
        void set(int var);
        void set(double var);
        void set(const std::string& var);
        void set(const char* var);
        void set(bool var);
        void autoset(const std::string& rawData);
        Types::DataType getDataType() const;

        template <class T>
        T get() const
        {
        }

        void copy(ContainerAttribute* newParent, const std::string& newid = "") const override;
        void write(std::ofstream* file, const std::string& spacing, unsigned int depth) const override;
        operator std::string() const;
        operator int() const;
        operator double() const;
        operator bool() const;
    };

    std::ostream& operator<<(std::ostream& stream, const BaseAttribute& attribute);

    template <>
    inline int BaseAttribute::get() const
    {
        if (m_dataType == Types::Int)
            return Int;
        if (m_dataType == Types::Float)
            return Float;
        throw aube::ErrorHandler::Raise("Vili.ViliHeader.BaseAttribute.WrongIntCast", {{"path", getNodePath()},{"type", dataTypeToString(m_dataType)}});
    }

    template <>
    inline double BaseAttribute::get() const
    {
        if (m_dataType == Types::Float)
            return Float;
        if (m_dataType == Types::Int)
            return Int;
        throw aube::ErrorHandler::Raise("Vili.ViliHeader.BaseAttribute.WrongFloatCast", {{"path", getNodePath()},{"type", dataTypeToString(m_dataType)}});
    }

    template <>
    inline bool BaseAttribute::get() const
    {
        if (m_dataType == Types::Bool)
            return Bool;
        throw aube::ErrorHandler::Raise("Vili.ViliHeader.BaseAttribute.WrongBoolCast", {{"path", getNodePath()},{"type", dataTypeToString(m_dataType)}});
    }

    template <>
    inline std::string BaseAttribute::get() const
    {
        if (m_dataType == Types::String)
            return String;
        throw aube::ErrorHandler::Raise("Vili.ViliHeader.BaseAttribute.WrongStringCast", {{"path", getNodePath()},{"type", dataTypeToString(m_dataType)}});
    }
}
