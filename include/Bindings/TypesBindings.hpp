#pragma once

#include <kaguya/kaguya.hpp>

namespace obe
{
    namespace Bindings
    {
        namespace TypesBindings
        {
            void LoadIdentifiable(kaguya::State* lua);
            void LoadSelectable(kaguya::State* lua);
            void LoadTogglable(kaguya::State* lua);
        }
    }
}