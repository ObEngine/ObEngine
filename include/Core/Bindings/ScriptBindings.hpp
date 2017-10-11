#pragma once

#include <kaguya/kaguya.hpp>

namespace obe
{
    namespace Bindings
    {
        /**
        * \brief Bindings to Script related classes and functions
        */
        namespace ScriptBindings
        {
            void LoadGameObject(kaguya::State* lua);
        }
    }
}