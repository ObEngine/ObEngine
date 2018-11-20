#pragma once

#include <memory>
#include <unordered_map>

namespace kaguya { class State; }

#include <Bindings/BindingTree.hpp>

#include <dynamicLinker/dynamicLinker.hpp> // DON'T FUCKING MOVE THIS

/**
* \brief Bind C++ Classes and Functions to Lua VMs
*/
namespace obe::Bindings
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
    void IndexBaseBindings();
    void IndexPluginsBindings();
}
