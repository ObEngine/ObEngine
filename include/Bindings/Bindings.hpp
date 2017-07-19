#pragma once

#include <Bindings/BindingTree.hpp>
#include <Bindings/BindingUtils.hpp>

namespace obe
{
    namespace Bindings
    {
        extern BindingTree BindTree;
        void BuildLuaLibPath(LuaTRef lua, std::vector<std::string>& path);
        void BuildLuaLibPath(kaguya::State& lua, const std::string& path);
        void Load(kaguya::State& lua, const std::string& lib);
        void IndexBindings();
    }
}
