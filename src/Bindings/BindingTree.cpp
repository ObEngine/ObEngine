#include <Bindings/BindingTree.hpp>
#include <Utils/VectorUtils.hpp>

namespace obe
{
    namespace Bindings
    {
        std::function<void(kaguya::State&)> NoLib = [](kaguya::State& lua){};

        BindingTree::BindingTree(const std::string& id, std::function<void(kaguya::State&)> lib) : Identifiable(id)
        {
            m_lib = lib;
        }
        BindingTree& BindingTree::operator[](const std::string& id)
        {
            for (auto& tree : m_children)
            {
                if (tree.getId() == id)
                    return tree;
            }
            // Add error <REVISION>
        }
        BindingTree& BindingTree::add(const std::string& id, std::function<void(kaguya::State&)> lib)
        {
            m_children.emplace_back(id, lib);
            return *this;
        }

        BindingTree& BindingTree::walkTo(std::vector<std::string> path)
        {
            if (this->exists(path[0]))
            {
                if (path.size() > 1)
                {
                    std::vector<std::string> subPath = Utils::Vector::getSubVector(path, 1, 0);
                    return this->operator[](path[0]).walkTo(subPath);
                }
                else if (path.size() == 1)
                {
                    return this->operator[](path[0]);
                }
            }
            else
            {
                // Raise Error <REVISION>
            }
        }

        bool BindingTree::exists(const std::string& id)
        {
            for (auto& tree : m_children)
            {
                if (tree.getId() == id)
                    return true;
            }
            return false;
        }

        void BindingTree::operator()(kaguya::State& lua)
        {
            for (auto& tree : m_children)
            {
                tree(lua);
            }
            std::cout << "Execute node " << m_id << std::endl;
            m_lib(lua);
            std::cout << "binding done" << std::endl;
        }
    }
}