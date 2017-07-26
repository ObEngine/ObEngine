#include <fstream>

#include "vili/ComplexNode.hpp"
#include "vili/NodeTemplate.hpp"
#include "vili/LinkNode.hpp"
#include "Functions.hpp"

namespace
{
    std::vector<std::string> convertPath(const std::string& path)
    {
        std::vector<std::string> vecPath = {};
        if (vili::Functions::String::occurencesInString(path, "/") >= 1)
            vecPath = vili::Functions::String::split(path, "/");
        else if (!path.empty())
            vecPath.push_back(path);
        return vecPath;
    }
}

namespace vili
{
    ComplexNode::ComplexNode(ComplexNode* parent, const std::string& id) : ContainerNode(parent, id, NodeType::ComplexNode)
    {
        m_parent = parent;
    }

    ComplexNode::ComplexNode(ComplexNode* parent, const std::string& id, ComplexNode* herit)
        : ContainerNode(parent, id, NodeType::ComplexNode)
    {
        m_parent = parent;
        this->heritage(herit);
    }

    ComplexNode::ComplexNode(ComplexNode* parent, const std::string& id, std::vector<ComplexNode*>* multipleHerit)
        : ContainerNode(parent, id, NodeType::ComplexNode)
    {
        m_parent = parent;
        for (unsigned int i = 0; i < multipleHerit->size(); i++)
            this->heritage(multipleHerit->at(i));
    }

    ComplexNode::ComplexNode(const std::string& id) : ContainerNode(nullptr, id, NodeType::ComplexNode)
    {
    }

    ComplexNode::ComplexNode(const std::string& id, ComplexNode* herit) : ContainerNode(nullptr, id, NodeType::ComplexNode)
    {
        this->heritage(herit);
    }

    ComplexNode::ComplexNode(const std::string& id, std::vector<ComplexNode*>* multipleHerit)
        : ContainerNode(nullptr, id, NodeType::ComplexNode)
    {
        for (unsigned int i = 0; i < multipleHerit->size(); i++)
            this->heritage(multipleHerit->at(i));
    }

    Node* ComplexNode::extractElement(Node* element)
    {
        if (Functions::Vector::isInList(element->getId(), m_childAttributesNames))
        {
            this->removeOwnership(element);
            m_childAttributes[element->getId()].release();
            m_childAttributes.erase(element->getId());
            Functions::Vector::eraseAll(m_childAttributesNames, element->getId());
            return element;
        }
        throw aube::ErrorHandler::Raise("Vili.Vili.ComplexAttribute.WrongExtraction", {{"path", getNodePath()},{"element", element->getNodePath()}});
    }

    void ComplexNode::heritage(ComplexNode* heritTarget)
    {
        for (const std::string& child : heritTarget->getAll(NodeType::Node))
        {
            heritTarget->get(child)->copy(this);
            this->get(child)->setVisible(false);
        }
        m_heritFrom.push_back(heritTarget->getId());
    }

    ComplexNode& ComplexNode::operator[](const std::string& cPath) const
    {
        return getPath(cPath);
    }

    ComplexNode& ComplexNode::at(const std::string& cPath) const
    {
        if (cPath.size() > 0 && Functions::String::extract(cPath, cPath.size() - 1, 0) == "/")
            return getPath(Functions::String::extract(cPath, 0, 1));
        return getPath(cPath);
    }

    ComplexNode& ComplexNode::getPath(std::string attributePath) const
    {
        if (attributePath.size() > 0 && Functions::String::extract(attributePath, attributePath.size() - 1, 0) == "/")
            attributePath = Functions::String::extract(attributePath, 0, 1);
        std::vector<std::string> sPath = convertPath(attributePath);
        if (sPath.size() > 0)
        {
            int pathIndex = 1;
            ComplexNode* getToPath = &this->getComplexAttribute(sPath[0]);
            while (pathIndex != sPath.size())
            {
                getToPath = &getToPath->getComplexAttribute(sPath[pathIndex]);
                pathIndex++;
            }
            return *getToPath;
        }
        throw aube::ErrorHandler::Raise("Vili.Vili.ComplexAttribute.EmptyPath", {{"path", getNodePath()}});
    }

