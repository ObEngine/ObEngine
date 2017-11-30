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
        for (auto& child : copy.m_children)
        {
            child->copy(this);
        }
        m_heritFrom = copy.m_heritFrom;
        m_template = nullptr;
    }

    std::unique_ptr<Node>& ComplexNode::getNodePtr(const std::string& id)
    {
        for (auto& child : m_children)
        {
            if (child->getId() == id)
                return child;
        }
        throw aube::ErrorHandler::Raise("Vili.Vili.ComplexNode.NodeNotFound", {{"path", getNodePath()}, {"node", id}});
    }

    Node* ComplexNode::extractElement(Node* element)
    {
        if (this->contains(element->getId()))
        {
            this->removeOwnership(element);
            unsigned int fIndex = 0;
            for (unsigned int i = 0; i < m_children.size(); i++)
            {
                if (element->getId() == m_children[i]->getId())
                    fIndex = i;
            }
            this->getNodePtr(element->getId()).release();
            m_children.erase(m_children.begin() + fIndex);
            return element;
        }
        throw aube::ErrorHandler::Raise("Vili.Vili.ComplexNode.WrongExtraction", {{"path", getNodePath()},{"element", element->getNodePath()}});
    }

    void ComplexNode::heritage(ComplexNode* heritTarget)
    {
        for (auto& child : heritTarget->getAll(NodeType::Node))
        {
            child->copy(this);
            child->setVisible(false);
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
        for (auto& child : m_children)
        {
            if (child->getId() == id)
                return child.get();
        }
        throw aube::ErrorHandler::Raise("Vili.Vili.ComplexNode.WrongGetAttributeKey", {{"node", id},{"path", getNodePath()}});
    }

    DataNode& ComplexNode::getDataNode(const std::string& id) const
    {
        return *static_cast<DataNode*>(this->get(id));
    }

    ArrayNode& ComplexNode::getArrayNode(const std::string& id) const
    {
        return *static_cast<ArrayNode*>(this->get(id));
    }

    LinkNode& ComplexNode::getLinkNode(const std::string& id) const
    {
        return *static_cast<LinkNode*>(this->get(id));
    }

    ComplexNode& ComplexNode::getComplexNode(const std::string& id) const
    {
        return *static_cast<ComplexNode*>(this->get(id));
    }

    NodeType ComplexNode::getNodeType(const std::string& id) const
    {
        return this->get(id)->getType();
    }

    std::vector<Node*> ComplexNode::getAll(NodeType searchType) const
    {
        std::vector<Node*> nodes;
        for (auto& child : m_children)
        {
            if (child->getType() == searchType)
                nodes.push_back(child.get());
            else if (searchType == NodeType::Node)
                nodes.push_back(child.get());
            else if (searchType == NodeType::ContainerNode && child->getType() == NodeType::ComplexNode)
                nodes.push_back(child.get());
            else if (searchType == NodeType::ContainerNode && child->getType() == NodeType::ArrayNode)
                nodes.push_back(child.get());
        }
        return nodes;
    }

    bool ComplexNode::contains(NodeType searchType, const std::string& id) const
    {
        for (auto& child : m_children)
        {
            if (child->getId() == id && child->getType() == searchType)
                return true;
        }
        return false;
    }

    bool ComplexNode::contains(const std::string& id) const
    {
        for (auto& child : m_children)
        {
            if (child->getId() == id)
                return true;
        }
        return false;
    }

    DataNode& ComplexNode::createDataNode(const std::string& id, const DataType& type, const std::string& data)
    {
        if (!this->contains(id))
            m_children.push_back(std::make_unique<DataNode>(this, id, type));
        this->getDataNode(id).autoset(data);
        return this->getDataNode(id);
    }

    DataNode& ComplexNode::createDataNode(const std::string& id, const DataType& type)
    {
        if (!this->contains(id))
            m_children.push_back(std::make_unique<DataNode>(this, id, type));
        return this->getDataNode(id);
    }

    DataNode& ComplexNode::createDataNode(const std::string& id, const std::string& data)
    {
        if (!this->contains(id))
            m_children.push_back(std::make_unique<DataNode>(this, id, DataType::String));
        this->getDataNode(id).set(data);
        return this->getDataNode(id);
    }

    DataNode& ComplexNode::createDataNode(const std::string& id, const char* data)
    {
        this->createDataNode(id, std::string(data));
        return this->getDataNode(id);
    }

    DataNode& ComplexNode::createDataNode(const std::string& id, bool data)
    {
        if (!this->contains(id))
            m_children.push_back(std::make_unique<DataNode>(this, id, DataType::Bool));
        this->getDataNode(id).set(data);
        return this->getDataNode(id);
    }

    DataNode& ComplexNode::createDataNode(const std::string& id, int data)
    {
        if (!this->contains(id))
            m_children.push_back(std::make_unique<DataNode>(this, id, DataType::Int));
        this->getDataNode(id).set(data);
        return this->getDataNode(id);
    }

    DataNode& ComplexNode::createDataNode(const std::string& id, double data)
    {
        if (!this->contains(id))
            m_children.push_back(std::make_unique<DataNode>(this, id, DataType::Float));
        this->getDataNode(id).set(data);
        return this->getDataNode(id);
    }

    DataNode& ComplexNode::pushDataNode(DataNode* attribute)
    {
        attribute->setParent(this);
        if (!this->contains(attribute->getId()))
            m_children.push_back(std::unique_ptr<DataNode>(attribute));
        else
            this->getNodePtr(attribute->getId()).reset(attribute);
        return this->getDataNode(attribute->getId());
    }

    ArrayNode& ComplexNode::createArrayNode(const std::string& id)
    {
        if (!this->contains(id))
            m_children.push_back(std::make_unique<ArrayNode>(this, id));
        return this->getArrayNode(id);
    }

    ArrayNode& ComplexNode::pushArrayNode(ArrayNode* attribute)
    {
        attribute->setParent(this);
        if (!this->contains(attribute->getId()))
            m_children.push_back(std::unique_ptr<ArrayNode>(attribute));
        else
            this->getNodePtr(attribute->getId()).reset(attribute);
        return this->getArrayNode(attribute->getId());
    }

    ComplexNode& ComplexNode::createComplexNode(const std::string& id)
    {
        if (!this->contains(id))
            m_children.push_back(std::make_unique<ComplexNode>(this, id));
        return this->getComplexNode(id);
    }

    ComplexNode& ComplexNode::pushComplexNode(ComplexNode* attribute)
    {
        attribute->setParent(this);
        if (!this->contains(attribute->getId()))
            m_children.push_back(std::unique_ptr<ComplexNode>(attribute));
        else
            this->getNodePtr(attribute->getId()).reset(attribute);
        return this->getComplexNode(attribute->getId());
    }

    LinkNode& ComplexNode::createLinkNode(const std::string& id, const std::string& path)
    {
        if (!this->contains(id))
            m_children.push_back(std::make_unique<LinkNode>(this, id, path));
        return this->getLinkNode(id);
    }

    LinkNode& ComplexNode::pushLinkNode(LinkNode* attribute)
    {
        attribute->setParent(this);
        if (!this->contains(attribute->getId()))
            m_children.push_back(std::unique_ptr<LinkNode>(attribute));
        else
            this->getNodePtr(attribute->getId()).reset(attribute);
        return this->getLinkNode(attribute->getId());
    }

    void ComplexNode::write(std::ofstream* file, const std::string& spacing, unsigned int depth) const
    {
        std::cout << "Writing : " << m_id << " with visibility " << m_visible << std::endl;
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
                    for (LinkNode* link : node->getAll<LinkNode>())
                    {
                        std::vector<std::string> linkParts = Functions::String::split(link->getPath(), "/");
                        if (Functions::String::isStringInt(linkParts[linkParts.size() - 2]) && linkParts[linkParts.size() - 1] == "value")
                        {
                            if (stoi(linkParts[linkParts.size() - 2]) <= argsMap.size())
                            {
                                std::vector<std::string> argPathFragments = Functions::String::split(link->getNodePath(), "/");
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
            for (auto& child : m_children)
                child->write(file, spacing, depth + 1);
            if (depth == 1)
                (*file) << std::endl;
        }
    }

    void ComplexNode::remove(const std::string& id)
    {
        m_children.erase(std::remove_if(m_children.begin(), m_children.end(), [&id](auto& child)
        {
            return (child->getId() == id);
        }), m_children.end());
    }

    void ComplexNode::clear()
    {
        m_children.clear();
    }

    void ComplexNode::copy(ContainerNode* newParent, const std::string& newid) const
    {
        std::string useID = (newid.empty()) ? this->m_id : newid;
        if (newParent->getType() == NodeType::ComplexNode)
        {
            dynamic_cast<ComplexNode*>(newParent)->createComplexNode(useID);
            for (auto& child : m_children)
            {
                child->copy(&dynamic_cast<ComplexNode*>(newParent)->getComplexNode(useID));
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
            for (ComplexNode* complex : this->getAll<ComplexNode>())
            {
                if (!baseIterator.over())
                    complex->walk(walkFunction, baseIterator);
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
        for (ComplexNode* complex : this->getAll<ComplexNode>())
        {
            if (!iterator.over())
                complex->walk(walkFunction, iterator);
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
