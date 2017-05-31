#include <fstream>

#include "vili/BaseAttribute.hpp"
#include "vili/ComplexAttribute.hpp"
#include "vili/ListAttribute.hpp"
#include "Functions.hpp"

namespace vili
{
    std::ostream& operator<<(std::ostream& stream, const BaseAttribute& attribute)
    {
        if (attribute.getDataType() == Types::Int)
            stream << attribute.Int;
        else if (attribute.getDataType() == Types::Float)
            stream << attribute.Float;
        else if (attribute.getDataType() == Types::Bool)
            stream << attribute.Bool;
        else if (attribute.getDataType() == Types::String)
            stream << attribute.String;
        return stream;
    }

    BaseAttribute::BaseAttribute(ContainerAttribute* parent, const std::string& id, const Types::DataType& dataType) : Attribute(parent, id, Types::BaseAttribute)
    {
        new(static_cast<void*>(&String)) std::string();
        m_dataType = dataType;
    }

    BaseAttribute::BaseAttribute(const std::string& id, const Types::DataType& dataType) : Attribute(nullptr, id, Types::BaseAttribute)
    {
        m_dataType = dataType;
        new(static_cast<void*>(&String)) std::string();
    }

    void BaseAttribute::set(int var)
    {
        if (m_dataType == Types::Int)
            Int = var;
        else
            throw aube::ErrorHandler::Raise("Vili.Vili.BaseAttribute.WrongIntSet", {{"path", getNodePath()},{"type", dataTypeToString(m_dataType)}});
    }

    void BaseAttribute::set(double var)
    {
        if (m_dataType == Types::Float)
            Float = var;
        else
            throw aube::ErrorHandler::Raise("Vili.Vili.BaseAttribute.WrongFloatSet", {{"path", getNodePath()},{"type", dataTypeToString(m_dataType)}});
    }

    void BaseAttribute::set(const std::string& var)
    {
        if (m_dataType == Types::String)
            String = var;
        else
            throw aube::ErrorHandler::Raise("Vili.Vili.BaseAttribute.WrongStringSet", {{"path", getNodePath()},{"type", dataTypeToString(m_dataType)}});
    }

    void BaseAttribute::set(const char* var)
    {
        if (m_dataType == Types::String)
            String = std::string(var);
        else
            throw aube::ErrorHandler::Raise("Vili.Vili.BaseAttribute.WrongStringSet", {{"path", getNodePath()},{"type", dataTypeToString(m_dataType)}});
    }

    void BaseAttribute::set(bool var)
    {
        if (m_dataType == Types::Bool)
            Bool = var;
        else
            throw aube::ErrorHandler::Raise("Vili.Vili.BaseAttribute.WrongBoolSet", {{"path", getNodePath()},{"type", dataTypeToString(m_dataType)}});
    }

    void BaseAttribute::autoset(const std::string& rawData)
    {
        std::string pop = m_id;
        if (Types::getVarType(rawData) == m_dataType)
        {
            if (m_dataType == Types::Int)
                Int = stoi(rawData);
            else if (m_dataType == Types::Float)
                Float = stod(rawData);
            else if (m_dataType == Types::String)
                String = Functions::String::extract(rawData, 1, 1);
            else if (m_dataType == Types::Bool)
                Bool = (rawData == "True" ? true : false);
        }
        else
            throw aube::ErrorHandler::Raise("Vili.Vili.BaseAttribute.WrongAutoset", {{"data", rawData},{"path", getNodePath()}});
    }

    std::string BaseAttribute::returnData() const
    {
        if (m_dataType == Types::String)
            return "\"" + String + "\"";
        if (m_dataType == Types::Int)
            return std::to_string(Int);
        if (m_dataType == Types::Float)
            return std::to_string(Float);
        if (m_dataType == Types::Bool)
            return (Bool ? "True" : "False");
        return "?TypeError?";
    }

    Types::DataType BaseAttribute::getDataType() const
    {
        return m_dataType;
    }

    void BaseAttribute::copy(ContainerAttribute* newParent, const std::string& newid) const
    {
        if (newParent->getType() == Types::ListAttribute)
        {
            if (m_dataType == Types::Int)
                static_cast<ListAttribute*>(newParent)->push(this->get<int>());
            else if (m_dataType == Types::Float)
                static_cast<ListAttribute*>(newParent)->push(this->get<double>());
            else if (m_dataType == Types::Bool)
                static_cast<ListAttribute*>(newParent)->push(this->get<bool>());
            else if (m_dataType == Types::String)
                static_cast<ListAttribute*>(newParent)->push(this->get<std::string>());
        }
        else if (newParent->getType() == Types::ComplexAttribute)
        {
            dynamic_cast<ComplexAttribute*>(newParent)->createBaseAttribute(newid.empty() ? m_id : newid, m_dataType);
            BaseAttribute* newCopy = &dynamic_cast<ComplexAttribute*>(newParent)->getBaseAttribute(newid.empty() ? m_id : newid);
            if (m_dataType == Types::Int)
                newCopy->set(Int);
            else if (m_dataType == Types::Float)
                newCopy->set(Float);
            else if (m_dataType == Types::Bool)
                newCopy->set(Bool);
            else if (m_dataType == Types::String)
                newCopy->set(String);
        }
    }

    void BaseAttribute::write(std::ofstream* file, const std::string& spacing, unsigned int depth) const
    {
        if (m_visible)
        {
            for (unsigned int j = 0; j < depth - 1; j++)
                (*file) << spacing;
            std::string returnedData = returnData();
            if (m_dataType == Types::Float)
            {
                while (returnedData.back() == '0')
                    returnedData.pop_back();
                if (returnedData.back() == '.')
                    returnedData.pop_back();
            }
            if (m_id.front() != '#')
                (*file) << m_id << ":" << returnedData << std::endl;
            else
                (*file) << returnedData << std::endl;
        }
    }

    BaseAttribute::operator std::string() const
    {
        if (m_dataType == Types::String)
            return String;
        throw aube::ErrorHandler::Raise("Vili.Vili.BaseAttribute.WrongStringCastOperator", {{"path", getNodePath()}});
    }

    BaseAttribute::operator int() const
    {
        if (m_dataType == Types::Int)
            return Int;
        throw aube::ErrorHandler::Raise("Vili.Vili.BaseAttribute.WrongIntCastOperator", {{"path", getNodePath()}});
    }

    BaseAttribute::operator double() const
    {
        if (m_dataType == Types::Float)
            return Float;
        throw aube::ErrorHandler::Raise("Vili.Vili.BaseAttribute.WrongFloatCastOperator", {{"path", getNodePath()}});
    }

    BaseAttribute::operator bool() const
    {
        if (m_dataType == Types::Bool)
            return Bool;
        throw aube::ErrorHandler::Raise("Vili.Vili.BaseAttribute.WrongBoolCastOperator", {{"path", getNodePath()}});
    }
}
