#pragma once

#include <kaguya/kaguya.hpp>

namespace obe
{
    namespace Bindings
    {
        namespace InputBindings
        {
            void LoadKeyClass(kaguya::State* lua);
            void LoadKeyboardActionEvent(kaguya::State* lua);
            void LoadKeyboardAction(kaguya::State* lua);
            void LoadKeyboardManager(kaguya::State* lua);
        }
    }
}