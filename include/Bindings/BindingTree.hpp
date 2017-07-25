#pragma once

#include <functional>
#include <vector>

#include <Bindings/BindingUtils.hpp>
#include <Types/Identifiable.hpp>

namespace obe
{
    namespace Bindings
    {
        extern std::function<void(kaguya::State*)> RegisterLib;

        class BindingTree : public Types::Identifiable
        {
        private:
            BindingTree* m_parent;
            std::vector<std::unique_ptr<BindingTree>> m_children;
            std::function<void(kaguya::State*)> m_lib;
            bool m_hasLib = false;
            std::string getNodePath() const;
        public:
            BindingTree(BindingTree* parent, const std::string& id, std::function<void(kaguya::State*)> lib);
            BindingTree(BindingTree* parent, const std::string& id);
            BindingTree(const std::string& id);
            BindingTree& operator[](const std::string& id);
            BindingTree& add(const std::string& id, std::function<void(kaguya::State*)> lib);
            BindingTree& add(const std::string& id);
            BindingTree& walkTo(std::vector<std::string> path);
            bool exists(const std::string& id);
            void operator()(kaguya::State* lua, bool spreads = true);
        };
    }
}
