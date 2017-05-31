#include <fstream>

#include "vili/LinkAttribute.hpp"
#include "Functions.hpp"

namespace vili
{
    LinkAttribute::LinkAttribute(ComplexAttribute* parent, const std::string& id, const std::string& path) : Attribute(parent, id, Types::LinkAttribute)
    {
        m_path = path;
    }

    Attribute* LinkAttribute::getTarget()
    {
        std::string linkroot = "";
        ComplexAttribute* complexParent = dynamic_cast<ComplexAttribute*>(m_parent);
        if (complexParent->contains(Types::BaseAttribute, "__linkroot__"))
            linkroot = complexParent->getBaseAttribute("__linkroot__").get<std::string>();
        ContainerAttribute* root = this->getParent();
        while (root->getParent() != nullptr)
            root = root->getParent();
        std::string abspath = linkroot + "/" + m_path;
        Attribute* location = root;
        std::vector<std::string> fullPath = Functions::String::split(abspath, "/");
        for (const std::string& pathPart : fullPath)
        {
            if (location->getType() == Types::ComplexAttribute)
            {
                ComplexAttribute* complexLocation = static_cast<ComplexAttribute*>(location);
                if (complexLocation->contains(Types::ComplexAttribute, pathPart))
                    location = &complexLocation->getComplexAttribute(pathPart);
                else if (complexLocation->contains(Types::BaseAttribute, pathPart))
                {
                    location = &complexLocation->getBaseAttribute(pathPart);
                    break;
                }
                else if (complexLocation->contains(Types::ListAttribute, pathPart))
                    location = &complexLocation->getListAttribute(pathPart);
                else
                    throw aube::ErrorHandler::Raise("Vili.Vili.LinkAttribute.WrongLinkPath", {{"path", getNodePath()},{"target", m_path},{"pathpart", pathPart}});
            }
            else if (location->getType() == Types::ListAttribute)
            {
                ListAttribute* listLocation = static_cast<ListAttribute*>(location);
                if (Functions::String::isStringInt(pathPart) && stoi(pathPart) < listLocation->size())
                    location = &listLocation->get(stoi(pathPart));
                else
                    throw aube::ErrorHandler::Raise("Vili.Vili.LinkAttribute.WrongLinkListIndex", {{"path", getNodePath()},{"target", m_path},{"index", pathPart}});
            }
        }
        return location;
    }

    std::string LinkAttribute::getPath() const
    {
        return m_path;
    }

    std::string LinkAttribute::getFullPath() const
    {
        std::string linkroot = "";
        ComplexAttribute* complexParent = dynamic_cast<ComplexAttribute*>(m_parent);
        if (complexParent->contains(Types::BaseAttribute, "__linkroot__"))
            linkroot = complexParent->getBaseAttribute("__linkroot__").get<std::string>();
        return linkroot + "/" + m_path;
    }

    void LinkAttribute::apply()
    {
        ComplexAttribute* complexParent = dynamic_cast<ComplexAttribute*>(m_parent);
        complexParent->deleteLinkAttribute(m_id);

        if (getTarget()->getType() == Types::ComplexAttribute)
            dynamic_cast<ComplexAttribute*>(getTarget())->copy(complexParent, m_id);
        else if (getTarget()->getType() == Types::ListAttribute)
            dynamic_cast<ListAttribute*>(getTarget())->copy(complexParent, m_id);
        else if (getTarget()->getType() == Types::BaseAttribute)
            dynamic_cast<BaseAttribute*>(getTarget())->copy(complexParent, m_id);
        else if (getTarget()->getType() == Types::LinkAttribute)
            dynamic_cast<LinkAttribute*>(getTarget())->copy(complexParent, m_id);
    }

    bool LinkAttribute::operator==(const LinkAttribute& compare) const
    {
        return (this->getFullPath() == compare.getFullPath());
    }

    void LinkAttribute::copy(ContainerAttribute* newParent, const std::string& newid) const
    {
        if (newParent->getType() == Types::ComplexAttribute)
            dynamic_cast<ComplexAttribute*>(newParent)->createLinkAttribute(newid.empty() ? m_id : newid, m_path);
        else
            throw aube::ErrorHandler::Raise("Vili.Vili.LinkAttribute.WrongCopyTarget", {{"path", getNodePath()},{"target", newParent->getNodePath()}});
    }

    void LinkAttribute::write(std::ofstream* file, const std::string& spacing, unsigned int depth) const
    {
        if (m_visible)
        {
            for (unsigned int j = 0; j < depth - 1; j++)
                (*file) << spacing;
            (*file) << m_id << ":&(" << getPath() << ")" << std::endl;
        }
    }

    void ListAttribute::reorder(int index)
    {
        for (int i = index + 1; i < m_dataList.size(); i++)
        {
            this->removeOwnership(m_dataList[i].get());
            m_dataList[i]->setID("#" + std::to_string(i));
            m_dataList[i]->setParent(this);
        }
    }
}
