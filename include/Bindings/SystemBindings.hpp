#pragma once

#include <kaguya/kaguya.hpp>

namespace obe
{
    namespace Bindings
    {
        namespace SystemBindings
        {
            void LoadCursor(kaguya::State* lua);
            void LoadMountablePath(kaguya::State* lua);
            void LoadPath(kaguya::State* lua);
        }
    }
}