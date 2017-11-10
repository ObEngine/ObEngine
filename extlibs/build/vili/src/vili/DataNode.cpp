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
            stream << std::get<int>(attribute.m_data);
        else if (attribute.getDataType() == DataType::Float)
            stream << std::get<double>(attribute.m_data);
        else if (attribute.getDataType() == DataType::Bool)
            stream << std::get<bool>(attribute.m_data);
        else if (attribute.getDataType() == DataType::String)
            stream << std::get<std::string>(attribute.m_data);
        return stream;
    }

    DataNode::DataNode(ContainerNode* parent, const std::string& id, const DataType& dataType) : Node(parent, id, NodeType::DataNode)
    {
        m_dataType = dataType;
    }

    DataNode::DataNode(const std::string& id, const DataType& dataType) : Node(nullptr, id, NodeType::DataNode)
    {
        m_dataType = dataType;
    }

    DataNode::DataNode(const DataNode& copy) : Node(copy)
    {
        m_dataType = copy.m_dataType;
    }

    DataNode::~DataNode()
    {
    }

    void DataNode::set(int var)
    {
        if (m_dataType == DataType::Int)
            m_data = var;
        else
            throw aube::ErrorHandler::Raise("Vili.Vili.DataNode.WrongIntSet", {{"path", getNodePath()},{"type", Types::dataTypeToString(m_dataType)}});
    }

    void DataNode::set(double var)
    {
        if (m_dataType == DataType::Float)
            m_data = var;
        else
            throw aube::ErrorHandler::Raise("Vili.Vili.DataNode.WrongFloatSet", {{"path", getNodePath()},{"type", Types::dataTypeToString(m_dataType)}});
    }

    void DataNode::set(const std::string& var)
    {
        if (m_dataType == DataType::String)
            m_data = var;
        else
            throw aube::ErrorHandler::Raise("Vili.Vili.DataNode.WrongStringSet", {{"path", getNodePath()},{"type", Types::dataTypeToString(m_dataType)}});
    }

    void DataNode::set(const char* var)
    {
        if (m_dataType == DataType::String)
            m_data = std::string(var);
        else
            throw aube::ErrorHandler::Raise("Vili.Vili.DataNode.WrongStringSet", {{"path", getNodePath()},{"type", Types::dataTypeToString(m_dataType)}});
    }

    void DataNode::set(bool var)
    {
        if (m_dataType == DataType::Bool)
            m_data = var;
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
                m_data = stoi(rawData);
            else if (m_dataType == DataType::Float)
                m_data = stod(rawData);
            else if (m_dataType == DataType::String)
                m_data = Functions::String::extract(rawData, 1, 1);
            else if (m_dataType == DataType::Bool)
                m_data = (rawData == "True" ? true : false);
        }
        else
            throw aube::ErrorHandler::Raise("Vili.Vili.DataNode.WrongAutoset", {{"data", rawData},{"path", getNodePath()}});
    }

    std::string DataNode::dumpData() const
    {
        if (m_dataType == DataType::String)
            return "\"" + std::get<std::string>(m_data) + "\"";
        if (m_dataType == DataType::Int)
            return std::to_string(std::get<int>(m_data));
        if (m_dataType == DataType::Float)
            return std::to_string(std::get<double>(m_data));
        if (m_dataType == DataType::Bool)
            return (std::get<bool>(m_data) ? "True" : "False");
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
                newCopy->set(std::get<int>(m_data));
            else if (m_dataType == DataType::Float)
                newCopy->set(std::get<double>(m_data));
            else if (m_dataType == DataType::Bool)
                newCopy->set(std::get<bool>(m_data));
            else if (m_dataType == DataType::String)
                newCopy->set(std::get<std::string>(m_data));
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
            return std::get<std::string>(m_data);
        throw aube::ErrorHandler::Raise("Vili.Vili.DataNode.WrongStringCastOperator", {{"path", getNodePath()}});
    }

	DataNode::operator unsigned int() const
	{
		return int(*this);
	}

	DataNode::operator int() const
    {
        if (m_dataType == DataType::Int)
            return std::get<int>(m_data);
        throw aube::ErrorHandler::Raise("Vili.Vili.DataNode.WrongIntCastOperator", {{"path", getNodePath()}});
    }

    DataNode::operator double() const
    {
        if (m_dataType == DataType::Float)
            return std::get<double>(m_data);
        throw aube::ErrorHandler::Raise("Vili.Vili.DataNode.WrongFloatCastOperator", {{"path", getNodePath()}});
    }

    DataNode::operator bool() const
    {
        if (m_dataType == DataType::Bool)
            return std::get<bool>(m_data);
        throw aube::ErrorHandler::Raise("Vili.Vili.DataNode.WrongBoolCastOperator", {{"path", getNodePath()}});
    }
}
