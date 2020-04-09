#pragma once

#include <functional>
#include <vector>

#include <Types/Identifiable.hpp>

#include <sol/sol.hpp>

namespace obe::Bindings
{
    std::function<void(sol::state_view)> InitTreeNodeAsTable(const std::string& nodeName);

    /**
     * \brief Holds and indexes all the CXX Bindings for Lua
     */
    class BindingTree : public Types::Identifiable
    {
    private:
        std::vector<std::unique_ptr<BindingTree>> m_children {};
        bool m_hasLib = false;
        std::function<void(sol::state_view)> m_lib;
        BindingTree* m_parent;

        [[nodiscard]] std::string getNodePath() const;

    public:
        /**
         * \brief Builds a BindingTree Node with a lib
         * \param parent Parent of the BindingTree Node
         * \param id Id of the new BindingTree node
         * \param lib Lib of the BindingTree Node
         */
        BindingTree(BindingTree* parent, const std::string& id,
            std::function<void(sol::state_view)> lib);
        /**
         * \brief Builds a BindingTree Node
         * \param parent Parent of the BindingTree Node
         * \param id Lib of the BindingTree Node
         */
        BindingTree(BindingTree* parent, const std::string& id);
        /**
         * \brief Builds a BindingTree root (without parent)
         * \param id Id of the BindingTree root
         */
        BindingTree(const std::string& id);
        /**
         * \brief Adds a child with a lib to the BindingTree node
         * \param id Id of the BindingTree Node to add
         * \param lib Library of the new Node
         * \return A reference to the original BindingTree node (to chain calls)
         */
        BindingTree& add(const std::string& id, std::function<void(sol::state_view)> lib);
        /**
         * \brief Adds a child to the BindingTree node
         * \param id Id of the BindingTree Node to add
         * \return A reference to the original BindingTree node (to chain calls)
         */
        BindingTree& add(const std::string& id);
        /**
         * \brief Checks if the BindingTree node contains a child with the given
         * id \param id Id of the Node to check the existence \return true if
         * the Node exists in the BindingTree children, false otherwise
         */
        bool exists(const std::string& id);
        /**
         * \brief Loads the contained library
         * \param lua Lua VM where to load the library
         * \param spreads Should be equal to true if the Node will call
         * operator() on all its children, false otherwise
         */
        void operator()(sol::state_view lua, bool spreads = true);
        /**
         * \brief Accesses a direct child of the BindingTree Node
         * \param id Id of the child to access
         * \return A reference to the child if found (raises an
         * ObEngine.Bindings.BindingTree.ChildNotFound Exception otherwise)
         */
        BindingTree& operator[](const std::string& id);
        /**
         * \brief Walks to BindingTree node at path
         * \param path Path where to walk to (A std::vector of std::string
         * containing ids of the Nodes forming the path) \return A reference of
         * the BindingTree node if found (raises an
         * ObEngine.Bindings.BindingTree.ChildNotFound Exception otherwise)
         */
        BindingTree& walkTo(std::vector<std::string> path);
    };
} // namespace obe::Bindings
