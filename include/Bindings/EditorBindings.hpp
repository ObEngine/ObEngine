#pragma once

#include <kaguya/kaguya.hpp>

namespace obe
{
    namespace Bindings
    {
        /**
        * \brief Bindings to Editor related classes and functions
        */
        namespace EditorBindings
        {
            void LoadEditorGrid(kaguya::State* lua);
        }
    }
}