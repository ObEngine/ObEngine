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
    ComplexNode::ComplexNode(const std::string& id) : ContainerNode(nullptr, id, NodeType::ComplexNode)
    {
    }

    ComplexNode::ComplexNode(const ComplexNode& copy) : ContainerNode(copy)
    {
        for (auto& child : copy.m_childAttributes)
        {
            m_childAttributes[child.first]->copy(this);
        }
        m_childAttributesNames = copy.m_childAttributesNames;
        m_heritFrom = copy.m_heritFrom;
        m_template = nullptr;
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
        throw aube::ErrorHandler::Raise("Vili.Vili.ComplexNode.WrongExtraction", {{"path", getNodePath()},{"element", element->getNodePath()}});
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
            ComplexNode* getToPath = &this->getComplexNode(sPath[0]);
            while (pathIndex != sPath.size())
            {
                getToPath = &getToPath->getComplexNode(sPath[pathIndex]);
                pathIndex++;
            }
            return *getToPath;
        }
        throw aube::ErrorHandler::Raise("Vili.Vili.ComplexNode.EmptyPath", {{"path", getNodePath()}});
    }

    Node* ComplexNode::get(const std::string& id) const
    {
        if (m_childAttributes.find(id) != m_childAttributes.end())
            return m_childAttributes.at(id).get();
        throw aube::ErrorHandler::Raise("Vili.Vili.ComplexNode.WrongGetAttributeKey", {{"node", id},{"path", getNodePath()}});
    }

    DataNode& ComplexNode::getDataNode(const std::string& id) const
    {
        if (m_childAttributes.find(id) != m_childAttributes.end() && m_childAttributes.at(id)->getType() == NodeType::DataNode)
            return *static_cast<DataNode*>(m_childAttributes.at(id).get());
        throw aube::ErrorHandler::Raise("Vili.Vili.ComplexNode.WrongGetBaseAttributeKey", {{"node", id},{"path", getNodePath()}});
    }

    ArrayNode& ComplexNode::getArrayNode(const std::string& id) const
    {
        if (m_childAttributes.find(id) != m_childAttributes.end() && m_childAttributes.at(id)->getType() == NodeType::ArrayNode)
            return *static_cast<ArrayNode*>(m_childAttributes.at(id).get());
        throw aube::ErrorHandler::Raise("Vili.Vili.ComplexNode.WrongGetListAttributeKey", {{"node", id},{"path", getNodePath()}});
    }

    LinkNode& ComplexNode::getLinkNode(const std::string& id) const
    {
        if (m_childAttributes.find(id) != m_childAttributes.end() && m_childAttributes.at(id)->getType() == NodeType::LinkNode)
            return *static_cast<LinkNode*>(m_childAttributes.at(id).get());
        throw aube::ErrorHandler::Raise("Vili.Vili.ComplexNode.WrongGetLinkAttributeKey", {{"node", id},{"path", getNodePath()}});
    }

    ComplexNode& ComplexNode::getComplexNode(const std::string& id) const
    {
        if (!m_childAttributes.empty() && m_childAttributes.find(id) != m_childAttributes.end() && m_childAttributes.at(id)->getType() == NodeType::ComplexNode)
            return *static_cast<ComplexNode*>(m_childAttributes.at(id).get());
        throw aube::ErrorHandler::Raise("Vili.Vili.ComplexNode.WrongGetComplexNodeKey", {{"node", id},{"path", getNodePath()}});
    }

    NodeType ComplexNode::getNodeType(const std::string& id) const
    {
        return this->get(id)->getType();
    }

    std::vector<std::string> ComplexNode::getAll(NodeType searchType) const
    {
        std::vector<std::string> attributes;
        for (const std::string& id : m_childAttributesNames)
        {
            if (m_childAttributes.at(id)->getType() == searchType)
                attributes.push_back(id);
            else if (searchType == NodeType::Node)
                attributes.push_back(id);
            else if (searchType == NodeType::ContainerNode && m_childAttributes.at(id)->getType() == NodeType::ComplexNode)
                attributes.push_back(id);
            else if (searchType == NodeType::ContainerNode && m_childAttributes.at(id)->getType() == NodeType::ArrayNode)
                attributes.push_back(id);
        }
        return attributes;
    }

    bool ComplexNode::contains(NodeType searchType, const std::string& id) const
    {
        if (m_childAttributes.find(id) != m_childAttributes.end() && m_childAttributes.at(id)->getType() == searchType)
            return true;
        return false;
    }

    bool ComplexNode::contains(const std::string& id) const
    {
        if (m_childAttributes.find(id) != m_childAttributes.end())
            return true;
        return false;
    }

    DataNode& ComplexNode::createDataNode(const std::string& id, const DataType& type, const std::string& data)
    {
        m_childAttributes[id] = std::make_unique<DataNode>(this, id, type);
        getDataNode(id).autoset(data);
        if (!Functions::Vector::isInList(id, m_childAttributesNames))
            m_childAttributesNames.push_back(id);
        return this->getDataNode(id);
    }

    DataNode& ComplexNode::createDataNode(const std::string& id, const DataType& type)
    {
        m_childAttributes[id] = std::make_unique<DataNode>(this, id, type);
        if (!Functions::Vector::isInList(id, m_childAttributesNames))
            m_childAttributesNames.push_back(id);
        return this->getDataNode(id);
    }

    DataNode& ComplexNode::createDataNode(const std::string& id, const std::string& data)
    {
        m_childAttributes[id] = std::make_unique<DataNode>(this, id, DataType::String);
        getDataNode(id).set(data);
        if (!Functions::Vector::isInList(id, m_childAttributesNames))
            m_childAttributesNames.push_back(id);
        return this->getDataNode(id);
    }

    DataNode& ComplexNode::createDataNode(const std::string& id, const char* data)
    {
        this->createDataNode(id, std::string(data));
        return this->getDataNode(id);
    }

    DataNode& ComplexNode::createDataNode(const std::string& id, bool data)
    {
        m_childAttributes[id] = std::make_unique<DataNode>(this, id, DataType::Bool);
        getDataNode(id).set(data);
        if (!Functions::Vector::isInList(id, m_childAttributesNames))
            m_childAttributesNames.push_back(id);
        return this->getDataNode(id);
    }

    DataNode& ComplexNode::createDataNode(const std::string& id, int data)
    {
        m_childAttributes[id] = std::make_unique<DataNode>(this, id, DataType::Int);
        getDataNode(id).set(data);
        if (!Functions::Vector::isInList(id, m_childAttributesNames))
            m_childAttributesNames.push_back(id);
        return this->getDataNode(id);
    }

    DataNode& ComplexNode::createDataNode(const std::string& id, double data)
    {
        m_childAttributes[id] = std::make_unique<DataNode>(this, id, DataType::Float);
        getDataNode(id).set(data);
        if (!Functions::Vector::isInList(id, m_childAttributesNames))
            m_childAttributesNames.push_back(id);
        return this->getDataNode(id);
    }

    DataNode& ComplexNode::pushDataNode(DataNode* attribute)
    {
        m_childAttributes[attribute->getId()] = std::unique_ptr<DataNode>(attribute);
        if (!Functions::Vector::isInList(attribute->getId(), m_childAttributesNames))
            m_childAttributesNames.push_back(attribute->getId());
        return this->getDataNode(attribute->getId());
    }

    ArrayNode& ComplexNode::createArrayNode(const std::string& id)
    {
        m_childAttributes[id] = std::make_unique<ArrayNode>(this, id);
        if (!Functions::Vector::isInList(id, m_childAttributesNames))
            m_childAttributesNames.push_back(id);
        return this->getArrayNode(id);
    }

    ArrayNode& ComplexNode::pushArrayNode(ArrayNode* attribute)
    {
        m_childAttributes[attribute->getId()] = std::unique_ptr<ArrayNode>(attribute);
        if (!Functions::Vector::isInList(attribute->getId(), m_childAttributesNames))
            m_childAttributesNames.push_back(attribute->getId());
        return this->getArrayNode(attribute->getId());
    }

    ComplexNode& ComplexNode::createComplexNode(const std::string& id)
    {
        m_childAttributes[id] = std::make_unique<ComplexNode>(this, id);
        if (!Functions::Vector::isInList(id, m_childAttributesNames))
            m_childAttributesNames.push_back(id);
        return this->getComplexNode(id);
    }

    ComplexNode& ComplexNode::pushComplexNode(ComplexNode* attribute)
    {
        m_childAttributes[attribute->getId()] = std::unique_ptr<ComplexNode>(attribute);
        if (!Functions::Vector::isInList(attribute->getId(), m_childAttributesNames))
            m_childAttributesNames.push_back(attribute->getId());
        return this->getComplexNode(attribute->getId());
    }

    LinkNode& ComplexNode::createLinkNode(const std::string& id, const std::string& path)
    {
        m_childAttributes[id] = std::make_unique<LinkNode>(this, id, path);
        if (!Functions::Vector::isInList(id, m_childAttributesNames))
            m_childAttributesNames.push_back(id);
        return this->getLinkNode(id);
    }

    LinkNode& ComplexNode::pushLinkNode(LinkNode* attribute)
    {
        m_childAttributes[attribute->getId()] = std::unique_ptr<LinkNode>(attribute);
        if (!Functions::Vector::isInList(attribute->getId(), m_childAttributesNames))
            m_childAttributesNames.push_back(attribute->getId());
        return this->getLinkNode(attribute->getId());
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
                        std::vector<std::string> linkParts = Functions::String::split(node->getLinkNode(currentLink).getPath(), "/");
                        if (Functions::String::isStringInt(linkParts[linkParts.size() - 2]) && linkParts[linkParts.size() - 1] == "value")
                        {
                            if (stoi(linkParts[linkParts.size() - 2]) <= argsMap.size())
                            {
                                std::vector<std::string> argPathFragments = Functions::String::split(node->getLinkNode(currentLink).getNodePath(), "/");
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

    void ComplexNode::removeNode(NodeType nodeType, const std::string& id, bool freeMemory)
    {
        if (Functions::Vector::isInList(id, this->getAll(nodeType)))
            m_childAttributesNames.erase(m_childAttributesNames.begin() + Functions::Vector::indexOfElement(id, m_childAttributesNames));
        typedef std::map<std::string, std::unique_ptr<Node>>::iterator it_type;
        it_type itDel = m_childAttributes.find(id);
        if (itDel != m_childAttributes.end() && m_childAttributes[id]->getType() == nodeType)
        {
            if (!freeMemory)
                m_childAttributes[id].release();
            m_childAttributes.erase(itDel);
        }
        else
        {
            // Add error <REVISION>
        }
    }

    void ComplexNode::copy(ContainerNode* newParent, const std::string& newid) const
    {
        std::string useID = (newid.empty()) ? this->m_id : newid;
        if (newParent->getType() == NodeType::ComplexNode)
        {
            dynamic_cast<ComplexNode*>(newParent)->createComplexNode(useID);
            for (const std::string& child : m_childAttributesNames)
            {
                m_childAttributes.at(child)->copy(&dynamic_cast<ComplexNode*>(newParent)->getComplexNode(useID));
            }
        }
        else
            throw aube::ErrorHandler::Raise("Vili.Vili.ComplexNode.WrongCopyTarget", {{"path", getNodePath()},{"target", newParent->getNodePath()}});
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
                    getComplexNode(complex).walk(walkFunction, baseIterator);
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
                getComplexNode(complex).walk(walkFunction, iterator);
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

    ComplexNode::~ComplexNode()
    {
    }
}