    Node* ComplexNode::get(const std::string& attributeID) const
    {
        if (m_childAttributes.find(attributeID) != m_childAttributes.end())
            return m_childAttributes.at(attributeID).get();
        throw aube::ErrorHandler::Raise("Vili.Vili.ComplexAttribute.WrongGetAttributeKey", {{"attribute", attributeID},{"path", getNodePath()}});
    }

    DataNode& ComplexNode::getBaseAttribute(const std::string& attributeID) const
    {
        if (m_childAttributes.find(attributeID) != m_childAttributes.end() && m_childAttributes.at(attributeID)->getType() == NodeType::DataNode)
            return *static_cast<DataNode*>(m_childAttributes.at(attributeID).get());
        throw aube::ErrorHandler::Raise("Vili.Vili.ComplexAttribute.WrongGetBaseAttributeKey", {{"attribute", attributeID},{"path", getNodePath()}});
    }

    ArrayNode& ComplexNode::getListAttribute(const std::string& attributeID) const
    {
        if (m_childAttributes.find(attributeID) != m_childAttributes.end() && m_childAttributes.at(attributeID)->getType() == NodeType::ArrayNode)
            return *static_cast<ArrayNode*>(m_childAttributes.at(attributeID).get());
        throw aube::ErrorHandler::Raise("Vili.Vili.ComplexAttribute.WrongGetListAttributeKey", {{"attribute", attributeID},{"path", getNodePath()}});
    }

    LinkNode& ComplexNode::getLinkAttribute(const std::string& attributeID) const
    {
        if (m_childAttributes.find(attributeID) != m_childAttributes.end() && m_childAttributes.at(attributeID)->getType() == NodeType::LinkNode)
            return *static_cast<LinkNode*>(m_childAttributes.at(attributeID).get());
        throw aube::ErrorHandler::Raise("Vili.Vili.ComplexAttribute.WrongGetLinkAttributeKey", {{"attribute", attributeID},{"path", getNodePath()}});
    }

    ComplexNode& ComplexNode::getComplexAttribute(const std::string& attributeID) const
    {
        if (!m_childAttributes.empty() && m_childAttributes.find(attributeID) != m_childAttributes.end() && m_childAttributes.at(attributeID)->getType() == NodeType::ComplexNode)
            return *static_cast<ComplexNode*>(m_childAttributes.at(attributeID).get());
        throw aube::ErrorHandler::Raise("Vili.Vili.ComplexAttribute.WrongGetComplexAttributeKey", {{"attribute", attributeID},{"path", getNodePath()}});
    }

    NodeType ComplexNode::getAttributeType(const std::string& attributeID) const
    {
        return this->get(attributeID)->getType();
    }

    std::vector<std::string> ComplexNode::getAll(NodeType searchType) const
    {
        std::vector<std::string> attributes;
        for (const std::string& attributeID : m_childAttributesNames)
        {
            if (m_childAttributes.at(attributeID)->getType() == searchType)
                attributes.push_back(attributeID);
            else if (searchType == NodeType::Node)
                attributes.push_back(attributeID);
            else if (searchType == NodeType::ContainerNode && m_childAttributes.at(attributeID)->getType() == NodeType::ComplexNode)
                attributes.push_back(attributeID);
            else if (searchType == NodeType::ContainerNode && m_childAttributes.at(attributeID)->getType() == NodeType::ArrayNode)
                attributes.push_back(attributeID);
        }
        return attributes;
    }

    bool ComplexNode::contains(NodeType searchType, const std::string& attributeID) const
    {
        if (m_childAttributes.find(attributeID) != m_childAttributes.end() && m_childAttributes.at(attributeID)->getType() == searchType)
            return true;
        return false;
    }

    bool ComplexNode::contains(const std::string& attributeID) const
    {
        if (m_childAttributes.find(attributeID) != m_childAttributes.end())
            return true;
        return false;
    }

    DataNode& ComplexNode::createBaseAttribute(const std::string& attributeID, const DataType& type, const std::string& data)
    {
        m_childAttributes[attributeID] = std::make_unique<DataNode>(this, attributeID, type);
        getBaseAttribute(attributeID).autoset(data);
        if (!Functions::Vector::isInList(attributeID, m_childAttributesNames))
            m_childAttributesNames.push_back(attributeID);
        return this->getBaseAttribute(attributeID);
    }

