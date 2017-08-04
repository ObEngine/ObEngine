#pragma once

#include <kaguya/kaguya.hpp>

#include <Bindings/BindingTree.hpp>

namespace obe
{
    /**
     * \brief Bind C++ Classes and Functions to Lua VMs
     */
    namespace Bindings
    {
        extern BindingTree BindTree;
        /**
         * \brief Loads a Library in the Lua VM
         * \param lua Lua VM where to load the library
         * \param lib Name of the library to load
         */
        void Load(kaguya::State* lua, const std::string& lib);
        /**
         * \brief To call when the engine starts, indexes all Lua bindings
         */
        void IndexBindings();
    }
}
