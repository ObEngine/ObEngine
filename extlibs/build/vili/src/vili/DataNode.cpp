#include <fstream>

#include "vili/DataNode.hpp"
#include "vili/ComplexNode.hpp"
#include "vili/ArrayNode.hpp"
#include "Functions.hpp"

namespace vili
{
    std::ostream& operator<<(std::ostream& stream, const DataNode& attribute)
    {
        if (attribute.getDataType() == DataType::Int)
            stream << attribute.m_data.Int;
        else if (attribute.getDataType() == DataType::Float)
            stream << attribute.m_data.Float;
        else if (attribute.getDataType() == DataType::Bool)
            stream << attribute.m_data.Bool;
        else if (attribute.getDataType() == DataType::String)
            stream << attribute.m_data.String;
        return stream;
    }

    DataNode::DataNode(ContainerNode* parent, const std::string& id, const DataType& dataType) : Node(parent, id, NodeType::DataNode)
    {
        m_dataType = dataType;
        new(static_cast<void*>(&m_data.String)) std::string();
    }

    DataNode::DataNode(const std::string& id, const DataType& dataType) : Node(nullptr, id, NodeType::DataNode)
    {
        m_dataType = dataType;
        new(static_cast<void*>(&m_data.String)) std::string();
    }

    DataNode::DataNode(const DataNode& copy) : Node(copy)
    {
        m_dataType = copy.m_dataType;
        new(static_cast<void*>(&m_data.String)) std::string();
    }

    DataNode::~DataNode()
    {
        //delete &m_data.String;
    }

    void DataNode::set(int var)
    {
        if (m_dataType == DataType::Int)
            m_data.Int = var;
        else
            throw aube::ErrorHandler::Raise("Vili.Vili.DataNode.WrongIntSet", {{"path", getNodePath()},{"type", Types::dataTypeToString(m_dataType)}});
    }

    void DataNode::set(double var)
    {
        if (m_dataType == DataType::Float)
            m_data.Float = var;
        else
            throw aube::ErrorHandler::Raise("Vili.Vili.DataNode.WrongFloatSet", {{"path", getNodePath()},{"type", Types::dataTypeToString(m_dataType)}});
    }

    void DataNode::set(const std::string& var)
    {
        if (m_dataType == DataType::String)
            m_data.String = var;
        else
            throw aube::ErrorHandler::Raise("Vili.Vili.DataNode.WrongStringSet", {{"path", getNodePath()},{"type", Types::dataTypeToString(m_dataType)}});
    }

    void DataNode::set(const char* var)
    {
        if (m_dataType == DataType::String)
            m_data.String = std::string(var);
        else
            throw aube::ErrorHandler::Raise("Vili.Vili.DataNode.WrongStringSet", {{"path", getNodePath()},{"type", Types::dataTypeToString(m_dataType)}});
    }

    void DataNode::set(bool var)
    {
        if (m_dataType == DataType::Bool)
            m_data.Bool = var;
        else
            throw aube::ErrorHandler::Raise("Vili.Vili.DataNode.WrongBoolSet", {{"path", getNodePath()},{"type", Types::dataTypeToString(m_dataType)}});
    }

    void DataNode::operator=(int var)
    {
        this->set(var);
    }

    void DataNode::operator=(double var)
    {
        this->set(var);
    }

    void DataNode::operator=(const std::string& var)
    {
        this->set(var);
    }

    void DataNode::operator=(const char* var)
    {
        this->set(var);
    }

    void DataNode::operator=(bool var)
    {
        this->set(var);
    }

    void DataNode::autoset(const std::string& rawData)
    {
        std::string pop = m_id;
        if (Types::getVarType(rawData) == m_dataType)
        {
            if (m_dataType == DataType::Int)
                m_data.Int = stoi(rawData);
            else if (m_dataType == DataType::Float)
                m_data.Float = stod(rawData);
            else if (m_dataType == DataType::String)
                m_data.String = Functions::String::extract(rawData, 1, 1);
            else if (m_dataType == DataType::Bool)
                m_data.Bool = (rawData == "True" ? true : false);
        }
        else
            throw aube::ErrorHandler::Raise("Vili.Vili.DataNode.WrongAutoset", {{"data", rawData},{"path", getNodePath()}});
    }

