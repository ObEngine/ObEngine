#pragma once

#include <kaguya/kaguya.hpp>

/**
 * \brief Bindings to Debug related classes and functions
 */
namespace obe::Bindings::DebugBindings
{
    void LoadConsoleMessage(kaguya::State* lua);
    void LoadConsoleStream(kaguya::State* lua);
    void LoadConsole(kaguya::State* lua);
} // namespace obe::Bindings::DebugBindings