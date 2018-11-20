#pragma once

namespace kaguya { class State; }

/**
* \brief Bindings to Script related classes and functions
*/
namespace obe::Bindings::ScriptBindings
{
    void LoadGameObject(kaguya::State* lua);
}