    std::string DataNode::dumpData() const
    {
        if (m_dataType == DataType::String)
            return "\"" + m_data.String + "\"";
        if (m_dataType == DataType::Int)
            return std::to_string(m_data.Int);
        if (m_dataType == DataType::Float)
            return std::to_string(m_data.Float);
        if (m_dataType == DataType::Bool)
            return (m_data.Bool ? "True" : "False");
        return "?TypeError?";
    }

    DataType DataNode::getDataType() const
    {
        return m_dataType;
    }

    void DataNode::copy(ContainerNode* newParent, const std::string& newid) const
    {
        if (newParent->getType() == NodeType::ArrayNode)
        {
            if (m_dataType == DataType::Int)
                static_cast<ArrayNode*>(newParent)->push(this->get<int>());
            else if (m_dataType == DataType::Float)
                static_cast<ArrayNode*>(newParent)->push(this->get<double>());
            else if (m_dataType == DataType::Bool)
                static_cast<ArrayNode*>(newParent)->push(this->get<bool>());
            else if (m_dataType == DataType::String)
                static_cast<ArrayNode*>(newParent)->push(this->get<std::string>());
        }
        else if (newParent->getType() == NodeType::ComplexNode)
        {
            dynamic_cast<ComplexNode*>(newParent)->createDataNode(newid.empty() ? m_id : newid, m_dataType);
            DataNode* newCopy = &dynamic_cast<ComplexNode*>(newParent)->getDataNode(newid.empty() ? m_id : newid);
            if (m_dataType == DataType::Int)
                newCopy->set(m_data.Int);
            else if (m_dataType == DataType::Float)
                newCopy->set(m_data.Float);
            else if (m_dataType == DataType::Bool)
                newCopy->set(m_data.Bool);
            else if (m_dataType == DataType::String)
                newCopy->set(m_data.String);
        }
    }

    void DataNode::write(std::ofstream* file, const std::string& spacing, unsigned int depth) const
    {
        if (m_visible)
        {
            for (unsigned int j = 0; j < depth - 1; j++)
                (*file) << spacing;
            std::string returnedData = dumpData();
            if (m_dataType == DataType::Float)
            {
                while (returnedData.size() > 2 && returnedData.back() == '0' && returnedData[returnedData.size() - 2] != '.')
                    returnedData.pop_back();
            }
            if (m_id.front() != '#')
                (*file) << m_id << ":" << returnedData << std::endl;
            else
                (*file) << returnedData << std::endl;
        }
    }

    DataNode::operator std::string() const
    {
        if (m_dataType == DataType::String)
            return m_data.String;
        throw aube::ErrorHandler::Raise("Vili.Vili.DataNode.WrongStringCastOperator", {{"path", getNodePath()}});
    }

	DataNode::operator unsigned int() const
	{
		return int(*this);
	}

	DataNode::operator int() const
    {
        if (m_dataType == DataType::Int)
            return m_data.Int;
        throw aube::ErrorHandler::Raise("Vili.Vili.DataNode.WrongIntCastOperator", {{"path", getNodePath()}});
    }

    DataNode::operator double() const
    {
        if (m_dataType == DataType::Float)
            return m_data.Float;
        throw aube::ErrorHandler::Raise("Vili.Vili.DataNode.WrongFloatCastOperator", {{"path", getNodePath()}});
    }

    DataNode::operator bool() const
    {
        if (m_dataType == DataType::Bool)
            return m_data.Bool;
        throw aube::ErrorHandler::Raise("Vili.Vili.DataNode.WrongBoolCastOperator", {{"path", getNodePath()}});
    }
}
