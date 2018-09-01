#pragma once

#include <memory>
#include <unordered_map>

#include <kaguya/kaguya.hpp>

#include <Bindings/BindingTree.hpp>

#include <dynamicLinker/dynamicLinker.hpp> // DON'T FUCKING MOVE THIS

#include <Config.hpp>
#include <Types/Global.hpp>

/**
* \brief Bind C++ Classes and Functions to Lua VMs
*/
namespace obe::Bindings
{
    GLOBE(0, BindTree, BindingTree);
    //GLOBE(0, HELLO_GLOBALS, int);
    //inline BindingTree BindTree("Root");

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
