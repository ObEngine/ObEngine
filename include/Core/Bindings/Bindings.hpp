#pragma once

#include <memory>

#include <dynamicLinker/dynamicLinker.hpp>
#include <kaguya/kaguya.hpp>

#include <Bindings/BindingTree.hpp>

/**
* \brief Bind C++ Classes and Functions to Lua VMs
*/
namespace obe::Bindings
{
    extern BindingTree BindTree;
    extern std::map<std::string, std::shared_ptr<dynamicLinker::dynamicLinker>> Plugins;

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
    void IndexPlugins();
}
