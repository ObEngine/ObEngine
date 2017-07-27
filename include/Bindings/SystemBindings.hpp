#pragma once

#include <kaguya/kaguya.hpp>

namespace obe
{
    namespace Bindings
    {
        /**
        * \brief Bindings to System related classes and functions
        */
        namespace SystemBindings
        {
            void LoadSCursor(kaguya::State* lua);
            void LoadMountablePath(kaguya::State* lua);
            void LoadPath(kaguya::State* lua);
            void LoadPackage(kaguya::State* lua);
            void LoadWorkspace(kaguya::State* lua);
        }
    }
}