    DataNode& ComplexNode::createBaseAttribute(const std::string& attributeID, const DataType& type)
    {
        m_childAttributes[attributeID] = std::make_unique<DataNode>(this, attributeID, type);
        if (!Functions::Vector::isInList(attributeID, m_childAttributesNames))
            m_childAttributesNames.push_back(attributeID);
        return this->getBaseAttribute(attributeID);
    }

    DataNode& ComplexNode::createBaseAttribute(const std::string& attributeID, const std::string& data)
    {
        m_childAttributes[attributeID] = std::make_unique<DataNode>(this, attributeID, DataType::String);
        getBaseAttribute(attributeID).set(data);
        if (!Functions::Vector::isInList(attributeID, m_childAttributesNames))
            m_childAttributesNames.push_back(attributeID);
        return this->getBaseAttribute(attributeID);
    }

    DataNode& ComplexNode::createBaseAttribute(const std::string& attributeID, const char* data)
    {
        this->createBaseAttribute(attributeID, std::string(data));
        return this->getBaseAttribute(attributeID);
    }

    DataNode& ComplexNode::createBaseAttribute(const std::string& attributeID, bool data)
    {
        m_childAttributes[attributeID] = std::make_unique<DataNode>(this, attributeID, DataType::Bool);
        getBaseAttribute(attributeID).set(data);
        if (!Functions::Vector::isInList(attributeID, m_childAttributesNames))
            m_childAttributesNames.push_back(attributeID);
        return this->getBaseAttribute(attributeID);
    }

    DataNode& ComplexNode::createBaseAttribute(const std::string& attributeID, int data)
    {
        m_childAttributes[attributeID] = std::make_unique<DataNode>(this, attributeID, DataType::Int);
        getBaseAttribute(attributeID).set(data);
        if (!Functions::Vector::isInList(attributeID, m_childAttributesNames))
            m_childAttributesNames.push_back(attributeID);
        return this->getBaseAttribute(attributeID);
    }

    DataNode& ComplexNode::createBaseAttribute(const std::string& attributeID, double data)
    {
        m_childAttributes[attributeID] = std::make_unique<DataNode>(this, attributeID, DataType::Float);
        getBaseAttribute(attributeID).set(data);
        if (!Functions::Vector::isInList(attributeID, m_childAttributesNames))
            m_childAttributesNames.push_back(attributeID);
        return this->getBaseAttribute(attributeID);
    }

    DataNode& ComplexNode::pushBaseAttribute(DataNode* attribute)
    {
        m_childAttributes[attribute->getId()] = std::unique_ptr<DataNode>(attribute);
        if (!Functions::Vector::isInList(attribute->getId(), m_childAttributesNames))
            m_childAttributesNames.push_back(attribute->getId());
        return this->getBaseAttribute(attribute->getId());
    }

    ArrayNode& ComplexNode::createListAttribute(const std::string& attributeID)
    {
        m_childAttributes[attributeID] = std::make_unique<ArrayNode>(this, attributeID);
        if (!Functions::Vector::isInList(attributeID, m_childAttributesNames))
            m_childAttributesNames.push_back(attributeID);
        return this->getListAttribute(attributeID);
    }

    ArrayNode& ComplexNode::pushListAttribute(ArrayNode* attribute)
    {
        m_childAttributes[attribute->getId()] = std::unique_ptr<ArrayNode>(attribute);
        if (!Functions::Vector::isInList(attribute->getId(), m_childAttributesNames))
            m_childAttributesNames.push_back(attribute->getId());
        return this->getListAttribute(attribute->getId());
    }

    ComplexNode& ComplexNode::createComplexAttribute(const std::string& attributeID)
    {
        m_childAttributes[attributeID] = std::make_unique<ComplexNode>(this, attributeID);
        if (!Functions::Vector::isInList(attributeID, m_childAttributesNames))
            m_childAttributesNames.push_back(attributeID);
        return this->getComplexAttribute(attributeID);
    }

    ComplexNode& ComplexNode::pushComplexAttribute(ComplexNode* attribute)
    {
        m_childAttributes[attribute->getId()] = std::unique_ptr<ComplexNode>(attribute);
        if (!Functions::Vector::isInList(attribute->getId(), m_childAttributesNames))
            m_childAttributesNames.push_back(attribute->getId());
        return this->getComplexAttribute(attribute->getId());
    }

