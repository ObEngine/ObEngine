#pragma once

#include <kaguya/kaguya.hpp>

namespace obe
{
    namespace Bindings
    {
        /**
        * \brief Bindings to Types related classes and functions
        */
        namespace TypesBindings
        {
            void LoadIdentifiable(kaguya::State* lua);
            void LoadSelectable(kaguya::State* lua);
            void LoadSerializable(kaguya::State* lua);
            void LoadTogglable(kaguya::State* lua);
        }
    }
}