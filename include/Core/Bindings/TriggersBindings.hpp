#pragma once

#include <kaguya/kaguya.hpp>

/**
* \brief Bindings to Triggers related classes and functions
*/
namespace obe::Bindings::TriggersBindings
{
    void LoadTrigger(kaguya::State* lua);
    void LoadTriggerDatabase(kaguya::State* lua);
    void LoadTriggerDelay(kaguya::State* lua);
    void LoadTriggerGroup(kaguya::State* lua);
}