    LinkNode& ComplexNode::createLinkAttribute(const std::string& attributeID, const std::string& path)
    {
        m_childAttributes[attributeID] = std::make_unique<LinkNode>(this, attributeID, path);
        if (!Functions::Vector::isInList(attributeID, m_childAttributesNames))
            m_childAttributesNames.push_back(attributeID);
        return this->getLinkAttribute(attributeID);
    }

    LinkNode& ComplexNode::pushLinkAttribute(LinkNode* attribute)
    {
        m_childAttributes[attribute->getId()] = std::unique_ptr<LinkNode>(attribute);
        if (!Functions::Vector::isInList(attribute->getId(), m_childAttributesNames))
            m_childAttributesNames.push_back(attribute->getId());
        return this->getLinkAttribute(attribute->getId());
    }

    void ComplexNode::write(std::ofstream* file, const std::string& spacing, unsigned int depth) const
    {
        if (m_visible && depth > 0)
        {
            for (unsigned int i = 0; i < depth - 1; i++)
                (*file) << spacing;
            if (m_template == nullptr)
            {
                if (m_heritFrom.empty())
                    (*file) << m_id << ":" << std::endl;
                else
                    (*file) << m_id << "(" << Functions::Vector::join(m_heritFrom, ", ") << "):" << std::endl;
            }
            else
            {
                std::vector<std::string> argsMap(m_template->getArgumentCount());
                std::string templateName = m_template->getName();

                m_template->getBody()->walk([this, &argsMap, templateName](NodeIterator& node)
                {
                    for (const std::string& currentLink : node->getAll(NodeType::LinkNode))
                    {
                        std::vector<std::string> linkParts = Functions::String::split(node->getLinkAttribute(currentLink).getPath(), "/");
                        if (Functions::String::isStringInt(linkParts[linkParts.size() - 2]) && linkParts[linkParts.size() - 1] == "value")
                        {
                            if (stoi(linkParts[linkParts.size() - 2]) <= argsMap.size())
                            {
                                std::vector<std::string> argPathFragments = Functions::String::split(node->getLinkAttribute(currentLink).getNodePath(), "/");
                                std::string returnedData = this->at<DataNode>(Functions::Vector::join(argPathFragments, "/", 2)).dumpData();
                                if (this->at<DataNode>(Functions::Vector::join(argPathFragments, "/", 2)).getDataType() == DataType::Float)
                                {
                                    while (returnedData.size() > 2 && returnedData.back() == '0' && returnedData[returnedData.size() - 2] != '.')
                                        returnedData.pop_back();
                                }
                                argsMap[stoi(linkParts[linkParts.size() - 2])] = returnedData;
                            }
                        }
                    }
                });

                (*file) << m_id << ":" << templateName << "(";
                for (int i = 0; i < argsMap.size(); i++)
                    (*file) << argsMap[i] << ((i < argsMap.size() - 1) ? ", " : "");
                (*file) << ")" << std::endl;
            }
        }
        if (m_visible && m_template == nullptr)
        {
            for (const std::string& child : m_childAttributesNames)
                m_childAttributes.at(child)->write(file, spacing, depth + 1);
            if (depth == 1)
                (*file) << std::endl;
        }
    }

    void ComplexNode::deleteBaseAttribute(const std::string& attributeID, bool freeMemory)
    {
        if (Functions::Vector::isInList(attributeID, this->getAll(NodeType::DataNode)))
            m_childAttributesNames.erase(m_childAttributesNames.begin() + Functions::Vector::indexOfElement(attributeID, m_childAttributesNames));
        typedef std::map<std::string, std::unique_ptr<Node>>::iterator it_type;
        it_type itDel = m_childAttributes.find(attributeID);
        if (itDel != m_childAttributes.end() && m_childAttributes[attributeID]->getType() == NodeType::DataNode)
        {
            if (!freeMemory)
                m_childAttributes[attributeID].release();
            m_childAttributes.erase(itDel);
        }
    }

