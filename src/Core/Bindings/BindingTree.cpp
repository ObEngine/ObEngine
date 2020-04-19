#include <Bindings/BindingTree.hpp>

#include <Bindings/Exceptions.hpp>
#include <Debug/Logger.hpp>
#include <Utils/VectorUtils.hpp>

namespace obe::Bindings
{
    std::function<void(sol::state_view)> InitTreeNodeAsTable(const std::string& nodeName)
    {
        return [nodeName](sol::state_view lua) { lua.safe_script(nodeName + " = {};"); };
    }

    bool checkIfLuaElementExists(sol::state_view lua, const std::string& path)
    {
        const bool exists = lua["LuaCore"]["IsLibLoaded"](path);
        return exists;
    }

    BindingTree::BindingTree(BindingTree* parent, const std::string& id,
        std::function<void(sol::state_view)> lib)
        : Identifiable(id)
    {
        m_parent = parent;
        m_lib = lib;
        m_hasLib = true;
    }

    BindingTree::BindingTree(BindingTree* parent, const std::string& id)
        : Identifiable(id)
    {
        m_parent = parent;
        m_hasLib = false;
    }

    BindingTree::BindingTree(const std::string& id)
        : Identifiable(id)
    {
        m_parent = nullptr;
        m_hasLib = false;
    }

    std::string BindingTree::getNodePath() const
    {
        std::vector<std::string> parentChain;
        BindingTree* currentParent = m_parent;
        if (currentParent != nullptr)
        {
            while (currentParent != nullptr)
            {
                parentChain.push_back(currentParent->getId());
                currentParent = currentParent->m_parent;
            }
            parentChain.pop_back();
            reverse(parentChain.begin(), parentChain.end());
            parentChain.push_back(m_id);
            std::string retPath = Utils::Vector::join(parentChain, ".");
            return retPath;
        }
        else
        {
            return m_id;
        }
    }

    BindingTree& BindingTree::operator[](const std::string& id)
    {
        for (auto& tree : m_children)
        {
            if (tree->getId() == id)
                return *tree.get();
        }
        std::vector<std::string> childrenIds;
        childrenIds.reserve(m_children.size());
        for (const auto& child : m_children)
        {
            childrenIds.push_back(child->getId());
        }
        throw Exceptions::BindingTreeNodeNotFound(
            this->getNodePath(), id, childrenIds, EXC_INFO);
    }

    BindingTree& BindingTree::add(
        const std::string& id, std::function<void(sol::state_view)> lib)
    {
        m_children.push_back(std::make_unique<BindingTree>(this, id, lib));
        return *this;
    }

    BindingTree& BindingTree::add(const std::string& id)
    {
        m_children.push_back(std::make_unique<BindingTree>(this, id));
        return *this;
    }

    BindingTree& BindingTree::walkTo(std::vector<std::string> path)
    {
        if (this->exists(path[0]))
        {
            if (path.size() > 1)
            {

                const std::vector<std::string> subPath(path.begin() + 1, path.end());
                return this->operator[](path[0]).walkTo(subPath);
            }
            if (path.size() == 1)
            {
                return this->operator[](path[0]);
            }
        }
        else
        {
            std::vector<std::string> childrenIds;
            childrenIds.reserve(m_children.size());
            for (const auto& child : m_children)
            {
                childrenIds.push_back(child->getId());
            }
            throw Exceptions::BindingTreeNodeNotFound(
                this->getNodePath(), path[0], childrenIds, EXC_INFO);
        }
        return *this;
    }

    bool BindingTree::exists(const std::string& id)
    {
        for (auto& tree : m_children)
        {
            if (tree->getId() == id)
                return true;
        }
        return false;
    }

    void BindingTree::operator()(sol::state_view lua, bool spreads)
    {
        std::vector<BindingTree*> createNodePath;
        BindingTree* currentParent = m_parent;
        if (currentParent != nullptr)
        {
            while (currentParent != nullptr)
            {
                createNodePath.push_back(currentParent);
                currentParent = currentParent->m_parent;
            }
            createNodePath.pop_back();
            reverse(createNodePath.begin(), createNodePath.end());
            for (BindingTree* parentNode : createNodePath)
            {
                (*parentNode)(lua, false);
            }
        }
        const bool elementAlreadyExists
            = checkIfLuaElementExists(lua, this->getNodePath());
        if (!elementAlreadyExists && m_hasLib)
        {
            Debug::Log->debug(
                "<BindingTree> Loading Lua Binding : {0}", this->getNodePath());
            Debug::Log->flush();
            lua.safe_script(
                "table.insert(LuaCore.libList, '" + this->getNodePath() + "');");
            m_lib(lua);
        }
        if (spreads)
        {
            for (auto& tree : m_children)
            {
                (*tree)(lua);
            }
        }
    }
} // namespace obe::Bindings