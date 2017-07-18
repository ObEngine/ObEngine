#pragma once

#include <functional>
#include <vector>

#include <Bindings/BindingUtils.hpp>
#include <Types/Identifiable.hpp>

namespace obe
{
    namespace Bindings
    {
        extern std::function<void(kaguya::State&)> NoLib;
        class BindingTree : public Types::Identifiable
        {
            private:
                std::vector<BindingTree> m_children;
                std::function<void(kaguya::State&)> m_lib;
            public:
                BindingTree(const std::string& id, std::function<void(kaguya::State&)> lib);
                BindingTree& operator[](const std::string& id);
                BindingTree& add(const std::string& id, std::function<void(kaguya::State&)> lib = NoLib);
                BindingTree& walkTo(std::vector<std::string> path);
                bool exists(const std::string& id);
                void operator()(kaguya::State& lua);
        };
    }
}