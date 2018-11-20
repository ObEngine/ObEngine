#pragma once

namespace kaguya { class State; }

/**
* \brief Bindings to System related classes and functions
*/
namespace obe::Bindings::SystemBindings
{
    void LoadSystemConstants(kaguya::State* lua);
    void LoadSCursor(kaguya::State* lua);
    void LoadMountablePath(kaguya::State* lua);
    void LoadPath(kaguya::State* lua);
    void LoadPackage(kaguya::State* lua);
    void LoadWorkspace(kaguya::State* lua);
    void LoadWindow(kaguya::State* lua);
}