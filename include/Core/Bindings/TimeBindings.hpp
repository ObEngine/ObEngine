#pragma once

namespace kaguya
{
    class State;
}

/**
 * \brief Bindings to Time related classes and functions
 */
namespace obe::Bindings::TimeBindings
{
    void LoadChronometer(kaguya::State* lua);
    void LoadFPSCounter(kaguya::State* lua);
    void LoadFramerateManager(kaguya::State* lua);
    void LoadTimeCheck(kaguya::State* lua);
    void LoadTimeUtils(kaguya::State* lua);
} // namespace obe::Bindings::TimeBindings