    void ComplexNode::deleteComplexAttribute(const std::string& attributeID, bool freeMemory)
    {
        if (Functions::Vector::isInList(attributeID, this->getAll(NodeType::ComplexNode)))
            m_childAttributesNames.erase(m_childAttributesNames.begin() + Functions::Vector::indexOfElement(attributeID, m_childAttributesNames));
        typedef std::map<std::string, std::unique_ptr<Node>>::iterator it_type;
        it_type itDel = m_childAttributes.find(attributeID);
        if (itDel != m_childAttributes.end() && m_childAttributes[attributeID]->getType() == NodeType::ComplexNode)
        {
            if (!freeMemory)
                m_childAttributes[attributeID].release();
            m_childAttributes.erase(itDel);
        }
    }

    void ComplexNode::deleteListAttribute(const std::string& attributeID, bool freeMemory)
    {
        if (Functions::Vector::isInList(attributeID, this->getAll(NodeType::ArrayNode)))
            m_childAttributesNames.erase(m_childAttributesNames.begin() + Functions::Vector::indexOfElement(attributeID, m_childAttributesNames));
        typedef std::map<std::string, std::unique_ptr<Node>>::iterator it_type;
        it_type itDel = m_childAttributes.find(attributeID);
        if (itDel != m_childAttributes.end() && m_childAttributes[attributeID]->getType() == NodeType::ArrayNode)
        {
            if (!freeMemory)
                m_childAttributes[attributeID].release();
            m_childAttributes.erase(itDel);
        }
    }

    void ComplexNode::deleteLinkAttribute(const std::string& attributeID, bool freeMemory)
    {
        if (Functions::Vector::isInList(attributeID, this->getAll(NodeType::LinkNode)))
            m_childAttributesNames.erase(m_childAttributesNames.begin() + Functions::Vector::indexOfElement(attributeID, m_childAttributesNames));
        typedef std::map<std::string, std::unique_ptr<Node>>::iterator it_type;
        it_type itDel = m_childAttributes.find(attributeID);
        if (itDel != m_childAttributes.end() && m_childAttributes[attributeID]->getType() == NodeType::LinkNode)
        {
            if (!freeMemory)
                m_childAttributes[attributeID].release();
            m_childAttributes.erase(itDel);
        }
    }

    void ComplexNode::copy(ContainerNode* newParent, const std::string& newid) const
    {
        std::string useID = (newid.empty()) ? this->m_id : newid;
        if (newParent->getType() == NodeType::ComplexNode)
        {
            dynamic_cast<ComplexNode*>(newParent)->createComplexAttribute(useID);
            for (const std::string& child : m_childAttributesNames)
            {
                m_childAttributes.at(child)->copy(&dynamic_cast<ComplexNode*>(newParent)->getComplexAttribute(useID));
            }
        }
        else
            throw aube::ErrorHandler::Raise("Vili.Vili.ComplexAttribute.WrongCopyTarget", {{"path", getNodePath()},{"target", newParent->getNodePath()}});
    }

    void ComplexNode::walk(std::function<void(NodeIterator&)> walkFunction, bool useCache)
    {
        if (useCache)
        {
            NodeIterator baseIterator(this);
            while (!baseIterator.last())
            {
                baseIterator.next();
                walkFunction(baseIterator);
            }
        }
        else
        {
            NodeIterator baseIterator;
            for (const std::string& complex : getAll(NodeType::ComplexNode))
            {
                if (!baseIterator.over())
                    getComplexAttribute(complex).walk(walkFunction, baseIterator);
                else
                    break;
            }
            if (!baseIterator.over())
            {
                baseIterator.next(this);
                walkFunction(baseIterator);
            }
        }
    }

    void ComplexNode::walk(std::function<void(NodeIterator&)> walkFunction, NodeIterator& iterator)
    {
        for (const std::string& complex : getAll(NodeType::ComplexNode))
        {
            if (!iterator.over())
                getComplexAttribute(complex).walk(walkFunction, iterator);
            else
                break;
        }
        if (!iterator.over())
        {
            iterator.next(this);
            walkFunction(iterator);
        }
    }

    void ComplexNode::useTemplate(NodeTemplate* useTemplate)
    {
        m_template = useTemplate;
    }

    NodeTemplate* ComplexNode::getCurrentTemplate() const
    {
        return m_template;
    }
}
