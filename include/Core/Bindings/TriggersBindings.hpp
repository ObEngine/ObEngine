#pragma once

namespace kaguya
{
    class State;
}

/**
 * \brief Bindings to Triggers related classes and functions
 */
namespace obe::Bindings::TriggersBindings
{
    void LoadTrigger(kaguya::State* lua);
    void LoadTriggerDatabase(kaguya::State* lua);
    void LoadTriggerDelay(kaguya::State* lua);
    void LoadTriggerGroup(kaguya::State* lua);
} // namespace obe::Bindings::TriggersBindings