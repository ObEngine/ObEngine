#include <fstream>

#include "vili/ComplexAttribute.hpp"
#include "vili/DataTemplate.hpp"
#include "vili/LinkAttribute.hpp"
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
    ComplexAttribute::ComplexAttribute(ComplexAttribute* parent, const std::string& id) : ContainerAttribute(parent, id, Types::ComplexAttribute)
    {
        m_parent = parent;
    }

    ComplexAttribute::ComplexAttribute(ComplexAttribute* parent, const std::string& id, ComplexAttribute* herit)
        : ContainerAttribute(parent, id, Types::ComplexAttribute)
    {
        m_parent = parent;
        this->heritage(herit);
    }

    ComplexAttribute::ComplexAttribute(ComplexAttribute* parent, const std::string& id, std::vector<ComplexAttribute*>* multipleHerit)
        : ContainerAttribute(parent, id, Types::ComplexAttribute)
    {
        m_parent = parent;
        for (unsigned int i = 0; i < multipleHerit->size(); i++)
            this->heritage(multipleHerit->at(i));
    }

    ComplexAttribute::ComplexAttribute(const std::string& id) : ContainerAttribute(nullptr, id, Types::ComplexAttribute)
    {
    }

    ComplexAttribute::ComplexAttribute(const std::string& id, ComplexAttribute* herit) : ContainerAttribute(nullptr, id, Types::ComplexAttribute)
    {
        this->heritage(herit);
    }

    ComplexAttribute::ComplexAttribute(const std::string& id, std::vector<ComplexAttribute*>* multipleHerit)
        : ContainerAttribute(nullptr, id, Types::ComplexAttribute)
    {
        for (unsigned int i = 0; i < multipleHerit->size(); i++)
            this->heritage(multipleHerit->at(i));
    }

    Attribute* ComplexAttribute::extractElement(Attribute* element)
    {
        if (Functions::Vector::isInList(element->getID(), m_childAttributesNames))
        {
            this->removeOwnership(element);
            m_childAttributes[element->getID()].release();
            m_childAttributes.erase(element->getID());
            Functions::Vector::eraseAll(m_childAttributesNames, element->getID());
            return element;
        }
        throw aube::ErrorHandler::Raise("Vili.Vili.ComplexAttribute.WrongExtraction", {{"path", getNodePath()},{"element", element->getNodePath()}});
    }

    void ComplexAttribute::heritage(ComplexAttribute* heritTarget)
    {
        for (const std::string& child : heritTarget->getAll(Types::Attribute))
        {
            heritTarget->get(child)->copy(this);
            this->get(child)->setVisible(false);
        }
        m_heritFrom.push_back(heritTarget->getID());
    }

    ComplexAttribute& ComplexAttribute::operator[](const std::string& cPath) const
    {
        return getPath(cPath);
    }

    ComplexAttribute& ComplexAttribute::at(const std::string& cPath) const
    {
        if (cPath.size() > 0 && Functions::String::extract(cPath, cPath.size() - 1, 0) == "/")
            return getPath(Functions::String::extract(cPath, 0, 1));
        return getPath(cPath);
    }

    ComplexAttribute& ComplexAttribute::getPath(std::string attributePath) const
    {
        if (attributePath.size() > 0 && Functions::String::extract(attributePath, attributePath.size() - 1, 0) == "/")
            attributePath = Functions::String::extract(attributePath, 0, 1);
        std::vector<std::string> sPath = convertPath(attributePath);
        if (sPath.size() > 0)
        {
            int pathIndex = 1;
            ComplexAttribute* getToPath = &this->getComplexAttribute(sPath[0]);
            while (pathIndex != sPath.size())
            {
                getToPath = &getToPath->getComplexAttribute(sPath[pathIndex]);
                pathIndex++;
            }
            return *getToPath;
        }
        throw aube::ErrorHandler::Raise("Vili.Vili.ComplexAttribute.EmptyPath", {{"path", getNodePath()}});
    }

    Attribute* ComplexAttribute::get(const std::string& attributeID) const
    {
        if (m_childAttributes.find(attributeID) != m_childAttributes.end())
            return m_childAttributes.at(attributeID).get();
        throw aube::ErrorHandler::Raise("Vili.Vili.ComplexAttribute.WrongGetAttributeKey", {{"attribute", attributeID},{"path", getNodePath()}});
    }

    BaseAttribute& ComplexAttribute::getBaseAttribute(const std::string& attributeID) const
    {
        if (m_childAttributes.find(attributeID) != m_childAttributes.end() && m_childAttributes.at(attributeID)->getType() == Types::BaseAttribute)
            return *static_cast<BaseAttribute*>(m_childAttributes.at(attributeID).get());
        throw aube::ErrorHandler::Raise("Vili.Vili.ComplexAttribute.WrongGetBaseAttributeKey", {{"attribute", attributeID},{"path", getNodePath()}});
    }

    ListAttribute& ComplexAttribute::getListAttribute(const std::string& attributeID) const
    {
        if (m_childAttributes.find(attributeID) != m_childAttributes.end() && m_childAttributes.at(attributeID)->getType() == Types::ListAttribute)
            return *static_cast<ListAttribute*>(m_childAttributes.at(attributeID).get());
        throw aube::ErrorHandler::Raise("Vili.Vili.ComplexAttribute.WrongGetListAttributeKey", {{"attribute", attributeID},{"path", getNodePath()}});
    }

    LinkAttribute& ComplexAttribute::getLinkAttribute(const std::string& attributeID) const
    {
        if (m_childAttributes.find(attributeID) != m_childAttributes.end() && m_childAttributes.at(attributeID)->getType() == Types::LinkAttribute)
            return *static_cast<LinkAttribute*>(m_childAttributes.at(attributeID).get());
        throw aube::ErrorHandler::Raise("Vili.Vili.ComplexAttribute.WrongGetLinkAttributeKey", {{"attribute", attributeID},{"path", getNodePath()}});
    }

    ComplexAttribute& ComplexAttribute::getComplexAttribute(const std::string& attributeID) const
    {
        if (!m_childAttributes.empty() && m_childAttributes.find(attributeID) != m_childAttributes.end() && m_childAttributes.at(attributeID)->getType() == Types::ComplexAttribute)
            return *static_cast<ComplexAttribute*>(m_childAttributes.at(attributeID).get());
        throw aube::ErrorHandler::Raise("Vili.Vili.ComplexAttribute.WrongGetComplexAttributeKey", {{"attribute", attributeID},{"path", getNodePath()}});
    }

    Types::AttributeType ComplexAttribute::getAttributeType(const std::string& attributeID) const
    {
        return this->get(attributeID)->getType();
    }

    std::vector<std::string> ComplexAttribute::getAll(Types::AttributeType searchType) const
    {
        std::vector<std::string> attributes;
        for (const std::string& attributeID : m_childAttributesNames)
        {
            if (m_childAttributes.at(attributeID)->getType() == searchType)
                attributes.push_back(attributeID);
            else if (searchType == Types::Attribute)
                attributes.push_back(attributeID);
            else if (searchType == Types::ContainerAttribute && m_childAttributes.at(attributeID)->getType() == Types::ComplexAttribute)
                attributes.push_back(attributeID);
            else if (searchType == Types::ContainerAttribute && m_childAttributes.at(attributeID)->getType() == Types::ListAttribute)
                attributes.push_back(attributeID);
        }
        return attributes;
    }

    bool ComplexAttribute::contains(Types::AttributeType searchType, const std::string& attributeID) const
    {
        if (m_childAttributes.find(attributeID) != m_childAttributes.end() && m_childAttributes.at(attributeID)->getType() == searchType)
            return true;
        return false;
    }

    bool ComplexAttribute::contains(const std::string& attributeID) const
    {
        if (m_childAttributes.find(attributeID) != m_childAttributes.end())
            return true;
        return false;
    }

    void ComplexAttribute::createBaseAttribute(const std::string& attributeID, const Types::DataType& type, const std::string& data)
    {
        m_childAttributes[attributeID] = std::make_unique<BaseAttribute>(this, attributeID, type);
        getBaseAttribute(attributeID).autoset(data);
        if (!Functions::Vector::isInList(attributeID, m_childAttributesNames))
            m_childAttributesNames.push_back(attributeID);
    }

    void ComplexAttribute::createBaseAttribute(const std::string& attributeID, const Types::DataType& type)
    {
        m_childAttributes[attributeID] = std::make_unique<BaseAttribute>(this, attributeID, type);
        if (!Functions::Vector::isInList(attributeID, m_childAttributesNames))
            m_childAttributesNames.push_back(attributeID);
    }

    void ComplexAttribute::createBaseAttribute(const std::string& attributeID, const std::string& data)
    {
        m_childAttributes[attributeID] = std::make_unique<BaseAttribute>(this, attributeID, Types::String);
        getBaseAttribute(attributeID).set(data);
        if (!Functions::Vector::isInList(attributeID, m_childAttributesNames))
            m_childAttributesNames.push_back(attributeID);
    }

    void ComplexAttribute::createBaseAttribute(const std::string& attributeID, const char* data)
    {
        this->createBaseAttribute(attributeID, std::string(data));
    }

    void ComplexAttribute::createBaseAttribute(const std::string& attributeID, bool data)
    {
        m_childAttributes[attributeID] = std::make_unique<BaseAttribute>(this, attributeID, Types::Bool);
        getBaseAttribute(attributeID).set(data);
        if (!Functions::Vector::isInList(attributeID, m_childAttributesNames))
            m_childAttributesNames.push_back(attributeID);
    }

    void ComplexAttribute::createBaseAttribute(const std::string& attributeID, int data)
    {
        m_childAttributes[attributeID] = std::make_unique<BaseAttribute>(this, attributeID, Types::Int);
        getBaseAttribute(attributeID).set(data);
        if (!Functions::Vector::isInList(attributeID, m_childAttributesNames))
            m_childAttributesNames.push_back(attributeID);
    }

    void ComplexAttribute::createBaseAttribute(const std::string& attributeID, double data)
    {
        m_childAttributes[attributeID] = std::make_unique<BaseAttribute>(this, attributeID, Types::Float);
        getBaseAttribute(attributeID).set(data);
        if (!Functions::Vector::isInList(attributeID, m_childAttributesNames))
            m_childAttributesNames.push_back(attributeID);
    }

    void ComplexAttribute::pushBaseAttribute(BaseAttribute* attribute)
    {
        m_childAttributes[attribute->getID()] = std::unique_ptr<BaseAttribute>(attribute);
        if (!Functions::Vector::isInList(attribute->getID(), m_childAttributesNames))
            m_childAttributesNames.push_back(attribute->getID());
    }

    void ComplexAttribute::createListAttribute(const std::string& attributeID)
    {
        m_childAttributes[attributeID] = std::make_unique<ListAttribute>(this, attributeID);
        if (!Functions::Vector::isInList(attributeID, m_childAttributesNames))
            m_childAttributesNames.push_back(attributeID);
    }

    void ComplexAttribute::pushListAttribute(ListAttribute* attribute)
    {
        m_childAttributes[attribute->getID()] = std::unique_ptr<ListAttribute>(attribute);
        if (!Functions::Vector::isInList(attribute->getID(), m_childAttributesNames))
            m_childAttributesNames.push_back(attribute->getID());
    }

    void ComplexAttribute::createComplexAttribute(const std::string& attributeID)
    {
        m_childAttributes[attributeID] = std::make_unique<ComplexAttribute>(this, attributeID);
        if (!Functions::Vector::isInList(attributeID, m_childAttributesNames))
            m_childAttributesNames.push_back(attributeID);
    }

    void ComplexAttribute::pushComplexAttribute(ComplexAttribute* attribute)
    {
        m_childAttributes[attribute->getID()] = std::unique_ptr<ComplexAttribute>(attribute);
        if (!Functions::Vector::isInList(attribute->getID(), m_childAttributesNames))
            m_childAttributesNames.push_back(attribute->getID());
    }

    void ComplexAttribute::createLinkAttribute(const std::string& attributeID, const std::string& path)
    {
        m_childAttributes[attributeID] = std::make_unique<LinkAttribute>(this, attributeID, path);
        if (!Functions::Vector::isInList(attributeID, m_childAttributesNames))
            m_childAttributesNames.push_back(attributeID);
    }

    void ComplexAttribute::pushLinkAttribute(LinkAttribute* attribute)
    {
        m_childAttributes[attribute->getID()] = std::unique_ptr<LinkAttribute>(attribute);
        if (!Functions::Vector::isInList(attribute->getID(), m_childAttributesNames))
            m_childAttributesNames.push_back(attribute->getID());
    }

    void ComplexAttribute::write(std::ofstream* file, const std::string& spacing, unsigned int depth) const
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
                    for (const std::string& currentLink : node->getAll(Types::LinkAttribute))
                    {
                        std::vector<std::string> linkParts = Functions::String::split(node->getLinkAttribute(currentLink).getPath(), "/");
                        if (Functions::String::isStringInt(linkParts[linkParts.size() - 2]) && linkParts[linkParts.size() - 1] == "value")
                        {
                            if (stoi(linkParts[linkParts.size() - 2]) <= argsMap.size())
                            {
                                std::vector<std::string> argPathFragments = Functions::String::split(node->getLinkAttribute(currentLink).getNodePath(), "/");
                                argsMap[stoi(linkParts[linkParts.size() - 2])] = at<BaseAttribute>(Functions::Vector::join(argPathFragments, "/", 2)).returnData();
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

    void ComplexAttribute::deleteBaseAttribute(const std::string& attributeID, bool freeMemory)
    {
        if (Functions::Vector::isInList(attributeID, this->getAll(Types::BaseAttribute)))
            m_childAttributesNames.erase(m_childAttributesNames.begin() + Functions::Vector::indexOfElement(attributeID, m_childAttributesNames));
        typedef std::map<std::string, std::unique_ptr<Attribute>>::iterator it_type;
        it_type itDel = m_childAttributes.find(attributeID);
        if (itDel != m_childAttributes.end() && m_childAttributes[attributeID]->getType() == Types::BaseAttribute)
        {
            if (!freeMemory)
                m_childAttributes[attributeID].release();
            m_childAttributes.erase(itDel);
        }
    }

    void ComplexAttribute::deleteComplexAttribute(const std::string& attributeID, bool freeMemory)
    {
        if (Functions::Vector::isInList(attributeID, this->getAll(Types::ComplexAttribute)))
            m_childAttributesNames.erase(m_childAttributesNames.begin() + Functions::Vector::indexOfElement(attributeID, m_childAttributesNames));
        typedef std::map<std::string, std::unique_ptr<Attribute>>::iterator it_type;
        it_type itDel = m_childAttributes.find(attributeID);
        if (itDel != m_childAttributes.end() && m_childAttributes[attributeID]->getType() == Types::ComplexAttribute)
        {
            if (!freeMemory)
                m_childAttributes[attributeID].release();
            m_childAttributes.erase(itDel);
        }
    }

    void ComplexAttribute::deleteListAttribute(const std::string& attributeID, bool freeMemory)
    {
        if (Functions::Vector::isInList(attributeID, this->getAll(Types::ListAttribute)))
            m_childAttributesNames.erase(m_childAttributesNames.begin() + Functions::Vector::indexOfElement(attributeID, m_childAttributesNames));
        typedef std::map<std::string, std::unique_ptr<Attribute>>::iterator it_type;
        it_type itDel = m_childAttributes.find(attributeID);
        if (itDel != m_childAttributes.end() && m_childAttributes[attributeID]->getType() == Types::ListAttribute)
        {
            if (!freeMemory)
                m_childAttributes[attributeID].release();
            m_childAttributes.erase(itDel);
        }
    }

    void ComplexAttribute::deleteLinkAttribute(const std::string& attributeID, bool freeMemory)
    {
        if (Functions::Vector::isInList(attributeID, this->getAll(Types::LinkAttribute)))
            m_childAttributesNames.erase(m_childAttributesNames.begin() + Functions::Vector::indexOfElement(attributeID, m_childAttributesNames));
        typedef std::map<std::string, std::unique_ptr<Attribute>>::iterator it_type;
        it_type itDel = m_childAttributes.find(attributeID);
        if (itDel != m_childAttributes.end() && m_childAttributes[attributeID]->getType() == Types::LinkAttribute)
        {
            if (!freeMemory)
                m_childAttributes[attributeID].release();
            m_childAttributes.erase(itDel);
        }
    }

    void ComplexAttribute::copy(ContainerAttribute* newParent, const std::string& newid) const
    {
        std::string useID = (newid.empty()) ? this->m_id : newid;
        if (newParent->getType() == Types::ComplexAttribute)
        {
            dynamic_cast<ComplexAttribute*>(newParent)->createComplexAttribute(useID);
            for (const std::string& child : m_childAttributesNames)
            {
                m_childAttributes.at(child)->copy(&dynamic_cast<ComplexAttribute*>(newParent)->getComplexAttribute(useID));
            }
        }
        else
            throw aube::ErrorHandler::Raise("Vili.Vili.ComplexAttribute.WrongCopyTarget", {{"path", getNodePath()},{"target", newParent->getNodePath()}});
    }

    void ComplexAttribute::walk(std::function<void(NodeIterator&)> walkFunction, bool useCache)
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
            for (const std::string& complex : getAll(Types::ComplexAttribute))
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

    void ComplexAttribute::walk(std::function<void(NodeIterator&)> walkFunction, NodeIterator& iterator)
    {
        for (const std::string& complex : getAll(Types::ComplexAttribute))
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

    void ComplexAttribute::useTemplate(DataTemplate* useTemplate)
    {
        m_template = useTemplate;
    }

    DataTemplate* ComplexAttribute::getCurrentTemplate() const
    {
        return m_template;
    }
}
